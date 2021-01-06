#include "connection.h"

connection::connection()
{

}
bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Gestion_Billeterie");//inserer le nom de la source de données ODBC
db.setUserName("ala2007");//inserer nom de l'utilisateur
db.setPassword("ala2007");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
