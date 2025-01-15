#include <iostream>
#include <string>

#include "../include/wc.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: No command provided." << endl;
    return 1;
  }

  string filename;
  if (argc == 2) {
    filename = argv[1];
    cout << "  " << linesInFile(filename) << " " << wordsInFile(filename) << " "
         << bytesInFile(filename) << " " << filename << endl;
    return 0;
  }

  int i = 1;
  filename = argv[argc - 1];
  while (i < argc - 1) {
    string command = argv[i];
    if (command == "-c") {
      cout << bytesInFile(filename) << " ";
    } else if (command == "-l") {
      cout << linesInFile(filename) << " ";
    } else if (command == "-w") {
      cout << wordsInFile(filename) << " ";
    } else if (command == "-m") {
      cout << charactersInFile(filename) << " ";
    }
    i++;
  }
  cout << filename << endl;

  return 0;
}
