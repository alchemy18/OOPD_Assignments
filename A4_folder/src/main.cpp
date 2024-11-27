#include "PublicationsDatabase.h"
#include "Author.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]) {
    // Create a PublicationsDatabase instance
    PublicationsDatabase database;

    // Get file paths from user
    std::string bibFilePath, facultyFilePath;
    std::cout << "Enter the path to the BibTeX file: ";
    std::getline(std::cin, bibFilePath);

    std::cout << "Enter the path to the Faculty CSV file: ";
    std::getline(std::cin, facultyFilePath);

    // Parse the faculty CSV file
    std::vector<Author> faculty = database.parseFacultyCSV(facultyFilePath);

    // Print the list of authors
    std::cout << "\nList of Faculty Authors:" << std::endl;
    for (const auto& author : faculty) {
        std::cout << "Name: " << author.getName() << ", Affiliation: " << author.getAffiliation() << std::endl;
    }

    // Parse the BibTeX file to populate the publication database
    try {
        database.parseBibFile(bibFilePath, "IIIT-Delhi");

        // Process command-line arguments for author names
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <author_name1> [<author_name2> ...]" << std::endl;
            return 1;
        }

        // Iterate over the authors provided via command-line arguments
        for (int i = 1; i < argc; ++i) {
            std::string authorName = argv[i];
            authorName = database.cleanAuthorName(authorName); // Call the clean function from PublicationsDatabase

            auto publications = database.getPublicationsByAuthor(authorName);
            std::cout << "\nPublications for " << authorName << ":\n";
            if (publications.empty()) {
                std::cout << "No publications found for this author." << std::endl;
            } else {
                for (const auto& publication : publications) {
                    std::cout << publication.getTitle() << ", "
                              << publication.getVenue() << ", "
                              << publication.getYear() << std::endl;
                }

                // Calculate the average number of co-authors for each paper by this author
                int totalCoAuthors = 0;
                for (const auto& publication : publications) {
                    int numCoAuthors = publication.getAuthors().size() - 1; // Exclude the author themselves
                    totalCoAuthors += numCoAuthors;
                }

                if (!publications.empty()) {
                    double averageCoAuthors = static_cast<double>(totalCoAuthors) / publications.size();
                    std::cout << "Average number of co-authors: " << averageCoAuthors << std::endl;
                }
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
