#include "database.hpp"
#include <iostream>
#include <limits>

void printMenu() {
    std::cout << "\n===== МЕНЮ =====" << std::endl;
    std::cout << "1. Показать все" << std::endl;
    std::cout << "2. Добавить" << std::endl;
    std::cout << "3. Найти по названию" << std::endl;
    std::cout << "4. Найти по категории" << std::endl;
    std::cout << "5. Удалить по ID" << std::endl;
    std::cout << "6. Редактировать по ID" << std::endl;
    std::cout << "7. Тестовые данные" << std::endl;
    std::cout << "8. Выход" << std::endl;
    std::cout << "Выбор: ";
}

int main() {
    Database db;
    int choice;
    
    do {
        printMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка!" << std::endl;
            continue;
        }
        
        switch(choice) {
            case 1:
                db.showAll();
                break;
                
            case 2: {
                Supply s;
                std::cin >> s;
                db.add(Supply(db.getNextId(), s.getName(), s.getCategory(),
                              s.getQuantity(), s.getPrice(), "unknown"));
                std::cout << "Добавлено!" << std::endl;
                break;
            }
                
            case 3: {
                std::cin.ignore();
                std::string search;
                std::cout << "Название (часть): ";
                std::getline(std::cin, search);
                Supply* found = db.findByName(search);
                if (found) std::cout << "Найдено: " << *found << std::endl;
                else std::cout << "Не найдено" << std::endl;
                break;
            }
                
            case 4: {
                std::cin.ignore();
                std::string search;
                std::cout << "Категория (часть): ";
                std::getline(std::cin, search);
                Supply* found = db.findByCategory(search);
                if (found) std::cout << "Найдено: " << *found << std::endl;
                else std::cout << "Не найдено" << std::endl;
                break;
            }
                
            case 5: {
                int id;
                std::cout << "ID: ";
                std::cin >> id;
                db.remove(id);
                break;
            }
                
            case 6: {
                int id;
                std::cout << "ID: ";
                std::cin >> id;
                db.edit(id);
                break;
            }
                
            case 7:
                db.addSampleData();
                break;
                
            case 8:
                std::cout << "До свидания!" << std::endl;
                break;
                
            default:
                std::cout << "Неверный выбор" << std::endl;
        }
    } while (choice != 8);
    
    return 0;
}
