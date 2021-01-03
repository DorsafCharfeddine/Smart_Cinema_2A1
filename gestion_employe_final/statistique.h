#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QSqlQuery>
#include <QPainter>
#include <QString>
#include <QtSql/QSqlQueryModel>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QDialog>
namespace Ui {
class statistique;
}
class statistique : public QDialog
{
    Q_OBJECT

public:
    statistique();

     double statestique_partie2();
     double statestique_partie1();

};

#endif // STATISTIQUE_H
