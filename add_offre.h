#ifndef ADD_OFFRE_H
#define ADD_OFFRE_H
#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QWidget>

namespace Ui {
class add_offre;
}

class add_offre : public QDialog
{
    Q_OBJECT

public:
    explicit add_offre(QWidget *parent = nullptr);
    ~add_offre();
    QString get_date() const ;
    QString text() const ;
    QString line() const ;
    QString combobox() const;

    void fill_form(QString);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_offre *ui;
};

#endif // ADD_OFFRE_H
