#ifndef SUPPLIES_H
#define SUPPLIES_H

#define MAX_NAME 50
#define MAX_CATEGORY 30
#define MAX_MANUFACTURER 40


typedef struct {
    int id;
    char name[MAX_NAME];
    char category[MAX_CATEGORY];
    int quantity;
    float price;
    char manufacturer[MAX_MANUFACTURER];
} Supply;


typedef struct {
    Supply* items;
    int count;
    int capacity;
} Database;


Database* create_db();
void free_db(Database* db);
void add_item(Database* db, Supply item);
void remove_item(Database* db, int id);
void show_all(Database* db);
void save_to_file(Database* db);
Database* load_from_file();
Supply* find_item(Database* db, char* name, int by_id);
void add_sample_data(Database* db); 

#endif
