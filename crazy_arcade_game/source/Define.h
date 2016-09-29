#define WIDTH_MAP 800						//�� �̹��� ũ��
#define HEIGHT_MAP 600						//�� �̹��� ũ��
#define MAP_XSIZE 15						//�ʹ迭 ũ��
#define MAP_YSIZE 13						//�ʹ迭 ũ��
#define MAP_XSPACE 40						//�ʹ迭 ����
#define MAP_YSPACE 40						//�ʹ迭 ����
#define START_XLOCATION 15					//�� ���� ��ġ
#define START_YLOCATION 35					//�� ���� ��ġ

#define CHARACTER_RGB RGB(248, 0, 248)		//�̹��� RGB
#define CHARACTER_SIZE 4					//ĳ���� ��
#define WIDTH_CHARACTER_IMAGE 300			//�̹��� ũ��
#define HEIGHT_CHARACTER_IMAGE 300			//�̹��� ũ��
#define WIDTH_CHARACTER_SIZE 5				//ĳ���� ���� �̹�����
#define HEIGHT_CHARACTER_SIZE 4				//ĳ���� ���� �̹�����
#define WIDTH_CHARACTER 50					//ĳ���� ���� ũ��
#define HEIGHT_CHARACTER 50					//ĳ���� ���� ũ��

#define WIDTH_BALLOON_SIZE 3				//��ǳ�� ���� �̹�����
#define BALLOON_SIZE 2						//��ǳ�� ��
#define WIDTH_BALLOON_IMAGE 219				//��ǳ�� �̹��� ũ��
#define HEIGHT_BALLOON_IMAGE 84				//��ǳ�� �̹��� ũ��
#define WIDTH_BALLOON 70					//��ǳ�� ũ��
#define HEIGHT_BALLOON 70					//��ǳ�� ũ��

#define WAVE_BALLOON_SIZE 40				//������ ��ǳ�� �̹��� ũ��
#define WAVE_ANI_SIZE 30

#define ITEM_SIZE 3							//������ �̹��� ��

#define BRICK_SIZE 2						//�� �̹��� ��


extern int Map[MAP_YSIZE][MAP_XSIZE];		//�ʹ迭
extern int chName[CHARACTER_SIZE];			//�̹��� �ε� ����
extern int balloonName[2];					//ǳ�� �ε� ����
extern int itemName[ITEM_SIZE];				//������ �ε� ����
extern int chLocation[4][2];				//ĳ���� ��ġ 4������
extern int brickName[BRICK_SIZE];			//���� �ε� ����

extern int BalloonUp[8][2];					//��ǳ�� �̹��� ��ǥ
extern int BalloonDown[8][2];
extern int BalloonLeft[8][2];
extern int BalloonRight[8][2];
extern int BalloonCenter[3][2];

extern int aniArr[WAVE_ANI_SIZE];
extern int temp[30];