#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LENGTH 100
#define FILENAME "tasks.txt"

char tasks[MAX_TASKS][MAX_LENGTH];
int task_count = 0;

// Function to load tasks from file
void loadTasks() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        return;
    }
    while (fgets(tasks[task_count], MAX_LENGTH, file)) {
        tasks[task_count][strcspn(tasks[task_count], "\n")] = 0; // Remove newline
        task_count++;
    }
    fclose(file);
}

// Function to save tasks to file
void saveTasks() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error saving tasks!\n");
        return;
    }
    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%s\n", tasks[i]);
    }
    fclose(file);
}

// Function to add a task
void addTask() {
    if (task_count >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }
    printf("Enter task: ");
    getchar(); // Consume newline left in buffer
    fgets(tasks[task_count], MAX_LENGTH, stdin);
    tasks[task_count][strcspn(tasks[task_count], "\n")] = 0; // Remove newline
    task_count++;
    saveTasks();
    printf("Task added successfully!\n");
}

// Function to view tasks
void viewTasks() {
    if (task_count == 0) {
        printf("No tasks available.\n");
        return;
    }
    printf("\n---- To-Do List ----\n");
    for (int i = 0; i < task_count; i++) {
        printf("%d. %s\n", i + 1, tasks[i]);
    }
    printf("--------------------\n");
}

// Function to remove a task
void removeTask() {
    if (task_count == 0) {
        printf("No tasks to remove.\n");
        return;
    }
    int index;
    printf("Enter task number to remove: ");
    scanf("%d", &index);
    if (index < 1 || index > task_count) {
        printf("Invalid task number!\n");
        return;
    }
    for (int i = index - 1; i < task_count - 1; i++) {
        strcpy(tasks[i], tasks[i + 1]);
    }
    task_count--;
    saveTasks();
    printf("Task removed successfully!\n");
}

// Main function
int main() {
    loadTasks();
    int choice;
    while (1) {
        printf("\nTo-Do List Menu:\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Remove Task\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                removeTask();
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please enter 1-4.\n");
        }
    }
}
