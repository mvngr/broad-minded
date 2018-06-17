#ifndef TEAMS_H
#define TEAMS_H

#include <squad.h>

#include <QList>

class Teams
{
public:
    Teams();
    Teams(QList<Squad> list);

    void addTeam(Squad squad);
//    Squad *nextTurn();
//    Squad *randomTurn();

//    Squad *getTurnTeam();

private:
    QList<Squad> list_;
    int turn_;
};

#endif // TEAMS_H
