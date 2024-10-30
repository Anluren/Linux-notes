# Define the AsciiDoc file and the output files
ASCIIDOC_MAIN_FILE = asciidoc_note.adoc
PDF_FILE = asciidoc_note.pdf
HTML_FILE = asciidoc_note.html

# Find all .adoc files except the main one
ASCIIDOC_ADDITIONAL_FILES = $(filter-out $(ASCIIDOC_MAIN_FILE), $(wildcard *.adoc))

# Default target
all: $(PDF_FILE) $(HTML_FILE)

# Rule to convert AsciiDoc to PDF
$(PDF_FILE): $(ASCIIDOC_MAIN_FILE) $(ASCIIDOC_ADDITIONAL_FILES)
	asciidoctor-pdf $(ASCIIDOC_MAIN_FILE) -o $(PDF_FILE)

# Rule to convert AsciiDoc to HTML
$(HTML_FILE): $(ASCIIDOC_MAIN_FILE) $(ASCIIDOC_ADDITIONAL_FILES)
	asciidoctor $(ASCIIDOC_MAIN_FILE) -o $(HTML_FILE)

# Clean target to remove the generated files
clean:
	rm -f $(PDF_FILE) $(HTML_FILE)

# Phony targets
.PHONY: all clean
