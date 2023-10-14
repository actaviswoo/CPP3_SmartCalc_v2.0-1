#ifndef SRC_VIEW_CALCULATORWINDOW_H
#define SRC_VIEW_CALCULATORWINDOW_H

#include <QVector>
#include <QWidget>

#include "../Controller/calculatorcontroller.h"

namespace Ui {
class CalculatorWindow;
}

class CalculatorWindow : public QWidget {
  Q_OBJECT

 public:
  explicit CalculatorWindow(QWidget *parent = nullptr);
  ~CalculatorWindow();

 private slots:
  void InputNumber();
  void InputOperation();
  void OutputResult();
  void InputClear();
  void InputDot();
  void InputBracket();
  void InputX();
  void InputFunction();
  void InputClearLast();
  void OutputGraph();

 private:
  Ui::CalculatorWindow *ui_;
  double xBegin_, xEnd_, h_, X_;
  int N_;
  QVector<double> x_, y_;
  s21::CalculatorController controller_;
};

#endif  // SRC_VIEW_CALCULATORWINDOW_H
