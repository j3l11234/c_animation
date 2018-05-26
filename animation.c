#include <windows.h>
#include "animation.h"

typedef struct {
	int x;
	int y;
	int remain;
}Square_Block;

static int anim_forword_getpos(Rect rect_pos, Pos pos_start, Pos *pos_list); //更新[刷新区域]的坐标
static void anim_forword_draw(HANDLE Stdout, Pos* point_list, int length); //绘制随机图案

static void anim_square_draw(HANDLE Stdout, Rect rect_pos, char **text_layer, Square_Block *flash_layer, int *remain);

/**************************************************
Function: 行进式动画
Description: 行进式动画
Input: Stdout 窗口句柄, rect_pos动画矩形范围, text_layer文本数组
Output: none
Return: void
Others:
**************************************************/
void anim_forword(HANDLE Stdout, Rect rect_pos, char **text_layer) {
	const int FLASH_WIDTH = 4; //闪烁动画宽度
	int width, height;
	int point_list_len;
	int i, j, k, l;//该变量用于给嵌套的for使用 
	Pos pos;
	Pos *point_list;

	width = rect_pos.right - rect_pos.left;
	height = rect_pos.bottom - rect_pos.top;
	point_list = (Pos*)malloc(height * sizeof(Pos));
	pos.y = rect_pos.top;
	for (i = 0 - (height * 2); i < width; i += 2)  //最大循环，i代表[刷新区]中第一[刷新列]的第一点x坐标 
	{
		pos.x = rect_pos.left + i + 6;
		point_list_len = anim_forword_getpos(rect_pos, pos, point_list);
		for (j = 0; j < 2; j++) { //该循环实现当前[刷新区域]方块闪烁动画效果 
			anim_forword_draw(Stdout, point_list, point_list_len);

			pos.x = rect_pos.left + i + 4;
			point_list_len = anim_forword_getpos(rect_pos, pos, point_list);
			for (k = 0; k < 2; k++) {
				anim_forword_draw(Stdout, point_list, point_list_len);
				pos.x = rect_pos.left + i + 2;
				point_list_len = anim_forword_getpos(rect_pos, pos, point_list);
				for (l = 0; l < 2; l++) {
					anim_forword_draw(Stdout, point_list, point_list_len);
				}
				Sleep(5);
			}
		}

		pos.x = rect_pos.left + i;
		point_list_len = anim_forword_getpos(rect_pos, pos, point_list);
		for (j = 0; j < point_list_len; j++) {
			pos_printf(Stdout, point_list[j], "%c%c",
				text_layer[point_list[j].y - rect_pos.top][point_list[j].x - rect_pos.left],
				text_layer[point_list[j].y - rect_pos.top][point_list[j].x - rect_pos.left + 1]);
		}
	}

	free(point_list);
}

/**************************************************
Function: anim_forword_getpos
Description: 行进式动画_得到刷新点
Input: rect_pos动画矩形范围, pos_start起始点, pos_list返回点数组
Output: none
Return: void
Others:
**************************************************/
static int anim_forword_getpos(Rect rect_pos, Pos pos_start, Pos *pos_list) {
	int i;
	int height;
	int count;
	Pos pos_cur;

	height = rect_pos.bottom - rect_pos.top;

	pos_cur = pos_start;
	count = 0;
	for (i = 0; i < height; i++) {
		//判断点是否超出范围 
		if (pos_cur.x >= rect_pos.left && pos_cur.x < rect_pos.right &&
			pos_cur.y >= rect_pos.top && pos_cur.y < rect_pos.bottom) {
			pos_list[count++] = pos_cur;
		}
		//step
		pos_cur.x += 2;
		pos_cur.y += 1;
	}

	return count;
}


/**************************************************
Function: 在当前指定的[刷新列]绘制随机图案实现动画效果
Description: 在当前指定的[刷新列]绘制随机图案实现动画效果
Input: _logo1_draw(第几列[刷新列],边框高度,[刷新区],[文本映射区])
Output: none
Return: void
Others:
**************************************************/
static void anim_forword_draw(HANDLE Stdout, Pos* point_list, int length) {
	int i;
	for (i = 0; i < length; i++) {
		if (rand() % 3 == 1)
			pos_printf(Stdout, point_list[i], "■");
		else
			pos_printf(Stdout, point_list[i], "  ");
	}
}


/**************************************************
Function: 方块刷新式动画
Description: 方块刷新式动画
Input: Stdout 窗口句柄, rect_pos动画矩形范围, text_layer文本数组
Output: none
Return: void
Others:
**************************************************/
void anim_square(HANDLE Stdout, Rect rect_pos, char **text_layer) {
	int width, height;
	int i, j, index;
	int remain;
	Square_Block *flash_layer;

	width = rect_pos.right - rect_pos.left;
	height = rect_pos.bottom - rect_pos.top;

	//闪烁层 剩余闪烁次数
	remain = width / 2 * height;
	flash_layer = (Square_Block*)malloc(remain * sizeof(Square_Block));
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j += 2) {
			index = (i * width / 2) + (j / 2);
			flash_layer[index].x = j;
			flash_layer[index].y = i;
			flash_layer[index].remain = (rand() % 5 + 3); //第一项表示该[序列]剩余刷新记数
		}
	}

	while (remain > 0) {
		for (i = 1; i <= 10; i++) {
			for (j = 1; j <= 10; j++) {
				anim_square_draw(Stdout, rect_pos, text_layer, flash_layer, &remain);
			}
			anim_square_draw(Stdout, rect_pos, text_layer, flash_layer, &remain);
			Sleep(3);
		}
		anim_square_draw(Stdout, rect_pos, text_layer, flash_layer, &remain);
		Sleep(5);
	}

	free(flash_layer);
}

/**************************************************
Function: 方块刷新式动画_绘制随机图案
Description: 随机选取一个位置实现动画效果
Input: Stdout 窗口句柄, rect_pos动画矩形范围, text_layer文本层,flash_layer闪烁层, remain剩余方块
Output: none
Return: void
Others:
**************************************************/
void anim_square_draw(HANDLE Stdout, Rect rect_pos, char **text_layer, Square_Block *flash_layer, int *remain) {
	int random;
	Pos pos;
	Square_Block * block;

	if (*remain <= 0) {
		return;
	}

	random = rand() % (*remain);
	block = flash_layer + random;
	pos.x = block->x + rect_pos.left;
	pos.y = block->y + rect_pos.top;
	if (block->remain > 0) { //计数不为0，则显示动画
		if (rand() % 4 == 1) {
			pos_printf(Stdout, pos, "■");
		}
		else {
			pos_printf(Stdout, pos, "  ");
		}
		block->remain--;
	}
	else {
		pos_printf(Stdout, pos, "%c%c",
			text_layer[block->y][block->x], text_layer[block->y][block->x + 1]);
		*block = flash_layer[(*remain) - 1];
		(*remain)--;
	}
}

/**************************************************
Function: 擦除动画
Description: 用于擦除动画的绘制
Input: Stdout 窗口句柄, rect_pos动画矩形范围, text_layer文本数组 sleepTime休息时间 flag 方向
Output: none
Return: void
Others:
**************************************************/
void anim_wipe(HANDLE Stdout, Rect rect_pos, char **text_layer, int sleepTime, int flag) {
	int width, height;
	int i, j; //用于循环
	int start_1, end_1, increment_1; //外层循环所需参数
	int start_2, end_2, increment_2; //内存循环所需参数
	int x, y; //坐标
	int count = 0; //显示计数
	int xtoy = 0; //x、y交换标记，为1则交换。因为算法限制，[上下方向动画]时两层循环i,j对应x,y的值与[其他反向动画]时相反
	double slope; //斜率,计算x,y对应关系用   一般情况下 x = (y / k) + i
	Pos pos;

	width = rect_pos.right - rect_pos.left;
	height = rect_pos.bottom - rect_pos.top;

	//判断动画类型
	if (ANIM_WIPE_DIR_L_R == flag) { //从左到右
		start_1 = 0; end_1 = width; increment_1 = 2;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = 99999999;
	}
	else if (ANIM_WIPE_DIR_R_L == flag) { //从右到左
		start_1 = width; end_1 = 0; increment_1 = -2;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = 99999999;
	}
	else if (ANIM_WIPE_DIR_U_D == flag) { //从上到下
		xtoy = 1;
		start_1 = 0; end_1 = height; increment_1 = 1;
		start_2 = 0; end_2 = width; increment_2 = 2;
		slope = 99999999;
	}
	else if (ANIM_WIPE_DIR_D_U == flag) { //从下到上
		xtoy = 1;
		start_1 = height; end_1 = 0; increment_1 = -1;
		start_2 = 0; end_2 = width; increment_2 = 2;
		slope = 99999999;
	}
	else if (ANIM_WIPE_DIR_LU_RD == flag) { //从左上到右下
		start_1 = 0; end_1 = 2 * width; increment_1 = 2;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = -1 * (height*1.0 / width*1.0);
	}
	else if (ANIM_WIPE_DIR_RD_LU == flag) { //从右下到左上
		start_1 = 2 * width; end_1 = 0; increment_1 = -2;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = -1 * (height*1.0 / width*1.0);
	}
	else if (ANIM_WIPE_DIR_LD_RU == flag) { //从左下到右上
		start_1 = -1 * width; end_1 = width; increment_1 = 2;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = (height*1.0 / width*1.0);
	}
	else if (ANIM_WIPE_DIR_RU_LD == flag) { //从右上到左下
		start_1 = width; end_1 = -1 * width; increment_1 = -1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = (height*1.0 / width*1.0);
	}
	else { //超出范围
		return;
	}

	for (i = start_1; i != (end_1 + increment_1); i += increment_1) //第一层循环
	{
		count = 0; //重置计数
		for (j = start_2; j != (end_2 + increment_2); j += increment_2) //第二层循环
		{
			if (xtoy == 0)// 普通情况 if(flag != 3 && flag != 4)
			{
				x = ((int)(((j / slope) + i) / 2)) * 2; //保证为偶数
				y = j;
			}
			else if (xtoy == 1) //上下方向的情况 if(flag == 3 || flag == 4)
			{
				x = ((int)(j / 2)) * 2; //保证为偶数
				y = (int)(j / slope) + i;
			}

			if ((x >= 0 && x < width) && (y >= 0 && y < height)) //检测是否超出范围
			{
				pos.x = x + rect_pos.left;
				pos.y = y + rect_pos.top;
				pos_printf(Stdout, pos, "%c%c", text_layer[y][x], text_layer[y][x + 1]);
				count++;
			}

		}
		if (count > 0) //本次循环有动画生成
			Sleep(sleepTime); //动画延迟
	}
}

/**************************************************
Function: 全方块擦除动画
Description: 用擦除动画实现一个方块
Input: Stdout 窗口句柄, rect_pos动画矩形范围, sleepTime休息时间,flag 方向,text文字
Output: none
Return: void
Others:
**************************************************/
void anim_wipe_cls(HANDLE Stdout, Rect rect_pos, int sleepTime, int flag, char *text) {
	int width, height;
	int i, j;
	char **text_layer;

	width = rect_pos.right - rect_pos.left;
	height = rect_pos.bottom - rect_pos.top;

	text_layer = (char**)malloc(height * sizeof(char*));
	for (i = 0; i < height; i++) {
		text_layer[i] = (char*)malloc(width * sizeof(char));
	}
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j += 2) {
			memcpy(text_layer[i] + j, text, 2 * sizeof(char));
		}
	}

	anim_wipe(Stdout, rect_pos, text_layer, sleepTime, flag);

	for (i = 0; i < height; i++) {
		free(text_layer[i]);
	}
	free(text_layer);
}

//===========生成[文本映射区]的边框像素===========
//功能： 映射每一个点对应的像素进[文本映射区]，形成一个边框 
//用法： _textPrintFrame(边框宽度,边框高度,[文本映射区]的指针)
//================================================
void anim_create_frame(int width, int height, char **text_layer) {
	int i;
	//==========上边框==========
	memcpy(&text_layer[0][0], "┏", 2 * sizeof(char));
	for (i = 2; i < width - 2; i += 2) {
		memcpy(&text_layer[0][i], "━", 2 * sizeof(char));
	}
	memcpy(&text_layer[0][width - 2], "┓", 2 * sizeof(char));

	//==========右边框========== 
	for (i = 1; i < height - 1; i++) {
		memcpy(&text_layer[i][width - 2], "┃", 2 * sizeof(char));
	}

	//==========下边框==========
	memcpy(&text_layer[height - 1][width - 2], "┛", 2 * sizeof(char));
	for (i = width - 4; i > 0; i -= 2) {
		memcpy(&text_layer[height - 1][i], "━", 2 * sizeof(char));
	}
	memcpy(&text_layer[height - 1][0], "┗", 2 * sizeof(char));

	//==========左边框========== 
	for (i = height - 2; i > 0; i--) {
		memcpy(&text_layer[i][0], "┃", 2 * sizeof(char));
	}
}


//
////===============方块刷新式动画logo==============
////功能： 方块刷新式动画logo
////用法： _logo2(窗口句柄,边框宽度,边框高度,起始x坐标,起始y坐标,文本数组,文本高度数组)
////================================================
//void _logo2(HANDLE Stdout, int width, int height, int left, int top, char **logoText, int *logoTextHeight)
//{
//	int i, j;
//
//	//声明[文本映射区]的字符串数组 
//	char ***positionText = (char***)malloc((width + 1) * sizeof(char**));
//	for (i = 0; i <= width; i++)
//	{
//		positionText[i] = (char**)malloc((height + 1) * sizeof(char*));
//		for (j = 0; j <= height; j++)
//			positionText[i][j] = (char*)malloc(3 * sizeof(char));
//	}
//
//	//写入文本映射区 
//	for (i = 1; i <= width; i++) //将空文本写入[文本映射区] 
//		for (j = 1; j <= height; j++)
//			strcpy(positionText[i][j], "  ");
//	_textPrintFrame(width, height, positionText); //生成边框进[文本映射区]
//
//	for (i = 1; i <= logoTextHeight[0]; i++) //将显示文本写入[文本映射区]
//		_textCreat(width, logoTextHeight[i], positionText, logoText[i]);
//
//	_logo2_animation(Stdout, width, height, left, top, positionText); //动画控制核心
//
//																	  //释放[文本映射区]的变量
//	for (i = 0; i <= width; i++)
//		for (j = 0; j <= height; j++)
//			free(positionText[i][j]);
//	for (i = 0; i< width; i++)
//		free(positionText[i]);
//	free(positionText);
//}
//

//
////==================擦除动画logo==================
////功能： 擦除动画logo 
////用法： _wipe_logo(窗口句柄, 边框宽度, 边框高度, 起始x坐标, 起始y坐标, 延迟时间, 方向标志, 文本数组,文本高度数组)
////================================================
//void _wipe_logo(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char **logoText, int *logoTextHeight)
//{
//	int i, j;//该变量用于给嵌套的for使用 
//
//			 //声明[文本映射区]的字符串数组 
//	char ***positionText = (char***)malloc((width + 1) * sizeof(char**));
//	for (i = 0; i <= width; i++)
//	{
//		positionText[i] = (char**)malloc((height + 1) * sizeof(char*));
//		for (j = 0; j <= height; j++)
//			positionText[i][j] = (char*)malloc(3 * sizeof(char));
//	}
//
//	//写入文本映射区 
//	for (i = 1; i <= width; i++) //将空文本写入[文本映射区] 
//		for (j = 1; j <= height; j++)
//			strcpy(positionText[i][j], "  ");
//	_textPrintFrame(width, height, positionText); //生成边框进[文本映射区]
//
//	for (i = 1; i <= logoTextHeight[0]; i++) //将显示文本写入[文本映射区]
//		_textCreat(width, logoTextHeight[i], positionText, logoText[i]);
//
//	_wipe_animation(Stdout, width, height, left, top, sleepTime, flag, positionText);
//
//	//释放[文本映射区]的变量
//	for (i = 0; i <= width; i++)
//		for (j = 0; j <= height; j++)
//			free(positionText[i][j]);
//	for (i = 0; i< width; i++)
//		free(positionText[i]);
//	free(positionText);
//}
//
//
//
////==========生成[文本映射区]中的文本像素==========
////功能： 将文本信息映射进边框中的某一行(居中) 
////用法：_creatText(边框宽度,边框高度,[文本映射区]的指针,文本)
////================================================
//void _textCreat(int width, int height, char*** positionText, char* text)
//
//{
//	int length = 0, x = 1;
//	length = strlen(text); //计算字符串长度 
//	x = ((int)(width - length) / 4) * 2 + 1;
//
//	int i = 0;
//	while (text[i] != '\0' && text[i + 1] != '\0')
//	{
//		if (x < width && x > 0)//防止覆盖边框
//		{
//			positionText[x][height][0] = text[i];
//			positionText[x][height][1] = text[i + 1];
//			i += 2;
//			x += 2;
//		}
//		else
//			break;
//	}
//}
//
//
////=================走圈式动画logo=================
////功能： 走圈式动画logo
////用法： _logo3(窗口句柄,边框宽度,边框高度,起始x坐标,起始y坐标,文本数组,文本高度数组)
////================================================
//void _logo3(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, char **logoText, int *logoTextHeight)
//{
//	int i;
//	_creatFrame(Stdout, width, height, left, top, sleepTime);
//	for (i = 1; i <= logoTextHeight[0]; i++)
//	{
//		_logo3_draw(Stdout, width, logoTextHeight[i], left, top, logoText[i]);
//		Sleep(sleepTime);
//	}
//}
//
//
////================生成边框(走圈式)================
////功能： 在屏幕上逐字绘制出一个边框 
////用法： _creatFrame(窗口句柄,边框长度,边框高度,绘制间隔)
////================================================  
//void _creatFrame(HANDLE Stdout, int width, int height, int left, int top, int sleepTime)
//{
//	int i;
//	//==========上========== 
//	_print(Stdout, left, top, "┏");
//	for (i = 2; i <= width - 4; i += 2)
//	{
//		_print(Stdout, left + i, top, "━");
//		Sleep(sleepTime);
//	}
//	_print(Stdout, left + width - 2, top, "┓");
//
//	//==========右========== 
//	for (i = 1; i <= height - 2; i++)
//	{
//		_print(Stdout, left + width - 2, top + i, "┃");
//		Sleep(sleepTime);
//	}
//
//	//==========下==========
//	_print(Stdout, left + width - 2, top + height - 1, "┛");
//	for (i = width - 4; i >= 2; i -= 2)
//	{
//		_print(Stdout, left + i, top + height - 1, "━");
//		Sleep(sleepTime);
//	}
//	_print(Stdout, left, top + height - 1, "┗");
//
//	//==========右========== 
//	for (i = height - 2; i >= 1; i--)
//	{
//		_print(Stdout, left, top + i, "┃");
//		Sleep(sleepTime);
//	}
//
//}
//
//
////================删除边框(走圈式)================
////功能： 清除屏幕上绘制出的边框(原理同绘制一样) 
////用法： _deleteFrame(边框长度,边框高度,绘制间隔)
////注意： 边框的高度和长度要与绘制的一致 
////================================================
//void _deleteFrame(HANDLE Stdout, int width, int height, int left, int top, int sleepTime)
//{
//
//	//==========左==========     
//	int k;
//	for (k = 1; k <= height; k++)
//	{
//		_print(Stdout, left, top + k, "  ");
//		Sleep(sleepTime);
//	}
//
//	//==========下==========     
//	for (k = 2; k <= width; k += 2)
//	{
//		_print(Stdout, left + k, top + height - 1, "  ");
//		Sleep(sleepTime);
//	}
//
//	//==========右==========     
//	for (k = height - 2; k >= 0; k--)
//	{
//		_print(Stdout, left + width - 2, top + k, "  ");
//		Sleep(sleepTime);
//	}
//
//	//==========上==========     
//	for (k = width - 4; k >= 0; k -= 2)
//	{
//		_print(Stdout, left + k, top, "  ");
//		Sleep(sleepTime);
//	}
//
//}
//
//
////==========走圈式动画logo_输出居中文字===========
////功能： 在窗口的任意一行居中输出文本 
////用法： _logo3_draw(窗口句柄,x坐标,y坐标,输出字符串)
////================================================
//void _logo3_draw(HANDLE Stdout, int width, int y, int left, int top, char* text)
//{
//	int length = 0, x = 1;
//	length = strlen(text);
//	x = (width - length) / 2;
//	_print(Stdout, left + x - 1, top + y - 1, text);
//}


void goto_pos(HANDLE Stdout, Pos pos) {
	COORD Pos = { pos.x, pos.y };
	SetConsoleCursorPosition(Stdout, Pos);
}

//====================输出文字====================
//功能： 在窗口的任意光标输出文本 
//用法： _print(窗口句柄,x坐标,y坐标,输出字符串)
//================================================
void pos_printf(HANDLE Stdout, Pos pos, const char *format, ...) {
	va_list args;
	va_start(args, format);
	goto_pos(Stdout, pos);
	vprintf(format, args);
	va_end(args);
}
