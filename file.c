#include <stdio.h>
#include <string.h>
#include "file.h"
#include<unistd.h>

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *ptr = fopen("contact.csv", "w+");
    if (ptr == NULL)
    {
        fprintf(stderr, "File not found\n");
        return;
    }
    for (int i = 0; i < addressBook->contactCount; i++)             // saving the contact
    {
        fprintf(ptr, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(ptr);
    for(int i = 0; i <= 100; i++)
    {
        printf("\rSaving and Exiting");
        for(int j = 0; j < i; j++)                     // animation of saving
            printf(".");
        for(int j = i; j < 100; j++)
            printf(" ");
        printf("] %3d%%\r", i);
        fflush(stdout);
        usleep(15000);
    }
    printf("\r\033[K");
    printf("Saved Successfully!\n");
    fflush(stdout);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *ptr = fopen("contact.csv", "r");
    if (ptr == NULL)
    {                                                                       // loading contact from the file
        fprintf(stderr, "File not found\n");
        return;
    }
    while((fscanf(ptr, " %[^,],%[^,],%[^\n]",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email))==3)
    {
         addressBook->contactCount++;
    }
    fclose(ptr);


}
