#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include "abonnement.h"
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
    void on_ajoutcl_clicked();

    void on_quittercl_clicked();

    void on_modifcl_clicked();

    void on_suppcl_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_trie_desc_clicked();

    void on_trie_asc_clicked();

    void on_imprimercl_clicked();

    void on_quittercl_2_clicked();

    void on_quitter_af_clicked();

    void on_refrech_clicked();

    void on_ajouterabo_clicked();

    void on_refrechabo_clicked();

    void on_rech_num_clicked();

    void on_rech_id_clicked();

    void on_quitterab_clicked();

    void on_quitterabo_clicked();

    void on_trie_asc_ab_clicked();

    void on_trie_desc_abo_clicked();

    void on_sup_abo_clicked();

    void on_refrech_ab_sup_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_sup_clicked();

    void on_imprimercl_2_clicked();

    void on_modifierabo_clicked();

private:
    Ui::MainWindow *ui;
client c_temp;
abonnement a_temp;
};
#endif // MAINWINDOW_H
