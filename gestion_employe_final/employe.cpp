#include "employe.h"

Employe::Employe()
{

}

bool Employe::ajouter()
{
    QSqlQuery query;


        query.prepare("INSERT INTO EMPLOYE (NOM,PRENOM,CIN,POSTE,MAIL) "
                      "VALUES(:NOM,:PRENOM,:CIN,:POSTE,:MAIL)");

        query.bindValue(":NOM",NOM);
        query.bindValue(":PRENOM",PRENOM);
        query.bindValue(":CIN",CIN );
        query.bindValue(":POSTE",POSTE);
        query.bindValue(":MAIL",MAIL);

  return query.exec();
}

QSqlQueryModel * Employe::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select* from EMPLOYE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("POSTE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL"));

    return model;
}

bool Employe::supprimer(QString NOM)
{
    QSqlQuery qry;
    QString temp_nom =NOM;
    qry.prepare("Delete from EMPLOYE where NOM = :NOM");
    qry.bindValue(":NOM",temp_nom);
    return qry.exec();
}

QSqlQueryModel *Employe::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from EMPLOYE where CIN LIKE '"+rech+"%'"/*or NOM LIKE '"+rech+"%' or PRENOM LIKE '"+rech+"%'"*/);



    return model;
}

QSqlQueryModel * Employe::tri()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from EMPLOYE order by POSTE desc");
    q->exec();
    model->setQuery(*q);
    return  model;
}
