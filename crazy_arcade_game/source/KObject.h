#pragma once
class KObject
{
public:
	KObject();
	~KObject();
	int m_x, m_y, m_w, m_h;							//오브젝트 좌표
	int image_x, image_y, image_w, image_h;			//이미지 좌표
	void Draw(HDC hdc);
	void Move(int dir);
};

