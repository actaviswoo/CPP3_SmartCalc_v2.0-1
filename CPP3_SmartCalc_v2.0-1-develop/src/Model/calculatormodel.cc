#include "calculatormodel.h"

bool s21::ModelCalculator::Validator(const std::string &str) {
  bool result = true;
  int right = 0, left = 0, len = str.size(), dot = 0, op = 1;
  result = StartEndValid(str, len);
  for (int i = 0; i < len && result; i++) {
    if (str[i] == ' ' || str[i] == 'e') continue;
    if (str[i] == ')') {
      right++;
      if (left > 0 && left == right) {
        if (op == 0) result = false;
        op = 2;
      }
      if (left < right) result = false;
    }
    if (str[i] == '(') left++;

    if (OnceValid(str, &i, &dot, &op)) {
      result = result && result;
    } else if (DoubleValid(str, &i, &left)) {
      result = result && result;
    } else if (TripleValid(str, &i, &dot, &op, &left)) {
      result = result && result;
    } else if (QuadroValid(str, &i, &op, &left)) {
      result = result && result;
    } else {
      result = false;
    }

    if (str[i] == '(' && str[i + 1] == ')') {
      result = false;
    }
  }
  if (op == 0) result = false;
  if (right != left) result = false;
  return result;
}

bool s21::ModelCalculator::StartEndValid(const std::string &str, int len) {
  bool result = true;
  if (std::strchr("0123456789).x\0", str[len - 1])) {
    result = true;
  } else {
    result = false;
  }
  if (std::strchr("^/*m.)", str[0])) result = false;
  return result;
}

bool s21::ModelCalculator::OnceValid(const std::string &str, int *i, int *dot,
                                     int *op) {
  bool result = true;
  if (str[*i] == '(') {
    *op = 1;
    if (*op == 1 && *op == 3 && *i != 0) result = false;
    if (std::strchr("/*^", str[*i + 1])) result = false;
  } else if (str[*i] == ')') {
    *op = 1;
    if (!std::strchr("+-/*^)m ", str[*i + 1])) result = false;
  } else if (std::strchr("+-/*^", str[*i])) {
    result = result && result;
    if (std::strchr("+-/*^m)", str[*i + 1])) result = false;
    if (*i == 0 && std::strchr("+-", str[*i]) &&
        !(std::strchr("+-/*^m)", str[*i + 1]))) {
      *op = 3;
      result = true;
    } else {
      *op = 0;
      *dot = 0;
    }
  } else if (str[*i] == '.' && (std::isdigit(str[*i + 1])) && *dot == 0 &&
             (std::isdigit(str[*i - 1])) && *i != 0) {
    *dot = 1;
    result = result && result;
  } else if (str[*i] == 'x') {
    *op = 1;
    if (!std::strchr("+-/*^m) ", str[*i + 1])) result = false;
  } else if (std::isdigit(str[*i])) {
    *op = 1;
    if (!std::strchr("0123456789.+-/*^m)e ", str[*i + 1])) result = false;
  } else {
    result = false;
  }
  return result;
}

bool s21::ModelCalculator::DoubleValid(const std::string &str, int *i,
                                       int *left) {
  bool result = true;
  if (str[*i] == 'l' && str[*i + 1] == 'n' && str[*i + 2] == '(') {
    if (str[*i + 3] == '/' || str[*i + 3] == '*' || str[*i + 3] == '^' ||
        str[*i + 3] == 'm' || str[*i + 3] == ')' || str[*i + 3] == '.')
      result = false;
    (*left)++;
    (*i) += 2;
  } else {
    result = false;
  }
  return result;
}

bool s21::ModelCalculator::TripleValid(const std::string &str, int *i, int *dot,
                                       int *op, int *left) {
  bool result = true;
  if ((str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd')) {
    if (str[*i + 3] == '+' || str[*i + 3] == '-' || str[*i + 3] == '/' ||
        str[*i + 3] == '*' || str[*i + 3] == '^' || str[*i + 3] == '.')
      result = false;
    if (*op == 0) result = false;
    *op = 0;
    *dot = 0;
    (*i) += 2;
    result = result && result;
  } else if ((str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n' &&
              str[*i + 3] == '(') ||
             (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's' &&
              str[*i + 3] == '(') ||
             (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n' &&
              str[*i + 3] == '(') ||
             (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g' &&
              str[*i + 3] == '(')) {
    if (str[*i + 4] == '/' || str[*i + 4] == '*' || str[*i + 4] == '^' ||
        str[*i + 4] == 'm' || str[*i + 4] == ')' || str[*i + 4] == '.')
      result = false;
    (*left)++;
    if (*op == 0 || *op == 3 || *i == 0 || str[*i - 1] == '(') {
      result = result && result;
    } else {
      result = false;
    }
    (*i) += 3;
  } else {
    result = false;
  }
  return result;
}

bool s21::ModelCalculator::QuadroValid(const std::string &str, int *i, int *op,
                                       int *left) {
  bool result = true;
  if ((str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'i' &&
       str[*i + 3] == 'n' && str[*i + 4] == '(') ||
      (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' &&
       str[*i + 3] == 's' && str[*i + 4] == '(') ||
      (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' &&
       str[*i + 3] == 'n' && str[*i + 4] == '(') ||
      (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
       str[*i + 3] == 't' && str[*i + 4] == '(')) {
    if (str[*i + 5] == '/' || str[*i + 5] == '*' || str[*i + 5] == '^' ||
        str[*i + 5] == 'm' || str[*i + 4] == ')' || str[*i + 4] == '.')
      result = false;
    (*left)++;
    if (*op == 0 || *op == 3 || *i == 0 || str[*i - 1] == '(') {
      result = result && result;
    } else {
      result = false;
    }
    (*i) += 4;
  } else {
    result = false;
  }
  return result;
}

bool s21::ModelCalculator::ValidatorInputNumber(const std::string &line_text) {
  bool result = true;
  if (line_text != "") {
    char last_symbol = line_text[line_text.size() - 1];
    if (std::strchr(")x", last_symbol)) result = false;
  }
  return result;
}

bool s21::ModelCalculator::ValidatorInputDot(const std::string &line_text) {
  bool result = true;
  char last_symbol = line_text[line_text.size() - 1];
  if (!(std::isdigit(last_symbol))) result = false;
  return result;
}

bool s21::ModelCalculator::ValidatorInputX(const std::string &line_text) {
  bool result = true;
  if (line_text != "") {
    char last_symbol = line_text[line_text.size() - 1];
    if (std::strchr(")x.", last_symbol) || std::isdigit(last_symbol))
      result = false;
  }
  return result;
}

bool s21::ModelCalculator::ValidatorInputBracket(const std::string &button_text,
                                                 const std::string &line_text) {
  bool result = true;
  char last_symbol = line_text[line_text.size() - 1];
  if (button_text == "(") {
    if (line_text != "") {
      if (std::strchr(")x.", last_symbol) || std::isdigit(last_symbol))
        result = false;
    }
  } else if (button_text == ")") {
    if (line_text == "") {
      result = false;
    } else {
      if (std::strchr("+-d^*/(.", last_symbol)) result = false;
    }
  } else {
    result = false;
  }
  return result;
}

bool s21::ModelCalculator::ValidatorInputOperation(
    const std::string &button_text, const std::string &line_text) {
  bool result = true;
  char last_symbol = line_text[line_text.size() - 1];
  if (std::strchr("^*/m", button_text[0])) {
    if (line_text == "") {
      result = false;
    } else {
      if (std::strchr("(+-d^*/.", last_symbol)) result = false;
    }
  } else if (std::strchr("+-", button_text[0])) {
    if (line_text != "") {
      if (std::strchr("+-d^*/.", last_symbol)) result = false;
    }
  } else {
    result = false;
  }
  return result;
}

bool s21::ModelCalculator::ValidatorInputFunction(
    const std::string &line_text) {
  bool result = true;
  if (line_text != "") {
    char last_symbol = line_text[line_text.size() - 1];
    if (std::strchr(")x.", last_symbol) || std::isdigit(last_symbol))
      result = false;
  }
  return result;
}

const std::map<std::string, s21::ModelCalculator::Lexeme>
    s21::ModelCalculator::map_lexeme_ = {
        {"(", LEFT},    {")", RIGHT},   {"cos", COS},   {"sin", SIN},
        {"tan", TAN},   {"acos", ACOS}, {"asin", ASIN}, {"atan", ATAN},
        {"sqrt", SQRT}, {"ln", LN},     {"log", LOG},   {"+", PLUS},
        {"-", MINUS},   {"mod", MOD},   {"*", MUL},     {"/", DIV},
        {"^", POW},     {"~", uMINUS},  {"x", X}};

void s21::ModelCalculator::Input(const std::string &input, double x) {
  input_ = input;
  x_ = x;
  flag_ = true;
  infix_.clear();
  postfix_.clear();
  while (!stack_.empty()) {
    stack_.pop();
  }
  while (!calculate_.empty()) {
    calculate_.pop();
  }
  CreateInfix();
  // PrintInfix();
  CreatePostfix();
  // PrintPostfix();
}

void s21::ModelCalculator::CreateInfix() {
  for (std::string::iterator i = input_.begin(); i != input_.end() && flag_;
       i++) {
    if (*i == ' ') {
      continue;
    } else if (isdigit(*i)) {
      ParseOperand(&i);
    } else {
      ParseOperation(&i);
    }
  }
}

void s21::ModelCalculator::ParseOperand(std::string::iterator *i) {
  std::string number_str = std::string(&(*i)[0]);
  size_t count = 0;
  double number = std::stod(number_str, &count);
  *i += count - 1;
  infix_.emplace_back(Union_{NUMBER, number, LexemeToPriority(NUMBER)});
}

void s21::ModelCalculator::ParseOperation(std::string::iterator *i) {
  if (**i == '+' || **i == '-') {
    if (infix_.empty() || infix_.at(infix_.size() - 1).lexeme == LEFT) {
      if (**i == '+') {
        infix_.emplace_back(Union_{uPLUS, 0, LexemeToPriority(uPLUS)});
      } else if (**i == '-') {
        infix_.emplace_back(Union_{uMINUS, 0, LexemeToPriority(uMINUS)});
      }
    } else {
      if (**i == '+') {
        infix_.emplace_back(Union_{PLUS, 0, LexemeToPriority(PLUS)});
      } else if (**i == '-') {
        infix_.emplace_back(Union_{MINUS, 0, LexemeToPriority(MINUS)});
      }
    }
  } else {
    flag_ = false;
    for (std::pair<std::string, s21::ModelCalculator::Lexeme> pair :
         map_lexeme_) {
      const std::string &str = pair.first;
      const s21::ModelCalculator::Lexeme &lexeme = pair.second;
      if (!strncmp(&(*i[0]), str.data(), str.size())) {
        infix_.emplace_back(Union_{lexeme, 0, LexemeToPriority(lexeme)});
        *i += str.size() - 1;
        flag_ = true;
      }
    }
  }
}

int s21::ModelCalculator::LexemeToPriority(Lexeme lexeme) {
  int result = 0;
  if (lexeme == NUMBER || lexeme == LEFT || lexeme == RIGHT || lexeme == X) {
    result = 0;
  } else if (lexeme == PLUS || lexeme == MINUS || lexeme == MOD ||
             lexeme == uPLUS) {
    result = 1;
  } else if (lexeme == MUL || lexeme == DIV) {
    result = 2;
  } else if (lexeme == POW || lexeme == uMINUS) {
    result = 3;
  } else if (lexeme == COS || lexeme == SIN || lexeme == TAN ||
             lexeme == ACOS || lexeme == ASIN || lexeme == ATAN ||
             lexeme == SQRT || lexeme == LN || lexeme == LOG) {
    result = 4;
  }
  return result;
}

void s21::ModelCalculator::CreatePostfix() {
  for (std::vector<s21::ModelCalculator::Union_>::iterator i = infix_.begin();
       i != infix_.end() && flag_; i++) {
    Lexeme lexeme = i->lexeme;
    if (lexeme == NUMBER || lexeme == X) {
      postfix_.push_back(*i);
    } else if (lexeme == LEFT) {
      stack_.push(*i);
    } else if (lexeme == COS || lexeme == SIN || lexeme == TAN ||
               lexeme == ACOS || lexeme == ASIN || lexeme == ATAN ||
               lexeme == SQRT || lexeme == LN || lexeme == LOG) {
      stack_.push(*i);
    } else if (lexeme == PLUS || lexeme == MINUS || lexeme == MUL ||
               lexeme == DIV || lexeme == POW || lexeme == MOD ||
               lexeme == uMINUS) {
      PriorityCompare(*i, ((!stack_.empty()) ? stack_.top().priority : 0),
                      i->priority);
    } else if (lexeme == RIGHT) {
      PriorityCompare();
    }
  }
  while (!stack_.empty() && flag_) {
    if (stack_.top().lexeme == LEFT || stack_.top().lexeme == RIGHT) {
      flag_ = false;
    }
    if (flag_) {
      postfix_.push_back(stack_.top());
      stack_.pop();
    }
  }
}

void s21::ModelCalculator::PriorityCompare(Union_ &i, int pr_stack,
                                           int pr_infix) {
  while (!stack_.empty()) {
    if (!(HigherPriority(pr_stack, pr_infix, i))) break;
    postfix_.push_back(stack_.top());
    stack_.pop();
    if (!stack_.empty()) pr_stack = stack_.top().priority;
  }
  stack_.push(i);
}

bool s21::ModelCalculator::HigherPriority(int pr_stack, int pr_infix,
                                          Union_ &i) {
  return (pr_stack > pr_infix ||
          (pr_stack == pr_infix &&
           ((i.lexeme != POW && i.lexeme != uMINUS) ||
            (stack_.top().lexeme != POW && stack_.top().lexeme != uMINUS))));
}

void s21::ModelCalculator::PriorityCompare() {
  if (!stack_.empty()) {
    while (!stack_.empty()) {
      if (stack_.top().lexeme == LEFT) break;
      postfix_.push_back(stack_.top());
      stack_.pop();
    }
    if (stack_.empty()) {
      flag_ = false;
    } else if (stack_.top().lexeme == LEFT) {
      stack_.pop();
    }
  } else {
    flag_ = false;
  }
}

double s21::ModelCalculator::Calculate() {
  double result = 0;
  for (std::vector<s21::ModelCalculator::Union_>::iterator i = postfix_.begin();
       i != postfix_.end() && flag_; i++) {
    Lexeme lexeme = i->lexeme;
    if (lexeme == NUMBER) {
      calculate_.push(i->value);
    } else if (lexeme == X) {
      calculate_.push(x_);
    } else if (lexeme == uMINUS) {
      calculate_.top() *= -1;
    } else if (lexeme == PLUS || lexeme == MINUS || lexeme == MUL ||
               lexeme == DIV || lexeme == POW || lexeme == MOD) {
      calculate_.push(Operation(lexeme));
    } else if (lexeme == COS || lexeme == SIN || lexeme == TAN ||
               lexeme == ACOS || lexeme == ASIN || lexeme == ATAN ||
               lexeme == SQRT || lexeme == LN || lexeme == LOG) {
      calculate_.push(Function(lexeme));
    }
  }
  result = calculate_.top();
  return result;
}

double s21::ModelCalculator::Function(Lexeme lexeme) {
  double value = calculate_.top();
  calculate_.pop();
  double result = 0;
  if (lexeme == SIN) {
    result = std::sin(value);
  } else if (lexeme == COS) {
    result = std::cos(value);
  } else if (lexeme == TAN) {
    result = std::tan(value);
  } else if (lexeme == ASIN) {
    result = std::asin(value);
  } else if (lexeme == ACOS) {
    result = std::acos(value);
  } else if (lexeme == ATAN) {
    result = std::atan(value);
  } else if (lexeme == SQRT) {
    result = std::sqrt(value);
  } else if (lexeme == LN) {
    result = std::log(value);
  } else if (lexeme == LOG) {
    result = std::log10(value);
  }
  return result;
}

double s21::ModelCalculator::Operation(Lexeme lexeme) {
  double b = calculate_.top();
  calculate_.pop();
  double a = calculate_.top();
  calculate_.pop();
  double result = 0;
  if (lexeme == PLUS) {
    result = a + b;
  } else if (lexeme == MINUS) {
    result = a - b;
  } else if (lexeme == MUL) {
    result = a * b;
  } else if (lexeme == DIV) {
    result = a / b;
  } else if (lexeme == POW) {
    result = std::pow(a, b);
  } else if (lexeme == MOD) {
    result = std::fmod(a, b);
  }
  return result;
}

// void s21::ModelCalculator::PrintInfix() {
//     for (auto j : infix_) {
//       std::cout<<j.lexeme<<" ";
//       std::cout<<j.value<<" ";
//       std::cout<<j.priority<<std::endl;
//     }
// };

// void s21::ModelCalculator::PrintPostfix() {
//     for (auto j : postfix_) {
//       std::cout<<j.lexeme<<" ";
//       std::cout<<j.value<<" ";
//       std::cout<<j.priority<<std::endl;
//     }
// };
