#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

int found, i, j, len, choice, count, c, attempts;

void listContacts(AddressBook *addressBook, int sortCriteria)
{
   
    switch (sortCriteria)
    {
        case 1:
            printf("sorting based on name\n");
            for (i = 0; i < addressBook->contactCount - 1; i++)                // sorting based on name
            {
                for (j = 0; j < addressBook->contactCount - i - 1; j++)
                {
                    if (strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name) > 0)   // by using bubble sort
                    {
                        Contact temp = addressBook->contacts[j];
                        addressBook->contacts[j] = addressBook->contacts[j+1];
                        addressBook->contacts[j+1] = temp;
                    }                                                                                       // swapping the contacts
                }
            }
            printf("Index\tname\t\tphone number\tmail id\n");
            for (i = 0; i < addressBook->contactCount; i++)
            {
                printf("%d\t%s\t%s\t%s\n",i + 1,addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);  // printing all contact (sort based on name)
                 printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            }
            break;

        case 2:                                                                                                     // sorting based on phone number
            printf("Sorting based on phone number\n");
            for (i = 0; i < addressBook->contactCount - 1; i++)
            {
                for (j = 0; j < addressBook->contactCount - i - 1; j++)                            // bubble sort
                {
                    if (strcasecmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone) > 0)
                    {
                        Contact temp = addressBook->contacts[j];                                                                                // swapping
                        addressBook->contacts[j] = addressBook->contacts[j+1];
                        addressBook->contacts[j+1] = temp;
                    }
                }
            }
            printf("Index\tname\tphone number\tmail id\n");
            for (i = 0; i < addressBook->contactCount; i++)
            {
				printf("%d\t%s\t%s\t%s\n",i + 1,addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);  // printing all contact (sort based on phone)
                 printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            }
            break;

        case 3:
            printf("sorting based on email\n");
            for (i = 0; i < addressBook->contactCount - 1; i++)                                                                 // sorting based on email
            {
                for (j = 0; j < addressBook->contactCount - i - 1; j++)                     // bubble sort
                {
                    if (strcasecmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email) > 0)
                    {                                                                                                   // swapping
                        Contact temp = addressBook->contacts[j];
                        addressBook->contacts[j] = addressBook->contacts[j+1];
                        addressBook->contacts[j+1] = temp;
                    }
                }
            }
            printf("Index\tname\t\tphone number\tmail id\n");
            for (i = 0; i < addressBook->contactCount; i++)
            {
				printf("%d\t%s\t%s\t%s\n",i + 1,addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);  // printing all contact (sort based on email)
                 printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            }
            break;

        case 4:
            break;                                              // exit
        default:
            printf("invalid input\n");
            break;
        printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    }
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);                                        // save file
    exit(EXIT_SUCCESS);
}

int namevalidation(AddressBook *addressBook, char name_dup[])            // name validation
{
    attempts = 0;
    while (attempts < 2)
    {
        printf("Enter the name : ");
        int valid = 1;
        if (!scanf(" %[^\n]", name_dup))
        {
            printf("Invalid input\n");
            while (getchar() != '\n');
            attempts++;
            continue;
        }
        for (int i = 0; name_dup[i] != '\0'; i++)
        {
            if (!isalpha(name_dup[i]) && !isspace(name_dup[i]))         // letter and space checking 
            {
                valid = 0;
                break;
            }
        }
        if (!valid)
        {
            printf("Error message :Only alphabets allowed\n");
            attempts++;
            continue;
        }
        if (strlen(name_dup) < 3)                                                           // checking the legth of the name 
        {
            printf("Error message :Name must contain at least 3 characters\n");
            attempts++;
            continue;
        }
        valid = 1;
        for (int k = 0; k < addressBook->contactCount; k++)
        {
            if (strcasecmp(addressBook->contacts[k].name, name_dup) == 0)
            {
                valid = 0;
                break;
            }
        }
        if (!valid)
        {
            printf("Error message :Name already exists\n");
            attempts++;
            continue;
        }
        return 1;                                              // Success
    }
    if(attempts==2)  
    {                       // Failed
    return 0;  
    }                                                  
}

int phonevalidation(AddressBook *addressBook, char phone_dup[])
{                                                                                                   // [phone validation]
    attempts = 0;
    while (attempts < 2)
    {
        
        printf("Enter the phone : ");
        if (!scanf(" %s", phone_dup))
        {
            printf("Invalid Input\n");
            while (getchar() != '\n');
            attempts++;
            continue;
        }
        count = 1;
        for (j = 0; phone_dup[j] != '\0'; j++)                                              // digit checking
        {
            if (!isdigit(phone_dup[j]))
            {
                count = 0;
                break;
            }
        }
        if (!count)
        {
            printf("Error message : phone number must contain only digits\n");
            attempts++;
            continue;
        }
        if (strlen(phone_dup) != 10)
        {                                                                                       // length checking, lenght must be equal to 10
            printf("Error message : Phone number must contain exactly 10 digits\n");
            attempts++;
            continue;
        }
        if (phone_dup[0] < '6' || phone_dup[0] > '9')                               // starting digit must be in between 6&9
        {
            printf("Error message : First digit must be in between 6 and 9\n");
            attempts++;
            continue;
        }
        count = 1;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcasecmp(addressBook->contacts[i].phone, phone_dup) == 0)                                         // comparing with existing phone
            {
                count = 0;
                break;
            }
        }
        if (!count)
        {
            printf("Error message :Phone number must be unique.\n");
            attempts++;
            continue;
        }
        return 1;
    }
    if (attempts == 2)                                                              // only two attempts are allowed
    {
        return 0;
    }
}

int emailvalidation(AddressBook *addressBook, char email_dup[])                     // email validation
{
    attempts = 0;
    while (attempts < 2)
    {
        printf("Enter the email : ");
        if (!scanf(" %[^\n]", email_dup))
        {
            printf("Invalid Input\n");
            while (getchar() != '\n');
            attempts++;
            continue;
        }
        count = 1;
        for (i = 0; email_dup[i] != '\0'; i++)                  // in email consists only these type's ( alphabets(small letters), numbers, '@' , '.' , '_' , '-' ) 
        {
            if (!((email_dup[i] >= 'a' && email_dup[i] <= 'z') ||(email_dup[i] >= '0' && email_dup[i] <= '9') ||email_dup[i] == '.' ||email_dup[i] == '@' ||email_dup[i] == '-' ||email_dup[i] == '_'))
            {
                count = 0;
                break;
            }
        }
        if (!count)
        {
            printf("Error message : Only lowercase letters, digits, '.', '@', '-' and '_' are allowed.\n");
            attempts++;
            continue;
        }
        int at_pos = 0, dot_pos = 0;
        int posat = 0, posdot = 0;
        for (i = 0; email_dup[i] != '\0'; i++)
        {
            if (email_dup[i] == '@')                                                // '@' Position check
            {
                at_pos++;
                posat = i;
            }
            if (email_dup[i] == '.')                                            // '.' position check
            {
                dot_pos++;
                posdot = i;
            }
        }
        if(!posat)
        {
            printf("Error message : user name is not found\n ");
            attempts++;
            continue;
        }
        if (at_pos == 0 && dot_pos == 0)                            
        {
        printf("Error message : '@' and '.' must be present.\n");     //  check '@' , '.' 
        attempts++;
        continue;
        }
        if(at_pos==0)
        {                                                               // check '@'
        printf("Error message : '@'  must be present.\n");
        attempts++;
        continue;
        }
        if(dot_pos==0)
        {
        printf("Error message : '.' must be present.\n");           // check '.'
        attempts++;
        continue;
        }
        if (at_pos != 1)                                        // only one '@' is allowed
        {
            printf("Error message :Email must contain exactly one '@'.\n");
            attempts++;
            continue;
        }
        if (dot_pos != 1)
        {                                                       // only one '.' is allowed
            printf("Error message : Email must contain exactly one '.'.\n");
            attempts++;
            continue;
        }
        if (posdot < posat)
        {                                                               // '.' after '@' 
            printf("Error message :'.' must come after '@'.\n");
            attempts++;
            continue;
        }
        if (posdot == posat + 1)
        {
            printf("Error message :There must be at least one character between '@' and '.'.\n"); // domain must be there in between '@' and '.'
            attempts++;
            continue;
        }
        count = 0;
        if((strcasecmp(&email_dup[posdot+1],"com"))!=0)                                             // after '.' com only allowed 
        {
            printf("Error message : after '.' com only allowed\n");
            attempts++;
            continue;
        }
        int duplicateEmail = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcasecmp(addressBook->contacts[i].email, email_dup) == 0)
            {
                duplicateEmail = 1;
                break;
            }
        }
        if (duplicateEmail)
        {
            printf("Error message :Email ID must be unique.\n");                                   // check with existing email's
            attempts++;
            continue;
        }
        return 1;                                               // success
    }
    if (attempts == 2)
    {  
        return 0;
    }
}


void createContact(AddressBook *addressBook)                                                // create contact
{
     printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    char name_dup[100];                                                                                   // creating duplicate name & phone & email
    char phone_dup[100];
    char email_dup[100];

    if (addressBook->contactCount >= MAX_CONTACTS)                                                                // checking whether the max limit reached or not
    {
        printf("Error message :Address book is full. Cannot add more contacts.\n");
        return;
    }
    printf("1. continue to create contact\n");
    printf("2. exit\n");
    printf("enter choice : ");
    if (scanf("%d", &choice) != 1)
    {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid choice : please try again\n");
        return;
    }

    switch(choice)
    {
        case 1:
            if(!namevalidation(addressBook,name_dup))                       // calling name validation
            {
                return;
            }
            if(!phonevalidation(addressBook,phone_dup))                     // calling phone validation
            {
                return;
            }
            if(!emailvalidation(addressBook, email_dup))                            // calling email validation
            {
                return;
            }
            printf("do you want to save the contact yes(press y) /No(press n) : ");             // yes / no for continue
            char ch;
            scanf(" %c",&ch);
            if(ch=='y')
            {
                int index = addressBook->contactCount;                                          // copy to the originals
                strcpy(addressBook->contacts[index].name, name_dup);
                strcpy(addressBook->contacts[index].phone, phone_dup);
                strcpy(addressBook->contacts[index].email, email_dup);
                addressBook->contactCount++;                             
                printf("CONTACT ADDED:\nname   :%s\nnumber :%s\nemail  :%s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
                 printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                break;
            }
            else if(ch=='n')
            {
                break;
            }
            break;
        case 2:
         printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");    
        break;
        default:
            printf("Invalid choice :  please try again\n");
             printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            return;
    }
}
void searchContact(AddressBook *addressBook)                    // search contact
{
     printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    char search_char[100];
    found = 0;                                                  // two case for search and exit 
    printf("1. Search contact\n");
    printf("2. exit\n");
    printf("Enter your choice : ");
    if (scanf("%d", &choice) != 1)
    {
        while ((c = getchar()) != '\n' && c != EOF); // clear bad input
        printf("Invalid input\n");
        return;
    }
    switch(choice)
    {
        case 1:
            printf("1. Search the name/number/email: ");                                   // check the name/number/email
            if (!(scanf(" %[^\n]",search_char))) 
            { 
                printf("Invalid Input\n"); 
                return; 
            }
            printf("\ndo you want to search the contact yes(press y) /No(press n) : ");             // yes / no for continue
            char ch;
            scanf(" %c",&ch);
            if(ch=='y')
            {           
                for (i = 0; i < addressBook->contactCount; i++)                                     // find the search element from the saved contacts
                {
                    if ((strstr(addressBook->contacts[i].name, search_char)) || (strstr(addressBook->contacts[i].phone, search_char)) || (strstr(addressBook->contacts[i].email, search_char)))
                    {
                        printf("%d\t%s\t%s\t%s\n",i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                         printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                        found = 1;
                    }
                }
                if (!found)
                {
                    printf("Contact is not found\n");
                    return;
                }
            }
            else if(ch=='n')
            {
                break;
            }
            else
            {
                printf("invalid input\n");
                return;
            }
            break;
        case 2:
         printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");                                                                     // exit
            break;
        default:
            printf("Invalid input\n");
            return;
    }
    
}

void editContact(AddressBook *addressBook)                                              // edit contact 
{
     printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    if (addressBook->contactCount == 0) 
    {
        printf("No contacts available to edit.\n");
        return;
    }

    int matchedIndexes[MAX_CONTACTS];                                    // store matched contact indices
    int matchCount = 0;
    int selectedIndex = -1;
    int edit_idx;
    char search_char1[100];
    char newName[100];                                                              // new variable for storing update contact details
    char newPhone[100];
    char newEmail[100];
    char ch;

    printf("1. Edit by name/phone/email\n");
    printf("2. exit\n");
    printf("Enter choice : ");
    if (scanf("%d", &choice) != 1)
    {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid input\n");
        return;
    }

    if (choice == 2)
        return;

    if (choice != 1)
    {
        printf("invalid input\n");
        return;
    }

    printf("Enter search to edit : ");
    if (scanf(" %[^\n]", search_char1) != 1)
    {
        printf("Invalid input\n");
        return;
    }
                                                                                            //comparing with previous contact details
    found = 0;
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, search_char1) ||strstr(addressBook->contacts[i].phone, search_char1) || strstr(addressBook->contacts[i].email, search_char1))
        {
            printf("%d\t%s\t%s\t%s\n", matchCount + 1, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            matchedIndexes[matchCount] = i;
            matchCount++;
            found = 1;
        }
    }

    if (!found)
    {
        printf("no contact is found\n");
        return;
    }

    printf("1. Edit by index \n");
    printf("2. exit\n");
    printf("Enter choice : ");
    if (scanf("%d", &choice) != 1)
    {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid input\n");
        return;
    }

    if (choice == 2)
        return;

    if (choice != 1)
    {
        printf("invalid input\n");
        return;
    }

    printf("Select the index number to edit: ");
    if (scanf("%d", &edit_idx) != 1 || edit_idx < 1 || edit_idx > matchCount)      // checking the enter index
    {
        printf("Invalid index\n");
        return;
    }
    selectedIndex = matchedIndexes[edit_idx - 1];

    printf("1. Edit name\n");
    printf("2. Edit phone number\n");
    printf("3. Edit email\n");
    printf("4. Edit entire contact\n");         // proiving oprion to seelct for edit in different ways
    printf("5. exit\n");
    printf("Select the choice: ");
    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid choice\n");
        return;
    }

    if (choice < 1 || choice > 5)
    {
        printf("invalid input\n");
        return;
    }

    if (choice == 5)
        return;

    switch (choice)
    {
        case 1:
            printf("\ndo you want to edit the contact yes(press y) /No(press n) : ");
            scanf(" %c", &ch);
            if (ch == 'y')
            {
                if (!namevalidation(addressBook, newName))         // calling name validation
                    return;
                strcpy(addressBook->contacts[selectedIndex].name, newName);           
            }
            else if (ch != 'n')
            {
                printf("invalid input\n");
                return;
            }
            break;          // exit

        case 2:
            printf("\ndo you want to edit the contact yes(press y) /No(press n) : ");
            scanf(" %c", &ch);
            if (ch == 'y')
            {                                                                   // calling phone validation
                if (!phonevalidation(addressBook, newPhone))
                    return;
                strcpy(addressBook->contacts[selectedIndex].phone, newPhone);
            }
            else if (ch != 'n')
            {
                printf("invalid input\n");
                return;
            }
            break;                                                                      // exit

        case 3:
            printf("\ndo you want to edit the contact yes(press y) /No(press n) : ");
            scanf(" %c", &ch);
            if (ch == 'y')
            {
                if (!emailvalidation(addressBook, newEmail))                                                // calling email validation 
                    return;
                strcpy(addressBook->contacts[selectedIndex].email, newEmail);
            }
            else if (ch != 'n')
            {
                printf("invalid input\n");
                return;
            }
            break;                                                                                                  // exit

        case 4:
            printf("do you want to save the contact yes(press y) /No(press n) : ");
            scanf(" %c", &ch);
            if (ch == 'y')
            {
                if (!namevalidation(addressBook, newName))                                              // calling all validation to edit entire contact
                    return;
                if (!phonevalidation(addressBook, newPhone))
                    return;
                if (!emailvalidation(addressBook, newEmail))
                    return;
                strcpy(addressBook->contacts[selectedIndex].name, newName);
                strcpy(addressBook->contacts[selectedIndex].phone, newPhone);                                               // copying all updated contact details to the original contact details 
                strcpy(addressBook->contacts[selectedIndex].email, newEmail);
            }
            else if (ch != 'n')
            {
                printf("invalid input\n");
                return;
            }
            break;           // exit
    }

    printf("Contact updated:\nName: %s\nPhone: %s\nEmail: %s\n",addressBook->contacts[selectedIndex].name,addressBook->contacts[selectedIndex].phone,addressBook->contacts[selectedIndex].email);   // displaying to the terminal
     printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
}

void deleteContact(AddressBook *addressBook)                        // delete contact
{
    char search_char[100];
    int delete_idx;
    int matchedIndexes[MAX_CONTACTS];
    int matchCount = 0;
    char ch;
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("1. continue to delete contact\n");
    printf("2. exit\n");
    printf("enter choice : ");
    if (scanf("%d", &choice) != 1)
    {
        while ((c = getchar()) != '\n' && c != EOF); // clear bad input
        printf("Invalid choice : please try again\n");
        return;
    }

    if (choice == 2)
        return;

    if (choice != 1)
    {
        printf("Invalid input\n");
        return;
    }

    printf("Search the name/number/email: ");
    if (scanf(" %[^\n]", search_char) != 1)            
    {
        printf("Invalid Input\n");
        return;
    }

    found = 0;
    for (i = 0; i < addressBook->contactCount; i++)   // comnparing with existing contacts
    {
        if (strstr(addressBook->contacts[i].name, search_char) || strstr(addressBook->contacts[i].phone, search_char) ||strstr(addressBook->contacts[i].email, search_char))
        {
            printf("%d\t%s\t%s\t%s\n", matchCount + 1,addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);  // printing matched contacts
            matchedIndexes[matchCount++] = i;    // storing the matched contact index
            found = 1;
        }
    }

    if (!found)
    {
        printf("Contact is not found\n");
        return;
    }

    printf("Select the index number to delete : ");
    if (scanf("%d", &delete_idx) != 1 || delete_idx < 1 || delete_idx > matchCount)           // comparing with entered index with matched indexes
    {
        printf("Invalid index\n");
        return;
    }

    i = matchedIndexes[delete_idx - 1];
    printf("do you want to delete the contact yes(press y) /No(press n) : ");
    scanf(" %c", &ch);
    if (ch == 'y')
    {
        for (j = i; j < addressBook->contactCount - 1; j++)
        {
            Contact temp =addressBook->contacts[j];                       
            addressBook->contacts[j] = addressBook->contacts[j + 1];  // shift later contacts left
            addressBook->contacts[j + 1]= temp;
        }
        addressBook->contactCount--;
        printf("Contact deleted successfully.\n");         // reducing the size of contacts
         printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        return;
    }
    else if (ch != 'n')
    {
        printf("invalid input\n");
         printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        return;                                             // exit
    }
     
}
