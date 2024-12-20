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


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"
#include <string.h>
#include <ctype.h>


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
           menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
           viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
          addAppointment(data->appointments, data->maxAppointments,
                         data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
           removeAppointment(data->appointments, data->maxAppointments,
                            data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt){
    int i = 0, flag = 0;
    displayPatientTableHeader(); //calls display function
    
    //loop through patient array up to max number of elements
    for(i = 0; i < max; i++){
        if(patient[i].patientNumber > 0){
            displayPatientData(&patient[i], fmt); //displays patient info in fmt once the number is > 0
            flag++;
        }
    }
    
    if(flag == 0) {
            printf("*** No records found ***");
        }
    printf("\n");
}


// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max){
    int selection;

    do {
        
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        
        selection = inputInt();
        putchar('\n');
        if(selection == 1){
            searchPatientByPatientNumber(patient, max);
            putchar('\n');
            suspend();
        }
        else if (selection == 2){
            searchPatientByPhoneNumber(patient, max);
            putchar('\n');
           suspend();
        }
    }while (selection !=0);

}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max){
    int index, emptyID = 0;
    
    index = findPatientIndexByPatientNum(emptyID, patient, max); //calls function and assigns value to space
    
    if (index == -1){
        printf("ERROR: Patient listing is FULL!\n\n");
        
    } else {// once space is available will assign next free memory index in patient to the nextPatientNumber
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
    }
 
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max){
    int patientNumber, index;
    
    printf("Enter the patient number: ");
    patientNumber = inputInt();
    
    index = findPatientIndexByPatientNum(patientNumber, patient, max);
     
    //if patient record is found then menuPatientEdit will be called and the index sent.
    if(index != -1){
        putchar('\n');
        menuPatientEdit(&patient[index]);
    } else {
        printf("\nERROR: Patient record not found!\n"); //**might need to take off line at beginning
    }
}
// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max){
    int patientNumber, index, flag = 1;
    char confirmation, endCh;
    
    printf("Enter the patient number: ");
    patientNumber = inputInt();
    
    index = findPatientIndexByPatientNum(patientNumber, patient, max);
    
    if (index == -1) {
        printf("\nERROR: Patient record not found!\n\n");
    }
    
    if (index != -1){
        putchar('\n');
        displayPatientData(&patient[index], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        do {
            scanf("%c%c", &confirmation, &endCh);
            
            if ((confirmation == 'n' || confirmation == 'N') && (endCh == '\n')) {
                printf("Operation aborted.\n\n");
                flag = 0;
                clearInputBuffer();
            }
            else if ((confirmation == 'y' || confirmation == 'Y') && (endCh == '\n')) {
                //reset patient info to an empty state
                patient[index].patientNumber = 0;
                printf("Patient record has been removed!\n\n");
                flag = 0;
            }
            else {
                clearInputBuffer();
                printf("ERROR: Character must be one of [yn]: ");
            }
        } while (flag == 1);
    }
}
   


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//Sorting Function
void sortAppointments(struct Appointment appoints[], int max){ //review this for better comments
    int i, j;
    struct Appointment temp;
    //bubble sort to sort by date and time
    for(i = 0; i < max - 1; i++){ // max - 1 since the 2nd to last element is the last element that needs to be checked for bubble
        for(j = 0; j < max - 1 - i; j++){
            
            //checks if the current appointment is at a later date than the next appointment. first checks if the year is greater than and if the year is the same then checks the month and if the month is the same then checks the day, if the day is the same then checks the hour and then the minutes
            if(appoints[j].date.year > appoints[j + 1].date.year || (appoints[j].date.year == appoints[j + 1].date.year && appoints[j].date.month > appoints[j + 1].date.month) || (appoints[j].date.year == appoints[j + 1].date.year && appoints[j].date.month == appoints[j + 1].date.month && appoints[j].date.day > appoints[j + 1].date.day) || (appoints[j].date.year == appoints[j + 1].date.year && appoints[j].date.month == appoints[j + 1].date.month && appoints[j].date.day == appoints[j + 1].date.day && appoints[j].time.hour > appoints[j + 1].time.hour) || (appoints[j].date.year == appoints[j + 1].date.year && appoints[j].date.month == appoints[j + 1].date.month && appoints[j].date.day == appoints[j + 1].date.day && appoints[j].time.hour == appoints[j + 1].time.hour && appoints[j].time.min > appoints[j + 1].time.min)){
                
                //swaps the appointments if the current appointment is at a later date than the next. temp stores the data of the current appointment which is then assigned to the next app which is then assigned to temp (which will then increment as the loop continues)
                temp = appoints[j];
                appoints[j] = appoints[j+1];
                appoints[j+1] = temp;
            }
        }
    }
}

//searchDate function which searches through dates for appointments
struct Date searchDate(void){
    struct Date date;
    int day;
 
 //getting the date - year, month, day by calling inputIntRange
 printf("Year        : ");
 date.year = inputIntPositive();
 
 printf("Month (1-12): ");
 date.month = inputIntRange(1, 12);
 
 //switch case for the days in the month selected
 switch (date.month) {
     case 4: case 6: case 9: case 11:
         day = 30;
         break;
     case 2:
         if (date.year % 4 == 0){ // if its a leap year, the days for Feb will be 29
             day = 29;
         } else {
             day = 28;
         }
         break;
     default:
         day = 31;
 }
 printf("Day (1-%d)  : ", day);
 date.day = inputIntRange(1, day);
 //putchar('\n');
    
    return date;
}
// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data) {
    int i, j;
    
    //calls the sorting function to sort the data in the array
    sortAppointments(data->appointments, data->maxAppointments);
    displayScheduleTableHeader(NULL, 1);
    for(i = 0; i < data->maxAppointments; i++){
        for(j = 0; j < data->maxPatient; j++){
            if(data->appointments[i].petId == data->patients[j].patientNumber){
                displayScheduleData(&data->patients[j], &data->appointments[i], 1);
            }
        }
    }
    putchar('\n');
}


// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data){
    struct Date date;
    int i, j;
    
    date = searchDate();
    
    //sorts the appointment data by date
    sortAppointments(data->appointments, data->maxAppointments);
    
    putchar('\n');
    displayScheduleTableHeader(&date, 0);
    
    //loop through the data for appointments and patients and display the data once the id and date match with the selected appointment date
    for (i = 0; i < data->maxAppointments; i++){
        if(data->appointments[i].date.year == date.year && data->appointments[i].date.month == date.month && data->appointments[i].date.day == date.day){
            for (j = 0; j < data->maxPatient; j++){
                if(data->appointments[i].petId == data->patients[j].patientNumber){
                    displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                }
            }
        }
    }
    putchar('\n');
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment (struct Appointment* appoints, int maxAppointments, struct Patient* patients, int maxPatients){
    int i, j, patientNumber, patientIndex, validTime = 0, slotAvailable;
    struct Date date;
    struct Time time;
    
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    
    patientIndex = findPatientIndexByPatientNum(patientNumber, patients, maxPatients);
   
    if (patientIndex == -1) {
            printf("\nERROR: Patient record not found!\n");
        putchar('\n');
            return; // Exit the function if the patient record is not found
        }
    
    date = searchDate();
    
        
        while (!validTime) {
            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);
            
            // Validate time
            if ((time.hour < START_TIME || time.hour > END_TIME) ||
                (time.hour == END_TIME && time.min > 0) ||
                (time.min % INTERVAL_MINS != 0)) {
                printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", START_TIME, END_TIME, INTERVAL_MINS);
                continue; // Prompts user again for time
            }
            
            // Check if the appointment slot is already booked
            slotAvailable = 1;
            for (j = 0; j < maxAppointments; j++) {
                if (appoints[j].petId != 0 &&
                    appoints[j].date.year == date.year &&
                    appoints[j].date.month == date.month &&
                    appoints[j].date.day == date.day &&
                    appoints[j].time.hour == time.hour &&
                    appoints[j].time.min == time.min) {
                    printf("\nERROR: Appointment timeslot is not available!\n\n");
                    slotAvailable = 0;
                }
            }
            
            if (slotAvailable) {
                validTime = 1; // Time is valid and slot is available
            } else {
                date = searchDate();
            }
        }
        
        // Add the appointment
        for (i = 0; i < maxAppointments; i++) {
            if (appoints[i].petId == 0) {
                appoints[i].petId = patientNumber;
                appoints[i].date = date;
                appoints[i].time = time;
                printf("\n*** Appointment scheduled! ***\n\n");
                return; // remove and put a flag
            }
        }
    }


// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appoints, int maxAppointments, struct Patient* patients, int maxPatients){
    int i, patientNumber, patientIndex, appointmentIndex = -1;
    struct Date date;
   
    char confirmation;
    
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    
    patientIndex = findPatientIndexByPatientNum(patientNumber, patients, maxPatients);
    
    if(patientIndex == -1){
        printf("ERROR: Patient record not found!\n");
        putchar('\n');
        return;
    }
    date = searchDate();
    
    for(i = 0; i < maxAppointments; i++){
        if (appoints[i].petId == patientNumber && appoints[i].date.year == date.year && appoints[i].date.month == date.month && appoints[i].date.day == date.day){
            appointmentIndex = i;
        }
    }
    
    if (appointmentIndex == -1){
        printf("ERROR: No matching appointment found.\n");
        return;
    }
    putchar('\n');
        displayPatientData(&patients[patientIndex], FMT_FORM);
        
        printf("Are you sure you want to remove this appointment (y,n): ");
        scanf("%c%*c", &confirmation);
        
        if (confirmation == 'y' || confirmation == 'Y'){
            
            //reset patient info to an empty state
            appoints[appointmentIndex].petId = 0;
            
            printf("\nAppointment record has been removed!\n\n");
        } else{
            printf("Operation aborted.\n\n");
        }
    }


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max){
    int patientNumber, index;
    printf("Search by patient number: ");
    
    //calls function to get the integer number entered
    patientNumber = inputInt();
    
    //calls result from findPatientIndex and stores to index
    index = findPatientIndexByPatientNum(patientNumber, patient, max);
    
    if (index != -1){
        putchar('\n');
        displayPatientData(&patient[index], FMT_FORM);
    } else {
        printf("\n");
        printf("*** No records found ***\n");
    }
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max){
    char phoneNumber[PHONE_LEN+1];
    int flag = 0, i = 0;
    
    printf("Search by phone number: ");
   inputCString(phoneNumber,PHONE_LEN, PHONE_LEN);
    putchar('\n');
    displayPatientTableHeader();
    
    for (i = 0; i < max; i++){
        if (strcmp(patient[i].phone.number, phoneNumber) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            flag++;
        }
    }
    if (flag == 0){
        printf("\n*** No records found ***\n");
    }
}

// Get the next highest patient number
// (Copy your code from MS#2)
// the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max) {
    int nextNumber = 0, i = 0;
    
    for(i = 0; i < max; i++){
        if (patient[i].patientNumber > nextNumber){
            nextNumber = patient[i].patientNumber;
        }
    }
    nextNumber = nextNumber + 1;
    
    return nextNumber;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max){
    int i = 0, flag = 1, index = -1;
    //loop through patient array to locate patient id number
    for (i = 0; i < max && (flag !=0); i++){
        if(patient[i].patientNumber == patientNumber) {
            index = i;
            flag = 0;
        }
    }
    //will return -1 if patient id cannot be found
    return index;
    
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) {
    
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN); //1 as minimum length and max as name_len
    printf("\n");
    
    inputPhoneData(&patient->phone);
    printf("*** New patient record added ***\n\n");
   
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone){
    int selection;
   
    
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');
    
    
    switch(selection){
        case 1: //copies the description into struct as CELL and maintains the description length
            strncpy(phone->description, "CELL", PHONE_DESC_LEN);
            
            printf("Contact: %s\n", phone->description);
            
            printf("Number : ");
            inputCString(phone->number, 10, 10);
            putchar('\n');
           
            break;
            
        case 2:
            strncpy(phone->description, "HOME", PHONE_DESC_LEN);
            printf("Contact: %s\n", phone->description);
            
            printf("Number : ");
            inputCString(phone->number, 10, 10);
            putchar('\n');
            
            break;
            
        case 3:
            strncpy(phone->description, "WORK", PHONE_DESC_LEN);
            printf("Contact: %s\n", phone->description);
            
            printf("Number : ");
            inputCString(phone->number, 10, 10);
            putchar('\n');
            
            break;
            
        case 4:
            strncpy(phone->description, "TBD", PHONE_DESC_LEN);
            break;
    }

}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max){
    int i = 0;
    FILE* fp = fopen(datafile, "r");

    if(fp != NULL){ //read the data in the file separated by | and store to the array
        while(i < max && fscanf(fp,"%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number) != EOF){
            i++;
        }
        fclose(fp);
    } else{ //display an error message if file cant be read
        printf("Error opening file %s\n", datafile);
    }
    return i;
}
    

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max){
    int i = 0;
    FILE* fp = fopen(datafile, "r");
    if(fp != NULL){ //read the data in the file separated by , and store in array
        while(i < max && fscanf(fp,"%d,%d,%d,%d,%d,%d", &appoints[i].petId, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) != EOF){
            i++;
        }
        fclose(fp);
    }else { //display error message if file cant be read
        printf("Error opening file %s\n", datafile);
}
    return i;
}
