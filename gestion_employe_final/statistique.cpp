#include "statistique.h"
#include <QSqlQuery>
#include <QPainter>
#include <QString>
#include <QtSql/QSqlQueryModel>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QPaintEvent>

statistique::statistique()
{

}
double statistique::statestique_partie1()
{

    double count=0 ;
    QSqlQuery requete("select * from POSTE where SALAIRE between 400 and 800") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;



}

double statistique::statestique_partie2()
{
    double count=0 ;
    QSqlQuery requete("select * from POSTE where SALAIRE between 801 and 1200") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;
}
