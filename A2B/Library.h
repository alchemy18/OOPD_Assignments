// #ifndef LIBRARY_H
// #define LIBRARY_H

// #include <iostream>
// #include "LibraryItem.h"
// #include "User.cpp"
// #include "Book.h"
// #include "PublicationRank.h"

// using namespace std;

// const int MAX_ITEMS = 1000;  // Maximum number of items the library can hold

// class Library
// {
// private:
//     LibraryItem *libraryItems[MAX_ITEMS];  // Array of pointers to library items
//     int itemCount;                         // Number of items in the library
//     int nextBookId;                        // ID to assign to the next book added
//     int totalCopies;                       // Total number of copies of books
    
//     User students[100];                    // Array to store student users (max 100)
//     int studentCount;                      // Current number of students

//     User teachers[50];                     // Array to store teacher users (max 50)
//     int teacherCount;                      // Current number of teachers

// public:
//     /**
//      * @brief Default constructor initializes the library with no items or users.
//      */
//     Library();

//     // Accessor methods for retrieving the number of students, teachers, and total users
//     int getStudentCount() const;
//     int getTeacherCount() const;
//     int getTotalUsers() const;
//     int getTotalItems() const;

//     // Method to add an item (book, journal, publication) to the library
//     void addItem(LibraryItem *item);

//     // Method to print the details of all items in the library
//     void printAllItems() const;

//     // Methods to search and retrieve books by ID or ISBN
//     Book *getBookByID(int bookID) const;
//     Book *getBookByIsbn(int bookIsbn) const;

//     // Methods to search for books, journals, and publications by various attributes
//     void searchBooksByAuthor(const string &bookAuthor, Book *matchingBooks[], int &matchingCount);
//     void searchBooksByTitle(const string &bookAuthor, Book *matchingBooks[], int &matchingCount);
//     void searchPublication(const string &bookAuthor, PublicationRank *matchingBooks[], int &matchingCount);
//     void searchJournal(const string &bookAuthor, Journals *matchingBooks[], int &matchingCount);

//     // Method to register a new user (student or teacher) in the library
//     void registerUser(const string &name, bool isTeacher);

//     // Method to display all registered users
//     void showAllRegisteredUsers();

//     // Utility methods for case-insensitive string comparison
//     bool isEqualIgnoreCase(const string &str1, const string &str2);
//     bool isEqualIgnore(const string &str1, const string &str2);

//     // Method to add a new book to the library
//     void addBook(int isbn, const string &author, const string &title, int originalPublicationYear);

//     // Methods to manage borrowing and returning books, publications, and journals
//     bool borrowBook(const string &userName, int bookIdToBorrow);
//     bool returnBook(Book *book);
//     bool borrowPublication(const string &userName, int publication);
//     bool returnPub(PublicationRank *publicationRank);
//     bool borrowJournal(const string &userName, int title);

//     // Virtual destructor
//     virtual ~Library();
// };

// #endif // LIBRARY_H
