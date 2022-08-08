#pragma once
#include <stdexcept>
#define ARRAY_TRAITS_IMPLEMENTED
class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

// YOUR CODE...
template <class T, size_t N>
class Array {
  static void SwapValue(T& buf1, T& buf2) {
    T tmp = buf1;
    buf1 = buf2;
    buf2 = tmp;
  }

 public:
  T mas[N];
  const T& operator[](size_t indx) const {
    return mas[indx];
  }
  const T& At(size_t indx) const {
    if (indx > N - 1) {
      throw ArrayOutOfRange{};
    }
    return mas[indx];
  }
  const T& Front() const {
    return mas[0];
  }
  const T& Back() const {
    return mas[N - 1];
  }
  const T* Data() const {
    return mas;
  }
  T& At(size_t indx) {
    if (indx > N - 1) {
      throw ArrayOutOfRange{};
    }
    return mas[indx];
  }
  T& operator[](size_t indx) {
    return mas[indx];
  }
  size_t Size() const {
    return N;
  }
  T& Front() {
    return mas[0];
  }
  T& Back() {
    return mas[N - 1];
  }
  bool Empty() const {
    bool flag = false;
    if (N == 0) {
      flag = true;
    }
    return flag;
  }
  void Fill(const T& value) {
    size_t i = 0;
    while (i < N) {
      mas[i] = value;
      i++;
    }
  }
  void Swap(Array<T, N>& other) {
    size_t i = 0;
    while (i < N) {
      SwapValue(mas[i], other[i]);
      i++;
    }
  }
};
template <class T, int64_t N>
int64_t GetSize(T (&)[N]) {
  return N;
}
template <class T>
int64_t GetSize(T) {
  return 0;
}
template <class T>
int64_t GetRank(T) {
  return 0;
}
template <class T, int64_t N>
int64_t GetRank(T (&a)[N]) {
  return 1 + GetRank(a[0]);
}
template <class T>
int64_t GetNumElements(T) {
  return 1;
}
template <class T, int64_t N>
int64_t GetNumElements(T (&mas)[N]) {
  return N * GetNumElements(mas[0]);
}
