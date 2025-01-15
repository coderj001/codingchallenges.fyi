#ifndef WC_H
#define WC_H
#include <string>

using namespace std;

// Function: returns No's of bytes in a file
int bytesInFile(const string &filename);
// Function: returns No's of lines in a file
int linesInFile(const string &filename);
// Function: returns No's of words in a file
int wordsInFile(const string &filename);
// Function: returns No's of characters in a file
int charactersInFile(const string &filename);

#endif // !WC_H
