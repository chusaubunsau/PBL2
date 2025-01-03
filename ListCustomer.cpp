#include "ListCustomer.h"
#include "Customer.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <string>
#include<vector>
#include <stdexcept>
using namespace std;

ListCustomer::ListCustomer() : customers(nullptr), customerCount(0) {}

ListCustomer::~ListCustomer() {
   
}
int ListCustomer::getCount(){
	return customerCount;
}
Customer* ListCustomer::getCus(){
	return customers;
}
void ListCustomer::AddOrUpdateCustomer(const Customer& customer, const Product& product) {
    int index = indexOf(customer.getPhone(), customer.getName());
    if (index != -1) {
        customers[index].addProduct(product);
        cout << "Product added to existing customer." << endl;
    } else {
        Customer* temp = new Customer[customerCount + 1];
        for (size_t i = 0; i < customerCount; ++i) {
            temp[i] = customers[i];
        }
        temp[customerCount] = customer;
        delete[] customers; 
        customers = temp;
        ++customerCount;

        cout << "New customer added with product." << endl;
    }
    writeToFile("customers.txt");
}

void ListCustomer::Remove(const Customer& customer) {
    int index = indexOf(customer.getPhone(), customer.getName());
    if (index == -1) {
        cout << "Customer not found!" << endl;
        return;
    }

    Customer* temp = new Customer[customerCount - 1];
    for (size_t i = 0, j = 0; i < customerCount; ++i) {
        if (i != index) {
            temp[j++] = customers[i];
        }
    }
    delete[] customers; 
    customers = temp;
    --customerCount;
    cout << "Customer removed!" << endl;
}

void ListCustomer::Show() const {
    if (customerCount == 0) {
        cout << "No customers to display.\n";
        return;
    }
    /*for (int i = 0; i < customerCount; ++i) {
        customers[i].display();
    }*/
    drawCustomersTable();
}
void ListCustomer::drawCustomersTable() const {
    if (customerCount == 0) {
        cout << "No customers to display.\n";
        return;
    }

    // Characters for drawing table
    char top_left = 201, top_right = 187, bottom_left = 200, bottom_right = 188;
    char horizontal = 205, vertical = 186, cross = 206;
    char left_t = 204, right_t = 185, top_t = 203, bottom_t = 202;

    // Colors
    string blue = "\033[1;34m";
    string reset = "\033[0m";

    int col_widths[] = {20, 15, 25, 10, 10, 15, 12, 15};  // Updated Total column width
    int total_width = 0;
    for (int i = 0; i < 8; ++i) total_width += col_widths[i];
    total_width += 9; // Add space for vertical separators

    // Helper function to draw a line
    auto draw_line = [&](char left, char middle, char right) {
        cout << blue << left;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < col_widths[i]; ++j) cout << horizontal;
            cout << (i < 7 ? middle : right);
        }
        cout << reset << endl;
    };

    // Draw top line
    draw_line(top_left, top_t, top_right);

    // Print header row
    cout << blue << vertical << reset
         << setw(col_widths[0]) << left << "Customer Name" << blue << vertical << reset
         << setw(col_widths[1]) << left << "Phone" << blue << vertical << reset
         << setw(col_widths[2]) << left << "Product Name" << blue << vertical << reset
         << setw(col_widths[3]) << left << "ID" << blue << vertical << reset
         << setw(col_widths[4]) << left << "Color" << blue << vertical << reset
         << setw(col_widths[5]) << right << "Price" << blue << vertical << reset
         << setw(col_widths[6]) << right << "Quantity" << blue << vertical << reset
         << setw(col_widths[7]) << right << "Total" << blue << vertical << reset << endl;

    // Draw separator row for header
    draw_line(left_t, cross, right_t);

    // Print customer and product data
    for (int i = 0; i < customerCount; ++i) {
        bool isFirstProduct = true; // Flag to print customer info only once
        const Customer& customer = customers[i];

        for (size_t j = 0; j < customer.getCount(); ++j) {
            const Product& product = customer.getProduct()[j];

            cout << blue << vertical << reset;
            if (isFirstProduct) {
                // Print customer name and phone for the first product
                cout << setw(col_widths[0]) << left << customer.getName() << blue << vertical << reset;
                cout << setw(col_widths[1]) << left << customer.getPhone()<< blue << vertical << reset;
                isFirstProduct = false;
            } else {
                // For subsequent products, leave customer name and phone blank
                cout << setw(col_widths[0]) << " " << blue << vertical << reset;
                cout << setw(col_widths[1]) << " " << blue << vertical;
            }

            // Print product details
            cout << setw(col_widths[2]) << left << product.getName() << blue << vertical << reset;
            cout << setw(col_widths[3]) << left << product.getID() << blue << vertical << reset;
            cout << setw(col_widths[4]) << left << product.getColor() << blue << vertical << reset;
            cout << setw(col_widths[5]) << right << product.getPrice() << blue << vertical << reset;
            cout << setw(col_widths[6]) << right << product.getQuantity() << blue << vertical << reset;
            cout << setw(col_widths[7]) << right << fixed << setprecision(2)
                 << product.getPrice() * product.getQuantity() << blue << vertical << reset << endl;
        }

        // If the customer has no products, display a message
        if (customer.getCount() == 0) {
            cout << blue << vertical << reset
                 << setw(col_widths[0]) << left << customer.getName() << blue << vertical << reset
                 << setw(col_widths[1]) << left << customer.getPhone() << blue << vertical << reset;

            // Calculate remaining width for the message
            int remaining_width = total_width - col_widths[0] - col_widths[1] - 2; // Subtract name and phone column widths
            cout << setw(remaining_width) << left << "No products available"
                 << blue << vertical << reset << endl;
        }
    }

    // Draw bottom line
    draw_line(bottom_left, bottom_t, bottom_right);
}


int ListCustomer::indexOf(const string& phone, const string& name) const {
    for (size_t i = 0; i < customerCount; ++i) {
        if (customers[i].getPhone() == phone && customers[i].getName() == name) {
            return i;
        }
    }
    return -1;
}

void ListCustomer::writeToFile(const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }

    outfile << customerCount << endl;
    for (size_t i = 0; i < customerCount; ++i) {
        customers[i].writeToFile(outfile);
    }
    outfile.close();
}

void ListCustomer::readFromFile(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cout << "Error opening file for reading: " << filename << endl;
        return;
    }

    infile >> customerCount;
    infile.ignore();
    delete[] customers;                  
    customers = new Customer[customerCount]; 
    for (size_t i = 0; i < customerCount; ++i) {
        customers[i].readFromFile(infile);
    }

    infile.close();
}
Customer& ListCustomer:: getCustomer(int index) {
        if (index >= 0 && index < customerCount) {
            return customers[index];
        }
        throw out_of_range("Customer index out of range");
    }
