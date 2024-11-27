#include "Author.h"

// Constructor to initialize the author's name and affiliation
Author::Author(const std::string& name, const std::string& affiliation)
    : name(name), affiliation(affiliation) {}

// Getter for name
std::string Author::getName() const {
    return name;
}

// Getter for affiliation
std::string Author::getAffiliation() const {
    return affiliation;
}
