#include <iostream>
#include <string>

using namespace std;

// Class representing an issue
class Issue {
public:
    string issueDescription;
    int unresolvedDays;
    bool resolvedStatus;
    string resolvedBy;  // To track who resolved the issue

    // Constructor
    Issue(string description) : issueDescription(description), unresolvedDays(0), resolvedStatus(false), resolvedBy("") {}

    // Method to mark issue as resolved
    void markResolved(const string& resolver) {
        resolvedStatus = true;
        resolvedBy = resolver;
        cout << "\n--- Issue has been successfully resolved by " << resolver << ": " << issueDescription << " ---\n" << endl;
    }

    // Method to increase unresolved days
    void addDay() {
        unresolvedDays++;
    }
};

// Abstract class for handling issues at different levels
class IssueHandler {
protected:
    IssueHandler* nextLevelHandler; // The next level authority
    string handlerTitle;

public:
    // Constructor
    IssueHandler(string title) : nextLevelHandler(nullptr), handlerTitle(title) {}

    // Set the next handler in the escalation chain
    void setNextLevelHandler(IssueHandler* next) {
        nextLevelHandler = next;
    }

    // Getter for handler title
    string getHandlerTitle() const {
        return handlerTitle;
    }

    // Virtual method for handling issues (to be overridden in subclasses)
    virtual void handleIssue(Issue& issue) {
        if (issue.resolvedStatus) {
            cout << "Issue has already been resolved by " << issue.resolvedBy << ".\n";
            return;
        }

        // Escalate based on unresolved days
        if (nextLevelHandler && issue.unresolvedDays >= 3) {
            cout << "Escalating issue to " << nextLevelHandler->getHandlerTitle() << "...\n";
            nextLevelHandler->handleIssue(issue);
        } else {
            processIssue(issue);
        }
    }

    // Abstract method to process the issue
    virtual void processIssue(Issue& issue) = 0;
};

// Level 1: Administrative Officer
class AdminOfficer : public IssueHandler {
public:
    AdminOfficer() : IssueHandler("Administrative Officer") {}

    void processIssue(Issue& issue) override {
        cout << handlerTitle << " is reviewing the issue: " << issue.issueDescription << endl;
        char resolveInput;
        cout << "\nShould the " << handlerTitle << " resolve the issue? (y/n): ";
        cin >> resolveInput;

        if (resolveInput == 'y' || resolveInput == 'Y') {
            issue.markResolved(handlerTitle);
        } else {
            cout << handlerTitle << " could not resolve the issue yet.\n";
            issue.addDay();
        }
    }
};

// Level 2: Associate Dean (IRD Specific)
class AssociateDean : public IssueHandler {
public:
    AssociateDean() : IssueHandler("Associate Dean") {}

    void processIssue(Issue& issue) override {
        cout << handlerTitle << " is addressing the issue: " << issue.issueDescription << endl;
        issue.addDay();
    }
};

// Level 2: Dean (General for Academics, Student Affairs, IRD)
class Dean : public IssueHandler {
public:
    Dean() : IssueHandler("Dean") {}

    void processIssue(Issue& issue) override {
        cout << handlerTitle << " is analyzing the issue: " << issue.issueDescription << endl;
        issue.addDay();
    }
};

// Level 3: Registrar (Final Authority for Some Departments)
class Registrar : public IssueHandler {
public:
    Registrar() : IssueHandler("Registrar") {}

    void processIssue(Issue& issue) override {
        cout << handlerTitle << " is finalizing the issue: " << issue.issueDescription << endl;
        issue.markResolved(handlerTitle);  // Registrar resolves the issue
    }
};

// Function to create department hierarchy
IssueHandler* createDepartmentHierarchy(const string& departmentName) {
    if (departmentName == "IRD") {
        AdminOfficer* adminOfficer = new AdminOfficer();
        AssociateDean* associateDean = new AssociateDean();
        Dean* dean = new Dean();
        Registrar* registrar = new Registrar();

        // Set up escalation chain
        adminOfficer->setNextLevelHandler(associateDean);
        associateDean->setNextLevelHandler(dean);
        dean->setNextLevelHandler(registrar);

        return adminOfficer;
    } else if (departmentName == "Academics" || departmentName == "Student Affairs") {
        AdminOfficer* adminOfficer = new AdminOfficer();
        Dean* dean = new Dean();
        Registrar* registrar = new Registrar();

        // Set up escalation chain
        adminOfficer->setNextLevelHandler(dean);
        dean->setNextLevelHandler(registrar);

        return adminOfficer;
    } else if (departmentName == "Store & Purchase" || departmentName == "Library") {
        AdminOfficer* adminOfficer = new AdminOfficer();
        Registrar* registrar = new Registrar();

        // Set up escalation chain
        adminOfficer->setNextLevelHandler(registrar);

        return adminOfficer;
    }
    return nullptr;
}

// Main function
int main() {
    // Available departments and their escalation hierarchies
    string availableDepartments[] = {"IRD", "Academics", "Student Affairs", "Store & Purchase", "Library"};
    
    // Display department choices
    cout << "Available departments for complaint submission:\n";
    for (const string& dept : availableDepartments) {
        cout << "- " << dept << endl;
    }

    // Get user input for complaint and department
    string selectedDepartment;
    cout << "Please enter the department you want to log your complaint with: ";
    getline(cin, selectedDepartment);

    // Check if the selected department is valid
    bool validDepartment = false;
    for (const string& dept : availableDepartments) {
        if (dept == selectedDepartment) {
            validDepartment = true;
            break;
        }
    }

    if (!validDepartment) {
        cout << "Invalid department selected. Please try again." << endl;
        return 1;
    }

    string issueDescription;
    cout << "Enter your complaint here: ";
    getline(cin, issueDescription);
    Issue issue(issueDescription);

    // Get the number of days to simulate
    int simulationDays;
    cout << "Enter the number of days to simulate the issue handling: ";
    cin >> simulationDays;

    // Create the department-specific hierarchy
    IssueHandler* initialHandler = createDepartmentHierarchy(selectedDepartment);

    // Simulate the handling of the issue day by day in the selected department
    for (int day = 1; day <= simulationDays; ++day) {
        cout << "\n--- Day " << day << " ---" << endl;
        initialHandler->handleIssue(issue);

        // Display current days unresolved
        cout << "Days unresolved: " << issue.unresolvedDays << endl;

        if (issue.resolvedStatus) {
            cout << "\nIssue successfully resolved by " << issue.resolvedBy << " on Day " << day << ".\n";
            break;
        }

        // Increment days only after handling
        issue.addDay();
    }

    if (!issue.resolvedStatus) {
        cout << "\nThe issue has reached the highest level but remains unresolved.\n";
    }

    return 0;
}
