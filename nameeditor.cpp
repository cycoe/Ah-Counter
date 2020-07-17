#include "nameeditor.h"
#include "ui_nameeditor.h"

#include <QListWidgetItem>

NameEditor::NameEditor(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::NameEditor)
{
  ui->setupUi(this);
}

NameEditor::~NameEditor()
{
  delete ui;
}

void NameEditor::add_name(const QString &name)
{
  QListWidgetItem* item = new QListWidgetItem(name, ui->lw_names);
  item->setCheckState(Qt::Checked);
  ui->lw_names->addItem(item);
}

QList<QString> const& NameEditor::get_names_to_remove()
{
  QListWidgetItem* item;
  for (int row = 0; row < ui->lw_names->count(); ++row) {
    item = ui->lw_names->item(row);
    if (item->checkState() == Qt::Unchecked) {
        names_to_remove.push_back(item->text());
      }
  }
  return names_to_remove;
}
