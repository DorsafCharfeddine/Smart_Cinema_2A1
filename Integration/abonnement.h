#ifndef ABONNEMENT_H
#define ABONNEMENT_H
#include<QSqlQueryModel>
#include<QString>

class abonnement
{
public:
    abonnement();
    abonnement(QString,QString,QString,QString,QString);
    bool verifiernum(QString );
    bool verifierid(QString );
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel * tridesc();
     QSqlQueryModel * tridasc();
      bool supprimer(QString);
      QString  apercu_pdf();
      bool modifier(QString,QString,QString,QString,QString);
private:
    QString numero;
    QString libelle;
    QString nb_point;
    QString id;
    QString datea;
};

#endif // ABONNEMENT_H
