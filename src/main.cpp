#include <iostream>
#include <string>

#include "../include/wc.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: No command provided." << endl;
    return 1;
  }

  string command = argv[1];
  string filename;

  if (command == "-c") {
    filename = argv[2];
    cout << bytesInFile(filename) << " " << filename;
  } else if (command == "-l") {
    filename = argv[2];
    cout << linesInFile(filename) << " " << filename;
  } else if (command == "-w") {
    filename = argv[2];
    cout << wordsInFile(filename) << " " << filename;
  } else if (command == "-m") {
    filename = argv[2];
    cout << charactersInFile(filename) << " " << filename;
  } else {
    filename = argv[1];
    cout << "  " << linesInFile(filename) << " " << wordsInFile(filename) << " "
         << bytesInFile(filename) << " " << filename;
  }

  cout << endl;

  return 0;
}
