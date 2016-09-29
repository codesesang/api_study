#define WIDTH_MAP 800						//맵 이미지 크기
#define HEIGHT_MAP 600						//맵 이미지 크기
#define MAP_XSIZE 15						//맵배열 크기
#define MAP_YSIZE 13						//맵배열 크기
#define MAP_XSPACE 40						//맵배열 간격
#define MAP_YSPACE 40						//맵배열 간격
#define START_XLOCATION 15					//맵 시작 위치
#define START_YLOCATION 35					//맵 시작 위치

#define CHARACTER_RGB RGB(248, 0, 248)		//이미지 RGB
#define CHARACTER_SIZE 4					//캐릭터 수
#define WIDTH_CHARACTER_IMAGE 300			//이미지 크기
#define HEIGHT_CHARACTER_IMAGE 300			//이미지 크기
#define WIDTH_CHARACTER_SIZE 5				//캐릭터 가로 이미지수
#define HEIGHT_CHARACTER_SIZE 4				//캐릭터 세로 이미지수
#define WIDTH_CHARACTER 50					//캐릭터 가로 크기
#define HEIGHT_CHARACTER 50					//캐릭터 세로 크기

#define WIDTH_BALLOON_SIZE 3				//물풍선 가로 이미지수
#define BALLOON_SIZE 2						//물풍선 수
#define WIDTH_BALLOON_IMAGE 219				//물풍선 이미지 크기
#define HEIGHT_BALLOON_IMAGE 84				//물풍선 이미지 크기
#define WIDTH_BALLOON 70					//물풍선 크기
#define HEIGHT_BALLOON 70					//물풍선 크기

#define WAVE_BALLOON_SIZE 40				//터지는 물풍선 이미지 크기
#define WAVE_ANI_SIZE 30

#define ITEM_SIZE 3							//아이템 이미지 수

#define BRICK_SIZE 2						//블럭 이미지 수


extern int Map[MAP_YSIZE][MAP_XSIZE];		//맵배열
extern int chName[CHARACTER_SIZE];			//이미지 로딩 변수
extern int balloonName[2];					//풍선 로딩 변수
extern int itemName[ITEM_SIZE];				//아이템 로딩 변수
extern int chLocation[4][2];				//캐릭터 위치 4꼭지점
extern int brickName[BRICK_SIZE];			//벽돌 로딩 변수

extern int BalloonUp[8][2];					//물풍선 이미지 좌표
extern int BalloonDown[8][2];
extern int BalloonLeft[8][2];
extern int BalloonRight[8][2];
extern int BalloonCenter[3][2];

extern int aniArr[WAVE_ANI_SIZE];
extern int temp[30];