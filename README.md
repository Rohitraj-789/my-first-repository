# Student Management System (C++)

A beginner-friendly console project demonstrating structures, vectors, functions,
loops, conditional statements, searching, and file handling in C++.

## Features
- Add a student record
- Display all student records
- Search by roll number
- Update a record
- Delete a record
- Store records in `students.txt` so they remain after the program closes

## Requirements
- A C++ compiler supporting C++17 (such as g++)

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra -o student_management main.cpp
./student_management
```
On Windows with MinGW:
```bash
g++ -std=c++17 -Wall -Wextra -o student_management.exe main.cpp
student_management.exe
```

The program creates `students.txt` in the current working directory when records are saved.
Use names and course names without the `|` character because it is used as the file delimiter.

## Suggested tests
1. Add a student and display all records.
2. Search for an existing roll number.
3. Search for a roll number that does not exist.
4. Update a student's course or marks.
5. Delete a student and display the list again.
6. Exit and reopen the program to confirm that records persist.
7. Try an invalid menu choice and marks outside the 0–100 range.

This is an educational sample project. Customize and test it before submitting it as your own internship work.
