#include <bits/stdc++.h>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

// Datatype

class JSONValue {
public:
  virtual ~JSONValue() = default;
  virtual void print() const = 0;
};

class JSONNull : public JSONValue {
public:
  void print() const override { cout << "null"; }
};

class JSONString : public JSONValue {
public:
  string value;
  explicit JSONString(const string &v) : value(v) {}
  void print() const override { cout << "\"" << value << "\""; }
};

class JSONNumber : public JSONValue {
public:
  double value;
  explicit JSONNumber(double v) : value(v) {}
  void print() const override { cout << value; }
};

class JSONBoolean : public JSONValue {
public:
  bool value;
  explicit JSONBoolean(bool v) : value(v) {}
  void print() const override { cout << (value ? "true" : "false"); }
};

class JSONArray : public JSONValue {
public:
  vector<shared_ptr<JSONValue>> values;
  void print() const {
    cout << "[";
    for (size_t i = 0; i < values.size(); i++) {
      values[i]->print();
      if (i < values.size() - 1) {
        cout << ", ";
      }
    }
    cout << "]";
  }
};

class JSONObject : public JSONValue {
public:
  unordered_map<string, shared_ptr<JSONValue>> values;
  void print() const {
    cout << "{";
    size_t i = 0;
    for (const auto &pair : values) {
      cout << "\"" << pair.first << "\":";
      pair.second->print();
      if (i < values.size() - 1) {
        cout << ", ";
        ++i;
      }
    }
    cout << "}";
  }
};

// Lexical Analysis

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

/*
 * Chain of Responsibility (Behavioral)
 * Process input characters using a sequence of handlers in a loop.
 * */
vector<Token> tokenizer(const string &input) {
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
    case 't': {
      tokens.emplace_back(TokenType::BOOLEAN, "true");
      break;
    }
    case 'f': {
      tokens.emplace_back(TokenType::BOOLEAN, "false");
      break;
    }
    case 'n': {
      tokens.emplace_back(TokenType::NULL_VAL, "null");
      break;
    }
    case '0' ... '9': {
      string num;
      while (pos < input.length() &&
             (isdigit(input[pos]) || input[pos] == '.')) {
        num += input[pos];
        pos++;
      }
      pos--;
      tokens.emplace_back(TokenType::NUMBER, num);
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

/** Builder Pattern -
 * Construct complex JSON structures step by step during parsing.
 **/
class JSONParser {
public:
  explicit JSONParser(const string &jsonstring)
      : tokens(tokenizer(jsonstring)), pos(0) {};

  shared_ptr<JSONValue> parser() {
    if (pos >= tokens.size()) {
      throw runtime_error("Empty Input");
    }
    return parseValue();
  }

private:
  vector<Token> tokens;
  size_t pos;

  void skipWhitespace() {
    while (pos < tokens.size() &&
           (tokens[pos].type == NULL_VAL ||
            (tokens[pos].type == STRING && tokens[pos].value.empty()))) {
      pos++;
    }
  }

  bool hasMore() { return pos < tokens.size(); }

  Token &nextToken() {
    if (!hasMore()) {
      throw runtime_error("Unexpected end of input");
    }
    return tokens[pos++];
  }

  Token &currentToken() {
    if (!hasMore()) {
      throw runtime_error("Unexpected end of input");
    }
    return tokens[pos];
  }

  shared_ptr<JSONObject> parseObject() {
    auto object = make_shared<JSONObject>();
    if (currentToken().type != TokenType::OBJECT_BEGIN) {
      throw runtime_error("Expected '{' at start of object");
    }
    nextToken();

    while (hasMore() && currentToken().type != TokenType::OBJECT_END) {
      if (currentToken().type != TokenType::STRING) {
        throw runtime_error("Expected string key in object.");
      }
      string key = nextToken().value; // check later

      if (currentToken().type != TokenType::COLON) {
        throw runtime_error("Expected ':' after object key");
      }
      nextToken();

      object->values[key] = parseValue();

      if (currentToken().type == TokenType::COMMA) {
        nextToken();
      }
    }

    if (currentToken().type != TokenType::OBJECT_END) {
      throw runtime_error("Expected '}' at end of object");
    }
    nextToken();
    return object;
  }

  shared_ptr<JSONArray> parseArray() {
    auto array = make_shared<JSONArray>();
    if (currentToken().type != TokenType::ARRAY_BEGIN) {
      throw runtime_error("Expected '[' at start of array");
    }
    nextToken();
    while (hasMore() && currentToken().type != TokenType::ARRAY_END) {
      array->values.emplace_back(parseValue());
      if (currentToken().type == TokenType::COMMA) {
        nextToken();
      }
    }

    if (!hasMore() || currentToken().type != TokenType::ARRAY_END) {
      throw runtime_error("Expected ']' at end of array");
    }
    nextToken();
    return array;
  }

  shared_ptr<JSONValue> parseValue() {
    auto token = currentToken();
    switch (token.type) {
    case TokenType::OBJECT_BEGIN:
      return parseObject();
    case TokenType::ARRAY_BEGIN:
      return parseArray();
    case TokenType::NULL_VAL:
      nextToken();
      return make_shared<JSONNull>();
    case TokenType::STRING:
      nextToken();
      return make_shared<JSONString>(token.value);
    case TokenType::BOOLEAN: {
      nextToken();
      bool val = (token.value == "true");
      return make_shared<JSONBoolean>(val);
    }
    case TokenType::NUMBER: {
      nextToken();
      double num = stod(token.value);
      return make_shared<JSONNumber>(num);
    }
    default:
      throw runtime_error("Unexpected token: " + token.value);
    }
  }
};

string getFileContents(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    throw runtime_error("Unable to open file.");
  }
  ostringstream oss;
  oss << file.rdbuf();
  return oss.str();
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: No command provided." << endl;
    return 1;
  }
  string filename = argv[argc - 1];

  try {
    JSONParser parser(getFileContents(filename));
    auto result = parser.parser();
    result->print();
  } catch (const runtime_error &e) {
    cout << "Error parsing JSON: " << e.what() << endl;
    return 1;
  }

  // vector<Token> tokens = tokenizer(
  //     R"({"name": "John", "age": 30, "isStudent": false, "courses": ["Math",
  //     "Science"]})");
  // for (auto token : tokens) {
  //   cout << token.getString() << endl;
  // }

  return 0;
}
