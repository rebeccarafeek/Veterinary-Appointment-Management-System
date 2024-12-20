/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
 Full Name  : Rebecca Rafeek
 Student ID#: 168393239
 Email      :rlrafeek@myseneca.ca
 Section    : NBB

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"
#include <string.h>
#include <ctype.h>

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//
// get an integer
int inputInt(void){
    int num;
    char last;
    
    do {
    scanf("%d%c",&num, &last);
        if (num < 0 || last != '\n'){
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
    }while (num<0|| last != '\n');
        
    return num;
}

//get a positive integer
int inputIntPositive(void){
    int num;
    do {
       num = inputInt();
        if (num <= 0){
            printf("ERROR! Value must be > 0: ");
        }
        
    }while (num <= 0);
    return num;
}

// ensure integer is within the range
int inputIntRange(int min, int max){
    int num;
    do {
        num = inputInt();
        if(num < min|| num > max){
            printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
        }
    } while (num< min || num > max);
    return num;
}

//ensure input contains the valid characters
char inputCharOption(const char validChars[]){
        char ch;
    int valid, i;
        
        do{
            scanf(" %c", &ch);
            clearInputBuffer();
            valid = 0;
            
            for(i = 0; validChars[i] != '\0'; i++){
                if (ch == validChars[i]){
                    valid = 1;
                }
            }
            if (valid == 0) {
                printf("ERROR: Character must be one of [%s]: ", validChars);
            }
        } while (valid == 0);
    return ch;
    }
//receive a string within certain length limits
void inputCString(char *str, int min, int max){
    char temp[200]; // temp variable to store user entered string(characters)
     int numChar;
     do {

       scanf("%[^\n]%*c",
             temp); // scans characters until newline character is found
       numChar = strlen(temp);
       if (min == max && max != numChar) {
         printf("Invalid %d-digit number! Number: ", min);
       } else if (numChar > max) {
         printf("ERROR: String length must be no more than %d chars: ", max);
       } else if (numChar < min) // checks the length of string
       {
         printf("ERROR: String length must be between %d and %d chars: ", min,
                max);
       }
     } while (numChar < min || numChar > max);
     strcpy(str, temp); // copies the string entered by user to the variable
   }
    /*int length;
    
    do {
        scanf("%[^\n]", str); //to scan entire input until enter is pressed
        clearInputBuffer();
        
        length = strlen(str);
        if(min == max && max != length){
            printf("Invalid %d-digit number! Number: ", min);
        } else if (length > max){
            printf("ERROR: String length must be no more than %d chars: ", max);
        } else if (length < min){
            printf("ERROR: String length must be between %d and %d chars: ", min, max);
        }
    } while (length < min || length > max);
   // strcpy(str, str); */
//}
        
      

//displays the phone number once valid input is entered
void displayFormattedPhone (const char *phone){
    int length = 0;
    int i = 0;
    int validFlag = 1;
        
    if (phone == NULL) {
        validFlag = 0;
        
    }else {
        length = strlen(phone);
        
        for (i = 0; i < length; i++){
            if (phone[i] < '0' || phone[i] > '9'){
                validFlag = 0;
            }
        }
        if(length != 10){
            validFlag = 0;
        }
    } // possibly remove this if doesnt work
        
        if (validFlag == 1) {
            printf("(%c%c%c)%c%c%c-%c%c%c%c", phone[0], phone[1], phone[2], phone[3], phone[4], phone[5], phone[6], phone[7], phone[8], phone[9]);
        } else  {
            printf("(___)___-____");
        }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

