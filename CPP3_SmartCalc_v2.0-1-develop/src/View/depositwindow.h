#ifndef SRC_VIEW_DEPOSITWINDOW_H
#define SRC_VIEW_DEPOSITWINDOW_H

#include <QComboBox>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include "../Controller/depositcontroller.h"

namespace Ui {
class DepositWindow;
}

class DepositWindow : public QWidget {
  Q_OBJECT

 public:
  explicit DepositWindow(QWidget *parent = nullptr);
  ~DepositWindow();

  struct DepositBox {
    QVector<QDateEdit *> vectorDateEdit_;
    QVector<QDoubleSpinBox *> vectorDoubleSpinBox_;
    QVector<QComboBox *> vectorComboBox_;
  };
 private slots:
  void GetTypes();
  void SetDefault();
  void OutputResult();
  void AddClicked(bool flag, DepositWindow::DepositBox *box);
  void DeleteClicked(int *count, DepositWindow::DepositBox *box,
                     QVBoxLayout *boxlayout);
  void GetDepositData(s21::DepositData *data, DepositWindow::DepositBox *box,
                      int count);
  void Add(bool flag);
  void CreateComboBox();
  void CreateDateEdit();
  void CreateDoubleSpinBox();
  void SetNull();

 private:
  Ui::DepositWindow *ui_;
  s21::DepositController controller_;
  double depositAmount_ = 0;
  int depositTerm_ = 0;
  double interestRate_ = 0;
  double taxRate_ = 0;
  int period_ = 0;
  bool capitalization_ = false;
  s21::DepositData replenishments_;
  s21::DepositData withdrawals_;
  double accruedInterest_ = 0;
  double taxAmount_ = 0;
  double depositEnd_ = 0;
  double depositTotal_ = 0;

  int replenishmentsCount_ = 0;
  int withdrawalsCount_ = 0;
  QDate lastDate_;

  QDateEdit *dateEdit_;
  QDoubleSpinBox *doubleSpinBox_;
  QComboBox *comboBox_;

  DepositBox replenishmentsBox_;
  DepositBox withdrawalsBox_;
  QVBoxLayout *replenishmentsBoxLayout_;
  QVBoxLayout *withdrawalsBoxLayout_;
};

#endif  // SRC_VIEW_DEPOSITWINDOW_H
