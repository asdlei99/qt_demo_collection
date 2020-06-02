/*
null: 表示为 null
boolean: 表示为 true 或 false
number: 一般的浮点数表示方式，在下一单元详细说明
string: 表示为 "..."
array: 表示为 [ ... ]
object: 表示为 { ... }

*/
#include <QCoreApplication>
#include <qdebug.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qfile.h>
#include <QMetaEnum>
#include <qdir.h>
#include <qjsonvalue.h>
#include <QJsonArray>

enum JsonType{
    Json,
    Binary
};

void jsonWriter(const JsonType mode = JsonType::Json);
void jsonReader(const JsonType mode = JsonType::Json);

void manJsonReader(const JsonType mode = JsonType::Json);
void manJsonWriter(const JsonType mode = JsonType::Json);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<"json pro demo.";

    //    jsonWriter("Json");
    //    jsonReader(JsonType::Json);

//    manJsonReader(JsonType::Json);
    manJsonWriter(JsonType::Json);

    return a.exec();
}

void jsonWriter(const JsonType mode){
    QJsonDocument jsonDoc;

    QJsonObject jsonObj;
    jsonObj["player"] = "1231";
    jsonObj["levels"] = "level-12";

    jsonDoc.setObject(jsonObj);

    QString fileName = (mode == JsonType::Json)?"save.json":"save.dat";
    QFile savefile(fileName);
    if(false == savefile.open(QIODevice::WriteOnly)){
        qWarning("cannot open save file.");
        return;
    }

    savefile.write(mode == JsonType::Json?jsonDoc.toJson():jsonDoc.toBinaryData());

    savefile.close();
}
void jsonReader(const JsonType mode){
#if 0
    QString currentPath = QDir::currentPath();
    qDebug()<<"currentPath:"<<currentPath;
    if(mode == "Json"){
        currentPath += QString("\save.json");
    }
    else{
        currentPath += QString("\save.dat");
    }
    qDebug()<<"currentPath:"<<currentPath;

#endif
    QFile loadFile(mode == JsonType::Json?"save.json":"save.dat");
    if(false == loadFile.open(QIODevice::ReadOnly)){
        qDebug()<<"reader open failed."<<loadFile.errorString();
        return;
    }

    QByteArray data = loadFile.readAll();

    QJsonDocument JsonDoc(
                mode == JsonType::Json?
                    QJsonDocument::fromJson(data):
                    QJsonDocument::fromBinaryData(data));

    QJsonObject jsonObj = JsonDoc.object();
    qDebug()<<"keys:"<<jsonObj.keys();
    if(jsonObj.contains("player") && jsonObj["player"].isObject()){
        qDebug()<<"player:"<<jsonObj["player"].toString();
    }
    else{
        qDebug()<<"cannot find player.";
    }
}

void manJsonReader(const JsonType mode){
    QFile loadFile(mode == JsonType::Json?"man.json":"man.dat");
    if(false == loadFile.open(QIODevice::ReadOnly)){
        qDebug()<<"manJsonReader open failed.";
        return;
    }

    QByteArray ba = loadFile.readAll();
    if(ba.isEmpty()){
        qDebug()<<"ba is empty.";
        return;
    }else {
        qDebug()<<"ba.size:"<<ba.size();
    }

    QJsonDocument jsonDoc(mode == JsonType::Json?
                              QJsonDocument::fromJson(ba):
                              QJsonDocument::fromBinaryData(ba));

    if(jsonDoc.isNull()){
        qDebug()<<"doc is null.";
        return;
    }
    else if(jsonDoc.isEmpty()){
        qDebug()<<"doc is empty.";
        return;
    }else if(jsonDoc.isObject()){
        qDebug()<<"doc is object.";
        QJsonObject jsonObj = jsonDoc.object();
#if 0
        qDebug()<<"keys:"<<jsonObj.keys();
        for(const auto item:jsonObj.keys()){
            QJsonValue jsonValue = jsonObj.value(item);

            qDebug()<<"jsonValue type:"
                   <<item<<"|"<<jsonValue.type();
        }
#endif
        for(const auto item:jsonObj.keys()){
            if(item == "title"){
                QJsonValue titileJValue= jsonObj.value(item);
                if(titileJValue.isString()){
                    qDebug()<<"title:"<<titileJValue.toString();
                }
            }else if(item == "subtitle"){
                QJsonValue subtitleJValue= jsonObj.value(item);
                if(subtitleJValue.isString()){
                    qDebug()<<"title:"<<subtitleJValue.toString();
                }
            }else if(item == "author"){
                QJsonValue authorJValue = jsonObj.value(item);
                if(authorJValue.isArray()){
                    QJsonArray authorArray = authorJValue.toArray();
                    for(const auto &item:authorArray){
                        qDebug()<<"author:"<<item.toString();
                    }
                }
            }else if(item == "publisher"){
                QJsonObject publisherJsonObj = jsonObj.value(item).toObject();
                qDebug()<<"publisher:"<<publisherJsonObj.value("Company").toString();
                qDebug()<<"publisher:"<<publisherJsonObj.value("Country").toString();
            }

        }
        return;
    }else if(jsonDoc.isArray()){
        qDebug()<<"doc is array";
        return;
    }
}
void manJsonWriter(const JsonType mode){
    qDebug()<<"manJsonWriter";

    QJsonObject jsonObj;
    jsonObj["title"] = "Design Patterns";
    jsonObj["year"] = 2009;

    QJsonArray authorJsonArray;
    authorJsonArray.append("Erich Gamma");
    authorJsonArray.append("Erich Gamma2");
    authorJsonArray.append("Erich Gamma3");

    QJsonObject publisherJsonObj;
    publisherJsonObj.insert("Company",QJsonValue("Pearson Education"));
    publisherJsonObj.insert("Country",QJsonValue("India"));

    jsonObj.insert("author",authorJsonArray);
    jsonObj.insert("publisher",publisherJsonObj);
    //写文件
    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObj);

    QString fileName = (mode == JsonType::Json)?"man2.json":"man2.dat";
    QFile savefile(fileName);
    if(false == savefile.open(QIODevice::WriteOnly)){
        qWarning("cannot open save file.");
        return;
    }

    savefile.write(mode == JsonType::Json?jsonDoc.toJson():jsonDoc.toBinaryData());

    savefile.close();
}





































