#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <list>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    botoes = {ui->btn00, ui->btn01, ui->btn02,
              ui->btn10, ui->btn11, ui->btn12,
              ui->btn20, ui->btn21, ui->btn22};
    for(QPushButton* pb : botoes)
    {
        connect(pb, SIGNAL(clicked()), this, SLOT(SetaPosicao()));
    }

    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(Quit()));
    connect(ui->btnNew, SIGNAL(clicked()), this, SLOT(NewGame()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetaPosicao()
{
    if (!gameOver)
    {
        QPushButton* pressedBtn = qobject_cast<QPushButton*>(sender());
        if (pressedBtn)
        {
            if (pressedBtn->text() != "X" && pressedBtn->text() != "O")
            {
                char nextP = ProximoAJogar();
                pressedBtn->setText(QString(nextP));
                gameOver=GameOver(nextP);
            }
        }
    }
}

void MainWindow::NewGame()
{
    gameOver = false;
    for(QPushButton* btn : botoes)
    {
        btn->setText(QString(""));
        ui->labelNextMove->setText(QString("Next to play: X"));
    }
}

void MainWindow::Quit()
{
    QCoreApplication::quit();
}

char MainWindow::ProximoAJogar()
{
    if (ui->labelNextMove->text().back()=="X")
    {
        ui->labelNextMove->setText(QString("Next to play: %1").arg('O'));
        return 'X';
    }

    ui->labelNextMove->setText(QString("Next to play: %1").arg('X'));
    return 'O';
}

bool MainWindow::GameOver(char ultimaJogada)
{
    if (Ganhou())
    {
        ui->labelNextMove->setText(QString("** %1 WINS! **").arg(ultimaJogada));
        return true;
    }
    else if (Empatou())
    {
        ui->labelNextMove->setText(QString("** DRAW **"));
        return true;
    }

    return false;
}

bool MainWindow::Ganhou()
{
    return (botoes[0]->text() == botoes[1]->text() && botoes[1]->text() == botoes[2]->text() && botoes[1]->text() != "") || // Linha 1
            (botoes[3]->text() == botoes[4]->text() && botoes[4]->text() == botoes[5]->text() && botoes[4]->text() != "") || // Linha 2
            (botoes[6]->text() == botoes[7]->text() && botoes[7]->text() == botoes[8]->text() && botoes[7]->text() != "") || // Linha 3
            (botoes[0]->text() == botoes[3]->text() && botoes[3]->text() == botoes[6]->text() && botoes[3]->text() != "") || // Coluna 1
            (botoes[1]->text() == botoes[4]->text() && botoes[4]->text() == botoes[7]->text() && botoes[4]->text() != "") || // Coluna 2
            (botoes[2]->text() == botoes[5]->text() && botoes[5]->text() == botoes[8]->text() && botoes[5]->text() != "") || // Coluna 3
            (botoes[0]->text() == botoes[4]->text() && botoes[4]->text() == botoes[8]->text() && botoes[4]->text() != "") || // Diagonal 1
            (botoes[6]->text() == botoes[4]->text() && botoes[4]->text() == botoes[2]->text() && botoes[4]->text() != ""); // Diagonal 2
}

bool MainWindow::Empatou()
{
    int i = 0;
    for(QPushButton* btn : botoes)
    {
        if(btn->text() == "X" || btn->text() == "O")
        {
            i++;
        }
    }

    if (i == 9)
    {
        return true;
    }

    return false;
}
