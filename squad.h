#ifndef SQUAD_H
#define SQUAD_H

#include <QString>
#include <QColor>
#include <QRandomGenerator>

class Squad
{
public:
    Squad();
    Squad(int index);
    Squad(QString name);
    Squad(QString name, QColor color);

    QString getName();
    int getScore();
    QColor getColor();

    void addToScore(int number);

private:
    int score_;
    QString name_;
    QColor color_;

    QColor makeColor();
};

#endif // SQUAD_H
