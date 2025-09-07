# CLI Quiz Game in C++

A command-line quiz application that reads questions from a text file and maintains a local ranking system.

# Description
This project is an interactive quiz game that presents multiple-choice questions (A-D) to users. The program loads questions from a text file, tracks player scores, and maintains a persistent ranking system in a separate file.

# Features
- Reads questions from external text files

- Real-time scoring system

- Persistent ranking storage between sessions

- Input validation (A-D only)

- Portuguese language interface

- Play again option

- Sorted ranking display

 Compilation & Execution
bash
# Compile the program
g++ -o quiz quiz.cpp

# Run the program
./quiz
 Project Details
 
# File Structure:
```
quiz.cpp - Main source code

questions.txt - Questions and answers data file

ranking.txt - Player scores storage (auto-generated)
```

# Code Structure:
```

Question struct - Stores question data

makeaquestion() - Question creation function

PrintQuestion() - Displays questions

WriteRanking() - Updates ranking file

PrintRanking() - Displays sorted rankings
```

Developed as a C++ programming exercise focusing on file handling and data structures. Perfect for learning and fun!
