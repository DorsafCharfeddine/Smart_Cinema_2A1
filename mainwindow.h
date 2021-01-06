#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QMessageBox>
#include "exportexcelobject.h"
#include <QDialog>
#include <QFileDialog>

#include <QtSerialPort>
#include "smtp.h"
#include "my_class.h"
#include "add_class.h"
#include "add_offre.h"
#include "offre.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    my_class tmp;
    offre tp;

    QSortFilterProxyModel *proxyo,*proxyr;

    void show_tables();




private slots:
    void on_actionadd_triggered();

    void on_actiondelete_triggered();

    void on_recherche_4_textChanged(const QString &arg1);

    void on_tableau_5_doubleClicked();

    void on_tableau_5_clicked(const QModelIndex &index);


   void    on_actionajouter_triggered() ;


   void sendMail();
   void mailSent(QString);
   void browse();


   void on_actionSupprimer_Offre_triggered();


   void on_recherche_3_textChanged(const QString &arg1);

   void on_tableau_4_doubleClicked(const QModelIndex &index);

   void on_tableau_4_clicked(const QModelIndex &index);

   void on_pushButton_clicked();

   void on_red_slider_rangeChanged(int value);

   void on_green_slider_rangeChanged(int value);
   void  updateRGB(QString command);





private:
    Ui::MainWindow *ui;
    int selectedr=0;
    QString selectedo="test";
        QStringList files;
         QSerialPort *arduino;
         bool arduino_is_available;
     static const quint16 arduino_uno_vendor_id = 9025;
     static const quint16 arduino_uno_product_id = 67;
     QString arduino_port_name;
};
#endif // MAINWINDOW_H
