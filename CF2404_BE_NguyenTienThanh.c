#include <stdio.h>
#include <stdlib.h>

int arr[100]; // Declare an array to store integers
int arrCount = 0; // Initialize the count of elements in the array

// Function prototypes
void menu();
void clearData();
void printArr();
void insertElement();
void deleteElement();
void arrInput(int k);
void maxElement();
void minElement();
void findElement();


int main()
{
    menu();
    return 0;
}

void menu() // Display the menu and handle user choices
{
    while (1) // loop forever
    {
        char option=0; // Initialize the option

        printf("\nCT Quan ly day so\n");
        printf("1. Input 'c' or 'C' to clear data of the array.\n");
        printf("2. Input 'p' or 'P' to print all elements in the array.\n");
        printf("3. Input 'i' or 'I' to Input value of 1 element at position k in the array.\n");
        printf("4. Input 'd' or 'D' to delete 1 element at position k.\n");
        printf("5. Input 'f' or 'F' to find 1 vaue x in the array.\n");
        printf("6. Input 'g' or 'G' to print the maximum number.\n");
        printf("7. Input 's' or 'S' to print the minimum number.\n");
        printf("8. Input 'q' or 'Q' to exit the program.\n");

        scanf("%c", &option); // Read the user's choice
        getc(stdin); // Clear the newline character from the input buffer

        switch (option)
        {
        case 'c': case 'C':
            clearData(); // Call the function to clear data
            printf("\n\n\n\n"); // down 4 lines
            break;
        case 'p': case 'P':
            printArr(); // Call the function to print array elements
            printf("\n\n\n\n"); // down 4 lines
            break; 
        case 'i': case 'I':
            insertElement(); // Call the function to insert an element
            printf("\n\n\n\n"); // down 4 lines
            break;
        case 'd': case 'D':
            deleteElement(); // Call the function to delete an element
            printf("\n\n\n\n"); // down 4 lines
            break;
        case 'f': case 'F':
            findElement(); // Call the function to find an element
            printf("\n\n\n\n"); // down 4 lines
            break;    
        case 'g': case 'G':
            maxElement(); // Call the function to find the maximum number
            printf("\n\n\n\n"); // down 4 lines
            break;
        case 's': case 'S':
            minElement(); // Call the function to find the minimum number
            printf("\n\n\n\n"); // down 4 lines
            break;
        case 'q': case 'Q':
            exit(0); // Exit the program
            break;                                                       
        default:
            break;
        }
    }
}

void clearData() // Clear all data in the array
{
    printf("Clear data of all element in the array\n");
    for (int i = 0; i < 100; i++)
    {
        arr[i] = '\0'; // Set each element to null
    }
}

void arrInput(int k) // Input an element at position k
{
    int i=0; // Initialize a counter for duplicate checking

    printf("Input 1 element at position %d in the array \n", k);
    printf("Value between 1 and 200 \n ");
    printf("No Duplicate value \n");

    scanf("%d", &arr[k]); // Read the user input for the element at position k
    getc(stdin); // Clear the newline character from the input buffer

    while ((arr[k] <1) || (arr[k] > 200)) // Validate the input value (ensure it is within the specified range)
    {
        printf("Input 1 element at position %d in the array \n", k);
        printf("value out of 1 and 200, reinput again \n");
        scanf("%d", &arr[k]);
        getc(stdin);
    }
    
    while (arr[k] == arr[i]) // Check for duplicate values
    {
        printf("Input 1 element at position %d in the array \n", k);
        printf("Value duplicate, reinput again \n");
        scanf("%d", &arr[k]);
        getc(stdin);

        if (i < 100)
        {
            i++; // Increment the counter to avoid infinite loop
        }
    }
    
}

void printArr() // Print all elements in the array
{
    for (int i=0; arr[i]!='\0'; i++) // Calculate the number of elements in the array
    {
        arrCount++;
    }

    if (arrCount == 0) // Check if the array is empty
    {
        printf("Empty array\n");
    }
    else
    {
        printf("Elements in the array \n"); // Print each element in the array
        for (int i = 0; i < arrCount; i++)
        {
            printf("arr[%d] = %d \n", i+1, arr[i]);
        }
        
    }    
}

void insertElement() // Insert an element into the array
{
   int k = 0; // Declare an integer variable 'k' to store the input position
   printf("Input position k from 0 to 199 \n"); 
   scanf("%d", &k); // Read the value of 'k' from user input
   getc(stdin); // Clear any remaining newline characters from the input buffer

   if (arr[k] != '\0') // Check if the element at position 'k' is not null
   {
        printf("Position %d in the array having element is %d ", k, arr[k]);
   }
   else
   {
        arrInput(k); // Call a function 'arrInput' to insert an element at position 'k'
   }
}

void deleteElement() // Delete an element from the array
{
   int k = 0; // Declare an integer variable 'k' to store the input position

   printf("Input position k from 0 to 199 \n");   
   scanf("%d", &k); // Read the value of 'k' from user input
   getc(stdin); // Clear any remaining newline characters from the input buffer

   if (arr[k] == '\0') // Check if the element at position 'k' is null (empty)
   {
        printf("No element at position %d ", k);
   }
   else
   {
        printf("Delete 1 element at position %d ", k);
        arr[k] = '\0'; // Set the element at position 'k' to 0 (indicating deletion)
   } 
}

void maxElement() // Find the maximum element in the array
{
    int maxValue = arr[0]; // Initialize the maximum value with the first element of the array
    for (int i=0;i<100;i++)
    {
        if (maxValue <= arr[i])  // Compare the current element with the maximum value
        {
            maxValue = arr[i]; // If the current element is greater, update the maximum value
        }
    }
    printf("Maximum number is %d \n", maxValue);
}

void minElement() // Find the minimum element in the array
{
    int minValue = arr[0]; // Initialize the minimum value with the first element of the array
    for (int i=0;i<100;i++)
    {
        if (minValue >= arr[i])  // Compare the current element with the minimum value
        {
            minValue = arr[i]; // If the current element is smaller, update the minimum value
        }
    }
    printf("Minimum number is %d \n", minValue);
}

void findElement() // Find value available in the array
{
    int x=0; // Initialize the value to search for
    int index=0; // Initialize the index where the value is found (or 0 if not found)

    printf("Input value of x\n");
    scanf("%d", &x); // Read the value from user input
    getc(stdin); // Clear any remaining newline characters from the input buffer

    for (int i = 0; i < 200; i++)
    {
        if (arr[i] == x) // Check if the current element matches the value
        {
            index = i; // Update the index where the value is found
            break; // Exit the loop once the value is found
        }
    }

    if (index == 0) // Print the result based on whether the value was found or not
    {
        printf("No value %d in the array \n", x);
    } 
    else
    {
        printf("Have value %d at position %d in the array \n", x, index);
    }
}