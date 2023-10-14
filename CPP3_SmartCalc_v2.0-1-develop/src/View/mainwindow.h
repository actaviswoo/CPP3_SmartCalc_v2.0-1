#ifndef SRC_VIEW_MAINWINDOW_H
#define SRC_VIEW_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_actionCalculator_triggered();

  void on_actionCredit_triggered();

  void on_actionDeposit_triggered();

 private:
  Ui::MainWindow *ui_;
};

#endif  // SRC_VIEW_MAINWINDOW_H
