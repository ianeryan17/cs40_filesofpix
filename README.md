# 💻 CS40 Homework Assignment – filesofpix (Corrupted PGM Restoration in C)

This repository contains my solution to the **filesofpix** assignment for CS40 (Machine Structure and Assembly Language Programming), a course I completed at Tufts University. The assignment focused on restoring corrupted PGM image files by parsing infusion sequences and digit sequences using Hanson data structures and outputting the original PGM image.

---

## 📚 Topics Covered

- Parsing dynamic-length lines from files with safe reallocation  
- Splitting lines into digit and infusion sequences  
- Using Hanson’s Table, Seq, and Atom modules for efficient key-value mapping  
- Reconstructing original pixel data by detecting repeated infusion keys  
- Printing valid PGM files with correct headers and pixel data  
- Careful memory management and cleanup of dynamically allocated buffers  
- Integration with the PNM Reader library for reading image metadata

---

## 📂 Repository Contents
| File            | Description                                 |
|-----------------|---------------------------------------------|
| `filesofpix.c`  | Main program for corrupted PGM restoration |
| `readaline.c`   | Reads a single line from input dynamically  |
| `parsealine.c`  | Parses lines into digit and infusion sequences |
| `tablecompare.c`| Inserts infusion-digit pairs into Hanson Table |
| `printpgm.c`    | Prints restored PGM file output              |
| `table.h`       | Hanson Table data structure header           |
| `seq.h`         | Hanson Seq data structure header             |
| `atom.h`        | Hanson Atom data structure header            |
| `except.h`      | Hanson exception handling utilities          |
| `Makefile`      | Build configuration                           |
| `.gitignore`    | Ignore build artifacts and temp files        |
| `README.md`     | This file                                     |

---

## ▶️ Running the filesofpix Program

### 🛠 Requirements

- GCC or compatible C compiler  
- Hanson CS40 support files: `table.h`, `seq.h`, `atom.h`, `except.h`  
- Standard POSIX environment

### 🔧 Build & Run
```bash
make
./filesofpix corrupted.pgm > restored.pgm
```

Replace corrupted.pgm with your corrupted PGM filename. The program reads the corrupted file, reconstructs the original pixel data, and writes a valid raw PGM image to standard output.

---

## 🏗 Architecture Overview

**`filesofpix.c`**

- Opens input file or reads from stdin  
- Repeatedly reads lines dynamically using `readaline()`  
- Parses each line into digit and infusion sequences with `parsealine()`  
- Uses `tablecompare()` to insert infusion-digit pairs into a Hanson Table, tracking duplicates to identify original pixel lines  
- Collects all original lines in a Hanson Seq sequence  
- Outputs restored PGM data with correct headers using `printpgm()`  
- Frees all dynamically allocated memory with `free_mem()`

**`readaline.c`**

- Reads an entire line from input, dynamically resizing buffer as needed to handle arbitrary line lengths  
- Returns the length of the line or zero on EOF

**`parsealine.c`**

- Splits a line into two arrays: digits (pixel values) and infusion characters (whitespace and other separators)  
- Adds these parsed arrays to sequences for later cleanup

**`tablecompare.c`**

- Uses Hanson Atoms to create keys from infusion sequences  
- Inserts key-value pairs into a Hanson Table, where values are digit arrays  
- Tracks original lines when duplicate keys appear

**`printpgm.c`**

- Prints PGM header: magic number, width, height, and max grayscale value  
- Prints pixel data lines as ASCII characters

**`free_mem()`**

- Frees all allocated memory for sequences, tables, and buffers to prevent leaks

---

## 🧪 Testing & Validation

- Tested with multiple corrupted PGM files  
- Verified output files load correctly in standard PGM viewers  
- Checked memory usage with valgrind to ensure no leaks

---

## 🧠 What I Learned

- Efficiently parsing and handling arbitrary-length input lines in C  
- Using Hanson’s data structures to solve non-trivial mapping problems  
- Reconstructing image files from partial and corrupted data  
- Writing robust C code with proper error checking and memory management  
- Handling PGM file format details and pixel output formatting

---

## 🏫 About the Course

CS40: Machine Structure and Assembly Language Programming,  
Tufts University – Fall 2023

---

## 📄 License  

This code was developed as part of an academic assignment and is shared for educational purposes only. Please do not plagiarize. Contact me if you'd like to discuss or learn more about this project.
