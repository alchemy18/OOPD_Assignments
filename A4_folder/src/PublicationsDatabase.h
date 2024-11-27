#ifndef PUBLICATIONS_DATABASE_H
#define PUBLICATIONS_DATABASE_H

#include "Publication.h"
#include "Author.h"
#include <vector>
#include <string>
#include <map>
#include <set>

// PublicationsDatabase class definition
class PublicationsDatabase {
public:
    // Constructor
    PublicationsDatabase() {}

    // Method to parse the BibTeX file and map publications by authors
    void parseBibFile(const std::string& filePath, const std::string& institute);

    // Method to get publications for a given author
    std::vector<Publication> getPublicationsByAuthor(const std::string& authorName) const;

    // Method to parse faculty CSV and return a list of Author objects
    std::vector<Author> parseFacultyCSV(const std::string& filePath);

    // Helper method to clean author names (remove affiliation info like "(IIIT-Delhi)")
    std::string cleanAuthorName(const std::string& author);

    // Method to add a publication to the database
    void addPublication(const Publication& publication);

private:
    // The map that stores publications by author names
    std::map<std::string, std::vector<Publication>> authorPublications;

    // Helper method to validate and process BibTeX entries
    void validateBibEntry(const std::string& entry, const std::string& institute);
};

#endif // PUBLICATIONS_DATABASE_H
