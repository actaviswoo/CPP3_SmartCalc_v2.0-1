#include "calculatorcontroller.h"

void s21::CalculatorController::Input(const std::string &input, double x) {
  modelCalculator_.Input(input, x);
}

double s21::CalculatorController::Calculate() {
  return modelCalculator_.Calculate();
}

bool s21::CalculatorController::Validator(const std::string &input) {
  return modelCalculator_.Validator(input);
}

bool s21::CalculatorController::ValidatorInputNumber(
    const std::string &line_text) {
  return modelCalculator_.ValidatorInputNumber(line_text);
}

bool s21::CalculatorController::ValidatorInputDot(
    const std::string &line_text) {
  return modelCalculator_.ValidatorInputDot(line_text);
}

bool s21::CalculatorController::ValidatorInputX(const std::string &line_text) {
  return modelCalculator_.ValidatorInputX(line_text);
}

bool s21::CalculatorController::ValidatorInputBracket(
    const std::string &button_text, const std::string &line_text) {
  return modelCalculator_.ValidatorInputBracket(button_text, line_text);
}

bool s21::CalculatorController::ValidatorInputOperation(
    const std::string &button_text, const std::string &line_text) {
  return modelCalculator_.ValidatorInputOperation(button_text, line_text);
}

bool s21::CalculatorController::ValidatorInputFunction(
    const std::string &line_text) {
  return modelCalculator_.ValidatorInputFunction(line_text);
}
