#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "./View/mainwindow.h"

int main(int argc, char *argv[]) {
  setenv("LC_NUMERIC", "C", 1);
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(":/icons/icon.png"));
  MainWindow w;
  w.show();
  return a.exec();
}
