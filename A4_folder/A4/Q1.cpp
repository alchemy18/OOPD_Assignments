#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Class to represent an author
class Author {
private:
    string name;
    string affiliation;

public:
    // Constructor
    Author(string name, string affiliation)
        : name(name), affiliation(affiliation) {}

    // Getters
    string getName() const { return name; }
    string getAffiliation() const { return affiliation; }

    // Function to display author details
    void display() const {
        cout << "Name: " << name << ", Affiliation: " << affiliation << endl;
    }

    // Check if the author is affiliated with the institute
    bool isInstituteAffiliated(const string& instituteAffiliation) const {
        return affiliation == instituteAffiliation;
    }
};

// Class to represent a publication
class Publication {
private:
    string title;
    string venue;
    int year;
    vector<Author> authors;
    string doi;

public:
    // Constructor
    Publication(string title, string venue, int year, const vector<Author>& authors, string doi = "")
        : title(title), venue(venue), year(year), authors(authors), doi(doi) {
        // Ensure at least one author is affiliated with the institute
        bool instituteAffiliated = false;
        for (const Author& author : authors) {
            if (author.isInstituteAffiliated("Institute of Research")) {
                instituteAffiliated = true;
                break;
            }
        }
        if (!instituteAffiliated) {
            throw invalid_argument("At least one author must have the institute's affiliation.");
        }
    }

    // Function to display publication details
    void display() const {
        cout << "Title: " << title << endl;
        cout << "Venue: " << venue << endl;
        cout << "Year: " << year << endl;
        cout << "DOI: " << (doi.empty() ? "N/A" : doi) << endl;
        cout << "Authors:" << endl;
        for (const Author& author : authors) {
            author.display();
        }
    }
};

// Main function
int main() {
    try {
        // Authors
        Author author1("Pragya", "Institute of Research");
        Author author2("Aditya", "IIIT Hyderabad");
        Author author3("Ayush", "NUS");

        // Vector of authors
        vector<Author> authors = {author1, author2, author3};

        Publication publication(
            "A Study on Object-Oriented Modeling",
            "International Journal of Computer Science",
            2024,
            authors,
            "10.1000/xyz123"
        );

        // Displaying publication details
        cout << "Publication Details:" << endl;
        publication.display();

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
