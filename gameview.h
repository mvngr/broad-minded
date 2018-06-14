#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>

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
    virtual void resizeEvent(QResizeEvent *e) override;
    QList<QList<QWidget *> *> *createField(QGridLayout *l);
    QString toStyleSheet(QColor color);

    Ui::GameView *ui;
    GameReader *gr_;
};

#endif // GAMEVIEW_H
