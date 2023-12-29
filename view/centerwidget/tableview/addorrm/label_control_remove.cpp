#include "label_control_remove.h"
#include <QDebug>

Label_Control_Remove::Label_Control_Remove(QWidget* parent)
{
	Init();

}

Label_Control_Remove::~Label_Control_Remove()
{
}

void Label_Control_Remove::Init()
{
	InitMembers();
	InitLayout();
}
void Label_Control_Remove::InitMembers()
{
	if (!image_icon_left_.load(QStringLiteral("C:/01_Work/03_Code/01_VS/03_SelfDevUitls/数据库增删改查操作/Image/Icons/left_arrow100x60.ico")))
	{
		qDebug() << "image_icon_right_ load error on Label_Control_Remove 30";
	};
	this->setFixedSize(100, 60);
	this->setPixmap(QPixmap::fromImage(image_icon_left_));
}

void Label_Control_Remove::InitLayout()
{
}

void Label_Control_Remove::mousePressEvent(QMouseEvent* ev)
{
	if (ev->button() != Qt::LeftButton)
	{
		return;
	}
	emit this->SignalRemoveClicked();
	qDebug() << __FUNCDNAME__;
}
