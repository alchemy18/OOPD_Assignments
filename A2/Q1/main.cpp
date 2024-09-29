#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name, email, phone, room_number;
public:
    Person(string n, string e, string p, string r) : name(n), email(e), phone(p), room_number(r) {}

    // Function to retrieve the name
    string get_name() const {
        return name;
    }

    virtual void get_contact_info() {
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Room: " << room_number << endl;
    }
};

class AdministrativeOfficer : public Person {
protected:
    string department, role;
public:
    AdministrativeOfficer(string n, string e, string p, string r, string d, string ro) 
        : Person(n, e, p, r), department(d), role(ro) {}
    
    void get_contact_info() override {
        Person::get_contact_info();
        cout << "Department: " << department << endl;
        cout << "Role: " << role << endl;
    }
};

class Dean : public AdministrativeOfficer {
    string assisted_by;
public:
    Dean(string n, string e, string p, string r, string d, string ro, string ab) 
        : AdministrativeOfficer(n, e, p, r, d, ro), assisted_by(ab) {}
    
    void get_contact_info() override {
        AdministrativeOfficer::get_contact_info();
        if (!assisted_by.empty())
            cout << "Assisted by: " << assisted_by << endl;
    }
};

class Registrar : public AdministrativeOfficer {
public:
    Registrar(string n, string e, string p, string r, string ro) 
        : AdministrativeOfficer(n, e, p, r, "Administration", ro) {}
    
    void get_contact_info() override {
        cout << "Registrar Details:" << endl;
        AdministrativeOfficer::get_contact_info();
    }
};

int main() {
    const int STAFF_SIZE = 20; // Define a maximum size for the array
    Person* staff[STAFF_SIZE];  // Array to hold Person pointers
    int count = 0; // Keep track of the number of staff added

    // IRD
    staff[count++] = new Registrar("Dr. Deepika Bhaskar", "deepika@iiitd.ac.in or registrar@iiitd.ac.in", "+91-11-26907419", "B-204 (Academic Block)", "Registrar");
    staff[count++] = new Dean("Vivek Bohara", "dird@iiitd.ac.in", "+91-11-26907454", "A-102", "IRD", "Dean", "Debarka Sengupta");
    staff[count++] = new Dean("Debarka Sengupta", "adird@iiitd.ac.in", "+91-11-26907446", "A-306 (R&D Block)", "IRD", "Associate Dean", "None");
    staff[count++] = new AdministrativeOfficer("Kapil Dev Garg", "kapildev@iiitd.ac.in", "+011-26907119", "A-306 (Academic Block)", "IRD", "Administrative Officer");
    staff[count++] = new AdministrativeOfficer("Imran Khan", "imran@iiitd.ac.in", "+011-26907594", "A-307 (Academic Block)", "IRD", "Junior Administrative Officer");
    
    // Academics
    staff[count++] = new Dean("Sumit J Darak", "doaa@iiitd.ac.in", "+91-11-26907427", "B-605 (R&D Block)", "Academics", "Dean", "None");
    staff[count++] = new AdministrativeOfficer("Ashutosh Brahma", "ashutosh@iiitd.ac.in", "+011-26907416", "B-202 (Academic Block)", "Academics", "Administrative Officer");
    staff[count++] = new AdministrativeOfficer("Anshu Dureja", "anshu@iiitd.ac.in", "+011-26907507", "B-208 (Academic Block)", "Academics", "Deputy Administrative Officer");
    
    // Student affair
    staff[count++] = new Dean("Shobha Sundar Ram", "dosa@iiitd.ac.in", "+91-11-26907424", "B-606 (R&D Block)", "Student Affairs", "Dean", "None");
    staff[count++] = new AdministrativeOfficer("Dr. Ravi Bhasin", "ravi@iiitd.ac.in", "+011-26907504", "A-207 (Academic Block)", "Student Affairs", "Administrative Officer");
    
    // Purchase and store
    staff[count++] = new AdministrativeOfficer("Ajay Kumar", "ajay@iiitd.ac.in", "+011-26907561", "A-103 (Academic Block)", "Store & Purchase", "Administrative Officer");
    staff[count++] = new AdministrativeOfficer("Nidhi Yadav", "nidhi@iiitd.ac.in", "+011-26907597", "A-108 (Academic Block)", "Store & Purchase", "Assistant Administrative Officer");
    
    // Library
    staff[count++] = new AdministrativeOfficer("Rajendra Singh", "rajendra@iiitd.ac.in", "+011-26907510", "Library Block", "Library", "Administrative Officer");
    staff[count++] = new AdministrativeOfficer("Parikshita Behera", "parikshita@iiitd.ac.in", "+011-26907503", "Library Block", "Library", "Junior Library Officer");

    // Ask for user input
    string query;
    cout << "Enter the name of the person you want to search for: ";
    getline(cin, query); // Take input from user
    
    // Fetch info by name
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (staff[i]->get_name() == query) {
            staff[i]->get_contact_info();
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "Person not found!" << endl;
    }

    // Clean up
    for (int i = 0; i < count; i++) {
        delete staff[i];
    }

    return 0;
}
