#ifndef WC_H
#define WC_H
#include <string>

using namespace std;

// Function: No's of bytes in a file
int bytesInFile(const string& filename);
int linesInFile(const string& filename);
int wordsInFile(const string& filename);
int charactersInFile(const string& filename);

#endif // !WC_H
