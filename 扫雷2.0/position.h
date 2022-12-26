/********************************************************************************
*                                                                               *
* ProcessEnv.h -- ApiSet Contract for api-ms-win-core-processenvironment-l1     *
*                                                                               *
* Copyright (c) Microsoft Corporation. All rights reserved.                     *
*                                                                               *
********************************************************************************/
#ifndef __POSITION_H__
#define __POSITION_H__

#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

#endif#pragma once
