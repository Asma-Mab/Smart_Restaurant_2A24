#include "connexion.h"
#include <exception>
#include <QDebug>
#include <QSqlError>
#include<QSqlQuery>

//test tutoriel git

Connexion::Connexion()
{}

bool Connexion::ouvrirConnexion()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test2");
    db.setUserName("system");
    db.setPassword("752841");
   if (db.open())
    test=true;
   qDebug() << db.lastError();

return  test;
}
void Connexion::fermerConnexion()
{db.close();}
