# Playfair Cipher System

A C++ implementation of an extended Playfair cipher, developed for my 4th Semester Information Security project at Punjab University.

## Features

- **Extended 6x6 Matrix**: Supports 26 letters and 10 digits (0-9).
- **Format-Preserving**: Maintains file structure, line breaks, and punctuation during encryption/decryption.
- **Keyword Management**: Save and load previously used keywords, securely protected by a Master Key.
- **File Operations**: Capable of encrypting and decrypting full text files smoothly.

## Compilation & Usage

Compile the project using G++ (C++11 or later):

```
g++ -o playfair main.cpp playfair.cpp
```

Run the compiled executable:

```
./playfair
```

The program will launch an interactive, menu-driven interface to handle encryption, decryption, and file operations.

## File Structure

- `playfair.h` / `playfair.cpp`: Core Playfair algorithm and matrix operations.
- `main.cpp`: Interactive menu and CLI interface.
