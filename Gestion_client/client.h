#ifndef CLIENT_H
#define CLIENT_H
#include<QSqlQueryModel>
#include<QString>

class client
{
public:
    client();
    client(QString,QString,QString,QString);
    bool verifierId(QString );
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier(QString,QString,QString,QString);
     bool supprimer(QString);
      QSqlQueryModel * rechercher(QString);
      QSqlQueryModel * recherche(QString);
      QSqlQueryModel * tridesc();
       QSqlQueryModel * tridasc();
       QString  apercu_pdf();

private:
    QString id;
    QString nom;
    QString prenom;
    QString email;
};

#endif // CLIENT_H
