#ifndef CPP3_S21_SMARTCALC_V2_0_FRONTEND_RESULTDIALOG_H_
#define CPP3_S21_SMARTCALC_V2_0_FRONTEND_RESULTDIALOG_H_

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace s21 {
class ResultDialog : public QDialog {
  Q_OBJECT

 public:
  explicit ResultDialog(QWidget *parent = nullptr) : QDialog(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    result_label_ = new QLabel(this);
    result_label_->setStyleSheet("QLabel { color : white; }");

    layout->addWidget(result_label_);
  }

  void setResultText(const QString &text) { result_label_->setText(text); }

 private:
  QLabel *result_label_;
};
}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V2_0_FRONTEND_RESULTDIALOG_H_
