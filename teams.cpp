#include "teams.h"

Teams::Teams()
{
    list_ = *new QList<Squad>;
    turn_ = NULL;
}
Teams::Teams(QList<Squad> list){
    list_ = list;
    turn_ = list.size() > 0 ? 0 : NULL;
}
void Teams::addTeam(Squad squad){
    list_.push_back(squad);
    return;
}
//Squad *Teams::nextTurn(){
//    turn_ = turn_ < list_.size() - 1 ? turn_ + 1 : 0;
//    return &list_[turn_];
//}
