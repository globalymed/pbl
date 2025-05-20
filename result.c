#include <stdio.h>
#include <string.h>
#include "quiz.h"

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
        printf("%-20s %-10d %-15d %-10.2f%%\n", results[i].name, results[i].score, results[i].totalQuestions, results[i].percentage);
    }
    printf("\nPress Enter to continue...");
    getchar(); getchar();
}

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
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = 0;
    printf("\nResults for '%s':\n", searchName);
    printf("%-10s %-15s %-10s\n", "Score", "Total Questions", "Percentage");
    printf("------------------------------------------\n");
    for (int i = 0; i < attemptCount; i++) {
        if (strcmp(attempts[i].participantName, searchName) == 0) {
            printf("%-10d %-15d %-10.2f%%\n", attempts[i].score, attempts[i].totalQuestions, attempts[i].percentage);
            found = 1;
        }
    }
    if (!found) {
        printf("No results found for '%s'.\n", searchName);
    }
    printf("\nPress Enter to continue...");
    getchar();
}

void saveResultsToFile() {
    FILE *rFile = fopen("results.txt", "w");
    if (rFile != NULL) {
        fprintf(rFile, "%d\n", participantCount);
        for (int i = 0; i < participantCount; i++) {
            fprintf(rFile, "%s\n%d\n%d\n%f\n", results[i].name, results[i].score, results[i].totalQuestions, results[i].percentage);
        }
        fprintf(rFile, "%d\n", attemptCount);
        for (int i = 0; i < attemptCount; i++) {
            fprintf(rFile, "%s\n%d\n%d\n%f\n", attempts[i].participantName, attempts[i].score, attempts[i].totalQuestions, attempts[i].percentage);
        }
        fclose(rFile);
    }
}

void loadResultsFromFile() {
    FILE *rFile = fopen("results.txt", "r");
    if (rFile != NULL) {
        fscanf(rFile, "%d\n", &participantCount);
        for (int i = 0; i < participantCount; i++) {
            fgets(results[i].name, MAX_NAME_LENGTH, rFile);
            results[i].name[strcspn(results[i].name, "\n")] = 0;
            fscanf(rFile, "%d\n", &results[i].score);
            fscanf(rFile, "%d\n", &results[i].totalQuestions);
            fscanf(rFile, "%f\n", &results[i].percentage);
        }
        fscanf(rFile, "%d\n", &attemptCount);
        for (int i = 0; i < attemptCount; i++) {
            fgets(attempts[i].participantName, MAX_NAME_LENGTH, rFile);
            attempts[i].participantName[strcspn(attempts[i].participantName, "\n")] = 0;
            fscanf(rFile, "%d\n", &attempts[i].score);
            fscanf(rFile, "%d\n", &attempts[i].totalQuestions);
            fscanf(rFile, "%f\n", &attempts[i].percentage);
        }
        fclose(rFile);
    }
} 