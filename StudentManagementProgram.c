#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

unsigned short count = 0; //count
unsigned short counts = 0; //count
void inputStudent();
void loadStudent();
void searchStudent();

// Define the student struct
typedef struct{
    unsigned short id;
    char full_name[25]; // Max length is 24 characters
    float average_mark;
} Student;

int main()
{
    remove("StudentManagement.bin"); //remove file avoid duplicate
    while(1) // Keep the loop running infinitely
    {
        char option=0; // Initialize the option
        printf("\nStudent management program\n");
        printf("Input 'a' to input a student from keyboard.\n");
        printf("Input 'd' to load all student file and display on screen.\n");
        printf("Input 's' to search for students ID.\n");
        printf("Input 'q' to exit the program.\n");

        scanf("%c", &option); // Read the user's choice
        getc(stdin); // Clear the newline character from the input buffer

        if ((option == 'a') || (option == 'd') || (option == 's') || (option == 'q')) // check if user input invalid key 
        {

        }
        else
        {
            printf("Invalid key \n");
        }
        
        switch (option) // option table
        {
        case 'a':
            inputStudent(); // Call the function to input student
            break; 
        case 'd':
            loadStudent(); // Call the function to load an student on screen
            break;
        case 's':
            searchStudent(); // Call the function to search an student id
            break;
        case 'q':
            printf("Program exit....\n");
            exit(0); // Exit the program
            break;                                                         
        default:
            break;
        }
    }
        
    return 0; 
}



void loadStudent() // load an student on screen
{
    Student sv;
    FILE *fp = fopen("studentManagement.bin", "ab+");   
    while (1)
    {
        fread(&sv, sizeof(sv), 1, fp); // read input of all field in sv struct
        
        if( feof(fp) ) //print until end of line
        { 
            break;
        }
        printf("%05hd_%s_%.1f\n", sv.id, sv.full_name, sv.average_mark);
    }
    printf("counts: %d\n", sv.id+1);
    fclose(fp);  
}

void inputStudent() // Input an element at position k
{
    Student sv;
    sv.id = 0;

    FILE *fp = fopen("studentManagement.bin", "ab+"); //open and append to file

    printf("Input student name: ");
    gets(sv.full_name);

    while (strlen(sv.full_name)>24) // name length > 24 reinput
    {
        printf("Invalid length\n");
        printf("Input student name: ");
        gets(sv.full_name);
    }

    printf("Input the user average mark: ");
    scanf("%f", &sv.average_mark);
    getc(stdin);

    while (sv.average_mark > 10) // mark length > 10 reinput
    {
        printf("Invalid value\n");
        printf("Input the user average mark: ");
        scanf("%f", &sv.average_mark);
        getc(stdin);
    }

    if (count < 60000)
    {
        sv.id = count;
        count++;
    }
    
    fwrite(&sv, sizeof(sv), 1, fp);
    fclose(fp);
}

void searchStudent() // search student name used id
{
    unsigned short id_input=0;
    Student sv;

    FILE *fp = fopen("studentManagement.bin", "rb"); // open and read  
    printf("Please input id ");
    scanf("%hd", &id_input);

    if (id_input == sv.id) // compare 2 number
    {
        while (1)
        {
            fread(&sv, sizeof(sv), 1, fp);  // read input of all field in sv struct
            if( feof(fp) ) //print until end of line in file
            { 
                break;
            }
            printf("%05d_%s_%.1f\n", sv.id, sv.full_name, sv.average_mark);
        }
    }
    else
    {
        printf("The student with ID %05hd does not exist.\n", id_input);
    }
    
    fclose(fp);
}