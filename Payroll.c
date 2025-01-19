#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for Employee
struct Employee {
    int id;
    char name[50];
    float basic_salary;
    float overtime; // Hours of overtime
    int leaves;     // Number of leaves
    float deductions; // Deductions (e.g., taxes, unpaid leave)
};

// File Path
const char *file_path = "employees.dat";

// Function Declarations
void mainMenu();
void addEmployee();
void displayEmployees();
void processPayroll();
void generateReport();
int employeeExists(int id);

// Utility Functions
void pauseScreen();
void clearScreen();

// Main Function
int main() {
    mainMenu();
    return 0;
}

// Main Menu Function
void mainMenu() {
    int choice;
    do {
        clearScreen();
        printf("=== Payroll System ===\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Process Payroll\n");
        printf("4. Generate Report\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: processPayroll(); break;
            case 4: generateReport(); break;
            case 5: printf("Exiting the system...\n"); break;
            default: printf("Invalid choice. Please try again.\n"); pauseScreen();
        }
    } while (choice != 5);
}

// Function to Add Employee
void addEmployee() {
    struct Employee emp;
    FILE *file = fopen(file_path, "ab");
    if (!file) {
        perror("Error opening file");
        return;
    }

    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);

    // Check if employee already exists
    if (employeeExists(emp.id)) {
        printf("Employee with ID %d already exists.\n", emp.id);
        pauseScreen();
        fclose(file);
        return;
    }

    printf("Enter Employee Name: ");
    scanf(" %[^\n]", emp.name);
    printf("Enter Basic Salary: ");
    scanf("%f", &emp.basic_salary);
    printf("Enter Overtime Hours: ");
    scanf("%f", &emp.overtime);
    printf("Enter Number of Leaves: ");
    scanf("%d", &emp.leaves);

    // Default deductions (can be updated in processPayroll)
    emp.deductions = 0.0;

    fwrite(&emp, sizeof(emp), 1, file);
    printf("Employee added successfully!\n");
    fclose(file);
    pauseScreen();
}

// Function to Display Employees
void displayEmployees() {
    struct Employee emp;
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    printf("\n=== Employee List ===\n");
    printf("ID\tName\t\tBasic Salary\tOvertime\tLeaves\n");
    printf("----------------------------------------------------\n");

    while (fread(&emp, sizeof(emp), 1, file)) {
        printf("%d\t%-15s%.2f\t\t%.2f\t\t%d\n", emp.id, emp.name, emp.basic_salary, emp.overtime, emp.leaves);
    }

    fclose(file);
    pauseScreen();
}

// Function to Process Payroll
void processPayroll() {
    struct Employee emp;
    FILE *file = fopen(file_path, "rb+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    printf("\n=== Process Payroll ===\n");

    while (fread(&emp, sizeof(emp), 1, file)) {
        // Calculate deductions for leaves (unpaid leave penalty)
        emp.deductions = emp.leaves * (emp.basic_salary / 30);

        // Calculate net salary
        float gross_salary = emp.basic_salary + (emp.overtime * 50); // Assuming $50/hour for overtime
        float net_salary = gross_salary - emp.deductions;

        // Update the file with deductions
        fseek(file, -sizeof(emp), SEEK_CUR);
        fwrite(&emp, sizeof(emp), 1, file);

        // Display salary details
        printf("\nID: %d | Name: %s\n", emp.id, emp.name);
        printf("Gross Salary: %.2f | Deductions: %.2f | Net Salary: %.2f\n", gross_salary, emp.deductions, net_salary);
    }

    fclose(file);
    pauseScreen();
}

// Function to Generate Report
void generateReport() {
    struct Employee emp;
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    printf("\n=== Payroll Report ===\n");
    printf("ID\tName\t\tNet Salary\n");
    printf("------------------------------------\n");

    while (fread(&emp, sizeof(emp), 1, file)) {
        // Calculate net salary
        float gross_salary = emp.basic_salary + (emp.overtime * 50); // Assuming $50/hour for overtime
        float net_salary = gross_salary - emp.deductions;

        printf("%d\t%-15s%.2f\n", emp.id, emp.name, net_salary);
    }

    fclose(file);
    pauseScreen();
}

// Utility: Check if Employee Exists
int employeeExists(int id) {
    struct Employee emp;
    FILE *file = fopen(file_path, "rb");
    if (!file) return 0;

    while (fread(&emp, sizeof(emp), 1, file)) {
        if (emp.id == id) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Utility: Pause Screen
void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// Utility: Clear Screen
void clearScreen() {
    system("clear || cls");
}
