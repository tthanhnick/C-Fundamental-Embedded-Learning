#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_EMPLOYEES 1000
#define MAX_EMPLOYEES_TIME 1000

char g_adminPassword[9] = "12345678"; // admin password
bool status = false;

struct Employee // Struct to hold employee salary information
{
    unsigned short id;
    char fullName[25];
    unsigned int basicSalary; 
};

// Define a struct to hold employee working time information
struct EmployeeTime 
{
    unsigned short id;
    char fullName[25];
    float timeRecord; // the working time recorded
    unsigned short timeStatus; // the working time status (in/out) 
};

// Function Declaration
void MainMenu();
void AdminModeMenu();
void ChangeAdminPassword();
void LoadEmployees(struct Employee employees[], unsigned short* numEmployees);
void AddEmployee(struct Employee employees[], unsigned short* numEmployees); 
void ViewEmployeeInfo(const struct Employee employees[], unsigned short numEmployees);
void LoadEmployeesTime(struct EmployeeTime employeesTime[], unsigned short* numEmployeesTime); 
void ViewWorkingTime(const struct EmployeeTime employeesTime[], unsigned short numEmployeesTime); 
void CalculateSalaries(const struct EmployeeTime employeesTime[], unsigned short numEmployeesTime, struct Employee employees[], unsigned short numEmployees); 
void NormalModeMenu();
void recordTime(struct Employee employees[], unsigned short numEmployees, unsigned short mode); 


int main()
{
    MainMenu();
    return 0;
}

void MainMenu() // Function to display the menu and get user's choice
{
    unsigned short option = 0;

    while (1)
    {
        printf("\nTime Keeping System\n");
        printf("Input 1 to choose 'Admin Mode'\n");
        printf("Input 2 to choose 'Normal Mode'\n");
        printf("Input 3 to Exit \n");
        printf("Enter your option: ");

        scanf("%hd",&option);
        getc(stdin);

        switch (option)
        {
            case 1: //Admin Mode
                printf("Admin Mode\n");
                AdminModeMenu();
                break;
            case 2: //Normal Mode
                printf("Normal Mode\n");
                NormalModeMenu();
                break;
            case 3: //Exit
                printf("\nExit the program\n");
                exit(0);
                break;
            default: //default
                printf("Invalid option. Please try again.\n");
                MainMenu();
                break;
        }
    }
}

void AdminModeMenu()
{
    struct Employee employees[MAX_EMPLOYEES];
    struct EmployeeTime employeesTime[MAX_EMPLOYEES_TIME];

    unsigned short numEmployees = 0;
    unsigned short numEmployeesTime = 0;
    unsigned short option = 0;

    LoadEmployees(employees, &numEmployees);
    LoadEmployeesTime(employeesTime, &numEmployeesTime);

    while (1)
    {
        printf("\nAdmin Mode Menu:\n");
        printf("1. Change Admin Password\n");
        printf("2. Add Employee\n");
        printf("3. View Employee Information\n");
        printf("4. View Working Time for a Specific Employee\n");
        printf("5. Calculate Salaries\n");
        printf("6. Exit Admin Mode\n");
        printf("7. Return to Main Menu\n");
        printf("Enter your option: ");

        scanf("%hd", &option);
        getc(stdin);

        switch (option) 
        {
            case 1: // Change Admin Password
                ChangeAdminPassword();
                break;
            case 2: // Add Employee
                AddEmployee(employees, &numEmployees);
                //SaveEmployees(employees, numEmployees);
                break;
            case 3: //View All Employee Information
                ViewEmployeeInfo(employees, numEmployees);
                break;
            case 4: // View Working Time for specific Employee
                ViewWorkingTime(employeesTime, numEmployeesTime); 
                break;
            case 5: // Calculate salaries for all emplyees
                CalculateSalaries(employeesTime, numEmployeesTime, employees, numEmployees); 
                break;
            case 6: //Exit 
                printf("Exiting Admin Mode.\n");
                exit(0);
                break;
            case 7: // Return to main menu
                MainMenu();
                break;
            default: //default
                printf("Invalid option. Please try again.\n");
                AdminModeMenu();
                break;
        }
    }
}

void ChangeAdminPassword() 
{
    char temp = 0; // temp character

    // Prompt for a new password
    printf("Enter your new password (8 characters numbers without space): ");
    gets(g_adminPassword);

    // Encrypt the password (reverse characters)
    for (int i = 0; i < (int) (strlen(g_adminPassword))/2; i++) // divide the string by half between left and right
    {
        temp = g_adminPassword[i]; // temp character = left character
        g_adminPassword[i] = g_adminPassword[strlen(g_adminPassword)-i -1]; // left character = right character
        g_adminPassword[strlen(g_adminPassword)-i -1] = temp; // right character = temp character
    }

    // Encrypt the password (add character with 24)
    for (int i = 0; i < (int) (strlen(g_adminPassword)); i++) 
    {
        g_adminPassword[i] += 24; // add 24 to the character
    }

    // Save the encrypted password to a file (e.g., "admin_password.txt")
    FILE *fp = fopen("AdminPassword.txt", "w");

    if (fp == NULL) // check if the password file open succeeded
    {
        printf("File creation failed");
        return; 
    }

    fprintf(fp, "%s", g_adminPassword);
    fclose(fp); 
}

// Function to load employee data from a file (you'll need to implement this)
void LoadEmployees(struct Employee employees[], unsigned short* numEmployees)
{
    char lineString[50]="";
    char stringCounters[50]="";

    struct Employee emp;

    // Read employee data from a file 
    FILE *file = fopen("employees.txt", "a+");

    if (file == NULL) //check if the file exists
    {
        printf("Error opening employees file.\n");
        return; 
    }

    //Count the number of characters in one line
    fscanf(file, "%[^\n]\n", stringCounters);
    unsigned short lineLength = (unsigned short) strlen(stringCounters);
    fclose(file);
    
    FILE *fp = fopen("employees.txt", "a+");

    if (fp == NULL) //check if the file exists
    {
        printf("Error opening employees file.\n");
        return; 
    }

    // Read the data of first line
    fscanf(fp, "%hd %d %24[^\n]s\n", &emp.id, &emp.basicSalary, emp.fullName);
   
   // Read the data of until end of line
    while (1)
    {
        if (feof(fp)) // break out of loop if end of file
        {
            break;
        }

        if(fgets (lineString, lineLength, fp)!=NULL) // Read the data of a line from line 2
        {
            employees[*numEmployees] = emp; // Populate the employees array
            (*numEmployees) ++; // Update numEmployees
            fscanf(fp,"%hd %d %24[^\n]s\n", &emp.id, &emp.basicSalary, emp.fullName);
        }


    }
    fclose(fp);    
}

// Function to add a new employee
void AddEmployee(struct Employee employees[], unsigned short* numEmployees) 
{
    if (*numEmployees >= MAX_EMPLOYEES) // Check if number of employees exceeds maximum
    {
        printf("Maximum number of employees reached.\n");
        return; 
    }

    struct Employee newEmployee;
    
    printf("Enter full name (up to 24 characters): ");
    gets(newEmployee.fullName);

    while (strlen(newEmployee.fullName)>24) // name length > 24 reinput
    {
        printf("Invalid length\n");
        printf("Enter full name (up to 24 characters): ");
        gets(newEmployee.fullName);
    }
    // Generate an auto-incremented Employee ID
    newEmployee.id = *numEmployees + 1;

    printf("Enter basic salary (VND per hour): ");
    scanf("%d", &newEmployee.basicSalary);
    getc(stdin);

    // Save the new employee data
    employees[*numEmployees] = newEmployee;
    (*numEmployees)++;
    
    FILE* fp = fopen("employees.txt", "a");

    if (fp == NULL) //check if the file open succeeded
    {
        printf("Error opening employees file for writing.\n");
        return; 
    }

    // Save the updated data to a file 
    fprintf(fp,"%hd %d %s\n", newEmployee.id, newEmployee.basicSalary, newEmployee.fullName);
    fclose(fp);
}

// Function to view employee information
void ViewEmployeeInfo(const struct Employee employees[], unsigned short numEmployees) 
{
    // Display Employee ID, full name, and basic salary for all employees
    for (int i = 0; i < numEmployees; i++) 
    {
        printf("ID: %hd, Full name: %s, Basic salary: %d\n", employees[i].id, employees[i].fullName, employees[i].basicSalary);
    }
}

void LoadEmployeesTime(struct EmployeeTime employeesTime[], unsigned short* numEmployeesTime) 
{
    char lineString[50]="";
    char stringCounters[50]="";

    struct EmployeeTime empT;

    // Read employee data from a file 
    FILE *file = fopen("employeesTime.txt", "a+");

    if (file == NULL) // check if file opened successfully
    {
        printf("Error opening employees file.\n");
        return; 
    }

    //Count the number of characters in one line
    fscanf(file, "%[^\n]\n", stringCounters);
    unsigned short lineLength = (unsigned short) strlen(stringCounters);
    fclose(file);

    FILE *fp = fopen("employeesTime.txt", "a+");

    if (fp == NULL) // check if file opened successfully
    {
        printf("Error opening employees file.\n");
        return; 
    }

    // Read data of first line
    fscanf(fp, "%hd %f %hd %24[^\n]s\n", &empT.id, &empT.timeRecord, &empT.timeStatus, empT.fullName);

    // Read data until end of line
    while (1)
    {
        if (feof(fp)) // break out of loop if end of file
        {
            break;
        }

        if(fgets (lineString,lineLength, fp)!=NULL) // Read data of a line from line 2
        {
            employeesTime[*numEmployeesTime] = empT; // Populate the employees array
            (*numEmployeesTime) ++; // Update numEmployees
            fscanf(fp, "%hd %f %hd %24[^\n]s\n", &empT.id, &empT.timeRecord, &empT.timeStatus, empT.fullName);
        }
    }
    fclose(fp); 
}


// Function to retrieve check-in and check-out times for an employee
void ViewWorkingTime(const struct EmployeeTime employeesTime[], unsigned short numEmployeesTime) 
{
    unsigned short days=0;
    unsigned short employeeId=0;

    printf("Enter Employee ID: ");
    scanf("%hd", &employeeId);
    getc(stdin);

    // Search for the specified employeeId
    for (int i = 0; i < numEmployeesTime; i++) 
    {
        if (employeesTime[i].id == employeeId) 
        {
            // Days of check-in and check-out times for this employee
            if (employeesTime[i].timeStatus == 0)
            {
                printf("Day: %hd\n",++days);
            }
            // Display the results
            printf("ID: %hd, Full Name: %s, ", employeesTime[i].id,employeesTime[i].fullName);
            printf("Time: %.2f, Time Status: %s\n", employeesTime[i].timeRecord, employeesTime[i].timeStatus == 0 ? "check-in" : "check-out");
            status = true;
        }
    }

    if (status == false) // If employee Id not found
    {
       printf("Employee with ID %d not found.\n", employeeId);
    }
    status = false; 
}

// Function to calculate salaries
void CalculateSalaries(const struct EmployeeTime employeesTime[], unsigned short numEmployeesTime, struct Employee employees[], unsigned short numEmployees) 
{
    float actualWorkingTime = 0.00;
    unsigned int salary = 0;

    // Match the employee Id between Admin Mode and Normal Mode
    for (int i = 0; i < numEmployees; i++)
    {
        for (int j = 0; j < numEmployeesTime; j++)
        {
            if (employees[i].id == employeesTime[j].id)
            {
                // Sum of actual working time
                if (employeesTime[j].timeStatus == 1) //check out
                {
                    actualWorkingTime = actualWorkingTime + employeesTime[j].timeRecord; // Sum of checkout time
                }
                else if (employeesTime[j].timeStatus == 0) //check in
                {
                    actualWorkingTime = actualWorkingTime - (employeesTime[j].timeRecord + 1); // Calculate actual working time (1 hrs lunch deduction)
                }
                
                salary = employees[i].basicSalary * actualWorkingTime; // Apply the salary formula to compute the salary

                // Deduct penalties for late check-in or early check-out
                if (employeesTime[j].timeStatus == 0) //check in
                {
                    if (employeesTime[j].timeRecord > 8.5) // Check in later than 8:30
                    {
                        salary = salary - 20000;
                    }
                }
                else if (employeesTime[j].timeStatus == 0) //check out
                {
                    if (employeesTime[j].timeStatus < 16.5) // Check out sooner than 17:00
                    {
                        salary = salary - 20000;
                    }
                }
                
            }
        }
        printf("ID: %hd, Full name: %s, Salary: %d VND\n", employees[i].id, employees[i].fullName, salary);
        actualWorkingTime = 0; //reset actualWorkingTime for next iteration
        salary = 0; //reset salary for next iteration
    }
}

void NormalModeMenu() 
{
    // Create an array of struct Employee
    struct Employee employees[MAX_EMPLOYEES];
    struct EmployeeTime employeesTime[MAX_EMPLOYEES_TIME];

    unsigned short option=0;
    unsigned short numEmployees = 0;
    unsigned short numEmployeesTime = 0;
    
    // Load employee data from a file (e.g., "employees.txt")
    LoadEmployeesTime(employeesTime, &numEmployeesTime);
    LoadEmployees(employees, &numEmployees);
    
    while (1) 
    {
        printf("\nNormal Mode Menu:\n");
        printf("1. Check-in\n");
        printf("2. Check-out\n");
        printf("3. Exit Normal mode\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your option: ");

        scanf("%hd", &option);
        getc(stdin);

        switch (option) 
        {
            case 1: // Check-in
                recordTime(employees, numEmployees, 0); 
                break;
            case 2: // Check-out
                recordTime(employees, numEmployees, 1);
                break;
            case 3:
                printf("Exiting Normal mode.\n");
                exit(0);
            case 4:
                MainMenu();
            default:
                printf("Invalid option. Please try again.\n");
                NormalModeMenu();
        }
    }
}

// Function to record check-in or check-out time
void recordTime(struct Employee employees[], unsigned short numEmployees, unsigned short mode) 
{
    unsigned short employeeId=0;
    char confirmation=0;

    printf("Enter your Employee ID: ");
    scanf("%hd", &employeeId);
    getc(stdin);

    // Search for the specified employeeId
    for (int i = 0; i < numEmployees; i++) 
    {
        if (employees[i].id == employeeId) 
        {
            // Display the full name and ask for confirmation of ID and name
            printf("Employee ID: %hd, Emoloyee Full name %s\n", employees[i].id, employees[i].fullName);
            printf("Confirm your information is correct (Y/N): ");

            scanf("%c", &confirmation); 
            getc(stdin);

            if ((confirmation == 'Y') || (confirmation == 'y'))
            {
                // Confirmation of procedure
                printf("Confirm to proceed the %s (Y/N): ", mode == 0 ? "check-in" : "check-out");
                scanf("%c", &confirmation); // Note the space before %c to consume newline
                getc(stdin);

                if ((confirmation == 'Y') || (confirmation == 'y')) 
                {
                    // Record the current time as check-in or check-out time
                    time_t s;
                    struct tm* current_time;
                
                    // time in seconds
                    s = time(NULL);
                
                    // to get current time
                    current_time = localtime(&s);
                    float timeCheck = (float) current_time->tm_hour + ((float)current_time->tm_min)/60 + ((float)current_time->tm_sec)/3600;

                    // Save the data to a file (e.g., "checkin_data.txt")
                    FILE* fp = fopen("employeesTime.txt", "a");

                    if (fp == NULL) // check if file opened successfully
                    {
                        printf("Error opening employees file.\n");
                        return;
                    }

                    fprintf(fp, "%hd %.2f %hd %s\n", employees[i].id, timeCheck, mode, employees[i].fullName);
                    fclose(fp);

                    printf("%s time is recorded successfully.\n", mode == 0 ? "Check-in" : "Check-out");
                } 
                else 
                {
                    printf("Process Aborted.\n");
                }                
            }
            else
            {
                printf("Process Aborted.\n");
            }

            return; //Exit the loop if employee ID found
        }
    }

    // If employee Id not found
    printf("Employee with ID %d not found.\n", employeeId);
}
