// #ifndef USER_H // Include guard to prevent multiple inclusions
// #define USER_H

// #include <ctime>
// #include <iostream>
// #include <iomanip> 
// #include <sstream> 
// #include <string>   

// using namespace std;

// // Forward declaration of dependent classes
// class Book;
// class PublicationRank;
// class Journals;

// class User {
// private:
//     string name;                                // User's name
//     bool isTeacher;                             // Indicates if the user is a teacher
//     static const int MAX_BORROWED_BOOKS = 3;  // Maximum number of books a user can borrow
//     int borrowedCount;                          // Current count of borrowed books

// public:
//     Book* borrowedBooks[MAX_BORROWED_BOOKS];         // Array to store borrowed Book pointers
//     PublicationRank* borrowedbooks[MAX_BORROWED_BOOKS]; // Array to store borrowed PublicationRank pointers
//     Journals* borrowedJournals[MAX_BORROWED_BOOKS]; // Array to store borrowed Journals pointers
//     time_t borrowedDates[MAX_BORROWED_BOOKS];        // Array to store the dates when books were borrowed

//     // Default constructor
//     User() : name(""), isTeacher(false), borrowedCount(0) {
//         for (int i = 0; i < MAX_BORROWED_BOOKS; ++i) {
//             borrowedBooks[i] = nullptr;
//             borrowedbooks[i] = nullptr; // Initialize borrowedbooks array
//             borrowedJournals[i] = nullptr; // Initialize borrowedJournals array
//             borrowedDates[i] = 0; // Initialize borrowedDates array
//         }
//     }

//     // Parameterized constructor
//     User(const string& name, bool isTeacher) : name(name), isTeacher(isTeacher), borrowedCount(0) {
//         for (int i = 0; i < MAX_BORROWED_BOOKS; ++i) {
//             borrowedBooks[i] = nullptr;
//             borrowedbooks[i] = nullptr; // Initialize borrowedbooks array
//             borrowedJournals[i] = nullptr; // Initialize borrowedJournals array
//             borrowedDates[i] = 0; // Initialize borrowedDates array
//         }
//     }

//     // Getter for user's name
//     string getName() const {
//         return name;
//     }

//     // Check if the user is a teacher
//     bool isTeacherUser() const {
//         return isTeacher;
//     }

//     // Get the current count of borrowed books
//     int getBorrowedCount() const {
//         return borrowedCount;
//     }

//     // Get the maximum number of books that can be borrowed
//     int getMaxBorrowedBooks() const {
//         return MAX_BORROWED_BOOKS;
//     }

//     // Increment the count of borrowed books
//     void incrementBorrowedCount() {
//         borrowedCount++;
//     }

//     // Check if a specific book is currently borrowed by the user
//     bool isBookBorrowed(Book* book) const {
//         for (int i = 0; i < MAX_BORROWED_BOOKS; ++i) {
//             if (borrowedBooks[i] == book) {
//                 return true;
//             }
//         }
//         return false;
//     }

//     // Check if the user can borrow more books
//     bool canBorrowMoreBooks() const {
//         return getBorrowedCount() < MAX_BORROWED_BOOKS;
//     }

//     // Get the last borrow time for a specific book
//     time_t getLastBorrowTime(const Book* book) const {
//         for (int i = 0; i < MAX_BORROWED_BOOKS; ++i) {
//             if (borrowedBooks[i] == book) {
//                 return borrowedDates[i];
//             }
//         }
//         return 0; // Return 0 if the book is not found in the user's borrowed books
//     }

//     // Set the last borrow time for a specific book
//     void setLastBorrowTime(const Book* book, time_t borrowTime) {
//         for (int i = 0; i < MAX_BORROWED_BOOKS; ++i) {
//             if (borrowedBooks[i] == book) {
//                 borrowedDates[i] = borrowTime;
//                 return; // Book found and last borrow time updated
//             }
//         }
//     }

//     // Get the last borrow time for a specific publication
//     time_t getLastBorrowPubTime(const PublicationRank* publicationRank) const {
//         for (int i = 0; i < MAX_BORROWED_BOOKS; ++i) {
//             if (borrowedbooks[i] == publicationRank) {
//                 return borrowedDates[i];
//             }
//         }
//         return 0; // Return 0 if the publication is not found in the user's borrowed publications
//     }

//     // Set the last borrow time for a specific publication
//     void setLastBorrowPubTime(const PublicationRank* publicationRank, time_t borrowTime) {
//         for (int i = 0; i < MAX_BORROWED_BOOKS; ++i) {
//             if (borrowedbooks[i] == publicationRank) {
//                 borrowedDates[i] = borrowTime;
//                 return; // Publication found and last borrow time updated
//             }
//         }
//     }
// };

// #endif // USER_H