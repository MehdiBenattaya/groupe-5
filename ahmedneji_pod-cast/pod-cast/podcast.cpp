#include "podcast.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

Podcast::Podcast()
{
id=0; sujet=" "; nmbdeparticipants=0; script=" "; duree=" "; date=" "; heure=" ";
}


Podcast::Podcast(int id,QString sujet,int nmbdeparticipants,QString script,QString duree,QString date,QString heure)
{this->id=id;  this->sujet=sujet; this->nmbdeparticipants=nmbdeparticipants; this->script=script; this->duree=duree; this->date=date; this->heure=heure;}
int Podcast::getid(){return id;}
int Podcast::getnmbdeparticipants(){return nmbdeparticipants;}
QString Podcast::getscript(){return script;}
QString Podcast::getduree(){return duree;}
QString Podcast::getdate(){return date;}
QString Podcast::getheure(){return heure;}
QString Podcast::getsujet(){return sujet;}
void Podcast::setid(int id){this->id=id;}
void Podcast::setnmbdeparticipants(int nmbdeparticipants){this->nmbdeparticipants=nmbdeparticipants;}
void Podcast::setscript(QString script){this->script=script;}
void Podcast::setduree(QString duree){this->duree=duree;}
void Podcast::setdate(QString date){this->date=date;}
void Podcast::setheure(QString heure){this->heure=heure;}
void Podcast::setsujet(QString sujet){this->sujet=sujet;}
bool Podcast::ajouter()
{
    bool test=false;

  QString id_string= QString::number(id);
  QString nmbdeparticipants_string= QString::number(nmbdeparticipants);
        QSqlQuery query;
        query.prepare("INSERT INTO PODCAST (IDPOD, SUJET, PARTICIPANT, SCRIPT, DUREE, DATEPOD, HEURE)"
                      "VALUES (:id_string, :sujet, :nmbdeparticipants_string, :script, :duree, :date, :heure)");
        query.bindValue(":id_string", id_string);
        query.bindValue(":sujet", sujet);
        query.bindValue(":nmbdeparticipants_string", nmbdeparticipants_string);
        query.bindValue(":script", script);
        query.bindValue(":duree", duree);
        query.bindValue(":date", date);
        query.bindValue(":heure", heure);
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




    return model;
}
