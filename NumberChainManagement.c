#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

float arr[100]; // Declare an array to store integers
int count = 0; // Number of elements in the array

void printArr();
void insertElement();
void arrInput(int k);

int main()
{
    while(1) // Keep the loop running infinitely
    {
        char option=0; // Initialize the option

        printf("\nNumber Chain management program\n");
        printf("Input 'p' to print all elements in the array.\n");
        printf("Input 'i' to Input value of 1 element at position k in the array.\n");
        printf("Input 'q' to exit the program.\n");

        scanf("%c", &option); // Read the user's choice
        getc(stdin); // Clear the newline character from the input buffer

        if ((option == 'i') || (option == 'p') || (option == 'q')) // check if user input invalid key 
        {

        }
        else
        {
            printf("Invalid key \n");
        }
        
        switch (option) // option table
        {
        case 'p':
            printArr(); // Call the function to print array elements
            break; 
        case 'i':
            insertElement(); // Call the function to insert an element
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



void printArr() // Print all elements in the array
{
    printf("Elements in the array \n"); // Print each element in the array
    for (int i = 0; i < 100; i++)
    {
        printf("arr[%d] = %.2f \n", i+1, arr[i]); //print each element in the array with 2 precision digits
    }   
}

void arrInput(int k) // Input an element at position k
{
    printf("Input 1 element at position %d in the array \n", k);
    scanf("%f", &arr[k]); // Read the user input for the element at position k
    getc(stdin); // Clear the newline character from the input buffer  
    count++; // count the number of elements in the array  
}

void insertElement() // Insert an element into the array
{
    int k = 0; // Declare an integer variable 'k' to store the input position
    printf("Input position k from 0 to 99 \n"); 
    scanf("%d", &k); // Read the value of 'k' from user input
    getc(stdin); // Clear any remaining newline characters from the input buffer

    if (arr[k] == '\0') // Check if the element at position 'k' is not null
    {
        arrInput(k); // Call a function 'arrInput' to insert an element at position 'k'
    }
    else
    {
        for (int i = 0; i < 100; i++) // Loop through the array
        {
            if (arr[i] == '\0') // check if that element not exists yet in the array
            {
                arrInput(i); // Call a function 'arrInput' to insert an element at position 'k'
            }  
        }               
    }    

    if (count == 100) // if insertion reach quality limit 100 elements
    {
        printf("Limit quanlity was reached \n");
    }
}