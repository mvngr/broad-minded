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
    QString rowName = "row" + QString::number(subjectId);
    QString colName = "q" + QString::number(questionId);
    if(data_.find(rowName) != data_.end()){
        QVariantMap row = data_[rowName].toMap();
        if(row.find(colName) != row.end()){
            QVariantMap col = row[colName].toMap();
            questionType = stringToQuestionType[col["type"].toString()];
            cost = col["cost"].toInt();
            return col["text"].toString();
        }
    }
    return "ERROR";
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
