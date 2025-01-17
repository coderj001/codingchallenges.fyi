#include <bits/stdc++.h>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using namespace std;

// datatype

class JSONValue {
public:
  virtual ~JSONValue() = default;
};

class JSONNull : public JSONValue {
public:
  void print() const { cout << "null"; }
};

class JSONString : public JSONValue {
public:
  string value;
  void print() const { cout << "\"" << value << "\""; }
};

class JSONNumber : public JSONValue {
public:
  double value;
  void print() const { cout << value; }
};

class JSONBoolean : public JSONValue {
public:
  bool value;
  void print() const { cout << (value ? "true" : "false"); }
};

class JSONArray : public JSONValue {
public:
  vector<shared_ptr<JSONString>> values;
  void print() const {
    cout << "[";
    for (size_t i = 0; i < values.size(); i++) {
      values[i]->print();
      if (i < values.size() - 1) {
        cout << ",";
      }
      cout << "]";
    }
  }
};

enum TokenType {
  OBJECT_BEGIN = '{',
  OBJECT_END = '}',
  ARRAY_BEGIN = '[',
  ARRAY_END = ']',
  COLON = ':',
  COMMA = ',',
  NULL_VAL,
  BOOLEAN,
  STRING,
  NUMBER,
};

struct Token {
  TokenType type;
  string value;

  Token(TokenType t, const string &v) : type(t), value(v) {}

  string getString() {
    stringstream ss;
    ss << "T(" << type << ") ";
    ss << "V: " << value << " ";
    return ss.str();
  }
};

vector<Token> tokenize(const string &input) {
  vector<Token> tokens;
  size_t pos = 0;

  while (pos < input.length()) {
    char c = input[pos];

    switch (c) {
    case '{':
      tokens.emplace_back(TokenType::OBJECT_BEGIN, "{");
      break;
    case '}':
      tokens.emplace_back(TokenType::OBJECT_END, "}");
      break;
    case '[':
      tokens.emplace_back(TokenType::ARRAY_BEGIN, "[");
      break;
    case ']':
      tokens.emplace_back(TokenType::ARRAY_END, "]");
      break;
    case ',':
      tokens.emplace_back(TokenType::COMMA, ",");
      break;
    case ':':
      tokens.emplace_back(TokenType::COLON, ":");
      break;
    case '"': {
      string str;
      pos++;
      while (pos < input.length() && input[pos] != '"') {
        str += input[pos];
        pos++;
      }
      tokens.emplace_back(TokenType::STRING, str);
      break;
    }
    case ' ':
    case '\t':
      break;
    case '\n':
      break;
    };

    pos++;
  }
  return tokens;
}

class JSONParser {
public:
  explicit JSONParser(const string &jsonstring)
      : tokens(tokenize(jsonstring)), pos(0) {};

private:
  vector<Token> tokens;
  size_t pos;

  void skipWhitespace() {
    while (pos < tokens.size() &&
           (tokens[pos].type == NULL_VAL ||
            tokens[pos].type == STRING && tokens[pos].value.empty())) {
      pos++;
    }
  }
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: No command provided." << endl;
    return 1;
  }

  string filename = argv[argc - 1];
  ifstream infile(filename);

  if (!infile.is_open()) {
    cerr << "Error: Opening the file." << endl;
    return 1;
  }

  string s;

  while (getline(infile, s)) {
    auto tokens = tokenize(s);
    for (auto token : tokens) {
      cout << token.getString() << endl;
    }
  }

  return 0;
}
