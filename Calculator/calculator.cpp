#include "calculator.h"

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

std::unique_ptr<IExpression> ParseMultiplier(const std::vector<Token>& v, size_t& index) {
  if (index >= v.size()) {
    throw WrongExpressionError{};
  }
  if (v[index] == Token{OpeningBracketToken{}}) {
    index++;
    auto result = BuildExpression(v, index);
    if (index >= v.size() || !(v[index] == Token{ClosingBracketToken{}})) {
      throw WrongExpressionError{};
    }
    index++;
    return result;
  }
  const NumberToken* t = std::get_if<NumberToken>(&v[index]);
  if (!t) {
    throw WrongExpressionError{};
  }
  index++;
  return std::unique_ptr<IExpression>(new Constant(t->value));
}

std::unique_ptr<IExpression> ParseAddendum(const std::vector<Token>& v, size_t& index) {
  std::unique_ptr<IExpression> result = ParseMultiplier(v, index);
  while (true) {
    if (index == v.size() || v[index] == Token{PlusToken{}} || v[index] == Token{MinusToken{}} ||
        v[index] == Token{ClosingBracketToken{}}) {
      return result;
    }
    if (v[index] == Token{MultiplyToken{}}) {
      index++;
      result = std::unique_ptr<IExpression>(new Multiply(std::move(result), ParseMultiplier(v, index)));
      continue;
    }
    if (v[index] == Token{DivideToken{}}) {
      index++;
      result = std::unique_ptr<IExpression>(new Divide(std::move(result), ParseMultiplier(v, index)));
      continue;
    }
    if (v[index] == Token{ResidualToken{}}) {
      index++;
      result = std::unique_ptr<IExpression>(new Residual(std::move(result), ParseMultiplier(v, index)));
      continue;
    }
    const UnknownToken* s = std::get_if<UnknownToken>(&v[index]);
    if (s != nullptr) {
      ++index;
      throw UnknownSymbolError{s->value};
    }
    throw WrongExpressionError{};
  }
}

std::unique_ptr<IExpression> BuildExpression(const std::vector<Token>& v, size_t& index) {
  std::unique_ptr<IExpression> result = ParseAddendum(v, index);
  while (true) {
    if (index == v.size() || v[index] == Token{ClosingBracketToken{}}) {
      return result;
    }
    if (v[index] == Token{PlusToken{}}) {
      index++;
      result = std::unique_ptr<IExpression>(new Sum(std::move(result), ParseAddendum(v, index)));
      continue;
    }
    if (v[index] == Token{MinusToken{}}) {
      index++;
      result = std::unique_ptr<IExpression>(new Subtract(std::move(result), ParseAddendum(v, index)));
      continue;
    }
    const UnknownToken* s = std::get_if<UnknownToken>(&v[index]);
    if (s != nullptr) {
      ++index;
      throw UnknownSymbolError{s->value};
    }
    throw WrongExpressionError{};
  }
}

std::unique_ptr<IExpression> ParseExpression(const std::vector<Token>& v, size_t& index) {
  index = 0;
  auto result = BuildExpression(v, index);
  if (index != v.size()) {
    throw WrongExpressionError{};
  }
  return result;
}

int CalculateExpression(std::string_view input) {
  size_t index = 0;
  return ParseExpression(Tokenize(input), index)->Calculate();
}
