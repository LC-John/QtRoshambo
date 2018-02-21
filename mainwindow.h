#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPixmap>
#include <QTime>
#include <QtMultimedia/qsound.h>
#include <roshambo.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPixmap rock_pixmap, paper_pixmap, scissors_pixmap;
    QPixmap me_pixmap, opposite_pixmap;
    QPixmap win_pixmap, draw_pixmap, defeated_pixmap;
    QPixmap none_pixmap;
    QPixmap title_pixmap;
    QSound win_sound, draw_sound, defeated_sound;
    QSound title_sound;

    int cheat;

    //QPixmap help_pixmap[10];
    //int help_no;

    QTime t;

    roshambo game;

    void show_me();
    void show_opposite();
    void show_score();
    QString op2string(int op);
    bool clicked();

private slots:
    void rock_clicked();
    void paper_clicked();
    void scissors_clicked();
    void menu_restart_clicked();
    void menu_about_clicked();
    //void menu_help_clicked();
    void menu_cheat_clicked();
};

#endif // MAINWINDOW_H
