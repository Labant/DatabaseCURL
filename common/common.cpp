#include "common.h"
#include <QDebug>

string db_select = "Db_Select";

Common* Common::instance = GetInstance();
static Common::Destory destory;

Common::Common()
{
}
Common::~Common()
{
}

Common* Common::GetInstance()
{
	if (instance != nullptr)
	{
		return instance;
	}
	else
	{
		instance = new Common();
	}
	return instance;
}

bool Common::InsertQObjectPtr(string&& key_, QObject* ptr_)
{
	if (map_.find(key_) == map_.end())
	{
		map_.emplace(key_, ptr_);
		return true;
	}
	return false;
}

QObject* Common::Get(string str_name_ptr)
{
	return (map_.find(str_name_ptr))->second;
}
