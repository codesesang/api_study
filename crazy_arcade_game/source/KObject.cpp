#include "stdafx.h"
#include "KObject.h"


KObject::KObject()
{
	m_x = 0;
	m_y = 0;
	m_w = 0;
	m_h = 0;

	image_x = 0;
	image_y = 0;
	image_w = 0;
	image_h = 0;
}


KObject::~KObject()
{
}


void KObject::Draw(HDC hdc)
{
}


void KObject::Move(int dir)
{
}
