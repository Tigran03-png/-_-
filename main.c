#include "supplies.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu() {
    printf("\n=== СКЛАД КАНЦТОВАРОВ ===\n");
    printf("1. Показать все\n");
    printf("2. Добавить\n");
    printf("3. Найти по названию\n");
    printf("4. Найти по ID\n");
    printf("5. Удалить\n");
    printf("6. Редактировать\n");
    printf("7. Тестовые данные\n");
    printf("8. Выход\n");
    printf("Выбор: ");
}

Supply input_supply(int id) {
    Supply s;
    s.id = id;
    
    printf("Название: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    
    printf("Категория: ");
    fgets(s.category, MAX_CATEGORY, stdin);
    s.category[strcspn(s.category, "\n")] = 0;
    
    printf("Количество: ");
    scanf("%d", &s.quantity);
    
    printf("Цена: ");
    scanf("%f", &s.price);
    
    while (getchar() != '\n');
    
    printf("Производитель: ");
    fgets(s.manufacturer, MAX_MANUFACTURER, stdin);
    s.manufacturer[strcspn(s.manufacturer, "\n")] = 0;
    
    return s;
}

void edit_supply(Supply* s) {
    char input[100];
    
    printf("Название [%s]: ", s->name);
    fgets(input, 100, stdin);
    if (input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(s->name, input);
    }
    
    printf("Категория [%s]: ", s->category);
    fgets(input, 100, stdin);
    if (input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        strcpy(s->category, input);
    }
    
    printf("Количество [%d]: ", s->quantity);
    fgets(input, 100, stdin);
    if (input[0] != '\n') {
        s->quantity = atoi(input);
    }
    
    printf("Цена [%.2f]: ", s->price);
    fgets(input, 100, stdin);
    if (input[0] != '\n') {
        s->price = atof(input);
    }
}

int get_next_id(Database* db) {
    int max = 0;
    for (int i = 0; i < db->count; i++) {
        if (db->items[i].id > max) {
            max = db->items[i].id;
        }
    }
    return max + 1;
}

int main() {
    Database* db = load_from_file();
    int choice;
    char search[100];
    
    do {
        menu();
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                show_all(db);
                break;
                
            case 2: {
                int id = get_next_id(db);
                Supply s = input_supply(id);
                add_item(db, s);
                printf("Добавлено!\n");
                break;
            }
                
            case 3:
                printf("Название: ");
                fgets(search, 100, stdin);
                search[strcspn(search, "\n")] = 0;
                
                Supply* found = find_item(db, search, 0);
                if (found) {
                    printf("ID: %d | %s | %d шт. | %.2f руб.\n",
                           found->id, found->name, found->quantity, found->price);
                } else {
                    printf("Не найдено\n");
                }
                break;
                
            case 4:
                printf("ID: ");
                fgets(search, 100, stdin);
                search[strcspn(search, "\n")] = 0;
                
                found = find_item(db, search, 1);
                if (found) {
                    printf("%s | %s | %d шт.\n",
                           found->name, found->category, found->quantity);
                } else {
                    printf("Не найдено\n");
                }
                break;
                
            case 5:
                {
                    int id;
                    printf("ID для удаления: ");
                    scanf("%d", &id);
                    while (getchar() != '\n');
                    remove_item(db, id);
                }
                break;
                
            case 6:
                {
                    int id;
                    printf("ID для редактирования: ");
                    scanf("%d", &id);
                    while (getchar() != '\n');
                    
                    char temp[20];
                    sprintf(temp, "%d", id);
                    Supply* found = find_item(db, temp, 1);
                    
                    if (found) {
                        edit_supply(found);
                        printf("Изменено!\n");
                    } else {
                        printf("Не найдено\n");
                    }
                }
                break;
                
            case 7:
                add_sample_data(db);
                break;
                
            case 8:
                save_to_file(db);
                printf("Выход\n");
                break;
                
            default:
                printf("Ошибка\n");
        }
    } while (choice != 8);
    
    free_db(db);
    return 0;
}
