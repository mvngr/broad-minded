#include "gamereader.h"

GameReader::GameReader()
{
    data_ = *new QVariantMap();
    gameAlreadyRead_ = false;
    stringToQuestionType.insert("q", QuestionTypes::question);
    stringToQuestionType.insert("c", QuestionTypes::cat);
}
bool GameReader::readData(){
    return readData(DEFAULT_FILE);
}
bool GameReader::readData(QString path){

    QFile fileObj(path);
    if (!fileObj.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open " << path;
        return false;
    }

    QTextStream fileText(&fileObj);
    QString jsonString = fileText.readAll();
    fileObj.close();
    QByteArray jsonBytes = jsonString.toLocal8Bit();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonBytes);
    if (jsonDoc.isNull()){
        qDebug() << "Failed to create JSON doc.";
        return false;
    }
    if (!jsonDoc.isObject()){
        qDebug() << "JSON is not an object.";
        return false;
    }
    QJsonObject jsonObj = jsonDoc.object();
    if(jsonObj.isEmpty()){
        qDebug()<<"JSON object is empty.";
        return false;
    }
    data_ = jsonObj.toVariantMap();
    gameAlreadyRead_ = true;
    return true;
}
QString GameReader::getQuestion(int subjectId, int questionId, QuestionTypes &questionType, int &cost){
    if(!gameAlreadyRead_ && !readData())
        return "ERROR";
    QString rowName = ROW_PREFIX + QString::number(subjectId);
    QString colName = COL_PREFIX + QString::number(questionId);
    if(data_.contains(rowName)){
        QVariantMap row = data_[rowName].toMap();
        if(row.contains(colName)){
            QVariantMap col = row[colName].toMap();
            questionType = stringToQuestionType[col["type"].toString()];
            cost = col["cost"].toInt();
            return col["text"].toString();
        }
    }
    return "ERROR";
}
QList<QList<int> *> *GameReader::getCostArray(){
    QList<QList<int> *> *res = new QList<QList<int> *>;
    if(!gameAlreadyRead_ && !readData())
        return res;
    size_t i = 0;
    while(data_.contains(ROW_PREFIX + QString::number(i))){
        res->push_back(new QList<int>);
        QVariantMap row = data_[ROW_PREFIX + QString::number(i)].toMap();
        size_t j = 0;
        while(row.contains(COL_PREFIX + QString::number(j))){
            QVariantMap element = row[COL_PREFIX + QString::number(j)].toMap();
            res->at(i)->push_back(element.contains("cost") ? element["cost"].toInt() : 0);
            j++;
        }
        i++;
    }
    return res;
}
QList<QPair<QString, QColor>> *GameReader::getTitles(){
    QList<QPair<QString, QColor>> *res = new QList<QPair<QString, QColor>>;
    if(!gameAlreadyRead_ && !readData())
        return res;
    size_t i = 0;
    while(data_.contains(ROW_PREFIX + QString::number(i))){
        QVariantMap row = data_[ROW_PREFIX + QString::number(i)].toMap();
        QString subj = row["subject"].toString() + "\n" + QString::number(row["time"].toInt()) + " сек";
        QJsonArray jAcolor = row["color"].toJsonArray();
        QColor color;
        for(int i = 0; i < jAcolor.size(); i++)
            switch (i) {
            case 0: color.setRed(jAcolor[i].toInt()); break;
            case 1: color.setGreen(jAcolor[i].toInt()); break;
            case 2: color.setBlue(jAcolor[i].toInt()); break;
            default: break;
            }
        res->push_back(QPair<QString, QColor>(subj, color));
        i++;
    }
    return res;
}
QString GameReader::questionTypesToString(QuestionTypes questionType){
    switch (questionType) {
    case QuestionTypes::question:
        return "q";
    case QuestionTypes::cat:
        return "c";
    default:
        return "ERROR";
    }
}
