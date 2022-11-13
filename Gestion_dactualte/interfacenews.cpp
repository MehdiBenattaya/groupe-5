#include "interfacenews.h"
#include "ui_interfacenews.h"
#include "actualite.h"
#include <QString>
#include <QMessageBox>
#include <QDate>
#include <QIntValidator>
#include <QDateEdit>
#include <QFileDialog>
#include <QByteArray>
#include <QImage>
#include <QBuffer>
//--------includes de pdf------
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QTextDocument>
//#include <QDateTime>
#include <QTextStream>
//include de files
#include  <QDir>







interfacenews::interfacenews(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interfacenews)
{
    ui->setupUi(this);

//ui->le_id->setValidator (new QIntValidator(100, 999, this));
//listView


//***graphe****
 int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;
total ( a,   b,  c,  d,  e,  f,   g,   h);
//***graphe****

ui->listView->setModel(A.afficher());
ui->le_imgurl->setVisible(false);
ui->bouton_supp->setVisible(false);
ui->frame_8->setVisible(false);






}

interfacenews::~interfacenews()
{
    delete ui;
}




// ----------------------------ajout-------------------------------------------

void interfacenews::on_pushButton_clicked()
{


  /*  QDate date = QDate::currentDate();
       QString dateString = date.toString();
       ui->le_date->setDate(dateString);
    QDate date = QDate::currentDate();
        ui->DateEdit->setDate(date);
   QDate date = QDate::currentDate();
      ui->le_date->setDate(date);
    QDate date= ui->le_datea->text();*/ //date edit false


    QString id= ui->le_id->text();
    QString Titre= ui->le_titre->text();
    QString lieu= ui->le_lieu->text();

    QDate date= ui->le_date->date(); // this is only vlaid if u visually design the window and placed dateEdit
    QString dateString = date.toString();

    QString source= ui->le_source->text();

    QString categorie= ui->le_categorie->currentText();


QString description= ui->le_description->toPlainText();


QString imageurl=ui->le_imgurl->text(); //copie  le path dans la  base de donnée

//***graphe****
 int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;
total ( a,   b,  c,  d,  e,  f,   g,   h);
//***graphe****


    Actualite A( id, Titre , lieu, date, source,categorie,description,imageurl);

    bool test=A.ajouter();
    if (test)
    { QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("ajout effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);

        //****************ajout historique*********************



        QFile file ("C:/Users/blade/OneDrive/Bureau/2eme esprit/Project C++ groupe 5 smart radio/projects/Gestion_dactualte/historique.txt");

        if (!file.open(QFile::WriteOnly  | QFile::Append))
            {
            QMessageBox::warning(this, "title","file  not open");
            }
        //file.write("ajout d'une nouvelle donnée a la date"
        QTextStream out (&file);

         QDate datenow = QDate::currentDate();
        QString datenowst=datenow.toString();
        QTime timenow= QTime::currentTime();
            QString timenowst=timenow.toString();

        //QString  text  = ui->history->toPlainText();
        out << "ajout d'une nouvelle donnee nomme ' " << Titre << " ' à la date ' " << datenowst << " ' à l'heure  ' " << timenowst << " '\n" ;
        file.flush();
        file.close ();




        //********************************




    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"), QObject::tr("ajout non effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}

// -----------------------------------------------------------------------




// ------------------------afficher rafraichir-----------------------------------------------

void interfacenews::on_rafraichir_clicked()
{
  Actualite A;
  ui->listView->setModel(A.afficher());
}


// ---------------------------------supprimer--------------------------------------

void interfacenews::on_bouton_supp_clicked()
{
Actualite A1;
A1.setid(ui->le_suppr->text());
bool test=A1.supprimer(A1.getid());

QMessageBox msgBox;
if (test)
    msgBox.setText("Suppression avec succes.");
   else
    msgBox.setText("Echec de suppression.") ;
msgBox.exec();




ui->bouton_supp->setVisible(false);

ui->frame_8->setVisible(false);


Actualite A;
ui->listView->setModel(A.afficher());




//****************supprimer historique*********************



QFile file ("C:/Users/blade/OneDrive/Bureau/2eme esprit/Project C++ groupe 5 smart radio/projects/Gestion_dactualte/historique.txt");

if (!file.open(QFile::WriteOnly  | QFile::Append))
    {
    QMessageBox::warning(this, "title","file  not open");
    }
//file.write("ajout d'une nouvelle donnée a la date"
QTextStream out (&file);

 QDate datenow = QDate::currentDate();
QString datenowst=datenow.toString();
QTime timenow= QTime::currentTime();
    QString timenowst=timenow.toString();

//QString  text  = ui->history->toPlainText();
out << "suppression d'une donnee  à la date ' " <<  datenowst << " ' à l'heure  ' " << timenowst << " '\n" ;
file.flush();
file.close ();




//********************************












}


// ---------------------------------list--------------------------------------




void interfacenews::on_listView_activated(const QModelIndex &index)
{


   QString id=ui->listView->model()->data(index).toString();




QSqlQuery qry;
qry.prepare("select * FROM ACTUALITE WHERE IDP='"+id+"' or TITRE='"+id+"' or LIEU='"+id+"' or DATEA='"+id+"' or SOURCE='"+id+"' or DESCRIPTION='"+id+"' or IMAGE='"+id+"' " );


if (qry.exec())
    {   while (qry.next())
            {
         ui->le_suppr->setText(qry.value(0).toString());



              ui->le_id_2->setText(qry.value(0).toString());
               ui->le_titre_2->setText(qry.value(1).toString());
                ui->le_lieu_2->setText(qry.value(2).toString());

               /* QString date_string = qry.value(3).toString();
                 QDate Date = QDate::fromString(date_string);
                  ui->le_date_2->setDisplayFormat(date_string);*/

                  ui->le_source_2->setText(qry.value(4).toString());


              //   QSqlQueryModel *modal=new QSqlQueryModel();
               //  modal    ->setQuery (qry);
         //    ui->le_categorie_2->findText(qry.value(4).toString());



             ui->le_description_2->setPlainText(qry.value(6).toString());


                  QImage image;
                 image.load (qry.value(7).toString());


                      image= image.scaledToWidth(ui->le_imageapercu->width(),Qt::SmoothTransformation);
                      ui->le_imageapercu->setPixmap(QPixmap::fromImage(image));


                      image= image.scaledToWidth(ui->le_image_2->width(),Qt::SmoothTransformation);
                      ui->le_image_2->setPixmap(QPixmap::fromImage(image));



            }
    }

}


// -----------------------------------------------------------------------


// ---------------------------modifier--------------------------------------------



void interfacenews::on_bouton_modif_2_clicked()
{



    Actualite A1;
    A1.setid(ui->le_suppr->text());





    QString id= ui->le_id_2->text();
    QString Titre= ui->le_titre_2->text();
    QString lieu= ui->le_lieu_2->text();

    QDate date= ui->le_date_2->date(); // this is only vlaid if u visually design the window and placed dateEdit
    QString dateString = date.toString();

    QString source= ui->le_source_2->text();

    QString categorie= ui->le_categorie_2->currentText();

    QString description= ui->le_description_2->toPlainText();


QString imageurl;

    Actualite A( id, Titre , lieu, date, source,categorie,description,imageurl);

    bool test=A.modifier();
    if (test)
    { QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("modification effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);



        //****************modification historique*********************



        QFile file ("C:/Users/blade/OneDrive/Bureau/2eme esprit/Project C++ groupe 5 smart radio/projects/Gestion_dactualte/historique.txt");

        if (!file.open(QFile::WriteOnly  | QFile::Append))
            {
            QMessageBox::warning(this, "title","file  not open");
            }
        //file.write("ajout d'une nouvelle donnée a la date"
        QTextStream out (&file);

         QDate datenow = QDate::currentDate();
        QString datenowst=datenow.toString();
        QTime timenow= QTime::currentTime();
            QString timenowst=timenow.toString();

        //QString  text  = ui->history->toPlainText();
        out << "modification d'une donnee nomme ' " << Titre << " ' à la date ' " << datenowst << " ' à l'heure  ' " << timenowst << " '\n" ;
        file.flush();
        file.close ();




        //********************************




    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"), QObject::tr("modification non effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);


    ui->bouton_supp->setVisible(false);
    ui->frame_8->setVisible(false);
    ui->listView->setModel(A.afficher());




}








//-----------------saisir le le sup--------------------------
void interfacenews::on_saisir_clicked()
{
    ui->bouton_supp->setVisible(true);

    ui->frame_8->setVisible(true);

}



// ---------------------------ajout d'image--------------------------------------------

void interfacenews::on_pushButton_10_clicked()
{


        QString filename = QFileDialog::getOpenFileName(this, tr("choose"),"",tr("Image (*.png *.jpg *.jpeg *.bmp *.gif)"));

        if (QString::compare(filename, QString())!=0)
        {
            QImage image;
            bool valid= image.load (filename);

            if (valid)
            {
                image= image.scaledToWidth(ui->le_image->width(),Qt::SmoothTransformation);
                ui->le_image->setPixmap(QPixmap::fromImage(image));

               ui->le_imgurl->setText(filename);   //copie le path dans un lineedit

            }


            else
            {
                //error handling
            }

        }

    }



//--------------------------------modif d'image-----------------------------------------------




void interfacenews::on_pushButton_11_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("choose"),"",tr("Image (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (QString::compare(filename, QString())!=0)
    {
        QImage image;
        bool valid= image.load (filename);

        if (valid)
        {
            image= image.scaledToWidth(ui->le_image->width(),Qt::SmoothTransformation);
            ui->le_image->setPixmap(QPixmap::fromImage(image));

           ui->le_imgurl->setText(filename);

        }


        else
        {
            //error handling
        }

    }
}






















//-----------------------------RECHERCHER----------------------------------------

void interfacenews::on_pushButton_7_clicked()
{

    Actualite A1;
    QString id ;
         id= ui->le_recherche->text();
    ui->listView->setModel(A1.rechercher(id));



}


//-----------------------------rechercherparcategorie----------------------------------------

void interfacenews::on_categoriechercher_activated()
{
    Actualite A2;

        QString categorie= ui->categoriechercher->currentText();

          ui->listView->setModel(A2.recherchercategorie(categorie));






}






//-----------------------------rechercherpartitre----------------------------------------

void interfacenews::on_pushButton_8_clicked()
{

    Actualite A2;

        QString titre= ui->le_recherche_2->text();

          ui->listView->setModel(A2.recherchertitre(titre));

}






//-----------------------------trier titre----------------------------------------


void interfacenews::on_trier_clicked()
{
    Actualite A2;

    ui->listView->setModel(A2.trier());


/*       // OUVRE UN FICHER
QString file_name= QFileDialog::getOpenFileName(this,"historique", QDir::homePath());
QMessageBox:: information (this, "..", file_name);
*/

}

//-----------------------------trier categorie----------------------------------------

void interfacenews::on_trier_2_clicked()
{
    Actualite A2;

    ui->listView->setModel(A2.triercategorie());
}


//-----------------------------trier date----------------------------------------

void interfacenews::on_trier_3_clicked()
{
    Actualite A2;

    ui->listView->setModel(A2.trierdate());
}



























//-----------------------------PDF----------------------------------------


void interfacenews::on_pushButton_2_clicked() /*pdf*/
{
    QString strStream;
            strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                if (QFileInfo(strStream).suffix().isEmpty())
                    { strStream.append(".pdf"); }

                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(strStream);

                      QTextStream out(&strStream);

                      const int rowCount = ui->listView->model()->rowCount();
                      const int columnCount = ui->listView->model()->columnCount();
                      QString TT = QDateTime::currentDateTime().toString();
                      out <<"<html>\n"
                            "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                          << "<title>ERP - COMmANDE LIST<title>\n "
                          << "</head>\n"
                          "<body bgcolor=#ffffff link=#5000A0>\n"
                             "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                            +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />" //path
                          "<h1 style=\"text-align: center;\"><strong> ***LISTE DES ACTUALITES *** </strong></h1>"

                          "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                            "</br> </br>";
                      // headers
                      out << "<thead><tr bgcolor=#d6e5ff>";
                      for (int column = 0; column < columnCount; column++)
                          if (!ui->listView->isColumnHidden(column))
                              out << QString("<th>%1</th>").arg(ui->listView->model()->headerData(column, Qt::Horizontal).toString());
                      out << "</tr></thead>\n";

                      // data table
                      for (int row = 0; row < rowCount; row++) {
                          out << "<tr>";
                          for (int column = 0; column < columnCount; column++)
                        {
                              if (!ui->listView->isColumnHidden(column)) {
                                  QString data =ui->listView->model()->data(ui->listView->model()->index(row, column)).toString().simplified();
                                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;")); //
                              }
                          }
                          out << "</tr>\n";
                      }
                      out <<  "</table>\n"
                          "</body>\n"
                          "</html>\n";

                      QTextDocument document;
                      document.setHtml(strStream);
                      document.print(&printer);

}









//------------------------------historique afficher--------------------------------------------


void interfacenews::on_histbouton_clicked()
{

    QFile file ("C:/Users/blade/OneDrive/Bureau/2eme esprit/Project C++ groupe 5 smart radio/projects/Gestion_dactualte/historique.txt");

    if (!file.open(QFile::ReadOnly  | QFile::Text))
        {
        QMessageBox::warning(this, "title","file  not open");
        }
    QTextStream in (&file);
    QString  text  = in.readAll();
    ui->history->setPlainText(text);

    file.close();
}


//------------------------------historique clear--------------------------------------------


void interfacenews::on_histbouton_2_clicked()
{


    QFile file ("C:/Users/blade/OneDrive/Bureau/2eme esprit/Project C++ groupe 5 smart radio/projects/Gestion_dactualte/historique.txt");

    if (!file.open(QFile::WriteOnly  | QFile::Truncate))
        {
        QMessageBox::warning(this, "title","file  not open");
        }

    file.flush();
    file.close ();


}

//------------------------------graphe actualiser--------------------------------------------


void interfacenews::on_graphebouton_clicked()
{
     int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;
total ( a,   b,  c,  d,  e,  f,   g,   h );

}


void interfacenews::total (int a,  int b, int c, int d, int e, int f, int  g,  int h )
{
    QBarSet *set0 = new QBarSet ("nombres d'articles");


    //**
    QSqlQuery qry;
    qry.prepare("SELECT * FROM ACTUALITE where CATEGORIE=:CATEGORIE");
       qry.bindValue(":CATEGORIE","categorie politique");
    qry.exec();
    while(qry.next())
        a++;
    //**
    qry.prepare("SELECT * FROM ACTUALITE where CATEGORIE=:CATEGORIE");
       qry.bindValue(":CATEGORIE","categorie sport");
    qry.exec();
    while(qry.next())
        b++;
    //**
    qry.prepare("SELECT * FROM ACTUALITE where CATEGORIE=:CATEGORIE");
       qry.bindValue(":CATEGORIE","categorie meteo");
    qry.exec();
    while(qry.next())
        c++;
    //**
    qry.prepare("SELECT * FROM ACTUALITE where CATEGORIE=:CATEGORIE");
       qry.bindValue(":CATEGORIE","categorie espace");
    qry.exec();
    while(qry.next())
        d++;
    //**
    qry.prepare("SELECT * FROM ACTUALITE where CATEGORIE=:CATEGORIE");
       qry.bindValue(":CATEGORIE","categorie filmatographie");
    qry.exec();
    while(qry.next())
        e++;
    //**
    qry.prepare("SELECT * FROM ACTUALITE where CATEGORIE=:CATEGORIE");
       qry.bindValue(":CATEGORIE","categorie technologique");
    qry.exec();
    while(qry.next())
        f++;
    //**
    qry.prepare("SELECT * FROM ACTUALITE where CATEGORIE=:CATEGORIE");
       qry.bindValue(":CATEGORIE","categorie sante");
    qry.exec();
    while(qry.next())
        g++;
    //**
    qry.prepare("SELECT * FROM ACTUALITE where CATEGORIE=:CATEGORIE");
       qry.bindValue(":CATEGORIE","categorie divers");
    qry.exec();
    while(qry.next())
        h++;

    *set0 << a << b << c << d << e << f << g << h;


    QBarSeries *series = new QBarSeries();
    series->append(set0);


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("graphique à bandes de nombres d'article par categorie");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    categories << "politique" << "sport" << "météo" << "espace" << "filmatographie" << "téchnologie"  << "sante"  << "divers";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    QChartView *chartview = new QChartView (chart);

    chartview->setParent(ui->graphe);
    //*******

}

