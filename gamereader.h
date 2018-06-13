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

class GameReader
{
public:
    GameReader();

    enum class QuestionTypes{question, cat};
    QMap<QString, QuestionTypes> stringToQuestionType;

    QString DEFAULT_FILE = "game1.json";

    QString getQuestion(int subjectId, int questionId, QuestionTypes &questionType, int &cost);
    bool readData();
    bool readData(QString path);
    QString questionTypesToString(QuestionTypes questionType);

private:
    bool gameAlreadyRead_;
    QVariantMap data_;

};

#endif // GAMEREADER_H
