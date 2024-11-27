#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

class Author {
private:
    std::string name;
    std::string affiliation;

public:
    // Constructor
    Author(const std::string& name, const std::string& affiliation);

    // Getter methods
    std::string getName() const;
    std::string getAffiliation() const;
};

#endif // AUTHOR_H

