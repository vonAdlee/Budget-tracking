#include <stdio.h>
#include <stdlib.h>
#include "entry.h"
#include "sortingNfiltering.h"

void display();

int main(int argc, char *argv[])
{


    if(argc != 2)
    {   
        // User did not provide a file as an argument.

        printf("User have not passed the file\n");
        return 1;
    }

    read_file(argv[1]);


    

    int exit = 1;

    do
    {
        
    printf("Budget Tracking System\n");
    printf("======================\n");

    printf("1. Display all entries\n");
    printf("2. Expense Distribution\n");
    printf("3. Sort Entries\n");
    printf("4. Add Income / Expense Entry\n");
    printf("5. Modify Entry\n");
    printf("6. Filter by Month\n");
    printf("7. Undo last operation\n");
    printf("8. Exit\n");

    printf("choice: ");

    int choice;

    scanf("%d" , &choice);  

    if(choice < 1 || choice > 8)                            // try again if invalid value.
    {
        system("clear");
        printf("You entered a wrong value. Try again\n\n");
    }


// Choice one to display all entries.

    if(choice == 1)
    {
        system("clear");
        display();
    }


// choice 2 to see the distribution of income and expenses.

    if(choice == 2)
    {
        system("clear");
        printf("==== Expense Distribution Report ====\n");
        distribution();
        printf("==============================\n\n\n");
    }


// Choice 3 to display sort menu

    if(choice == 3)
    {
        int sortChoice;

        system("clear");

        printf("Sort Menu\n");              // Display a new menu for sort. 
        printf("1. Sort by ID\n2. Sort by Date\n3. Sort by Amount\n4. Sort by Description\n");
        printf("Choice: ");

        scanf("%d" , &sortChoice);

        if(sortChoice < 1 || sortChoice > 4)                // if choice is invalid.
        {
            printf("Entered wrong value. Please try again.\n\n");
        }

        if(sortChoice == 1)                                 // if choice is 1 sort by id
        {
            system("clear");
            sort_by_id();
            display();
        }

        if(sortChoice == 2)                                 // if choice is 2 sort by date
        {
            system("clear");
            sort_by_date();
            display();
        }

        if(sortChoice == 3)                                 // if choice is 3 sort by amount
        {
            system("clear");
            sort_by_amount();
            display();
        }

        if(sortChoice == 4)                                 // if choice is 4 sort by description
        {
            system("clear");
            sort_by_description();
            display();
        }
    }


// Choice 4 to add a new entry.

    if(choice == 4)
    {
        system("clear");
        add_entry();
    }

// Choice 5 to modify an entry by amount or date.

    if(choice == 5)
    {
        system("clear");
        display();
        modify();
    }



// Choice 6 to filter entries by Month.

    if(choice == 6)
    {
        system("clear");
        filter_by_month();
        printf("\n\n");
    }

// Choice 7 for undoing the last operation.

    if(choice == 7)
    {
        system("clear");
        undo_last_action();

    }

// Choice 8 for exiting the program.
    if(choice == 8)
    {
        system("clear");
        printf("Goodbye and thanks for using our budget tracker app.\n");

        exit = 0;
    }

    } while (exit == 1);

    free_entries();
    return 0;
}


// Function to display all of the entries in a organized form.

void display()
{
        printf("Finances Summary\n");
        printf("================\n\n\n");

        printf("%-5s %-12s %-10s %-10s %-15s %-10s\n", "ID", "Date", "Type", "Category", "Description", "Amount");  // Organizing the entry template
        printf("--------------------------------------------------------------\n");

// Reading every entry in the entries array.

        for (int i = 0; i < count; i++)
        {
            printf("%-5d %-12s %-10s %-10s %-15s $%.2f\n", 
            entries[i].id, entries[i].date, entries[i].type, 
            entries[i].subtype, entries[i].description, entries[i].amount);
        }
        printf("\n\n");
}

