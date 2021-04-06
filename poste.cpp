#include "poste.h"

poste::poste()
{
    this->matricule=0;
    this->type="";
    this->salaire=0;
    this->nb_heures=0;
}
poste::poste(int matricule,QString type,int salaire,int nb_heures){
    this->matricule=matricule;
    this->type=type;
    this->salaire=salaire;
    this->nb_heures=nb_heures;

}
poste::~poste()
{

}
int poste::getmatricule(){
    return matricule;
}

QString poste::gettype(){
    return type;
}
int poste::getsalaire(){
    return salaire;
}

int poste::getnb_heures(){
    return nb_heures;
}

void poste::setmatricule(int matricule){
    this->matricule=matricule;
}
void poste::settype(QString type){
    this->type=type;
}

void poste::setsalaire(int salaire){
    this->salaire=salaire;
}


void poste::setnb_heures(int nb_heures){
    this->nb_heures=nb_heures;
}

bool poste::ajouter(){
    QSqlQuery query;
    query.prepare("insert into poste (matricule,nom,nb_heures,salaire) values (:matricule,:nom,:nb_heures,:salaire)");
    query.bindValue(":matricule",matricule);
    query.bindValue(":type",type);
    query.bindValue(":nb_heures",nb_heures);
    query.bindValue(":salaire",salaire);

    return query.exec();
}


QSqlQueryModel * poste::afficher(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from poste");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE_CR"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NOMBRE_EMP"));
    return model;
}

bool poste::supprimer(int matricule){
    QSqlQuery q;
    q.prepare("select * from poste where matricule=:matricule");
    q.bindValue(":matricule",matricule);
    q.exec();
    int total=0;
    while(q.next()){
        total++;
    }
    if(total==1){
        QSqlQuery qu;
        qu.prepare("select * from employe where id_poste=:matricule");
        qu.bindValue(":matricule",matricule);
        qu.exec();
        while(qu.next()){
            e.supprimer(qu.value(0).toInt());
        }

        QSqlQuery query;
        query.prepare("delete from poste where matricule=:matricule");
        query.bindValue(":matricule",matricule);
        return query.exec();
    }
    else{
        return false;
    }

}

poste poste::trouver(int matricule){
    QSqlQuery query;
    query.prepare("select * from poste where matricule=:matricule");
    query.bindValue(":matricule",matricule);
    query.exec();
    poste e;
    while(query.next()){
        e.setmatricule(query.value(0).toInt());
        e.settype(query.value(1).toString());
        e.setsalaire(query.value(2).toInt());
        e.setnb_heures(query.value(3).toInt());

    }
    return e;
}


bool poste::modifier(int idr){
    QSqlQuery query;
    query.prepare("update poste set matricule=:matricule,nom=:nom,salaire=:salaire,nombre_emp=:nombre_emp where matricule=:idr");
    query.bindValue(":idr",idr);
    query.bindValue(":matricule",matricule);
    query.bindValue(":type",type);
    query.bindValue(":salaire",salaire);
    query.bindValue(":nb_heures",nb_heures);
    return query.exec();
}
QSqlQueryModel * poste::trisalaire(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from poste order by salaire ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NB_HEURES"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("SALAIRE"));


    return model;
}
QSqlQueryModel * poste::tritype(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from poste order by nombre_emp ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NB_HEURES"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("SALAIRE"));


    return model;
}
QSqlQueryModel * poste::tri_matricule(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from poste order by matricule ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NB_HEURES"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("SALAIRE"));


    return model;
}
QSqlQueryModel * poste::recherche_poste(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from poste where type like '"+str+"%' or matricule like '"+str+"%' or salaire like '"+str+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NB_HEURES"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("SALAIRE"));


    return model;
}

QSqlQueryModel * poste::recherche_type_matricule(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from poste where type like '"+str+"%' or matricule like '"+str+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NB_HEURES"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("SALAIRE"));


    return model;
}
QSqlQueryModel * poste::recherche_type_salaire(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from poste where type like '"+str+"%' or salaire like '"+str+"%'" );
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NB_HEURES"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("SALAIRE"));


    return model;
}
QSqlQueryModel * poste::recherche_matricule_salaire(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from poste where matricule like '"+str+"%' or salaire like '"+str+"%'" );
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NB_HEURES"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("SALAIRE"));


    return model;
}
QSqlQueryModel * poste::recherche_type(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from poste where type like '"+str+"%'" );
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID_DEPARTEMENTs"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NB_HEURES"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("SALAIRE"));


    return model;
}
QSqlQueryModel * poste::recherche_matricule(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from poste where matricule like '"+str+"%'" );
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NB_HEURES"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("SALAIRE"));


    return model;
}
QSqlQueryModel * poste::recherche_salaire(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from poste where salaire like '"+str+"%'" );
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("NB_HEURES"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("SALAIRE"));


    return model;
}


QStringList poste::listPoste(){
    QSqlQuery query;
    query.prepare("select matricule from poste");
    query.exec();
    QStringList list;
    while(query.next()){
        list.append(query.value(0).toString());
    }
    return list;

}
