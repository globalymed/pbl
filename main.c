#include <stdio.h>

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

// Global variables
Question questions[MAX_QUESTIONS];
Result results[MAX_PARTICIPANTS];
Attempt attempts[MAX_ATTEMPTS];
int questionCount = 0;
int participantCount = 0;
int attemptCount = 0;

// Function prototypes
void clearScreen();
int validateInput(int min, int max);
void addQuestion();
void viewQuestions();
void takeQuiz();
void viewResults();
void viewResultsByName();
void saveQuestionsToFile();
void loadQuestionsFromFile();
void saveResultsToFile();
void loadResultsFromFile();

void displayMenu() {
    printf("\n====== QUIZ MANAGEMENT SYSTEM ======\n");
    printf("1. Add Question\n");
    printf("2. View Questions\n");
    printf("3. Take Quiz\n");
    printf("4. View All Results\n");
    printf("5. Search Results by Name\n");
    printf("6. Save Data\n");
    printf("0. Exit\n");
    printf("====================================\n");
}

int main() {
    int choice;
    loadQuestionsFromFile();
    loadResultsFromFile();
    while (1) {
        clearScreen();
        displayMenu();
        printf("Enter your choice: ");
        choice = validateInput(0, 6);
        switch (choice) {
            case 1:
                addQuestion();
                break;
            case 2:
                viewQuestions();
                break;
            case 3:
                takeQuiz();
                break;
            case 4:
                viewResults();
                break;
            case 5:
                viewResultsByName();
                break;
            case 6:
                saveQuestionsToFile();
                saveResultsToFile();
                printf("Data saved successfully!\n");
                printf("Press Enter to continue...");
                getchar(); getchar();
                break;
            case 0:
                saveQuestionsToFile();
                saveResultsToFile();
                printf("Thank you for using Quiz Management System!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
