#ifndef COUNTBOX_H
#define COUNTBOX_H

#include <QWidget>

namespace Ui {
  class CountBox;
}

class CountBox : public QWidget
{
  Q_OBJECT

public:
  explicit CountBox(QWidget *parent = nullptr);
  ~CountBox();
  void set_label(QString const&);
  QString text();
  void set_text(QString const&);

signals:
  void text_changed();

private slots:
  void on_btn_plus_clicked();
  void on_btn_less_clicked();

private:
  Ui::CountBox *ui;
  static std::size_t const count_max = 999;
};

#endif // COUNTBOX_H
