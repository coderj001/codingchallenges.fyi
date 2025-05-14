//
// Created by raju ghorai on 12/05/25.
//

#ifndef CUT_H
#define CUT_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &s, char delimiter);
void processLine(const string &line, const vector<size_t> &fields,
                 char delimiter);
void processStream(istream &input, const vector<size_t> &fields, char delimiter,
                   const string &sourceName = "stdin");

#endif // CUT_H
