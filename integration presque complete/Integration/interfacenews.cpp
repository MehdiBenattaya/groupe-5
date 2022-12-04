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
#include  <QDir>

#include <QLayout>



#include "interfacenews.h"
#include "ui_interfacenews.h"
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

//*********ahmed
//************

#include "podcast.h"
#include <QSqlQuery>
#include <QtMultimedia/QMediaPlayer>
#include <QFileDialog>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QPrinter>
#include <QTextDocument>
#include <QTextStream>
#include <QBuffer>
#include <QByteArray>
#include <QIntValidator>
#include <QString>


//zgolli
#include"gestion_musique.h"









using qrcodegen::QrCode;


interfacenews::interfacenews(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interfacenews)
{
    /*ichrak*/
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->le_id_ich->setValidator(new QIntValidator(0, 99999, this));
    ui->le_numero_telephone_ich->setValidator(new QIntValidator(0, 99999999, this));
   ui->TableView_ich->setModel(E.afficher());

//ui->le_id->setValidator (new QIntValidator(100, 999, this));
//listView




   //ahmed

           ui->tab_podcast->setModel(P.afficher());
           mMediaPlayer = new QMediaPlayer(this);

           connect(mMediaPlayer, &QMediaPlayer::positionChanged, [&](qint64 pos){
               ui->progressBar_audio->setValue(pos);
           });

           connect(mMediaPlayer, &QMediaPlayer::durationChanged, [&](qint64 dur){
               ui->progressBar_audio->setMaximum(dur);
           });







//aziz
               ui->tab_musique_2->setModel(m.afficher());









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
//



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


void interfacenews::on_pushButton_annuler_ich_clicked()
{
    ui->le_id_ich->clear();
    ui->le_nom_ich->clear();
    ui->le_mdp_ich->clear();
    ui->le_prenom_ich->clear();
    ui->le_nom_utilisateur_ich->clear();
    ui->le_salaire_ich->clear();
    ui->le_numero_telephone_ich->clear();
}

void interfacenews::on_pb_supprimer_ich_clicked()
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

void interfacenews::on_pushButton_modif_ich_clicked()
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

void interfacenews::on_pb_recherche_ich_clicked()
{
           QString search=ui->le_recherche_ich->text();
           ui->TableView_ich->setModel(E.Rechercher(search));
}

void interfacenews::on_pushButton_trierid_ich_clicked()
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

void interfacenews::on_pushButton_triernom_ich_clicked()
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

void interfacenews::on_pushButton_triersalaire_ich_clicked()
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

void interfacenews::on_pushButton_excel_ich_clicked()
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

void interfacenews::on_pushButton_pdf_ich_clicked()
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
void interfacenews::on_TableView_ich_doubleClicked(const QModelIndex &index)
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
/*
void interfacenews::on_btnLogin_4_clicked()
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
                if (query.value(0).toString() == "Actualite" )
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

void interfacenews::on_pb_deconnexion_clicked()
{
    ui->le_username->clear();
    ui->le_password->clear();
    ui->stackedWidget->setCurrentIndex(0);
}
*/

void interfacenews::on_pushButton_stat_ich_clicked()
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

void interfacenews::on_pushButton_ajout_ich_clicked()
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












//********************************AHMED


void interfacenews::on_pb_ajouter_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    int nmbdeparticipants=ui->lineEdit_nmbdeparticipants->text().toInt();
    QString script=ui->lineEdit_script->text();
    QString duree=ui->lineEdit_duree->text();
    QString date=ui->lineEdit_date->text();
    QString heure=ui->lineEdit_heure->text();
    QString sujet=ui->lineEdit_sujet->text();
    QString categorie=ui->comboBox_categorie->currentText();
    QString audio=ui->lineEdit_path->text();
Podcast P(id, sujet, nmbdeparticipants, script, duree, date, heure,categorie,audio);
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




















void interfacenews::on_pushButton_supprimer_clicked()
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









void interfacenews::on_pushButton_tri_sujet_clicked()
{
 ui->tab_podcast->setModel(P.tri_sujet());
}
void interfacenews::on_pushButton_tri_categorie_clicked()
{
    Podcast P2;
    QString categorie ;
         categorie= ui->comboBox_categorie_tri->currentText();

        ui->tab_podcast->setModel(P2.triercategorie(categorie));
}
void interfacenews::on_pushButton_modifier_clicked()
{
    Podcast P1;
       P1.setid(ui->lineEdit_id_supp->text().toInt());

       int id= ui->lineEdit_id1->text().toInt();
       int nmbdeparticipants= ui->lineEdit_nmbdeparticipants1->text().toInt();
       QString script= ui->lineEdit_script1->text();

       QString duree= ui->lineEdit_duree1->text(); // this is only vlaid if u visually design the window and placed dateEdit
       QString date = ui->lineEdit_date1->text();

       QString heure= ui->lineEdit_heure1->text();

       QString categorie= ui->comboBox_categorie_1->currentText();

       QString sujet= ui->lineEdit_sujet1->text();

       QString audio= ui->lineEdit_path_1->text();




       Podcast P( id, sujet, nmbdeparticipants, script, duree, date, heure, categorie,audio);

       bool test=P.modifier();
       if (test)
       { QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("modification effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);
       }
       else
           QMessageBox::critical(nullptr, QObject::tr("not OK"), QObject::tr("modification non effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);



}

void interfacenews::on_tab_podcast_activated(const QModelIndex &index)
{
    int id=ui->tab_podcast->model()->data(index).toInt();




    QString id_string= QString::number(id);


    QSqlQuery qry;
    qry.prepare("select * FROM PODCAST WHERE IDPOD='"+id_string+"' or SUJET='"+id_string+"' or PARTICIPANT='"+id_string+"' or SCRIPT='"+id_string+"' or DUREE='"+id_string+"' or DATEPOD='"+id_string+"' or HEURE='"+id_string+"' or CATEGORIEPOD='"+id_string+"' or AUDIO='"+id_string+"' " );


    if (qry.exec())
        {   while (qry.next())
                {
             ui->lineEdit_id_supp->setText(qry.value(0).toString());



                  ui->lineEdit_id1->setText(qry.value(0).toString());
                   ui->lineEdit_sujet1->setText(qry.value(1).toString());
                    ui->lineEdit_nmbdeparticipants1->setText(qry.value(2).toString());

                   /* QString date_string = qry.value(3).toString();
                     QDate Date = QDate::fromString(date_string);
                      ui->le_date_2->setDisplayFormat(date_string);*/

                      ui->lineEdit_script1->setText(qry.value(3).toString());
                 ui->lineEdit_duree1->setText(qry.value(4).toString());
                 ui->lineEdit_date1->setText(qry.value(5).toString());
                 ui->lineEdit_heure1->setText(qry.value(6).toString());

                 //QSqlQueryModel *modal=new QSqlQueryModel();
                 //modal    ->setQuery (qry);
                 //ui->comboBox_categorie_1->findText(qry.value(7).toString());

                 mMediaPlayer->setMedia(QUrl::fromLocalFile(qry.value(8).toString()));
                 mMediaPlayer->setVolume(ui->horizontalScrollBar_audio->value());
                 on_pushButton_play_clicked();






                }
        }
}

void interfacenews::on_pushButton_rafraichir_clicked()
{
    Podcast P;
    ui->tab_podcast->setModel(P.afficher());
}

void interfacenews::on_pushButton_rechercher_clicked()
{
    Podcast P1;
        int id ;
             id= ui->lineEdit_rechercher->text().toInt();
        ui->tab_podcast->setModel(P1.rechercher(id));
}

void interfacenews::on_pushButton_recherche_sujet_clicked()
{
    Podcast P1;
        QString sujet;
            sujet= ui->lineEdit_recherche_sujet->text();
            ui->tab_podcast->setModel(P1.rechercher_sujet(sujet));
}

void interfacenews::on_pushButton_recherche_date_clicked()
{
    Podcast P1;
        QString date;
            date= ui->lineEdit_recherche_date->text();
            ui->tab_podcast->setModel(P1.rechercher_date(date));
}





void interfacenews::on_pushButton_inserer_clicked()
{
  QString filename = QFileDialog::getOpenFileName(this, "Inserer");
  if (filename.isEmpty()){
      return;
  }
  mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
  mMediaPlayer->setVolume(ui->horizontalScrollBar_audio->value());
  on_pushButton_play_clicked();
  ui->lineEdit_path->setText(filename);
}

void interfacenews::on_pushButton_play_clicked()
{
    mMediaPlayer->play();
}

void interfacenews::on_pushButton_mute_clicked()
{
    if (ui->pushButton_mute->text() == "Mute"){
        mMediaPlayer->setMuted(true);
        ui->pushButton_mute->setText("Unmute");
     } else {
        mMediaPlayer->setMuted(false);
        ui->pushButton_mute->setText("Mute");
    }
}

void interfacenews::on_pushButton_stop_clicked()
{
mMediaPlayer->stop();
}

void interfacenews::on_pushButton_pause_clicked()
{
mMediaPlayer->pause();
}

void interfacenews::on_horizontalScrollBar_audio_valueChanged(int value)
{
mMediaPlayer->setVolume(value);
}

void interfacenews::on_pushButton_pdf_clicked()
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

                          const int rowCount = ui->tab_podcast->model()->rowCount();
                          const int columnCount = ui->tab_podcast->model()->columnCount();
                          QString TT = QDateTime::currentDateTime().toString();
                          out <<"<html>\n"
                                "<head>\n"
                                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                              << "<title>ERP - COMmANDE LIST<title>\n "
                              << "</head>\n"
                              "<body bgcolor=#ffffff link=#5000A0>\n"
                                 "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                                +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />" //path
                                 "<h1 style=\"text-align: center;\"><strong> ***LISTE DES PODCASTS *** </strong></h1>"

                              "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                                "</br> </br>";
                          // headers
                          out << "<thead><tr bgcolor=#d6e5ff>";
                          for (int column = 0; column < columnCount; column++)
                              if (!ui->tab_podcast->isColumnHidden(column))
                                  out << QString("<th>%1</th>").arg(ui->tab_podcast->model()->headerData(column, Qt::Horizontal).toString());
                          out << "</tr></thead>\n";

                          // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++)
                            {
                                  if (!ui->tab_podcast->isColumnHidden(column)) {
                                      QString data =ui->tab_podcast->model()->data(ui->tab_podcast->model()->index(row, column)).toString().simplified();
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




void interfacenews::on_pushButton_14_clicked()
{
    ui->tab_podcast->setModel(P.tri());
}




//zgolli



void interfacenews::on_pb_ajouter_3_clicked()
{
    QString titre=ui->l_titre_2->text();
    QString nom=ui->l_nom_2->text();
    QString nat=ui->l_nat_2->text();
    QString genre=ui->l_genre_2->text();
    QString descr=ui->l_descr_2->text();

    GESTION_MUSIQUE gm(titre,nom,nat,genre,descr);
    bool test=gm.ajouter();
    QMessageBox msgbox;

    if(test)
        msgbox.setText("ajout avec succes");
    else
        msgbox.setText("echec de l'ajout");
    msgbox.exec();
}



void interfacenews::on_pb_supp_2_clicked()
{
    GESTION_MUSIQUE m1; m1.settitre(ui->l_titresupp_2->text());
    bool test=m1.supprimer(m1.gettitre());
    QMessageBox msgbox;

    if(test)
       { msgbox.setText("suppression avec succes");
    ui->tab_musique_2->setModel(m.afficher());}
    else
        msgbox.setText("echec de suppression");
    msgbox.exec();
}



void interfacenews::on_psuh_recherche_clicked()
{
    GESTION_MUSIQUE m;
    QString text;

    if (ui->rad_Nom->isChecked()==true)
    {
        m.clearTable(ui->tab_musique_2);
            QString Nom=ui->lineEdit_recherche->text();
            m.chercheNom(ui->tab_musique_2,Nom);
    }
    if (ui->rad_Titre->isChecked()==true)
    {
        m.clearTable(ui->tab_musique_2);
            QString titre=ui->lineEdit_recherche->text();
            m.chercheTitre(ui->tab_musique_2,titre);
    }
}




void interfacenews::on_push_TriNom_clicked()
{
    ui->tab_musique_2->setModel(m.tri_Nom());
}

void interfacenews::on_push_TriTitre_clicked()
{
    ui->tab_musique_2->setModel(m.tri_Titre());

}

void interfacenews::on_psuh_TriGenre_clicked()
{
    ui->tab_musique_2->setModel(m.tri_Genre());

}



void interfacenews::on_pushButton_25_clicked()
{
      ui->tab_musique_2->setModel(m.afficher());
}




void interfacenews::update_nb()
{

  data=AA.read_from_arduino();

  if(data== "1"){
      ui->label_8->setText("mouvement detecté");
  }
  else if(data== "0"){
      ui->label_8->setText("mouvement non detecté");
      }
  qDebug()<<"data"<<data;
}

