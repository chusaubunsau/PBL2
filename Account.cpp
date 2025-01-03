#include "Account.h"
#include "Staff.h"   


Account::Account() = default;

Account::Account(const string& user, const string& pass, const string& Role)
    : Username(user), Password(pass), Role(Role) {}

Account::Account(const Account& other){
        Username = other.Username;
        Password = other.Password;
        Role = other.Role;
    }
Account::Account(const Staff& staff) 
: Username(staff.getUsername()), Password(staff.getPassword()), Role(staff.getRole()) {}
Account::~Account() = default;


string Account::getRole() const { return Role; }
string Account::getPassword() const { return Password; }
string Account::getUsername() const { return Username; }


void Account::setUsername(const string& user) { Username = user; }
void Account::setPassword(const string& pass) { Password = pass; }
void Account::setRole(const string& role) { Role = role; }


bool Account::verifyPassword(const string& inputPassword) const {
    return Password == inputPassword;
}


void Account::writeAccountToBinaryFile(std::ofstream& outfile) const {
    size_t usernameLength = Username.size();
    outfile.write(reinterpret_cast<const char*>(&usernameLength), sizeof(usernameLength));
    outfile.write(Username.c_str(), usernameLength);

    size_t passwordLength = Password.size();
    outfile.write(reinterpret_cast<const char*>(&passwordLength), sizeof(passwordLength));
    outfile.write(Password.c_str(), passwordLength);

    size_t roleLength = Role.size();
    outfile.write(reinterpret_cast<const char*>(&roleLength), sizeof(roleLength));
    outfile.write(Role.c_str(), roleLength);
}


void Account::readAccountFromBinaryFile(std::ifstream& infile) {
    size_t usernameLength;
    infile.read(reinterpret_cast<char*>(&usernameLength), sizeof(usernameLength));
    Username.resize(usernameLength);
    infile.read(&Username[0], usernameLength);

    size_t passwordLength;
    infile.read(reinterpret_cast<char*>(&passwordLength), sizeof(passwordLength));
    Password.resize(passwordLength);
    infile.read(&Password[0], passwordLength);

    size_t roleLength;
    infile.read(reinterpret_cast<char*>(&roleLength), sizeof(roleLength));
    Role.resize(roleLength);
    infile.read(&Role[0], roleLength);
}

void Account::readAccountsFromFile(const std::string& filename, std::vector<Account>& accounts) {
    ifstream infile(filename, ios::binary | ios::in);
    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }


    Account admin;
    admin.readAccountFromBinaryFile(infile);
    accounts.push_back(admin); 

   
    size_t staffCount;
    infile.read(reinterpret_cast<char*>(&staffCount), sizeof(staffCount));

   
    for (size_t i = 0; i < staffCount; ++i) {
        Staff staff;
        staff.readFromBinaryFile(infile);  
        accounts.push_back(staff);  
    }

    infile.close();
}

