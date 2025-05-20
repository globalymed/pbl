#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// Global variables
Question questions[MAX_QUESTIONS];
Result results[MAX_PARTICIPANTS];
Attempt attempts[MAX_ATTEMPTS];
int questionCount = 0;
int participantCount = 0;
int attemptCount = 0;

// Function prototypes
void displayMenu();
void addQuestion();
void viewQuestions();
void takeQuiz();
void viewResults();
void viewResultsByName();
void saveData();
void loadData();
void clearScreen();
int validateInput(int min, int max);

int main() {
    int choice;
    
    // Load saved data when program starts
    loadData();
    
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
                saveData();
                printf("Data saved successfully!\n");
                printf("Press Enter to continue...");
                getchar(); getchar();
                break;
            case 0:
                saveData();
                printf("Thank you for using Quiz Management System!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

// Function to display the main menu
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

// Function to add a new question
void addQuestion() {
    clearScreen();
    printf("\n===== ADD NEW QUESTION =====\n");
    
    if (questionCount >= MAX_QUESTIONS) {
        printf("Question bank is full! Cannot add more questions.\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
        return;
    }
    
    printf("Enter question: ");
    getchar(); // Clear input buffer
    fgets(questions[questionCount].question, MAX_QUESTION_LENGTH, stdin);
    questions[questionCount].question[strcspn(questions[questionCount].question, "\n")] = 0; // Remove newline
    
    for (int i = 0; i < 4; i++) {
        printf("Enter option %c: ", 'A' + i);
        fgets(questions[questionCount].options[i], MAX_OPTION_LENGTH, stdin);
        questions[questionCount].options[i][strcspn(questions[questionCount].options[i], "\n")] = 0; // Remove newline
    }
    
    printf("Enter correct option (1-4 for A-D): ");
    questions[questionCount].correctOption = validateInput(1, 4) - 1; // Convert 1-4 to 0-3
    
    questionCount++;
    printf("\nQuestion added successfully!\n");
    printf("Press Enter to continue...");
    getchar();
}

// Function to view all questions
void viewQuestions() {
    clearScreen();
    printf("\n===== VIEW ALL QUESTIONS =====\n");
    
    if (questionCount == 0) {
        printf("No questions available.\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
        return;
    }
    
    for (int i = 0; i < questionCount; i++) {
        printf("\nQuestion %d: %s\n", i + 1, questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'A' + j, questions[i].options[j]);
        }
        printf("Correct Answer: %c\n", 'A' + questions[i].correctOption);
        printf("----------------------------\n");
    }
    
    printf("\nPress Enter to continue...");
    getchar(); getchar();
}

// Function to take a quiz
void takeQuiz() {
    clearScreen();
    printf("\n===== TAKE QUIZ =====\n");
    
    if (questionCount == 0) {
        printf("No questions available. Cannot start quiz.\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
        return;
    }
    
    char name[MAX_NAME_LENGTH];
    int score = 0;
    int answer;
    
    printf("Enter your name: ");
    getchar(); // Clear input buffer
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline
    
    printf("\nStarting quiz for %s...\n", name);
    printf("There are %d questions. Good luck!\n\n", questionCount);
    
    for (int i = 0; i < questionCount; i++) {
        printf("Question %d: %s\n", i + 1, questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'A' + j, questions[i].options[j]);
        }
        
        printf("Your answer (1-4 for A-D): ");
        answer = validateInput(1, 4) - 1; // Convert 1-4 to 0-3
        
        if (answer == questions[i].correctOption) {
            printf("Correct!\n\n");
            score++;
        } else {
            printf("Incorrect. The correct answer is %c.\n\n", 'A' + questions[i].correctOption);
        }
    }
    
    float percentage = (float)score / questionCount * 100;
    
    printf("\n===== QUIZ COMPLETED =====\n");
    printf("Name: %s\n", name);
    printf("Score: %d / %d\n", score, questionCount);
    printf("Percentage: %.2f%%\n", percentage);
    
    // Save result
    strcpy(results[participantCount].name, name);
    results[participantCount].score = score;
    results[participantCount].totalQuestions = questionCount;
    results[participantCount].percentage = percentage;
    
    // Also save to attempt history
    strcpy(attempts[attemptCount].participantName, name);
    attempts[attemptCount].score = score;
    attempts[attemptCount].totalQuestions = questionCount;
    attempts[attemptCount].percentage = percentage;
    // In a more advanced version, we could add date/time here
    
    participantCount++;
    attemptCount++;
    
    printf("\nPress Enter to continue...");
    getchar();
}

// Function to view all results
void viewResults() {
    clearScreen();
    printf("\n===== VIEW ALL RESULTS =====\n");
    
    if (participantCount == 0) {
        printf("No quiz results available.\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
        return;
    }
    
    printf("%-20s %-10s %-15s %-10s\n", "Name", "Score", "Total Questions", "Percentage");
    printf("--------------------------------------------------------------\n");
    
    for (int i = 0; i < participantCount; i++) {
        printf("%-20s %-10d %-15d %-10.2f%%\n", 
               results[i].name, 
               results[i].score, 
               results[i].totalQuestions, 
               results[i].percentage);
    }
    
    printf("\nPress Enter to continue...");
    getchar(); getchar();
}

// Function to view results by name
void viewResultsByName() {
    clearScreen();
    printf("\n===== SEARCH RESULTS BY NAME =====\n");
    
    if (attemptCount == 0) {
        printf("No quiz attempts available.\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
        return;
    }
    
    char searchName[MAX_NAME_LENGTH];
    int found = 0;
    
    printf("Enter name to search: ");
    getchar(); // Clear input buffer
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = 0; // Remove newline
    
    printf("\nResults for '%s':\n", searchName);
    printf("%-10s %-15s %-10s\n", "Score", "Total Questions", "Percentage");
    printf("------------------------------------------\n");
    
    for (int i = 0; i < attemptCount; i++) {
        if (strcmp(attempts[i].participantName, searchName) == 0) {
            printf("%-10d %-15d %-10.2f%%\n", 
                   attempts[i].score, 
                   attempts[i].totalQuestions, 
                   attempts[i].percentage);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No results found for '%s'.\n", searchName);
    }
    
    printf("\nPress Enter to continue...");
    getchar();
}

// Function to save data to files
void saveData() {
    // Save questions
    FILE *qFile = fopen("questions.dat", "wb");
    if (qFile != NULL) {
        fwrite(&questionCount, sizeof(int), 1, qFile);
        fwrite(questions, sizeof(Question), questionCount, qFile);
        fclose(qFile);
    }
    
    // Save results
    FILE *rFile = fopen("results.dat", "wb");
    if (rFile != NULL) {
        fwrite(&participantCount, sizeof(int), 1, rFile);
        fwrite(results, sizeof(Result), participantCount, rFile);
        fclose(rFile);
    }
    
    // Save attempts
    FILE *aFile = fopen("attempts.dat", "wb");
    if (aFile != NULL) {
        fwrite(&attemptCount, sizeof(int), 1, aFile);
        fwrite(attempts, sizeof(Attempt), attemptCount, aFile);
        fclose(aFile);
    }
}

// Function to load data from files
void loadData() {
    // Load questions
    FILE *qFile = fopen("questions.dat", "rb");
    if (qFile != NULL) {
        fread(&questionCount, sizeof(int), 1, qFile);
        fread(questions, sizeof(Question), questionCount, qFile);
        fclose(qFile);
    }
    
    // Load results
    FILE *rFile = fopen("results.dat", "rb");
    if (rFile != NULL) {
        fread(&participantCount, sizeof(int), 1, rFile);
        fread(results, sizeof(Result), participantCount, rFile);
        fclose(rFile);
    }
    
    // Load attempts
    FILE *aFile = fopen("attempts.dat", "rb");
    if (aFile != NULL) {
        fread(&attemptCount, sizeof(int), 1, aFile);
        fread(attempts, sizeof(Attempt), attemptCount, aFile);
        fclose(aFile);
    }
}

// Function to clear the screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to validate numerical input within a range
int validateInput(int min, int max) {
    int input;
    char buffer[100];
    
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        
        // Check if input is a number
        if (sscanf(buffer, "%d", &input) != 1) {
            printf("Invalid input. Please enter a number between %d and %d: ", min, max);
            continue;
        }
        
        // Check if input is within range
        if (input < min || input > max) {
            printf("Input out of range. Please enter a number between %d and %d: ", min, max);
            continue;
        }
        
        return input;
    }
}
