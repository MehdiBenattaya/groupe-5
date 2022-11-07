#include "Pub.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

PUB::PUB()
{
    id=0; titre=""; description=""; type=""; date="";
}

    PUB::PUB(int id,QString titre,QString description,QString type,QString date)
    {this->id=id; this->titre=titre; this->description=description; this->type=type; this->date=date;}

    int PUB::getid(){return id;}
    QString PUB::gettitre(){return titre;}
    QString PUB::getdescription(){return description;}
    QString PUB::gettype(){return type;}
    QString PUB::getdate(){return date;}

    void PUB :: setid(int id){this->id=id;}
    void PUB :: settitre (QString titre){this->titre=titre;}
    void PUB :: setdescription(QString description){this->description=description;}
    void PUB :: settype(QString type){this->type=type;}
    void PUB :: setdate(QString date){this->date=date;}

    bool PUB :: ajouter()
    {
        //bool test=false;
        QSqlQuery query;
        QString id_string= QString::number(id);

        query.prepare("INSERT INTO PUB1 (ID, TITRE, DESCRIPTION, TYPE, DATE_P) "
                       "VALUES (:ID, :TITRE, :DESCRIPTION, :YPE, :DATE_P)");
        query.bindValue( 0 , id);
        query.bindValue( 1 , titre);
        query.bindValue( 2 , description);
        query.bindValue( 3 ,  type);
        query.bindValue( 4 , date);

    return query.exec();
    }



    QSqlQueryModel* PUB::afficher()
    {
        QSqlQueryModel* model= new QSqlQueryModel();

        model->setQuery("SELECT* FROM PUB1");
        model->setHeaderData( 0 , Qt :: Horizontal, QObject::tr("ID"));
        model->setHeaderData( 1 , Qt :: Horizontal, QObject::tr("TITRE"));
        model->setHeaderData( 2 , Qt :: Horizontal, QObject::tr("DESCRIPTION"));
        model->setHeaderData( 3 , Qt :: Horizontal, QObject::tr("TYPE"));
        model->setHeaderData( 4 , Qt :: Horizontal, QObject::tr("DATE_P"));

                return model;
    }

    bool PUB::supprimer(int)
    {
        QSqlQuery query;
        //QString id_string= QString::number(id);

        query.prepare("DELETE from PUB1 WHERE ID=:ID");
        query.bindValue( 0 , id);

        return query.exec();
    }


    bool PUB::modifier()
    {
        QSqlQuery query;
        QString id_string= QString::number(id);

query.prepare("UPDATE PUB1 SET ID='"+id_string+"' , TITRE='"+titre+"' , DESCRIPTION='"+description+"', TYPE='"+type+"', DATE_P='"+date+"'   where ID='"+id_string+"' ");
           query.bindValue( 0 , id);
           query.bindValue( 1 , titre);
           query.bindValue( 2 , description);
           query.bindValue( 3 ,  type);
           query.bindValue( 4 , date);
           return query.exec();
    }

    QSqlQueryModel *PUB::Rechercher(QString type)

     {

     QSqlQuery query;

          query.prepare("SELECT *  FROM PUB1 where TYPE=:TYPE");

            query.bindValue(":TYPE",type);
            query.exec();

       QSqlQueryModel* model= new QSqlQueryModel;
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("TITRE"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_P"));

           //model->setHeaderData(7, Qt::Horizontal, QObject::tr("image"));

           model->setQuery(query);
         return model;
}
