#include "qt_layout_base.h"

Qt_Layout_Base::Qt_Layout_Base()
{
}

Qt_Layout_Base::~Qt_Layout_Base()
{
}

void Qt_Layout_Base::SetControler(QObject* view_ptr_)
{
}

void Qt_Layout_Base::Init()
{
	this->InitMembers();
	this->InitLayout();
}
