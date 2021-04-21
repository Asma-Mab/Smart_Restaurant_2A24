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
db.setDatabaseName("test");
    db.setUserName("system");
    db.setPassword("752841");
    db.open();
    test=true;

return  test;
}
void Connexion::fermerConnexion()
{db.close();}
