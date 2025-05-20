#ifndef QUIZ_H
#define QUIZ_H

#define MAX_QUESTIONS 100
#define MAX_PARTICIPANTS 50
#define MAX_NAME_LENGTH 50
#define MAX_QUESTION_LENGTH 200
#define MAX_OPTION_LENGTH 100
#define MAX_ATTEMPTS 100

// Structure for a quiz question
typedef struct {
    char question[MAX_QUESTION_LENGTH];
    char options[4][MAX_OPTION_LENGTH];
    int correctOption; // 0-3 (A-D)
} Question;

// Structure for participant's quiz result
typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
    int totalQuestions;
    float percentage;
} Result;

// Structure for quiz attempt history
typedef struct {
    char participantName[MAX_NAME_LENGTH];
    int score;
    int totalQuestions;
    float percentage;
    char date[20]; // Date of attempt (not implemented in this version)
} Attempt;

// Function prototypes
void addQuestion();
void viewQuestions();
void saveQuestionsToFile();
void loadQuestionsFromFile();

void takeQuiz();

void viewResults();
void viewResultsByName();
void saveResultsToFile();
void loadResultsFromFile();

void clearScreen();
int validateInput(int min, int max);

extern Question questions[MAX_QUESTIONS];
extern Result results[MAX_PARTICIPANTS];
extern Attempt attempts[MAX_ATTEMPTS];
extern int questionCount;
extern int participantCount;
extern int attemptCount;

#endif // QUIZ_H 