#include "actualite.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QDate>
#include <QObject>
#include <QImage>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QDateTime>
#include <QTextStream>



Actualite::Actualite()
{
id=" ";
Titre= " ";
lieu= " ";
//date= " ";
date = QDate::fromString(" ");
source= " ";
categorie= " ";
description= " ";

}

Actualite::Actualite(QString id,QString Titre ,QString lieu,QDate date,QString source,QString categorie,QString description,QString imageurl)
{
    this->id=id; this->Titre=Titre;this->lieu=lieu;this->date=date;this->source=source;this->categorie=categorie;this->description=description;this->imageurl=imageurl;
}
QString Actualite::getid(){return id;}
QString Actualite::getTitre() {return Titre;}
QString Actualite::getlieu() {return lieu;}
QDate Actualite::getdate() {return date;}
QString Actualite::getsource()  {return source;}
QString Actualite::getcategorie() {return categorie;}
QString Actualite::getdescription() {return description;}
QString Actualite::getimage() {return imageurl;}

void Actualite::setid(QString id) {this->id=id;}
void Actualite::setTitre(QString Titre){this->Titre=Titre;}
void Actualite::setlieu(QString lieu){this->lieu=lieu;}
void Actualite::setdate(QDate date)  {this->date=date;}
void Actualite::setsource(QString source)  {this->source=source;}
void Actualite::setcategorie(QString categorie)   {this->categorie=categorie;}
void Actualite::setdescription(QString description)  {this->description=description;}
void Actualite::setimage(QString imageurl)  {this->imageurl=imageurl;}


//-------------------------------------------------------------------------------

bool Actualite::ajouter()
{
    bool test=false;


    QSqlQuery query;
         query.prepare("INSERT INTO ACTUALITE (IDP, TITRE, LIEU,DATEA,SOURCE,CATEGORIE,DESCRIPTION,IMAGE) "
                       "VALUES (:id, :Titre, :lieu, :date, :source,:categorie,:description,:image)");
         query.bindValue(":id", id);
         query.bindValue(":Titre", Titre);
         query.bindValue(":lieu", lieu);
         query.bindValue(":date", date);
         query.bindValue(":source", source);
         query.bindValue(":categorie", categorie);
          query.bindValue(":description", description);
           query.bindValue(":image", imageurl);
















        return query.exec();





    return test;
}


//-------------------------------------------------------------------------------

QSqlQueryModel *Actualite::afficher()
{
  QSqlQueryModel* model= new QSqlQueryModel();

       model->setQuery("SELECT *  FROM ACTUALITE ");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("lieu"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("source"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("categorie"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("description"));
      model->setHeaderData(7, Qt::Horizontal, QObject::tr("image"));
    return model;
}


//-------------------------------------------------------------------------------


 bool Actualite::supprimer(QString id)
 {

     QSqlQuery query;
          query.prepare("Delete from ACTUALITE where IDP=:IDP");
          query.bindValue(0, id);

         return query.exec();


 }


 //-------------------------------------------------------------------------------
 bool Actualite::modifier()
 {
     bool test=false;



        QString dateString = date.toString();
     QSqlQuery query;
          query.prepare("UPDATE ACTUALITE set IDP='"+id+"',TITRE='"+Titre+"', LIEU='"+lieu+"', DATEA='"+dateString+"', SOURCE='"+source+"', CATEGORIE='"+categorie+"', DESCRIPTION='"+description+"' where IDP='"+id+"'");
         return query.exec();










         return test;
}










 //-------------------------------------------------------------------------------



 QSqlQueryModel *Actualite::rechercher(QString id)
 {

 QSqlQuery query;

      query.prepare("SELECT *  FROM ACTUALITE where IDP=:IDP");

        query.bindValue(":IDP",id);
        query.exec();

   QSqlQueryModel* model= new QSqlQueryModel;
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("lieu"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("source"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("categorie"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("description"));
       model->setHeaderData(7, Qt::Horizontal, QObject::tr("image"));

       model->setQuery(query);
     return model;

 }



 //-------------------------------------------------------------------------------



 QSqlQueryModel *Actualite::recherchercategorie(QString categorie)
 {

 QSqlQuery query;

      query.prepare("SELECT *  FROM ACTUALITE where CATEGORIE=:CATEGORIE");

        query.bindValue(":CATEGORIE",categorie);
        query.exec();

   QSqlQueryModel* model= new QSqlQueryModel;
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("lieu"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("source"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("categorie"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("description"));
       model->setHeaderData(7, Qt::Horizontal, QObject::tr("image"));

       model->setQuery(query);
     return model;

 }


 //-------------------------------------------------------------------------------




 QSqlQueryModel *Actualite::recherchertitre(QString titre)
 {

 QSqlQuery query;

      query.prepare("SELECT *  FROM ACTUALITE where TITRE=:TITRE");

        query.bindValue(":TITRE",titre);
        query.exec();

   QSqlQueryModel* model= new QSqlQueryModel;
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("lieu"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("source"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("categorie"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("description"));
       model->setHeaderData(7, Qt::Horizontal, QObject::tr("image"));

       model->setQuery(query);
     return model;

 }









//-------------------------------------------------------------------------------


QSqlQueryModel* Actualite::trier()
{
    QSqlQueryModel* model= new QSqlQueryModel;
     model->setQuery("SELECT *  FROM ACTUALITE ORDER  BY TITRE");


     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("lieu"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("source"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("categorie"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("description"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("image"));


     return model;
}

//-------------------------------------------------------------------------------



QSqlQueryModel* Actualite::triercategorie()
{
    QSqlQueryModel* model= new QSqlQueryModel;
     model->setQuery("SELECT *  FROM ACTUALITE ORDER  BY CATEGORIE");


     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("lieu"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("source"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("categorie"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("description"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("image"));


     return model;
}

//-------------------------------------------------------------------------------


QSqlQueryModel* Actualite::trierdate()
{
    QSqlQueryModel* model= new QSqlQueryModel;
     model->setQuery("SELECT *  FROM ACTUALITE ORDER  BY DATEA");


     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("lieu"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("source"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("categorie"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("description"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("image"));


     return model;
}











//-------------------------------------------------------------------------------

void Actualite::genererPDFact()
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

            pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toString() +" "" " "</td> </td>" ;
        }
        doc.setHtml(pdf);
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);


    }
