#include "database.hpp"
#include <iostream>
#include <fstream>

Database::Database() : filename("data.bin") {
    load();
    if (items.empty()) {
        addSampleData();
    }
}

void Database::add(Supply s) {
    items.push_back(s);
    save();
}

void Database::remove(int id) {
    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i].getId() == id) {
            items.erase(items.begin() + i);
            save();
            std::cout << "Удалено!" << std::endl;
            return;
        }
    }
    std::cout << "Не найдено" << std::endl;
}

void Database::edit(int id) {
    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i].getId() == id) {
            std::cout << "Редактируем: " << items[i] << std::endl;
            std::cin >> items[i];
            save();
            std::cout << "Сохранено!" << std::endl;
            return;
        }
    }
    std::cout << "Не найдено" << std::endl;
}

void Database::showAll() {
    if (items.empty()) {
        std::cout << "Пусто" << std::endl;
        return;
    }
    std::cout << "\n=== Товары (" << items.size() << ") ===" << std::endl;
    for (int i = 0; i < (int)items.size(); i++) {
        std::cout << items[i] << std::endl;
    }
}

Supply* Database::findByName(std::string part) {
    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i].containsName(part)) {
            return &items[i];
        }
    }
    return nullptr;
}

Supply* Database::findByCategory(std::string part) {
    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i].containsCategory(part)) {
            return &items[i];
        }
    }
    return nullptr;
}

void Database::save() {
    std::ofstream f(filename, std::ios::binary);
    if (!f) return;
    
    int size = items.size();
    f.write((char*)&size, sizeof(int));
    
    for (int i = 0; i < size; i++) {
        int id = items[i].getId();
        int qty = items[i].getQuantity();
        double price = items[i].getPrice();
        
        std::string name = items[i].getName();
        std::string cat = items[i].getCategory();
        std::string man = "unknown";
        
        int len;
        
        f.write((char*)&id, sizeof(int));
        
        len = name.size();
        f.write((char*)&len, sizeof(int));
        f.write(name.c_str(), len);
        
        len = cat.size();
        f.write((char*)&len, sizeof(int));
        f.write(cat.c_str(), len);
        
        f.write((char*)&qty, sizeof(int));
        f.write((char*)&price, sizeof(double));
        
        len = man.size();
        f.write((char*)&len, sizeof(int));
        f.write(man.c_str(), len);
    }
    std::cout << "Сохранено " << size << " записей" << std::endl;
}

void Database::load() {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return;
    
    int size;
    f.read((char*)&size, sizeof(int));
    
    items.clear();
    for (int i = 0; i < size; i++) {
        int id, qty;
        double price;
        std::string name, cat, man;
        int len;
        
        f.read((char*)&id, sizeof(int));
        
        f.read((char*)&len, sizeof(int));
        name.resize(len);
        f.read(&name[0], len);
        
        f.read((char*)&len, sizeof(int));
        cat.resize(len);
        f.read(&cat[0], len);
        
        f.read((char*)&qty, sizeof(int));
        f.read((char*)&price, sizeof(double));
        
        f.read((char*)&len, sizeof(int));
        man.resize(len);
        f.read(&man[0], len);
        
        items.push_back(Supply(id, name, cat, qty, price, man));
    }
    std::cout << "Загружено " << size << " записей" << std::endl;
}

void Database::addSampleData() {
    items.push_back(Supply(1, "Ручка", "Ручки", 100, 15.5, "Erich"));
    items.push_back(Supply(2, "Карандаш", "Карандаши", 80, 8, "Koh-i-Noor"));
    items.push_back(Supply(3, "Тетрадь", "Тетради", 50, 45, "Атлант"));
    items.push_back(Supply(4, "Ластик", "Ластики", 60, 12.5, "Faber"));
    save();
    std::cout << "Добавлены тестовые данные" << std::endl;
}

int Database::getNextId() {
    int max = 0;
    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i].getId() > max) max = items[i].getId();
    }
    return max + 1;
}

int Database::getCount() {
    return items.size();
}

Supply& Database::operator[](int index) {
    return items[index];
}
