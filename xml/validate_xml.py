from lxml import etree

def process_xinclude_and_validate(xml_file, xsd_file):
    # Parse the main XML file with XInclude processing
    parser = etree.XMLParser(load_dtd=True, no_network=False)
    tree = etree.parse(xml_file, parser)
    tree.xinclude()

    # Validate against the schema
    schema = etree.XMLSchema(file=xsd_file)
    schema.assertValid(tree)
    print("XML is valid.")

if __name__ == "__main__":
    xml_file = 'books.xml'
    xsd_file = 'books.xsd'
    process_xinclude_and_validate(xml_file, xsd_file)