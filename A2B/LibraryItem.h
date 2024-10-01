#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H
#include <iostream>
#include <iomanip> 
#include <sstream> 
#include <string>   

using namespace std;

class LibraryItem
{
public:
    virtual void printDetails() const;
    virtual ~LibraryItem() {}
};

#endif // LIBRARYITEM_H