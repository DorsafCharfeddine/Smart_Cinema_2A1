#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "film.h"
#include "projection.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVariant data(const QModelIndex &index, int role) const;



;

private slots:

    void on_ajouter_clicked();

    void on_tableView_films_activated(const QModelIndex &index);

    void on_pushButton_suppFilm_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_clicked();

    void on_pushButton_pdfFilms_clicked();

    void on_pushButton_tri_clicked();

    void on_pushButton_ajouter_proj_clicked();

    void on_tableView_projections_activated(const QModelIndex &index);

    void on_pushButton_update_proj_clicked();

    void on_pushButton_supp_proj_clicked();

    void on_pushButton_2_clicked();

    void on_rech_proj_clicked();

    void on_tri_proj_clicked();

    void on_exporterPdf_proj_clicked();

    void on_exporterExcel_proj_clicked();

private:
    Ui::MainWindow *ui;
    film tmpFilm;
    projection tmpProjection;
    //QSound *son;

};
#endif // MAINWINDOW_H
