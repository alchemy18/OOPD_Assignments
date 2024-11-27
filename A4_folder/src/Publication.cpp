#include "Publication.h"

// Constructor to initialize the publication with title, venue, authors, year, and optionally DOI
Publication::Publication(const std::string& title, const std::string& venue, const std::vector<Author>& authors, int year, const std::string& doi)
    : title(title), venue(venue), authors(authors), year(year), doi(doi) {}

// Getter methods
std::string Publication::getTitle() const {
    return title;
}

std::string Publication::getVenue() const {
    return venue;
}

std::vector<Author> Publication::getAuthors() const {
    return authors;
}

int Publication::getYear() const {
    return year;
}

std::string Publication::getDOI() const {
    return doi;
}
