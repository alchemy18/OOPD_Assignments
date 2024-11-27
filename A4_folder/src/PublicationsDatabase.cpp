#include "PublicationsDatabase.h"
#include "Publication.h"
#include "Author.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>
#include <iostream>
#include <set> 
#include <vector>
#include <string>

// Helper function to clean author names by removing affiliations (e.g., "(IIIT-Delhi)")
std::string PublicationsDatabase::cleanAuthorName(const std::string& author) {
    // Find and remove the affiliation part enclosed in parentheses
    size_t pos = author.find("(");
    if (pos != std::string::npos) {
        return author.substr(0, pos);  // Return only the name before the "("
    }
    return author;
}

void PublicationsDatabase::addPublication(const Publication& publication) {
    for (const auto& author : publication.getAuthors()) {
        std::string cleanedAuthor = cleanAuthorName(author.getName());
        // Add the publication to the map under the cleaned author name
        authorPublications[cleanedAuthor].push_back(publication);
    }
}

std::vector<Publication> PublicationsDatabase::getPublicationsByAuthor(const std::string& authorName) const {
    // Search for the author in the map and return the associated publications
    auto it = authorPublications.find(authorName);
    if (it != authorPublications.end()) {
        return it->second;  // Return the publications for the found author
    }
    return {};  // Return an empty vector if no publications found for the author
}

void PublicationsDatabase::parseBibFile(const std::string& filePath, const std::string& institute) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open the BibTeX file.");
    }

    std::string line;
    std::string currentEntry;
    while (std::getline(file, line)) {
        // Detect the start of a new entry
        if (line.find("@") != std::string::npos && !currentEntry.empty()) {
            // Process the last entry
            validateBibEntry(currentEntry, institute);
            currentEntry.clear();
        }
        currentEntry += line + "\n";
    }

    // Process the last entry in the file
    if (!currentEntry.empty()) {
        validateBibEntry(currentEntry, institute);
    }
}

void PublicationsDatabase::validateBibEntry(const std::string& entry, const std::string& institute) {
    std::regex authorRegex("author\\s*=\\s*\\{([^}]+)\\}");
    std::regex titleRegex("title\\s*=\\s*\\{([^}]+)\\}");
    std::regex yearRegex("year\\s*=\\s*\\{([^}]+)\\}");
    std::regex venueRegex("journal|booktitle\\s*=\\s*\\{([^}]+)\\}");

    std::smatch match;
    if (!std::regex_search(entry, match, authorRegex)) {
        throw std::runtime_error("Invalid BibTeX entry: Missing authors.");
    }

    // Extract authors
    std::string authorList = match[1].str();
    std::vector<std::string> authors;
    std::stringstream authorStream(authorList);
    std::string author;
    while (std::getline(authorStream, author, ',')) {
        authors.push_back(author);
    }

    // Check for duplicate authors
    std::set<std::string> authorSet(authors.begin(), authors.end());
    if (authorSet.size() != authors.size()) {
        throw std::runtime_error("Invalid BibTeX entry: Duplicate authors detected.");
    }

    // Check for at least one author from the institute
    bool hasInstituteAuthor = false;
    for (const auto& authorName : authors) {
        if (authorName.find(institute) != std::string::npos) {
            hasInstituteAuthor = true;
            break;
        }
    }
    if (!hasInstituteAuthor) {
        throw std::runtime_error("Invalid BibTeX entry: No author from the institute.");
    }

    // Extract other details (title, year, venue)
    std::string title, venue, year;
    if (std::regex_search(entry, match, titleRegex)) {
        title = match[1].str();
    } else {
        throw std::runtime_error("Invalid BibTeX entry: Missing title.");
    }

    if (std::regex_search(entry, match, venueRegex)) {
        venue = match[1].str();
    }

    if (std::regex_search(entry, match, yearRegex)) {
        year = match[1].str();
    } else {
        throw std::runtime_error("Invalid BibTeX entry: Missing year.");
    }

    // Create Author objects and add to the publication
    std::vector<Author> authorObjects;
    for (const auto& authorName : authors) {
        // Assuming we have an empty affiliation string for simplicity
        authorObjects.push_back(Author(authorName, ""));
    }

    // Create the publication
    Publication publication(title, venue, authorObjects, std::stoi(year));

    // Add the publication to the database
    addPublication(publication);
}

std::vector<Author> PublicationsDatabase::parseFacultyCSV(const std::string& filePath) {
    std::vector<Author> authors;
    std::ifstream file(filePath);
    std::string line;
    std::getline(file, line);  // Skip the header line

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, affiliation;
        std::getline(ss, name, ',');
        std::getline(ss, affiliation, ',');
        
        // Create an Author object and add it to the authors list
        authors.push_back(Author(name, affiliation));
    }

    return authors;
}
