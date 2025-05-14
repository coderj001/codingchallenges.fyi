#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/cut.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " -f list [-d delimiter] [file...]" << endl;
    return 1;
  }

  vector<size_t> fields;
  vector<string> files;
  char delimiter = '\t';

  for (int i = 1; i < argc; ++i) {
    string arg = argv[i];
    if (arg == "-f") {
      string feildList = argv[++i];
      istringstream iss(feildList);
      int feild;
      while (iss >> feild) {
        fields.push_back(feild);
        if (iss.peek() == ',') {
          iss.ignore();
        }
      }
    } else if (arg == "-d") {
      delimiter = argv[++i][0];
    } else {
      files.push_back(arg);
    }
  }

  if (files.empty()) {
    processStream(cin, fields, delimiter);
  } else {
    for (const auto &file : files) {
      ifstream infile(file);
      if (!infile.is_open()) {
        cerr << "Error: Could not open file " << file << endl;
        continue;
      }
      processStream(infile, fields, delimiter, file);

      infile.close();
    }
  }

  return 0;
}
