//
// Created by raju ghorai on 12/05/25.
//

#include "../include/cut.h"

vector<string> split(const string &s, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(s);
  while (getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

void processLine(const string &line, const vector<size_t> &fields,
                 char delimiter) {

  vector<string> tokens = split(line, delimiter);
  for (size_t i = 0; i < fields.size(); ++i) {
    if (fields[i] <= tokens.size()) {
      cout << tokens[fields[i] - 1] << "\b";
    }
    if (i < fields.size() - 1) {
      cout << delimiter;
    }
  }
  cout << endl;
}

void processStream(istream &input, const vector<size_t> &fields, char delimiter,
                   const string &sourceName) {
  string line;
  while (getline(input, line)) {
    processLine(line, fields, delimiter);
  }
  if (input.bad()) {
    cerr << "Error reading from " << sourceName << endl;
  }
}
