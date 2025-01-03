#include "Customer.h"
#include "Product.h"
#include <iostream>
#include <fstream>
using namespace std;

Customer::Customer(string phone, string name)
    : Phone(phone), Name(name), purchasedProducts(nullptr), productCount(0) {}
Customer::Customer(const Customer& other)
    : Phone(other.Phone), Name(other.Name), productCount(other.productCount) {
    purchasedProducts = new Product[productCount];
    for (size_t i = 0; i < productCount; ++i) {
        purchasedProducts[i] = other.purchasedProducts[i];
    }
}

Customer::~Customer() {
    
}
int Customer::getCount()const{
	return productCount;
}

Product* Customer::getProduct()const{
	return purchasedProducts;
}
void Customer::addProduct(const Product& product) {
    Product* temp = new Product[productCount + 1]; 
    for (size_t i = 0; i < productCount; ++i) {
        temp[i] = purchasedProducts[i];
    }
    temp[productCount] = product; 
    delete[] purchasedProducts;   
    purchasedProducts = temp;
    ++productCount;
}

void Customer::Showproducts() const {
    if (productCount == 0) {
        cout << "No products available." << endl;
        return;
    }
    for (size_t i = 0; i < productCount; ++i) {
        purchasedProducts[i].display();
    }
}
string Customer::getPhone() const {
    return Phone;
}

string Customer::getName() const {
    return Name;
}

void Customer::display() const {
    cout << "\033[1;34mName: " << Name << ", Phone: " << Phone << "\033[0m" << endl;
    Showproducts();
}

void Customer::writeToFile(ofstream& outfile) const {
    outfile << Phone << endl;
    outfile << Name << endl;
    outfile << productCount << endl;
    for (int i = 0; i < productCount; ++i) {
        purchasedProducts[i].writeToFile(outfile);
    }
}

void Customer::readFromFile(ifstream& infile) {
    getline(infile, Phone);
    getline(infile, Name);
    infile >> productCount;
    infile.ignore();
    delete[] purchasedProducts;              
    purchasedProducts = new Product[productCount]; 
    for (size_t i = 0; i < productCount; ++i) {
        purchasedProducts[i].readFromFile(infile);
    }
}
