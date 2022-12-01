#include "interfacenews.h"
#include "ui_interfacenews.h"
#include "pub.h"
#include "actualite.h"
#include <QString>
#include <QMessageBox>
#include <QDate>
#include <QIntValidator>
#include <QDateEdit>
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

#include <QLayout>



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qrcode.h"
#include "excel.h"
#include <QSqlQueryModel>
#include <QPixmap>
#include<QDirModel>
#include <QtSvg/QSvgRenderer>
#include <QFile>
#include <QFileDialog>
#include <fstream>
//#include <QSerialPort>
//#include <QSerialPortInfo>
#include <QDebug>
#include<QRegularExpression>


#include "arduino.h"

#include "QMainWindow"








using qrcodegen::QrCode;


interfacenews::interfacenews(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interfacenews)
{
    ui->setupUi(this);

//ui->le_id->setValidator (new QIntValidator(100, 999, this));
//listView


    //***********arduino******************
       int ret=AA.connect_arduino(); // lancer la connexion à arduino
       switch(ret){
       case(0):qDebug()<< "arduino is available and connected to : "<< AA.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<AA.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(AA.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
        //le slot update_label suite à la reception du signal readyRead (reception des données).
   //*******************************








    ui->le_id_3->setValidator(new QIntValidator(100, 9999999, this));
    ui->tab_pub->setModel(p.afficher());



//***graphe****
 int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;
//total ( a,   b,  c,  d,  e,  f,   g,   h);
 clearLayout(ui->graphe);
 ui->graphe->addWidget(total( a,   b,  c,  d,  e,  f,   g,   h));


//***graphe****

ui->listView->setModel(A.afficher());
ui->le_imgurl->setVisible(false);
ui->bouton_supp->setVisible(false);
ui->frame_8->setVisible(false);




/*
QSqlQuery query;
  QString id;
  query.prepare("select IDP from ACTUALITE");
  query.exec();

  query.first();


  id = query.value(0).toString() ;
  ui->le_suppr->setText(id);*/


}

interfacenews::~interfacenews()
{
    delete ui;
}


//************************


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
//total ( a,   b,  c,  d,  e,  f,   g,   h);
//***graphe****


    Actualite A( id, Titre , lieu, date, source,categorie,description,imageurl);




    bool test=A.ajouter();
    if (test)
    {

    AA.write_to_arduino(("1"));
    AA.write_to_arduinoid((id.toUtf8()));


        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("ajout effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);

        clearLayout(ui->graphe);

        ui->graphe->addWidget(total( a,   b,  c,  d,  e,  f,   g,   h));

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
QString id=ui->le_suppr->text();

QMessageBox msgBox;
if (test)
  {
    AA.write_to_arduino(("0"));
    AA.write_to_arduinoid((id.toUtf8()));

    msgBox.setText("Suppression avec succes.");
}
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


   //**
id=ui->le_id_2->text();
AA.write_to_arduino(("3"));
AA.write_to_arduinoid((id.toUtf8()));
  //**



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
    {
        AA.write_to_arduino(("2"));
        AA.write_to_arduinoid((id.toUtf8()));

        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("modification effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);



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
            image= image.scaledToWidth(ui->le_image_2->width(),Qt::SmoothTransformation);
            ui->le_image_2->setPixmap(QPixmap::fromImage(image));

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
   clearLayout(ui->graphe);
int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;
    ui->graphe->addWidget(total( a,   b,  c,  d,  e,  f,   g,   h));
}





QChartView * interfacenews::total (int a,  int b, int c, int d, int e, int f, int  g,  int h )
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

   // chartview->setParent(ui->graphe1);
    chartview->setRenderHint(QPainter::Antialiasing);
return chartview;
    //*******

}




void interfacenews::clearLayout(QLayout *layout)
{
     QLayoutItem *item;
     while ((item = layout->takeAt(0)))
         delete item;
}












//**********************************************************************************TRAVAIL DE  KHALIL BEDOUI****************************************







void interfacenews::on_pushButton_3_clicked()  //Ajout
{
    int id=ui->le_id_3->text().toInt();
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


void interfacenews::on_id_supp_clicked() //SUPPRESSION
{
    PUB p;
    p.setid(ui->le_id_supp_2->text().toInt());
    bool test=p.supprimer(p.getid());

    QMessageBox msgBox;
    if(test)
    {
    msgBox.setText("Suppression avec succes.");
    ui->tab_pub->setModel(p.afficher());
    }
else
    msgBox.setText("Echec de suppression");
    msgBox.exec();
}


void interfacenews::on_pb_update_clicked() //UPDATE
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



void interfacenews::on_refresh_clicked() //Refresh
{
    PUB p;
    ui->tab_pub->setModel(p.afficher());
}



void interfacenews::on_tab_pub_activated(const QModelIndex &index) //controle_de_saisie
{


    QString id=ui->tab_pub->model()->data(index).toString();

    QSqlQuery qry;
    qry.prepare("select * FROM PUB1 WHERE ID='"+id+"' or TITRE='"+id+"' or DESCRIPTION='"+id+"' or TYPE='"+id+"' or DATE_P='"+id+"' or DESCRIPTION='"+id+"' " );

    if (qry.exec())
        {   while (qry.next())
                {
             ui->le_id_supp_2->setText(qry.value(0).toString());
                  ui->le_newid->setText(qry.value(0).toString());
                   ui->le_newtitre->setText(qry.value(1).toString());
                    ui->le_newdescription->setText(qry.value(2).toString());
                      ui->le_newdate->setText(qry.value(4).toString());
                }
        }
}


void interfacenews::on_type_2_activated() //Recherchertype
{
    PUB p;
    QString type ;
         type= ui->type_2->currentText();
    ui->tab_pub->setModel(p.Rechercher(type));

}

void interfacenews::on_pushButton_5_clicked() //RECHERCHER_ID
{
    PUB p;
    int id ;
    id= ui->le_id_supp_2->text().toInt();
    ui->tab_pub->setModel(p.Rechercherid(id));
}





void interfacenews::on_titre_2_clicked()  //RechercherTITRE
{
    PUB p;
    QString titre ;
         titre= ui->titre_3->text();
    ui->tab_pub->setModel(p.Recherchertitre(titre));
}

void interfacenews::on_pushButton_6_clicked()  //tri_ID
{
    ui->tab_pub->setModel(p.tri());
}
void interfacenews::on_triDate_clicked()
{
    PUB p;
    ui->tab_pub->setModel(p.tridate());
}


void interfacenews::on_pushButton_9_clicked() //tri par ordre alpha :
{
    PUB p;
    ui->tab_pub->setModel(p.tri());
}



void interfacenews::on_commandLinkButton_clicked()  //PDF
{
    QString strStream;



                    QTextStream out(&strStream);
                    const int rowCount = ui->tab_pub->model()->rowCount();
                    const int columnCount =ui->tab_pub->model()->columnCount();


                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("eleve")
                            <<  "</head>\n"
                            "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                                "<h1>Liste des Evenements</h1>"

                                "<table border=1 cellspacing=0 cellpadding=2>\n";

                    // headers
                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tab_pub->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tab_pub->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tab_pub->isColumnHidden(column)) {
                                       QString data = ui->tab_pub->model()->data(ui->tab_pub->model()->index(row, column)).toString().simplified();
                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";



            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);


            //QTextDocument document;
            //document.setHtml(html);
            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("PDF.pdf");
            document->print(&printer);


}





void interfacenews::on_EXCEL_clicked()  //EXCEL
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),

                                                                tr("Excel Files (*.xls)"));

                if (fileName.isEmpty())

                    return;



                ExportExcelObject obj(fileName, "mydata", ui->tab_pub);



                //colums to export



                obj.addField(0, "ID", "char(20)");

                obj.addField(1, "TITRE", "char(20)");

                obj.addField(2, "DESCRIPTION", "char(20)");

                obj.addField(3, "TYPE", "char(20)");

                obj.addField(4, "DATE_P", "char(20)");






                int retVal = obj.export2Excel();

                if( retVal > 0)

                {

                    QMessageBox::information(this, tr("Done"),

                                             QString(tr("%1 records exported!")).arg(retVal)

                                             );

                }
}






void interfacenews::on_browseBtn_clicked() // mailing
{
    files.clear();

        QFileDialog dialog(this);
        dialog.setDirectory(QDir::homePath());
        dialog.setFileMode(QFileDialog::ExistingFiles);

        if (dialog.exec())
            files = dialog.selectedFiles();

        QString fileListString;
        foreach(QString file, files)
            fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

        ui->file->setText( fileListString );
}



void interfacenews::on_sendBtn_clicked()
{
    mail* smtp = new mail("bedoui.khalil@esprit.tn",ui->mail_pass->text(), "mail.gmail.com");
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        if( !files.isEmpty() )
            smtp->sendMail("bedoui.khalil@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
        else
            smtp->sendMail("bedoui.khalil@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
    }


 void   interfacenews::mailSent(QString status)
    {

        if(status == "Message sent")
            QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
        ui->rcpt->clear();
        ui->subject->clear();
        ui->file->clear();
        ui->msg->clear();
        ui->mail_pass->clear();
}



void interfacenews::on_pb_code_clicked()    //QR CODE
{
    PUB p ;
        if(ui->tab_pub->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                            QObject::tr("Veuillez Choisir une PUB du Tableau.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {
                           p.setid(ui->le_id->text().toInt());
                           p.settitre(ui->titre->text());
                           p.setdescription(ui->description->text());
                           p.settype(ui->type->currentText());
                           p.setdate(ui->date->text());

                   // int idAnim=ui->tab_animaux->model()->data(ui->tab_animaux->model()->index(ui->tab_animaux->currentIndex().row(),0)).toInt();


                 //QString  rawQr = "ID:%1 TITRE:%2 DESCRIPTION:%3 TYPE:%4 DATE_P:%5 adress:%6 " ;
                 QString  rawQr = "ID_PUBLICITE:%1 Nom:%2 prenom:%3 Age:%4 tel:%5 adress:%6 " ;
                 rawQr = rawQr.arg(  p.getid()).arg(  p.gettitre()).arg(p.getdescription()).arg(p.gettype()).arg(p.getdate());
                 QrCode qr = QrCode::encodeText(rawQr.toUtf8().constData(), QrCode::Ecc::HIGH);


                  //  const QrCode qr = QrCode::encodeText(std::to_string(idAnim).c_str(), QrCode::Ecc::LOW);
                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    QPixmap pix( QSize(140, 140) );
                    QPainter pixPainter( &pix );
                    svgRenderer.render( &pixPainter );
                    ui->label_qrcode->setPixmap(pix);
               }
}
