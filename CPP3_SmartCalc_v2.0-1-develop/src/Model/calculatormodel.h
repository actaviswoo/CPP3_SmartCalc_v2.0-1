#ifndef SRC_MODEL_CALCULATORMODEL_H
#define SRC_MODEL_CALCULATORMODEL_H

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

namespace s21 {

class ModelCalculator {
 public:
  enum Lexeme {
    NUMBER = 1,
    X = 2,
    PLUS = 3,
    MINUS = 4,
    MUL = 5,
    DIV = 6,
    POW = 7,
    MOD = 8,
    COS = 9,
    SIN = 10,
    TAN = 11,
    ACOS = 12,
    ASIN = 13,
    ATAN = 14,
    LOG = 15,
    LN = 16,
    SQRT = 17,
    LEFT = 18,
    RIGHT = 19,
    uPLUS = 20,
    uMINUS = 21
  };
  ModelCalculator(){};
  ~ModelCalculator(){};

  bool Validator(const std::string &input);
  bool ValidatorInputNumber(const std::string &line_text);
  bool ValidatorInputDot(const std::string &line_text);
  bool ValidatorInputX(const std::string &line_text);
  bool ValidatorInputBracket(const std::string &button_text,
                             const std::string &line_text);
  bool ValidatorInputOperation(const std::string &button_text,
                               const std::string &line_text);
  bool ValidatorInputFunction(const std::string &line_text);

  void Input(const std::string &input, double x);
  double Calculate();
  // void PrintInfix();
  // void PrintPostfix();

 private:
  std::string input_;
  bool flag_;
  static const std::map<std::string, Lexeme> map_lexeme_;
  struct Union_ {
    Lexeme lexeme;
    double value;
    int priority;
  };
  std::vector<Union_> infix_;
  std::stack<Union_> stack_;
  std::vector<Union_> postfix_;
  std::stack<double> calculate_;
  double x_;

  int LexemeToPriority(Lexeme lexeme);
  void CreateInfix();
  void ParseOperand(std::string::iterator *i);
  void ParseOperation(std::string::iterator *i);
  void CreatePostfix();
  void PriorityCompare(Union_ &i, int pr_stack, int pr_infix);
  bool HigherPriority(int pr_stack, int pr_infix, Union_ &i);
  void PriorityCompare();
  double Function(Lexeme lexeme);
  double Operation(Lexeme lexeme);

  bool StartEndValid(const std::string &str, int len);
  bool OnceValid(const std::string &str, int *i, int *dot, int *op);
  bool DoubleValid(const std::string &str, int *i, int *left);
  bool TripleValid(const std::string &str, int *i, int *dot, int *op,
                   int *left);
  bool QuadroValid(const std::string &str, int *i, int *op, int *left);
};

}  // namespace s21

#endif  // SRC_MODEL_CALCULATORMODEL_H
