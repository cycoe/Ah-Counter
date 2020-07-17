#ifndef NAMEEDITOR_H
#define NAMEEDITOR_H

#include <QDialog>

namespace Ui {
  class NameEditor;
}

class NameEditor : public QDialog
{
  Q_OBJECT

public:
  explicit NameEditor(QWidget *parent = nullptr);
  ~NameEditor();
  void add_name(QString const& name);
  QList<QString> const& get_names_to_remove();

private:
  Ui::NameEditor *ui;
  QList<QString> names_to_remove;
};

#endif // NAMEEDITOR_H
