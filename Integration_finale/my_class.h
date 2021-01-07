#ifndef MY_CLASS_H
#define MY_CLASS_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>


class my_class
{
public:


    my_class();
    my_class(int,QString,QString,QString,QString);


    bool ajouter();
    bool modifier(int);
     QSqlQueryModel * afficher();
      bool supprimer(int);


      int nombre;
      QString text, nom, num, date;


};

#endif // MY_CLASS_H
