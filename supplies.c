#include "supplies.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Database* create_db() {
    Database* db = malloc(sizeof(Database));
    db->count = 0;
    db->capacity = 10;
    db->items = malloc(db->capacity * sizeof(Supply));
    return db;
}


void free_db(Database* db) {
    free(db->items);
    free(db);
}


void add_sample_data(Database* db) {

    if (db->count > 0) return;
    
    Supply s1 = {1, "Ручка шариковая", "Ручки", 100, 15.50, "Erich Krause"};
    Supply s2 = {2, "Карандаш HB", "Карандаши", 80, 8.00, "Koh-i-Noor"};
    Supply s3 = {3, "Тетрадь 48л", "Тетради", 50, 45.00, "Атлант"};
    Supply s4 = {4, "Линейка 30см", "Линейки", 30, 25.00, "Геодез"};
    Supply s5 = {5, "Ластик", "Ластики", 60, 12.50, "Faber"};
    
    add_item(db, s1);
    add_item(db, s2);
    add_item(db, s3);
    add_item(db, s4);
    add_item(db, s5);
    
    printf("Добавлено 5 тестовых товаров\n");
}


void add_item(Database* db, Supply item) {
    if (db->count >= db->capacity) {
        db->capacity *= 2;
        db->items = realloc(db->items, db->capacity * sizeof(Supply));
    }
    db->items[db->count] = item;
    db->count++;
}


void remove_item(Database* db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->items[i].id == id) {
           
            db->items[i] = db->items[db->count - 1];
            db->count--;
            printf("Удален товар ID: %d\n", id);
            return;
        }
    }
    printf("Товар ID %d не найден\n", id);
}


void show_all(Database* db) {
    if (db->count == 0) {
        printf("Склад пуст\n");
        return;
    }
    
    printf("\nВсе товары (%d шт):\n", db->count);
    for (int i = 0; i < db->count; i++) {
        Supply s = db->items[i];
        printf("%d. %s - %d шт. по %.2f руб. [%s]\n",
               s.id, s.name, s.quantity, s.price, s.category);
    }
}


Supply* find_item(Database* db, char* search, int by_id) {
    if (by_id) {
       
        int search_id = atoi(search);
        for (int i = 0; i < db->count; i++) {
            if (db->items[i].id == search_id) {
                return &db->items[i];
            }
        }
    } else {
       
        for (int i = 0; i < db->count; i++) {
            if (strstr(db->items[i].name, search) != NULL) {
                return &db->items[i];
            }
        }
    }
    return NULL;
}

void save_to_file(Database* db) {
    FILE* file = fopen("supplies.bin", "wb");
    if (!file) return;
    
    fwrite(&db->count, sizeof(int), 1, file);
    fwrite(db->items, sizeof(Supply), db->count, file);
    
    fclose(file);
    printf("Сохранено %d товаров\n", db->count);
}


Database* load_from_file() {
    FILE* file = fopen("supplies.bin", "rb");
    if (!file) {
        
        Database* db = create_db();
        add_sample_data(db);
        return db;
    }
    
    int count;
    fread(&count, sizeof(int), 1, file);
    
    Database* db = create_db();
    
   
    if (count > db->capacity) {
        db->capacity = count;
        db->items = realloc(db->items, db->capacity * sizeof(Supply));
    }
    
   
    fread(db->items, sizeof(Supply), count, file);
    db->count = count;
    
    fclose(file);
    printf("Загружено %d товаров\n", count);
    return db;
}
