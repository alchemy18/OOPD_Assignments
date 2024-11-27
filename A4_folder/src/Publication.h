#ifndef PUBLICATION_H
#define PUBLICATION_H

#include "Author.h"
#include <string>
#include <vector>

class Publication {
private:
    std::string title;
    std::string venue;
    std::vector<Author> authors;
    int year;
    std::string doi;

public:
    // Constructor
    Publication(const std::string& title, const std::string& venue, const std::vector<Author>& authors, int year, const std::string& doi = "");

    // Getter methods
    std::string getTitle() const;
    std::string getVenue() const;
    std::vector<Author> getAuthors() const;
    int getYear() const;
    std::string getDOI() const;
};

#endif // PUBLICATION_H
