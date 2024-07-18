#include <stdio.h>

void swap(int *evenNumber, int *oddNumber) // Use pointers to avoid clear result after assign the value 
{
    int temp = *evenNumber; // temp pointed to evenNumber address's value
    *evenNumber = *oddNumber;// evenNumber pointed to oddNumber address's value
    *oddNumber = temp;  // oddNumber pointed to temp address's value
}

int main()
{
    int evenNumber = 2; // Assign evenNumber to 2
    int oddNumber = 3; // Assign oddNumber to 3
    printf("evenNumber: %d, oddNumber: %d\n", evenNumber, oddNumber); 
    swap(&evenNumber, &oddNumber); // swap function and point to the address of the even and odd numbers
    printf("evenNumber: %d, oddNumber: %d\n", evenNumber, oddNumber); 
    return 0;
}