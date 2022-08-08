#include <iostream>
#include <string_view>
#include <string>
#include <variant>
#include <sstream>
#include <vector>
#include <memory>
#pragma once

class UnknownSymbolError : public std::runtime_error {
 public:
  explicit UnknownSymbolError(const std::string& symbol = "") : std::runtime_error("UnknownSymbolError: " + symbol) {
  }
};

class WrongExpressionError : public std::runtime_error {
 public:
  explicit WrongExpressionError(const std::string& msg = "") : std::runtime_error("WrongExpressionError: " + msg) {
  }
};

struct PlusToken {
  friend bool operator==(PlusToken, PlusToken) {
    return true;
  }
};
struct MultiplyToken {
  friend bool operator==(MultiplyToken, MultiplyToken) {
    return true;
  }
};
struct ResidualToken {
  friend bool operator==(ResidualToken, ResidualToken) {
    return true;
  }
};
struct DivideToken {
  friend bool operator==(DivideToken, DivideToken) {
    return true;
  }
};
struct MinusToken {
  friend bool operator==(MinusToken, MinusToken) {
    return true;
  }
};
struct OpeningBracketToken {
  friend bool operator==(OpeningBracketToken, OpeningBracketToken) {
    return true;
  }
};
struct NumberToken {
  int value = 0;
  friend bool operator==(const NumberToken& x, const NumberToken& y) {
    bool flag = true;
    if (x.value != y.value) {
      flag = false;
    }
    return flag;
  }
};
struct UnknownToken {
  std::string value;
  friend bool operator==(const UnknownToken& x, const UnknownToken& y) {
    bool flag = true;
    if (x.value != y.value) {
      flag = false;
    }
    return flag;
  }
};
struct ClosingBracketToken {
  friend bool operator==(ClosingBracketToken, ClosingBracketToken) {
    return true;
  }
};
struct SqrToken {
  friend bool operator==(SqrToken, SqrToken) {
    return true;
  }
};
struct MaxToken {
  friend bool operator==(MaxToken, MaxToken) {
    return true;
  }
};
struct MinToken {
  friend bool operator==(MinToken, MinToken) {
    return true;
  }
};
struct AbsToken {
  friend bool operator==(AbsToken, AbsToken) {
    return true;
  }
};
using Token = std::variant<PlusToken, MultiplyToken, OpeningBracketToken, ClosingBracketToken, ResidualToken,
                           MinusToken, DivideToken, SqrToken, UnknownToken, MaxToken, MinToken, AbsToken, NumberToken>;
Token ToToken(std::string_view sv);
std::vector<Token> Tokenize(std::string_view sv);

class IExpression {
 public:
  virtual int Calculate() const = 0;
  virtual ~IExpression() = default;
};

class Constant : public IExpression {
 private:
  int n_;

 public:
  explicit Constant(int n) : n_(n) {
  }
  int Calculate() const override {
    return n_;
  }
};

class IBinaryOperation : public IExpression {
 public:
  explicit IBinaryOperation(std::unique_ptr<IExpression>&& left, std::unique_ptr<IExpression>&& right)
      : left_(std::move(left)), right_(std::move(right)) {
  }
  virtual int Operation(int left, int right) const = 0;
  int Calculate() const override {
    return Operation(left_->Calculate(), right_->Calculate());
  }

 private:
  std::unique_ptr<IExpression> left_;
  std::unique_ptr<IExpression> right_;
};

class Sum : public IBinaryOperation {
 public:
  explicit Sum(std::unique_ptr<IExpression>&& left, std::unique_ptr<IExpression>&& right)
      : IBinaryOperation(std::move(left), std::move(right)) {
  }
  int Operation(int left, int right) const override {
    return left + right;
  }
};

class Multiply : public IBinaryOperation {
 public:
  explicit Multiply(std::unique_ptr<IExpression>&& left, std::unique_ptr<IExpression>&& right)
      : IBinaryOperation(std::move(left), std::move(right)) {
  }
  int Operation(int left, int right) const override {
    return left * right;
  }
};

class Subtract : public IBinaryOperation {
 public:
  explicit Subtract(std::unique_ptr<IExpression>&& left, std::unique_ptr<IExpression>&& right)
      : IBinaryOperation(std::move(left), std::move(right)) {
  }
  int Operation(int left, int right) const override {
    return left - right;
  }
};

class Divide : public IBinaryOperation {
 public:
  explicit Divide(std::unique_ptr<IExpression>&& left, std::unique_ptr<IExpression>&& right)
      : IBinaryOperation(std::move(left), std::move(right)) {
  }
  int Operation(int left, int right) const override {
    return left / right;
  }
};

class Residual : public IBinaryOperation {
 public:
  explicit Residual(std::unique_ptr<IExpression>&& left, std::unique_ptr<IExpression>&& right)
      : IBinaryOperation(std::move(left), std::move(right)) {
  }
  int Operation(int left, int right) const override {
    return (left % right);
  }
};

class Minimum : public IBinaryOperation {
 public:
  explicit Minimum(std::unique_ptr<IExpression>&& left, std::unique_ptr<IExpression>&& right)
      : IBinaryOperation(std::move(left), std::move(right)) {
  }
  int Operation(int left, int right) const override {
    return left < right ? left : right;
  }
};

class Maximum : public IBinaryOperation {
 public:
  explicit Maximum(std::unique_ptr<IExpression>&& left, std::unique_ptr<IExpression>&& right)
      : IBinaryOperation(std::move(left), std::move(right)) {
  }
  int Operation(int left, int right) const override {
    return left > right ? left : right;
  }
};

class IUnaryOperation : public IExpression {
 private:
  std::unique_ptr<IExpression> child_;

 public:
  explicit IUnaryOperation(std::unique_ptr<IExpression>&& child) : child_(std::move(child)) {
  }
  virtual int Operation(int child) const = 0;
  int Calculate() const override {
    return Operation(child_->Calculate());
  }
};

class Square : public IUnaryOperation {
 public:
  explicit Square(std::unique_ptr<IExpression>&& child) : IUnaryOperation(std::move(child)) {
  }
  int Operation(int child) const override {
    return child * child;
  }
};

class AbsoluteValue : public IUnaryOperation {
 public:
  explicit AbsoluteValue(std::unique_ptr<IExpression>&& child) : IUnaryOperation(std::move(child)) {
  }
  int Operation(int child) const override {
    return child > 0 ? child : -1 * child;
  }
};

std::unique_ptr<IExpression> BuildExpression(const std::vector<Token>& v, size_t& index);

std::unique_ptr<IExpression> ParseMultiplier(const std::vector<Token>& v, size_t& index);

std::unique_ptr<IExpression> ParseAddendum(const std::vector<Token>& v, size_t& index);

std::unique_ptr<IExpression> ParseExpression(const std::vector<Token>& v, size_t& index);

int CalculateExpression(std::string_view input);
