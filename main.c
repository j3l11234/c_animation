#include <stdio.h>
#include <windows.h>
#include "animation.h"

int main() {
	system("pause");

	HANDLE Stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i;

	Rect rect_pos = { 0,0,50,5};

	char **logoText = (char**)malloc(5 * sizeof(char*));
	for (i = 0; i <= 5; i++){
		logoText[i] = (char*)malloc(50 * sizeof(char));
	}
	memcpy(logoText[0], "                                                  ", 50 * sizeof(char));
	memcpy(logoText[1], "                    ģ��                          ", 50 * sizeof(char));
	memcpy(logoText[2], "              By 1205 ��ʥ  12301120              ", 50 * sizeof(char));
	memcpy(logoText[3], "                  2012.10.23                      ", 50 * sizeof(char));
	memcpy(logoText[4], "                                                  ", 50 * sizeof(char));
	anim_create_frame(50, 5, logoText);
	//anim_forword(Stdout, rect_pos, logoText);
	//anim_square(Stdout, rect_pos, logoText);
	anim_wipe_cls(Stdout, rect_pos, 10, ANIM_WIPE_DIR_RD_LU, "��");

	anim_wipe(Stdout, rect_pos, logoText, 10, ANIM_WIPE_DIR_RD_LU);

	Pos pos = { 1,5 };
	pos_printf(Stdout, pos, "");

	char * text = "��";
	printf("%c%c", text[0], text[1]);
	system("pause");

	//�˴���ʼд�������

	return 0;
}