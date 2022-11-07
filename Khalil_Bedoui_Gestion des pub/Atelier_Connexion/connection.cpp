#include "connection.h"

Connection::Connection()
{
}

bool Connection::createconnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("TEST_BD");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("system");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void Connection::closeConnection()
{db.close();}
