#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &s, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(s);
  while (getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " -f list [-d delimiter] [file...]" << endl;
    return 1;
  }

  vector<int> feilds;
  vector<string> files;
  char delimiter = '\t';

  for (int i = 1; i < argc; ++i) {
    string arg = argv[i];
    if (arg == "-f") {
      string feildList = argv[++i];
      istringstream iss(feildList);
      int feild;
      while (iss >> feild) {
        feilds.push_back(feild);
        if (iss.peek() == ',') {
          iss.ignore();
        }
      }
    } else if (arg == "-d") {
      delimiter = argv[++i][0];
    } else {
      files.push_back(arg);
    }

    // Process each files
    for (const auto &file : files) {
      ifstream infile(file);
      if (!infile.is_open()) {
        cerr << "Error: Could not open file " << file << endl;
        continue;
      }

      string line;
      while (getline(infile, line)) {
        vector<string> tokens = split(line, delimiter);
        for (size_t i = 0; i < feilds.size(); ++i) {
          if (feilds[i] <= tokens.size()) {
            cout << tokens[feilds[i]] << endl;
          }
          if (i < feilds.size() - 1) {
            cout << delimiter;
          }
        }
      }

      infile.close();
    }
  }

  return 0;
}
