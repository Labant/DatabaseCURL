#include "label_control_addi.h"
#include <QDebug>

Label_Control_Addi::Label_Control_Addi(QWidget* parent)
{
	Init();
}

Label_Control_Addi::~Label_Control_Addi()
{
}

void Label_Control_Addi::Init()
{
	InitMembers();
	InitLayout();
}

void Label_Control_Addi::InitMembers()
{
	if (!image_icon_right_.load(QStringLiteral("C:/01_Work/03_Code/01_VS/03_SelfDevUitls/数据库增删改查操作/Image/Icons/right_arrow100x60.ico")))
	{
		qDebug() << "image_icon_right_ load error on Label_Control_Addi 23";
	};

}

void Label_Control_Addi::InitLayout()
{
	this->setFixedSize(100, 60);
	this->setPixmap(QPixmap::fromImage(image_icon_right_));
}

void Label_Control_Addi::mousePressEvent(QMouseEvent* ev)
{
	if (ev->button() != Qt::LeftButton)
	{
		return;
	}
	emit this->SignalAddiClicked();
	qDebug() << __FUNCDNAME__;
}
