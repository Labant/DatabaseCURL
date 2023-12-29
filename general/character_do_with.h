#pragma once
#include <QString>
#include <QStringList>
#include "common.h"

class Character_Do_With
{
public:
	Character_Do_With();
	~Character_Do_With();

	static QString GetFrom2ToPlace(QString);
	static QStringList Split1(QString);//#ºÅ·Ö¸î
	static QPair<QString, QString> Splice1(QList<EnteryStruceData>&,int index_connect_table_keyid);//#ºÅÆ´½Ó
private:
	static QStringList* string_list_from_2_to_ptr_;
};

