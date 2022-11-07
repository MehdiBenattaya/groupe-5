#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "podcast.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_podcast->setModel(P.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    int nmbdeparticipants=ui->lineEdit_nmbdeparticipants->text().toInt();
    QString script=ui->lineEdit_script->text();
    QString duree=ui->lineEdit_duree->text();
    QString date=ui->lineEdit_date->text();
    QString heure=ui->lineEdit_heure->text();
    QString sujet=ui->lineEdit_sujet->text();
Podcast P(id, sujet, nmbdeparticipants, script, duree, date, heure);
bool test=P.ajouter();

QMessageBox msgBox;

if(test)
{msgBox.setText("ajout avec succes.");
ui->tab_podcast->setModel(P.afficher());
}

else
    msgBox.setText("echec de l'ajout");
    msgBox.exec();


}



void MainWindow::on_pushButton_supprimer_clicked()
{
    Podcast P1; P1.setid(ui->lineEdit_id_supp->text().toInt());
    bool test=P1.supprimer(P1.getid());

    QMessageBox msgBox;

    if(test)
    {msgBox.setText("suppression avec succes.");
    ui->tab_podcast->setModel(P.afficher());
    }

    else
        msgBox.setText("echec de suppression");
        msgBox.exec();


}







