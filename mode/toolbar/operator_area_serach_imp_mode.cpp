#include "operator_area_serach_imp_mode.h"
#include "qt_layout_include.h"
#include "db_connect.h"
#include <QSqlQueryModel>
#include <QDebug>

Operator_Area_Serach_Imp_Mode::Operator_Area_Serach_Imp_Mode()
{
	Init();
}

Operator_Area_Serach_Imp_Mode::~Operator_Area_Serach_Imp_Mode()
{
}

void Operator_Area_Serach_Imp_Mode::OnGetAllTableName2ComBox()
{
	//QSqlQueryModel query_model_;
	QStringList tem_data;
	QList<QVariant> tem =  qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_"))->OnGetDbAllTableName();
	for (int i = 0 ;i < tem.size();++i)
	{
		//qDebug() << tem.at(i);
		tem_data.push_back(tem.at(i).toString());
	}
	qobject_cast<QComboBox*>(COMMON->Get("combo_box_operator_area_serach_imp_"))->clear();
	qobject_cast<QComboBox*>(COMMON->Get("combo_box_operator_area_serach_imp_"))->addItems(tem_data);
}

void Operator_Area_Serach_Imp_Mode::InitMembers()
{
}

void Operator_Area_Serach_Imp_Mode::InitConnects()
{
}
