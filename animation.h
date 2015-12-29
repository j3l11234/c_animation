#ifndef logo_h //��ֹ�ض���
#define logo_h

//�Ӵ˰汾��ʼ �ı�ӳ�䲻����Ҫ��|���ֶΣ�����ǧ��Ҫע�����ģ�
//2012.11.06

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

//�н�ʽ����logo
void _logo1(HANDLE Stdout,int width, int height, int left, int top, char **logoText, int *logoTextHeight);
void _logo1_animation(HANDLE Stdout,int width, int height, int left, int top, char*** positionText); //�������ƺ���
void _logo1_getPositon(int width, int height, int left, int top, int x, int y, int*** positionDrawing); //����[ˢ������]������
void _logo1_draw(HANDLE Stdout, int x, int height, int*** positionDrawing, char*** positionText); //�������ͼ��

//����ˢ��ʽ����logo
void _logo2(HANDLE Stdout,int width, int height, int left, int top, char **logoText, int *logoTextHeight);
void _logo2_animation(HANDLE Stdout, int width, int height, int left, int top, char*** positionText); //�������ƺ���
void _logo2_draw(HANDLE Stdout, int** printPositionCount, char*** positionText, int left, int top); //�������ͼ��

//��Ȧʽ����
void _logo3(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, char **logoText, int *logoTextHeight);
void _logo3_draw(HANDLE Stdout, int width,int y, int left, int top, char* text); //�����������

//��������
void _wipe_logo(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char **logoText, int *logoTextHeight);
void _wipe_cls(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char *text);
int _wipe_animation(HANDLE Stdout, int width, int height, int left, int top, int sleeptime, int flag, char ***positionText);

//���ú���
void _textPrintFrame(int width, int height, char*** positionText); //����[�ı�ӳ����]�ı߿�����
void _textCreat(int width,int height, char*** positionText, char* text); //����[�ı�ӳ����]���ı�����
void _creatFrame(HANDLE Stdout, int width, int height, int left, int top, int sleepTime); //���ɱ߿�(��Ȧʽ)
void _deleteFrame(HANDLE Stdout, int width, int height, int left, int top, int sleepTime); //ɾ���߿�(��Ȧʽ)
void _print(HANDLE Stdout,int x,int y,char* text); //�������


//=================�н�ʽ����logo=================
//���ܣ� �н�ʽ����logo
//�÷��� _logo1(���ھ��,�߿���,�߿�߶�,��ʼx����,��ʼy����,�ı�����,�ı��߶�����)
//================================================
void _logo1(HANDLE Stdout,int width, int height, int left, int top, char **logoText, int *logoTextHeight)
{
	int i,j;//�ñ������ڸ�Ƕ�׵�forʹ�� 

	//����[�ı�ӳ����]���ַ������� 
	char ***positionText = (char***)malloc((width+1) * sizeof(char**));  
	for(i=0; i <= width; i++)  
	{    
		positionText[i] = (char**)malloc((height+1) * sizeof(char*));  
		for(j=0; j <= height; j++)  
			positionText[i][j] = (char*)malloc(3 * sizeof(char)); 
	}

	for(i=1;i <= width;i++) //�����ı�д��[�ı�ӳ����] 
		for(j=1;j <= height;j++)
			strcpy(positionText[i][j],"  ");       
	_textPrintFrame(width, height, positionText);//���߿�д��[�ı�ӳ����] 

	for(i=1; i<= logoTextHeight[0]; i++) //����ʾ�ı�д��[�ı�ӳ����]
		_textCreat(width, logoTextHeight[i], positionText, logoText[i]);

	_logo1_animation(Stdout, width, height, left, top, positionText); //�������ƺ���

	//�ͷ�[�ı�ӳ����]�ı���
	for(i=0; i <= width; i++)
		for(j=0; j <= height; j++) 
			free(positionText[i][j]);    
	for(i=0; i< width; i++)        
		free(positionText[i]);  
	free(positionText); 
}


//==========�н�ʽ����logo_�������ƺ���===========
//���ܣ� ���ڿ����н�ʽ�����Ļ��ƣ�Ϊ�˷�����ö������� 
//�÷��� _logo1_animation(���ھ��, �߿���, �߿�߶�, ��ʼx����, ��ʼy����, [�ı�ӳ����])
//================================================
void _logo1_animation(HANDLE Stdout,int width, int height, int left, int top, char*** positionText)
{
	srand(time(NULL));
	int i,j,k,l,m;

	//����[ˢ����]������ 
	int ***positionDrawing = (int***)malloc(4 * sizeof(int**));  
	for(i=0; i < 4; i++)  
	{    
		positionDrawing[i] = (int**)malloc((height) * sizeof(int*));  
		for(j=0; j < height; j++)  
			positionDrawing[i][j] = (int*)malloc(3 * sizeof(int));  
	}

	for (i=0;i<= width+(height*2);i+=2)  //���ѭ����i����[ˢ����]�е�һ[ˢ����]�ĵ�һ��x���� 
	{
		_logo1_getPositon(width, height, left, top, 2+i, 0, positionDrawing); //��ȡ[ˢ������]������ 

		for(j=1;j<=2;j++) //��ѭ��ʵ�ֵ�ǰ[ˢ������]������˸����Ч�� 
		{    
			for(k=1;k<=3;k++)
			{     
				for(l=1;l<=2;l++)
					_logo1_draw(Stdout, 0, height, positionDrawing, positionText);//_draw����ʵ�ֵ�ǰ[ˢ����]�Ķ���Ч���� 
				_logo1_draw(Stdout, 1, height, positionDrawing, positionText);     
			}  
			_logo1_draw(Stdout, 2, height, positionDrawing, positionText); //�в�ε���ʾ��1��2��3�еĶ���Ч��
			Sleep(5);
		} 
		//��ǰ[ˢ������]�Ķ������

		for(m=0; m < height; m++) //��ѭ����ʾ��ǰ����[ˢ����]���ı� 
		{
			if(positionDrawing[3][m][0] == 1)  //���õ��Ƿ�Ӧ����ʾ 
			{
				_print(Stdout,positionDrawing[3][m][1],positionDrawing[3][m][2],"");//��λ����ʾ�ı������� 
				printf("%s",positionText[positionDrawing[3][m][1]-left+1][positionDrawing[3][m][2]-top+1]);//��ȡ[�ı�ӳ����]���ı�����ʾ 
				//  printf(" %d,%d ",positionDrawing[3][m][1]+1,positionDrawing[3][m][2]+1);
				// system("pause");  
			}
		}
		//��ǰ[ˢ������]�Ķ����Լ��ı����  
	}

	//�ͷ�[ˢ����]�ı���    
	for(i=0; i < 4; i++)
		for(j=0; j < height; j++) 
			free(positionDrawing[i][j]);    
	for(i=0; i< 4; i++)        
		free(positionDrawing[i]);  
	free(positionDrawing);

}


//======�н�ʽ����logo_����[ˢ������]������=======
//���ܣ� ��ĳ��������[��ʼˢ�µ�]���¶���[ˢ������]������ 
//�÷��� _logo1_getPositon(��Ŀ�� ,��ĸ߶�,��ʼ������,��ʼ������,[��ʼˢ�µ�]��x����,[��ʼˢ�µ�]��y����,[ˢ����])
//================================================
void _logo1_getPositon(int width ,int height,int left ,int top,int x,int y, int*** positionDrawing)
{


	static int currentPositon[3];//currentPositon[3] ��ʾ[�����жϵ�ˢ�µ�]������ 
	static int i,j,k;

	for(i=0;i <= 3;i++)
	{
		currentPositon[1] = left+x-(i-1)*2; // ������ʼ[ˢ�µ�]������
		currentPositon[2] = top+y;

		for (j=0; j < height; j++)
		{  
			//printf("%d,%d   \n",currentPositon[1],currentPositon[2]);
			positionDrawing[i][j][1]=currentPositon[1];// д�뵱ǰ[ˢ�µ�]������
			positionDrawing[i][j][2]=currentPositon[2];

			//�жϵ�ǰ[ˢ�µ�]�����Ƿ񳬳���Χ 
			if ((currentPositon[1] <= left+width-1 && currentPositon[1] > left-1) && (currentPositon[2] <= top+height-1 && currentPositon[2] > top-1))
				positionDrawing[i][j][0]=1;//δ������1��Ϊ��ʾ 
			else 
				positionDrawing[i][j][0]=0;//�ѳ�����0��Ϊ����ʾ 

			currentPositon[1] = currentPositon[1]-2;//[�����жϵ�ˢ�µ�]������ ���� 
			currentPositon[2] = currentPositon[2]+1;
		} 
	}
}


//=========�н�ʽ����logo_�������ͼ��============
//���ܣ� �ڵ�ǰָ����[ˢ����]�������ͼ��ʵ�ֶ���Ч�� 
//�÷��� _logo1_draw(�ڼ���[ˢ����],�߿�߶�,[ˢ����],[�ı�ӳ����])
//================================================
void _logo1_draw(HANDLE Stdout, int x, int height, int*** positionDrawing, char*** positionText)
{
	static int i;
	for(i=0;i < height;i++)
	{
		if(positionDrawing[x][i][0] == 1)
			if ((int)rand() % 3 == 1)  
				_print(Stdout,positionDrawing[x][i][1],positionDrawing[x][i][2],"��");
			else
				_print(Stdout,positionDrawing[x][i][1],positionDrawing[x][i][2],"  ");
	}
}


//===============����ˢ��ʽ����logo==============
//���ܣ� ����ˢ��ʽ����logo
//�÷��� _logo2(���ھ��,�߿���,�߿�߶�,��ʼx����,��ʼy����,�ı�����,�ı��߶�����)
//================================================
void _logo2(HANDLE Stdout,int width, int height, int left, int top, char **logoText, int *logoTextHeight)
{
	int i,j;

	//����[�ı�ӳ����]���ַ������� 
	char ***positionText = (char***)malloc((width+1) * sizeof(char**));  
	for(i=0; i <= width; i++)  
	{    
		positionText[i] = (char**)malloc((height+1) * sizeof(char*));  
		for(j=0; j <= height; j++)  
			positionText[i][j] = (char*)malloc(3*sizeof(char));  
	}

	//д���ı�ӳ���� 
	for(i=1;i <= width;i++) //�����ı�д��[�ı�ӳ����] 
		for(j=1;j <= height;j++)
			strcpy(positionText[i][j],"  ");   
	_textPrintFrame(width,height,positionText); //���ɱ߿��[�ı�ӳ����]

	for(i=1; i<= logoTextHeight[0]; i++) //����ʾ�ı�д��[�ı�ӳ����]
		_textCreat(width, logoTextHeight[i], positionText, logoText[i]);  

	_logo2_animation(Stdout, width, height, left, top, positionText); //�������ƺ���

	//�ͷ�[�ı�ӳ����]�ı���
	for(i=0; i <= width; i++)
		for(j=0; j <= height; j++) 
			free(positionText[i][j]);    
	for(i=0; i< width; i++)        
		free(positionText[i]);  
	free(positionText);   
}


//========����ˢ��ʽ����logo_�������ƺ���=========
//���ܣ� ���ڿ��Ʒ���ˢ��ʽ�����Ļ��ƣ�Ϊ�˷�����ö������� 
//�÷��� _logo2_animation(���ھ��, �߿���, �߿�߶�, ��ʼx����, ��ʼy����, [�ı�ӳ����])
//================================================
void _logo2_animation(HANDLE Stdout,int width, int height, int left, int top, char*** positionText)
{
	int i,j;

	//����[������ʾ������] 
	int **printPositionCount = (int**)malloc((width*height + 1)*sizeof(int*));
	for(i=0; i < width*height + 1; i++)    
		printPositionCount[i] = (int*)malloc(3*sizeof(int)); 
	//Ϊ[������ʾ������]��ֵ  
	for(i=1;i <= height;i++) 
		for(j=1;j <= width;j+=2)
		{ 
			printPositionCount[(i-1)*width/2 + (j+1)/2][0]  = 1 + ((int)rand()%5 + 3); //��һ���ʾ��[����]ʣ��ˢ�¼���
			printPositionCount[(i-1)*width/2 + (j+1)/2][1] = j; //�ڶ����ʾ��[����]��Ӧx���� 
			printPositionCount[(i-1)*width/2 + (j+1)/2][2] = i; //��һ���ʾ��[����]��Ӧy���� 
		} 
		printPositionCount[0][0] = width*height/2;//[������ʾ������]������ 

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

		//�ͷ�[������ʾ������]�ı���    
		for(i=0; i <= width*height; i++)        
			free(printPositionCount[i]);  
		free(printPositionCount);
}


//=======����ˢ��ʽ����logo_�������ͼ��==========
//���ܣ� ���ѡȡһ��λ��ʵ�ֶ���Ч�� 
//�÷��� _logo2_draw(���ھ��,[������ʾ������],[�ı�ӳ����],��ʼx����,��ʼy����)
//================================================
void _logo2_draw(HANDLE Stdout, int** printPositionCount, char*** positionText, int left, int top)
{
	static int random,  remain, x, y;
	remain = printPositionCount[0][0]; //��ȡ����ʣ�����(Ϊ��ֱ��) 
	if ( remain >=1)
	{ 
		random = 1 + ((int)rand() % (remain));
		x = printPositionCount[random][1]; //��[������ʾ������]��ȡx���� 
		y = printPositionCount[random][2]; //��[������ʾ������]��ȡy���� 

		//_print(Stdout,0,10,"");
		//printf("Debug:  random=%d,  remain=%d, count=%d, x=%d, y=%d    ",random,remain,printPositionCount[random][0],x,y);
		//system("pause");

		if(printPositionCount[random][0] > 0)  //������Ϊ0������ʾ����
		{                          
			if ((int)rand() % 4 == 1) 
				_print(Stdout,x+left-1,y+top-1,"��");
			else
				_print(Stdout,x+left-1,y+top-1,"  "); 
			printPositionCount[random][0]--;
		}
		else
			if (printPositionCount[random][0] == 0) //����Ϊ0����ʾ����
			{
				_print(Stdout,x+left-1,y+top-1,"");
				printf("%s", positionText[x][y]); 
				//�����һ���뵱ǰ����
				printPositionCount[random][0] = printPositionCount[remain][0];
				printPositionCount[random][1] = printPositionCount[remain][1];
				printPositionCount[random][2] = printPositionCount[remain][2];
				printPositionCount[remain][0] = 0; //���Ϊ0��˵������
				printPositionCount[0][0]--;    
			}       
	} 
}


//==================��������logo==================
//���ܣ� ��������logo 
//�÷��� _wipe_logo(���ھ��, �߿���, �߿�߶�, ��ʼx����, ��ʼy����, �ӳ�ʱ��, �����־, �ı�����,�ı��߶�����)
//================================================
void _wipe_logo(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char **logoText, int *logoTextHeight)
{
	int i,j;//�ñ������ڸ�Ƕ�׵�forʹ�� 

	//����[�ı�ӳ����]���ַ������� 
	char ***positionText = (char***)malloc((width+1) * sizeof(char**));  
	for(i=0; i <= width; i++)  
	{    
		positionText[i] = (char**)malloc((height+1) * sizeof(char*));  
		for(j=0; j <= height; j++)  
			positionText[i][j] = (char*)malloc(3 * sizeof(char)); 
	}

	//д���ı�ӳ���� 
	for(i=1;i <= width;i++) //�����ı�д��[�ı�ӳ����] 
		for(j=1;j <= height;j++)
			strcpy(positionText[i][j],"  ");   
	_textPrintFrame(width,height,positionText); //���ɱ߿��[�ı�ӳ����]

	for(i=1; i<= logoTextHeight[0]; i++) //����ʾ�ı�д��[�ı�ӳ����]
		_textCreat(width, logoTextHeight[i], positionText, logoText[i]);       

	_wipe_animation(Stdout, width, height, left, top, sleepTime, flag, positionText);

	//�ͷ�[�ı�ӳ����]�ı���
	for(i=0; i <= width; i++)
		for(j=0; j <= height; j++) 
			free(positionText[i][j]);    
	for(i=0; i< width; i++)        
		free(positionText[i]);  
	free(positionText); 
}


//=================ȫ�����������=================
//���ܣ� �ò�������ʵ��һ������ 
//�÷��� _wipe_logo(���ھ��, �߿���, �߿�߶�, ��ʼx����, ��ʼy����, �ӳ�ʱ��, �����־, �ı�����)
//================================================
void _wipe_cls(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char *text)
{
	int i,j;//�ñ������ڸ�Ƕ�׵�forʹ�� 

	//����[�ı�ӳ����]���ַ������� 
	char ***positionText = (char***)malloc((width+1) * sizeof(char**));  
	for(i=0; i <= width; i++)  
	{    
		positionText[i] = (char**)malloc((height+1) * sizeof(char*));  
		for(j=0; j <= height; j++)  
			positionText[i][j] = (char*)malloc(3 * sizeof(char)); 
	}

	for(i=1;i <= width;i++) //�����ı�д��[�ı�ӳ����] 
		for(j=1;j <= height;j++)
			strcpy(positionText[i][j],text); 

	_wipe_animation(Stdout, width, height, left, top, sleepTime, flag, positionText);

	//�ͷ�[�ı�ӳ����]�ı���
	for(i=0; i <= width; i++)
		for(j=0; j <= height; j++) 
			free(positionText[i][j]);    
	for(i=0; i< width; i++)        
		free(positionText[i]);  
	free(positionText); 
}


//=============��������_�������ƺ���==============
//���ܣ� ���ڲ��������Ļ��ƣ�Ϊ�˷�����ö������� 
//�÷��� _wipe_animation(���ھ��, �߿���, �߿�߶�, ��ʼx����, ��ʼy����, �ӳ�ʱ��, �����־, [�ı�ӳ����])
//================================================
int _wipe_animation(HANDLE Stdout, int width, int height, int left, int top, int sleepTime, int flag, char ***positionText)
{
	int i,j; //����ѭ��
	int start_1, end_1, increment_1; //���ѭ���������
	int start_2, end_2, increment_2; //�ڴ�ѭ���������
	int x,y; //����
	int xtoy=0; //x��y������ǣ�Ϊ1�򽻻�����Ϊ�㷨���ƣ�[���·��򶯻�]ʱ����ѭ��i,j��Ӧx,y��ֵ��[�������򶯻�]ʱ�෴
	double slope; //б��,����x,y��Ӧ��ϵ��   һ������� x = (y / k) + i

	//�ж϶�������
	if (flag ==1) //������
	{
		start_1 = 0; end_1 = width; increment_1 = 1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = 99999999;
	}
	else if(flag ==2) //���ҵ���
	{
		start_1 = width; end_1 = 0; increment_1 = -1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = 99999999;
	}
	else if(flag ==3) //���ϵ���
	{
		xtoy = 1;
		start_1 = 0; end_1 = height; increment_1 = 1;
		start_2 = 0; end_2 = width; increment_2 = 1;
		slope = 99999999;
	}
	else if(flag ==4) //���µ���
	{
		xtoy = 1;
		start_1 = height; end_1 = 0; increment_1 = -1;
		start_2 = 0; end_2 = width; increment_2 = 1;
		slope = 99999999;
	}
	else if(flag ==5) //�����ϵ�����
	{
		start_1 = 0; end_1 = 2 * width; increment_1 = 1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = -1 * (height*1.0 / width*1.0);
	}
	else if(flag ==6) //�����µ�����
	{
		start_1 = 2 * width; end_1 = 0; increment_1 = -1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = -1 * (height*1.0 / width*1.0);
	}
	else if(flag ==7) //�����µ�����
	{
		start_1 = -1 * width; end_1 = width; increment_1 = 1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = (height*1.0 / width*1.0);
	}
	else if(flag ==8) //�����ϵ�����
	{
		start_1 = width; end_1 = -1 * width; increment_1 = -1;
		start_2 = 0; end_2 = height; increment_2 = 1;
		slope = (height*1.0 / width*1.0);
	}
	else //������Χ
		return -1;

	int count = 0; //��ʾ����
	for (i = start_1; i != (end_1 + increment_1) ; i += increment_1) //��һ��ѭ��
	{
		count = 0; //���ü���
		for (j = start_2; j != (end_2 + increment_2); j += increment_2) //�ڶ���ѭ��
		{
			if (xtoy == 0)// ��ͨ��� if(flag != 3 && flag != 4)
			{
				x = ((int)(((j/slope)+i)/2))*2; //��֤Ϊż��
				y = j; 
			}
			else if (xtoy == 1) //���·������� if(flag == 3 || flag == 4)
			{
				x = ((int)(j/2))*2; //��֤Ϊż��
				y = (j/slope)+i; 
			}

			if ((x>0 && x <= width) && ( y>0 && y <= height)) //����Ƿ񳬳���Χ
			{
				_print(Stdout,x+left-2,y+top-1,"");
				printf("%s",positionText[x-1][y]);
				count++;
			}

		}
		if (count > 0) //����ѭ���ж�������
			Sleep(sleepTime); //�����ӳ�
	}
	return 0;
}


//===========����[�ı�ӳ����]�ı߿�����===========
//���ܣ� ӳ��ÿһ�����Ӧ�����ؽ�[�ı�ӳ����]���γ�һ���߿� 
//�÷��� _textPrintFrame(�߿���,�߿�߶�,[�ı�ӳ����]��ָ��)
//================================================
void _textPrintFrame(int width,int height,char*** positionText)
{
	int left=1,top=1, i;   //��ֲ�����ĺ���������left��top������ 
	//==========�ϱ߿�==========
	strcpy(positionText[left][top],"��");
	for (i=2;i<=width-4;i+=2)
		strcpy(positionText[left+i][top],"��"); 
	strcpy(positionText[left+width-2][top],"��");

	//==========�ұ߿�========== 
	for (i=1;i<=height-2;i++)
		strcpy(positionText[left+width-2][top+i],"��");

	//==========�±߿�==========
	strcpy(positionText[left+width-2][top+height-1],"��");
	for (i=width-4;i>=2;i-=2)
		strcpy(positionText[left+i][top+height-1],"��");
	strcpy(positionText[left][top+height-1],"��");

	//==========�ұ߿�========== 
	for (i=height-2;i>=1;i--)
		strcpy(positionText[left][top+i],"��");
}


//==========����[�ı�ӳ����]�е��ı�����==========
//���ܣ� ���ı���Ϣӳ����߿��е�ĳһ��(����) 
//�÷���_creatText(�߿���,�߿�߶�,[�ı�ӳ����]��ָ��,�ı�)
//================================================
void _textCreat(int width,int height, char*** positionText, char* text)

{
	int length=0,x=1;  
	length = strlen(text); //�����ַ������� 
	x = (int(width - length) / 4)*2 +1  ;

	int i = 0;
	while (text[i] != '\0' && text[i+1] != '\0')
	{
		if(x < width && x > 0)//��ֹ���Ǳ߿�
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


//=================��Ȧʽ����logo=================
//���ܣ� ��Ȧʽ����logo
//�÷��� _logo3(���ھ��,�߿���,�߿�߶�,��ʼx����,��ʼy����,�ı�����,�ı��߶�����)
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


//================���ɱ߿�(��Ȧʽ)================
//���ܣ� ����Ļ�����ֻ��Ƴ�һ���߿� 
//�÷��� _creatFrame(���ھ��,�߿򳤶�,�߿�߶�,���Ƽ��)
//================================================  
void _creatFrame(HANDLE Stdout,int width,int height,int left, int top,int sleepTime)
{    
	int i;   
	//==========��========== 
	_print(Stdout,left,top,"��");
	for (i=2;i<=width-4;i+=2)
	{
		_print(Stdout,left+i,top,"��");
		Sleep(sleepTime);
	}
	_print(Stdout,left+width-2,top,"��");

	//==========��========== 
	for (i=1;i<=height-2;i++)
	{
		_print(Stdout,left+width-2,top+i,"��");
		Sleep(sleepTime);
	}

	//==========��==========
	_print(Stdout,left+width-2,top+height-1,"��");
	for (i=width-4;i>=2;i-=2)
	{
		_print(Stdout,left+i,top+height-1,"��");
		Sleep(sleepTime);
	}
	_print(Stdout,left,top+height-1,"��");

	//==========��========== 
	for (i=height-2;i>=1;i--)
	{
		_print(Stdout,left,top+i,"��");
		Sleep(sleepTime);
	} 

}


//================ɾ���߿�(��Ȧʽ)================
//���ܣ� �����Ļ�ϻ��Ƴ��ı߿�(ԭ��ͬ����һ��) 
//�÷��� _deleteFrame(�߿򳤶�,�߿�߶�,���Ƽ��)
//ע�⣺ �߿�ĸ߶Ⱥͳ���Ҫ����Ƶ�һ�� 
//================================================
void _deleteFrame(HANDLE Stdout,int width,int height,int left, int top,int sleepTime)
{

	//==========��==========     
	int k;
	for (k=1;k<=height;k++)
	{
		_print(Stdout,left,top+k,"  ");
		Sleep(sleepTime);
	}

	//==========��==========     
	for (k=2;k<=width;k+=2)
	{
		_print(Stdout,left+k,top+height-1,"  ");
		Sleep(sleepTime);
	}

	//==========��==========     
	for (k=height-2;k>=0;k--)
	{
		_print(Stdout,left+width-2,top+k,"  ");
		Sleep(sleepTime);
	}

	//==========��==========     
	for (k=width-4;k>=0;k-=2)
	{
		_print(Stdout,left+k,top,"  ");
		Sleep(sleepTime);
	}

}


//==========��Ȧʽ����logo_�����������===========
//���ܣ� �ڴ��ڵ�����һ�о�������ı� 
//�÷��� _logo3_draw(���ھ��,x����,y����,����ַ���)
//================================================
void _logo3_draw(HANDLE Stdout,int width,int y, int left, int top, char* text)
{
	int length=0,x=1;
	length = strlen(text);
	x = (width - length) / 2;
	_print(Stdout, left+x-1, top+y-1, text);
}


//====================�������====================
//���ܣ� �ڴ��ڵ�����������ı� 
//�÷��� _print(���ھ��,x����,y����,����ַ���)
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