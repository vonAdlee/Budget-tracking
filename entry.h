#ifndef ENTRY_H
#define ENTRY_H

// Define a entry struct.
#define LENGTH 51

    typedef struct 
    {
        int id;
        char date[LENGTH];
        char type[LENGTH];
        char subtype[LENGTH];
        char description[LENGTH];
        double amount;
    }Entry;

extern Entry *entries;
extern int count;
extern int capacity;

void read_file(const char *filename);
void distribution();
void add_entry();
void modify();
void free_entries();
void undo_last_action();

#endif