#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTime>
#include <QCoreApplication>
#include <QString>
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    win_sound("C:/Users/DrLC/Desktop/QtRoshambo/sounds/win.wav"),
    draw_sound("C:/Users/DrLC/Desktop/QtRoshambo/sounds/draw.wav"),
    defeated_sound("C:/Users/DrLC/Desktop/QtRoshambo/sounds/defeated.wav"),
    title_sound("C:/Users/DrLC/Desktop/QtRoshambo/sounds/title.wav"),
    cheat(-1)
{
    rock_pixmap = QPixmap("C:/Users/DrLC/Desktop/QtRoshambo/figures/rock.png");
    paper_pixmap = QPixmap("C:/Users/DrLC/Desktop/QtRoshambo/figures/paper.png");
    scissors_pixmap = QPixmap("C:/Users/DrLC/Desktop/QtRoshambo/figures/scissors.png");
    me_pixmap = QPixmap("C:/Users/DrLC/Desktop/QtRoshambo/figures/player.png");
    opposite_pixmap = QPixmap("C:/Users/DrLC/Desktop/QtRoshambo/figures/computer.png");
    win_pixmap = QPixmap("C:/Users/DrLC/Desktop/QtRoshambo/figures/win.png");
    draw_pixmap = QPixmap("C:/Users/DrLC/Desktop/QtRoshambo/figures/draw.png");
    defeated_pixmap = QPixmap("C:/Users/DrLC/Desktop/QtRoshambo/figures/defeated.png");
    none_pixmap = QPixmap("C:/Users/DrLC/Desktop/QtRoshambo/figures/none.png");
    title_pixmap = QPixmap("C:/Users/DrLC/Desktop/QtRoshambo/figures/title.png");

    //help_no = 5;
    //for (int i = 0; i < help_no; i++)
    //{
    //    char tmp[10];
    //    sprintf_s(tmp, "%d", i+1);
    //    help_pixmap[i] = QPixmap(QString("C:/Users/DrLC/Desktop/QtRoshambo/figures/game")+QString(i+1)+QString(".png"));
    //}

    ui->setupUi(this);

    connect(ui->rock_btn, SIGNAL(clicked()), this, SLOT(rock_clicked()));
    ui->rock_btn->setIcon(rock_pixmap);
    connect(ui->scissors_btn, SIGNAL(clicked()), this, SLOT(scissors_clicked()));
    ui->scissors_btn->setIcon(scissors_pixmap);
    connect(ui->paper_btn, SIGNAL(clicked()), this, SLOT(paper_clicked()));
    ui->paper_btn->setIcon(paper_pixmap);
    ui->me_label_img->setPixmap(me_pixmap);
    ui->opposite_label_img->setPixmap(opposite_pixmap);

    connect(ui->menu_restart_btn, SIGNAL(triggered()), this, SLOT(menu_restart_clicked()));
    connect(ui->menu_about_btn, SIGNAL(triggered()), this, SLOT(menu_about_clicked()));
    //connect(ui->menu_help_btn, SIGNAL(triggered()), this, SLOT(menu_help_clicked()));
    connect(ui->menu_cheat_btn, SIGNAL(triggered()), this, SLOT(menu_cheat_clicked()));

    ui->centralWidget->setLayout(ui->main_layout);

    show_me();
    show_opposite();
    show_score();

    title_sound.setLoops(3);
    title_sound.play();
    QMessageBox msg(QMessageBox::NoIcon, "Roshambo Welcome", "");
    msg.setIconPixmap(title_pixmap);
    msg.exec();
    title_sound.stop();

    win_sound.play(); win_sound.stop();
    draw_sound.play(); draw_sound.stop();
    defeated_sound.play(); defeated_sound.stop();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_me()
{
    me_pixmap.scaled(ui->me_img->size(), Qt::KeepAspectRatio);
    switch(game.get_me())
    {
    case 0:
        ui->me_img->setPixmap(rock_pixmap);
        break;
    case 1:
        ui->me_img->setPixmap(scissors_pixmap);
        break;
    case 2:
        ui->me_img->setPixmap(paper_pixmap);
        break;
    default:
        ui->me_img->setPixmap(none_pixmap);
        break;
    }
}

void MainWindow::show_opposite()
{
    opposite_pixmap.scaled(ui->opposite_img->size(), Qt::KeepAspectRatio);
    switch(game.get_opposite())
    {
    case 0:
        ui->opposite_img->setPixmap(rock_pixmap);
        break;
    case 1:
        ui->opposite_img->setPixmap(scissors_pixmap);
        break;
    case 2:
        ui->opposite_img->setPixmap(paper_pixmap);
        break;
    default:
        ui->opposite_img->setPixmap(none_pixmap);
        break;
    }
}

void MainWindow::show_score()
{
    ui->me_label->setText(QString("PLAYER: "));
    ui->me_score->setValue(game.get_me_score());
    ui->opposite_label->setText(QString("COMPUTER: "));
    ui->opposite_score->setValue(game.get_opposite_score());
}

QString MainWindow::op2string(int op)
{
    switch (op) {
    case 0:
        return "ROCK";
    case 1:
        return "SCISSORS";
    case 2:
        return "PAPER";
    default:
        return "";
    }
}

bool MainWindow::clicked()
{
    if(!game.set_opposite(cheat))
        return false;
    //t.start();
    //int seg = 500, next_cnt = 0, __me_img = 0, __opposite_img = 2;
    //QPixmap *rsp_pixmaps[3] = {&rock_pixmap, &scissors_pixmap, &paper_pixmap};
    //while(t.elapsed()<5000)
    //{
    //    if (t.elapsed() > next_cnt)
    //    {
    //        ui->me_img->setPixmap(*(rsp_pixmaps[__me_img]));
    //        ui->opposite_img->setPixmap(*(rsp_pixmaps[__opposite_img]));
    //        __me_img = (__me_img + 1) % 3;
    //        __opposite_img = (__opposite_img + 1) % 3;
    //        next_cnt += seg;
    //        if (next_cnt >= 2000)
    //            seg = 1000;
    //    }
    //}
    show_me();
    show_opposite();
    if(!game.comp())
        return false;
    switch(game.get_if_win())
    {
    case 0:
        draw_sound.play();
        break;
    case 1:
        win_sound.play();
        break;
    case -1:
        defeated_sound.play();
        break;
    default:
        break;
    }
    t.start();
    while(t.elapsed()<200)
        QCoreApplication::processEvents();
    QMessageBox msg(QMessageBox::NoIcon, "Roshambo Result", "");
    switch(game.get_if_win())
    {
    case 0:
        msg.setIconPixmap(draw_pixmap);
        break;
    case 1:
        msg.setIconPixmap(win_pixmap);
        break;
    case -1:
        msg.setIconPixmap(defeated_pixmap);
        break;
    default:
        break;
    }
    msg.exec();
    show_score();
    return true;
}

void MainWindow::rock_clicked()
{
    game.set_me(0);
    clicked();
}

void MainWindow::scissors_clicked()
{
    game.set_me(1);
    clicked();
}

void MainWindow::paper_clicked()
{
    game.set_me(2);
    clicked();
}

void MainWindow::menu_restart_clicked()
{
    game.reset();
    show_me();
    show_opposite();
    show_score();
}

void MainWindow::menu_about_clicked()
{
    QString txt = "Hi! I'm DrLC. I'm a PKU under-graduate. This is my Qt game for the Embedded Linux course. I hope you enjoy it. :)";
    QMessageBox msg(QMessageBox::NoIcon, "Roshambo About Me", txt);
    msg.exec();
}

/*
void MainWindow::menu_help_clicked()
{
    for (int i = 0; i < help_no; i++)
    {
        QMessageBox msg(QMessageBox::NoIcon, "Roshambo Help", "");
        msg.setIconPixmap(help_pixmap[i]);
        msg.exec();
    }
}
*/

void MainWindow::menu_cheat_clicked()
{

}
