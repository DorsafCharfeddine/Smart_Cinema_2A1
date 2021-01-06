#include "poste.h"

poste::poste()
{

}

bool poste::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO POSTE (NOM,ID,NBRH,SALAIRE) "
                  "VALUES(:NOM,:ID,:NBRH,:SALAIRE)");

    query.bindValue(":NOM",NOM);
    query.bindValue(":ID",ID);
    query.bindValue(":NBRH",NBRH );
    query.bindValue(":SALAIRE",SALAIRE);

    return query.exec();
}

QSqlQueryModel * poste::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select* from POSTE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NBRH"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("SALAIRE"));

    return model;
}

bool poste::supprimer(QString NOM)
{
    QSqlQuery qry;
    QString temp_nom =NOM;
    qry.prepare("DELETE from POSTE where NOM =:NOM");
    qry.bindValue(":NOM",temp_nom);
    return qry.exec();
}

QSqlQueryModel *poste::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from POSTE where ID LIKE '"+rech+"%'"/*or NOM LIKE '"+rech+"%' or PRENOM LIKE '"+rech+"%'"*/);



    return model;
}

QSqlQueryModel* poste::tri()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery* q = new QSqlQuery();
    q->prepare("select * from POSTE order by ID desc");
    q->exec();
    model->setQuery(*q);
    return  model;
}
