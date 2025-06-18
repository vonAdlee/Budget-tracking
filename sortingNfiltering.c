#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entry.h"


void filter_by_month()
{
    int year;
    int month;

    printf("Enter year (YYYY): ");          // User enters year.
    scanf("%d" , &year);

    printf("Enter month (From 1 to 12): "); // User enters month.
    scanf("%d" , &month);

    char date[8];
    sprintf(date, "%d-%02d", year , month);         // Store the year and month as string.

    for(int i = 0 ; i < count ; i++)
    {
        if(strstr(entries[i].date , date) == entries[i].date)           // Check every entry if it matches the month and year.
        {
            printf("%-5d %-12s %-10s %-10s %-15s $%.2f\n",              // Print the entry.
                   entries[i].id, entries[i].date, entries[i].type,
                   entries[i].subtype, entries[i].description, entries[i].amount);
        }
    }
}


// Comparitor for amount.

int compare_amount(const void *a, const void *b) {
    Entry *ea = (Entry *)a;
    Entry *eb = (Entry *)b;
    return (ea->amount > eb->amount) - (ea->amount < eb->amount);
}

void sort_by_amount() {
    qsort(entries, count, sizeof(Entry), compare_amount);
}


// Comparitor for descrption.

int compare_by_description(const void *a, const void *b) {
    const Entry *ea = (const Entry *)a;
    const Entry *eb = (const Entry *)b;
    return strcmp(ea->description, eb->description);
}

void sort_by_description() {
    qsort(entries, count, sizeof(Entry), compare_by_description);
    printf("Entries sorted by description.\n");
}

//Comparitor for id.

int compare_by_id(const void *a, const void *b) {
    const Entry *ea = (const Entry *)a;
    const Entry *eb = (const Entry *)b;
    return ea->id - eb->id;
}

void sort_by_id() {
    qsort(entries, count, sizeof(Entry), compare_by_id);
    printf("Entries sorted by ID.\n");
}

// Comparitor for date.

int compare_by_date(const void *a, const void *b) {
    const Entry *ea = (const Entry *)a;
    const Entry *eb = (const Entry *)b;
    return strcmp(ea->date, eb->date);
}

void sort_by_date() {
    qsort(entries, count, sizeof(Entry), compare_by_date);
    printf("Entries sorted by date.\n");
}