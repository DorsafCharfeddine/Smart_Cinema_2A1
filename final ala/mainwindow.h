#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"billet.h"
#include"pointdevente.h"
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

private slots:
    void on_ajouter_billet_clicked();

    void on_modifier_billet_clicked();

    void on_supprimer_billet_clicked();

    void on_rech_billet_clicked();

    void on_triee_billet_clicked();

    void on_imprimer_billet_clicked();

    void on_ajouter_p_clicked();

    void on_ajouter_pointdevente_clicked();

    void on_rech_p_clicked();

    void on_trie_p_clicked();

    void on_modif_point_clicked();

    void on_pushButton_clicked();

    void on_imprimer_p_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    billet b_temp;
pointdevente p_temp;

};
#endif // MAINWINDOW_H
