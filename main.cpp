#include <iostream>
#include <limits>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "Product.h"
#include "Manage.h"
#include "Customer.h"
#include "Account.h"
#include "Staff.h"
#include "Admin.h"
#include "ListCustomer.h"
#include<iomanip>
#define MAX 100000

using namespace std;

void checkFloat(float &input) {
    const float MAX_VALUE = 1000000000;

    while (true) {
        cin >> input;

        
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid float number." << endl;
        } else {
            if (input < 0) { 
                cout << "Negative values are not allowed. Please try again." << endl;
            } else if (input > MAX_VALUE) { // Ki?m tra giá tr? l?n hon gi?i h?n
                cout << "The value exceeds the maximum allowed (1,000,000,000). Please try again." << endl;
            } else {
                break; 
            }
        }
    }

    
    cout << fixed << setprecision(2); 
}
void checkInt(int &input) {
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer." << endl;
        } else {
            if (input < 0 || input > MAX) {
                cout << "Too big or invalid. Try again." << endl;
            } else {
                break;
            }
        }
    }
}
string getValidatedInput(const string& prompt,int n) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);

        if (input.length() > n) {
            cout << "Error: Input cannot exceed " << n << " characters. Please try again.\n";
        } else if (input.empty()) {
            cout << "Error: Input cannot be empty. Please try again.\n";
        }
    } while (input.length() > n || input.empty());

    return input;
}
void setMousePosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawLoginBox() {
    char top_left = 201, top_right = 187, bottom_left = 200, bottom_right = 188;
    char horizontal = 205, vertical = 186;
    int console_width = 80;
    int box_width = 35;
    int padding_left = (console_width - box_width) / 2;

    string padding(padding_left, ' ');

    cout << padding << top_left;
    for (int i = 0; i < 20; i++) cout << horizontal;
    cout << top_right << endl;

    cout << padding << vertical << "                    " << vertical << endl;
    cout << padding << vertical << " Username:          " << vertical << endl;
    cout << padding << vertical << " Password:          " << vertical << endl;
    cout << padding << vertical << "                    " << vertical << endl;

    cout << padding << bottom_left;
    for (int i = 0; i < 20; i++) cout << horizontal;
    cout << bottom_right << endl;
}

Account* login(vector<Account>& accounts) {
    string username, password, masked_password;
    int cursorY = 0;

    int username_position_x = 33, username_position_y = 2;
    int password_position_x = 33, password_position_y = 3;

    while (true) {
        system("cls");
        drawLoginBox();
        setMousePosition(username_position_x, username_position_y);
        cout << username;
        setMousePosition(password_position_x, password_position_y);
        cout << masked_password;

        if (cursorY == 0) {
            setMousePosition(username_position_x + username.size(), username_position_y);
        } else {
            setMousePosition(password_position_x + masked_password.size(), password_position_y);
        }

        char ch = _getch();

        if (ch == 13 || ch == 80) { 
            if (cursorY == 0) {
                cursorY++;
            } else {
                for (auto& account : accounts) {
                    if (account.getUsername() == username && account.getPassword() == password) {
                        cout<< endl<<endl<<endl;
						cout << "Welcome " << username << "!\n";
                        return &account;
                    }
                }
                system("cls");
                cout << "Invalid credentials. Try again.\n";
                _getch();
                username.clear();
                password.clear();
                masked_password.clear();
                cursorY = 0;
            }
        } else if (ch == 72) {
            if (cursorY > 0) cursorY--;
        } else if (ch == 8) {
            if (cursorY == 0 && !username.empty()) {
                username.pop_back();
            } else if (cursorY == 1 && !password.empty()) {
                password.pop_back();
                masked_password.pop_back();
            }
        } else {
            if (cursorY == 0) {
                username += ch;
            } else if (cursorY == 1) {
                password += ch;
                masked_password += '*';
            }
        }
    }
}
void displayMenu(int current_choice, const string& Role) {
    char top_left = 201, top_right = 187;
    char bottom_left = 200, bottom_right = 188;
    char horizontal = 205, vertical = 186;

    string red = "\033[1;31m";
    string reset = "\033[0m";

    int console_width = 80;
    int box_width = 50;
    int padding_left = (console_width - box_width) / 2;

    vector<string> menu_items = {
        "  1. Add Product",
        "  2. Remove Product",
        "  3. Show Product List",
        "  4. Sort Products by Price",
        "  5. Search Product by ID",
        "  6. Update Product",
        "  7. Sell Product",
        "  8. View Customer List",
        "  9. ManageAccount  ",
        "  10. Logout",
        "  0. Exit",
};

if (Role == "staff") {
    menu_items = {
        "  1. Show Product List",
        "  2. Sort Products by Price",
        "  3. Search Product by ID",
        "  4. Sell Product",
        "  5. View Customer List",
        "  6. Change Password",
        "  7. Logout",
        "  0. Exit",
    };
}

cout << string(padding_left, ' ') << top_left;
cout << string(box_width - 2, horizontal) << top_right << endl;

cout << string(padding_left, ' ') << vertical 
     << red << "           PRODUCT MANAGEMENT MENU           " << reset 
     << string(box_width - 47, ' ') << vertical << endl;

for (size_t i = 0; i < menu_items.size(); i++) {
    cout << string(padding_left, ' ') << vertical;
    if (static_cast<int>(i) == current_choice) {
        cout << red << "> " << menu_items[i] << reset;
    } else {
        cout << "  " << menu_items[i];
    }
    cout << string(box_width - menu_items[i].length() - 4, ' ') << vertical << endl;
}

cout << string(padding_left, ' ') << bottom_left;
cout << string(box_width - 2, horizontal) << bottom_right << endl;
}


void sellProduct(Manage& productManager, ListCustomer& Customers) {
    string customerName = getValidatedInput("Enter customer name: ",20);
    string customerContact = getValidatedInput("Enter customer contact: ",20);
    char continueBuying;
    int quantity;

    do {
        cout << "\nProducts List:\n";
        productManager.show();

        string productId = getValidatedInput("Enter product ID to sell: ",9);
        cout << "Enter quantity to sell: ";
        checkInt(quantity);

        Product* productToSell = productManager.searchByID(productId);
        Product productSold;

        if (productToSell) {
            if (productToSell->getQuantity() >= quantity) {
                // C?p nh?t s? lu?ng s?n ph?m còn l?i
                productToSell->setQuantity(productToSell->getQuantity() - quantity);
                cout << "Sold " << quantity << " units of " << productToSell->getName() 
                     << " to " << customerName << "!\n";

                // T?o b?n sao s?n ph?m d? ghi nh?n giao d?ch
                productSold = *productToSell;
                productSold.setQuantity(quantity);

                // Thêm s?n ph?m vào thông tin khách hàng
                int customerIndex = Customers.indexOf(customerContact, customerName);
                if (customerIndex != -1) {
                    Customer& existingCustomer = Customers.getCustomer(customerIndex);
                    existingCustomer.addProduct(productSold);
                } else {
                    Customer newCustomer(customerContact, customerName);
                    newCustomer.addProduct(productSold);
                    Customers.AddOrUpdateCustomer(newCustomer, productSold);
                }

                cout << "Sale recorded for " << customerName << ".\n";
            } else {
                cout << "Insufficient quantity available. Only " << productToSell->getQuantity() 
                     << " units in stock.\n";
            }
        } else {
            cout << "Product with ID " << productId << " not found.\n";
        }

        cout << "Do you want to buy another product? (y/n): ";
        cin >> continueBuying;
        cin.ignore(); 

    } while (tolower(continueBuying) == 'y'); 

    cout << "Thank you for your purchase, " << customerName << "!\n";
}

void displayManageAccountMenu(int current_choice) {
    char top_left = 201, top_right = 187;
    char bottom_left = 200, bottom_right = 188;
    char horizontal = 205, vertical = 186;

    string red = "\033[1;31m";
    string reset = "\033[0m";

    int console_width = 80;
    int box_width = 50;
    int padding_left = (console_width - box_width) / 2;

    vector<string> menu_items = {
        "  1. Add Staff",
        "  2. Remove Staff",
        "  3. Change Admin Password",
        "  4. Show Staff List",
        "  0. Back to Main Menu"
    };

    cout << string(padding_left, ' ') << top_left;
    cout << string(box_width - 2, horizontal) << top_right << endl;

    cout << string(padding_left, ' ') << vertical 
         << red << "             MANAGE ACCOUNT MENU             " << reset 
         << string(box_width - 47, ' ') << vertical << endl;

    for (size_t i = 0; i < menu_items.size(); i++) {
        cout << string(padding_left, ' ') << vertical;
        if (static_cast<int>(i) == current_choice) {
            cout << red << "> " << menu_items[i] << reset;
        } else {
            cout << "  " << menu_items[i];
        }
        cout << string(box_width - menu_items[i].length() - 4, ' ') << vertical << endl;
    }

    cout << string(padding_left, ' ') << bottom_left;
    cout << string(box_width - 2, horizontal) << bottom_right << endl;
}

void manageAccount(Admin& admin) {
    int current_choice = 0;
    int choice;

    do {
        system("cls");
        displayManageAccountMenu(current_choice);
        char ch = _getch();
        if (ch == 72 && current_choice > 0) {  
            current_choice--;
        } else if (ch == 80 && current_choice < 4) {  
            current_choice++;
        } else if (ch == 13) {  
            choice = current_choice;
            system("cls");

            switch (choice) {
                case 0: {  
                    string id, name, role, phone, username, password;
                    int result;
                    do {
                        id = getValidatedInput("Enter staff ID: ",9);
                        name = getValidatedInput("Enter name: ",20);
                        phone = getValidatedInput("Enter phone: ",20);
                        username = getValidatedInput("Enter username: ",10);
                        password = getValidatedInput("Enter password: ",10);
                        role = "staff";

                        Staff newStaff(username, password, role, id, name, phone);
                        result = admin.addStaff(newStaff);
                        if (result == 1) {
                            cout << "Staff added successfully!\n";
                        } else {
                            cout << "Failed to add staff. Please check the input and try again.\n";
                        }
                    } while (result != 1);
                    break;
                }
                case 1: {  
                    string staffId = getValidatedInput("Enter staff ID to remove: ",9);
                    admin.removeStaff(staffId);
                    break;
                }
                case 2: {  
                    string currentPassword = getValidatedInput("Enter current password: ",10);
                    if (admin.getPassword() != currentPassword) {
                        cout << "Incorrect password. Password change failed.\n";
                    } else {
                        string newPassword = getValidatedInput("Enter new password: ",10);
                        string confirmPassword = getValidatedInput("Confirm new password: ",10);
                        if (newPassword == confirmPassword) {
                            admin.setPassword(newPassword);
                            cout << "Admin password changed successfully.\n";
                        } else {
                            cout << "Passwords do not match. Password change failed.\n";
                        }
                    }
                    break;
                }
                case 3: {  
                    cout << "\033[1;31mStaff List:\033[0m\n";
                    admin.showStaff();
                    break;
                }
                case 4:  
                    return;
                default:
                    cout << "Invalid choice.\n";
            }

            cout << "\nPress any key to continue...\n";
            _getch();
        }
    } while (choice != 4);
}


void drawSearch(Product* product){
    char top_left = 201, top_right = 187, bottom_left = 200, bottom_right = 188;
    char horizontal = 205, vertical = 186, cross = 206;
    char left_t = 204, right_t = 185, top_t = 203, bottom_t = 202;
    string dark_blue = "\033[0;34m"; 
    string pink = "\033[1;35m";    
    string reset = "\033[0m";

    // Set default column widths
    int col_widths[] = {30, 12, 20, 15, 10, 10, 12}; // Increased width of Product to 30
    int total_col_width = col_widths[0] + col_widths[1] + col_widths[2] + col_widths[3] + col_widths[4] + col_widths[5] + col_widths[6] + 7; // Including separators
    int console_width = 100;  // Default console width

    // Adjust column widths if the table exceeds the console width
    if (total_col_width > console_width) {
        int remaining_width = console_width - 7; // 7 for vertical bars
        int total_column_count = sizeof(col_widths) / sizeof(col_widths[0]);
        
        // Distribute remaining width to the columns, if possible
        int adjusted_width = remaining_width / total_column_count;
        
        // Set new column widths to fit the console width
        for (int i = 1; i < total_column_count; ++i) {
            col_widths[i] = adjusted_width; // Keep Product column wide
        }
        total_col_width = remaining_width + 7;
    }

    int padding_left = (console_width - total_col_width) / 2;
    if (padding_left < 0) padding_left = 0;  // Ensure non-negative padding
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
    cout << top_t;
    for (int i = 0; i < col_widths[6]; i++) cout << horizontal;
    cout << top_right << reset << endl;

    // Print column headers
    cout << padding << dark_blue << vertical << reset 
        << pink << setw(col_widths[0]) << left << "Product"
        << dark_blue << vertical << reset 
        << pink << setw(col_widths[1]) << left << "ID"
        << dark_blue << vertical << reset 
        << pink << setw(col_widths[2]) << left << "Brand"
        << dark_blue << vertical << reset 
        << pink << setw(col_widths[3]) << left << "Color"
        << dark_blue << vertical << reset 
        << pink << setw(col_widths[4]) << left << "Quantity"
        << dark_blue << vertical << reset 
        << pink << setw(col_widths[5]) << left << "Size"
        << dark_blue << vertical << reset 
        << pink << setw(col_widths[6]) << left << "Price"
        << dark_blue << vertical << reset << endl;

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
    cout << cross;
    for (int i = 0; i < col_widths[6]; i++) cout << horizontal;
    cout << right_t << reset << endl;

    // Assuming 'product' is a valid pointer to a product object
    cout << padding << dark_blue << vertical << reset 
        << setw(col_widths[0]) << left << product->getName()
        << dark_blue << vertical << reset 
        << setw(col_widths[1]) << left << product->getID()
        << dark_blue << vertical << reset 
        << setw(col_widths[2]) << left << product->getBrand()
        << dark_blue << vertical << reset 
        << setw(col_widths[3]) << left << product->getColor()
        << dark_blue << vertical << reset 
        << setw(col_widths[4]) << right << product->getQuantity()
        << dark_blue << vertical << reset 
        << setw(col_widths[5]) << right << product->getSize()
        << dark_blue << vertical << reset 
        << setw(col_widths[6]) << right << product->getPrice()
        << dark_blue << vertical << reset << endl;

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
    cout << bottom_t;
    for (int i = 0; i < col_widths[6]; i++) cout << horizontal;
    cout << bottom_right << reset << endl;
}
int main() {
    Admin admin;
    Account acc;
    vector<Account> accounts;
    const string filename = "ManageStaff.dat";

    admin.readFromBinaryFile("ManageStaff.dat");
    acc.readAccountsFromFile("ManageStaff.dat",accounts);

    if (accounts.empty()) {
        accounts.push_back({"admin", "admin123", "admin"});
        string user,pass,role;
        user ="admin";pass="admin123";role = "admin";
        admin.setUsername(user);
        admin.setPassword(pass);
        admin.setRole(role);
    }

    Manage productManager;
    productManager.readFromFile("products.txt");

    ListCustomer Customers;
    Customers.readFromFile("customers.txt");

    Account* loggedInUser = nullptr;
    while (!loggedInUser) {
        loggedInUser = login(accounts);
    }


    int current_choice = 0;
    int choice;

    do {
        system("cls");
        displayMenu(current_choice, loggedInUser->getRole());  
        char ch = _getch();

        if (ch == 72 && current_choice > 0) {  
            current_choice--;
        } else if (ch == 80 && 
                   ((loggedInUser->getRole() == "admin" && current_choice < 10) || 
                    (loggedInUser->getRole() == "staff" && current_choice < 7))) { 
            current_choice++;
        } else if (ch == 13) {  
            choice = current_choice;
            system("cls");
            if (loggedInUser->getRole() == "admin") {
                switch (choice) {
                 case 0: { 
						    string name, id, brand, color;
						    float price;
						    int size, quantity;
						    int result;
						
						    do {
						        name = getValidatedInput("Enter product name (Shoe Name): ",20);
						        id = getValidatedInput("Enter product ID: ",9);
						        brand = getValidatedInput("Enter brand: ",20);
						        color = getValidatedInput("Enter color: ",15);
						
						        cout << "Enter price: ";
						        checkFloat(price);
						        cout << "Enter size: ";
						        checkInt(size);
						        cout << "Enter quantity: ";
						        checkInt(quantity);
						        cin.ignore();
						
						        Product newProduct(name, id, brand, color, price, size, quantity);
						        result = productManager.Add(newProduct);  
						    } while (result == 1);
						
						    cout << "Product added successfully!\n";
						    break;
						}

                    case 1: {  
                        cout << "\033[1;31m                                             Shoes List\033[0m" << endl;
                        productManager.show();
                        string id;
                        cout << "Enter product ID to remove: ";
                        getline(cin, id);
                        if (productManager.Remove(id)) {
                            cout << "Product removed successfully!\n";
                        }
                        break;
                    }
                    case 2:  
                        cout << "\033[1;31m                                             Shoes List\033[0m" << endl;
                        productManager.show();
                        break;
                    case 3: 
                        productManager.sort();
                        cout << "Products sorted by price!\n";
                        break;
                    case 4: {  
                        string id;
                        cout << "\033[1;31m                                             Shoes List\033[0m" << endl;
                        productManager.show();
                        cout << "Enter product ID to search: ";
                        getline(cin, id);
                        Product* product = productManager.searchByID(id);
                        if (product) {
                           drawSearch(product); 
                        } else {
                            cout << "Product not found.\n";
                        }
                        break;
                    }
                    case 5: {  
                        cout << "\033[1;31m                                             Shoes List\033[0m" << endl;
                        productManager.show();
                        string id;
                        cout << "Enter product ID to update: ";
                        getline(cin, id);
                        productManager.Update(id);
                        break;
                    }
                    case 6:  
                        sellProduct(productManager, Customers);
                        break;
                    case 7: 
                        cout << "\033[1;31m                                                View Customer List\033[0m" << endl;
                        Customers.Show();
                        break;
                    
                    case 8: {
					    manageAccount(admin);
                        break;
                        }

                    case 9: 
                        loggedInUser = nullptr;
                        while (!loggedInUser) {
                            loggedInUser = login(accounts);  
                        }
                        break;
                    case 10:  
                        admin.writeToBinaryFile("ManageStaff.dat");
                        productManager.writeToFile("products.txt");
                        cout << "Exiting the program.\n";
                        break;
                }
            } else if (loggedInUser->getRole() == "staff") {
                switch (choice) {
                    case 0:  
                        cout << "\033[1;31m                                             Shoes List\033[0m" << endl;
                        productManager.show();
                        break;
                    case 1: 
                        productManager.sort();
                        cout << "Products sorted by price!\n";
                        break;
                    case 2: {  
                        cout << "\033[1;31m                                             Shoes List\033[0m" << endl;
                        productManager.show();
                        string id;
                        cout << "Enter product ID to search: ";
                        getline(cin, id);
                        Product* product = productManager.searchByID(id);
                        if (product) {
                            cout << "Product found: " << product->getName() << ", Price: " << product->getPrice() << endl;
                        } else {
                            cout << "Product not found.\n";
                        }
                        break;
                    }
                    case 3: 
                        sellProduct(productManager, Customers);
                        break;
                    case 4:  
                        cout << "\033[1;31m               View Customer List:\033[0m" << endl;
                        Customers.Show();
                        break;
                    case 5: {
							    string currentPassword, newPassword, confirmPassword;
							
							    currentPassword = getValidatedInput("Enter current password: ",10);
							    if (loggedInUser->getPassword() != currentPassword) {
							        cout << "Incorrect password. Password change failed.\n";
							    } else {
							        newPassword = getValidatedInput("Enter new password: ",10);
							        confirmPassword = getValidatedInput("Confirm new password: ",10);
							
							        if (newPassword == confirmPassword) {
							            loggedInUser->setPassword(newPassword);
							            admin.changePasswordOfStaff(loggedInUser->getUsername(), newPassword);
							            cout << "Password changed successfully.\n";
							        } else {
							            cout << "Passwords do not match. Password change failed.\n";
							        }
							    }
							    break;
							}

                    case 6: 
                        loggedInUser = nullptr;
                        while (!loggedInUser) {
                            loggedInUser = login(accounts); 
                        }
                        break;
                    case 7:  
                        admin.writeToBinaryFile("ManageStaff.dat");
                        productManager.writeToFile("products.txt");
                        cout << "Exiting the program.\n";
                        break;
                }
            }

        cout << "\n\nPress any key to continue...\n";
        _getch();
    }
} while (choice != (loggedInUser->getRole() == "admin" ? 10 : 7));

return 0;
}

