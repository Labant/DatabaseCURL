#pragma once
#ifndef COMMON_H
#define COMMOD_H

#include <map>
#include <string>
#include <QObject>

using std::string;
using std::map;

extern string db_select;

#define COMMON Common::GetInstance()

typedef struct EnteryMapStruce
{
	int category;  //text¡¢audio
	int index_key_id;      //connect keyId
	int index_tem_table_key_id;      //temp table keyId
	QString IdString;
	QString ShortNameString;
	int count = 0;
	QString target_str_id_string = "";
	QString target_str_short_name_string = "";
}EnteryStruceData;

typedef struct ContentMapStruce
{
	int keyId;
	QString ShortName;
	QString color = "FF0000";
	QString caption = QString::fromLocal8Bit("ÎÞ");
}ContentStruceData;

class Common
{
private:
	Common();
	~Common();

public:
	bool InsertQObjectPtr(string&& key_,QObject* ptr_);
	QObject* Get(string str_name_ptr);

	static Common* GetInstance();

class Destory 
{
public:
	Destory() {};
	~Destory() {
		if (nullptr != instance)
		{
			delete instance;
			instance = nullptr;
		}
	};

};

private:
	static Common* instance;
	map<string,QObject*> map_;
};

#endif  //!COMMOD_H