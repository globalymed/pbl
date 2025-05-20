# Quiz Management System

A C-based quiz application that allows for creating, managing, and taking multiple-choice quizzes.

## Features

- **Add Questions**: Create multiple-choice questions with 4 options each
- **View Questions**: Display all questions in the database
- **Take Quiz**: Allow users to attempt quizzes and receive scores
- **View Results**: See all participants' performance
- **Search by Name**: Retrieve quiz results for a specific participant
- **Data Persistence**: Automatically saves and loads quiz data

## System Requirements

- C compiler (GCC recommended)
- Windows or Linux operating system

## How to Compile

```
gcc main.c -o quiz_system
```

## How to Run

```
./quiz_system
```

On Windows:
```
quiz_system.exe
```

## Usage Instructions

### Adding Questions
1. Choose option 1 from the main menu
2. Enter the question text
3. Enter 4 possible answers (labeled A-D)
4. Specify which option is correct (1-4)

### Taking a Quiz
1. Choose option 3 from the main menu
2. Enter your name
3. Answer each question by selecting options 1-4 (for A-D)
4. View your score at the end

### Viewing Results
- Option 4: View all participants' results
- Option 5: Search for a specific participant's results by name

## Data Storage

The system stores data in three binary files:
- `questions.dat`: Contains all quiz questions
- `results.dat`: Contains latest results for each participant
- `attempts.dat`: Contains history of all quiz attempts

## Project Structure

- `main.c`: Contains all the code for the Quiz Management System
- `questions.dat`: Binary file for question storage
- `results.dat`: Binary file for results storage
- `attempts.dat`: Binary file for attempt history storage

## Future Enhancements

- Add date/time tracking for quiz attempts
- Multiple quiz categories
- User authentication system
- Timer for quizzes
- Statistics and analytics 