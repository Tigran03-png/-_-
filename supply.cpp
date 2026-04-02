#include "supply.hpp"
#include <iomanip>

Supply::Supply() : id(0), quantity(0), price(0) {}

Supply::Supply(int id, std::string name, std::string category,
               int quantity, double price, std::string manufacturer)
    : id(id), name(name), category(category), quantity(quantity), 
      price(price), manufacturer(manufacturer) {}

int Supply::getId() const { return id; }
std::string Supply::getName() const { return name; }
std::string Supply::getCategory() const { return category; }
int Supply::getQuantity() const { return quantity; }
double Supply::getPrice() const { return price; }

void Supply::setQuantity(int q) { quantity = q; }
void Supply::setPrice(double p) { price = p; }
void Supply::setName(std::string n) { name = n; }
void Supply::setCategory(std::string c) { category = c; }

std::ostream& operator<<(std::ostream& os, const Supply& s) {
    os << "ID:" << s.id << " | " << s.name 
       << " | " << s.category << " | " << s.quantity 
       << "шт | " << std::fixed << std::setprecision(2) << s.price << "руб";
    return os;
}

std::istream& operator>>(std::istream& is, Supply& s) {
    std::cout << "Название: ";
    is.ignore();
    std::getline(is, s.name);
    std::cout << "Категория: ";
    std::getline(is, s.category);
    std::cout << "Количество: ";
    is >> s.quantity;
    std::cout << "Цена: ";
    is >> s.price;
    std::cout << "Производитель: ";
    is.ignore();
    std::getline(is, s.manufacturer);
    return is;
}

std::string Supply::operator[](int index) const {
    switch(index) {
        case 0: return std::to_string(id);
        case 1: return name;
        case 2: return category;
        case 3: return std::to_string(quantity);
        case 4: return std::to_string(price);
        default: return "";
    }
}

bool Supply::containsName(const std::string& part) const {
    return name.find(part) != std::string::npos;
}

bool Supply::containsCategory(const std::string& part) const {
    return category.find(part) != std::string::npos;
}
