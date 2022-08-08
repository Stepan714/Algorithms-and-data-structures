#include "cppstring.h"
String::String() : s_(nullptr), size_(0), capacity_(0) {
}
size_t String::Size() const {
  return this->size_;
}
size_t String::Length() const {
  return this->size_;
}
String::String(size_t length, char symbol) {
  if (length > 0) {
    s_ = new char[length + 1];
    size_ = length;
    capacity_ = length;
    for (size_t i = 0; i < length; ++i) {
      s_[i] = symbol;
    }
    s_[length] = '\0';
  } else {
    s_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
}
size_t Len(const char* str) {
  size_t i = 0;
  while (str[i] != '\0') {
    i++;
  }
  return i;
}
String::String(const char* str) {  // NOLINT
  size_t len = Len(str);
  s_ = new char[len + 1];
  size_ = len;
  capacity_ = len;
  for (size_t i = 0; i < len; ++i) {
    s_[i] = str[i];
  }
  s_[len] = '\0';
}
String::String(const char* str, size_t length) {
  s_ = new char[length + 1];
  size_ = length;
  capacity_ = length;
  for (size_t i = 0; i < length; ++i) {
    s_[i] = str[i];
  }
  s_[length] = '\0';
}
String::String(const String& other) {
  if (other.capacity_ == 0 && other.s_ == nullptr) {
    this->size_ = 0;
    this->capacity_ = 0;
    this->s_ = nullptr;
  } else {
    this->size_ = Len(other.s_);
    this->capacity_ = size_;
    this->s_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      this->s_[i] = other.s_[i];
    }
    this->s_[size_] = '\0';
  }
}
String::~String() {
  delete[] s_;
}
const char& String::operator[](size_t idx) const {
  return s_[idx];
}
char& String::operator[](size_t idx) {
  return s_[idx];
}
String& String::operator=(const String& other) {
  if (size_ == other.size_) {
    for (size_t i = 0; i < size_; ++i) {
      s_[i] = other[i];
    }
  } else {
    auto tmp = new char[other.size_ + 1];
    delete[] s_;
    s_ = tmp;
    size_ = other.size_;
    capacity_ = size_;
    for (size_t i = 0; i < size_; ++i) {
      s_[i] = other[i];
    }
  }
  return *this;
}

const char& String::At(size_t idx) const {
  if (idx > size_ - 1) {
    throw StringOutOfRange{};
  }
  return s_[idx];
}
char& String::At(size_t idx) {
  if (idx > size_ - 1) {
    throw StringOutOfRange{};
  }
  return s_[idx];
}
const char& String::Front() const {
  return s_[0];
}
const char& String::Back() const {
  return s_[size_ - 1];
}
char& String::Front() {
  return s_[0];
}
char& String::Back() {
  return s_[size_ - 1];
}
const char* String::CStr() const {
  return s_;
}
char* String::CStr() {
  return s_;
}
const char* String::Data() const {
  return s_;
}
bool String::Empty() const {
  bool flag = false;
  if (size_ == 0) {
    flag = true;
  }
  return flag;
}
size_t String::Capacity() const {
  return this->capacity_;
}
void String::Clear() {
  size_ = 0;
}
void String::Swap(String& other) {
  auto tmp = this->s_;
  auto buf = this->size_;
  auto cap = this->capacity_;
  this->s_ = other.s_;
  this->size_ = other.size_;
  this->capacity_ = other.capacity_;
  other.s_ = tmp;
  other.size_ = buf;
  other.capacity_ = cap;
}
void String::PopBack() {
  if (size_ > 0) {
    s_[size_ - 1] = '\0';
    size_--;
  }
  if (size_ * 4 < capacity_) {
    auto tmp = new char[2 * size_ + 1];
    char* buf = s_;
    s_ = tmp;
    capacity_ = 2 * size_;
    size_t i = 0;
    while (i != size_) {
      s_[i] = buf[i];
      i++;
    }
    s_[size_] = '\0';
    delete[] buf;
  }
}
void String::PushBack(const char symbol) {
  if (size_ == capacity_) {
    if (capacity_ == 0) {
      auto tmp = new char[2];
      size_t i = 0;
      while (i != size_) {
        tmp[i] = s_[i];
        i++;
      }
      tmp[size_] = symbol;
      tmp[size_ + 1] = '\0';
      size_++;
      capacity_ += 1;
      delete[] s_;
      s_ = tmp;
    } else {
      auto tmp = new char[2 * capacity_ + 1];
      size_t i = 0;
      while (i != size_) {
        tmp[i] = s_[i];
        i++;
      }
      tmp[size_] = symbol;
      tmp[size_ + 1] = '\0';
      size_++;
      capacity_ *= 2;
      delete[] s_;
      s_ = tmp;
    }
  } else {
    s_[size_] = symbol;
    s_[size_ + 1] = '\0';
    size_++;
  }
}
String& String::operator+=(const String& other) {
  size_t len = other.size_;
  size_t i = 0;
  while (i != len) {
    this->PushBack(other.s_[i]);
    i++;
  }
  return *this;
}
String& String::Resize(size_t new_size, const char symbol) {
  if (new_size <= capacity_) {
    if (new_size <= size_) {
      size_ = new_size;
    } else {
      size_t i = size_ - 1;
      while (i != new_size) {
        s_[i] = symbol;
        i++;
      }
      s_[new_size] = '\0';
      size_ = new_size;
    }
  } else {
    auto tmp = new char[new_size + 1];
    capacity_ = new_size;
    size_t i = 0;
    while (i != size_) {
      tmp[i] = s_[i];
      i++;
    }
    while (i != new_size) {
      tmp[i] = symbol;
      i++;
    }
    tmp[new_size] = '\0';
    delete[] s_;
    s_ = tmp;
    size_ = new_size;
  }
  return *this;
}
void String::Reserve(size_t new_capacity) {
  if (new_capacity > capacity_) {
    capacity_ = new_capacity;
    auto tmp = new char[new_capacity + 1];
    size_t i = 0;
    while (i != size_) {
      tmp[i] = s_[i];
      i++;
    }
    tmp[size_] = '\0';
    delete[] s_;
    s_ = tmp;
  }
}
void String::ShrinkToFit() {
  if (capacity_ > size_) {
    capacity_ = size_;
    auto tmp = new char[size_ + 1];
    size_t i = 0;
    while (i != size_) {
      tmp[i] = s_[i];
      i++;
    }
    tmp[size_] = '\0';
    delete[] s_;
    s_ = tmp;
  }
}
String operator+(const String& str, const String& other) {
  String tmp;
  tmp.s_ = new char[str.size_ + other.size_ + 1];
  tmp.size_ = str.size_ + other.size_;
  tmp.capacity_ = tmp.size_;
  size_t i = 0;
  while (i != str.size_) {
    tmp.s_[i] = str.s_[i];
    i++;
  }
  i = 0;
  size_t len = str.size_;
  while (i != other.size_) {
    tmp.s_[len + i] = other.s_[i];
    i++;
  }
  tmp.s_[len + i] = '\0';
  return tmp;
}
bool operator==(const String& str1, const String& str2) {
  bool flag = true;
  if (str1.s_ == nullptr || str2.s_ == nullptr) {
    if (!(str1.s_ == nullptr && str2.s_ == nullptr)) {
      flag = false;
    }
  } else {
    if (str1.size_ != str2.size_) {
      flag = false;
      return flag;
    }
    size_t i = 0;
    while (i != str1.size_) {
      if (str1.s_[i] != str2.s_[i]) {
        flag = false;
        break;
      }
      i++;
    }
  }
  return flag;
}
bool operator!=(const String& str1, const String& str2) {
  bool flag = false;
  if (str1.s_ == nullptr || str2.s_ == nullptr) {
    if (!(str1.s_ == nullptr && str2.s_ == nullptr)) {
      flag = true;
    }
  } else {
    if (str1.size_ != str2.size_) {
      flag = true;
      return flag;
    }
    size_t i = 0;
    while (i != str1.size_) {
      if (str1.s_[i] != str2.s_[i]) {
        flag = true;
        break;
      }
      i++;
    }
  }
  return flag;
}
bool operator<(const String& str1, const String& str2) {
  bool flag = true;
  if (str1.s_ == nullptr || str2.s_ == nullptr) {
    if (str1.s_ == nullptr && str2.s_ != nullptr) {
      flag = true;
    }
    if (str1.s_ != nullptr && str2.s_ == nullptr) {
      flag = false;
    }
    if (str1.s_ == nullptr && str2.s_ == nullptr) {
      flag = false;
    }
  } else {
    if (str1.size_ == str2.size_) {
      bool t = true;
      size_t i = 0;
      size_t buf = 0;
      while (i != str1.size_) {
        if (str1.s_[i] > str2.s_[i]) {
          flag = false;
          t = false;
          break;
        }
        if (str1.s_[i] < str2.s_[i]) {
          flag = true;
          t = false;
          break;
        }
        if (str1.s_[i] == str2.s_[i]) {
          buf++;
        }
        i++;
      }
      if (buf == i && t) {
        flag = false;
      }
    } else {
      size_t buf = 0;
      size_t len = str1.size_ < str2.size_ ? str1.size_ : str2.size_;
      size_t i = 0;
      bool t = true;
      while (i != len) {
        if (str1.s_[i] > str2.s_[i]) {
          flag = false;
          t = false;
          break;
        }
        if (str1.s_[i] < str2.s_[i]) {
          flag = true;
          t = false;
          break;
        }
        if (str1.s_[i] == str2.s_[i]) {
          buf++;
        }
        i++;
      }
      if (buf == i && t) {
        if (len == str2.size_) {
          flag = false;
        }
      }
    }
  }
  return flag;
}
bool operator>(const String& str1, const String& str2) {
  bool flag = true;
  if (str1.s_ == nullptr || str2.s_ == nullptr) {
    if (str1.s_ == nullptr && str2.s_ != nullptr) {
      flag = false;
    }
    if (str1.s_ != nullptr && str2.s_ == nullptr) {
      flag = true;
    }
    if (str1.s_ == nullptr && str2.s_ == nullptr) {
      flag = false;
    }
  } else {
    if (str1.size_ == str2.size_) {
      bool t = true;
      size_t i = 0;
      size_t buf = 0;
      while (i != str1.size_) {
        if (str1.s_[i] < str2.s_[i]) {
          flag = false;
          t = false;
          break;
        }
        if (str1.s_[i] > str2.s_[i]) {
          flag = true;
          t = false;
          break;
        }
        if (str1.s_[i] == str2.s_[i]) {
          buf++;
        }
        i++;
      }
      if (buf == i && t) {
        flag = false;
      }
    } else {
      bool t = true;
      size_t buf = 0;
      size_t len = str1.size_ < str2.size_ ? str1.size_ : str2.size_;
      size_t i = 0;
      while (i != len) {
        if (str1.s_[i] < str2.s_[i]) {
          flag = false;
          t = false;
          break;
        }
        if (str1.s_[i] > str2.s_[i]) {
          flag = true;
          t = false;
          break;
        }
        if (str1.s_[i] == str2.s_[i]) {
          buf++;
        }
        i++;
      }
      if (buf == i && t) {
        if (len == str1.size_) {
          flag = false;
        }
      }
    }
  }
  return flag;
}
bool operator>=(const String& str1, const String& str2) {
  bool flag = false;
  if (str1 > str2 || str1 == str2) {
    flag = true;
  }
  return flag;
}
bool operator<=(const String& str1, const String& str2) {
  bool flag = false;
  if (str1 < str2 || str1 == str2) {
    flag = true;
  }
  return flag;
}
std::ostream& operator<<(std::ostream& out, const String& str) {
  size_t i = 0;
  while (i != str.size_) {
    out << str.s_[i];
    i++;
  }
  return out;
}
