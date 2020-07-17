#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , recorder(new Recorder)
{
    ui->setupUi(this);
    add_connects();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete recorder;
}

void MainWindow::add_name(const QString &name)
{
  if (recorder->find_name(name.toStdString())) {
      ui->statusbar->showMessage("Name exists!", 3000);
      return;
    }
    recorder->add_name(name.toStdString());
    ui->cbName->addItem(name);
    ui->cbName->setCurrentText(name);
}

void MainWindow::add_specie(const QString &specie)
{
  if (recorder->find_specie(specie.toStdString())) {
      ui->statusbar->showMessage("Specie exists!", 3000);
      return;
    }
    recorder->add_specie(specie.toStdString());
    add_specie_widget(specie);
}

void MainWindow::remove_name(const QString &name)
{
  if (!recorder->find_name(name.toStdString())) {
     ui->statusbar->showMessage("No name deleted!", 3000);
     return;
  }
  Recorder::names_size_type index = recorder->name_index(name.toStdString());
  recorder->remove_name(name.toStdString());
  ui->cbName->removeItem(index);
}

void MainWindow::remove_specie(const QString &specie)
{
  if (!recorder->find_specie(specie.toStdString())) {
    ui->statusbar->showMessage("No specie found!", 3000);
  }
  // Before remove the specie from recorder, get the index first
  std::size_t index = recorder->specie_index(specie.toStdString());
  // remove specie from recorder species list
  recorder->remove_specie(specie.toStdString());
  // remove widget from layout
  ui->verticalLayout->removeWidget(specie_widgets[index]);
  // destruct widget
  delete specie_widgets[index];
  // remove widget pointer from list
  specie_widgets.erase(specie_widgets.begin() + index);
}

void MainWindow::add_connects()
{
  connect(ui->action_Export, &QAction::triggered,
          this, &MainWindow::on_action_export_triggered);
  connect(ui->action_Names, &QAction::triggered,
          this, &MainWindow::on_action_names_triggered);
  connect(ui->actionS_pecies, &QAction::triggered,
          this, &MainWindow::on_action_species_triggered);
}

void MainWindow::on_countbox_text_changed(QString const& specie,
                                          CountBox* countbox)
{
  QString const& name = ui->cbName->currentText();
  std::size_t& count = recorder->
      by_name_specie(name.toStdString(), specie.toStdString());

  bool converted;
  std::size_t new_count = countbox->text().toUInt(&converted);
  if (converted)
    count = new_count;
}

void MainWindow::add_specie_widget(const QString &specie)
{
    auto* count_box = new CountBox(this);
    count_box->set_label(specie);
    specie_widgets.push_back(count_box);
    ui->verticalLayout->addWidget(count_box);
    // pointer count_box is a local valiable, so we must pass it by
    // value
    connect(count_box, &CountBox::text_changed, this, [=]() {
       this->on_countbox_text_changed(specie, count_box);
    });
}

void MainWindow::on_btnAddName_clicked()
{
    QString name = ui->leName->text();
    add_name(name);
    ui->leName->setText("");
}

void MainWindow::on_cbName_currentIndexChanged(const QString &name)
{
  Recorder::count_type count = recorder->by_name(name.toStdString());
  for (Recorder::count_size_type i = 0; i < count.size(); ++i) {
    specie_widgets[i]->set_text(QString::number(count[i]));
  }
}

void MainWindow::on_btnAddSpecie_clicked()
{
  QString specie = ui->leSpecie->text();
  add_specie(specie);
  ui->leSpecie->setText("");
}

void MainWindow::on_leName_textChanged(const QString &text)
{
  ui->btnAddName->setEnabled(!text.isEmpty());
}

void MainWindow::on_leSpecie_textChanged(const QString &text)
{
  ui->btnAddSpecie->setEnabled(!text.isEmpty());
}

void MainWindow::on_action_export_triggered()
{
  QString file_name;
  file_name = QFileDialog::getSaveFileName(this, "Export to",
                                           "", "Text File(*.txt)");
  std::ofstream ofs(file_name.toStdString());
  recorder->export_data(std::ostream_iterator<std::string>(ofs));
  ofs.close();
}

void MainWindow::on_action_names_triggered()
{
  NameEditor name_editor(this);
  for (auto const& name : recorder->names()) {
   name_editor.add_name(QString::fromStdString(name));
  }
  name_editor.setWindowModality(Qt::ApplicationModal);
  if (name_editor.exec() == QDialog::Accepted) {
    QList<QString> const& names_to_remove = name_editor.get_names_to_remove();
    for (auto const& name : names_to_remove) {
      remove_name(name);
    }
  }
}

void MainWindow::on_action_species_triggered()
{
  NameEditor specie_editor(this);
  for (auto const& specie : recorder->species()) {
    specie_editor.add_name(QString::fromStdString(specie));
  }
  specie_editor.setWindowModality(Qt::ApplicationModal);
  if (specie_editor.exec() == QDialog::Accepted) {
    QList<QString> const& species_to_remove = specie_editor.get_names_to_remove();
    for (auto const& specie : species_to_remove) {
      remove_specie(specie);
    }
  }
}
