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