#ifndef logo_h //防止重定义
#define logo_h

//从此版本开始 文本映射不在需要“|”分段，但是千万要注意中文！
//2012.11.06

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

//行进式动画logo
void _logo1(HANDLE Stdout,int width, int height, int left, int top, char **logoText, int *logoTextHeight);
void _logo1_animation(HANDLE Stdout,int width, int height, int left, int top, char*** positionText); //动画控制核心
void _logo1_getPositon(int width, int height, int left, int top, int x, int y, int*** positionDrawing); //更新[刷新区域]的坐标
void _logo1_draw(HANDLE Stdout, int x, int height, int*** positionDrawing, char*** positionText); //绘制随机图案

//方块刷新式动画logo
void _logo2(HANDLE Stdout,int width, int height, int left, int top, char **logoText, int *logoTextHeight);
void _logo2_animation(HANDLE Stdout, int width, int height, int left, int top, char*** positionText); //动画控制核心
void _logo2_draw(HANDLE Stdout, int** printPositionCount, char*** positionText, int left, int top); //绘制随机图案

//走圈式动画
void _logo3(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, char **logoText, int *logoTextHeight);
void _logo3_draw(HANDLE Stdout, int width,int y, int left, int top, char* text); //输出居中文字

//擦除动画
void _wipe_logo(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char **logoText, int *logoTextHeight);
void _wipe_cls(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char *text);
int _wipe_animation(HANDLE Stdout, int width, int height, int left, int top, int sleeptime, int flag, char ***positionText);

//公用函数
void _textPrintFrame(int width, int height, char*** positionText); //生成[文本映射区]的边框像素
void _textCreat(int width,int height, char*** positionText, char* text); //生成[文本映射区]的文本像素
void _creatFrame(HANDLE Stdout, int width, int height, int left, int top, int sleepTime); //生成边框(走圈式)
void _deleteFrame(HANDLE Stdout, int width, int height, int left, int top, int sleepTime); //删除边框(走圈式)
void _print(HANDLE Stdout,int x,int y,char* text); //输出文字


//=================行进式动画logo=================
//功能： 行进式动画logo
//用法： _logo1(窗口句柄,边框宽度,边框高度,起始x坐标,起始y坐标,文本数组,文本高度数组)
//================================================
void _logo1(HANDLE Stdout,int width, int height, int left, int top, char **logoText, int *logoTextHeight)
{
	int i,j;//该变量用于给嵌套的for使用 

	//声明[文本映射区]的字符串数组 
	char ***positionText = (char***)malloc((width+1) * sizeof(char**));  
	for(i=0; i <= width; i++)  
	{    
		positionText[i] = (char**)malloc((height+1) * sizeof(char*));  
		for(j=0; j <= height; j++)  
			positionText[i][j] = (char*)malloc(3 * sizeof(char)); 
	}

	for(i=1;i <= width;i++) //将空文本写入[文本映射区] 
		for(j=1;j <= height;j++)
			strcpy(positionText[i][j],"  ");       
	_textPrintFrame(width, height, positionText);//将边框写入[文本映射区] 

	for(i=1; i<= logoTextHeight[0]; i++) //将显示文本写入[文本映射区]
		_textCreat(width, logoTextHeight[i], positionText, logoText[i]);

	_logo1_animation(Stdout, width, height, left, top, positionText); //动画控制核心

	//释放[文本映射区]的变量
	for(i=0; i <= width; i++)
		for(j=0; j <= height; j++) 
			free(positionText[i][j]);    
	for(i=0; i< width; i++)        
		free(positionText[i]);  
	free(positionText); 
}


//==========行进式动画logo_动画控制核心===========
//功能： 用于控制行进式动画的绘制，为了方便调用独立出来 
//用法： _logo1_animation(窗口句柄, 边框宽度, 边框高度, 起始x坐标, 起始y坐标, [文本映射区])
//================================================
void _logo1_animation(HANDLE Stdout,int width, int height, int left, int top, char*** positionText)
{
	srand(time(NULL));
	int i,j,k,l,m;

	//声明[刷新区]的数组 
	int ***positionDrawing = (int***)malloc(4 * sizeof(int**));  
	for(i=0; i < 4; i++)  
	{    
		positionDrawing[i] = (int**)malloc((height) * sizeof(int*));  
		for(j=0; j < height; j++)  
			positionDrawing[i][j] = (int*)malloc(3 * sizeof(int));  
	}

	for (i=0;i<= width+(height*2);i+=2)  //最大循环，i代表[刷新区]中第一[刷新列]的第一点x坐标 
	{
		_logo1_getPositon(width, height, left, top, 2+i, 0, positionDrawing); //获取[刷新区域]的坐标 

		for(j=1;j<=2;j++) //该循环实现当前[刷新区域]方块闪烁动画效果 
		{    
			for(k=1;k<=3;k++)
			{     
				for(l=1;l<=2;l++)
					_logo1_draw(Stdout, 0, height, positionDrawing, positionText);//_draw负责实现当前[刷新列]的动画效果， 
				_logo1_draw(Stdout, 1, height, positionDrawing, positionText);     
			}  
			_logo1_draw(Stdout, 2, height, positionDrawing, positionText); //有层次的显示第1、2、3列的动画效果
			Sleep(5);
		} 
		//当前[刷新区域]的动画完成

		for(m=0; m < height; m++) //该循环显示当前第四[刷新列]的文本 
		{
			if(positionDrawing[3][m][0] == 1)  //检测该点是否应该显示 
			{
				_print(Stdout,positionDrawing[3][m][1],positionDrawing[3][m][2],"");//定位到显示文本的坐标 
				printf("%s",positionText[positionDrawing[3][m][1]-left+1][positionDrawing[3][m][2]-top+1]);//读取[文本映射区]的文本并显示 
				//  printf(" %d,%d ",positionDrawing[3][m][1]+1,positionDrawing[3][m][2]+1);
				// system("pause");  
			}
		}
		//当前[刷新区域]的动画以及文本完成  
	}

	//释放[刷新区]的变量    
	for(i=0; i < 4; i++)
		for(j=0; j < height; j++) 
			free(positionDrawing[i][j]);    
	for(i=0; i< 4; i++)        
		free(positionDrawing[i]);  
	free(positionDrawing);

}


//======行进式动画logo_更新[刷新区域]的坐标=======
//功能： 由某个给定的[起始刷新点]重新定义[刷新区域]的坐标 
//用法： _logo1_getPositon(框的宽度 ,框的高度,起始横坐标,起始纵坐标,[起始刷新点]的x坐标,[起始刷新点]的y坐标,[刷新区])
//================================================
void _logo1_getPositon(int width ,int height,int left ,int top,int x,int y, int*** positionDrawing)
{


	static int currentPositon[3];//currentPositon[3] 表示[正在判断的刷新点]的坐标 
	static int i,j,k;

	for(i=0;i <= 3;i++)
	{
		currentPositon[1] = left+x-(i-1)*2; // 定义起始[刷新点]的坐标
		currentPositon[2] = top+y;

		for (j=0; j < height; j++)
		{  
			//printf("%d,%d   \n",currentPositon[1],currentPositon[2]);
			positionDrawing[i][j][1]=currentPositon[1];// 写入当前[刷新点]的坐标
			positionDrawing[i][j][2]=currentPositon[2];

			//判断当前[刷新点]坐标是否超出范围 
			if ((currentPositon[1] <= left+width-1 && currentPositon[1] > left-1) && (currentPositon[2] <= top+height-1 && currentPositon[2] > top-1))
				positionDrawing[i][j][0]=1;//未超出，1记为显示 
			else 
				positionDrawing[i][j][0]=0;//已超出，0记为不显示 

			currentPositon[1] = currentPositon[1]-2;//[正在判断的刷新点]的坐标 步进 
			currentPositon[2] = currentPositon[2]+1;
		} 
	}
}


//=========行进式动画logo_绘制随机图案============
//功能： 在当前指定的[刷新列]绘制随机图案实现动画效果 
//用法： _logo1_draw(第几列[刷新列],边框高度,[刷新区],[文本映射区])
//================================================
void _logo1_draw(HANDLE Stdout, int x, int height, int*** positionDrawing, char*** positionText)
{
	static int i;
	for(i=0;i < height;i++)
	{
		if(positionDrawing[x][i][0] == 1)
			if ((int)rand() % 3 == 1)  
				_print(Stdout,positionDrawing[x][i][1],positionDrawing[x][i][2],"■");
			else
				_print(Stdout,positionDrawing[x][i][1],positionDrawing[x][i][2],"  ");
	}
}


//===============方块刷新式动画logo==============
//功能： 方块刷新式动画logo
//用法： _logo2(窗口句柄,边框宽度,边框高度,起始x坐标,起始y坐标,文本数组,文本高度数组)
//================================================
void _logo2(HANDLE Stdout,int width, int height, int left, int top, char **logoText, int *logoTextHeight)
{
	int i,j;

	//声明[文本映射区]的字符串数组 
	char ***positionText = (char***)malloc((width+1) * sizeof(char**));  
	for(i=0; i <= width; i++)  
	{    
		positionText[i] = (char**)malloc((height+1) * sizeof(char*));  
		for(j=0; j <= height; j++)  
			positionText[i][j] = (char*)malloc(3*sizeof(char));  
	}

	//写入文本映射区 
	for(i=1;i <= width;i++) //将空文本写入[文本映射区] 
		for(j=1;j <= height;j++)
			strcpy(positionText[i][j],"  ");   
	_textPrintFrame(width,height,positionText); //生成边框进[文本映射区]

	for(i=1; i<= logoTextHeight[0]; i++) //将显示文本写入[文本映射区]
		_textCreat(width, logoTextHeight[i], positionText, logoText[i]);  

	_logo2_animation(Stdout, width, height, left, top, positionText); //动画控制核心

	//释放[文本映射区]的变量
	for(i=0; i <= width; i++)
		for(j=0; j <= height; j++) 
			free(positionText[i][j]);    
	for(i=0; i< width; i++)        
		free(positionText[i]);  
	free(positionText);   
}


//========方块刷新式动画logo_动画控制核心=========
//功能： 用于控制方块刷新式动画的绘制，为了方便调用独立出来 
//用法： _logo2_animation(窗口句柄, 边框宽度, 边框高度, 起始x坐标, 起始y坐标, [文本映射区])
//================================================
void _logo2_animation(HANDLE Stdout,int width, int height, int left, int top, char*** positionText)
{
	int i,j;

	//声明[像素显示区序列] 
	int **printPositionCount = (int**)malloc((width*height + 1)*sizeof(int*));
	for(i=0; i < width*height + 1; i++)    
		printPositionCount[i] = (int*)malloc(3*sizeof(int)); 
	//为[像素显示区序列]赋值  
	for(i=1;i <= height;i++) 
		for(j=1;j <= width;j+=2)
		{ 
			printPositionCount[(i-1)*width/2 + (j+1)/2][0]  = 1 + ((int)rand()%5 + 3); //第一项表示该[序列]剩余刷新记数
			printPositionCount[(i-1)*width/2 + (j+1)/2][1] = j; //第二项表示该[序列]对应x坐标 
			printPositionCount[(i-1)*width/2 + (j+1)/2][2] = i; //第一项表示该[序列]对应y坐标 
		} 
		printPositionCount[0][0] = width*height/2;//[像素显示区序列]的数量 

		srand(time(NULL));
		while(printPositionCount[0][0] > 0)
		{
			for(i=1;i <= (int)rand()%10; i++) 
			{
				for(j=1;j <= (int)rand()%20; j++)
					_logo2_draw(Stdout, printPositionCount, positionText, left, top);
				_logo2_draw(Stdout, printPositionCount, positionText, left, top);
				Sleep((int)rand() % 2);
			}
			_logo2_draw(Stdout, printPositionCount, positionText, left, top);
			Sleep((int)rand() % 5);
		}

		//_print(Stdout,x,y,"")

		//释放[像素显示区序列]的变量    
		for(i=0; i <= width*height; i++)        
			free(printPositionCount[i]);  
		free(printPositionCount);
}


//=======方块刷新式动画logo_绘制随机图案==========
//功能： 随机选取一个位置实现动画效果 
//用法： _logo2_draw(窗口句柄,[像素显示区序列],[文本映射区],起始x坐标,起始y坐标)
//================================================
void _logo2_draw(HANDLE Stdout, int** printPositionCount, char*** positionText, int left, int top)
{
	static int random,  remain, x, y;
	remain = printPositionCount[0][0]; //获取序列剩余计数(为更直观) 
	if ( remain >=1)
	{ 
		random = 1 + ((int)rand() % (remain));
		x = printPositionCount[random][1]; //从[像素显示区序列]获取x坐标 
		y = printPositionCount[random][2]; //从[像素显示区序列]获取y坐标 

		//_print(Stdout,0,10,"");
		//printf("Debug:  random=%d,  remain=%d, count=%d, x=%d, y=%d    ",random,remain,printPositionCount[random][0],x,y);
		//system("pause");

		if(printPositionCount[random][0] > 0)  //计数不为0，则显示动画
		{                          
			if ((int)rand() % 4 == 1) 
				_print(Stdout,x+left-1,y+top-1,"■");
			else
				_print(Stdout,x+left-1,y+top-1,"  "); 
			printPositionCount[random][0]--;
		}
		else
			if (printPositionCount[random][0] == 0) //计数为0，显示文字
			{
				_print(Stdout,x+left-1,y+top-1,"");
				printf("%s", positionText[x][y]); 
				//将最后一个与当前交换
				printPositionCount[random][0] = printPositionCount[remain][0];
				printPositionCount[random][1] = printPositionCount[remain][1];
				printPositionCount[random][2] = printPositionCount[remain][2];
				printPositionCount[remain][0] = 0; //标记为0，说明废弃
				printPositionCount[0][0]--;    
			}       
	} 
}


//==================擦除动画logo==================
//功能： 擦除动画logo 
//用法： _wipe_logo(窗口句柄, 边框宽度, 边框高度, 起始x坐标, 起始y坐标, 延迟时间, 方向标志, 文本数组,文本高度数组)
//================================================
void _wipe_logo(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char **logoText, int *logoTextHeight)
{
	int i,j;//该变量用于给嵌套的for使用 

	//声明[文本映射区]的字符串数组 
	char ***positionText = (char***)malloc((width+1) * sizeof(char**));  
	for(i=0; i <= width; i++)  
	{    
		positionText[i] = (char**)malloc((height+1) * sizeof(char*));  
		for(j=0; j <= height; j++)  
			positionText[i][j] = (char*)malloc(3 * sizeof(char)); 
	}

	//写入文本映射区 
	for(i=1;i <= width;i++) //将空文本写入[文本映射区] 
		for(j=1;j <= height;j++)
			strcpy(positionText[i][j],"  ");   
	_textPrintFrame(width,height,positionText); //生成边框进[文本映射区]

	for(i=1; i<= logoTextHeight[0]; i++) //将显示文本写入[文本映射区]
		_textCreat(width, logoTextHeight[i], positionText, logoText[i]);       

	_wipe_animation(Stdout, width, height, left, top, sleepTime, flag, positionText);

	//释放[文本映射区]的变量
	for(i=0; i <= width; i++)
		for(j=0; j <= height; j++) 
			free(positionText[i][j]);    
	for(i=0; i< width; i++)        
		free(positionText[i]);  
	free(positionText); 
}


//=================全方块擦除动画=================
//功能： 用擦除动画实现一个方块 
//用法： _wipe_logo(窗口句柄, 边框宽度, 边框高度, 起始x坐标, 起始y坐标, 延迟时间, 方向标志, 文本像素)
//================================================
void _wipe_cls(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char *text)
{
	int i,j;//该变量用于给嵌套的for使用 

	//声明[文本映射区]的字符串数组 
	char ***positionText = (char***)malloc((width+1) * sizeof(char**));  
	for(i=0; i <= width; i++)  
	{    
		positionText[i] = (char**)malloc((height+1) * sizeof(char*));  
		for(j=0; j <= height; j++)  
			positionText[i][j] = (char*)malloc(3 * sizeof(char)); 
	}

	for(i=1;i <= width;i++) //将空文本写入[文本映射区] 
		for(j=1;j <= height;j++)
			strcpy(positionText[i][j],text); 

	_wipe_animation(Stdout, width, height, left, top, sleepTime, flag, positionText);

	//释放[文本映射区]的变量
	for(i=0; i <= width; i++)
		for(j=0; j <= height; j++) 
			free(positionText[i][j]);    
	for(i=0; i< width; i++)        
		free(positionText[i]);  
	free(positionText); 
}


//=============擦除动画_动画控制核心==============
//功能： 用于擦除动画的绘制，为了方便调用独立出来 
//用法： _wipe_animation(窗口句柄, 边框宽度, 边框高度, 起始x坐标, 起始y坐标, 延迟时间, 方向标志, [文本映射区])
//================================================
int _wipe_animation(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char ***positionText)
{
	int i,j; //用于循环
	int start_1, end_1, increment_1; //外层循环所需参数
	int start_2, end_2, increment_2; //内存循环所需参数
	int x,y; //坐标
	int xtoy=0; //x、y交换标记，为1则交换。因为算法限制，[上下方向动画]时两层循环i,j对应x,y的值与[其他反向动画]时相反
	double slope; //斜率,计算x,y对应关系用   一般情况下 x = (y / k) + i

	//判断动画类型
	if (flag ==1) //从左到右
	{
		start_1 = 0; end_1 = width; increment_1 = 1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = 99999999;
	}
	else if(flag ==2) //从右到左
	{
		start_1 = width; end_1 = 0; increment_1 = -1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = 99999999;
	}
	else if(flag ==3) //从上到下
	{
		xtoy = 1;
		start_1 = 0; end_1 = height; increment_1 = 1;
		start_2 = 0; end_2 = width; increment_2 = 1;
		slope = 99999999;
	}
	else if(flag ==4) //从下到上
	{
		xtoy = 1;
		start_1 = height; end_1 = 0; increment_1 = -1;
		start_2 = 0; end_2 = width; increment_2 = 1;
		slope = 99999999;
	}
	else if(flag ==5) //从左上到右下
	{
		start_1 = 0; end_1 = 2 * width; increment_1 = 1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = -1 * (height*1.0 / width*1.0);
	}
	else if(flag ==6) //从右下到左上
	{
		start_1 = 2 * width; end_1 = 0; increment_1 = -1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = -1 * (height*1.0 / width*1.0);
	}
	else if(flag ==7) //从左下到右上
	{
		start_1 = -1 * width; end_1 = width; increment_1 = 1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = (height*1.0 / width*1.0);
	}
	else if(flag ==8) //从右上到左下
	{
		start_1 = width; end_1 = -1 * width; increment_1 = -1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = (height*1.0 / width*1.0);
	}
	else //超出范围
		return -1;

	int count = 0; //显示计数
	for (i = start_1; i != (end_1 + increment_1) ; i += increment_1) //第一层循环
	{
		count = 0; //重置计数
		for (j = start_2; j != (end_2 + increment_2); j += increment_2) //第二层循环
		{
			if (xtoy == 0)// 普通情况 if(flag != 3 && flag != 4)
			{
				x = ((int)(((j/slope)+i)/2))*2; //保证为偶数
				y = j; 
			}
			else if (xtoy == 1) //上下方向的情况 if(flag == 3 || flag == 4)
			{
				x = ((int)(j/2))*2; //保证为偶数
				y = (j/slope)+i; 
			}

			if ((x>0 && x <= width) && ( y>0 && y <= height)) //检测是否超出范围
			{
				_print(Stdout,x+left-2,y+top-1,"");
				printf("%s",positionText[x-1][y]);
				count++;
			}

		}
		if (count > 0) //本次循环有动画生成
			Sleep(sleepTime); //动画延迟
	}
	return 0;
}


//===========生成[文本映射区]的边框像素===========
//功能： 映射每一个点对应的像素进[文本映射区]，形成一个边框 
//用法： _textPrintFrame(边框宽度,边框高度,[文本映射区]的指针)
//================================================
void _textPrintFrame(int width,int height,char*** positionText)
{
	int left=1,top=1, i;   //移植过来的函数，保留left和top参数。 
	//==========上边框==========
	strcpy(positionText[left][top],"┏");
	for (i=2;i<=width-4;i+=2)
		strcpy(positionText[left+i][top],"━"); 
	strcpy(positionText[left+width-2][top],"┓");

	//==========右边框========== 
	for (i=1;i<=height-2;i++)
		strcpy(positionText[left+width-2][top+i],"┃");

	//==========下边框==========
	strcpy(positionText[left+width-2][top+height-1],"┛");
	for (i=width-4;i>=2;i-=2)
		strcpy(positionText[left+i][top+height-1],"━");
	strcpy(positionText[left][top+height-1],"┗");

	//==========右边框========== 
	for (i=height-2;i>=1;i--)
		strcpy(positionText[left][top+i],"┃");
}


//==========生成[文本映射区]中的文本像素==========
//功能： 将文本信息映射进边框中的某一行(居中) 
//用法：_creatText(边框宽度,边框高度,[文本映射区]的指针,文本)
//================================================
void _textCreat(int width,int height, char*** positionText, char* text)

{
	int length=0,x=1;  
	length = strlen(text); //计算字符串长度 
	x = (int(width - length) / 4)*2 +1  ;

	int i = 0;
	while (text[i] != '\0' && text[i+1] != '\0')
	{
		if(x < width && x > 0)//防止覆盖边框
		{
			positionText[x][height][0]= text[i];
			positionText[x][height][1]= text[i+1];
			i+=2;
			x+=2;
		}
		else
			break;
	}
}


//=================走圈式动画logo=================
//功能： 走圈式动画logo
//用法： _logo3(窗口句柄,边框宽度,边框高度,起始x坐标,起始y坐标,文本数组,文本高度数组)
//================================================
void _logo3(HANDLE Stdout,int width, int height, int left, int top, int sleepTime, char **logoText, int *logoTextHeight)
{
	int i;
	_creatFrame(Stdout,width,height,left,top,sleepTime);
	for(i=1; i <= logoTextHeight[0]; i++)
	{
		_logo3_draw(Stdout, width, logoTextHeight[i], left, top, logoText[i]);
		Sleep(sleepTime);
	}
}


//================生成边框(走圈式)================
//功能： 在屏幕上逐字绘制出一个边框 
//用法： _creatFrame(窗口句柄,边框长度,边框高度,绘制间隔)
//================================================  
void _creatFrame(HANDLE Stdout,int width,int height,int left, int top,int sleepTime)
{    
	int i;   
	//==========上========== 
	_print(Stdout,left,top,"┏");
	for (i=2;i<=width-4;i+=2)
	{
		_print(Stdout,left+i,top,"━");
		Sleep(sleepTime);
	}
	_print(Stdout,left+width-2,top,"┓");

	//==========右========== 
	for (i=1;i<=height-2;i++)
	{
		_print(Stdout,left+width-2,top+i,"┃");
		Sleep(sleepTime);
	}

	//==========下==========
	_print(Stdout,left+width-2,top+height-1,"┛");
	for (i=width-4;i>=2;i-=2)
	{
		_print(Stdout,left+i,top+height-1,"━");
		Sleep(sleepTime);
	}
	_print(Stdout,left,top+height-1,"┗");

	//==========右========== 
	for (i=height-2;i>=1;i--)
	{
		_print(Stdout,left,top+i,"┃");
		Sleep(sleepTime);
	} 

}


//================删除边框(走圈式)================
//功能： 清除屏幕上绘制出的边框(原理同绘制一样) 
//用法： _deleteFrame(边框长度,边框高度,绘制间隔)
//注意： 边框的高度和长度要与绘制的一致 
//================================================
void _deleteFrame(HANDLE Stdout,int width,int height,int left, int top,int sleepTime)
{

	//==========左==========     
	int k;
	for (k=1;k<=height;k++)
	{
		_print(Stdout,left,top+k,"  ");
		Sleep(sleepTime);
	}

	//==========下==========     
	for (k=2;k<=width;k+=2)
	{
		_print(Stdout,left+k,top+height-1,"  ");
		Sleep(sleepTime);
	}

	//==========右==========     
	for (k=height-2;k>=0;k--)
	{
		_print(Stdout,left+width-2,top+k,"  ");
		Sleep(sleepTime);
	}

	//==========上==========     
	for (k=width-4;k>=0;k-=2)
	{
		_print(Stdout,left+k,top,"  ");
		Sleep(sleepTime);
	}

}


//==========走圈式动画logo_输出居中文字===========
//功能： 在窗口的任意一行居中输出文本 
//用法： _logo3_draw(窗口句柄,x坐标,y坐标,输出字符串)
//================================================
void _logo3_draw(HANDLE Stdout,int width,int y, int left, int top, char* text)
{
	int length=0,x=1;
	length = strlen(text);
	x = (width - length) / 2;
	_print(Stdout, left+x-1, top+y-1, text);
}


//====================输出文字====================
//功能： 在窗口的任意光标输出文本 
//用法： _print(窗口句柄,x坐标,y坐标,输出字符串)
//================================================
void _print(HANDLE Stdout,int x,int y,char* text)
{
	COORD Pos={0, 0};
	Pos.X=x;
	Pos.Y=y;
	SetConsoleCursorPosition(Stdout, Pos);
	printf("%s",text);
}

#endif 