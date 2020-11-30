#include "projection.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QStringListModel>
#include <QTableView>
#include <QTableWidget>

projection::projection()
{

}

projection::projection(int num_projection, int id, QDateTime date_projection, int num_salle, int capacite_salle)
{
    this->num_projection = num_projection;
    this->id = id;
    this->date_projection = date_projection;
    this->num_salle = num_salle;
    this->capacite_salle = capacite_salle;

}

bool projection::ajouter_p()
{
    QSqlQuery query;
    query.prepare("INSERT into PROJECTION (num_projection, id, date_projection, num_salle, capacite_salle)"
              "Values(:num_projection, :id, :date_projection, :num_salle, :capacite_salle)");
    query.bindValue(":num_projection", num_projection);
    query.bindValue(":id", id);
    query.bindValue(":date_projection", date_projection);
    query.bindValue(":num_salle", num_salle);
    query.bindValue(":capacite_salle", capacite_salle);

    return query.exec();
}

QSqlQueryModel * projection::afficher_p()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * from PROJECTION");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num projection"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID film"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date de projection"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numero salle"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Capacite salle"));

    return model;
}

bool projection::supprimer_p(int num_projection)
{
    QSqlQuery query;
    QString res = QString::number(num_projection);
    query.prepare("DELETE from PROJECTION where num_projection = :num_projection");
    query.bindValue(":num_projection", res);
    return query.exec();
}

QSqlQueryModel * projection::rechercher_p(int num_projection, QDateTime date_projection, int num_salle)
{
    QSqlQuery *query=new QSqlQuery();
    query->prepare("select * from projection where num_projection=:num_projection or date_projection=:date_projection "
                   "or num_salle=:num_salle");
    query->bindValue(":num_projection",num_projection);
    query->bindValue(":date_projection",date_projection);
    query->bindValue(":num_salle",num_salle);
    query->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*query);
    return model;
}


