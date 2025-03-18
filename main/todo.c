#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_TASKS 100
#define MAX_LENGTH 100
#define FILENAME "tasks.txt"

char tasks[MAX_TASKS][MAX_LENGTH];
int task_count = 0;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Load tasks from file
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

// Save tasks to file
void saveTasks() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        setColor(12); // Red color
        printf("Error saving tasks!\n");
        setColor(7); // Reset to default
        return;
    }
    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%s\n", tasks[i]);
    }
    fclose(file);
}

// Add task
void addTask() {
    if (task_count >= MAX_TASKS) {
        setColor(12); // Red
        printf("Task list is full!\n");
        setColor(7); // Reset
        return;
    }
    setColor(14); // Yellow
    printf("Enter task: ");
    setColor(7);
    getchar(); // Clear buffer
    fgets(tasks[task_count], MAX_LENGTH, stdin);
    tasks[task_count][strcspn(tasks[task_count], "\n")] = 0;
    task_count++;
    saveTasks();
    setColor(10); // Green
    printf("Task added successfully!\n");
    setColor(7);
}

// View tasks
void viewTasks() {
    if (task_count == 0) {
        setColor(12);
        printf("No tasks available.\n");
        setColor(7);
        return;
    }
    setColor(11);
    printf("\n==== To-Do List ====\n");
    for (int i = 0; i < task_count; i++) {
        setColor(14); // Yellow
        printf("%d. ", i + 1);
        setColor(7);  // Reset
        printf("%s\n", tasks[i]);
    }
    setColor(11);
    printf("====================\n");
    setColor(7);
}

// Remove task
void removeTask() {
    if (task_count == 0) {
        setColor(12);
        printf("No tasks to remove.\n");
        setColor(7);
        return;
    }
    int index;
    setColor(14);
    printf("Enter task number to remove: ");
    setColor(7);
    scanf("%d", &index);
    if (index < 1 || index > task_count) {
        setColor(12);
        printf("Invalid task number!\n");
        setColor(7);
        return;
    }
    for (int i = index - 1; i < task_count - 1; i++) {
        strcpy(tasks[i], tasks[i + 1]);
    }
    task_count--;
    saveTasks();
    setColor(10);
    printf("Task removed successfully!\n");
    setColor(7);
}

// Main function
int main() {
    loadTasks();
    int choice;

    while (1) {
        setColor(11);
        printf("\n======= To-Do List Menu =======\n");
        setColor(14);
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Remove Task\n");
        printf("4. Exit\n");
        setColor(11);
        printf("===============================\n");
        setColor(7);
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
                setColor(10);
                printf("Exiting program...\n");
                setColor(7);
                return 0;
            default:
                setColor(12);
                printf("Invalid choice! Please enter 1-4.\n");
                setColor(7);
        }
    }
}
