#include "edit_query_model.h"
#include "character_do_with.h"
#include <QDebug>

Edit_Query_Model::Edit_Query_Model()
{
}

Edit_Query_Model::~Edit_Query_Model()
{
}

QVariant Edit_Query_Model::data(const QModelIndex& index, int role) const
{
	if (variant_list_.isEmpty())return QVariant("NAN");
	//qDebug() << variant_list_.at(index.row());
	//return Character_Do_With::GetFrom2ToPlace(variant_list_.at(index.row()).toString());
	return variant_list_.at(index.row()).toString();
	//qDebug() << index.row() << ","<< index.column();

	//static int i = 0;
	//QString xx = i > 0 ? QString::number(index.row() + (1)) : QString::number(index.row());
	//if (i > 0)i = 0;
	//if (i <  1)i = 1;
	//return xx;

}

bool Edit_Query_Model::setData(const QModelIndex& index, const QVariant& value, int role)
{
	//if (index.column() < 1)
	//	return false;
	return true;
}

Qt::ItemFlags Edit_Query_Model::flags(const QModelIndex& index) const
{
	// 1. 获取当前单位格的编辑状态
	Qt::ItemFlags flag = QSqlQueryModel::flags(index);
	// 2.给现有的标志增加一个可编辑的标志
	if (index.column() == 1)
		flag = flag | Qt::ItemIsEditable; //给它设置一个可编辑的状态
	return flag;
}

void Edit_Query_Model::SetConfig(const QSqlQuery& query, QString str_)
{
	cow_name_.clear();
	cow_name_ = str_;
	if (cow_name_.isEmpty())return;
	variant_list_.clear();
	QSqlQuery query_ = query;
	query_.exec();
	//qDebug() << query_.record().count();
	map_.clear();
	for (; query_.next();)
	{
		map_.emplace(query_.value(cow_name_).toString(),
			query_.value("keyId").toInt());
		variant_list_.append(query_.value(cow_name_));
	}
}

int Edit_Query_Model::GetKeyIdOfShortNameString(QString str__)
{
	//for (auto ptr_= map_.begin(); ptr_!= map_.end(); ptr_++)
	//{
	//	qDebug()<< (*ptr_).first <<"," << (*ptr_).second;
	//}

	auto tem_itor = map_.find(str__);
	if (tem_itor != map_.end())
	{
		return (*tem_itor).second;
	};
	return -1;
}
