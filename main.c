/*
NAME         : VEERAMREDDIGARI SESHU KUMAR REDDY
ADMIN NO     : 26012_108
Start date   : 09-07-2026
End date     : 28-07-2026
PROJECT TITLE: Addressbook

>> For this project used functions are strstr ( for searching purpose), strcasecmp ( somparing the contact details), loops, conditions, structures, functions, datatypes, strings, arrays, pointers, file saving method, stdios, isalpha( character checking), 
   isdigit( digits checking), isspace( space checking). 

----ADDRESSBOOK MENU-----
1. Create contact           : creating a contact and then check the validation of (name, phone, email).
2. Search contact           : searching contact by using strcasecmp function  
3. Edit contact             : edit contact is done by using search and the storing sreach contact indexes and by using index value upated the contact details
4. Delete contact           : first searching the contact by using name / phone / email storing the matched contact indexes , by entering the index delete contact is done
5. List all contacts        : In list contact , bubble sort is used to list all contact in a orderr by ( name , phone, email).
6. Exit 

---- CREATE CONTACT----
1.enter name
2.enter phone number
3.enter email

---- SEARCH CONTACT-----
1. search contact by name/email/phone

-----EDIT CONTACT-----
1. search contact to edit 

EDIT IS DONE BY USING INDEX

1. edit  name
2. edit  phone
3. edit email
4. edit entire contact

----DELETE CONTACT----
1. search contact

DELETE IS DONE BY USING INDEX

1. enter index to delete

---SAVE FILE-----
1.saving file

---------SAMPLE INPUT 1-------
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
----------SAMPLE OUTPUT 1-----
CONTACT ADDED:
name   :seshu
number :9398347711
email  :seshu@gmail.com

*/
#include <stdio.h>
#include "contact.h"

int main() {
    int choice, sortChoice,c ;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: "); 
        if(scanf("%d", &choice) == 0)
        {
            while((c = getchar()) != '\n');
        }
        switch (choice) 
        {
            
            case 1:
                createContact(&addressBook);                    // calling create contact function to create contact
                break;
            case 2:
                searchContact(&addressBook);                    // calling search contact function to search contact
                break;
            case 3:
                editContact(&addressBook);                      // calling editcontact function to edit contact
                break;
            case 4:
                deleteContact(&addressBook);                       // calling delete contact to delete contact
                break;
            case 5:
              printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("4. exit\n");
                printf("Enter your choice: ");
                if(scanf("%d", &sortChoice) == 0)
                {
                    while((c = getchar()) != '\n');
                }
                listContacts(&addressBook, sortChoice);        // calling list contact function to list all contacts
                break;
            case 6:
                 saveContactsToFile(&addressBook);              // calling savecontacttofile function to save file
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        
       
    } while (choice != 6);
    
       return 0;                                        //exit
}
