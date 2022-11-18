#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QDateTime>
#include <QTextStream>
#include <QtDebug>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->le_id_ich->setValidator(new QIntValidator(0, 99999, this));
    ui->le_numero_telephone_ich->setValidator(new QIntValidator(0, 99999999, this));
   ui->TableView_ich->setModel(E.afficher());
 }

MainWindow::~MainWindow()
{
    delete ui;
}

/////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButton_ajout_ich_clicked()
{
    QString id=ui->le_id_ich->text();
    QString numero_telephone=ui->le_numero_telephone_ich->text();
    QString salaire=ui->le_salaire_ich->text();
    QString nom=ui->le_nom_ich->text();
    QString prenom=ui->le_prenom_ich->text();
    QDate date_naissance=ui->dateEdit_ajout_ich->date();
    QString mdp = ui->le_mdp_ich->text();
    QString un = ui->le_nom_utilisateur_ich->text();
    QString type = ui->comboBox_type_ajout_ich->currentText();

    Employe E(id, numero_telephone,salaire,  nom, prenom, date_naissance,un,mdp,type);
    bool test=E.ajouter();
    if(test)
       {
                msgBox.setText("Ajout avec succes.");
                ui->TableView_ich->setModel(E.afficher());

        }
    else
            msgBox.setText("Echec de l'ajout.");

   msgBox.exec();
}

void MainWindow::on_pushButton_annuler_ich_clicked()
{
    ui->le_id_ich->clear();
    ui->le_nom_ich->clear();
    ui->le_mdp_ich->clear();
    ui->le_prenom_ich->clear();
    ui->le_nom_utilisateur_ich->clear();
    ui->le_salaire_ich->clear();
    ui->le_numero_telephone_ich->clear();
}

void MainWindow::on_pb_supprimer_ich_clicked()
{
    QString id_supp = ui->le_id_supp_ich->text();
    bool test = E.supprimer(id_supp);
    if(test)
    {
        msgBox.setText("Suppression avec succes.");
        ui->TableView_ich->setModel(E.afficher());
    }
    else
        msgBox.setText("Echec de suppression.");

    msgBox.exec();
}

void MainWindow::on_pushButton_modif_ich_clicked()
{
    QString id=ui->le_id_ich_mod->text();
    QString numero_telephone=ui->le_numero_telephone_ich_mod->text();
    QString salaire=ui->le_salaire_ich_mod->text();
    QString nom=ui->le_nom_ich_mod->text();
    QString prenom=ui->le_prenom_ich_mod->text();
    QDate date_naissance=ui->dateEdit_ajout_ich_mod->date();
    QString mdp = ui->le_mdp_ich_mod->text();
    QString un = ui->le_nom_utilisateur_ich_mod->text();
    QString type = ui->comboBox_type_ich_mod->currentText();

    Employe E(id,numero_telephone,salaire,nom,prenom,date_naissance,un,mdp,type);

    bool test=E.update();
    if (test)
        {
              QMessageBox::information(nullptr, QObject::tr("OK"),
                          QObject::tr("modification effectué.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
              ui->TableView_ich->setModel(E.afficher());


        }
          else
              QMessageBox::critical(nullptr, QObject::tr("not OK"),
                          QObject::tr("modification non effectué.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_recherche_ich_clicked()
{
           QString search=ui->le_recherche_ich->text();
           ui->TableView_ich->setModel(E.Rechercher(search));
}

void MainWindow::on_pushButton_trierid_ich_clicked()
{
    Employe E;

    ui->TableView_ich->setModel(E.tri());

    bool test=E.tri();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("tri effectué. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_triernom_ich_clicked()
{
    Employe E;

    ui->TableView_ich->setModel(E.trinom());

    bool test=E.tri();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("tri effectué. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_triersalaire_ich_clicked()
{
    Employe E;

    ui->TableView_ich->setModel(E.trisalaire());

    bool test=E.tri();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("tri effectué. \n"
                                             "click Cancel to exist."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("tri non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_excel_ich_clicked()
{
    QTableView *table;
                   table = ui->TableView_ich;

                   QString filters("CSV files (.csv);;All files (.*)");
                   QString defaultFilter("CSV files (*.csv)");
                   QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                      filters, &defaultFilter);
                   QFile file(fileName + ".csv");

                   QAbstractItemModel *model =  table->model();
                   if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                       QTextStream data(&file);
                       QStringList strList;
                       for (int i = 0; i < model->columnCount(); i++) {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");
                       }
                       data << strList.join(";") << "\n";
                       for (int i = 0; i < model->rowCount(); i++) {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++) {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") + "\n";
                       }
                       file.close();
                       QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
                   }
}

void MainWindow::on_pushButton_pdf_ich_clicked()
{
    QSqlQuery query;


       QString id=ui->TableView_ich->model()->data(ui->TableView_ich->model()->index(ui->TableView_ich->currentIndex().row(),0)).toString();

       QPdfWriter pdf("C:/Users/Ichrak/Desktop/employes.pdf");
           QPainter painter(&pdf);
           painter.setPen(Qt::red);
           painter.setFont(QFont("Arial", 30));
           painter.drawText(2000,1200,"ID Employé: "+id);

           painter.setPen(Qt::black);
           painter.setFont(QFont("Arial", 50));
           painter.drawRect(2000,3000,5000,9000);
           painter.setFont(QFont("Arial", 10));
           painter.drawText(2500,3300,"ID : ");
           painter.drawText(2500,3800,"Numero Téléphone: ");
           painter.drawText(2500,4300,"Salaire: ");
           painter.drawText(2500,4800,"Nom: ");
           painter.drawText(2500,5300,"Prenom: ");
           painter.drawText(2500,5800,"Date de naissance: ");
           painter.drawText(2500,6300,"Nom d'utilisateur: ");
           painter.drawText(2500,6800,"Mot de passe: ");
           painter.drawText(2500,7300,"Type: ");


           query.prepare("select * from employes WHERE id=:id");
           query.bindValue(":id",id);
           query.exec();
           while (query.next())
           {
               painter.drawText(4500,3300,query.value(0).toString());
               painter.drawText(4500,3800,query.value(1).toString());
               painter.drawText(4500,4300,query.value(2).toString());
               painter.drawText(4500,4800,query.value(3).toString());
               painter.drawText(4500,5300,query.value(4).toString());
               painter.drawText(4500,5800,query.value(5).toString());
               painter.drawText(4500,6300,query.value(6).toString());
               painter.drawText(4500,6800,query.value(7).toString());
               painter.drawText(4500,7300,query.value(8).toString());


           }

           int reponse = QMessageBox::question(this, "PDF généré avec succés", "Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
           if (reponse == QMessageBox::Yes)
           {
               QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Ichrak/Desktop/employes.pdf"));
               painter.end();
           }
           if (reponse == QMessageBox::No)
           {
               painter.end();
           }
}
void MainWindow::on_TableView_ich_doubleClicked(const QModelIndex &index)
{
    QString datestring = ui->TableView_ich->model()->data(ui->TableView_ich->model()->index(index.row(),5)).toString();
    QDate date=QDate::fromString(datestring,"dd-MMM-yy");
    ui->le_id_ich_mod->setText(ui->TableView_ich->model()->data(ui->TableView_ich->model()->index(index.row(),0)).toString());
    ui->le_numero_telephone_ich_mod->setText(ui->TableView_ich->model()->data(ui->TableView_ich->model()->index(index.row(),1)).toString());
    ui->le_salaire_ich_mod->setText(ui->TableView_ich->model()->data(ui->TableView_ich->model()->index(index.row(),2)).toString());
    ui->le_nom_ich_mod->setText(ui->TableView_ich->model()->data(ui->TableView_ich->model()->index(index.row(),3)).toString());
    ui->le_prenom_ich_mod->setText(ui->TableView_ich->model()->data(ui->TableView_ich->model()->index(index.row(),4)).toString());
    ui->le_nom_utilisateur_ich_mod->setText(ui->TableView_ich->model()->data(ui->TableView_ich->model()->index(index.row(),6)).toString());
    ui->le_mdp_ich_mod->setText(ui->TableView_ich->model()->data(ui->TableView_ich->model()->index(index.row(),7)).toString());
    ui->comboBox_type_ich_mod->setCurrentText(ui->TableView_ich->model()->data(ui->TableView_ich->model()->index(index.row(),8)).toString());


    ui->dateEdit_ajout_ich_mod->setDate(date);
    ui->TabWidget_gestion->setCurrentIndex(1);
}

void MainWindow::on_btnLogin_4_clicked()
{
    QString username = ui->le_username->text();
    QString password = ui->le_password->text();

    QSqlQuery query ;
    query.prepare("Select type from employes where (username = '"+username+"' AND password = '"+password+"') ");
    bool test = query.exec();
    bool find = false ;
    if (test)
    {
            while (query.next())
            {
                if (query.value(0).toString() == "Admin" )
                {
                    msgBox.setText(" Connecté !");
                    ui->stackedWidget->setCurrentIndex(1);
                    find = true ;
                }
                else if (query.value(0).toString() == "Musique")
                {
                     msgBox.setText(" pas de gestion de musique!");
                     find = true ;
                }

            }
            if (find == false)
                msgBox.setText(" erroné !!!");
    }

    msgBox.exec();





}

void MainWindow::on_pb_deconnexion_clicked()
{
    ui->le_username->clear();
    ui->le_password->clear();
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_pushButton_stat_ich_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT type FROM employes WHERE  type='Admin' ");
        float countAdmin=model->rowCount();
        model->setQuery("SELECT type FROM employes WHERE  type='Musique' ");
        float countMusique=model->rowCount();
        model->setQuery("SELECT type FROM employes WHERE  type='Podcast' ");
        float countPodcast=model->rowCount();
        model->setQuery("SELECT type FROM employes WHERE  type='Publicite' ");
        float countpub=model->rowCount();
        model->setQuery("SELECT type FROM employes WHERE  type='Actualite' ");
        float countAc=model->rowCount();

        float total=countAdmin+countAc+countpub+countMusique+countPodcast;

                QPieSeries *series = new QPieSeries();
                series->append("Admin",countAdmin);
                series->append("Actualité",countAc);
                series->append("Musique",countMusique);
                series->append("Podcast",countPodcast);
                 series->append("Publicite",countpub);

                if (countAdmin!=0)
                {QPieSlice *slice = series->slices().at(0);
                    slice->setLabel("Admin "+QString("%1%").arg(100*slice->percentage(),3,'f',1));
                    slice->setLabelVisible();
                    slice->setPen(QPen(Qt::black));}
                if ( countAc!=0)
                {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice1 = series->slices().at(1);
                    //slice1->setExploded();
                    slice1->setLabel("Actualite "+QString("%1%").arg(100*slice1->percentage(),3,'f',1));
                    slice1->setLabelVisible();
                    slice1->setBrush(QColor(Qt::cyan));
                }
                if ( countMusique!=0)
                {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice2 = series->slices().at(2);
                    //slice1->setExploded();
                    slice2->setLabel("Musique "+QString("%1%").arg(100*slice2->percentage(),3,'f',1));
                    slice2->setLabelVisible();
                    slice2->setBrush(QColor(Qt::red));
                }
                if ( countPodcast!=0)
                {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice2 = series->slices().at(3);
                    //slice1->setExploded();
                    slice2->setLabel("Podcast "+QString("%1%").arg(100*slice2->percentage(),3,'f',1));
                    slice2->setLabelVisible();
                    slice2->setBrush(QColor(Qt::yellow));
                }
                if ( countpub!=0)
                {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice2 = series->slices().at(4);
                    //slice1->setExploded();
                    slice2->setLabel("Publicite "+QString("%1%").arg(100*slice2->percentage(),3,'f',1));
                    slice2->setLabelVisible();
                    slice2->setBrush(QColor(Qt::green));
                }

                // Create the chart widget
                QChart *chart = new QChart();
                // Add data to chart with title and hide legend
                chart->addSeries(series);
                chart->setTitle("Totale "+ QString::number(total));
                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chart->legend()->hide();
                chartView->show();
}
