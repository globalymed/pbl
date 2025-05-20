# Quiz Management System (Modular C Version)

A modular C-based quiz application for creating, managing, and taking multiple-choice quizzes. The system is split into logical components for maintainability and extensibility.

---

## Features

- **Add Questions**: Create multiple-choice questions (4 options each)
- **View Questions**: Display all questions in the database
- **Take Quiz**: Attempt quizzes and receive scores
- **View Results**: See all participants' performance
- **Search by Name**: Retrieve quiz results for a specific participant
- **Data Persistence**: Questions and results are saved in text files

---

## System Requirements

- C compiler (GCC recommended)
- Windows, Linux, or macOS

---

## Build Instructions

### Using Makefile (Recommended)

1. Open a terminal/command prompt in the project directory.
2. Run:
   ```sh
   make
   ```
   This will produce an executable named `quiz_system` (or `quiz_system.exe` on Windows).

### Manual Compilation

If you do not have `make`, compile with:
```sh
gcc -o quiz_system main.c question.c quiz.c result.c
```

---

## Run Instructions

- On **Windows**:
  ```sh
  quiz_system.exe
  ```
- On **Linux/macOS**:
  ```sh
  ./quiz_system
  ```

---

## Usage Guide

### Main Menu
You will see:
```
====== QUIZ MANAGEMENT SYSTEM ======
1. Add Question
2. View Questions
3. Take Quiz
4. View All Results
5. Search Results by Name
6. Save Data
0. Exit
====================================
Enter your choice:
```

### 1. Add Question
- Enter the question text
- Enter 4 options (A-D)
- Enter the correct option (1-4 for A-D)
- The question is saved to `questions.txt`

### 2. View Questions
- Lists all questions and their options
- Shows the correct answer for each

### 3. Take Quiz
- Enter your name
- Answer each question (1-4 for A-D)
- At the end, your score and percentage are shown
- Your result is saved to `results.txt`

### 4. View All Results
- Displays all participants' scores and percentages

### 5. Search Results by Name
- Enter a participant's name to see all their quiz attempts

### 6. Save Data
- Manually saves questions and results to their respective files

### 0. Exit
- Saves all data and exits the program

---

## Data Storage

- `questions.txt`: Stores all quiz questions and options in plain text
- `results.txt`: Stores all participant results and attempt history in plain text

**Note:** Data is loaded from these files at startup and saved after relevant operations.

---

## Project Structure

- `main.c`      : Handles the main menu and program flow
- `question.c`  : Functions for adding, viewing, saving, and loading questions
- `quiz.c`      : Quiz logic (conducting the quiz, input validation, screen clearing)
- `result.c`    : Functions for viewing and saving results
- `quiz.h`      : Shared data structures, constants, extern variables, and function prototypes
- `Makefile`    : For easy compilation

---

## Extending the System

- Add new features by creating additional `.c`/`.h` files and updating the Makefile
- To add new data fields, update the structs in `quiz.h` and adjust file I/O accordingly
- For advanced features (timers, categories, analytics), modularize further as needed

---

## Troubleshooting

- If you see warnings about `system("cls")` or `system("clear")`, they are safe to ignore (used for screen clearing)
- Ensure you have write permissions in the project directory for data files
- If you encounter build errors, ensure all `.c` and `.h` files are present and included in the build command

---

## License

This project is provided for educational purposes. Feel free to modify and extend it! 