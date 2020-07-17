#include "countbox.h"
#include "ui_countbox.h"

#include <QValidator>

CountBox::CountBox(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CountBox)
{
  ui->setupUi(this);
  ui->le->setValidator(new QIntValidator(0, 100, ui->le));
  connect(ui->le, &QLineEdit::textChanged, this, &CountBox::text_changed);
}

CountBox::~CountBox()
{
  delete ui;
}

void CountBox::set_label(const QString &label)
{
  ui->lbl->setText(label);
}

QString CountBox::text()
{
  return ui->le->text();
}

void CountBox::set_text(const QString &str)
{
  ui->le->setText(str);
}

void CountBox::on_btn_plus_clicked()
{
  std::size_t count = ui->le->text().toUInt();
  if (count < 100)
    ui->le->setText(QString::number(++count));
}

void CountBox::on_btn_less_clicked()
{
  std::size_t count = ui->le->text().toUInt();
  if (count > 0)
    ui->le->setText(QString::number(--count));
}
