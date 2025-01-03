	#pragma once

#include "Account.h"  

using namespace std;

class Staff : public Account {
protected:
    string id;
    string name;
    string phone;

public:
    
    Staff(const string& user, const string& pass, const string& Role, 
          const string& id = "", const string& name = "", const string& phone = "");
    Staff(const Staff& other) : Account(other) { 
        id = other.id;
        name = other.name;
        phone = other.phone;
    }

    Staff();
    ~Staff() override;
    string getId() const;
    string getName() const;
    string getPhone() const;
    void display() const;
    void writeToBinaryFile(ofstream& outfile) const;
    void readFromBinaryFile(ifstream& infile);
    void writeStringToFile(ofstream& outfile, const string& str) const;
    string readStringFromFile(ifstream& infile) ;
};

