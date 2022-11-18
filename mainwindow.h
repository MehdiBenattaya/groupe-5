#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
///////////////////////////////////////////////////////////////////////////////

    void on_pushButton_ajout_ich_clicked();

    void on_pushButton_annuler_ich_clicked();

    void on_pb_supprimer_ich_clicked();

    void on_pushButton_modif_ich_clicked();

    void on_pb_recherche_ich_clicked();

    void on_pushButton_trierid_ich_clicked();

    void on_pushButton_triernom_ich_clicked();

    void on_pushButton_triersalaire_ich_clicked();

    void on_pushButton_excel_ich_clicked();

    void on_pushButton_pdf_ich_clicked();


    void on_TableView_ich_doubleClicked(const QModelIndex &index);

    void on_btnLogin_4_clicked();

    void on_pb_deconnexion_clicked();

    void on_pushButton_stat_ich_clicked();

private:
    Ui::MainWindow *ui;
    Employe E;
    QMessageBox msgBox;

};

#endif // MAINWINDOW_H
