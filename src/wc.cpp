#include <codecvt>
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
  infile.close();

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
  infile.close();

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
  infile.close();

  cout << num_of_words << " " << filename << endl;
}

void charactersInFile(const string &filename) {
  wifstream infile(filename);
  infile.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

  if (!infile.is_open()) {
    cerr << "Error: Unable to open the file." << endl;
    return;
  }

  wchar_t ch;
  int num_of_characters = 0;

  while (infile.get(ch)) {
    num_of_characters++;
  }

  infile.close();

  cout << num_of_characters << " " << filename << endl;
}

