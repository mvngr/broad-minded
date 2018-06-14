#ifndef GAMEREADER_H
#define GAMEREADER_H

#include <QDebug>
#include <QString>
#include <QVariantMap>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QList>
#include <QColor>

#define ROW_PREFIX "row"
#define COL_PREFIX "q"

class GameReader
{
public:
    GameReader();

    enum class QuestionTypes{question, cat};
    QMap<QString, QuestionTypes> stringToQuestionType;

    QString DEFAULT_FILE = "game1.json";

    QString getQuestion(int subjectId, int questionId, QuestionTypes &questionType, int &cost);
    QList<QList<int> *> *getCostArray();
    QList<QPair<QString, QColor> > *getTitles();
    bool readData();
    bool readData(QString path);
    QString questionTypesToString(QuestionTypes questionType);

private:
    bool gameAlreadyRead_;
    QVariantMap data_;

};

#endif // GAMEREADER_H
