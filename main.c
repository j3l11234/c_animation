#include <stdio.h>
#include <windows.h>
#include "animation.h"

int main() {
	system("pause");

	HANDLE Stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i;
	Rect rect_pos;

	char **logoText = (char**)malloc(5 * sizeof(char*));
	for (i = 0; i < 5; i++){
		logoText[i] = (char*)malloc(50 * sizeof(char));
	}
	memcpy(logoText[0], "                                                  ", 50 * sizeof(char));
	memcpy(logoText[1], "                      模板                        ", 50 * sizeof(char));
	memcpy(logoText[2], "              By 1205 蒋圣  12301120              ", 50 * sizeof(char));
	memcpy(logoText[3], "                    2012.10.23                    ", 50 * sizeof(char));
	memcpy(logoText[4], "                                                  ", 50 * sizeof(char));
	anim_create_frame(50, 5, logoText);

	rect_pos.left = 10;
	rect_pos.top = 10;
	rect_pos.right = 60;
	rect_pos.bottom = 15;

	Pos pos = { 0,5 };

	anim_forword(Stdout, rect_pos, logoText);
	goto_pos(Stdout, pos);
	system("pause");

	anim_square(Stdout, rect_pos, logoText);
	goto_pos(Stdout, pos);
	system("pause");

	anim_wipe_cls(Stdout, rect_pos, 10, ANIM_WIPE_DIR_RD_LU, "■");
	anim_wipe(Stdout, rect_pos, logoText, 10, ANIM_WIPE_DIR_RD_LU);
	pos_printf(Stdout, pos, "");
	
	system("pause");

	for ( i = 0; i < 5; i++) {
		free(logoText[i]);
	}
	free(logoText);

	//此处开始写程序代码

	return 0;
}