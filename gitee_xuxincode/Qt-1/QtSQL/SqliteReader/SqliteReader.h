/*!
 * \file SqliteReader.h
 *
 * \author lesliefish
 * 
 */
#pragma once

#include <QObject>
#include <QVariant>

class QSqlDatabase;
class SqliteReader
{
public:
	static std::map<QString, std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>> read(const QString& name);
				// 	 ����	  //������vector	 //ÿһ������ÿһ�е���Ϣvector   ����   ����      ֵ
	static QSqlDatabase s_db;
};