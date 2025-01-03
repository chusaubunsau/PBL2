#ifndef PRODUCT_H
#define PRODUCT_H
#include <fstream>
#include <string>
using namespace std;

class Product {
private:
    string Name;
    string ID;
    string Brand;
    string Color;
    float Price;
    float Size;
    int Quantity; 

public:
    Product(string name = "", string id = "", string brand = "", string color = "", float price = 0.0, int size = 0, int quantity = 1);
    Product(const Product &other);
    ~Product();	
    string getName() const;
    string getID() const;
    string getBrand() const;
    string getColor() const;
    float getPrice() const;
    float getSize()const;
    int getQuantity() const;
    void setName(const string& name);
    void setID(const string& id);
    void setPrice(float price);
    void setQuantity(int quantity);
    void increaseQuantity(int amount);
    void writeToFile(ofstream &outfile) const;
    void readFromFile(ifstream &infile);
    void display() const;
};

#endif 
