#include <iostream>

#include "../include/FileReader.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: No filename provided." << endl;
    return 1;
  }

  try {
    FileReader reader(argv[argc - 1]);
    auto freqs = reader.getFrequencies();
    cout << "X: " << freqs['X'] << endl;
    cout << "t: " << freqs['t'] << endl;
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    return 1;
  }

  return 0;
}
