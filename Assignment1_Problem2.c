#include <stdio.h>

int main(){
    char string1[25]=""; // assign first string with size of 25 and no characters
    char string2[25]=""; // assign second string with size of 25 and no characters
    int count1 = 0; // assign first count to 0
    int count2 = 0; // assign second count to 0

    printf("Input first string\n");
    gets(string1); //get value of first string
    printf("Input second string\n");
    gets(string2); //get value of second string

    for (int i = 0; i < 25; i++) //loop through 25 characters
    {
        if (string1[i] != '\0') // compare if first string not contains null characters
        {    
            count1++; // count length of first string
        }
    }

    for (int j = 0; j < 25; j++) //loop through 25 characters
    {
        if ( string2[j] != '\0')  // compare if second string not contains null characters
        {
            count2++; // count length of second string
        }
    } 

    if(count1 > count2) // if first string length > second string length
    {
        printf("string1 = %s", string1); 
    } 
    else if (count1 < count2) // if first string length < second string length
    {    
        printf("string2 = %s", string2);
    } 
    else // none of 2 conditions
    {
        printf("equal length");
    }
    return 0;
}
