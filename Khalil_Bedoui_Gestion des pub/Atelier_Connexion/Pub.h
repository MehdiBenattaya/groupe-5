#ifndef PUB_H
#define PUB_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class PUB
{
public:
    PUB();
    PUB(int,QString,QString,QString,QString );

    int getid();
    QString gettitre();
    QString getdescription();
    QString gettype();
    QString getdate();

    void setid (int);
    void settitre(QString);
    void setdescription(QString);
    void settype(QString);
    void setdate(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* Rechercher(QString);

private:
    int id;
    QString titre,description,type,date;
};

#endif // PUB_H
