#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class Employe
{
public:
    Employe();
    Employe(QString,QString,QString,QString,QString,QDate,QString,QString,QString);
    QString getid();
    QString getnumero_telephone();
    QString getsalaire();
    QString getnom();
    QString getprenom();
    QString getdate_naissance();

    void setid(QString);
    void setnumero_telephone(QString) ;
    void setsalaire(QString);
    void setnom(QString);
    void setprenom(QString);
    void setdate_naissance(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool update();
    QSqlQueryModel* Rechercher(QString);
    QSqlQueryModel* tri();
     QSqlQueryModel* trinom();
      QSqlQueryModel* trisalaire();
    void genererPDFact();


private:
    QString id;
    QString nom,prenom,numero_telephone,salaire,username,password,type;
    QDate date_naissance;

};

#endif // EMPLOYE_H
