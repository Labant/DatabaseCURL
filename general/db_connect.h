#pragma once
#include <qobject.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDir>
#include "common.h"
#include "qt_mode_base.h"
#include <QSqlTableModel> 
#include <QSqlResult>
#include <QSqlField> 
#include "edit_query_model.h"
#include <map>
#include <QPair>
#include <QList>

//typedef std::map<int, std::map<int, std::map<std::string, std::string>>> EntryMap;

#define HOPEVALUE -1  //解决 关联改变时互相影响

class Db_Connect :
    public QObject,public Qt_Mode_Base
{
    Q_OBJECT
public:
    Db_Connect();
    ~Db_Connect();
   
    //front page,open db
    QSqlDatabase& OpenDB();
    void OnOpenDb();
    void OnCloseDb();
    QList<QVariant>& OnGetDbAllTableName();
    
    //serach on operator area
	void OnCurrentTextChanged(QString);  //combox value is setted when QCombox::statechange

    //insert on operator area
    void OnCurrentTextChangedOfInsert();  //Combox state changed
    void OnSetComboxValueOfInsert();  //set combox of insert values
    void OnCurrentTextChangedOfComboxOfInsert(QString);  //QCombox::statechange
    void OnGetTableViewContentsModels(int category, QString str_data_);  //Table_View_Content_Insert place get data for two table
    void OnUpMoveBtnClicked();
    void OnDownMoveBtnClicked();
    void UpdataModel2();
    void OnSureBtnClicked();
    void OnLeftTableClicked();
    void OnSignalAddiClicked();
    void OnSignalRmClicked();
protected:
	void OpenDbPath();
    QSqlDatabase& OpenDb();

protected:
	virtual void InitMembers() override;
	virtual void InitConnects() override;
    void SplitTable();
    void RefreshRightTable(int start,int end);
signals:
    void FileNameFromDialog();
    void ErrorInfo(QString);
    void ShowStatusBarInfo(QString);
private:

    QSqlDatabase sql_database_;
    QSqlQueryModel* sql_model_query_ptr_ = nullptr;
    QSqlQueryModel* sql_model_query_of_serach_ptr_ = nullptr;

    Edit_Query_Model* edit_query_model_ptr_ = nullptr;
    QSqlQueryModel sql_model_query_of_Edit_;

    QSqlTableModel* sql_table_model = nullptr;
	QList<QVariant> table_name_ls;

	QSqlQueryModel sql_query_model1;
	QSqlQueryModel sql_query_model2;

    QPair<int, QString> pair_1;
    QPair<int, QString> pair_2;

    int row_count;
	int count = 0;
	int count_i = 0;
    int index_connect_table_keyid;

    QList<EnteryStruceData> text_map_data_list_;
	QList<EnteryStruceData> audio_map_data_list_;
    std::map<int, int> index_map_text;
    std::map<int, int> index_map_audio;
    int hope_value_index = 0;

    QList<std::map<QString, ContentMapStruce>> text_map_data_add_infos_;
    QList<std::map<QString, ContentMapStruce>> audio_map_data_add_infos_;
    ContentMapStruce content_map_struce_;  //音频
    int index_addi_ = 0;

};

