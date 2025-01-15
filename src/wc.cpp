#include <codecvt>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int bytesInFile(const string &filename) {
  ifstream infile(filename);
  if (!infile.is_open()) {
    cerr << "Error: Opening the file." << endl;
    return 1;
  }

  string s;
  int num_of_bytes = 0;

  while (getline(infile, s)) {
    num_of_bytes += s.length() + 1;
  }
  infile.close();

  return num_of_bytes;
}

int linesInFile(const string &filename) {
  wifstream infile(filename);
  infile.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
  if (!infile.is_open()) {
    cerr << "Error: Opening the file." << endl;
    return 1;
  }

  wstring s;
  int num_of_lines = 0;

  while (getline(infile, s)) {
    num_of_lines += 1;
  }
  infile.close();

  return num_of_lines;
}

int wordsInFile(const string &filename) {
  wifstream infile(filename);
  infile.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
  if (!infile.is_open()) {
    cerr << "Error: Opening the file." << endl;
    return -1;
  }

  wstring word;
  int num_of_words = 0;

  while (infile >> word) {
    num_of_words++;
  }
  infile.close();

  return num_of_words;
}

int charactersInFile(const string &filename) {
  wifstream infile(filename);
  infile.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

  if (!infile.is_open()) {
    cerr << "Error: Unable to open the file." << endl;
    return 1;
  }

  wchar_t ch;
  int num_of_characters = 0;

  while (infile.get(ch)) {
    num_of_characters++;
  }

  infile.close();

  return num_of_characters;
}
