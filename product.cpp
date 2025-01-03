#include "Product.h"
#include <iostream>
#include <iomanip> 
Product::Product(string name, string id, string brand, string color, float price, int size, int quantity)
    : Name(name), ID(id), Brand(brand), Color(color), Price(price), Size(size), Quantity(quantity) {}

Product::Product(const Product &other) 
    : Name(other.Name), ID(other.ID), Brand(other.Brand),  Color(other.Color), Price(other.Price), Size(other.Size), Quantity(other.Quantity) {}

Product::~Product() {}
void Product::writeToFile(ofstream &outfile) const{
    outfile << Name << "," << ID << "," << Brand <<  "," << Color << "," << Price << "," << Size <<"," << Quantity << endl;
}

void Product::readFromFile(ifstream &infile) {
    getline(infile, Name, ',');
    getline(infile, ID, ',');
    getline(infile, Brand, ',');
    getline(infile, Color, ',');
    infile >> Price;
    infile.ignore(1); 
    infile >> Size;
    infile.ignore(1); 
    infile >> Quantity;
    infile.ignore(1); 
}
string Product::getName() const {
    return this->Name;
}

string Product::getID() const {
    return this->ID;
}
string Product::getBrand() const {
    return this->Brand;
}
string Product::getColor() const {
    return this->Color;
}
float Product::getPrice() const {
    return this->Price;
}
float Product::getSize() const {
    return this->Size;
}

int Product::getQuantity() const {
    return this->Quantity;
}

void Product::setName(const string& name) {
    this->Name = name;
}

void Product::setID(const string& id) {
    this->ID = id;
}

void Product::setPrice(float price) {
    this->Price = price;
}

void Product::setQuantity(int quantity) {
    this->Quantity = quantity;
}

void Product::increaseQuantity(int amount) {
    this->Quantity += amount;
}

void Product::display() const {
 	  cout << "\033[34m- Product: \033[0m" << std::setw(15) << std::left << Name
     << "\033[34m ID: \033[0m" << std::setw(6) << ID
     << "\033[34m Color: \033[0m" << std::setw(8) << Color
     << "\033[34m Price: \033[0m" << std::setw(8) << Price
     << "\033[34m Quantity: \033[0m" << std::setw(6) << Quantity << std::endl;
}
