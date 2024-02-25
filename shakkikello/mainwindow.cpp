#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    player1Time = 0;
    player2Time = 0;
    currentPlayer = 1;
    gameTime = 0;

    player1ProgressBar = new QProgressBar(this);
    player2ProgressBar = new QProgressBar(this);
    gameInfoLabel = new QLabel(this);

    startGameButton = new QPushButton("START GAME", this);
    stopGameButton = new QPushButton("Stop Game", this);
    QPushButton *switchPlayerButton1 = new QPushButton("Switch Player 1", this);
    QPushButton *switchPlayerButton2 = new QPushButton("Switch Player 2", this);

    pQTimer = new QTimer(this);

    connect(pQTimer, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(startGameButton, SIGNAL(clicked()), this, SLOT(onStartGameButtonClicked()));
    connect(switchPlayerButton1, SIGNAL(clicked()), this, SLOT(onSwitchPlayerButtonClicked()));
    connect(switchPlayerButton2, SIGNAL(clicked()), this, SLOT(onSwitchPlayerButtonClicked()));
    connect(stopGameButton, &QPushButton::clicked, this, &MainWindow::onStopGameButtonClicked);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(player1ProgressBar, 0, 0);
    layout->addWidget(player2ProgressBar, 0, 1);
    layout->addWidget(switchPlayerButton1, 1, 0);
    layout->addWidget(switchPlayerButton2, 1, 1);
    layout->addWidget(gameInfoLabel, 2, 0, 1, 2);
    layout->addWidget(startGameButton, 3, 0, 1, 1);
    layout->addWidget(stopGameButton, 3, 1, 1, 1);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeout()
{
    currentGameTime--;

    if (currentGameTime >= 0) {
        if (currentPlayer == 1) {
            player1Time = currentGameTime;
            player1ProgressBar->setValue((static_cast<double>(currentGameTime) / initialGameTime) * 100);
        } else {
            player2Time = currentGameTime;
            player2ProgressBar->setValue((static_cast<double>(currentGameTime) / initialGameTime) * 100);
        }

        updateProgressBar();
    } else {
        onSwitchPlayerButtonClicked();
    }
}

void MainWindow::updateProgressBar()
{

    player1ProgressBar->setValue(player1Time);
    player2ProgressBar->setValue(player2Time);
}

void MainWindow::setGameInfoText(const QString& text, short fontSize)
{

    gameInfoLabel->setText(text);
    gameInfoLabel->setFont(QFont("Arial", fontSize));
}

void MainWindow::onStartGameButtonClicked()
{
    QGridLayout *layout = qobject_cast<QGridLayout*>(centralWidget()->layout());

    if (layout) {
        QPushButton *button120Sec = new QPushButton("120 Seconds", this);
        QPushButton *button5Min = new QPushButton("5 Minutes", this);

        layout->addWidget(button120Sec);
        layout->addWidget(button5Min);

        connect(button120Sec, &QPushButton::clicked, [&]() {
            startGame(120);
        });

        connect(button5Min, &QPushButton::clicked, [&]() {
            startGame(300);
        });


    }
}
void MainWindow::onStopGameButtonClicked()
{
    pQTimer->stop();
    setGameInfoText("Game Stopped. Select time and press start the game.", 12);
    int selectedGameTime = QInputDialog::getInt(this, "Select Game Time", "Select playtime in seconds:", 120, 1, 600, 1);

    startGame(selectedGameTime);
}
void MainWindow::startGame(int selectedGameTime)
{
    setGameInfoText("Select playtime and press start the game",12);
    initialGameTime = selectedGameTime;
    currentGameTime = initialGameTime;
    player1Time = initialGameTime;
    player2Time = initialGameTime;
    gameTime = initialGameTime;
    currentPlayer = 1;

    player1ProgressBar->setValue(100);
    player2ProgressBar->setValue(100);

    updateProgressBar();
    setGameInfoText("Game ongoing", 12);

    pQTimer->start(1000);
}
void MainWindow::onSwitchPlayerButtonClicked()
{
    currentGameTime = initialGameTime;

    if (currentPlayer == 1) {
        player1ProgressBar->setEnabled(false);
        player2ProgressBar->setEnabled(true);
        currentPlayer = 2;
        setGameInfoText("Game ongoing", 12);
    } else {
        player1ProgressBar->setEnabled(true);
        player2ProgressBar->setEnabled(false);
        currentPlayer = 1;
        setGameInfoText("Game ongoing", 12);
    }

    if (player1Time <= 0 || player2Time <= 0) {
        pQTimer->stop();

        QString winner = (player1Time <= 0) ? "Player 2" : "Player 1";
        QMessageBox::information(this, "Game Over", winner + " wins!");


        int selectedGameTime = QInputDialog::getInt(this, "Select Game Time",
                                                    "Select playtime in seconds:", 120, 1, 600, 1);
        startGame(selectedGameTime);
    }
}
