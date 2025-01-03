#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Account {
protected:
    string Username;
    string Password;
    string Role;

public:
  
    Account();
    Account(const string& user, const string& pass, const string& Role);
    Account(const Account& ) ;

    Account(const class Staff& staff);
    virtual ~Account();
    string getRole() const;
    string getPassword() const;
    string getUsername() const;
    void setUsername(const string& user);
    void setPassword(const string& pass);
    void setRole(const string& role);
    bool verifyPassword(const string& inputPassword) const;
    virtual void writeAccountToBinaryFile(ofstream& outfile) const;
    virtual void readAccountFromBinaryFile(ifstream& infile);
    static void readAccountsFromFile(const string& filename, vector<Account>& accounts);
};

