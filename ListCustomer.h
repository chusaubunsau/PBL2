#include <vector>
#include "Customer.h"

using namespace std;  
class ListCustomer {
private:
    Customer* customers;  
    int customerCount; 
public:
    ListCustomer();
    ~ListCustomer();
    int getCount();
    Customer* getCus();
    void AddOrUpdateCustomer(const Customer& customer, const Product& product);
    void Remove(const Customer& customer);
    void Show() const;
    void drawCustomersTable()const; 
    void writeToFile(const string& filename);
    void readFromFile(const string& filename);
    int indexOf(const string& phone, const string& name) const;
    Customer& getCustomer(int index);
};
