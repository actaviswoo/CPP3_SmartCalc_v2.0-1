#ifndef SRC_VIEW_CREDITWINDOW_H
#define SRC_VIEW_CREDITWINDOW_H

#include <QLabel>
#include <QWidget>

#include "../Controller/creditcontroller.h"

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QWidget {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();

 private slots:
  void GetTypes();
  void OutputResult();
  void SetDefault();
  void SetNull();

 private:
  Ui::CreditWindow *ui_;
  double totalCreditAmount_ = 0;
  int term_ = 0;
  double interestRate_ = 0;
  int type_ = 1;
  double monthlyPayment_ = 0;
  double overpaymentOnCredit_ = 0;
  double totalPayment_ = 0;
  double diffMonthlyPaymentMax_ = 0;
  double diffMonthlyPaymentMin_ = 0;
  s21::CreditController *controller_;
};

#endif  // SRC_VIEW_CREDITWINDOW_H
