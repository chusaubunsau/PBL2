#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Product.h"
#include <string>
#include <fstream>
using namespace std;

class Customer {
private:
    string Phone;
    string Name;
    Product* purchasedProducts; 
    int productCount;       
public:
    Customer(string phone = "", string name = "");
    Customer(const Customer& other);
    ~Customer();
    string getPhone() const;
    string getName() const;
	int getCount()const;
	Product* getProduct()const;
    void display() const;
    void Showproducts() const;
    void addProduct(const Product& product);

    void writeToFile(ofstream& outfile) const;
    void readFromFile(ifstream& infile);
};
#endif