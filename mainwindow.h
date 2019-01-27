#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:    
    bool gameOver = false;
    std::vector<QPushButton*> botoes;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool GameOver(char ultimaJogada);
    char ProximoAJogar();
    bool Ganhou();
    bool Empatou();

private:
    Ui::MainWindow *ui;

public slots:
    void SetaPosicao();
    void Quit();
    void NewGame();
};

#endif // MAINWINDOW_H
