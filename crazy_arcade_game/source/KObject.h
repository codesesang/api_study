#pragma once
class KObject
{
public:
	KObject();
	~KObject();
	int m_x, m_y, m_w, m_h;							//������Ʈ ��ǥ
	int image_x, image_y, image_w, image_h;			//�̹��� ��ǥ
	void Draw(HDC hdc);
	void Move(int dir);
};

