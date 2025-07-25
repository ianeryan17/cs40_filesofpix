# 💻 CS40 Homework Assignment – Universal Machine Emulator (C)

This repository contains my solution to Homework 6 for CS40 (Machine Structure and Assembly Language Programming), a course I completed at Tufts University. The assignment focused on building a Universal Machine (UM) emulator in C that supports segmented memory, register-based instructions, and efficient execution of UM programs.

---

## 📚 Topics Covered

- Emulating a register-based Universal Machine (UM)
- Implementing segmented memory with mapping and unmapping
- Bit-packing and instruction decoding
- Switch-case dispatch for opcode execution
- Efficient memory management with UArrays and sequences
- Assertion-based error handling for invalid operations
- Performance optimization techniques for large instruction counts

---

## 📂 Repository Contents

| File           | Description                                |
| -------------- | ------------------------------------------ |
| `um.c`         | Main program reader and entrypoint         |
| `um_driver.c`  | Core UM runtime, command execution logic   |
| `segments.c`   | Segmented memory implementation            |
| `segments.h`   | Header for segmented memory module         |
| `callmain.ums` | μASM file to call main and halt (provided) |
| `printd.ums`   | μASM helper to print integers (provided)   |
| `urt0.ums`     | μASM stack initialization (provided)       |
| `Makefile`     | Build configuration                        |
| `.gitignore`   | Ignore build artifacts and temp files      |
| `README.md`    | This file                                  |

---

## ▶️ Running the UM Emulator

### 🛠 Requirements

- GCC or compatible C compiler
- Tufts CS40 support files: uarray.h, seq.h, bitpack.h, atom.h, table.h, etc.
- Standard POSIX environment

### 🔧 Build & Run

```bash
make
./um hello.um
```

Replace hello.um with any valid UM program file. The emulator reads the program, initializes segmented memory, and executes instructions until halt or program end.

---

## 🏗 Architecture Overview

`um.c`

- Reads a .um file, converts its contents into 32-bit words using UArray_T
- Passes the program array to run() to start emulation

`um_driver.c`

- Implements the main UM runtime loop and instruction execution
- Maintains program counter, registers array, and segmented memory instance
- Uses a switch statement for fast opcode dispatch
- Implements each opcode command (conditional_move, segmented_load, halt, etc.) as an inline function
- Uses assertions to catch invalid register indices and illegal operations

`segments.c`

- Implements segmented memory as a table mapping segment IDs to UArray_T sequences of 32-bit words
- Tracks unmapped segment IDs for reuse, avoiding ID exhaustion
- Supports mapping new zero-initialized segments and unmapping existing ones
- Provides word-level load and store functions with bounds checking
- Manages segment 0 specially as the currently running program segment
- Includes cleanup functions to free individual and all segments from memory safely

---

## 🧪 Test Programs Included (umtests/)

| Test Name       | Description                                     |
| --------------- | ----------------------------------------------- |
| `halt.um`       | Tests halt instruction stops execution          |
| `load_val.um`   | Tests loading immediate values into registers   |
| `output.um`     | Tests character output via the output opcode    |
| `add.um`        | Tests basic addition instruction                |
| `map1.um`       | Tests segment mapping                           |
| `input.um`      | Tests input instruction and EOF handling        |
| `operations.um` | Tests combined instruction set with various ops |

---

## ⏳ Performance

- Initial design using sequences for segments was too slow on large inputs
- Refactored to use UArray_T for segments to reduce overhead
- Optimized mapping/unmapping logic and segment copying using UArray_copy
- Switching from sequences to arrays for registers improved speed
- Using switch-case instead of function pointers sped up opcode dispatch
- Example: Emulator ran 50 million instructions in approximately 27 hours and 47 minutes on a midmark.um test

---

## 🕒 Time Spent

- Analyzing the assignment: ~3 hours
- Preparing design and architecture: ~10 hours
- Implementation and debugging: ~20 hours

---

## 🧠 What I Learned

- Implementing a complex virtual machine architecture in C
- Designing and managing segmented memory with dynamic allocation and reuse
- Low-level bit manipulation for instruction decoding
- Balancing code correctness with runtime performance optimizations
- Using assertions effectively to detect and prevent invalid operations
- Modular program design separating memory management and execution logic

---

## 🏫 About the Course

CS40: Machine Structure and Assembly Language Programming,
Tufts University – Fall 2023

---

## 📄 License

This code was developed as part of an academic assignment and is shared for educational purposes only. Please do not plagiarize. Contact me if you'd like to discuss or learn more about this project.
