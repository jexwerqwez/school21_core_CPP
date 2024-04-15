#include <QApplication>

#include "./backend/s21_smartcalc_controller.h"
#include "./frontend/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  std::locale::global(std::locale("C"));
  s21::S21SmartCalcController controller;
  s21::MainWindow main_window(&controller);

  QObject::connect(&main_window, &s21::MainWindow::CalculateExpression,
                   &controller,
                   &s21::S21SmartCalcController::OnCalculateExpression);
  QObject::connect(&controller,
                   &s21::S21SmartCalcController::SendCalculationResult,
                   &main_window, &s21::MainWindow::DisplayResult);

  main_window.show();

  return a.exec();
}
