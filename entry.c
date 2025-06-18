#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "entry.h"


    

    Entry *entries = NULL;
    int count = 0;
    int capacity = 15;
    Entry *undo_entry = NULL;

    void read_file(const char *filename)
    {
        FILE *file = fopen(filename, "r");

        if(!file)
        {
            printf("Error opening file.\n");
            exit(EXIT_FAILURE);
        }

        entries = malloc(sizeof(Entry) * capacity);         // allocate memory for entries

        if(!entries)
        {
            printf("Error allocating memory");
            exit(EXIT_FAILURE);
        }

        char line[512];

        while(fgets(line, sizeof(line), file))
        {
            if(count >= capacity)
            {
                capacity = capacity * 2;
                entries = realloc(entries, sizeof(Entry)* capacity);
            }


        char *token = strtok(line, "|");
        entries[count].id = atoi(token);
        token = strtok(NULL, "|"); strcpy(entries[count].date, token);
        token = strtok(NULL, "|"); strcpy(entries[count].type, token);
        token = strtok(NULL, "|"); strcpy(entries[count].subtype, token);
        token = strtok(NULL, "|"); strcpy(entries[count].description, token);
        token = strtok(NULL, "|"); entries[count].amount = atof(token);

        count++;    // To read the next entry.
        }

        fclose(file);           // Close file.

    } 


    void distribution()
    {
        double income = 0;
        double expense = 0;
        double wants = 0;
        double needs = 0;
        double net = 0;


        for(int i = 0 ; i < count ; i++)
        {
            if(strcmp(entries[i].type , "income") == 0)
            {
                income += entries[i].amount;
            }

            else
            {
                expense += entries[i].amount;
            }

            if(strcmp(entries[i].subtype , "Needs") == 0)
            {
                needs += entries[i].amount;
            }

            if(strcmp(entries[i].subtype , "Wants") == 0)
            {
                wants += entries[i].amount;
            }

            
        }

            net = income - expense;

            printf("Total Income: $%.2f\n" , income);
            printf("Total Expenses: $%.2f\n", expense);
            printf("Needs: $%.2f (%.2f%% of expenses, %.2f%% of income)\n" , needs , needs * 100/ expense , needs * 100/income);
            printf("Wants: $%.2f (%.2f%% of expenses, %.2f%% of income)\n" , wants , wants * 100/ expense , wants * 100/income);
            printf("Net Balance: $%.2f\n", net);
        
    }

    void add_entry()
    {
        if(count >= capacity)           // Reallocate memory if needed
            {
                capacity = capacity * 2;
                entries = realloc(entries, sizeof(Entry)* capacity);
            }

        Entry newEntry;

        newEntry.id = entries[count-1].id + 1;         // Id is incremented

        char today[2];

        printf("Use today's date? (y/n): ");
        scanf(" %1c" , today);

        if(today[0] == 'y')                 //Use current date if yes
        {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            sprintf(newEntry.date, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        }

        else
        {
            printf("Enter date (YYYY-MM-DD): ");        // Entering a date manually.
            scanf("%s" , newEntry.date);
        }

        printf("Type (income/expense): ");              // Entering the type of entry.
        scanf("%s" , newEntry.type);

        printf("Category: ");                           // Entering the category of the entry.
        scanf("%s" , newEntry.subtype);

        printf("Description: ");                        // Entering the description of the entry.
        scanf("%s" , newEntry.description);

        printf("Amount: $");                            // Entering the amount of the entry (in dollars).
        scanf("%lf" , &newEntry.amount);

        entries[count++] = newEntry;

        undo_entry = malloc(sizeof(Entry));
        *undo_entry = newEntry;
        printf("Entry added successfully with ID: %d\n\n", newEntry.id);
    }

    void modify()
    {
        int id;

        printf("Enter ID of entry to modify: ");
        scanf("%d" , &id);

        for(int i = 0 ; i <= count ; i++)
        {
            if(entries[i].id == id)             // Check if the entry exists and match one of the entry.
            {
                int choice;

                // Display details of the entry found.

                printf("\nCurrent Details:");
                printf("ID: %d\n" , id);
                
                printf("Date: %s\n" , entries[i].date);
                printf("Type: %s\n" , entries[i].type);
                printf("Category: %s\n" , entries[i].subtype);
                printf("Description: %s\n" , entries[i].description);
                printf("Amount: $%.2f\n" , entries[i].amount);

                printf("\nWhat would you like to modify?\n");
                printf("1.Date\n2.Amount\nChoice: ");

                scanf("%d" , &choice);

                if(choice == 1)             // Choice 1 to modify entry.
                {
                    printf("Enter new date (YYYY-MM-DD): ");

                    scanf("%s" , entries[i].date);
                }

                if(choice == 2)             // Choice 2 to modify the amount.
                {
                    double newAmount;
                    printf("Enter new amount: $");

                    scanf("%lf" , &newAmount);

                    if(newAmount < 0)      // Check if the amount is not negative.
                    {
                        printf("Invalid negative amount\n"); 
                        return;
                    }

                    undo_entry = malloc(sizeof(Entry));
                    *undo_entry = entries[i];
                    entries[i].amount = newAmount;
                }  

                printf("Entry updated successfully.\n\n");
                return;
            }
        }

        printf("Entry not found\n\n");
    }

    void free_entries()
    {
        free(entries);
    }


    void undo_last_action() {
    if (!undo_entry)
    {
        printf("Nothing to undo.\n");
         return;
    }

    for (int i = 0; i < count; i++) {
        if (entries[i].id == undo_entry->id) 
        {
            entries[i] = *undo_entry;
            printf("Undo completed.\n");
            free(undo_entry); 
            undo_entry = NULL;
            return;
        }
    }
    count--;
    printf("Undo add completed.\n");
    free(undo_entry); 
    undo_entry = NULL;
}
