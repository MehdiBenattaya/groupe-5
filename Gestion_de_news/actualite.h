#ifndef ACTUALITE_H
#define ACTUALITE_H

#include <QString>


class Actualite
{
public:
    Actualite();
    Actualite(int id ,QString Titre ,QString lieu,QString date,QString source,QString categorie,QString description );
    int getid();
    QString getTitre();
    QString getlieu();
    QString getdate();
    QString getsource();
    QString getcategorie();
    QString getdescription();
    void setid(int);
    void setTitre(QString);
    void setlieu(QString);
    void setdate(QString);
    void setsource(QString);
    void setcategorie(QString);
    void setdescription(QString);
private:
    int id;
    QString Titre,lieu,date,source,categorie,description;



};

#endif // ACTUALITE_H
