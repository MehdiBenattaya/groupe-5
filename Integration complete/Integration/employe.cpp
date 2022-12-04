#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
#include <QObject>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
//#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>


Employe::Employe()
{
id="" ;numero_telephone="";salaire="" ; nom="" ; prenom="" ;  }

Employe::Employe(QString id ,QString numero_telephone, QString salaire,QString nom,QString prenom, QDate date_naissance,QString un,QString mdp,QString type)
{
    this->id=id;
    this->numero_telephone=numero_telephone;
    this->salaire=salaire;
    this->nom=nom;
    this->prenom=prenom;
    this->date_naissance=date_naissance;
    this->username = un ;
    this->password = mdp ;
    this->type = type ;
   // this->image=image;


}
QString Employe::getid()
{   return id;  }
QString Employe::getnumero_telephone()
{   return numero_telephone;  }
QString Employe::getsalaire()
{   return salaire; }
QString Employe::getnom()
{   return nom; }
QString Employe::getprenom()
{   return prenom;  }

/*QString Employe::getimage()
{   return image;  }*/
void Employe::setid(QString id){ this->id=id; }
void Employe::setnumero_telephone(QString numero_telephone){this->numero_telephone=numero_telephone; }
void Employe::setsalaire(QString  salaire){this->salaire=salaire; }
void Employe::setnom(QString nom){this->nom=nom; }
void Employe::setprenom(QString prenom){this->prenom=prenom; }
//void Employe::setimage(QString image){this->image=image; }

bool Employe::ajouter()
{
    //QString date = date_naissance.toString();
   QSqlQuery query;

          query.prepare("INSERT INTO EMPLOYES (ID,NUMERO_TELEPHONE,SALAIRE ,NOM,PRENOM,DATE_NAISSANCE,username,password,type) "
                        "VALUES (:id,:numero_telephone, :saliare,:nom, :prenom,:date_naissance,:username,:password,:type )");
          query.bindValue(0, id);
          query.bindValue(1, numero_telephone);
          query.bindValue(2, salaire);
          query.bindValue(3, nom);
          query.bindValue(4, prenom);
          query.bindValue(5 ,date_naissance);
          query.bindValue(6 ,username );
          query.bindValue(7 ,password);
          query.bindValue(8 ,type);

           return query.exec();

}
QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM EMPLOYES");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("numero_telephone"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("salaire"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("prenom"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_naissance"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Nom d'utilisateur"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("Mot de passe"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("Type"));

          return  model;
}
bool Employe::supprimer(QString id)
{

    QSqlQuery query;

           query.prepare("Delete from EMPLOYES where id=:id");
           query.bindValue(0, id);

            return query.exec();

}
bool Employe::update()
        {
            //QString date = date_naissance.toString();
            QSqlQuery query;
                query.prepare("UPDATE EMPLOYES SET NUMERO_TELEPHONE='"+numero_telephone+"' , SALAIRE='"+salaire+"' , NOM='"+nom+"' , PRENOM='"+prenom+"' , DATE_NAISSANCE=:date,username ='"+username+"' , password= '"+password+"',type = '"+type+"'  where ID='"+id+"' ");
                query.bindValue(":date" ,date_naissance);
                return   query.exec();


        }

QSqlQueryModel* Employe::tri()
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("SELECT * FROM EMPLOYES ORDER BY ID ");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("numero_telephone"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("salaire"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("nom"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("prenom"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_naissance"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("Nom d'utilisateur"));
   model->setHeaderData(7, Qt::Horizontal, QObject::tr("Mot de passe"));
   model->setHeaderData(8, Qt::Horizontal, QObject::tr("Type"));

   return  model;

}



QSqlQueryModel* Employe::trinom()
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("SELECT * FROM EMPLOYES ORDER BY NOM ");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("numero_telephone"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("salaire"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("nom"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("prenom"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_naissance"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("Nom d'utilisateur"));
   model->setHeaderData(7, Qt::Horizontal, QObject::tr("Mot de passe"));
   model->setHeaderData(8, Qt::Horizontal, QObject::tr("Type"));

   return  model;

}




QSqlQueryModel* Employe::trisalaire()
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("SELECT * FROM EMPLOYES ORDER BY SALAIRE ");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("numero_telephone"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("salaire"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("nom"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("prenom"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_naissance"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("Nom d'utilisateur"));
   model->setHeaderData(7, Qt::Horizontal, QObject::tr("Mot de passe"));
   model->setHeaderData(8, Qt::Horizontal, QObject::tr("Type"));

   return  model;

}

QSqlQueryModel* Employe ::Rechercher(QString id_string)
{
    QSqlQueryModel *model=new::QSqlQueryModel;
                   model->setQuery("SELECT * FROM  EMPLOYES where ID like '%"+id_string+"%'");
                   return model;

    }





