#pragma once

class Jump
{
public:
	Jump(void);
	~Jump(void);

	int LocationFlag=1;

	int UpJump(int *speed, int gravity, int *xPos, int *yPos, bool *JUMP);
	int DownJump(int *speed, int gravity, int *xPos, int *yPos, bool *JUMP);
	int DownJumpCheck(int *xPos, int *yPos);
};

