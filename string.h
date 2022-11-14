#ifndef STRING_H
#define STRING_H
#include <cstring>
#include <iostream>

class string;
class string {
public:
  string();
  string(const string&);
  string(const char*);
  string& operator=(const string&);
  string& operator=(const char*);
  string& operator+(const string&);
  string& operator+(const char*);
  char& operator[](int);
  const char& operator[](int) const;
  ~string();
  char* get_str() const { return str_data; }

  int length() { return len; }
  int size() { return len; }
  static int number() { return string_num; }

  bool empty() const;
  void append(const string&);
  void append(const char*);
  void push_back(const char);
  void swap(char*);
  void swap(string&);
  int find(string&, size_t);
  int find(char*, size_t);

  friend std::ostream& operator<<(std::ostream&, const string&);
  friend std::istream& operator>>(std::istream&s, string&);
  friend bool operator==(const string&, const string&);
  friend bool operator==(const string&, const char*);
  friend bool operator<(const string&, const string&);
  friend bool operator>(const string&, const string&);

private:
  char* str_data;
  int len;
  static int string_num;
  static const int INPUT_LIMIT = 100;
};

int string::string_num = 0;

string::string() {
  ++string_num; 
  len = 0;
  str_data = new char[1];
  str_data[0] = '\0';
}

string::string(const string& str) {
  ++string_num;
  len = str.len;
  str_data = new char[len + 1];
  std::strcpy(str_data, str.str_data);
}

string::string(const char* str) {
  ++string_num;
  len = std::strlen(str);
  str_data = new char[len + 1];
  std::strcpy(str_data, str);
}

string::~string() {
  delete[] str_data;
  --string_num;
}

bool string::empty() const { return this->str_data == 0; }

void string::append(const string& _str) {
  std::strcat(this->str_data, _str.str_data);
  this->len = std::strlen(this->str_data);
  return;
}

void string::append(const char* _str) {
  std::strcat(this->str_data, _str);
  this->len = std::strlen(this->str_data);
  return;
}

void string::push_back(const char ch) {
  std::strcat(this->str_data, &ch);
  this->len = std::strlen(this->str_data);
  return;
}

void string::swap(string& _str) {
  char temp[this->INPUT_LIMIT];
  std::strcpy(temp, _str.str_data);
  std::strcpy(_str.str_data, this->str_data);
  std::strcpy(this->str_data, temp);
  this->len = std::strlen(this->str_data);
  return;
}

void string::swap(char* _str) {
  char temp[this->INPUT_LIMIT];
  std::strcpy(temp, _str);
  std::strcpy(_str, this->str_data);
  std::strcpy(this->str_data, temp);
  this->len = std::strlen(this->str_data);
  return;
} 

int string::find(string& _str, size_t index) {
  int length = std::strlen(_str.str_data);
  for (int t_index = index; t_index < this->len; t_index++) {
    if (this->str_data[t_index] == _str.str_data[0])
      for (int s_index = 0; s_index < length; s_index++) {
        if (this->str_data[t_index + s_index] != _str.str_data[s_index]) break;
        if (s_index == length - 1) return t_index;
      }
  }
  return -1;
}

int string::find(char* _str, size_t index) {
  int length = std::strlen(_str);
  for (int t_index = index; t_index < this->len; t_index++) {
    if (this->str_data[t_index] == _str[0])
      for (int s_index = 0; s_index< length; s_index++) {
        if (this->str_data[t_index + s_index] != _str[s_index]) break;
        if (s_index == length - 1) return t_index;
      }
  }
  return -1;
}

string& string::operator=(const string& str) {
  if (this == &str) return *this;
  delete[] str_data;
  len = str.len;
  str_data = new char[std::strlen(str.str_data) + 1];
  std::strcpy(str_data, str.str_data);
  return *this;
}

string& string::operator=(const char* str) {
  if (this->str_data == str) return *this;
  delete[] str_data;
  len = std::strlen(str);
  str_data = new char[len + 1];
  std::strcpy(str_data, str);
  return *this;
}

string& string::operator+(const string& str) {
  std::strcat(this->str_data, str.str_data);
  return *this;
}

string& string::operator+(const char* str) {
  std::strcat(this->str_data, str);
  return *this;
}


char& string::operator[](int i) { return str_data[i]; }

const char& string::operator[](int i) const { return str_data[i]; }

bool operator==(const string& str1, const string& str2) { return (std::strcmp(str1.str_data, str2.str_data) == 0); }

bool operator==(const string& str1, const char* str2) { return (std::strcmp(str1.str_data, str2) == 0); }

bool operator<(const string& str1, const string& str2) { return (std::strcmp(str1.str_data, str2.str_data) < 0); }

bool operator>(const string& str1, const string& str2) { return str2 < str1; }

std::ostream& operator<<(std::ostream& os, const string& str) {
  os << str.get_str();
  return os;
}

std::istream& operator>>(std::istream& is, string& str) {
  char temp[string::INPUT_LIMIT];
  if (is) str = temp;
  while(is && is.get() != '\n') continue;
  return is;
}
#endif // STRING_H
