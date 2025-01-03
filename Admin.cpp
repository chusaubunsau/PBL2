#include "Admin.h" 
Admin::Admin() = default;

Admin::Admin(const string& user, const string& pass, const string& Role)
    : Account(user, pass, Role) {}
    

int Admin::addStaff(const Staff& staff) {
   
    for (const auto& existingStaff : listStaff) {
        if (existingStaff.getId() == staff.getId()) {
            cout << "Error: Staff ID '" << staff.getId() << "' already exists." << endl;
            return -1;
        }
        if (existingStaff.getPhone() == staff.getPhone()) {
            cout << "Error: Phone number '" << staff.getPhone() << "' already exists." << endl;
            return -1;
        }
        if (existingStaff.getUsername() == staff.getUsername()) {
            cout << "Error: Username '" << staff.getUsername() << "' already exists." << endl;
            return -1;
        }
    }

   
    listStaff.push_back(staff);
    cout << "Added staff with ID: " << staff.getId() << endl;
    return 1;
}

Admin::~Admin() {
}

void Admin::removeStaff(string staffId) {
    for (auto it = listStaff.begin(); it != listStaff.end(); ++it) {
        if (it->getId() == staffId) {
            listStaff.erase(it);
            cout << "Removed staff with ID: " << staffId << endl;
            return;
        }
    }
    cout << "Staff with ID " << staffId << " not found.\n";
}
void Admin::writeToBinaryFile(const string& filename) const {
    ofstream outfile(filename, ios::binary | ios::out);
    if (!outfile.is_open()) {
       cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

  
    Account::writeAccountToBinaryFile(outfile);  

    
    size_t staffCount = listStaff.size();
    outfile.write(reinterpret_cast<const char*>(&staffCount), sizeof(staffCount));

    
    for (const auto& staff : listStaff) {
        staff.writeToBinaryFile(outfile);  // Ghi thông tin t?ng Staff
    }

    outfile.close();
}
void Admin::readFromBinaryFile(const string& filename) {
    ifstream infile(filename, ios::binary | ios::in);
    if (!infile.is_open()) {
        cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    
    Account::readAccountFromBinaryFile(infile);

    
    size_t staffCount;
    infile.read(reinterpret_cast<char*>(&staffCount), sizeof(staffCount));

    listStaff.clear();
    for (size_t i = 0; i < staffCount; ++i) {
        Staff staff;
        staff.readFromBinaryFile(infile); 
        listStaff.push_back(staff);  
    }

    infile.close();
}



bool Admin::changePassword(string staffId, const string& newPassword) {
    for (auto& staff : listStaff) {
        if (staff.getId() == staffId) {
            staff.setPassword(newPassword);
            cout << "Password changed successfully for staff ID: " << staffId << endl;
            return true;
        }
    }
    cout << "Staff with ID " << staffId << " not found.\n";
    return false;
}

bool Admin::changePasswordOfStaff(string user, const string& newPassword) {
    for (auto& staff : listStaff) {
        if (staff.getUsername() == user) {
            staff.setPassword(newPassword);
            return true;
        }
    }
    cout << "Password change failed.\n";
    return false;
}

void Admin::showStaff() const {
    
    for (const auto& staff : listStaff) {
        cout << "ID: " << staff.getId()
             << ", Name: " << staff.getName()
             << ", Phone: " << staff.getPhone()
             << ", Username: " << staff.getUsername() << endl;
    }
}

