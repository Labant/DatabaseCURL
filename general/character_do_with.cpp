#include "character_do_with.h"
#include <algorithm>
#include <QDebug>
QStringList* Character_Do_With::string_list_from_2_to_ptr_ = new QStringList;

//以普通函数的方式实现自定义排序规则
bool mycomp(EnteryStruceData i, EnteryStruceData j) {
	return (i.index_tem_table_key_id < j.index_tem_table_key_id);
}

Character_Do_With::Character_Do_With()
{
}

Character_Do_With::~Character_Do_With()
{
	delete string_list_from_2_to_ptr_;
	string_list_from_2_to_ptr_ = nullptr;
}

QString Character_Do_With::GetFrom2ToPlace(QString str_origin_)
{
	string_list_from_2_to_ptr_->clear();
	//qDebug() << "str_origin_:" << str_origin_;
	*string_list_from_2_to_ptr_ = str_origin_.split("#");
	QStringList tem_string_list;
	tem_string_list.clear();
	for (QString xx : *string_list_from_2_to_ptr_)
	{
		tem_string_list.append(xx.split(","));
		//qDebug() << "xx:" << xx;
	}
	if (tem_string_list.isEmpty() || (3 > tem_string_list.size()))
		return QString();
	//qDebug() << " tem_string_list.at(0):" << tem_string_list.at(0) << "tem_string_list.size():" << tem_string_list.size();
	//qDebug() <<" tem_string_list.at(2):" << tem_string_list.at(2);
	return QString(tem_string_list.at(0) +"-" + tem_string_list.at(2));
}

QStringList Character_Do_With::Split1(QString str_)
{
	return str_.split("#");
}

QPair<QString, QString> Character_Do_With::Splice1(QList<EnteryStruceData>& struct_list_, 
	int index_connect_table_keyid)
{
	QString target_str_id_string; target_str_id_string.clear();
	QString target_str_short_name_string; target_str_short_name_string.clear();
	std::sort(struct_list_.begin(), struct_list_.end(), mycomp);

	for (EnteryStruceData& data : struct_list_)
	{
		if (data.index_key_id == index_connect_table_keyid)
		{
			target_str_id_string.append(data.IdString);
			target_str_short_name_string.append(data.ShortNameString);
			target_str_id_string.append("#");
			target_str_short_name_string.append("#");
			qDebug() << data.index_tem_table_key_id << " " << data.IdString <<" "<< data.ShortNameString;
		}
	}

	QPair<QString, QString> tmep_pair_ = QPair<QString, QString>(target_str_id_string.remove(target_str_id_string.size() - 1, 1),
		target_str_short_name_string.remove(target_str_short_name_string.size() - 1, 1));

	qDebug() << "target_str_id_string_origin:" << tmep_pair_.first;
	qDebug() << "target_str_short_name_string_origin:" << tmep_pair_.second;
	return tmep_pair_;
}
