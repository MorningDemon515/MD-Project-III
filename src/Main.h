#include "../Resource.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <iostream>

#include <time.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void ErrorMessage_1(const char* message);
void ErrorMessage_2(HWND hwnd, const char* message);
float TimeDelta();
