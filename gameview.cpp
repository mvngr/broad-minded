#include "gameview.h"
#include "ui_gameview.h"

GameView::GameView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameView)
{
    ui->setupUi(this);

    gr_ = new GameReader();
    GameReader::QuestionTypes qt;
    int cost;
    QString text = gr_->getQuestion(0, 0, qt, cost);
    qDebug() << cost << gr_->questionTypesToString(qt) << text;
    if(!gr_->readData()){
        QMessageBox::warning(this, "Ошибка чтения", "Упс..\nПроизошла ошибка при чтении из \"" + gr_->DEFAULT_FILE + "\".");
    }
}

GameView::~GameView()
{
    delete ui;
}
