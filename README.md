# Quiz Management System

## Overview

This project is a modular, menu-driven C program for managing quizzes, participants, and results. It allows users to add questions, take quizzes, view and search results, and persist all data in text files. The codebase is split into four main files for clarity and maintainability:

- `main.c` — Program entry point and menu logic
- `quiz.c` — Quiz-taking logic and input validation
- `question.c` — Question management (add/view/save/load)
- `result.c` — Result management (view/search/save/load)

---

## Data Structures

All files use these shared structures:

```c
#define MAX_QUESTIONS 100
#define MAX_PARTICIPANTS 100
#define MAX_ATTEMPTS 100
#define MAX_NAME_LENGTH 100
#define MAX_QUESTION_LENGTH 256
#define MAX_OPTION_LENGTH 128

typedef struct {
    char question[MAX_QUESTION_LENGTH];
    char options[4][MAX_OPTION_LENGTH];
    int correctOption;
} Question;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
    int totalQuestions;
    float percentage;
} Result;

typedef struct {
    char participantName[MAX_NAME_LENGTH];
    int score;
    int totalQuestions;
    float percentage;
} Attempt;
```

- `questions[]` — Stores all quiz questions.
- `results[]` — Stores the best result for each participant.
- `attempts[]` — Stores all quiz attempts (for search/history).
- `questionCount`, `participantCount`, `attemptCount` — Track the number of entries in each array.

---

## Workflow

1. **Startup:**
    - Loads questions from `questions.txt` and results from `results.txt`.
    - Initializes all global arrays and counters.
2. **Menu Loop:**
    - Displays a menu with options:
        1. Add Question
        2. View Questions
        3. Take Quiz
        4. View All Results
        5. Search Results by Name
        6. Save Data
        0. Exit
    - Waits for user input and invokes the corresponding function.
3. **Functionality:**
    - Each menu option triggers a function in the appropriate module (`question.c`, `quiz.c`, or `result.c`).
    - Data is updated in memory and saved to files as needed.
4. **Exit:**
    - Saves all data to files before exiting.

---

## File Storage

- **`questions.txt`**
    - Stores all quiz questions and options.
    - Format: number of questions, then for each question: text, four options, correct option.
- **`results.txt`**
    - Stores all participant results and all attempts.
    - Format: number of participants, then for each: name, score, total questions, percentage; then number of attempts, then for each: name, score, total questions, percentage.

---

## Source File Breakdown

### main.c — Program Entry and Menu

#### Functions
- **`main()`**
    - Loads questions and results from files.
    - Displays the main menu in a loop.
    - Handles user choices and calls the appropriate function.
- **`displayMenu()`**
    - Prints the main menu options.
- **`validateInput(int min, int max)`**
    - Reads and validates integer input from the user within a specified range.
- **`clearScreen()`**
    - Clears the terminal screen (cross-platform).

#### Menu Option Invocations
- **Add Question:** Calls `addQuestion()` from `question.c`.
- **View Questions:** Calls `viewQuestions()` from `question.c`.
- **Take Quiz:** Calls `takeQuiz()` from `quiz.c`.
- **View All Results:** Calls `viewResults()` from `result.c`.
- **Search Results by Name:** Calls `viewResultsByName()` from `result.c`.
- **Save Data:** Calls `saveQuestionsToFile()` and `saveResultsToFile()`.
- **Exit:** Calls `saveQuestionsToFile()` and `saveResultsToFile()` before exiting.

---

### question.c — Question Management

#### Functions
- **`addQuestion()`**
    - Prompts the user to enter a new question and four options.
    - Asks for the correct option (A-D, entered as 1-4).
    - Adds the question to the `questions[]` array and saves to file.
- **`viewQuestions()`**
    - Displays all questions and their options.
    - Shows the correct answer for each question.
- **`saveQuestionsToFile()`**
    - Writes all questions to `questions.txt` for persistence.
- **`loadQuestionsFromFile()`**
    - Reads questions from `questions.txt` at startup.

#### Data Flow
- When adding a question, the user is prompted for the question text and four options.
- The correct answer is specified as a number (1-4).
- All questions are saved to a text file for persistence.

---

### quiz.c — Quiz Logic

#### Functions
- **`takeQuiz()`**
    - Prompts the user for their name.
    - Asks each question in order, displaying options A-D.
    - Validates the user's answer.
    - Tracks the score and calculates the percentage.
    - Saves the result to both `results[]` and `attempts[]`.
    - Calls `saveResultsToFile()` to persist the result.
- **`validateInput(int min, int max)`**
    - Ensures the user enters a valid integer within the specified range.
- **`clearScreen()`**
    - Clears the terminal screen.

#### Data Flow
- The user is asked each question in turn.
- After the quiz, the score and percentage are shown.
- The result is saved for both summary and history.

---

### result.c — Result Management

#### Functions
- **`viewResults()`**
    - Displays all participants' best results in a table.
- **`viewResultsByName()`**
    - Prompts for a participant's name.
    - Displays all attempts by that participant.
- **`saveResultsToFile()`**
    - Writes all results and attempts to `results.txt`.
- **`loadResultsFromFile()`**
    - Reads results and attempts from `results.txt` at startup.

#### Data Flow
- Results are shown in a formatted table.
- Users can search for all attempts by a specific name.
- All data is saved and loaded from a text file.

---

## Example Workflow

1. **Start the program.**
2. **Add questions** (if none exist).
3. **Take a quiz** — user answers questions, result is saved.
4. **View all results** — see a summary of all participants.
5. **Search results by name** — see all attempts for a specific participant.
6. **Save data** — manually save to files (also happens on exit).
7. **Exit** — data is saved automatically.

---

## Function Reference (All Files)

### main.c
- `main()` — Program entry, menu loop.
- `displayMenu()` — Prints menu.
- `validateInput(int, int)` — Input validation.
- `clearScreen()` — Clears terminal.

### question.c
- `addQuestion()` — Add a new question.
- `viewQuestions()` — View all questions.
- `saveQuestionsToFile()` — Save questions to file.
- `loadQuestionsFromFile()` — Load questions from file.

### quiz.c
- `takeQuiz()` — Run the quiz for a user.
- `validateInput(int, int)` — Input validation.
- `clearScreen()` — Clears terminal.

### result.c
- `viewResults()` — View all results.
- `viewResultsByName()` — Search results by name.
- `saveResultsToFile()` — Save results to file.
- `loadResultsFromFile()` — Load results from file.

---

## Developer Notes

- All data is stored in simple text files for persistence.
- The user interacts via a clear, menu-driven interface.
- The code is modular and easy to extend or maintain.
- No external dependencies or libraries are required beyond the C standard library.

---

## Extending the Project

- To add new features (e.g., timed quizzes, question categories), add new functions to the relevant `.c` file and update the menu in `main.c`.
- To change data storage, update the file read/write logic in `question.c` and `result.c`.

---

## Summary

- The project is modular, with each `.c` file handling a specific aspect.
- All data is stored in simple text files for persistence.
- The user interacts via a clear, menu-driven interface.
- The code is easy to extend and maintain.

---

If you have questions about a specific function or want to extend the project, see the comments in each `.c` file or contact the maintainer. 