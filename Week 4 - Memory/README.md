# Week 4: Memory

This week focused on memory-related concepts in C, including pointers, arrays, and dynamic memory allocation. We explored how programs manage memory, how files are represented in bytes, and how we can manipulate image files and recover lost data.

## Problem Set

### Volume  
Modify the volume of an audio file in WAV format by scaling its sample values.

- **Problem to Solve:**  
  WAV files store audio as a sequence of “samples”: numbers that represent the value of some audio signal at a particular point in time. WAV files begin with a 44-byte “header” that contains information about the file itself, including the size of the file, the number of samples per second, and the size of each sample. After the header, the WAV file contains a sequence of samples, each a single 2-byte (16-bit) integer.

  Scaling each sample value by a given factor changes the audio's volume. For example, multiplying by 2.0 doubles the volume, while multiplying by 0.5 cuts it in half.

- **Objective:**  
  In a file called `volume.c` in a folder called `/volume/`, write a program to modify the volume of an audio file.

### Filter (Less Comfortable)  
Applies different filters to a BMP image file using loops and basic pixel manipulation.

- **Objective:**  
  Implement grayscale, sepia, reflect, and blur filters by manually modifying each pixel's RGB values.

### Filter (More Comfortable)  
Extends the less comfortable version by introducing edge detection and using convolution algorithms.

- **Objective:**  
  In addition to grayscale, sepia, reflect, and blur, implement the Sobel operator to detect edges in an image.

### Recover  
Recovers JPEG images from a forensic image by scanning for file signatures and writing each JPEG to a separate file.

- **Objective:**  
  Use byte-level manipulation and file operations to recover JPEGs from a raw memory card image.

## Files

- `/volume/` – Audio volume adjustment program
- `/filter/less/` – Filter implementation (less comfortable version)
- `/filter/more/` – Filter implementation (more comfortable version)
- `/recover/` – JPEG recovery script
- `/submissions/` – Screenshots and links of CS50 check/submit results
