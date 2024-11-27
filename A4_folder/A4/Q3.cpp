#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <stdexcept>
#include <cassert>

using namespace std;

// Struct to store publication details
struct Publication {
    string title;
    string venue;
    int year;
    vector<string> authors;

    void display() const {
        cout << "Title: " << title << endl;
        cout << "Venue: " << venue << endl;
        cout << "Year: " << year << endl;
        cout << "Authors: ";
        for (const auto& author : authors) {
            cout << author << (author == authors.back() ? "" : ", ");
        }
        cout << endl;
    }
};

// Parse a faculty list from a CSV file
set<string> loadFaculty(const string& filename) {
    set<string> faculty;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open faculty list file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        faculty.insert(line); // Assume each line contains a faculty name
    }
    return faculty;
}

map<string, vector<Publication>> parseBibFile(const string& filename, const set<string>& faculty) {
    map<string, vector<Publication>> authorPublications;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open bib file: " + filename);
    }

    string line, entry;
    bool insideEntry = false; // Flag to check if we're inside an entry
    while (getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '%') continue;

        // If the line starts an entry, begin a new entry string
        if (line.find("{") != string::npos && !insideEntry) {
            insideEntry = true;
            entry = line; // Start concatenating the entry
        } 
        else if (insideEntry) {
            entry += line; // Continue concatenating the entry until we find the closing brace
        }

        // When we reach the end of the entry (closing brace found), process it
        if (insideEntry && line.find("}") != string::npos) {
            // Validate braces using a simple counter
            int braceCount = 0;
            bool bracesValid = true;
            for (char c : entry) {
                if (c == '{') braceCount++;
                else if (c == '}') braceCount--;
                if (braceCount < 0) {
                    bracesValid = false;
                    break;
                }
            }

            // If the braces are not balanced, report the error
            if (!bracesValid || braceCount != 0) {
                cerr << "Error: Mismatched braces in entry: " << entry << endl;
                throw runtime_error("Mismatched braces in entry");
            }

            // Extract fields from the entry
            try {
                string title, venue, doi;
                int year = 0;
                vector<string> authors;
                bool instituteAffiliation = false;

                // Extract title
                size_t pos = entry.find("title={");
                if (pos != string::npos) {
                    title = entry.substr(pos + 7, entry.find('}', pos) - pos - 7);
                }

                // Extract venue (check both venue and journal for different entry types)
                pos = entry.find("venue={");
                if (pos != string::npos) {
                    venue = entry.substr(pos + 7, entry.find('}', pos) - pos - 7);
                } else {
                    pos = entry.find("journal={");
                    if (pos != string::npos) {
                        venue = entry.substr(pos + 8, entry.find('}', pos) - pos - 8);
                    }
                }

                // Extract year
                pos = entry.find("year={");
                if (pos != string::npos) {
                    year = stoi(entry.substr(pos + 6, entry.find('}', pos) - pos - 6));
                }

                // Extract authors
                pos = entry.find("author={");
                if (pos != string::npos) {
                    string authorsStr = entry.substr(pos + 8, entry.find('}', pos) - pos - 8);
                    stringstream ss(authorsStr);
                    string author;
                    set<string> uniqueAuthors; // To check for duplicates
                    while (getline(ss, author, ',')) {
                        author = author.substr(author.find_first_not_of(" "), author.find_last_not_of(" ") + 1);
                        
                        // Check if the author belongs to the institute (look for "(IIIT-Delhi)")
                        if (author.find("(IIIT-Delhi)") != string::npos) {
                            instituteAffiliation = true;
                            author = author.substr(0, author.find(" (")); // Remove affiliation annotation
                        }
                        
                        // Insert unique authors
                        if (!uniqueAuthors.insert(author).second) {
                            cerr << "Warning: Duplicate author detected: " << author << endl;
                        }
                        authors.push_back(author);
                    }
                }

                // Validate institute affiliation
                if (!instituteAffiliation) {
                    cerr << "Warning: No author is affiliated with IIIT-Delhi in entry: " << entry << endl;
                }

                // Extract DOI (optional field)
                pos = entry.find("doi={");
                if (pos != string::npos) {
                    doi = entry.substr(pos + 5, entry.find('}', pos) - pos - 5);
                }

                // Add the publication to all authors
                Publication pub{title, venue, year, authors};
                for (const auto& author : authors) {
                    authorPublications[author].push_back(pub);
                }

            } catch (const exception& e) {
                cerr << "Error parsing entry: " << e.what() << endl;
                cerr << "Entry: " << entry << endl;
                throw;
            }

            // Clear for next entry
            entry.clear();
            insideEntry = false; // Reset the flag
        }
    }
    return authorPublications;
}



// Search publications by author name
void searchPublications(const map<string, vector<Publication>>& authorPublications, const string& author) {
    auto it = authorPublications.find(author);
    if (it == authorPublications.end()) {
        cout << "No publications found for author: " << author << endl;
        return;
    }

    cout << "Publications for " << author << ":" << endl;
    for (const auto& pub : it->second) {
        pub.display();
        cout << "--------------------------------------" << endl;
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            cerr << "Usage: " << argv[0] << " <author_name1> [<author_name2> ...]" << endl;
            return 1;
        }

        // Load faculty list
        string facultyFile = "faculty.csv";
        set<string> faculty = loadFaculty(facultyFile);

        // Parse .bib file
        string bibFile;
        cout << "Enter the path of the .bib file: ";
        cin >> bibFile;
        map<string, vector<Publication>> authorPublications = parseBibFile(bibFile, faculty);

        // Process each author name provided as input
        for (int i = 1; i < argc; ++i) {
            string authorName = argv[i];
            auto it = authorPublications.find(authorName);

            // Check if the author has publications
            if (it == authorPublications.end()) {
                cout << "No publications found for author: " << authorName << endl;
                continue;
            }

            // Display publications
            cout << "Publications for " << authorName << ":" << endl;
            double totalCoAuthors = 0;
            int paperCount = 0;
            for (const auto& pub : it->second) {
                pub.display();
                totalCoAuthors += pub.authors.size() - 1; // Exclude the author themselves
                paperCount++;
                cout << "--------------------------------------" << endl;
            }

            // Calculate and display average number of co-authors
            double averageCoAuthors = (paperCount > 0) ? totalCoAuthors / paperCount : 0;
            cout << "Average number of co-authors per paper for " << authorName << ": " 
                 << averageCoAuthors << endl;
            cout << "=======================================" << endl;
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
