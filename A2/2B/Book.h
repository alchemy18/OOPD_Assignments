#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include "LibraryItem.h"

using namespace std;

class Book : public LibraryItem
{
private:
    int ID;                           // Unique ID for the book object
    int book_id;                      // Unique book identifier within the library
    int isbn;                         // ISBN number of the book
    string title;                     // Title of the book
    string authors;                   // Authors of the book
    int original_publication_year;    // Year of the book's original publication
    bool borrowed;                    // Status indicating whether the book is borrowed

public:
    /**
     * @brief Default constructor for the Book class.
     *        Initializes the book with default values.
     */
    Book();

    /**
     * @brief Parameterized constructor for the Book class.
     * @param ID The unique ID of the book object.
     * @param book_id The library-specific ID for the book.
     * @param isbn The ISBN number of the book.
     * @param title The title of the book.
     * @param authors The authors of the book.
     * @param original_publication_year The year the book was originally published.
     */
    Book(int ID, int book_id, int isbn, const string &title, const string &authors, int original_publication_year);

    // Getter and setter functions

    /**
     * @brief Gets the unique ID of the book object.
     * @return The unique ID of the book object.
     */
    // int getID() const;

    int getID() const { return ID; }
    void setID(int ID) { this->ID = ID; }

    /**
     * @brief Sets the unique ID of the book object.
     * @param id The unique ID to set.
     */
    // void setID(int id);

    /**
     * @brief Gets the library-specific book ID.
     * @return The book's library-specific ID.
     */
    int getBookID() const;

    /**
     * @brief Sets the library-specific book ID.
     * @param bookid The book ID to set.
     */
    void setBookID(int bookid);

    /**
     * @brief Gets the ISBN number of the book.
     * @return The ISBN number.
     */
    int getISBN() const;

    /**
     * @brief Sets the ISBN number of the book.
     * @param Isbn The ISBN number to set.
     */
    void setISBN(int Isbn);

    /**
     * @brief Gets the title of the book.
     * @return The title of the book.
     */
    string getTitle() const;

    /**
     * @brief Sets the title of the book.
     * @param newTitle The title to set.
     */
    void setTitle(const string &newTitle);

    /**
     * @brief Gets the authors of the book.
     * @return The authors of the book.
     */
    string getAuthors() const;

    /**
     * @brief Sets the authors of the book.
     * @param newAuthor The authors to set.
     */
    void setAuthors(const string &newAuthor);

    /**
     * @brief Gets the original publication year of the book.
     * @return The original publication year.
     */
    int getPublicationYear() const;

    /**
     * @brief Sets the original publication year of the book.
     * @param year The year to set.
     */
    void setPublicationYear(int year);

    /**
     * @brief Checks if the book is currently borrowed.
     * @return True if the book is borrowed, false otherwise.
     */
    bool isBorrowed() const;

    /**
     * @brief Sets the borrowed status of the book.
     * @param status The borrowed status to set (true for borrowed, false for available).
     */
    void setBorrowed(bool status);

    /**
     * @brief Prints the details of the book.
     *        Overrides the printDetails method in LibraryItem.
     */
    void printDetails() const override;
};

#endif // BOOK_H
