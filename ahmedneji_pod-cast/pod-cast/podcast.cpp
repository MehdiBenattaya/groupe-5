#include "podcast.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QString>
#include <QDate>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QDateTime>
#include <QTextStream>

Podcast::Podcast()
{
id=0; sujet=" "; nmbdeparticipants=0; script=" "; duree=" "; date=" "; heure=" "; categorie=" "; audio=" ";
}


Podcast::Podcast(int id,QString sujet,int nmbdeparticipants,QString script,QString duree,QString date,QString heure,QString categorie,QString audio)
{this->id=id;  this->sujet=sujet; this->nmbdeparticipants=nmbdeparticipants; this->script=script; this->duree=duree; this->date=date; this->heure=heure; this->categorie=categorie; this->audio=audio;}
int Podcast::getid(){return id;}
int Podcast::getnmbdeparticipants(){return nmbdeparticipants;}
QString Podcast::getscript(){return script;}
QString Podcast::getduree(){return duree;}
QString Podcast::getdate(){return date;}
QString Podcast::getheure(){return heure;}
QString Podcast::getsujet(){return sujet;}
QString Podcast::getcategorie(){return categorie;}
QString Podcast::getaudio(){return audio;}
void Podcast::setid(int id){this->id=id;}
void Podcast::setnmbdeparticipants(int nmbdeparticipants){this->nmbdeparticipants=nmbdeparticipants;}
void Podcast::setscript(QString script){this->script=script;}
void Podcast::setduree(QString duree){this->duree=duree;}
void Podcast::setdate(QString date){this->date=date;}
void Podcast::setheure(QString heure){this->heure=heure;}
void Podcast::setsujet(QString sujet){this->sujet=sujet;}
void Podcast::setcategorie(QString categorie){this->categorie=categorie;}
void Podcast::setaudio(QString audio){this->audio=audio;}
bool Podcast::ajouter()
{
    bool test=false;

  QString id_string= QString::number(id);
  QString nmbdeparticipants_string= QString::number(nmbdeparticipants);
        QSqlQuery query;
        query.prepare("INSERT INTO PODCAST (IDPOD, SUJET, PARTICIPANT, SCRIPT, DUREE, DATEPOD, HEURE, CATEGORIEPOD, AUDIO)"
                      "VALUES (:id_string, :sujet, :nmbdeparticipants_string, :script, :duree, :date, :heure, :categoriepod, :audio)");
        query.bindValue(":id_string", id_string);
        query.bindValue(":sujet", sujet);
        query.bindValue(":nmbdeparticipants_string", nmbdeparticipants_string);
        query.bindValue(":script", script);
        query.bindValue(":duree", duree);
        query.bindValue(":date", date);
        query.bindValue(":heure", heure);
        query.bindValue(":categoriepod", categorie);
        query.bindValue(":audio", audio);
       return query.exec();
    return test;
}
bool Podcast::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from PODCAST where IDPOD=:IDPOD");
    query.bindValue(0, id);

   return query.exec();
}
QSqlQueryModel* Podcast::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT* FROM PODCAST");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sujet"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbr de participants"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Script"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Duree"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date du podcast"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Heure du podcast"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Categorie du podcast"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Extrait vocal"));




    return model;
}
QSqlQueryModel * Podcast::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM PODCAST ORDER BY IDPOD ASC");
        return model;
}
QSqlQueryModel * Podcast::tri_sujet()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM PODCAST ORDER BY SUJET ASC");
        return model;
}



bool Podcast::modifier()
 {
     bool test=false;

     QString id_string= QString::number(id);
     QString nmbdeparticipants_string= QString::number(nmbdeparticipants);


     QSqlQuery query;
          query.prepare("UPDATE PODCAST set IDPOD='"+id_string+"',SUJET='"+sujet+"', PARTICIPANT='"+nmbdeparticipants_string+"', SCRIPT='"+script+"', DUREE='"+duree+"', DATEPOD='"+date+"', HEURE='"+heure+"', CATEGORIEPOD='"+categorie+"', AUDIO='"+audio+"' where IDPOD='"+id_string+"'");
         return query.exec();


         return test;
}


QSqlQueryModel *Podcast::rechercher(int id)
 {

 QSqlQuery query;

      query.prepare("SELECT *  FROM PODCAST where IDPOD=:IDPOD");

        query.bindValue(":IDPOD",id);
        query.exec();

   QSqlQueryModel* model= new QSqlQueryModel;
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sujet"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbr de participants"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Script"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("Duree"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date du podcast"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("Heure du podcast"));
   model->setHeaderData(7, Qt::Horizontal, QObject::tr("Categorie du podcast"));
   model->setHeaderData(8, Qt::Horizontal, QObject::tr("Extrait vocal"));

       model->setQuery(query);
     return model;

 }

QSqlQueryModel *Podcast::rechercher_sujet(QString sujet)
 {

 QSqlQuery query;

      query.prepare("SELECT *  FROM PODCAST where SUJET=:SUJET");

        query.bindValue(":SUJET",sujet);
        query.exec();

   QSqlQueryModel* model= new QSqlQueryModel;
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sujet"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbr de participants"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Script"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("Duree"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date du podcast"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("Heure du podcast"));
   model->setHeaderData(7, Qt::Horizontal, QObject::tr("Categorie du podcast"));
   model->setHeaderData(8, Qt::Horizontal, QObject::tr("Extrait vocal"));

       model->setQuery(query);
     return model;

 }

QSqlQueryModel *Podcast::rechercher_date(QString date)
 {

 QSqlQuery query;

      query.prepare("SELECT *  FROM PODCAST where DATEPOD=:DATEPOD");

        query.bindValue(":DATEPOD",date);
        query.exec();

   QSqlQueryModel* model= new QSqlQueryModel;
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sujet"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbr de participants"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Script"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("Duree"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date du podcast"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("Heure du podcast"));
   model->setHeaderData(7, Qt::Horizontal, QObject::tr("Categorie du podcast"));
   model->setHeaderData(8, Qt::Horizontal, QObject::tr("Extrait vocal"));

       model->setQuery(query);
     return model;

 }



QSqlQueryModel* Podcast::triercategorie(QString categorie)

{
    QSqlQuery query;



     query.prepare("SELECT *  FROM PODCAST where CATEGORIEPOD=:CATEGORIEPOD");

     query.bindValue(":CATEGORIEPOD",categorie);
     query.exec();

     QSqlQueryModel* model= new QSqlQueryModel;

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sujet"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbr de participants"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Script"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Duree"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date du podcast"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("Heure du podcast"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("Categorie du podcast"));
     model->setHeaderData(8, Qt::Horizontal, QObject::tr("Extrait vocal"));

     model->setQuery(query);

     return model;

}



void Podcast::genererPDFact()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty())
            { fileName.append(".pdf"); }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        QSqlQuery q;
        q.prepare("SELECT * FROM EMPLOYES ");
        q.exec();
        QString pdf="<br> <h1  style='color:blue'>LISTE DES EMPLOYES  <br></h1>\n <br> <table>  <tr>  <th>ID </th> <th>NUMERO-TELEPHONE </th> <th>PRENOM  </th> <th>SALAIRE  </th><th>NOM  </th><th>PRENOM </th><th>DATE_NAISSANCE  </th> </tr>" ;
    //br traja ll star oel tr tzidlek colonne th tzidlek ligne h1 asghrr size o akbr size h6 //

        while ( q.next())
            {

            pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toString() +" <td>" +q.value(6).toString() +" <td>" +q.value(7).toString() +" <td>" +q.value(8).toString() +" "" " "</td> </td>" ;
        }
        doc.setHtml(pdf);
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);


    }

