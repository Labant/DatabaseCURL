#include "db_connect.h"
#include "qt_mode_include.h"
#include <QDebug>
#include "character_do_with.h"

Db_Connect::Db_Connect()
{
	Init();
}

Db_Connect::~Db_Connect()
{
	//if (sql_database_ptr_ != nullptr || sql_database_ptr_->isOpen())
	//{
	//	sql_database_ptr_->close();
	//	delete sql_database_ptr_;
	//	sql_database_ptr_ = nullptr;
	//}
}

QSqlDatabase& Db_Connect::OpenDB()
{
	OpenDbPath();
	return OpenDb();
}

void Db_Connect::OnOpenDb()
{
	//qDebug() << STATE->state_db_is_should_open.load();

	if (!STATE->state_db_is_should_open.load())
	{
		qDebug() << STATE->state_db_is_should_open.load();
		return;
	}

	//sql_database_ptr_ = &OpenDB();
	sql_database_ = OpenDB();
	//COMMON->InsertQObjectPtr("sql_database_", dynamic_cast<QObject*>(&sql_database_));

	STATE->db_state_info.store(State_Machine::Opened);
	STATE->state_db_is_should_open.store(false);

	//sql_model_query_ptr_->setQuery(QString("SELECT tbl_name as %1 FROM sqlite_master ").arg(QStringLiteral("表名")), *sql_database_ptr_);
	sql_model_query_ptr_->setQuery(QString("SELECT tbl_name as %1 FROM sqlite_master ").arg(QStringLiteral("表名")), sql_database_);
	
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
	qDebug() << "tbl_name_index：" << sql_table_model->fieldIndex("tbl_name");

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
	//sql_database_ptr_->close();
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
	//sql_model_query_of_serach_ptr_->setQuery(QString("SELECT * FROM %1").arg(table_name__), *sql_database_ptr_);
	sql_model_query_of_serach_ptr_->setQuery(QString("SELECT * FROM %1").arg(table_name__), sql_database_);
	QSqlRecord record = sql_model_query_ptr_->record();
	for (int i = 0; i < record.count(); ++i)
	{
		sql_model_query_of_serach_ptr_->setHeaderData(i, Qt::Vertical, record.fieldName(i));
	}
	qobject_cast<Table_Content_And_Operator_Widget*>(COMMON->Get("serach_center_widget_ptr_"))->SetTableMode(sql_model_query_of_serach_ptr_);
}

void Db_Connect::OnCurrentTextChangedOfInsert()
{
	//just for TReportTextConnect and TReportAudioConnect
	QStringList str_list;
	str_list.append("TReportTextConnect");
	str_list.append("TReportAudioConnect");
	qobject_cast<QComboBox*>(COMMON->Get("opera_area_insert_combox_ptr_"))->clear();
	qobject_cast<QComboBox*>(COMMON->Get("opera_area_insert_combox_ptr_"))->addItems(str_list);
	STATE->table_category_state_info_of_insert_window.store(State_Machine::TextCategory);

	//init table
	OnCurrentTextChangedOfComboxOfInsert("TReportTextConnect");
}

//combox 
void Db_Connect::OnSetComboxValueOfInsert()
{
	//edit_query_model_ptr_->setQuery(QString("SELECT ShortNameString FROM TReportAudioConnect"), *sql_database_ptr_);
	edit_query_model_ptr_->setQuery(QString("SELECT ShortNameString FROM TReportAudioConnect"), sql_database_);
	QSqlRecord record = sql_model_query_ptr_->record();
	for (int i = 0; i < record.count(); ++i)
	{
		edit_query_model_ptr_->setHeaderData(i, Qt::Vertical, record.fieldName(i));
	}
	qobject_cast<Table_Content_And_Operator_Widget*>(COMMON->Get("serach_center_widget_ptr_"))->SetTableMode(sql_model_query_of_serach_ptr_);

}

//combox text state change
void Db_Connect::OnCurrentTextChangedOfComboxOfInsert(QString table_name__)
{
	if (table_name__.compare("TReportAudioConnect",Qt::CaseSensitive) == 0)
	{
		STATE->table_category_state_info_of_insert_window.store(State_Machine::AudioCategory);
	}
	else {
		STATE->table_category_state_info_of_insert_window.store(State_Machine::TextCategory);
	}

	//QSqlQuery sql_query(*sql_database_ptr_);
	QSqlQuery sql_query(sql_database_);
	sql_query.prepare(QString("SELECT keyId,ShortNameString FROM %1").arg(table_name__));
	sql_query.exec();

	
	for (;sql_query.next();)
	{
		//qDebug() << sql_query.value("ShortNameString");
		//Character_Do_With::GetFrom2ToPlace(sql_query.value("").toString());
	}

	edit_query_model_ptr_->SetConfig(sql_query,"ShortNameString");  //ShortNameString通用
	edit_query_model_ptr_->setQuery(sql_query);  //sys invoke

	QSqlRecord record = edit_query_model_ptr_->record();

	//edit_query_model_ptr_->setData();
	for (int i = 0; i < record.count(); ++i)
	{
		qDebug() << "record.field(i):" << record.field(i).name();
		edit_query_model_ptr_->setHeaderData(0, Qt::Vertical, QStringLiteral("区间ID"));
	}

	//set
	qobject_cast<Table_Content_And_Operator_Widget*>(COMMON->Get("insert_center_widget_ptr_"))->SetTableModeEntery(edit_query_model_ptr_);

}

void Db_Connect::OnGetTableViewContentsModels(int category, QString str_data_)
{
	QSqlQuery sql_query_1(sql_database_);
	QSqlQuery sql_query_2(sql_database_);
	sql_query_1.clear();
	sql_query_2.clear();
	
	int index = edit_query_model_ptr_->GetKeyIdOfShortNameString(str_data_); //获取keyId
	index_connect_table_keyid = index; 

	switch (STATE->table_category_state_info_of_insert_window)
	{
	case State_Machine::AudioCategory:
		sql_query_1.prepare(QString("select keyId as '%1',ShortName as '%2' from TAudioPath")
			.arg(QStringLiteral("音频ID")).arg(QStringLiteral("音频文件说明")));
		sql_query_1.exec();
		audio_map_data_add_infos_.clear();
		for (; sql_query_1.next();)
		{
			std::map < QString, ContentMapStruce> temp_map;
			ContentMapStruce cms;
			cms.keyId = sql_query_1.value(QStringLiteral("音频ID")).toInt();
			cms.ShortName = sql_query_1.value(QStringLiteral("音频文件说明")).toString();
			temp_map.emplace(sql_query_1.value(QStringLiteral("音频文件说明")).toString(), cms);
			audio_map_data_add_infos_.append(temp_map);
		}
		sql_query_model1.setQuery(sql_query_1);

		//摧毁临时表
		sql_query_2.clear();
		sql_query_2.prepare("DROP TABLE main.tempAudioTable");
		sql_query_2.exec();
		sql_query_2.clear();
		//创建临时表
		sql_query_2.prepare(
			"CREATE TABLE tempAudioTable(" \
			"keyId INT PRIMARY KEY     NOT NULL," \
			"StringCompont     TEXT    NOT NULL)" \
		);
		sql_query_2.exec();
		sql_query_2.clear();

		//查询原始表
		sql_query_2.prepare(QString("select IdString, ShortNameString as '%1' from TReportAudioConnect where keyId = %2")
			.arg(QStringLiteral("音频文件说明,站点说明")).arg(QString::number(index)));
		sql_query_2.exec();
		count = 0;
		audio_map_data_list_.clear();
		//插入临时表
		for (; sql_query_2.next();)
		{
			auto str__ = sql_query_2.value(QStringLiteral("音频文件说明,站点说明")).toString();
			auto str_IdString = sql_query_2.value(QStringLiteral("IdString")).toString();
			QStringList temList = Character_Do_With::Split1(str__);
			QStringList temList_2 = Character_Do_With::Split1(str_IdString);
			if (temList.size() != temList_2.size())
			{
				emit this->ErrorInfo(QStringLiteral("条目格式非法!"));
				return;
			}
			for (int i = 0; i < temList.length(); ++i)
			{
				//qDebug() << "temList[" << i << "]:" << temList[i];
				QSqlQuery tempQuery(sql_database_);
				tempQuery.prepare(QString("INSERT INTO tempAudioTable VALUES(%1,'%2')").arg(QString::number(i)).arg(temList[i]));
				tempQuery.exec();

				//不存在，添加索引
				//if (index_map_audio.find(index) == index_map_audio.end())
				if (str__.isEmpty() || str_IdString.isEmpty())
				{
					return;
				}
				{
					count++;
					index_map_audio.emplace(index, index);
					EnteryStruceData temp_entery_struct_data;
					temp_entery_struct_data.category = State_Machine::AudioCategory;
					temp_entery_struct_data.index_key_id = index;
					temp_entery_struct_data.index_tem_table_key_id = i;
					temp_entery_struct_data.IdString = temList_2[i];
					temp_entery_struct_data.ShortNameString = temList[i];
					temp_entery_struct_data.count = count;
					audio_map_data_list_.append(temp_entery_struct_data);
				}
				qDebug() << "[" << i << "]:";
			}
		}
 		sql_query_2.clear();
		//读取临时表
		sql_query_2.prepare("select StringCompont from tempAudioTable");
		sql_query_2.exec();
		index_addi_ = 0;
		for (; sql_query_2.next();)
		{
			index_addi_++;
		}
		sql_query_model2.setQuery(sql_query_2);

		sql_query_model1.setHeaderData(0, Qt::Horizontal, QStringLiteral("音频ID"));
		sql_query_model1.setHeaderData(1, Qt::Horizontal, QStringLiteral("音频文件说明"));
		sql_query_model2.setHeaderData(0, Qt::Horizontal, QStringLiteral("音频文件说明,站点说明"));

		break;
	case State_Machine::TextCategory:
		//!右一操作
		//sql_query_1.prepare("select keyId as '字幕ID',ShortName as '字幕说明' from TTextContent");
		sql_query_1.clear();
		sql_query_1.prepare(QString("select keyId as '%1',ShortName as '%2' from TTextContent")
			.arg(QStringLiteral("字幕ID")).arg(QStringLiteral("字幕说明")));
		sql_query_1.exec();
		text_map_data_add_infos_.clear();
		for (; sql_query_1.next();)
		{
			std::map < QString, ContentMapStruce> temp_map;
			ContentMapStruce cms;
			cms.keyId = sql_query_1.value(QStringLiteral("字幕ID")).toInt();
			cms.ShortName = sql_query_1.value(QStringLiteral("字幕说明")).toString();
			temp_map.emplace(sql_query_1.value(QStringLiteral("字幕说明")).toString(), cms);
			text_map_data_add_infos_.append(temp_map);
		}
		sql_query_model1.setQuery(sql_query_1);

		//!左一表操作
		//摧毁临时表
		sql_query_2.clear();
		sql_query_2.prepare("DROP TABLE main.tempTextTable");
		sql_query_2.exec();
		sql_query_2.clear();
		//创建临时表
		sql_query_2.prepare(
			"CREATE TABLE tempTextTable(" \
			"keyId INT PRIMARY KEY     NOT NULL," \
			"StringCompont     TEXT    NOT NULL)" \
		);
		sql_query_2.exec();
		sql_query_2.clear();

		//查询原始表
		sql_query_2.prepare(QString("select IdString,ShortNameString as '%1' from TReportTextConnect where keyId = %2")
			.arg(QStringLiteral("字幕说明，RGB，站点说明")).arg(QString::number(index)));
		sql_query_2.exec();
		count = 0;
		text_map_data_list_.clear();
		//插入临时表
		for (; sql_query_2.next();)
		{
			auto str__ = sql_query_2.value(QStringLiteral("字幕说明，RGB，站点说明")).toString();
			auto str_IdString = sql_query_2.value(QStringLiteral("IdString")).toString();
			QStringList temList = Character_Do_With::Split1(str__);
			QStringList temList_2 = Character_Do_With::Split1(str_IdString);
			if (temList.size() != temList_2.size())
			{
				emit this->ErrorInfo(QStringLiteral("条目格式非法!"));
				return;
			}
			for (int i = 0; i < temList.length(); ++i)
			{
				//qDebug() << "temList[" << i << "]:" << temList[i];
				QSqlQuery tempQuery(sql_database_);
				tempQuery.prepare(QString("INSERT INTO tempTextTable VALUES(%1,'%2')").arg(QString::number(i)).arg(temList[i]));
				tempQuery.exec();

				//不存在，添加索引
				//if (index_map_text.find(index) == index_map_text.end())
				if (str__.isEmpty() || str_IdString.isEmpty())
				{
					return;
				}
				count++;
				//index_map_text.emplace(index, index);
				EnteryStruceData temp_entery_struct_data;
				temp_entery_struct_data.category = State_Machine::TextCategory;
				temp_entery_struct_data.index_key_id = index;  //current connect keyId
				temp_entery_struct_data.index_tem_table_key_id = i;
				temp_entery_struct_data.IdString = temList_2[i];
				temp_entery_struct_data.ShortNameString = temList[i];
				temp_entery_struct_data.count = count;
				text_map_data_list_.append(temp_entery_struct_data);

			}
		}
		sql_query_2.clear();
		//读取临时表
		sql_query_2.prepare("select StringCompont from tempTextTable");
		sql_query_2.exec();
		index_addi_ = 0;
		for (; sql_query_2.next();)
		{
			index_addi_++;
		}

		sql_query_model2.setQuery(sql_query_2);

		//sql_query_2.prepare(QString("select ShortNameString as '字幕说明，RGB，站点说明' from TReportTextConnect where keyId = %1")
		//	.arg(QString::number(index)));
		//sql_query_2.exec();
		//sql_query_model2.setQuery(sql_query_2);

		sql_query_model1.setHeaderData(0, Qt::Horizontal, QStringLiteral("字幕ID"));
		sql_query_model1.setHeaderData(1, Qt::Horizontal, QStringLiteral("字幕说明"));
		sql_query_model2.setHeaderData(0, Qt::Horizontal, QStringLiteral("字幕说明，RGB，站点说明"));
		break;
	default:
		break;
	}

	qobject_cast<Table_View_Content_Insert*>(COMMON->Get("dou_table_view_ptr_"))->SetModels(&sql_query_model1,&sql_query_model2);
}

void Db_Connect::OnUpMoveBtnClicked()
{
	QString temp_ = qobject_cast<Table_View_Content*>(COMMON->Get("table_view_right_ptr_"))->GetCurrentData();
	qDebug() << "OnUpMoveBtnClicked:" << temp_;

	//1.匹配行,确定索引值，保存索引值1，保存内容
	QSqlQuery sqlquery_(sql_database_);

	switch (STATE->table_category_state_info_of_insert_window)
	{
	case State_Machine::AudioCategory:
		//2.上移行：
		//2.1 保存上一行内容，保存索引值2
		sqlquery_.prepare(QString("select * from tempAudioTable where StringCompont = '%1'").arg(temp_));
		sqlquery_.exec();
		for (; sqlquery_.next();)
		{
			pair_1.first = sqlquery_.value("keyId").toInt();
		}
		pair_1.second = temp_;
		qDebug() << pair_1;

		if (pair_1.first < 1)return;
		sqlquery_.clear();
		sqlquery_.prepare(QString("select * from tempAudioTable where keyId = %1").arg(QString::number(pair_1.first-1)));
		sqlquery_.exec();
		pair_2.first = pair_1.first - 1;
		for (; sqlquery_.next();)
		{
			pair_2.second = sqlquery_.value("StringCompont").toString();
		}
		qDebug() << pair_2;
		//2.1 update两行，
		sqlquery_.clear();
		sqlquery_.prepare(QString("update tempAudioTable set StringCompont = '%1' WHERE keyId = %2")
			.arg(pair_1.second).arg(pair_2.first));
		sqlquery_.exec();
		sqlquery_.clear();
		sqlquery_.prepare(QString("update tempAudioTable set StringCompont = '%1' WHERE keyId = %2")
			.arg(pair_2.second).arg(pair_1.first));
		sqlquery_.exec();

		count_i = 0;
		//关联改变
		for (EnteryStruceData& t_entery : audio_map_data_list_)
		{

			//改变临时表索引
			if (t_entery.index_tem_table_key_id == pair_1.first && t_entery.category == State_Machine::AudioCategory
				&& index_connect_table_keyid == t_entery.index_key_id)
			{
				t_entery.index_tem_table_key_id = HOPEVALUE;  //后面设置值
				hope_value_index = count_i;  //被设置值的索引
			}
			//改变临时表索引
			if (t_entery.index_tem_table_key_id == pair_2.first && t_entery.category == State_Machine::AudioCategory
				&& index_connect_table_keyid == t_entery.index_key_id)
			{
				t_entery.index_tem_table_key_id = pair_1.first;
			}
			count_i++;
		}
		audio_map_data_list_[hope_value_index].index_tem_table_key_id = pair_2.first; //设置值

		break;
	case State_Machine::TextCategory:
		//2.上移行：
		//2.1 保存上一行内容，保存索引值2
		sqlquery_.prepare(QString("select * from tempTextTable where StringCompont = '%1'").arg(temp_));
		sqlquery_.exec();
		for (; sqlquery_.next();)
		{
			pair_1.first = sqlquery_.value("keyId").toInt();
		}
		pair_1.second = temp_;
		qDebug() << pair_1;

		if (pair_1.first < 1)
		{
			qDebug() << QStringLiteral("已经到顶啦~");
			return;
		}
		sqlquery_.clear();
		sqlquery_.prepare(QString("select * from tempTextTable where keyId = %1").arg(QString::number(pair_1.first - 1)));
		sqlquery_.exec();
		pair_2.first = pair_1.first - 1;
		for (; sqlquery_.next();)
		{
			pair_2.second = sqlquery_.value("StringCompont").toString();
		}
		qDebug() << pair_2;
		//2.1 update两行，
		sqlquery_.clear();
		sqlquery_.prepare(QString("update tempTextTable set StringCompont = '%1' WHERE keyId = %2")
			.arg(pair_1.second).arg(pair_2.first));
		sqlquery_.exec();
		sqlquery_.clear();
		sqlquery_.prepare(QString("update tempTextTable set StringCompont = '%1' WHERE keyId = %2")
			.arg(pair_2.second).arg(pair_1.first));
		sqlquery_.exec();

		count_i = 0;
		//关联改变
		for (EnteryStruceData& t_entery : text_map_data_list_)
		{
			
			//改变临时表索引
			if (t_entery.index_tem_table_key_id == pair_1.first && t_entery.category == State_Machine::TextCategory
				&& index_connect_table_keyid == t_entery.index_key_id)
			{
				t_entery.index_tem_table_key_id = HOPEVALUE;  //后面设置值
				hope_value_index = count_i;  //被设置值的索引
			}
			//改变临时表索引
			if (t_entery.index_tem_table_key_id == pair_2.first && t_entery.category == State_Machine::TextCategory
				&& index_connect_table_keyid == t_entery.index_key_id)
			{
				t_entery.index_tem_table_key_id = pair_1.first;
			}
			count_i++;
		}
		text_map_data_list_[hope_value_index].index_tem_table_key_id = pair_2.first; //设置值
		break;
	default:
		break;
	}

	UpdataModel2();

}

void Db_Connect::OnDownMoveBtnClicked()
{
	QString temp_ = qobject_cast<Table_View_Content*>(COMMON->Get("table_view_right_ptr_"))->GetCurrentData();
	qDebug() << "OnUpMoveBtnClicked:" << temp_;

	//1.匹配行,确定索引值，保存索引值1，保存内容
	QSqlQuery sqlquery_(sql_database_);

	switch (STATE->table_category_state_info_of_insert_window)
	{
	case State_Machine::AudioCategory:
		//2.上移行：
		//preset
		sqlquery_.clear();
		sqlquery_.prepare(QString("select * from tempAudioTable"));
		sqlquery_.exec();
		row_count = 0;
		for (; sqlquery_.next();)
		{
			row_count++;
		}
		//2.1 保存上一行内容，保存索引值2
		sqlquery_.prepare(QString("select * from tempAudioTable where StringCompont = '%1'").arg(temp_));
		sqlquery_.exec();
		for (; sqlquery_.next();)
		{
			pair_1.first = sqlquery_.value("keyId").toInt();
		}
		pair_1.second = temp_;

		sqlquery_.clear();
		sqlquery_.prepare(QString("select * from tempAudioTable where keyId = %1").arg(pair_1.first + 1));
		sqlquery_.exec();
		pair_2.first = pair_1.first + 1;
		for (; sqlquery_.next();)
		{
			pair_2.second = sqlquery_.value("StringCompont").toString();
		}
		//2.1 update两行，交换两行
		sqlquery_.clear();
		sqlquery_.prepare(QString("update tempAudioTable set StringCompont = '%1' WHERE keyId = %2")
			.arg(pair_1.second).arg(pair_2.first));
		sqlquery_.exec();
		sqlquery_.clear();
		sqlquery_.prepare(QString("update tempAudioTable set StringCompont = '%1' WHERE keyId = %2")
			.arg(pair_2.second).arg(pair_1.first));
		sqlquery_.exec();

		count_i = 0;
		//关联改变
		for (EnteryStruceData& t_entery : audio_map_data_list_)
		{

			//改变临时表索引
			if (t_entery.index_tem_table_key_id == pair_1.first && t_entery.category == State_Machine::AudioCategory
				&& index_connect_table_keyid == t_entery.index_key_id)
			{
				t_entery.index_tem_table_key_id = HOPEVALUE;  //后面设置值
				hope_value_index = count_i;  //被设置值的索引
			}
			//改变临时表索引
			if (t_entery.index_tem_table_key_id == pair_2.first && t_entery.category == State_Machine::AudioCategory
				&& index_connect_table_keyid == t_entery.index_key_id)
			{
				t_entery.index_tem_table_key_id = pair_1.first;
			}
			count_i++;
		}
		audio_map_data_list_[hope_value_index].index_tem_table_key_id = pair_2.first; //设置值

		break;
	case State_Machine::TextCategory:
		//2.上移行：
		//preset
		sqlquery_.clear();
		sqlquery_.prepare(QString("select * from tempTextTable"));
		sqlquery_.exec();
		row_count = 0;
		for (; sqlquery_.next();)
		{
			row_count++;
		}
		//2.1 保存上一行内容，保存索引值2
		sqlquery_.prepare(QString("select * from tempTextTable where StringCompont = '%1'").arg(temp_));
		sqlquery_.exec();
		for (; sqlquery_.next();)
		{
			pair_1.first = sqlquery_.value("keyId").toInt();
		}
		pair_1.second = temp_;

		if (pair_1.first == row_count-1) 
		{
			qDebug() << QStringLiteral("已经到最下面啦~");
			return;
		}
		sqlquery_.clear();
		sqlquery_.prepare(QString("select * from tempTextTable where keyId = %1").arg(QString::number(pair_1.first + 1)));
		sqlquery_.exec();
		pair_2.first = pair_1.first + 1;
		for (; sqlquery_.next();)
		{
			pair_2.second = sqlquery_.value("StringCompont").toString();
		}
		//2.1 update两行，
		sqlquery_.clear();
		sqlquery_.prepare(QString("update tempTextTable set StringCompont = '%1' WHERE keyId = %2")
			.arg(pair_1.second).arg(pair_2.first));
		sqlquery_.exec();
		sqlquery_.clear();
		sqlquery_.prepare(QString("update tempTextTable set StringCompont = '%1' WHERE keyId = %2")
			.arg(pair_2.second).arg(pair_1.first));
		sqlquery_.exec();

		count_i = 0;
		//关联改变
		for (EnteryStruceData& t_entery : text_map_data_list_)
		{

			//改变临时表索引
			if (t_entery.index_tem_table_key_id == pair_1.first && t_entery.category == State_Machine::TextCategory
				&& index_connect_table_keyid == t_entery.index_key_id)
			{
				t_entery.index_tem_table_key_id = HOPEVALUE;  //后面设置值
				hope_value_index = count_i;  //被设置值的索引
			}
			//改变临时表索引
			if (t_entery.index_tem_table_key_id == pair_2.first && t_entery.category == State_Machine::TextCategory
				&& index_connect_table_keyid == t_entery.index_key_id)
			{
				t_entery.index_tem_table_key_id = pair_1.first;
			}
			count_i++;
		}
		text_map_data_list_[hope_value_index].index_tem_table_key_id = pair_2.first; //设置值
		break;
	default:
		break;
	}

	UpdataModel2();
}

void Db_Connect::UpdataModel2()
{
	QSqlQuery sql_query_(sql_database_);

	//left table 
	switch (STATE->table_category_state_info_of_insert_window)
	{
	case State_Machine::AudioCategory:
		//读取临时表
		sql_query_.prepare("select StringCompont from tempAudioTable");
		sql_query_.exec();

		sql_query_model2.setQuery(sql_query_);
		break;
	case State_Machine::TextCategory:
		//读取临时表
		sql_query_.prepare("select StringCompont from tempTextTable");
		sql_query_.exec();

		sql_query_model2.setQuery(sql_query_);
		break;
	default:
		break;
	}
	qobject_cast<Table_View_Content_Insert*>(COMMON->Get("dou_table_view_ptr_"))->SetModel2(&sql_query_model2);
}

void Db_Connect::OnSureBtnClicked()
{
	QPair<QString, QString> temp_pari;

	QSqlQuery sql_query_(sql_database_);
	switch (STATE->table_category_state_info_of_insert_window)
	{
	case State_Machine::AudioCategory:
		temp_pari = Character_Do_With::Splice1(audio_map_data_list_, index_connect_table_keyid);

		qDebug() << "target_str_id_string:" << temp_pari.first;
		qDebug() << "target_str_short_name_string:" << temp_pari.second;
		sql_query_.clear();
		sql_query_.prepare(QString("update TReportAudioConnect set IdString = '%1',ShortNameString = '%2' where keyId = %3")
		.arg(temp_pari.first).arg(temp_pari.second).arg(index_connect_table_keyid));
		sql_query_.exec();
		break;
	case State_Machine::TextCategory:
		temp_pari = Character_Do_With::Splice1(text_map_data_list_, index_connect_table_keyid);
		sql_query_.clear();
		sql_query_.prepare(QString("update TReportTextConnect set IdString = '%1',ShortNameString = '%2' where keyId = %3")
			.arg(temp_pari.first).arg(temp_pari.second).arg(index_connect_table_keyid));
		sql_query_.exec();
		break;
	default:
		break;
	}


}

void Db_Connect::OnLeftTableClicked()
{
	QString temp_str_ = qobject_cast<Table_View_Content*>(COMMON->Get("table_view_left_ptr_"))->GetCurrentData();
	qDebug() << "table_view_left_ptr_:" << temp_str_;
	switch (STATE->table_category_state_info_of_insert_window)
	{
	case State_Machine::AudioCategory:
		for (int i = 0; i < audio_map_data_add_infos_.size(); ++i)
		{
			if (audio_map_data_add_infos_.at(i).find(temp_str_) != audio_map_data_add_infos_.at(i).end())
			{
				content_map_struce_ = (*(audio_map_data_add_infos_.at(i).find(temp_str_))).second;
				//qDebug() << content_map_struce_.keyId;
				break;
			}
		}
		break;
	case State_Machine::TextCategory:
		for (int i = 0;i < text_map_data_add_infos_.size();++i)
		{
			if (text_map_data_add_infos_.at(i).find(temp_str_) != text_map_data_add_infos_.at(i).end())
			{
				content_map_struce_ = (*(text_map_data_add_infos_.at(i).find(temp_str_))).second;
				//qDebug() << content_map_struce_.keyId;
				break;
			}
		}
		break;
	default:
		break;
	}


}

void Db_Connect::OnSignalAddiClicked()
{
	QSqlQuery sql_query_(sql_database_);
	EnteryStruceData temp_entery_struct_data;
	switch (STATE->table_category_state_info_of_insert_window)
	{
	case State_Machine::AudioCategory:
		//向临时表中插入数据
		sql_query_.clear();
		sql_query_.prepare(QString("insert into tempAudioTable values(%1,'%2')")
			.arg(index_addi_).arg(content_map_struce_.ShortName + "," + content_map_struce_.caption));
		sql_query_.exec();
		index_addi_++;
		//向拼接字符中插入数据
		index_map_audio.emplace(count, count);
		temp_entery_struct_data.category = State_Machine::AudioCategory;
		temp_entery_struct_data.index_key_id = index_connect_table_keyid;
		temp_entery_struct_data.index_tem_table_key_id = count;
		temp_entery_struct_data.IdString = QString("%1,%2").arg(content_map_struce_.keyId).arg(0);
		temp_entery_struct_data.ShortNameString = content_map_struce_.ShortName + "," + QStringLiteral("无");
		temp_entery_struct_data.count = count;
		audio_map_data_list_.append(temp_entery_struct_data);
		++count;

		break;
	case State_Machine::TextCategory:
		sql_query_.clear();
		sql_query_.prepare(QString("insert into tempTextTable values(%1,'%2')")
			.arg(index_addi_).arg(content_map_struce_.ShortName+","+ content_map_struce_.color+","+ content_map_struce_.caption));
		sql_query_.exec();
		index_addi_++;
		//向拼接字符中插入数据
		index_map_audio.emplace(count, count);
		temp_entery_struct_data.category = State_Machine::TextCategory;
		temp_entery_struct_data.index_key_id = index_connect_table_keyid;
		temp_entery_struct_data.index_tem_table_key_id = count;
		temp_entery_struct_data.IdString = QString("%1,%2").arg(content_map_struce_.keyId).arg(0);
		temp_entery_struct_data.ShortNameString = content_map_struce_.ShortName + "," + content_map_struce_.color + "," + QStringLiteral("无");  //缩写也得拼接，以“，”
		temp_entery_struct_data.count = count;
		text_map_data_list_.append(temp_entery_struct_data);
		++count;

		break;
	default:
		break;
	}
	UpdataModel2();
}

void Db_Connect::OnSignalRmClicked()
{
	QString temp_ = qobject_cast<Table_View_Content*>(COMMON->Get("table_view_right_ptr_"))->GetCurrentData();
	qDebug() << "OnSignalRmClicked:" << temp_;

	QSqlQuery sql_query_(sql_database_);
	int tem_keyId;

	switch (STATE->table_category_state_info_of_insert_window)
	{
	case State_Machine::AudioCategory:
		//查询keyId
		sql_query_.clear();
		sql_query_.prepare(QString("select * from tempAudioTable where StringCompont = '%1'")
			.arg(temp_));
		sql_query_.exec();
		for (; sql_query_.next();)
		{
			tem_keyId = sql_query_.value("keyId").toInt();
			qDebug() << "tem_keyId:" << tem_keyId;
		}

		index_addi_--;
		RefreshRightTable(tem_keyId, audio_map_data_list_.size());
		qDebug() << "old:" << audio_map_data_list_.size();
		//向拼接字符中删除数据
		for (int i = 0; i < audio_map_data_list_.size(); ++i)
		{
			if (audio_map_data_list_.at(i).index_tem_table_key_id == tem_keyId)
			{
				audio_map_data_list_.removeAt(i); //缩小一个
				break;
			}
		}
		//更新索引
		for (int i = tem_keyId; i < audio_map_data_list_.size(); ++i)
		{
			audio_map_data_list_[i].index_tem_table_key_id = i;
		}
		qDebug() << "new:" << audio_map_data_list_.size();


		break;
	case State_Machine::TextCategory:
		//!最终需求是临时表需要和text_map_data_list_里的数据同步修改

		//查询keyId
		sql_query_.clear();
		sql_query_.prepare(QString("select * from tempTextTable where StringCompont = '%1'")
			.arg(temp_));
		sql_query_.exec();
		for (;sql_query_.next();)
		{
			tem_keyId = sql_query_.value("keyId").toInt();
			qDebug() << "tem_keyId:" << tem_keyId;
		}

		index_addi_--;
		RefreshRightTable(tem_keyId, text_map_data_list_.size());
		qDebug() << "old:" << text_map_data_list_.size();
		//向拼接字符中删除数据
		for (int i = 0; i < text_map_data_list_.size(); ++i)
		{
			if (text_map_data_list_.at(i).index_tem_table_key_id == tem_keyId)
			{
				text_map_data_list_.removeAt(i); //缩小一个
				break;
			}
		}
		//更新索引
		for (int i = tem_keyId; i < text_map_data_list_.size(); ++i)
		{
			text_map_data_list_[i].index_tem_table_key_id = i;
		}
		qDebug() << "new:" << text_map_data_list_.size();

		break;
	default:
		break;
	}
	UpdataModel2();
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
		qDebug() <<"Error:"<<__FUNCDNAME__ << qobject_cast<Menu_Bar*>(COMMON->Get("menu_bar_ptr_"))->file_path_str_;
	}
	qDebug() << "PATH:" << qobject_cast<Menu_Bar*>(COMMON->Get("menu_bar_ptr_"))->file_path_str_;
	//sql_database_ptr_->setDatabaseName(qobject_cast<Menu_Bar*>(COMMON->Get("menu_bar_ptr_"))->file_path_str_);
	sql_database_.setDatabaseName(qobject_cast<Menu_Bar*>(COMMON->Get("menu_bar_ptr_"))->file_path_str_);
	
	//if (sql_database_ptr_->open())
	if (sql_database_.open())
	{
		STATE->db_state_info = State_Machine::Opened;
		STATE->state_db_is_should_open = false;  //not opened
	}
	else
	{
		STATE->state_db_is_should_open = true;  //can open db
		//qDebug() << "ERROR:" << sql_database_ptr_->lastError() << __FUNCDNAME__;
		qDebug() << "ERROR:" << sql_database_.lastError() << __FUNCDNAME__;
	}

	//return *sql_database_ptr_;
	return sql_database_;

}

void Db_Connect::InitMembers()
{
	//sql_database_ptr_ = new QSqlDatabase;
	//sql_database_ptr_ = &QSqlDatabase::addDatabase("QSQLITE");
	sql_database_ = QSqlDatabase::addDatabase("QSQLITE");
	sql_model_query_ptr_ = new QSqlQueryModel;
	COMMON->InsertQObjectPtr("sql_model_query_ptr_", sql_model_query_ptr_);

	sql_model_query_of_serach_ptr_ = new QSqlQueryModel;
	COMMON->InsertQObjectPtr("sql_model_query_of_serach_ptr_", sql_model_query_of_serach_ptr_);
	
	edit_query_model_ptr_ = new Edit_Query_Model;
	COMMON->InsertQObjectPtr("edit_query_model_ptr_", edit_query_model_ptr_);

	sql_table_model = new QSqlTableModel;
	COMMON->InsertQObjectPtr("sql_table_model", sql_table_model);

}

void Db_Connect::InitConnects()
{
}

void Db_Connect::SplitTable()
{

}

void Db_Connect::RefreshRightTable(int start, int end)
{
	QSqlQuery sql_query_(sql_database_);
	QString	StringCompont;
	switch (STATE->table_category_state_info_of_insert_window)
	{
	case State_Machine::AudioCategory:


		for (int start_ = start; start_ < end; start_++)
		{
			sql_query_.clear();
			sql_query_.prepare(QString("select * from tempAudioTable where keyId = %1 ")
				.arg(start_ + 1));
			sql_query_.exec();
			for (; sql_query_.next();)
			{
				StringCompont.clear();
				StringCompont = sql_query_.value("StringCompont").toString();
			}
			//向前覆盖
			sql_query_.prepare(QString("update tempAudioTable set StringCompont = '%1' where keyId = %2")
				.arg(StringCompont).arg(start_));
			sql_query_.exec();
			sql_query_.clear();
			UpdataModel2();
		}
		//而后删除一个
		sql_query_.clear();
		sql_query_.prepare(QString("delete from tempAudioTable where keyId = %1 ")
			.arg(end - 1));
		sql_query_.exec();
		count--;

		break;
	case State_Machine::TextCategory:

		//sql_query_.clear();
		//sql_query_.prepare(QString("delete from tempTextTable where keyId = %1")
		//	.arg(start));
		//sql_query_.exec();
		//UpdataModel2();

		//向前移动一个
		for (int start_ = start; start_ < end; start_++)
		{
			sql_query_.clear();
			sql_query_.prepare(QString("select * from tempTextTable where keyId = %1 ")
				.arg(start_ + 1));
			sql_query_.exec();
			for (; sql_query_.next();)
			{
				StringCompont.clear();
				StringCompont = sql_query_.value("StringCompont").toString();
			}
			//向前覆盖
			sql_query_.prepare(QString("update tempTextTable set StringCompont = '%1' where keyId = %2")
				.arg(StringCompont).arg(start_));
			sql_query_.exec();
			sql_query_.clear();
			UpdataModel2();
		}
		//而后删除一个
		sql_query_.clear();
		sql_query_.prepare(QString("delete from tempTextTable where keyId = %1 ")
			.arg(end-1));
		sql_query_.exec();
		count--;

		break;
	default:
		break;
	}
	UpdataModel2();
}
