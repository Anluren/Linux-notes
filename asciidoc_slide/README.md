# Creating Slides with AsciiDoc

Follow these steps to create slides using AsciiDoc:

1. **Install Asciidoctor**:
    ```sh
    gem install asciidoctor
    ```

2. **Install Asciidoctor Reveal.js**:
    ```sh
    gem install asciidoctor-revealjs
    ```

3. **Create Your AsciiDoc File**:
    - Create a new file with the `.adoc` extension.
    - Add your slide content using AsciiDoc syntax.

4. **Convert AsciiDoc to HTML Slides**:
    ```sh
    asciidoctor-revealjs yourfile.adoc
    ```

5. **Open the Generated HTML File**:
    - Open the generated `yourfile.html` in a web browser to view your slides.

6. **Customize Your Slides** (Optional):
    - You can customize the appearance and behavior of your slides by modifying the AsciiDoc file or using Reveal.js options.

Example of a simple AsciiDoc slide:

```adoc
= Presentation Title
Author Name
:revealjs_theme: simple

== Slide 1
Content for slide 1.

== Slide 2
Content for slide 2.
```

For more details, refer to the [AsciiDoctor Reveal.js documentation](https://asciidoctor.org/docs/asciidoctor-revealjs/).
7. **Install Reveal.js Locally** (Optional):
    - If you prefer to use a local version of Reveal.js, you can download it from the [Reveal.js GitHub repository](https://github.com/hakimel/reveal.js/).
    - Extract the downloaded archive and place it in a directory of your choice.
    - Update your AsciiDoc file to point to the local Reveal.js files by setting the `revealjsdir` attribute:

    ```adoc
    :revealjsdir: path/to/reveal.js
    ```

    - Convert your AsciiDoc file to HTML slides as before:

    ```sh
    asciidoctor-revealjs yourfile.adoc
    ```

    - Open the generated `yourfile.html` in a web browser to view your slides using the local Reveal.js files.


   add following contents to the slides
    ```
    = My Presentation
Author Name
:revealjs_theme: white
:revealjs_transition: slide
:revealjsdir: reveal.js/reveal.js-4.1.0
:stylesheet: custom.css
:source-highlighter: rouge
:plantuml:

    ```

generating slide:
```bash
asciidoctor-revealjs -r asciidoctor-diagram my_presentation.adoc
```

8. **Preview Slides with Live Server** (Optional):
    - Install the Live Server extension in Visual Studio Code.
    - Open your workspace in Visual Studio Code.
    - Right-click on the generated `yourfile.html` file and select "Open with Live Server".
    - Your default web browser will open and display the slides. Any changes you make to the AsciiDoc file will be automatically reflected in the browser.