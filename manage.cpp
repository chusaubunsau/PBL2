#include "Manage.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <string>
#include<vector>
#define MAX 100000



Manage::Manage() : p(nullptr), count(0) {}

Manage::~Manage() {
    delete[] p;
}

void Manage::checkFloat(float &input) {
    const float MAX_VALUE = 1000000000; 

    while (true) {
        cin >> input;

        // Ki?m tra l?i nh?p li?u
        if (cin.fail()) {
            cin.clear(); // Xóa tr?ng thái l?i
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid float number." << endl;
        } else {
            if (input < 0) { // Ki?m tra giá tr? âm
                cout << "Negative values are not allowed. Please try again." << endl;
            } else if (input > MAX_VALUE) { 
                cout << "The value exceeds the maximum allowed (1,000,000,000). Please try again." << endl;
            } else {
                break; 
            }
        }
    }

    
    cout << fixed << setprecision(2); 
}
void Manage::checkInt(int &input) {
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid credentials. Try again." << endl;
        } else if (input <= 0 || input > MAX) {
            cout << "Too big or invalid. Try again." << endl;
        } else {
            break;
        }
    }
}

void Manage::readFromFile(const string& nameFile) {
    ifstream infile(nameFile);
    if (!infile) {
        cerr << "Error: Could not open file " << nameFile << ".\n";
        return;
    }
    infile >> count;  
    infile.ignore(numeric_limits<streamsize>::max(), '\n'); 
    delete[] p;
    p = new Product[count];

    for (int i = 0; i < count; ++i) {
        p[i].readFromFile(infile);  
    }

    infile.close();
    cout << "Loaded " << count << " products from file.\n";
}

void Manage::writeToFile(const string&nameFile) {
	ofstream outfile(nameFile);
        if (!outfile) {
            cerr << "Open file error.\n";
            return;
        }
        outfile << count << "\n"; 
        for (int i = 0; i < count; ++i) {
      p[i].writeToFile(outfile) ;
        }
        outfile.close();
}
int Manage::Add(const Product& product) {
    int idx = indexOf(product.getID());
    int inoA = indexOfAdvanced(product);
    if (inoA != -1) {
        p[idx].increaseQuantity(product.getQuantity());
        cout << "Product already exists. Increased quantity to " << p[idx].getQuantity() << ".\n";
        return 0;
    } else if(idx != -1 ){
    	cout << "Same Id.Try again." <<endl;
		return 1; 
    }else{
        Product* newProducts = new Product[count + 1];
        for (int i = 0; i < count; ++i) {
            newProducts[i] = p[i];
        }
        newProducts[count] = product;
        delete[] p;
        p = newProducts;
        ++count;
        writeToFile("products.txt");
        return 0;
    }
}

int Manage::Remove(const string& id) {
    int idx = indexOf(id);
    if (idx != -1) {
        Product* newProducts = new Product[count - 1];
        for (int i = 0, j = 0; i < count; ++i) {
            if (i != idx) {
                newProducts[j++] = p[i];
            }
        }
        delete[] p;
        p = newProducts;
        --count;
        cout << "Product removed.\n";
        return 1;
    } else {
        cout << "Product with ID " << id << " not found.\n";
         return 0;
    }
   
}

int Manage::indexOf(const string& id) {
    for (int i = 0; i < count; ++i) {
        if (p[i].getID() == id) {
            return i;
        }
    }
    return -1;
}
int Manage::indexOfAdvanced(const Product& product) {
    for (int i = 0; i < count; ++i) {
        if (p[i].getID() == product.getID() && 
            p[i].getBrand() == product.getBrand() && 
            p[i].getName() == product.getName() && 
            p[i].getColor() == product.getColor() && 
            p[i].getPrice() == product.getPrice()) {
            return i; 
        }
    }
    return -1; 
}
void Manage::show()const{
//	cout<<count<<endl;
    drawProductTable();
}
void Manage::drawProductTable() const {
    char top_left = 201, top_right = 187, bottom_left = 200, bottom_right = 188;
    char horizontal = 205, vertical = 186, cross = 206;
    char left_t = 204, right_t = 185, top_t = 203, bottom_t = 202;
    string dark_blue = "\033[0;34m"; 
    string pink = "\033[1;35m";    
    string reset = "\033[0m";
    
    // Modified column widths (reduced the width of Size and Quantity)
    int col_widths[] = {20, 12, 15, 15, 10, 10};  // Size and Quantity are now 10
    int table_width = col_widths[0] + col_widths[1] + col_widths[2] + col_widths[3] + col_widths[4] + col_widths[5] + 6;
    int console_width = 100; 
    int padding_left = (console_width - table_width) / 2;
    string padding(padding_left, ' ');

    // Draw table header
    cout << padding << dark_blue << top_left;
    for (int i = 0; i < col_widths[0]; i++) cout << horizontal;
    cout << top_t;
    for (int i = 0; i < col_widths[1]; i++) cout << horizontal;
    cout << top_t;
    for (int i = 0; i < col_widths[2]; i++) cout << horizontal;
    cout << top_t;
    for (int i = 0; i < col_widths[3]; i++) cout << horizontal;
    cout << top_t;
    for (int i = 0; i < col_widths[4]; i++) cout << horizontal;
    cout << top_t;
    for (int i = 0; i < col_widths[5]; i++) cout << horizontal;
    cout << top_right << reset << endl;

    // Print column headers
    cout << padding << dark_blue << vertical << reset 
         << pink << setw(col_widths[0]) << left << "Product"
         << dark_blue << vertical << reset 
         << pink << setw(col_widths[1]) << left << "ID"
         << dark_blue << vertical << reset 
         << pink << setw(col_widths[2]) << left << "Color"
         << dark_blue << vertical << reset 
         << pink << setw(col_widths[3]) << left << "Price"
         << dark_blue << vertical << reset 
         << pink << setw(col_widths[4]) << left << "Size"
         << dark_blue << vertical << reset 
         << pink << setw(col_widths[5]) << left << "Quantity"
         << dark_blue << vertical << reset 
         << endl;

    // Draw separator row
    cout << padding << dark_blue << left_t;
    for (int i = 0; i < col_widths[0]; i++) cout << horizontal;
    cout << cross;
    for (int i = 0; i < col_widths[1]; i++) cout << horizontal;
    cout << cross;
    for (int i = 0; i < col_widths[2]; i++) cout << horizontal;
    cout << cross;
    for (int i = 0; i < col_widths[3]; i++) cout << horizontal;
    cout << cross;
    for (int i = 0; i < col_widths[4]; i++) cout << horizontal;
    cout << cross;
    for (int i = 0; i < col_widths[5]; i++) cout << horizontal;
    cout << right_t << reset << endl;

    // Assuming 'count' and 'p' are valid in this scope
    vector<Product> products;
    // Populate products vector from the array/list 'p'
    for (int i = 0; i < count; i++) {
        products.push_back(p[i]);  // Add each product to the vector
    }

    // Print each product's information in rows
    for (const auto& product : products) {
        cout << padding << dark_blue << vertical << reset 
             << setw(col_widths[0]) << left << product.getName()
             << dark_blue << vertical << reset 
             << setw(col_widths[1]) << left << product.getID()
             << dark_blue << vertical << reset 
             << setw(col_widths[2]) << left << product.getColor()
             << dark_blue << vertical << reset 
             << setw(col_widths[3]) << right << product.getPrice()
             << dark_blue << vertical << reset 
             << setw(col_widths[4]) << right << product.getSize()
             << dark_blue << vertical << reset 
             << setw(col_widths[5]) << right << product.getQuantity()
             << dark_blue << vertical << reset << endl;
    }

    // Draw footer row
    cout << padding << dark_blue << bottom_left;
    for (int i = 0; i < col_widths[0]; i++) cout << horizontal;
    cout << bottom_t;
    for (int i = 0; i < col_widths[1]; i++) cout << horizontal;
    cout << bottom_t;
    for (int i = 0; i < col_widths[2]; i++) cout << horizontal;
    cout << bottom_t;
    for (int i = 0; i < col_widths[3]; i++) cout << horizontal;
    cout << bottom_t;
    for (int i = 0; i < col_widths[4]; i++) cout << horizontal;
    cout << bottom_t;
    for (int i = 0; i < col_widths[5]; i++) cout << horizontal;
    cout << bottom_right << reset << endl;
}




void Manage::sort() {
    for (int i = 0; i < this->count - 1; i++) {
        for (int j = 0; j < this->count - i - 1; j++) {
            if (p[j].getPrice() > p[j + 1].getPrice()) {
                Product temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}


void Manage::Update(const string& id) {
    int idx = indexOf(id);
    string name, brand,color;
    float price;
    int size,quantity;
    if (idx == -1) {
    	cout << "Product with ID " << id << " not found.\n"; 
    } else {
    	cout << "Enter new product details:\n";
                cout << "Name: "; getline(cin,name);
                cout << "Brand: ";getline(cin,brand);
                cout << "Color: ";getline(cin,color);
                cout << "Price: "; this->checkFloat(price);
                cout << "Size: ";  this->checkInt(size);
                cout << "Quantity: ";  this->checkInt(quantity);
            Product updatedProduct(name, id, brand,color, price, size,quantity);
         p[idx] = updatedProduct;
    }
}

Product* Manage::searchByID(const string& id) {
    int idx = indexOf(id);
    if (idx != -1) {
        return &p[idx];
    }
    return nullptr;
}
