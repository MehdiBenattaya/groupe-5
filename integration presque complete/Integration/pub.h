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

    //CRUD:
    bool ajouter();
    bool modifier();
    QSqlQueryModel* afficher();
    bool supprimer(int);

    //RECHERCHER:
    QSqlQueryModel* Rechercher(QString);
    QSqlQueryModel* Rechercherid(int);
    QSqlQueryModel* Recherchertitre(QString titre);

    //TRI:
    QSqlQueryModel * tri(); //tri_id
    QSqlQueryModel * tridate();
    QSqlQueryModel * trititre();

    void PDF();

private:
    int id;
    QString titre,description,type,date;
};










#endif // PUB_H
