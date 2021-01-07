#include "add_class.h"
#include "ui_add_class.h"

add_class::add_class(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_class)
{
    ui->setupUi(this);
}

add_class::~add_class()
{
    delete ui;
}


//config ok et cancel
void add_class::on_buttonBox_accepted()
{
accept();
}

void add_class::on_buttonBox_rejected()
{
reject();
}


//recuperation des donnees du formulaire

QString add_class::get_date() const { //date
    return ui->date_res->date().toString("dd.MM.yyyy");
}

QString add_class::texte() const { //text edit
    return ui->texte_res->toPlainText();
}

QString add_class::nom() const { //text edit
    return ui->nom->text();
}
QString add_class::num() const { //text edit
    return ui->num->text();
}

int add_class::nbr() const{ //integer

    return ui->nb->value();
}


//QString add_class::get_time() const { //time

 //   return ui->timeEdit->time().toString("hh:mm");
//}

//remplissage des champs du formulaire a partir de la base

void add_class::fill_form(int selected ) {
    QSqlQuery query;
    query.prepare("select * from RES where V_INT= :integer");
    query.bindValue(":integer", selected);
    query.exec();
    while(query.next()){
        ui->date_res->setDate(QDate::fromString(query.value(4).toString(),"dd.MM.yyyy"));//date
 ui->nom->setText(query.value(1).toString());//text edit
  ui->num->setText(query.value(2).toString()); //line edit
    ui->nb->setValue(selected);// integer

  ui->texte_res->setText(query.value(3).toString());

    }


}

