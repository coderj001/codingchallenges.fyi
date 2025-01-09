#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: No command provided." << endl;
    return 1;
  }

  string command = argv[1];
  cout << command;
  return 0;
}
