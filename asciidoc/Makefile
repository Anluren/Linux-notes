# Define the AsciiDoc file and the output files
ASCIIDOC_MAIN_FILE = asciidoc_note.adoc
PDF_FILE = asciidoc_note.pdf
HTML_FILE = asciidoc_note.html
THEME_FILE = custom-theme.yml

# Find all .adoc files except the main one
ASCIIDOC_ADDITIONAL_FILES = $(filter-out $(ASCIIDOC_MAIN_FILE), $(wildcard *.adoc))

# Default target
all: $(PDF_FILE) $(HTML_FILE)

# Rule to convert AsciiDoc to PDF with custom theme and section numbers
$(PDF_FILE): $(ASCIIDOC_MAIN_FILE) $(ASCIIDOC_ADDITIONAL_FILES) $(THEME_FILE)
	asciidoctor-pdf -r asciidoctor-diagram -a pdf-theme=$(THEME_FILE) -a sectnums $(ASCIIDOC_MAIN_FILE) -o $(PDF_FILE)

# Rule to convert AsciiDoc to HTML with section numbers
$(HTML_FILE): $(ASCIIDOC_MAIN_FILE) $(ASCIIDOC_ADDITIONAL_FILES)
	asciidoctor -r asciidoctor-diagram -a sectnums $(ASCIIDOC_MAIN_FILE) -o $(HTML_FILE)

# Clean target to remove the generated files
clean:
	rm -f $(PDF_FILE) $(HTML_FILE)

# Phony targets
.PHONY: all clean
