#ifndef JOURNALS_H
#define JOURNALS_H

#include <iostream>
#include <string>
#include "LibraryItem.h"

using namespace std;

class Journals : public LibraryItem
{
private:
    int ID;            // Unique ID for the journal
    string title;      // Title of the journal

public:
    /**
     * @brief Constructor for the Journals class.
     * @param ID The unique ID of the journal.
     * @param title The title of the journal.
     */
    Journals(int ID, const string &title);

    /**
     * @brief Gets the unique ID of the journal.
     * @return The unique ID of the journal.
     */
    int getID() const;

    /**
     * @brief Gets the title of the journal.
     * @return The title of the journal.
     */
    string getTitle() const;

    /**
     * @brief Prints the details of the journal.
     *        Overrides the printDetails method in LibraryItem.
     */
    void printDetails() const override;
};

#endif // JOURNALS_H
