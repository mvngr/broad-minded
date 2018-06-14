#include "gameview.h"
#include "ui_gameview.h"

GameView::GameView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameView)
{
    ui->setupUi(this);

    gr_ = new GameReader();
    if(!gr_->readData())
        QMessageBox::warning(this, "Ошибка чтения", "Упс..\nПроизошла ошибка при чтении из \"" + gr_->DEFAULT_FILE + "\".");
    createField(ui->gridLayout_2);
}

GameView::~GameView()
{
    delete ui;
}

void GameView::resizeEvent(QResizeEvent *e){
    if(e->size().width() <= 900)
        ui->centralWidget->setStyleSheet("font-size: 11pt;");
    if(e->size().width() > 900 && e->size().width() <= 1200)
        ui->centralWidget->setStyleSheet("font-size: 13pt;");
    if(e->size().width()>1200)
        ui->centralWidget->setStyleSheet("font-size: 15pt;");
}

QList<QList<QWidget *> *> *GameView::createField(QGridLayout *l){
    QList<QPair<QString, QColor>> *themes = gr_->getTitles();
    QList<QList<int> *> *costs = gr_->getCostArray();

    QList<QList<QWidget *> *> *widgetRefs = new QList<QList<QWidget *> *>;
    for(int i = 0; i < themes->size(); i++){
        widgetRefs->push_back(new QList<QWidget *>);

        QLabel *label = new QLabel(this);
        label->setText(themes->at(i).first);
        label->setStyleSheet(toStyleSheet(themes->at(i).second));
        label->setAlignment(Qt::AlignCenter);
        label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        widgetRefs->last()->push_back(label);
        l->addWidget(label, i, 0);
    }
    for(int i = 0; i < costs->size(); i++){
        if(widgetRefs->size() < costs->size())
            widgetRefs->push_back(new QList<QWidget *>);
        for(int j = 0; j < costs->at(i)->size(); j++){
            QPushButton *pb = new QPushButton(this);
            pb->setText(QString::number(costs->at(i)->at(j)));
            pb->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            widgetRefs->at(i)->push_back(pb);
            l->addWidget(pb, i, j+1);
        }
    }
    return widgetRefs;
}

QString GameView::toStyleSheet(QColor color){
    QString res = "QLabel { background-color: rgb(";
    res += QString::number(color.red());
    res += ", ";
    res += QString::number(color.green());
    res += ", ";
    res += QString::number(color.blue());
    res += "); }";
    return res;
}
