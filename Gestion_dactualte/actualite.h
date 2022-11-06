#ifndef ACTUALITE_H
#define ACTUALITE_H
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QImage>

class Actualite
{
public:
    Actualite();
    Actualite(QString id ,QString Titre ,QString lieu,QDate date,QString source,QString categorie,QString description,QString imageurl);
    QString getid();
    QString getTitre();
    QString getlieu();
    QDate getdate();
    QString getsource();
   QString getcategorie();
     QString getdescription();
   QString getimage();
    void setid(QString);
    void setTitre(QString);
    void setlieu(QString);
    void setdate(QDate);
    void setsource(QString);

    bool ajouter();
     bool modifier();
    bool supprimer(QString id);
  void setcategorie(QString);
    void setdescription(QString);
     void setimage(QString);




     QSqlQueryModel* afficher();
   QSqlQueryModel* rechercher(QString id);
 QSqlQueryModel* recherchercategorie(QString categorie);

 QSqlQueryModel* trier();


private:

    QString  id,Titre,lieu,source,categorie,description;
QDate date;

QString imageurl;
};

#endif // ACTUALITE_H
