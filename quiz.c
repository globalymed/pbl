#include <stdio.h>
#include <string.h>
#include "quiz.h"

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
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;
    printf("\nStarting quiz for %s...\n", name);
    printf("There are %d questions. Good luck!\n\n", questionCount);
    for (int i = 0; i < questionCount; i++) {
        printf("Question %d: %s\n", i + 1, questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'A' + j, questions[i].options[j]);
        }
        printf("Your answer (1-4 for A-D): ");
        answer = validateInput(1, 4) - 1;
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
    participantCount++;
    attemptCount++;
    saveResultsToFile();
    printf("\nPress Enter to continue...");
    getchar();
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int validateInput(int min, int max) {
    int input;
    char buffer[100];
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &input) != 1) {
            printf("Invalid input. Please enter a number between %d and %d: ", min, max);
            continue;
        }
        if (input < min || input > max) {
            printf("Input out of range. Please enter a number between %d and %d: ", min, max);
            continue;
        }
        return input;
    }
} 