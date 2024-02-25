#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void timeout();
    void updateProgressBar();
    void setGameInfoText(const QString& text, short fontSize);
    void startGame(int selectedGameTime);


private:
    short player1Time;
    short player2Time;
    short currentPlayer;
    short gameTime;
    short initialGameTime;
    short currentGameTime;
    QTimer *pQTimer;
    Ui::MainWindow *ui;

    QProgressBar *player1ProgressBar;
    QProgressBar *player2ProgressBar;
    QLabel *gameInfoLabel;

    QPushButton *startGameButton;
    QPushButton *switchPlayerButton;
    QPushButton *stopGameButton;
private slots:
    void onStartGameButtonClicked();
    void onSwitchPlayerButtonClicked();
    void onStopGameButtonClicked();
};

#endif
