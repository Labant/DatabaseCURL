#include "operator_aera.h"
#include "common.h"

Operator_Aera::Operator_Aera()
{
	Init();
}

Operator_Aera::~Operator_Aera()
{
}

void Operator_Aera::InitMembers()
{
	grid_layout_operator_area_ptr = new QGridLayout;
	COMMON->InsertQObjectPtr("grid_layout_operator_area_ptr", grid_layout_operator_area_ptr);
}

void Operator_Aera::InitLayout()
{
	this->setTitle(QStringLiteral("²Ù×÷Çø"));
	this->setLayout(grid_layout_operator_area_ptr);

}
