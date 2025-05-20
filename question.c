#include <stdio.h>
#include <string.h>

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

// Extern global variables
extern Question questions[MAX_QUESTIONS];
extern Result results[MAX_PARTICIPANTS];
extern Attempt attempts[MAX_ATTEMPTS];
extern int questionCount;
extern int participantCount;
extern int attemptCount;

// Function prototypes
void clearScreen();
int validateInput(int min, int max);
void saveQuestionsToFile();
void loadQuestionsFromFile();

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
    getchar();
    fgets(questions[questionCount].question, MAX_QUESTION_LENGTH, stdin);
    questions[questionCount].question[strcspn(questions[questionCount].question, "\n")] = 0;
    for (int i = 0; i < 4; i++) {
        printf("Enter option %c: ", 'A' + i);
        fgets(questions[questionCount].options[i], MAX_OPTION_LENGTH, stdin);
        questions[questionCount].options[i][strcspn(questions[questionCount].options[i], "\n")] = 0;
    }
    printf("Enter correct option (1-4 for A-D): ");
    questions[questionCount].correctOption = validateInput(1, 4) - 1;
    questionCount++;
    printf("\nQuestion added successfully!\n");
    printf("Press Enter to continue...");
    getchar();
    saveQuestionsToFile();
}

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

void saveQuestionsToFile() {
    FILE *qFile = fopen("questions.txt", "w");
    if (qFile != NULL) {
        fprintf(qFile, "%d\n", questionCount);
        for (int i = 0; i < questionCount; i++) {
            fprintf(qFile, "%s\n", questions[i].question);
            for (int j = 0; j < 4; j++) {
                fprintf(qFile, "%s\n", questions[i].options[j]);
            }
            fprintf(qFile, "%d\n", questions[i].correctOption);
        }
        fclose(qFile);
    }
}

void loadQuestionsFromFile() {
    FILE *qFile = fopen("questions.txt", "r");
    if (qFile != NULL) {
        fscanf(qFile, "%d\n", &questionCount);
        for (int i = 0; i < questionCount; i++) {
            fgets(questions[i].question, MAX_QUESTION_LENGTH, qFile);
            questions[i].question[strcspn(questions[i].question, "\n")] = 0;
            for (int j = 0; j < 4; j++) {
                fgets(questions[i].options[j], MAX_OPTION_LENGTH, qFile);
                questions[i].options[j][strcspn(questions[i].options[j], "\n")] = 0;
            }
            fscanf(qFile, "%d\n", &questions[i].correctOption);
        }
        fclose(qFile);
    }
} 