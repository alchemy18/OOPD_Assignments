#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Function to check if a string is numeric
bool isNumeric(const string &str);

// Function to split a CSV line into fields based on commas
void splitCSVLine(const string &line, string fields[], int fieldCount);

// Function to split a line into fields (default behavior is to split by new line)
void splitLine(const string &line, string fields[], int fieldCount);

// Function to split a string into fields based on commas
void splitString(const string &input, string fields[], int fieldCount);

// Function to validate a username (only allows alphabetic characters and spaces)
bool isValidUserName(const string &userName);

// Function to get a specific field from a CSV line by index
string getField(const string &line, int fieldIndex);

#endif // FUNCTIONS_H
