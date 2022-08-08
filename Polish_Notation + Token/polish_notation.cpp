#include "polish_notation.h"
Token ToToken(std::string_view sv) {
  if (sv == "+") {
    return PlusToken{};
  }
  if (sv == "*") {
    return MultiplyToken{};
  }
  if (sv == "-") {
    return MinusToken{};
  }
  if (sv == "(") {
    return OpeningBracketToken{};
  }
  if (sv == ")") {
    return ClosingBracketToken{};
  }
  if (sv == "/") {
    return DivideToken{};
  }
  if (sv == "%") {
    return ResidualToken{};
  }
  if (sv == "sqr") {
    return SqrToken{};
  }
  if (sv == "min") {
    return MinToken{};
  }
  if (sv == "max") {
    return MaxToken{};
  }
  if (sv == "abs") {
    return AbsToken{};
  }
  std::string s = std::string(sv);
  std::istringstream is(s);
  int n = 0;
  is >> n;
  if (is.eof()) {
    return NumberToken{n};
  }
  return UnknownToken{std::move(s)};
}
std::vector<Token> Tokenize(std::string_view sv) {
  std::vector<Token> result;
  while (!sv.empty()) {
    auto idx = sv.find(' ');
    if (idx == sv.npos) {
      result.push_back(ToToken(sv));
      break;
    }
    if (idx != 0) {
      result.push_back(ToToken(sv.substr(0, idx)));
    }
    sv.remove_prefix(idx + 1);
  }
  return result;
}
std::unique_ptr<IExpression> BuildExpressions(const std::vector<Token>& v, size_t& index) {
  if (index >= v.size()) {
    throw WrongExpressionError{};
  }
  if (Token{PlusToken{}} == v[index]) {
    ++index;
    std::unique_ptr<IExpression> left = BuildExpressions(v, index);
    std::unique_ptr<IExpression> right = BuildExpressions(v, index);
    return std::unique_ptr<IExpression>(new Sum(std::move(left), std::move(right)));
  }
  if (Token{MultiplyToken{}} == v[index]) {
    ++index;
    std::unique_ptr<IExpression> left = BuildExpressions(v, index);
    std::unique_ptr<IExpression> right = BuildExpressions(v, index);
    return std::unique_ptr<IExpression>(new Multiply(std::move(left), std::move(right)));
  }
  if (Token{MinusToken{}} == v[index]) {
    ++index;
    std::unique_ptr<IExpression> left = BuildExpressions(v, index);
    std::unique_ptr<IExpression> right = BuildExpressions(v, index);
    return std::unique_ptr<IExpression>(new Subtract(std::move(left), std::move(right)));
  }
  if (Token{DivideToken{}} == v[index]) {
    ++index;
    std::unique_ptr<IExpression> left = BuildExpressions(v, index);
    std::unique_ptr<IExpression> right = BuildExpressions(v, index);
    return std::unique_ptr<IExpression>(new Divide(std::move(left), std::move(right)));
  }
  if (Token{ResidualToken{}} == v[index]) {
    ++index;
    std::unique_ptr<IExpression> left = BuildExpressions(v, index);
    std::unique_ptr<IExpression> right = BuildExpressions(v, index);
    return std::unique_ptr<IExpression>(new Residual(std::move(left), std::move(right)));
  }
  if (Token{MinToken{}} == v[index]) {
    ++index;
    std::unique_ptr<IExpression> left = BuildExpressions(v, index);
    std::unique_ptr<IExpression> right = BuildExpressions(v, index);
    return std::unique_ptr<IExpression>(new Minimum(std::move(left), std::move(right)));
  }
  if (Token{MaxToken{}} == v[index]) {
    ++index;
    std::unique_ptr<IExpression> left = BuildExpressions(v, index);
    std::unique_ptr<IExpression> right = BuildExpressions(v, index);
    return std::unique_ptr<IExpression>(new Maximum(std::move(left), std::move(right)));
  }
  const UnknownToken* s = std::get_if<UnknownToken>(&v[index]);
  if (s != nullptr) {
    ++index;
    throw UnknownSymbolError{s->value};
  }
  if (Token{SqrToken{}} == v[index]) {
    ++index;
    std::unique_ptr<IExpression> child = BuildExpressions(v, index);
    return std::unique_ptr<IExpression>(new Square(std::move(child)));
  }
  if (Token{AbsToken{}} == v[index]) {
    ++index;
    std::unique_ptr<IExpression> child = BuildExpressions(v, index);
    return std::unique_ptr<IExpression>(new AbsoluteValue(std::move(child)));
  }

  NumberToken t = std::get<NumberToken>(v[index]);
  ++index;
  return std::unique_ptr<IExpression>(new Constant(t.value));
}

std::unique_ptr<IExpression> BuildExpression(const std::vector<Token>& v) {
  size_t index = 0;
  std::unique_ptr<IExpression> result;
  try {
    result = BuildExpressions(v, index);
  } catch (...) {
    throw;
  }
  if (index != v.size()) {
    throw WrongExpressionError{};
  }
  return result;
}

int CalculatePolishNotation(std::string_view input) {
  auto ptr = BuildExpression(Tokenize(input));
  return ptr->Calculate();
}
