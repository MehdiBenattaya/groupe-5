#include "actualite.h"
#include <
Actualite::Actualite()
{
id=0;
Titre= " ";
lieu= " ";
date= " ";
source= " ";
description= " ";
categorie= " ";
}

Actualite::Actualite(int id,QString Titre ,QString lieu,QString date,QString source,QString categorie,QString description)
{
    this->id=id; this->Titre=Titre;this->lieu=lieu;this->date=date;this->source=source;this->categorie=categorie;this->description=description;

}
int Actualite::getid(){return id;}

QString Actualite::getTitre() {return Titre;}
QString Actualite::getlieu() {return lieu;}
QString Actualite::getdate() {return date;}
QString Actualite::getsource()  {return source;}
QString Actualite::getcategorie() {return categorie;}
QString Actualite::getdescription() {return description;}


void Actualite::setid(int id) {this->id=id;}
void Actualite::setTitre(QString Titre){this->Titre=Titre;}
void Actualite::setlieu(QString lieu){this->lieu=lieu;}
void Actualite::setdate(QString date)  {this->date=date;}
void Actualite::setsource(QString source)  {this->source=source;}
void Actualite::setcategorie(QString categorie)   {this->categorie=categorie;}
void Actualite::setdescription(QString description)  {this->description=description;}
