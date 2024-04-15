#ifndef CPP3_S21_SMARTCALC_V2_0_BACKEND_S21_SMARTCALC_MODEL_H_
#define CPP3_S21_SMARTCALC_V2_0_BACKEND_S21_SMARTCALC_MODEL_H_

#include <cmath>
#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>
#include <functional>

namespace s21 {
class S21SmartCalc {
 public:
  explicit S21SmartCalc(const std::string& expression, double x)
      : infix_expression_(ReplaceSubstring(expression, "mod", "%")), x_(x) {
    ConvertToPostfix();
  }

  double Evaluate() {
    std::string modified_postfix =
        ReplaceSubstring(postfix_expression_, "x", Parser(std::to_string(x_)));
    return Calculation(modified_postfix);
  }

  std::string GetPostfixExpression() const { return postfix_expression_; }

 private:
  std::string infix_expression_;
  std::string postfix_expression_;
  double x_;

  std::map<std::string, int> operator_precedence_ = {
      {"(", 0},    {"+", 1},    {"-", 1},    {"*", 2},    {"/", 2},
      {"%", 2},    {"^", 3},    {"sin", 4},  {"cos", 4},  {"tan", 4},
      {"acos", 4}, {"asin", 4}, {"atan", 4}, {"sqrt", 4}, {"ln", 4},
      {"log", 4},  {"~", 5},    {"#", 5}};

  int GetPrecedence(const std::string& op) { return operator_precedence_[op]; }

  bool IsFunction(const std::string& s) {
    return operator_precedence_.find(s) != operator_precedence_.end() &&
           operator_precedence_[s] == 4;
  }

  bool IsOperator(const std::string& op) {
    return (GetPrecedence(op) > 0 && GetPrecedence(op) < 4) ||
           GetPrecedence(op) == 5;
  }

  std::string ReplaceSubstring(std::string str, const std::string& from,
                               const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
    }
    return str;
  }

  void ConvertToPostfix() { postfix_expression_ = Parser(infix_expression_); }

  std::string CheckFunction(const std::string& expression, size_t i) {
    std::string func;
    while (i < expression.size() && isalpha(expression[i]) &&
           expression[i] != '(') {
      func += expression[i];
      i++;
    }
    if (IsFunction(func)) {
      return func;
    } else {
      return "ERROR";
    }
  }

  std::string Parser(const std::string& expression) {
    std::stack<std::string> operators;
    std::string postfix;
    for (size_t i = 0; i < expression.size(); ++i) {
      char ch = expression[i];
      if (ch == ' ') {
        continue;
      } else if (isdigit(ch) || ch == '.') {
        DigitProcessing(expression, postfix, i);
      } else if (ch == 'x') {
        postfix += "x ";
      } else if (isalpha(ch)) {
        std::string func = CheckFunction(expression, i);
        operators.push(func);
        i += func.size() - 1;
      } else if (ch == ')') {
        CheckRParentheses(operators, postfix);
      } else if (ch == '(' || CheckFunction(expression, i) != "ERROR") {
        CheckLParentheses(operators, expression, ch, i);
      } else if ((ch == '-' || ch == '+') &&
                 (i == 0 || expression.at(i - 1) == '(')) {
        std::string op(1, ch);
        op = (ch == '+') ? "#" : "~";
        operators.push(op);
      } else if (IsOperator(std::string(1, ch))) {
        OperatorProcessing(operators, postfix, ch);
      }
    }
    CheckParenthesesMatch(operators, postfix);
    return postfix;
  }

void CheckParenthesesMatch(std::stack<std::string>& operators, std::string& postfix) {
    while (!operators.empty()) {
      if (operators.top() == "(") {
        throw std::runtime_error("Mismatched parentheses");
      }
      postfix += operators.top() + " ";
      operators.pop();
    }
}

void CheckRParentheses(std::stack<std::string>& operators, std::string& postfix) {
  while (!operators.empty() && operators.top() != "(") {
    postfix += operators.top() + " ";
    operators.pop();
  }
  operators.pop();
  if (!operators.empty() && IsFunction(operators.top())) {
    postfix += operators.top() + " ";
    operators.pop();
  }
}

void CheckLParentheses(std::stack<std::string>& operators, const std::string& expression, char& ch, size_t& i) {
  if (ch == '(') {
    operators.push("(");
  } else {
    std::string func = CheckFunction(expression, i);
    operators.push(func);
    i += func.size() - 1;
  }
}

void OperatorProcessing(std::stack<std::string>& operators, std::string& postfix, char& ch) {
  std::string op(1, ch);
  while (!operators.empty() &&
         GetPrecedence(operators.top()) >= GetPrecedence(op) &&
         op != "^") {
    postfix += operators.top() + " ";
    operators.pop();
  }
  operators.push(op);
}

void DigitProcessing(const std::string& expression, std::string& postfix, size_t& i) {
  while (
      i < expression.size() &&
      (isdigit(expression[i]) || expression[i] == '.' ||
       expression[i] == 'e' || expression[i] == 'E' ||
       (i > 0 && (expression[i - 1] == 'e' || expression[i - 1] == 'E') &&
        (expression[i] == '+' || expression[i] == '-')))) {
    postfix += expression[i++];
  }
  i--;
  postfix += " ";
}

double applyOperation(char op, double a, double b = 0) {
    switch (op) {
        case '+': return b + a;
        case '-': return b - a;
        case '*': return b * a;
        case '/': if (a == 0) throw std::runtime_error("Division by zero"); return b / a;
        case '%': return static_cast<int>(b) % abs(static_cast<int>(round(a = (a > -1 && a < 1) ? 1 : a)));
        case '^': return pow(b, a);
        case '~': return -a;
        case '#': return a;
        default:  throw std::runtime_error("Unknown operation");
    }
}

double applyFunction(const std::string& func, double a, std::stack<double>& values) {
    values.pop();
    if (func == "sin") return sin(a);
    if (func == "cos") return cos(a);
    if (func == "tan") return tan(a);
    if (func == "acos") return acos(a);
    if (func == "asin") return asin(a);
    if (func == "atan") return atan(a);
    if (func == "sqrt") return sqrt(a);
    if (func == "ln") return log(a);
    if (func == "log") return log10(a);
    throw std::runtime_error("Unknown function");
}

double parseNumber(const std::string& postfix, size_t& i, char& ch) {
    std::string num;
    num += ch;
    while (++i < postfix.size() &&
           (isdigit(postfix[i]) || postfix[i] == '.' || postfix[i] == 'e' ||
            postfix[i] == 'E' || postfix[i] == '+' || postfix[i] == '-')) {
        if ((postfix[i] == '+' || postfix[i] == '-') &&
            !(postfix[i - 1] == 'e' || postfix[i - 1] == 'E'))
            break;
        num += postfix[i];
    }
    i--;
    return std::stod(num);
}

double Calculation(const std::string& postfix) {
    std::stack<double> values;
    for (size_t i = 0; i < postfix.size(); i++) {
        char ch = postfix[i];
        std::string op(1, ch);
        if (ch == ' ') continue;
        else if (isdigit(ch) || ch == '.' || ch == 'e' || ch == 'E' ||
                 (ch == '-' && i > 0 && (postfix[i - 1] == 'e' || postfix[i - 1] == 'E'))) {
            i--;
            values.push(parseNumber(postfix, ++i, ch));
        } else if (operator_precedence_.find(op) != operator_precedence_.end()) {
            int precedence = operator_precedence_[op];
            if (precedence != 4) {
                double a = values.top(); values.pop();
                double result = ch == '~' || ch == '#' ? applyOperation(ch, a) : applyOperation(ch, a, values.top());
                if (ch != '~' && ch != '#') values.pop();
                values.push(result);
            }
        } else {
            std::string func;
          while (i < postfix.size() && isalpha(postfix[i])) func += postfix[i++];
          i--;
          values.push(applyFunction(func, values.top(), values));
        }
    }
    return values.top();
}
};
}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V2_0_BACKEND_S21_SMARTCALC_MODEL_H_
