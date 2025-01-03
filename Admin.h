#pragma once
#include "Account.h"  
#include "Staff.h"   

using namespace std;

class Admin : public Account {
protected:
    vector<Staff> listStaff;

public:
    Admin();
    Admin(const string& user, const string& pass, const string& Role = "admin");
     ~Admin() override;

    int addStaff(const Staff& staff);
    void removeStaff(string staffId);
    
    void writeToBinaryFile(const string& filename) const;
    void readFromBinaryFile(const string& filename);
    
    bool changePassword(string staffId, const string& newPassword);
    bool changePasswordOfStaff(string user, const string& newPassword);

    void showStaff() const;
};

