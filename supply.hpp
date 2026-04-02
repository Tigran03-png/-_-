#ifndef SUPPLY_HPP
#define SUPPLY_HPP

#include <iostream>
#include <string>
#include <fstream>

class Supply {
private:
    int id;
    std::string name;
    std::string category;
    int quantity;
    double price;
    std::string manufacturer;

public:
    Supply();
    Supply(int id, std::string name, std::string category, 
           int quantity, double price, std::string manufacturer);
    
    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    int getQuantity() const;
    double getPrice() const;
    
    void setQuantity(int q);
    void setPrice(double p);
    void setName(std::string n);
    void setCategory(std::string c);
    
    friend std::ostream& operator<<(std::ostream& os, const Supply& s);
    friend std::istream& operator>>(std::istream& is, Supply& s);
    
    std::string operator[](int index) const;
    
    bool containsName(const std::string& part) const;
    bool containsCategory(const std::string& part) const;
};

#endif
