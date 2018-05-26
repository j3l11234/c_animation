#ifndef LOGO_H
#define LOGO_H

#include <stdio.h>

#include <time.h>
#include <string.h>

#define ANIM_WIPE_DIR_L_R	00
#define ANIM_WIPE_DIR_R_L	01
#define ANIM_WIPE_DIR_U_D	02
#define ANIM_WIPE_DIR_D_U	03
#define ANIM_WIPE_DIR_LU_RD	04
#define ANIM_WIPE_DIR_RD_LU	05
#define ANIM_WIPE_DIR_LD_RU	06
#define ANIM_WIPE_DIR_RU_LD	07

typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} Rect;

typedef struct {
	int x;
	int y;
} Pos;


//行进式动画
void anim_forword(HANDLE Stdout, Rect rect_pos, char **text_layer);

//方块刷新式动画
void anim_square(HANDLE Stdout, Rect rect_pos, char **text_layer);

//擦除动画
void anim_wipe(HANDLE Stdout, Rect rect_pos, char **text_layer, int sleepTime, int flag);
void anim_wipe_cls(HANDLE Stdout, Rect rect_pos, int sleepTime, int flag, char *text);

//公用函数
void anim_create_frame(int width, int height, char **text_layer); //生成[文本映射区]的边框像素
void goto_pos(HANDLE Stdout, Pos pos);
void pos_printf(HANDLE Stdout, Pos pos, const char *format, ...);


//void _logo2(HANDLE Stdout, int width, int height, int left, int top, char **logoText, int *logoTextHeight);
//void _logo2_draw(HANDLE Stdout, int** printPositionCount, char*** positionText, int left, int top); //绘制随机图案
//
////走圈式动画
//void _logo3(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, char **logoText, int *logoTextHeight);
//void _logo3_draw(HANDLE Stdout, int width, int y, int left, int top, char* text); //输出居中文字
//
//void _textCreat(int width, int height, char*** positionText, char* text); //生成[文本映射区]的文本像素
//void _creatFrame(HANDLE Stdout, int width, int height, int left, int top, int sleepTime); //生成边框(走圈式)
//void _deleteFrame(HANDLE Stdout, int width, int height, int left, int top, int sleepTime); //删除边框(走圈式)

#endif 