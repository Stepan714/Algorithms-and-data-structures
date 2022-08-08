#include <iostream>
#include <cstring>
#include <stdexcept>
#pragma once

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
  char* s_;
  size_t size_;
  size_t capacity_;

 public:
  String();
  size_t Size() const;
  size_t Length() const;
  String(size_t, char);
  String(const char*);  // NOLINT
  String(const char*, size_t);
  String(const String&);
  ~String();
  String& operator=(const String&);
  const char& operator[](size_t) const;
  char& operator[](size_t);
  const char& At(size_t) const;
  char& At(size_t);
  const char& Front() const;
  char& Front();
  const char& Back() const;
  char& Back();
  const char* CStr() const;
  char* CStr();
  const char* Data() const;
  bool Empty() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String&);
  void PopBack();
  void PushBack(const char);
  String& operator+=(const String& other);
  String& Resize(size_t, const char);
  void Reserve(size_t);
  void ShrinkToFit();
  friend String operator+(const String&, const String&);
  friend bool operator<(const String&, const String&);
  friend bool operator<=(const String&, const String&);
  friend bool operator>(const String&, const String&);
  friend bool operator>=(const String&, const String&);
  friend bool operator!=(const String&, const String&);
  friend bool operator==(const String&, const String&);
  friend std::ostream& operator<<(std::ostream&, const String&);
};
size_t Len(const char*);
