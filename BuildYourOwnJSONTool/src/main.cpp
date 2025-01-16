#include <bits/stdc++.h>
#include <cstddef>
#include <iostream>
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
  COLON = ';',
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
};

int main(int argc, char *argv[]) { return 0; }
