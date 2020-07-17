#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QList>
#include <QHBoxLayout>
#include "recorder.h"
#include "nameeditor.h"
#include "countbox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddName_clicked();
    void on_btnAddSpecie_clicked();
    void on_cbName_currentIndexChanged(const QString&);
    void on_countbox_text_changed(QString const&, CountBox*);
    void on_leName_textChanged(const QString &arg1);
    void on_leSpecie_textChanged(const QString &arg1);
    void on_action_export_triggered();
    void on_action_names_triggered();
    void on_action_species_triggered();
    void on_name_edit_finished(int);
    void on_specie_edit_finished(int);

private:
    void add_name(QString const&);
    void add_specie(QString const&);
    void remove_name(QString const&);
    void remove_specie(QString const&);
    void add_specie_widget(QString const&);
    void add_connects();

    Ui::MainWindow *ui = nullptr;
    Recorder *recorder = nullptr;
    NameEditor* name_editor = nullptr;
    NameEditor* specie_editor = nullptr;
    QList<CountBox*> specie_widgets;
};
#endif // MAINWINDOW_H
