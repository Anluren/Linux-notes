from lxml import etree
import copy

class MyElement(etree.ElementBase):
    def my_custom_method(self):
        print(f"Element tag: {self.tag}")

# Custom lookup class
class MyLookup(etree.CustomElementClassLookup):
    def lookup(self, node_type, document, namespace, name):
        if node_type == 'element':
            return MyElement

# Set the custom lookup
lookup = MyLookup()
parser = etree.XMLParser()
parser.set_element_class_lookup(lookup)

# Parse the XML file using the custom parser
tree = etree.parse('/home/dzheng/workspace/Linux-notes/xml/books.xml', parser)

# Process XInclude
tree.xinclude()

# Function to graft an element from one tree to another
def graft_element(source_element, target_parent):
    # Detach the element from its original tree
    source_element.getparent().remove(source_element)
    # Append the element to the target parent
    target_parent.append(source_element)

# Replace an element with a new type
def replace_element(old_element, new_tag):
    new_element = etree.Element(new_tag)
    new_element[:] = old_element[:]
    new_element.text = old_element.text
    new_element.tail = old_element.tail
    for key, value in old_element.attrib.items():
        new_element.set(key, value)
    parent = old_element.getparent()
    if parent is not None:
        parent.replace(old_element, new_element)
    return new_element

# Example usage of the custom method and replacing elements
root = tree.getroot()

# Create a new tree to graft elements into
new_root = etree.Element("new_catalog")
new_tree = etree.ElementTree(new_root)

# Iterate over all elements from the root
for elem in root.iter():
    if isinstance(elem, MyElement):
        elem.my_custom_method()
        # Replace the element with a new type
        replace_element(elem, "new_tag")
        # Graft the element to the new tree
        graft_element(elem, new_root)

# Example usage of deepcopying an element
original_element = root.find(".//book")
deepcopied_element = copy.deepcopy(original_element)
new_root.append(deepcopied_element)

# Write the adjusted XML to a new file
new_tree.write('/home/dzheng/workspace/Linux-notes/xml/processed_books.xml', pretty_print=True, xml_declaration=True, encoding='UTF-8')

# Pretty-print the new_root element
pretty_xml = etree.tostring(new_root, pretty_print=True, xml_declaration=True, encoding='UTF-8').decode('UTF-8')
print(pretty_xml)