#include "squad.h"

Squad::Squad()
{
    name_ = "Команда " + QString::number(QRandomGenerator::global()->generate() % 1000);
    score_ = 0;
    color_ = makeColor();
}
Squad::Squad(int index){
    name_ = "Команда " + QString::number(index);
    score_ = 0;
    color_ = makeColor();
}
Squad::Squad(QString name){
    name_ = name;
    score_ = 0;
    color_ = makeColor();
}
Squad::Squad(QString name, QColor color){
    name_ = name;
    score_ = 0;
    color_ = color;
}
QColor Squad::makeColor(){
    return QColor(QRandomGenerator::global()->generate() % 128 + 128, QRandomGenerator::global()->generate() % 128 + 128, QRandomGenerator::global()->generate() % 128 + 128);
}
QString Squad::getName(){
    return name_;
}
int Squad::getScore(){
    return score_;
}
QColor Squad::getColor(){
    return color_;
}
void Squad::addToScore(int number){
    score_ += number;
    return;
}
