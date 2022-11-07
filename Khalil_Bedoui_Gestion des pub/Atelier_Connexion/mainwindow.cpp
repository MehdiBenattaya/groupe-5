#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Pub.h"
#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(100, 9999999, this));
    ui->tab_pub->setModel(p.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()  //Ajout
{
    int id=ui->le_id->text().toInt();
    QString titre=ui->titre->text();
    QString description=ui->description->text();
    QString type=ui->type->currentText();
    QString date=ui->date->text();

    PUB p(id,titre,description,type,date);
    bool test=p.ajouter();
    QMessageBox msgBox;
    if(test)
    {
    msgBox.setText("Ajout avec succes.");
    ui->tab_pub->setModel(p.afficher());
    }
    else
        msgBox.setText("Echec de l'Ajout");
        msgBox.exec();
}


void MainWindow::on_id_supp_clicked() //SUPPRESSION
{
    PUB p;
    p.setid(ui->le_id_supp->text().toInt());
    bool test=p.supprimer(p.getid());

    QMessageBox msgBox;
    if(test)
    {
    //ui->tab_pub->setModel(p.afficher());
    msgBox.setText("Suppression avec succes.");
    ui->tab_pub->setModel(p.afficher());
    }
else
    msgBox.setText("Echec de suppression");
    msgBox.exec();

}

void MainWindow::on_pb_update_clicked()  //UPDATE
{
    int id=ui->le_newid->text().toInt();
        QString titre= ui->le_newtitre->text();
        QString description=ui->le_newdescription->text();
        QString type=ui->le_newtype->currentText();
        QString date=ui->le_newdate->text();
        PUB p(id,titre,description,type,date);
        bool test=p.modifier();
        if (test)
         {
            ui->tab_pub->setModel(p.afficher());
            QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Modification effectue\n ""click cancel"),QMessageBox::Cancel);

         }
         else
         {
            QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Modification non fonctional\n""click to cancel"),QMessageBox::Cancel);}

}
/*{

    Actualite A1;
    QString id ;
         id= ui->le_recherche->text();
    ui->listView->setModel(A1.rechercher(id));



}*/


void MainWindow::on_type_2_activated()
{
    PUB p;
    QString type ;
         type= ui->type_2->currentText();
    ui->tab_pub->setModel(p.Rechercher(type));

}

void MainWindow::on_refresh_clicked()
{
    PUB p;
    ui->tab_pub->setModel(p.afficher());
}

void MainWindow::on_tab_pub_activated(const QModelIndex &index)
{


    QString id=ui->tab_pub->model()->data(index).toString();

    QSqlQuery qry;
    qry.prepare("select * FROM PUB1 WHERE ID='"+id+"' or TITRE='"+id+"' or DESCRIPTION='"+id+"' or TYPE='"+id+"' or DATE_P='"+id+"' or DESCRIPTION='"+id+"' " );

    if (qry.exec())
        {   while (qry.next())
                {
             ui->le_id_supp->setText(qry.value(0).toString());
                  ui->le_newid->setText(qry.value(0).toString());
                   ui->le_newtitre->setText(qry.value(1).toString());
                    ui->le_newdescription->setText(qry.value(2).toString());
                      ui->le_newdate->setText(qry.value(4).toString());
                }
        }
    }

