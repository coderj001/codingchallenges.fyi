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
    // cout << "Output number of bytes in the file. " << filename;
    bytesInFile(filename);
  } else if (command == "-l") {
    filename = argv[2];
    cout << "Output number of lines in the file. " << filename;
  } else if (command == "-w") {
    filename = argv[2];
    cout << "Output number of words in the file. " << filename;
  } else if (command == "-m") {
    filename = argv[2];
    cout << "Output number of characters in the file. " << filename;
  } else {
    cout << "Output number of characters in the file. " << command;
  }

  return 0;
}
