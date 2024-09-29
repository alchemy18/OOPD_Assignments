#include <iostream>
#include <string>

using namespace std;

// Base class for a person in the department
class Person {
protected:
    string name;
    string roomNumber;
    string phoneNumber;
    string email; // Added email attribute

public:
    Person(string name, string room, string phone, string email)
        : name(name), roomNumber(room), phoneNumber(phone), email(email) {}

    virtual void getContactInfo() {
        cout << "Name: " << name << endl;
        cout << "Room: " << roomNumber << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Email: " << email << endl; // Display email
    }

    string getName() const {
        return name;
    }
};

// Class for Faculty, inherits from Person
class Faculty : public Person {
public:
    Faculty(string name, string room, string phone, string email)
        : Person(name, room, phone, email) {}
};

// Class for Head of Department, inherits from Faculty
class HeadOfDepartment : public Faculty {
public:
    HeadOfDepartment(string name, string room, string phone, string email)
        : Faculty(name, room, phone, email) {}

    void getContactInfo() override {
        cout << "Head of Department" << endl;
        Faculty::getContactInfo();
    }
};

// Class for Administrative Officer
class AdminOfficer : public Person {
public:
    AdminOfficer(string name, string room, string phone, string email)
        : Person(name, room, phone, email) {}

    void getContactInfo() override {
        cout << "Administrative Officer" << endl;
        Person::getContactInfo();
    }
};

// Class representing a Department
class Department {
private:
    string departmentName;
    HeadOfDepartment* hod;
    AdminOfficer* adminOfficer;
    Faculty** facultyMembers; // Use a raw pointer array for faculty members
    int facultyCount; // To keep track of the number of faculty members

public:
    Department(string deptName, HeadOfDepartment* hod, AdminOfficer* adminOfficer, Faculty** faculty, int count)
        : departmentName(deptName), hod(hod), adminOfficer(adminOfficer), facultyCount(count) {
        facultyMembers = new Faculty*[facultyCount];
        for (int i = 0; i < facultyCount; ++i) {
            facultyMembers[i] = faculty[i];
        }
    }

    void getDepartmentDetails() {
        cout << "Department: " << departmentName << endl;
        cout << "-----------------------------------" << endl;

        hod->getContactInfo();
        cout << "-----------------------------------" << endl;

        adminOfficer->getContactInfo();
        cout << "-----------------------------------" << endl;

        cout << "Faculty Members:" << endl;
        for (int i = 0; i < facultyCount; ++i) {
            facultyMembers[i]->getContactInfo();
            cout << "-----------------------------------" << endl;
        }
    }

    void fetchContactInfoByName(const string& name) {
        if (hod->getName() == name) {
            cout << "Contact found in department: " << departmentName << endl;
            hod->getContactInfo();
            return;
        }

        if (adminOfficer->getName() == name) {
            cout << "Contact found in department: " << departmentName << endl;
            adminOfficer->getContactInfo();
            return;
        }

        for (int i = 0; i < facultyCount; ++i) {
            if (facultyMembers[i]->getName() == name) {
                cout << "Contact found in department: " << departmentName << endl;
                facultyMembers[i]->getContactInfo();
                return;
            }
        }

        cout << "No contact found with the name: " << name << " in department: " << departmentName << endl;
    }

    ~Department() {
        delete hod;
        delete adminOfficer;
        for (int i = 0; i < facultyCount; ++i) {
            delete facultyMembers[i];  // Clean up each faculty member
        }
        delete[] facultyMembers; // Clean up the faculty array
    }
};

// Main function to create the departments and faculty
int main() {
    // Faculty members for CSE Department
    Faculty* facultyCSE[] = {
        new Faculty("Pushpendra Singh", "A-502 (R&D Block)", "011-26907458", "psingh@iiitd.ac.in"),
        new Faculty("Saket Anand", "B-410 (R&D Block)", "011-26907425", "anands@iiitd.ac.in"),
        new Faculty("Rinku Shah", "B-502 (R&D Block)", "011-26907538", "rinku@iiitd.ac.in"),
        new Faculty("Angshul Majumdar", "A-606 (R&D Block)", "011-26907451", "angshul@iiitd.ac.in"),
        new Faculty("Sujay Deb", "A-607 (R&D Block)", "011-26907452", "sdeb@iiitd.ac.in")
    };

    HeadOfDepartment* hodCSE = new HeadOfDepartment("Sambuddho Chakravarty", "B-503 (R&D Block)", "011-26907478", "sambuddho@iiitd.ac.in");
    AdminOfficer* adminCSE = new AdminOfficer("Priti Patwal", "A-501 (R&D Block)", "01126907411", "pritip@iiitd.ac.in");
    Department CSE("Computer Science and Engineering", hodCSE, adminCSE, facultyCSE, 5);

    // Faculty members for ECE Department
    Faculty* facultyECE[] = {
        new Faculty("Saket Anand", "B-410 (R&D Block)", "011-26907425", "anands@iiitd.ac.in"),
        new Faculty("Arani Bhattacharya", "B-510 (R&D Block)", "011-26907434", "arani@iiitd.ac.in"),
        new Faculty("Ranjitha Prasad", "A-403 (R&D Block)", "011-26907357", "ranjitha@iiitd.ac.in"),
        new Faculty("Angshul Majumdar", "A-606 (R&D Block)", "011-26907451", "angshul@iiitd.ac.in"),
        new Faculty("Sujay Deb", "A-607 (R&D Block)", "011-26907452", "sdeb@iiitd.ac.in")
    };

    HeadOfDepartment* hodECE = new HeadOfDepartment("A V Subramanyam", "B-604 (R&D Block)", "+91 011-26907437", "subramanyam@iiitd.ac.in");
    AdminOfficer* adminECE = new AdminOfficer("Sanjna Khosla", " A-601 (R&D Block)", "011-26907593", "sanjna@iiitd.ac.in");
    Department ECE("Electronics and Communication Engineering", hodECE, adminECE, facultyECE, 5);

    // Faculty members for Math Department
    Faculty* facultyMath[] = {
        new Faculty("Kaushik Kalyanaraman", "B-302 (R&D Block)", "011-26907537", "kaushik@iiitd.ac.in"),
        new Faculty("Prof. Anuradha Sharma", "B-311 (R&D Block)", "+91-11-26907534", "anuradha@iiitd.ac.in"),
        new Faculty("Dr. Rajiv Raman", "B-507 (R&D Block)", "+91-11-26907573", "rajiv@iiitd.ac.in"),
        new Faculty("Dr. Subhashree Mohapatra", "A-309 (R&D Block)", "+91-11-26907459", "subhashree@iiitd.ac.in"),
        new Faculty("Dr. Sneha Chaubey", "B-308 (R&D Block)", "+91-11-26907462", "sneha@iiitd.ac.in")
    };

    HeadOfDepartment* hodMath = new HeadOfDepartment("Kaushik Kalyanaraman", "B-302 (R&D Block)", "011-26907537", "kaushik@iiitd.ac.in");
    AdminOfficer* adminMath = new AdminOfficer("Risha Lal", "B-301 (R & D Block)", "011-26907548", "risha@iiitd.ac.in");
    Department Math("Mathematics", hodMath, adminMath, facultyMath, 5);

    // Faculty members for SSH Department
    Faculty* facultySSH[] = {
        new Faculty("Dr. J. V. Meenakshi", "A-205 (R&D Block)", "+91-11-26907535", "meena@iiitd.ac.in"),
        new Faculty("Dr. Gaurav Arora", "B-206 (R&D Block)", "+91-11-26907547", "gaurav@iiitd.ac.in"),
        new Faculty("Dr. Manohar Kumar", "B-207 (R&D Block)", "+91-11-26907557", "manohar.kumar@iiitd.ac.in"),
        new Faculty("Dr. Mrinmoy Chakrabarty", "A-202", "+91-11-26907363", "mrinmoy@iiitd.ac.in"),
        new Faculty("Deepak Prince", "A-210 (R&D Block)", "+011-26907 595", "deepak@iiitd.ac.in")
    };

    HeadOfDepartment* hodSSH = new HeadOfDepartment("Dr. J. V. Meenakshi", "B-205 (R&D Block)", "+91-11-26907535", "meena@iiitd.ac.in");
    AdminOfficer* adminSSH = new AdminOfficer("Ms. Rubina Thakur", "B-201(R&D Block)", "+91-11-26907497", "sophia.wilson@ssh.edu");
    Department SSH("Social Sciences and Humanities", hodSSH, adminSSH, facultySSH, 5);

    // Faculty members for Bio Department
    Faculty* facultyBio[] = {
        new Faculty("Debarka Sengupta", "A-306 (R&D Block)", "+91-11-26907446", "debarka@iiitd.ac.in"),
        new Faculty("GPS Raghava", "A-302 (R&D Block)", "011-26907444", "raghava@iiitd.ac.in"),
        new Faculty("Jaspreet Kaur Dhanjal", "A-307 (R&D Block)", "011-26907522", "jaspreet@iiitd.ac.in"),
        new Faculty("Ganesh Bagler", "A-305 (R&D Block)", "011-26907443", "bagler@iiitd.ac.in"),
        new Faculty("Gaurav Ahuja", "A-303 (R&D Block)", "011-26907475", "gaurav.ahuja@iiitd.ac.in")
    };

    HeadOfDepartment* hodBio = new HeadOfDepartment("GPS Raghava", "A-302 (R&D Block)", "011-26907444", "raghava@iiitd.ac.in");
    AdminOfficer* adminBio = new AdminOfficer("Shipra Jain", "A-302 (R&D Block)", "011-78901230", "shipra@iiitd.ac.in");
    Department Bio("Biology", hodBio, adminBio, facultyBio, 5);

    // User input for fetching contact info
    string name;
    cout << "Enter the name of the person to fetch room, phone number, and email: ";
    getline(cin, name);
    
    // Fetch contact info for the entered name
    CSE.fetchContactInfoByName(name);
    ECE.fetchContactInfoByName(name);
    Math.fetchContactInfoByName(name);
    SSH.fetchContactInfoByName(name);
    Bio.fetchContactInfoByName(name);

    // Ask user which department they want to view
    string deptChoice;
    cout << "Enter the department name you want to view (CSE, ECE, Math, SSH, Bio): ";
    getline(cin, deptChoice);

    // Show department info based on user choice
    if (deptChoice == "CSE") {
        CSE.getDepartmentDetails();
    } else if (deptChoice == "ECE") {
        ECE.getDepartmentDetails();
    } else if (deptChoice == "Math") {
        Math.getDepartmentDetails();
    } else if (deptChoice == "SSH") {
        SSH.getDepartmentDetails();
    } else if (deptChoice == "Bio") {
        Bio.getDepartmentDetails();
    } else {
        cout << "Invalid department name." << endl;
    }

    return 0;
}
