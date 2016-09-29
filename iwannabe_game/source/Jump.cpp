#include "stdafx.h"
#include "Jump.h"

Jump::Jump(void)
{
	
}


Jump::~Jump(void)
{
	
}

int Jump::UpJump(int *speed, int gravity, int *xPos, int *yPos, bool *JUMP)	//50 10 
{
	if (true == *JUMP)
	{
		*yPos -= *speed;

		*speed -= gravity;

		if (0 == *speed)
		{
			*JUMP = false;
		}
	}

	if (-1 == DownJumpCheck(&*xPos, &*yPos) || false == *JUMP)		//추락
	{
		DownJump(&*speed, gravity, &*xPos, &*yPos, &*JUMP);

		if (2 == LocationFlag)
		{
			//*yPos = 226;
		}
	}


	if (0 == DownJumpCheck(&*xPos, &*yPos))		//추락 X
	{
		if (1 == LocationFlag)
		{
			*yPos = 98;
		}

		if (2 == LocationFlag)
		{
			*yPos = 226;
		}

		if (3 == LocationFlag)
		{
			*yPos = 354;
		}

		if (4 == LocationFlag)
		{
			*yPos = 482;
		}

		if (5 == LocationFlag)
		{
			*yPos = 610;
		}
	}

	
	
	return 0;
}

int Jump::DownJump(int *speed, int gravity, int *xPos, int *yPos, bool *JUMP)
{
	if (false == *JUMP)
	{
		if (*speed != 30)
		{
			*speed += gravity;
		}
		*yPos += *speed;
	}

	return 0;
}

int Jump::DownJumpCheck(int *xPos, int *yPos)
{
	if (1 == LocationFlag)
	{
		if (*yPos < 23)
		{
			*yPos = 23;

			return -1;
		}

		if (*yPos < 98)
		{
			return -1;
		}
	}

	if (2 == LocationFlag)
	{
		if (*yPos < 151)
		{
			*yPos = 151;

			return -1;
		}

		if (*yPos < 226)
		{

			return -1;
		}
	}

	if (3 == LocationFlag)
	{
		if (*yPos < 279)
		{
			*yPos = 279;

			return -1;
		}

		if (*yPos < 354)
		{

			return -1;
		}
	}

	if (4 == LocationFlag)
	{
		if (*yPos < 407)
		{
			*yPos = 407;

			return -1;
		}

		if (*yPos < 482)
		{

			return -1;
		}
	}

	if (5 == LocationFlag)
	{
		if (*yPos < 535)
		{
			*yPos = 535;

			return -1;
		}

		if (*yPos < 610)
		{

			return -1;
		}
	}



	return 0;
}