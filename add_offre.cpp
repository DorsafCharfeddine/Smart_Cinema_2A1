#include "add_offre.h"
#include "ui_add_offre.h"
#include "offre.h"

add_offre::add_offre(QWidget *parent) :
     QDialog(parent),
    ui(new Ui::add_offre)
{
    ui->setupUi(this);
}

add_offre::~add_offre()
{
    delete ui;
}

void add_offre::on_pushButton_clicked()
{



     accept();


}

void add_offre::on_pushButton_2_clicked()
{
  reject();
}
QString add_offre::get_date() const { //date
    return ui->dateTimeEdit_offre->date().toString("dd.MM.yyyy");
}

QString add_offre::text() const { //text edit
    return ui->textEdit_offre->toPlainText();
}

QString add_offre::combobox() const { //combo box

    return ui->comboBox_offre->currentText();
}

QString add_offre::line() const { //line edit

    return ui->lineEdit_offre->text();
}

void add_offre::fill_form(QString selected ) {
    QSqlQuery query;
    query.prepare("select * from TABLE1 where NOM_OFFRE= :line");
    query.bindValue("NOM_OFFRE", selected);
    query.exec();
    while(query.next()){
        ui->dateTimeEdit_offre->setDate(QDate::fromString(query.value(3).toString(),"dd.MM.yyyy"));//date
      //  ui->timeEdit->setTime(QTime::fromString(query.value(6).toString(),"hh:mm"));//time
 ui->textEdit_offre->setText(query.value(4).toString());//text edit
  ui->lineEdit_offre->setText(query.value(1).toString()); //line edit
  ui->comboBox_offre->setCurrentText(query.value(1).toString()); //combobox
     //ui->lineEdit->setValue(selected);
     // integer
   //  ui->doubleSpinBox->setValue(query.value(1).toReal()); // reel

    }


}

