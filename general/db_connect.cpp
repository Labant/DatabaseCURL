#include "db_connect.h"
#include "qt_mode_include.h"
#include <QDebug>


Db_Connect::Db_Connect()
{
	Init();
}

Db_Connect::~Db_Connect()
{
}

QSqlDatabase& Db_Connect::OpenDB()
{
	OpenDbPath();
	return OpenDb();
}

void Db_Connect::OnOpenDb()
{
	qDebug() << STATE->state_db_is_should_open.load();

	if (!STATE->state_db_is_should_open.load())
	{
		qDebug() << STATE->state_db_is_should_open.load();
		return;
	}

	sql_database_ = OpenDB();
	//COMMON->InsertQObjectPtr("sql_database_", dynamic_cast<QObject*>(&sql_database_));

	STATE->db_state_info.store(State_Machine::Opened);
	STATE->state_db_is_should_open.store(false);

	sql_model_query_ptr_->setQuery(QString("SELECT tbl_name as %1 FROM sqlite_master ").arg(QStringLiteral("±íÃû")), sql_database_);
	
	QSqlRecord record = sql_model_query_ptr_->record();
	for (int i = 0; i < record.count();++i)
	{
		sql_model_query_ptr_->setHeaderData(i, Qt::Vertical, record.fieldName(i));
	}
	//sql_model_query_ptr_->setHeaderData(0, Qt::Horizontal, QStringLiteral("keyId"));
	//sql_model_query_ptr_->setHeaderData(1, Qt::Horizontal, QStringLiteral("StringContent"));
	//sql_model_query_ptr_->setHeaderData(2, Qt::Horizontal, QStringLiteral("ShortName"));

	qobject_cast<Table_Content_And_Operator_Widget*>(COMMON->Get("open_or_close_center_widget_ptr_"))->SetTableMode(sql_model_query_ptr_);
	qobject_cast<Table_Content_And_Operator_Widget*>(COMMON->Get("open_or_close_center_widget_ptr_"))->show();

#if 0
		//!QSqlTableModel start
	sql_table_model->setTable("sqlite_master");
	sql_table_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	//sql_table_model->setFilter("name=\'TTextContent\'");
	sql_table_model->select();
	qDebug() << sql_table_model->setHeaderData(0, Qt::Vertical, QStringLiteral("tbl_name"));
	qDebug() << "tbl_name_index£º" << sql_table_model->fieldIndex("tbl_name");

	qobject_cast<Table_Content_And_Operator_Widget*>(COMMON->Get("open_or_close_center_widget_ptr_"))->SetTableMode(sql_table_model);
	qobject_cast<QTableView*>(COMMON->Get("table_view_ptr_"))->hideColumn(0);
	qobject_cast<QTableView*>(COMMON->Get("table_view_ptr_"))->hideColumn(2);
	qobject_cast<QTableView*>(COMMON->Get("table_view_ptr_"))->hideColumn(3);
	qobject_cast<QTableView*>(COMMON->Get("table_view_ptr_"))->hideColumn(4);
	qobject_cast<Table_Content_And_Operator_Widget*>(COMMON->Get("open_or_close_center_widget_ptr_"))->show();
	//!QSqlTableModel start
#endif


	//QSqlQuery query;
	//std::vector<db_data> vec_data;

	//query.prepare("SELECT * FROM TTextContent");
	//query.exec();
	//QSqlRecord record = query.record();
	//qDebug() << record.fieldName(0) << record.fieldName(1) << record.fieldName(2);

	//for (; query.next();)
	//{
	//	db_data data;
	//	data.keyId = query.value("keyId").toInt();
	//	data.StringContent = query.value("StringContent").toString();
	//	data.ShortName = query.value("ShortName").toString();

	//	vec_data.emplace_back(data);
	//}

	//if (!vec_data.empty())
	//{
	//	for (int i = 0; i < vec_data.size(); ++i)
	//	{
	//		qDebug() << vec_data[i].keyId << " :"  \
	//			<< vec_data[i].StringContent << " :" \
	//			<< vec_data[i].ShortName;
	//	}
	//}
}

void Db_Connect::OnCloseDb()
{
	sql_database_.close();
	STATE->db_state_info.store(State_Machine::Closed);
	STATE->state_db_is_should_open.store(true);
}

QList<QVariant>& Db_Connect::OnGetDbAllTableName()
{
	table_name_ls.clear();

	QSqlQuery query;
	query.prepare("SELECT tbl_name FROM sqlite_master");
	query.exec();

	for (; query.next();)
	{
		//qDebug() << query.value("tbl_name");
		table_name_ls.push_back(query.value("tbl_name"));
	}
	return table_name_ls;
}

void Db_Connect::OnCurrentTextChanged(QString table_name__)
{
	sql_model_query_of_serach_ptr_->setQuery(QString("SELECT * FROM %1").arg(table_name__), sql_database_);
	QSqlRecord record = sql_model_query_ptr_->record();
	for (int i = 0; i < record.count(); ++i)
	{
		sql_model_query_of_serach_ptr_->setHeaderData(i, Qt::Vertical, record.fieldName(i));
	}
	qobject_cast<Table_Content_And_Operator_Widget*>(COMMON->Get("serach_center_widget_ptr_"))->SetTableMode(sql_model_query_of_serach_ptr_);
}

void Db_Connect::OpenDbPath()
{

	qDebug() << __FUNCTION__ << "@file_path_str_:" << qobject_cast<Menu_Bar*>(COMMON->Get("menu_bar_ptr_"))->file_path_str_;
}

QSqlDatabase& Db_Connect::OpenDb()
{
	STATE->bool_is_clearn_db_connect_name.store(true);
	emit this->FileNameFromDialog();

	if (qobject_cast<Menu_Bar*>(COMMON->Get("menu_bar_ptr_"))->file_path_str_.isEmpty())
	{
		qDebug() << qobject_cast<Menu_Bar*>(COMMON->Get("menu_bar_ptr_"))->file_path_str_;
	}

	sql_database_.setDatabaseName(qobject_cast<Menu_Bar*>(COMMON->Get("menu_bar_ptr_"))->file_path_str_);
	
	if (sql_database_.open())
	{
		STATE->db_state_info = State_Machine::Opened;
		STATE->state_db_is_should_open = false;  //not opened
	}
	else
	{
		STATE->state_db_is_should_open = true;  //can open db
		qDebug() << "ERROR:" << sql_database_.lastError() << __FUNCDNAME__;
	}

	return sql_database_;

}

void Db_Connect::InitMembers()
{
	sql_database_ = QSqlDatabase::addDatabase("QSQLITE");
	sql_model_query_ptr_ = new QSqlQueryModel;
	COMMON->InsertQObjectPtr("sql_model_query_ptr_", sql_model_query_ptr_);

	sql_model_query_of_serach_ptr_ = new QSqlQueryModel;
	COMMON->InsertQObjectPtr("sql_model_query_of_serach_ptr_", sql_model_query_of_serach_ptr_);
	
	
	sql_table_model = new QSqlTableModel;
	COMMON->InsertQObjectPtr("sql_table_model", sql_table_model);

}

void Db_Connect::InitConnects()
{
}
