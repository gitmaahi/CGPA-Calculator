#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"info.h"

#define MAX_STUDENTS 10000

struct Student {
    int rollNumber;
    char name[50];
    float sgpa[8];
    float cgpa;
    int semNumber;  
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;


void insertStudent() {
    if (studentCount < MAX_STUDENTS) {
        struct Student newStudent;
        printf("Enter Roll Number: ");
        scanf("%d", &newStudent.rollNumber);
        printf("Enter Name: ");
        scanf("%s", newStudent.name);
        
        printf("Enter Number of Semesters Completed: ");
        scanf("%d", &newStudent.semNumber);

       
        for (int i = 0; i < 8; i++) {
            newStudent.sgpa[i] = 0;
        }

        printf("Enter SGPA for %d Semesters: ", newStudent.semNumber);
        for (int i = 0; i < newStudent.semNumber; i++) {
            scanf("%f", &newStudent.sgpa[i]);
        }

        newStudent.cgpa = 0.0;
        for (int i = 0; i < newStudent.semNumber; i++) {
            newStudent.cgpa += newStudent.sgpa[i];
        }
        newStudent.cgpa /= newStudent.semNumber;

        students[studentCount++] = newStudent;
        printf("Student entry added successfully!\n");
    } else {
        printf("Maximum number of students reached!\n");
    }
}

void deleteStudent(int rollNumber) {
    int foundIndex = -1;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }

        studentCount--;
        printf("Student with Roll Number %d deleted successfully!\n", rollNumber);
    } else {
        printf("Student not found!\n");
    }
}


int compareCGPA(const void *a, const void *b) {
    float cgpaA = ((struct Student*)a)->cgpa;
    float cgpaB = ((struct Student*)b)->cgpa;

    if (cgpaA > cgpaB) return -1;
    else if (cgpaA < cgpaB) return 1;
    else return 0;
}


void sortStudents() {
    qsort(students, studentCount, sizeof(struct Student), compareCGPA);
}


void displayTop5() {
    printf("\nTop 5 Students based on CGPA:\n");
    for (int i = 0; i < studentCount && i < 5; i++) {
        printf("Roll Number: %d, Name: %s, CGPA: %.2f\n", students[i].rollNumber, students[i].name, students[i].cgpa);
    }
}

int main() {
    int choice;
    int rollNumber;

    do {
        printf("\nMenu:\n");
        printf("1. Insert Student\n");
        printf("2. Delete Student\n");
        printf("3. Sort Students\n");
        printf("4. Display Top 5 Students\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertStudent();
                break;
            case 2:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &rollNumber);
                deleteStudent(rollNumber);
                break;
            case 3:
                sortStudents();
                printf("Students sorted successfully!\n");
                break;
            case 4:
                displayTop5();
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}
