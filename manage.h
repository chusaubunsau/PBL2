#ifndef MANAGE_H
#define MANAGE_H

#include "Product.h"

class Manage {
private:
    Product *p;
    int count;
public:
    Manage();
    ~Manage();
    int Add(const Product& product);
    int Remove(const string& id);
    int indexOf(const string& id);
    int indexOfAdvanced(const Product& product);
    void show()const;
    void drawProductTable()const; 
    void sort();
    void Update(const string& id);
    void readFromFile(const string&nameFile);
    void writeToFile(const string&nameFile);
    void checkFloat(float&);
    void checkInt(int&);
    Product* searchByID(const string& id); 
};

#endif 

