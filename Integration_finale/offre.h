#ifndef OFFRE_H
#define OFFRE_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>


class offre
{
public:


    offre();
    offre(QString,QString,QString,QString);


    bool ajouter();
    bool modifier(QString);
     QSqlQueryModel * afficher();
      bool supprimer(QString);



      QString text, line, combo, date;


};
#endif // OFFREH_H
