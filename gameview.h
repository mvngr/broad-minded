#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>

#include <gamereader.h>

namespace Ui {
class GameView;
}

class GameView : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = 0);
    ~GameView();

private:
    Ui::GameView *ui;
    GameReader *gr_;
};

#endif // GAMEVIEW_H
