#include "Staff.h"  

Staff::Staff(const string& user, const string& pass, const string& Role, 
             const string& id, const string& name, const string& phone)
    : Account(user, pass, Role), id(id), name(name), phone(phone) {}


Staff::Staff() : Account("", "", "staff"), id(""), name(""), phone("") {}


Staff::~Staff() {
}


string Staff::getId() const { return id; }
string Staff::getName() const { return name; }
string Staff::getPhone() const { return phone; }


void Staff::display() const {
    cout << "ID: " << id
         << "\nName: " << name
         << "\nPhone: " << phone <<endl;
}

void Staff::writeToBinaryFile(std::ofstream& outfile) const {
    // Ghi thông tin c?a l?p Account
    Account::writeAccountToBinaryFile(outfile);

    // Ghi thông tin riêng c?a Staff
    writeStringToFile(outfile, id);
    writeStringToFile(outfile, name);
    writeStringToFile(outfile, phone);
}

void Staff::writeStringToFile(std::ofstream& outfile, const std::string& str) const {
    size_t length = str.size();  // Không c?n +1, vì không ghi ký t? '\0'
    outfile.write(reinterpret_cast<const char*>(&length), sizeof(length));
    outfile.write(str.data(), length);  // Ghi chu?i tr?c ti?p
}


void Staff::readFromBinaryFile(std::ifstream& infile) {
    // Ð?c thông tin c?a l?p Account
    Account::readAccountFromBinaryFile(infile);

    // Ð?c thông tin riêng c?a Staff
    id = readStringFromFile(infile);
    name = readStringFromFile(infile);
    phone = readStringFromFile(infile);
}

std::string Staff::readStringFromFile(std::ifstream& infile) {
    size_t length;
    infile.read(reinterpret_cast<char*>(&length), sizeof(length));  // Ð?c kích thu?c chu?i

    // S? d?ng std::string d? qu?n lý b? nh? an toàn
    std::string result(length, '\0');
    infile.read(&result[0], length);  // Ð?c d? li?u tr?c ti?p vào chu?i
    return result;
}



