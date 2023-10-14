#ifndef SRC_CONTROLLER_CALCULATORCONTROLLER_H
#define SRC_CONTROLLER_CALCULATORCONTROLLER_H

#include "../Model/calculatormodel.h"

namespace s21 {

class CalculatorController {
 public:
  CalculatorController(){};
  ~CalculatorController(){};

  void Input(const std::string &input, double x);
  double Calculate();

  bool Validator(const std::string &input);
  bool ValidatorInputNumber(const std::string &line_text);
  bool ValidatorInputDot(const std::string &line_text);
  bool ValidatorInputX(const std::string &line_text);
  bool ValidatorInputBracket(const std::string &button_text,
                             const std::string &line_text);
  bool ValidatorInputOperation(const std::string &button_text,
                               const std::string &line_text);
  bool ValidatorInputFunction(const std::string &line_text);

 private:
  s21::ModelCalculator modelCalculator_;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_CALCULATORCONTROLLER_H
