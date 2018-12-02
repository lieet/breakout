#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define PI 3.14159265

const int OBJ_SIZE = 1;
const int WIDTH = 600, HEIGHT = 900;
const int left = 0, right = 35, bottom = 0, top = 35; //dimensões da tela
const int updateTimerMs = 30000; //taxa de atualização, em ms, da função timer
const float ballSpeed = .15;
const float playerMove = .75;
const int MAX_ZOOM_IN = 20, MAX_ZOOM_OUT = 30, MIN_ANGLE_Y = 0, MAX_ANGLE_Y = 80;
const bool drawBB = true;

#endif