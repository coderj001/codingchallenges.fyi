#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void bytesInFile(const string &filename) {
  ifstream infile(filename);
  if (!infile.is_open()) {
    cerr << "Error: Opening the file." << endl;
  }

  string s;
  int num_of_bytes = 0;

  while (getline(infile, s)) {
    for (char byte : s) {
      if (byte == '\n') {
        num_of_bytes += 2;
      } else {
        num_of_bytes += 1;
      }
    }
  }

  cout << num_of_bytes << " " << filename << endl;
}
