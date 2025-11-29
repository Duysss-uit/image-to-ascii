# **High-Resolution ASCII Art Renderer**

## **Overview**

This project is a C++ implementation of an image-to-ASCII converter that utilizes TrueType font rendering to generate high-resolution output images. Unlike traditional ASCII generators that output text to the console, this tool rasterizes individual characters into a graphics buffer, preserving the color fidelity and structural details of the original input image.

The application is built with a focus on performance and minimal dependencies, utilizing the single-header STB libraries for image processing and font parsing.

## **Key Features**

* **TrueType Font Rasterization:** Implements stb\_truetype.h to parse .ttf files and render glyphs directly onto the image buffer.  
* **Color Preservation:** Analyzes input pixel data to apply accurate RGB coloring to generated ASCII characters.  
* **Minimal Dependencies:** Built entirely using header-only libraries (stb\_image, stb\_image\_write, stb\_truetype). No external installation or complex linking (e.g., OpenCV, Boost) is required.  
* **Configurable Resolution:** Allows adjustment of sampling steps and font sizes to balance between output detail and file size.

## **Dependencies**

* **C++ Compiler:** GCC, Clang, or MSVC supporting C++11 or later.  
* **STB Libraries:** Included in the project source (or available at [nothings/stb](https://github.com/nothings/stb)).  
* **Font File:** A valid TrueType Font (.ttf) file.

## **Project Structure**

.  
├── main.cpp                \# Entry point and core rendering logic  
├── stb\_image.h             \# Library for loading image files  
├── stb\_image\_write.h       \# Library for writing image files  
├── stb\_truetype.h          \# Library for font parsing and rasterization  
├── font.ttf                \# (User provided) Font resource  
└── input.jpg               \# (User provided) Input image

## **Build Instructions**

This project does not require a build system like CMake, though one can be added. It can be compiled directly using g++ or clang++.

**Optimization Note:** It is highly recommended to use the \-O3 optimization flag, as the rendering pipeline involves intensive pixel manipulation loops.

### **Linux / macOS**

g++ main.cpp \-o ascii\_renderer \-O3

### **Windows (MinGW)**

g++ main.cpp \-o ascii\_renderer.exe \-O3

## **Usage**

1. Ensure a source image named input.jpg and a font file named font.ttf are present in the executable directory.  
2. Run the application:  
   ./ascii\_renderer

3. The output will be saved as output\_final.jpg.

## **Configuration**

Rendering parameters can be modified directly in main.cpp via the following constants:

* step: Determines the sampling interval (grid size) of the original image.  
* fontSize: Specifies the pixel height of the rendered characters.  
* ASCII\_CHARS: The character set used for luminance mapping.

// Configuration snippet in main.cpp  
int step \= 8;           // Sample every 8th pixel  
float fontSize \= 24.0f; // Render characters at 24px height

## **Technical Implementation Details**

The rendering pipeline operates in the following stages:

1. **Initialization:** The stb\_truetype library parses the provided font file to retrieve glyph indices and metric data (ascent, descent, line gap).  
2. **Sampling:** The input image is traversed in a grid pattern defined by the step variable. The average color and luminance of each grid cell are calculated.  
3. **Glyph Selection:** Luminance values are mapped to an index within the ASCII\_CHARS string to select the appropriate character density.  
4. **Rasterization & Blitting:**  
   * The selected character is rasterized into a temporary 8-bit alpha bitmap.  
   * This bitmap is blitted onto the destination RGB buffer.  
   * Pixel colors from the source image are applied to the non-transparent pixels of the glyph.  
5. **Output:** The final buffer is encoded and written to disk using stb\_image\_write.

## **License**

This project is open-source and available under the MIT License.