#include <bits/stdc++.h>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

enum TokenType {
  LEFT_BRACE = '{',
  RIGHT_BRACE = '}',
  LEFT_BRACKET = '(',
  RIGHT_BRACKET = ')',
  LEFT_SQUARE_BRACKET = '[',
  RIGHT_SQUARE_BRACKET = ']',
  COMMA = ',',
  COLON = ':',
  SEMICOLON = ';',
  DOUBLE_QUOTE = '"',
  BOOLEAN,
  NUMBER,
  STRING,
  NULL_VALUE
};

struct Token {
  TokenType type;
  string value;
  size_t line;
  size_t colunm;

  Token(TokenType t, const string &v, size_t l = 0, size_t c = 0)
      : type(t), value(v), line(l), colunm(c) {}

  string getValue() {
    stringstream ss;
    ss << "L" << line << " ";
    ss << "C" << colunm << " ";
    ss << "T(" << type << ") ";
    ss << "V: " << value << " ";
    return ss.str();
  }
};

vector<Token> tokenize(const string &input) {
  vector<Token> tokens;
  size_t pos = 0;
  size_t line = 1;
  size_t col = 1;

  while (pos < input.length()) {
    char c = input[pos];

    switch (c) {
    case '{':
      tokens.emplace_back(TokenType::LEFT_BRACE, "{", line, col);
      break;
    case '}':
      tokens.emplace_back(TokenType::RIGHT_BRACE, "}", line, col);
      break;
    case ':':
      tokens.emplace_back(TokenType::COLON, ":", line, col);
      break;
    case ',':
      tokens.emplace_back(TokenType::COMMA, ",", line, col);
      break;
    case '"': {
      string str;
      pos++;
      col++;
      while (pos < input.length() && input[pos] != '"') {
        str += input[pos];
        pos++;
        col++;
      }
      tokens.emplace_back(TokenType::STRING, str, line, col);
      break;
    }
    case ' ':
    case '\t':
      col++;
      break;
    case '\n':
      line++;
      col = 1;
      break;
    default:
      if (isalpha(c)) {
        string value;
        while (pos < input.length() && std::isalnum(input[pos])) {
          value += input[pos];
          pos++;
          col++;
        }
        pos--;
        tokens.emplace_back(TokenType::STRING, value, line, col);
      }
    };
    pos++;
    col++;
  }
  return tokens;
}

int main(int argc, char *argv[]) {
  string input = "{\"key\":\"value\",}";
  auto tokens = tokenize(input);
  for (auto token : tokens) {
    cout << token.getValue() << endl;
  }
  return 0;
}
