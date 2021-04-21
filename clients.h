#ifndef CLIENTS_H
#define CLIENTS_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
class clients
{  QString nom, prenom, adresse, email;
    int CIN, num;
public:

    clients(){}
    clients(int, QString, QString, QString , QString, int );



    QString getAdresse(){return adresse;}
    QString getEmail(){return email;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    int getCIN(){return CIN;}
    int getNum(){return num;}

    void setAdresse(QString adresse){adresse=adresse;}
    void setNom(QString nom){nom=nom;}
    void setPrenom(QString prenom){prenom=prenom;}
    void setEmail(QString email){email=email;}
    void setCIN(int CIN){CIN=CIN;}
    void setNum(int num){num=num;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier(int/*,int,QString,QString,QString,QString*/);
    bool supprimer(int);

    bool recherche_nom(QString);
    bool recherche_num(int);
    bool recherche_cin(int);

    QSqlQueryModel * trie_az();
    QSqlQueryModel * trie_CIN();
    QSqlQueryModel * trie_num();
    QSqlQuery request(QString);

};

#endif // CLIENTS_H
