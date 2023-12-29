#include "table_view_content_insert.h"
#include "operator_icon_domain.h"
#include <QDebug>

Table_View_Content_Insert::
	Table_View_Content_Insert(QWidget* parent):QWidget(parent)
{
	this->Init();
}

Table_View_Content_Insert::~Table_View_Content_Insert()
{
}

void Table_View_Content_Insert::SetModels(QAbstractItemModel* model1, QAbstractItemModel* model2)
{
	table_view_contents_ptr_->SetModels(model1, model2);  //model1:TAudioPath::ShortName,两列：音频ID、音频文件说明
														  //	   TTextContent::ShortName，两列：字幕ID、字幕说明
														  //model2:TReportAudioConnect::ShortNameString分解为2个，音频文件说明、站点说明
														  //	   TReportTextConnect::ShortNameString分解三个为一组：字幕说明、RGB、站点说明
}

void Table_View_Content_Insert::SetModel2(QAbstractItemModel* model2)
{
	table_view_contents_ptr_->SetModel2(model2);
}

void Table_View_Content_Insert::OnSignalTableViewClick(QString str_data_)
{
	qDebug() << "str_data_:" << str_data_ << str_data_.isEmpty();
	emit this->GetTableViewContentsModels(STATE->table_category_state_info_of_insert_window.load(), str_data_);
}

void Table_View_Content_Insert::InitMembers()
{
	gridlayout_table_view_content_insert_ptr_ = new QGridLayout;
	COMMON->InsertQObjectPtr("gridlayout_table_view_content_insert_ptr_", gridlayout_table_view_content_insert_ptr_);
	table_view_contents_ptr_ = new Table_View_Contents(this);
	COMMON->InsertQObjectPtr("table_view_contents_ptr_", table_view_contents_ptr_);
	operator_icon_domain_ptr_ = new Operator_Icon_Domain(this);
	COMMON->InsertQObjectPtr("operator_icon_domain_ptr_", operator_icon_domain_ptr_);
	operator_icon_domain_ptr_->setObjectName("operator_icon_domain_ptr_");
	operator_icon_domain_ptr_->setStyleSheet("#operator_icon_domain_ptr_{background-color:red;}");

}

void Table_View_Content_Insert::InitLayout()
{
	this->setLayout(gridlayout_table_view_content_insert_ptr_);
	gridlayout_table_view_content_insert_ptr_->addWidget(table_view_contents_ptr_, 0, 0, 1, 1);
	gridlayout_table_view_content_insert_ptr_->addWidget(operator_icon_domain_ptr_, 0, 1, 1, 1);
	SetIconsOnCenter();
}

void Table_View_Content_Insert::SetIconsOnCenter()
{
	if (operator_icon_domain_ptr_ == nullptr)
		return;
	operator_icon_domain_ptr_->setMaximumSize(200, 120);
	table_view_contents_ptr_->stackUnder(operator_icon_domain_ptr_);
	//operator_icon_domain_ptr_->move(this->width() / 2.0f - 100, this->height() / 2.0f - 60);
	//table_view_contents_ptr_->setGeometry(0,0,
	//	this->width(), this->height());
	//operator_icon_domain_ptr_->setGeometry(this->width() / 2.0f, this->height() / 2.0f,
	//	200, 120);
	//operator_icon_domain_ptr_->move(50, 50 );
	qDebug() << "operator_icon_domain_ptr_.pos():" << operator_icon_domain_ptr_->pos();
}
