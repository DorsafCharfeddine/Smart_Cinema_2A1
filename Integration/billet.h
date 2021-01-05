#ifndef BILLET_H
#define BILLET_H
#include<QSqlQueryModel>
#include<QString>

class billet
{
public:
    billet();
    billet(QString,QString,int);
    bool ajouter();
    QSqlQueryModel *  afficher();
bool modifier(QString ,QString ,int);
bool  supprimer(QString);
QSqlQueryModel * rechercher(QString);
QSqlQueryModel *tridesc();
QString apercu_pdf();




private:
    QString reference;
    QString categorie;
    int prix;

};

#endif // BILLET_H
