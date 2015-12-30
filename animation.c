#include <windows.h>
#include "animation.h"

typedef struct {
	int x;
	int y;
	int remain;
}Square_Block;

static int anim_forword_getpos(Rect rect_pos, Pos pos_start, Pos *pos_list); //����[ˢ������]������
static void anim_forword_draw(HANDLE Stdout, Pos* point_list, int length); //�������ͼ��

static void anim_square_draw(HANDLE Stdout, Rect rect_pos, char **text_layer, Square_Block *flash_layer, int *remain);

/**************************************************
Function: �н�ʽ����
Description: �н�ʽ����
Input: Stdout ���ھ��, rect_pos�������η�Χ, text_layer�ı�����
Output: none
Return: void
Others:
**************************************************/
void anim_forword(HANDLE Stdout, Rect rect_pos, char **text_layer) {
	const int FLASH_WIDTH = 4; //��˸�������
	int width, height;
	int point_list_len;
	int i, j, k, l;//�ñ������ڸ�Ƕ�׵�forʹ�� 
	Pos pos;
	Pos *point_list;

	width = rect_pos.right - rect_pos.left;
	height = rect_pos.bottom - rect_pos.top;
	point_list = (Pos*)malloc(height * sizeof(Pos));
	pos.y = rect_pos.top;
	for (i = 0 - (height * 2); i < width; i += 2)  //���ѭ����i����[ˢ����]�е�һ[ˢ����]�ĵ�һ��x���� 
	{
		pos.x = rect_pos.left + i + 6;
		point_list_len = anim_forword_getpos(rect_pos, pos, point_list);
		for (j = 0; j < 2; j++) { //��ѭ��ʵ�ֵ�ǰ[ˢ������]������˸����Ч�� 
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
Description: �н�ʽ����_�õ�ˢ�µ�
Input: rect_pos�������η�Χ, pos_start��ʼ��, pos_list���ص�����
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
		//�жϵ��Ƿ񳬳���Χ 
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
Function: �ڵ�ǰָ����[ˢ����]�������ͼ��ʵ�ֶ���Ч��
Description: �ڵ�ǰָ����[ˢ����]�������ͼ��ʵ�ֶ���Ч��
Input: _logo1_draw(�ڼ���[ˢ����],�߿�߶�,[ˢ����],[�ı�ӳ����])
Output: none
Return: void
Others:
**************************************************/
static void anim_forword_draw(HANDLE Stdout, Pos* point_list, int length) {
	int i;
	for (i = 0; i < length; i++) {
		if (rand() % 3 == 1)
			pos_printf(Stdout, point_list[i], "��");
		else
			pos_printf(Stdout, point_list[i], "  ");
	}
}


/**************************************************
Function: ����ˢ��ʽ����
Description: ����ˢ��ʽ����
Input: Stdout ���ھ��, rect_pos�������η�Χ, text_layer�ı�����
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

	//��˸�� ʣ����˸����
	remain = width / 2 * height;
	flash_layer = (Square_Block*)malloc(remain * sizeof(Square_Block));
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j += 2) {
			index = (i * width / 2) + (j / 2);
			flash_layer[index].x = j;
			flash_layer[index].y = i;
			flash_layer[index].remain = (rand() % 5 + 3); //��һ���ʾ��[����]ʣ��ˢ�¼���
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
Function: ����ˢ��ʽ����_�������ͼ��
Description: ���ѡȡһ��λ��ʵ�ֶ���Ч��
Input: Stdout ���ھ��, rect_pos�������η�Χ, text_layer�ı���,flash_layer��˸��, remainʣ�෽��
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
	if (block->remain > 0) { //������Ϊ0������ʾ����
		if (rand() % 4 == 1) {
			pos_printf(Stdout, pos, "��");
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
Function: ��������
Description: ���ڲ��������Ļ���
Input: Stdout ���ھ��, rect_pos�������η�Χ, text_layer�ı����� sleepTime��Ϣʱ�� flag ����
Output: none
Return: void
Others:
**************************************************/
void anim_wipe(HANDLE Stdout, Rect rect_pos, char **text_layer, int sleepTime, int flag) {
	int width, height;
	int i, j; //����ѭ��
	int start_1, end_1, increment_1; //���ѭ���������
	int start_2, end_2, increment_2; //�ڴ�ѭ���������
	int x, y; //����
	int count = 0; //��ʾ����
	int xtoy = 0; //x��y������ǣ�Ϊ1�򽻻�����Ϊ�㷨���ƣ�[���·��򶯻�]ʱ����ѭ��i,j��Ӧx,y��ֵ��[�������򶯻�]ʱ�෴
	double slope; //б��,����x,y��Ӧ��ϵ��   һ������� x = (y / k) + i
	Pos pos;

	width = rect_pos.right - rect_pos.left;
	height = rect_pos.bottom - rect_pos.top;

	//�ж϶�������
	if (ANIM_WIPE_DIR_L_R == flag) { //������
		start_1 = 0; end_1 = width; increment_1 = 2;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = 99999999;
	}
	else if (ANIM_WIPE_DIR_R_L == flag) { //���ҵ���
		start_1 = width; end_1 = 0; increment_1 = -2;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = 99999999;
	}
	else if (ANIM_WIPE_DIR_U_D == flag) { //���ϵ���
		xtoy = 1;
		start_1 = 0; end_1 = height; increment_1 = 1;
		start_2 = 0; end_2 = width; increment_2 = 2;
		slope = 99999999;
	}
	else if (ANIM_WIPE_DIR_D_U == flag) { //���µ���
		xtoy = 1;
		start_1 = height; end_1 = 0; increment_1 = -1;
		start_2 = 0; end_2 = width; increment_2 = 2;
		slope = 99999999;
	}
	else if (ANIM_WIPE_DIR_LU_RD == flag) { //�����ϵ�����
		start_1 = 0; end_1 = 2 * width; increment_1 = 2;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = -1 * (height*1.0 / width*1.0);
	}
	else if (ANIM_WIPE_DIR_RD_LU == flag) { //�����µ�����
		start_1 = 2 * width; end_1 = 0; increment_1 = -2;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = -1 * (height*1.0 / width*1.0);
	}
	else if (ANIM_WIPE_DIR_LD_RU == flag) { //�����µ�����
		start_1 = -1 * width; end_1 = width; increment_1 = 2;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = (height*1.0 / width*1.0);
	}
	else if (ANIM_WIPE_DIR_RU_LD == flag) { //�����ϵ�����
		start_1 = width; end_1 = -1 * width; increment_1 = -1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = (height*1.0 / width*1.0);
	}
	else { //������Χ
		return;
	}

	for (i = start_1; i != (end_1 + increment_1); i += increment_1) //��һ��ѭ��
	{
		count = 0; //���ü���
		for (j = start_2; j != (end_2 + increment_2); j += increment_2) //�ڶ���ѭ��
		{
			if (xtoy == 0)// ��ͨ��� if(flag != 3 && flag != 4)
			{
				x = ((int)(((j / slope) + i) / 2)) * 2; //��֤Ϊż��
				y = j;
			}
			else if (xtoy == 1) //���·������� if(flag == 3 || flag == 4)
			{
				x = ((int)(j / 2)) * 2; //��֤Ϊż��
				y = (int)(j / slope) + i;
			}

			if ((x >= 0 && x < width) && (y >= 0 && y < height)) //����Ƿ񳬳���Χ
			{
				pos.x = x + rect_pos.left;
				pos.y = y + rect_pos.top;
				pos_printf(Stdout, pos, "%c%c", text_layer[y][x], text_layer[y][x + 1]);
				count++;
			}

		}
		if (count > 0) //����ѭ���ж�������
			Sleep(sleepTime); //�����ӳ�
	}
}

/**************************************************
Function: ȫ�����������
Description: �ò�������ʵ��һ������
Input: Stdout ���ھ��, rect_pos�������η�Χ, sleepTime��Ϣʱ��,flag ����,text����
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

//===========����[�ı�ӳ����]�ı߿�����===========
//���ܣ� ӳ��ÿһ�����Ӧ�����ؽ�[�ı�ӳ����]���γ�һ���߿� 
//�÷��� _textPrintFrame(�߿���,�߿�߶�,[�ı�ӳ����]��ָ��)
//================================================
void anim_create_frame(int width, int height, char **text_layer) {
	int i;
	//==========�ϱ߿�==========
	memcpy(&text_layer[0][0], "��", 2 * sizeof(char));
	for (i = 2; i < width - 2; i += 2) {
		memcpy(&text_layer[0][i], "��", 2 * sizeof(char));
	}
	memcpy(&text_layer[0][width - 2], "��", 2 * sizeof(char));

	//==========�ұ߿�========== 
	for (i = 1; i < height - 1; i++) {
		memcpy(&text_layer[i][width - 2], "��", 2 * sizeof(char));
	}

	//==========�±߿�==========
	memcpy(&text_layer[height - 1][width - 2], "��", 2 * sizeof(char));
	for (i = width - 4; i > 0; i -= 2) {
		memcpy(&text_layer[height - 1][i], "��", 2 * sizeof(char));
	}
	memcpy(&text_layer[height - 1][0], "��", 2 * sizeof(char));

	//==========��߿�========== 
	for (i = height - 2; i > 0; i--) {
		memcpy(&text_layer[i][0], "��", 2 * sizeof(char));
	}
}


//
////===============����ˢ��ʽ����logo==============
////���ܣ� ����ˢ��ʽ����logo
////�÷��� _logo2(���ھ��,�߿���,�߿�߶�,��ʼx����,��ʼy����,�ı�����,�ı��߶�����)
////================================================
//void _logo2(HANDLE Stdout, int width, int height, int left, int top, char **logoText, int *logoTextHeight)
//{
//	int i, j;
//
//	//����[�ı�ӳ����]���ַ������� 
//	char ***positionText = (char***)malloc((width + 1) * sizeof(char**));
//	for (i = 0; i <= width; i++)
//	{
//		positionText[i] = (char**)malloc((height + 1) * sizeof(char*));
//		for (j = 0; j <= height; j++)
//			positionText[i][j] = (char*)malloc(3 * sizeof(char));
//	}
//
//	//д���ı�ӳ���� 
//	for (i = 1; i <= width; i++) //�����ı�д��[�ı�ӳ����] 
//		for (j = 1; j <= height; j++)
//			strcpy(positionText[i][j], "  ");
//	_textPrintFrame(width, height, positionText); //���ɱ߿��[�ı�ӳ����]
//
//	for (i = 1; i <= logoTextHeight[0]; i++) //����ʾ�ı�д��[�ı�ӳ����]
//		_textCreat(width, logoTextHeight[i], positionText, logoText[i]);
//
//	_logo2_animation(Stdout, width, height, left, top, positionText); //�������ƺ���
//
//																	  //�ͷ�[�ı�ӳ����]�ı���
//	for (i = 0; i <= width; i++)
//		for (j = 0; j <= height; j++)
//			free(positionText[i][j]);
//	for (i = 0; i< width; i++)
//		free(positionText[i]);
//	free(positionText);
//}
//

//
////==================��������logo==================
////���ܣ� ��������logo 
////�÷��� _wipe_logo(���ھ��, �߿���, �߿�߶�, ��ʼx����, ��ʼy����, �ӳ�ʱ��, �����־, �ı�����,�ı��߶�����)
////================================================
//void _wipe_logo(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char **logoText, int *logoTextHeight)
//{
//	int i, j;//�ñ������ڸ�Ƕ�׵�forʹ�� 
//
//			 //����[�ı�ӳ����]���ַ������� 
//	char ***positionText = (char***)malloc((width + 1) * sizeof(char**));
//	for (i = 0; i <= width; i++)
//	{
//		positionText[i] = (char**)malloc((height + 1) * sizeof(char*));
//		for (j = 0; j <= height; j++)
//			positionText[i][j] = (char*)malloc(3 * sizeof(char));
//	}
//
//	//д���ı�ӳ���� 
//	for (i = 1; i <= width; i++) //�����ı�д��[�ı�ӳ����] 
//		for (j = 1; j <= height; j++)
//			strcpy(positionText[i][j], "  ");
//	_textPrintFrame(width, height, positionText); //���ɱ߿��[�ı�ӳ����]
//
//	for (i = 1; i <= logoTextHeight[0]; i++) //����ʾ�ı�д��[�ı�ӳ����]
//		_textCreat(width, logoTextHeight[i], positionText, logoText[i]);
//
//	_wipe_animation(Stdout, width, height, left, top, sleepTime, flag, positionText);
//
//	//�ͷ�[�ı�ӳ����]�ı���
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
////==========����[�ı�ӳ����]�е��ı�����==========
////���ܣ� ���ı���Ϣӳ����߿��е�ĳһ��(����) 
////�÷���_creatText(�߿���,�߿�߶�,[�ı�ӳ����]��ָ��,�ı�)
////================================================
//void _textCreat(int width, int height, char*** positionText, char* text)
//
//{
//	int length = 0, x = 1;
//	length = strlen(text); //�����ַ������� 
//	x = ((int)(width - length) / 4) * 2 + 1;
//
//	int i = 0;
//	while (text[i] != '\0' && text[i + 1] != '\0')
//	{
//		if (x < width && x > 0)//��ֹ���Ǳ߿�
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
////=================��Ȧʽ����logo=================
////���ܣ� ��Ȧʽ����logo
////�÷��� _logo3(���ھ��,�߿���,�߿�߶�,��ʼx����,��ʼy����,�ı�����,�ı��߶�����)
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
////================���ɱ߿�(��Ȧʽ)================
////���ܣ� ����Ļ�����ֻ��Ƴ�һ���߿� 
////�÷��� _creatFrame(���ھ��,�߿򳤶�,�߿�߶�,���Ƽ��)
////================================================  
//void _creatFrame(HANDLE Stdout, int width, int height, int left, int top, int sleepTime)
//{
//	int i;
//	//==========��========== 
//	_print(Stdout, left, top, "��");
//	for (i = 2; i <= width - 4; i += 2)
//	{
//		_print(Stdout, left + i, top, "��");
//		Sleep(sleepTime);
//	}
//	_print(Stdout, left + width - 2, top, "��");
//
//	//==========��========== 
//	for (i = 1; i <= height - 2; i++)
//	{
//		_print(Stdout, left + width - 2, top + i, "��");
//		Sleep(sleepTime);
//	}
//
//	//==========��==========
//	_print(Stdout, left + width - 2, top + height - 1, "��");
//	for (i = width - 4; i >= 2; i -= 2)
//	{
//		_print(Stdout, left + i, top + height - 1, "��");
//		Sleep(sleepTime);
//	}
//	_print(Stdout, left, top + height - 1, "��");
//
//	//==========��========== 
//	for (i = height - 2; i >= 1; i--)
//	{
//		_print(Stdout, left, top + i, "��");
//		Sleep(sleepTime);
//	}
//
//}
//
//
////================ɾ���߿�(��Ȧʽ)================
////���ܣ� �����Ļ�ϻ��Ƴ��ı߿�(ԭ��ͬ����һ��) 
////�÷��� _deleteFrame(�߿򳤶�,�߿�߶�,���Ƽ��)
////ע�⣺ �߿�ĸ߶Ⱥͳ���Ҫ����Ƶ�һ�� 
////================================================
//void _deleteFrame(HANDLE Stdout, int width, int height, int left, int top, int sleepTime)
//{
//
//	//==========��==========     
//	int k;
//	for (k = 1; k <= height; k++)
//	{
//		_print(Stdout, left, top + k, "  ");
//		Sleep(sleepTime);
//	}
//
//	//==========��==========     
//	for (k = 2; k <= width; k += 2)
//	{
//		_print(Stdout, left + k, top + height - 1, "  ");
//		Sleep(sleepTime);
//	}
//
//	//==========��==========     
//	for (k = height - 2; k >= 0; k--)
//	{
//		_print(Stdout, left + width - 2, top + k, "  ");
//		Sleep(sleepTime);
//	}
//
//	//==========��==========     
//	for (k = width - 4; k >= 0; k -= 2)
//	{
//		_print(Stdout, left + k, top, "  ");
//		Sleep(sleepTime);
//	}
//
//}
//
//
////==========��Ȧʽ����logo_�����������===========
////���ܣ� �ڴ��ڵ�����һ�о�������ı� 
////�÷��� _logo3_draw(���ھ��,x����,y����,����ַ���)
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

//====================�������====================
//���ܣ� �ڴ��ڵ�����������ı� 
//�÷��� _print(���ھ��,x����,y����,����ַ���)
//================================================
void pos_printf(HANDLE Stdout, Pos pos, const char *format, ...) {
	va_list args;
	va_start(args, format);
	goto_pos(Stdout, pos);
	vprintf(format, args);
	va_end(args);
}
