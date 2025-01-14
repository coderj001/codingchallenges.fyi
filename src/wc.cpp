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
    num_of_bytes += s.length() + 1; // for `\n`
  }

  cout << num_of_bytes << " " << filename << endl;
}

void linesInFile(const string &filename) {
  ifstream infile(filename);
  if (!infile.is_open()) {
    cerr << "Error: Opening the file." << endl;
  }

  string s;
  int num_of_lines = 0;

  while (getline(infile, s)) {
    num_of_lines += 1;
  }

  cout << num_of_lines << " " << filename << endl;
}

void wordsInFile(const string &filename) {
  ifstream infile(filename);
  if (!infile.is_open()) {
    cerr << "Error: Opening the file." << endl;
  }

  string s;
  int num_of_words = 0;

  while (getline(infile, s)) {
    for (char c : s) {
      if (c == ' ' || c == '\n') {
        num_of_words++;
      }
    }
  }

  cout << num_of_words << " " << filename << endl;
}
