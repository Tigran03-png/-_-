#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "supply.hpp"
#include <vector>

class Database {
private:
    std::vector<Supply> items;
    std::string filename;

public:
    Database();
    
    void add(Supply s);
    void remove(int id);
    void edit(int id);
    void showAll();
    
    Supply* findByName(std::string part);
    Supply* findByCategory(std::string part);
    
    void save();
    void load();
    void addSampleData();
    
    int getNextId();
    int getCount();
    
    Supply& operator[](int index);
};

#endif
