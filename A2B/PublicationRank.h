#ifndef PUBLICATIONRANK_H
#define PUBLICATIONRANK_H

#include <iostream>
#include <iomanip> 
#include <sstream> 
#include <string>   
#include "LibraryItem.h"

using namespace std;

class PublicationRank : public LibraryItem
{
private:
    int ID;                          // Unique ID for the publication
    string publication;              // Name of the publication
    int rank;                        // Rank of the publication
    double totalPaid;                // Total amount paid for the publication
    bool borrowed;                   // Status indicating whether the publication is borrowed

public:
    /**
     * @brief Constructor for the PublicationRank class.
     * @param ID The unique ID of the publication.
     * @param publication The name of the publication.
     * @param rank The rank of the publication.
     * @param totalPaid The total amount paid for the publication.
     */
    PublicationRank(int ID, const string &publication, int rank, double totalPaid);

    /**
     * @brief Gets the unique ID of the publication.
     * @return The unique ID of the publication.
     */
    int getID() const;

    /**
     * @brief Gets the name of the publication.
     * @return The name of the publication.
     */
    string getPublication() const;

    /**
     * @brief Gets the rank of the publication.
     * @return The rank of the publication.
     */
    int getrank() const;

    /**
     * @brief Gets the total amount paid for the publication.
     * @return The total amount paid.
     */
    double gettotalPaid() const;

    /**
     * @brief Checks if the publication is currently borrowed.
     * @return True if the publication is borrowed, false otherwise.
     */
    bool isBorrowed() const;

    /**
     * @brief Sets the borrowed status of the publication.
     * @param status The borrowed status to set (true for borrowed, false for available).
     */
    void setBorrowed(bool status);

    /**
     * @brief Prints the details of the publication.
     *        Overrides the printDetails method in LibraryItem.
     */
    void printDetails() const override;
};

#endif // PUBLICATIONRANK_H
