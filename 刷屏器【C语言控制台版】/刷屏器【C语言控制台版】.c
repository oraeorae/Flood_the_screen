/*
���� ������ 2783608988      C������Դ����Ⱥ 519536269


������ؼ� ���������������� 
void Start_send_messages(void);			//ģ�ⰴ��������Ϣ 
void SetClipBoardText(char * message);	//�ü������ı� 
ֻҪ�Լ����� ��Ҳ��������ˢ���� ������ѭ���� 

������󲿷�������Ч��    ��ʵ��������ˢ���Ĵ������������������ 

*/


/*		ͷ�ļ�		*/
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

/*		��������		*/
void main_mean(int show);				//���˵� 
void gotoxy(int x,int y);				//��굽ָ��λ�� 
void Start_send_messages(void);			//ģ�ⰴ��������Ϣ 
void a_word_printf(char * a, int time); //���ֽ��� 
void SetClipBoardText(char * message);	//�ü������ı� 

/*		ȫ�ֱ���		*/
int interval = 1000;		//ʱ����
char * text = NULL;			//ˢ������ 

int main(void)
{
	int location = 1 ,setup ;		//ѡ��,�����Ƿ�ɹ� 
	
	system("title ˢ��������C���Կ���̨�桿");			//�ı䴰�ڱ���
	system("mode con: cols=38 lines=24");				//���ô��ڴ�С
	
	
	/*				���ع��			*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	//��ñ�׼����豸���
	CONSOLE_CURSOR_INFO cci;							//��������Ϣ�ṹ�� 
	GetConsoleCursorInfo(hConsole, &cci);				//��õ�ǰ�����Ϣ 
	cci.bVisible = 0;  									//Ϊ0ʱ��겻�ɼ�
	SetConsoleCursorInfo(hConsole, &cci);
	
	main_mean(1);		//��ʾ���˵� 
	
	while(1)	//��ѭ�� 
	{
		switch(getch())
		{
			case 'W':case 'w':
				location--;
				if( location == 0 )
				{
					location++;
				}	
				else if( location == 1 )
				{
					/* ��������ѡ��ۼ� */
					gotoxy(8,4);
					printf("��"); 
					/* ����ϴ�ѡ��ۼ� */
					gotoxy(8,7);
					printf("  "); 
				}
				else if( location == 2 )
				{
					/* ��������ѡ��ۼ� */
					gotoxy(8,7);
					printf("��"); 
					/* ����ϴ�ѡ��ۼ� */
					gotoxy(8,10);
					printf("  "); 
				}
				else if( location == 3 )
				{
					/* ��������ѡ��ۼ� */
					gotoxy(8,10);
					printf("��"); 
					/* ����ϴ�ѡ��ۼ� */
					gotoxy(8,13);
					printf("  "); 
				}
				break;
			
			case 'S':case 's':
				location++;
				if( location == 2 )
				{
					/* ��������ѡ��ۼ� */
					gotoxy(8,7);
					printf("��"); 
					/* ����ϴ�ѡ��ۼ� */
					gotoxy(8,4);
					printf("  "); 
				}
				else if( location == 3 )
				{
					/* ��������ѡ��ۼ� */
					gotoxy(8,10);
					printf("��"); 
					/* ����ϴ�ѡ��ۼ� */
					gotoxy(8,7);
					printf("  "); 
				}
				else if( location == 4 )
				{
					/* ��������ѡ��ۼ� */
					gotoxy(8,13);
					printf("��");
					/* ����ϴ�ѡ��ۼ� */ 
					gotoxy(8,10);
					printf("  "); 
				}
				else if( location == 5 )
				{
					location--;
				}	
				break;
			
			case 13:
				//���뵱ǰѡ�� 		�س���:VK_RETURN (13)  
				
				main_mean(0);//��ʾ���� 
			
			if( location == 1 )			/*	ѡ�����ˢ�����ڡ�	*/ 
			{	
				printf("������ˢ������(��λ������)��"); 
				scanf_s("%d%*c",&interval);
				setup = 1;	//���óɹ�
			}
			else if( location == 2 )	/*	ѡ�����ˢ�����ݡ�	*/
			{
				int word_number;    //�ַ������� 
			
				printf("\n������ˢ�����ݵĴ��������");
				scanf_s("%d",&word_number);
			
				text = (char *)malloc(word_number*2);	 //�ַ����ı� 
				printf("\n������ˢ�����ݣ�");
				scanf_s("%s",text);	
				setup = 1;	//���óɹ� 
		
			}
			else if( location == 3 )	/*	ѡ�������ʼˢ����	*/
			{
				char ch;
				printf("�������Ƿ������ı���"
			    	   "     ��     ��    ");
			    /* �����ۼ� */
				gotoxy(22,3);
				printf("��"); 
				location = 'l';
				
				ch = getch();
				
				while( ch != 13 )  	//�ж��û��Ƿ���ȷ�� 
				{
					switch(ch)
					{
					case 'A':case'a':
						location = 'l';
						/* ����ϴ�ѡ��ۼ� */
						gotoxy(29,3);
						printf("  ");
						/* ��������ѡ��ۼ� */
						gotoxy(22,3);
						printf("��"); 
					break; 
					
					case 'D':case 'd':
						location = 'r';
						/* ����ϴ�ѡ��ۼ� */
						gotoxy(22,3);
						printf("  "); 
						/* ��������ѡ��ۼ� */
						gotoxy(29,3);
						printf("��"); 
					break;			
					}
					ch = getch();
				} 
				 if( location == 'r' ) 	//ѡ���Ƿ��м������ı�������
				{
					if( text != NULL )	//�ж��Ƿ�������ˢ���ı� 
					{
						SetClipBoardText(text); 
					}
					else
					{
						gotoxy(0,5);
						printf("δ����ˢ������ ����������"); 
						setup = 0 ; //���ò��ɹ� 
						break;	//����switch 
					} 
				}
				printf("\n\n�Ƿ�ʼˢ����      "
					 "     ��     ��    ");
		 		/* �����ۼ�	*/
				gotoxy(22,5);
				printf("��");
				location = 'l';
				
				ch = getch();
				
				while( ch != 13 )  	//�ж��û��Ƿ���ȷ�� 
				{
					switch(ch)
					{
					case 'A':case'a':
						location = 'l';
						/* ����ϴ�ѡ��ۼ� */
						gotoxy(29,5);
						printf("  ");
						/* ��������ѡ��ۼ� */
						gotoxy(22,5);
						printf("��"); 
					break; 
					
					case 'D':case 'd':
						location = 'r';
						/* ����ϴ�ѡ��ۼ� */
						gotoxy(22,5);
						printf("  "); 
						/* ��������ѡ��ۼ� */
						gotoxy(29,5);
						printf("��"); 
					break;			
					}
					ch=getch();
				}
				
				if( location == 'l' ) 		//ѡ���Ƿ�ʼˢ�������ǡ� 
				{
					system("cls");
	 				main_mean(0);			//��ʾ���� 
					int time;	
					for( time = 10 ; time >= 0 ; time-- )
					{


						if( time == 10 )
						{
							gotoxy(12, 10);
							printf("10���ʼˢ��");
						}
					Sleep(1000);
					gotoxy(12, 10);
					printf("%d���ʼˢ��",time);
					}
					while(1)
					{
						if(_kbhit())		// ��鵱ǰ�Ƿ��м�������
						{
							break; //����whileѭ�� 
						}
							Sleep(interval);
							Start_send_messages();
					}
				}
				else						//ѡ���Ƿ�ʼˢ�������� 
				{
					setup = 0;	 
				} 
		
			} 
			else if( location == 4 )	/*	ѡ���ʹ��˵��	*/
			{
				a_word_printf("�񱾳����ɰ���������[C���Կ���̨��]����ʵ�ڴ�֮ǰ���Ѿ�����ˢ�����Ĵ�"
			  "�ڰ�,Ϊ�˷����ѧ��ѧϰ������������̨���.����ҪԴ���С�����Լ���QQ:"
			  "27836089 88  ���� C������Դ����Ⱥ 519536269 .\n\n"
			  "ʹ��˵����ˢ��ʱ�䡪��ÿ���������һ��ˢ����1��=1000���룩��Ĭ����1000"
			  "����.\n��ʼˢ�������ɹ�������Ϻ��뽫����Ƶ���Ҫˢ���Ĵ��ڣ�10�����"
			  "�󽫿�ʼ�Զ�ˢ��.\n" 	
				,50); 
			}
			
			
			SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_INTENSITY); //���ÿ���̨������ɫ
			gotoxy(0,16);
			if( setup == 1 )
			{
				printf("======================================\n��ʾ��\n\n      ���óɹ�����������������˵�");
			}
			else if( setup == 0 )
			{
				printf("======================================\n��ʾ��\n\n         sss��������������˵�");
			}
			getch(); 
			main_mean(1);
			location = 1; 
			
			break; 
		 } //switch 
		
	}//while 
	
	return 0;
 } 




/*
================================================= 
���������ã���ʾ���� 
����1���Ƿ���ʾ�˵���Ϊ1��ʾ���� ��Ϊ1ֻ��ʾ���ƣ� 
================================================= 
*/
 void main_mean(int show)
 {
 	system("cls");    //���� 		
	gotoxy(0,0); 
 	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY); //���ÿ���̨������ɫ 
	printf( "                                  \n"
			"   ������ˢ��������C���Կ���̨�桿\n"
		    "                                  \n"); 
	int line;
	for( line = 0 ; line < 5 ; line++ ) 
	{
		if( show == 1 )
		{
		SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY|COMMON_LVB_GRID_HORIZONTAL); //���ÿ���̨������ɫ 
		printf( "                                     \n" );
		SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //���ÿ���̨������ɫ
		
		
		if( line == 0 )
		{
			if( interval != 1000 )
			{
				printf("             ˢ�����ڡ��           \n");
			}
			else
			{
				printf("             ˢ�����ڡ�Ĭ��           \n");
			}
		}
		else if( line == 1 )		
		{ 
			if( text == NULL )
			{
				printf("             ˢ�����ݡ��ա�           \n");
			}
			else
			{
				printf("             ˢ�����ݡ��           \n");
			}
		
		} 
		else if( line == 2 )	
		{ 
			printf("               ��ʼˢ��               \n" );
		} 
		else if( line == 3 )	
		{ 
			printf("               ʹ��˵��               \n");
		} 
 
		}
	}
	
	
	if( show == 1 )
	{
		
	/*		�����ʾ��ʾ	*/
	SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_INTENSITY); //���ÿ���̨������ɫ
	srand((unsigned)time(NULL));							//���������	 
	gotoxy(0,16);
	int tips = ( rand() % 7 ) + 1;
	if( tips == 1 ) 
	{
		printf("======================================\n                С��ʾ\n\n           ���ˢ������̫��\n      ���ܻ���ɵ��Կ�����ʧ��");
	}
	else if( tips == 2 ) 
	{
		printf("======================================\n                С��ʾ\n\n            1000����=1�룡\n      Ĭ�ϵ�ˢ��������1000����Ŷ");
	}
	else if( tips == 3 ) 
	{
		printf("======================================\n                С��ʾ\n\n          ����QQ 2783608988\n        �����ʵ�С�����Լ�Q");
	}
	else if( tips == 4 ) 
	{
		printf("======================================\n                С��ʾ\n\n            �����ʼˢ����\n      ��ѹ���Ƶ���Ҫˢ���Ĵ���");
	}
	else if( tips == 5 ) 
	{
		printf("======================================\n                С��ʾ\n\n        ������ʹ��C��������\n        ��ȫ�޶� �����ʹ��");
	}
	else if( tips == 6 ) 
	{
		printf("======================================\n                С��ʾ\n\n         ���������ڿ���̨��\n        ��Ҫ���ڰ�Ŀ��Լ���Q");
	}
	else if( tips == 7 ) 
	{
		printf("======================================\n                С��ʾ\n\n �����ˢͼƬ,���Ը�����Ҫˢ����ͼƬ\n Ȼ��ѡ���Ƿ��м������ı������ǡ�");
	} 
	
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //���ÿ���̨������ɫ
 	gotoxy(8,4);
	printf("��"); 
	}
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //���ÿ���̨������ɫ

 	return;
 }
 
/*
======================================= 
���������ã�ģ�ⰴ���ﵽ������Ϣ��Ŀ�� 
ԭ���������еļ����ı�����ģ�ⰴ����
Ctrl+V[ճ��]
QQ�����ַ��Ϳ�ݼ���Ctrl+Enter��Enter
======================================= 
*/
 void Start_send_messages(void)
 {
 	/*
	
	*/
		keybd_event(0x11,0,0,0);					//����ctrl��
		keybd_event(86,0,0,0);						//����V��
		keybd_event(86,0,KEYEVENTF_KEYUP,0);		//�ɿ�v��
		keybd_event(0x11,0,KEYEVENTF_KEYUP,0);		//�ɿ�ctrl��
		keybd_event(0x11,0,0,0);					//����ctrl��
		keybd_event(0xD,0,0,0);						//����Enter��
		keybd_event(0xD,0,KEYEVENTF_KEYUP,0);		//�ɿ�Enter����
		keybd_event(0x11,0,KEYEVENTF_KEYUP,0);		//�ɿ�ctrl��
		keybd_event(0xD,0,0,0);						//����Enter��
		keybd_event(0xD,0,KEYEVENTF_KEYUP,0);		//�ɿ�Enter��
 	
 	return; 
 } 
 
 
 
 
 /*
==================================== 
���������ã����ַ���һ��һ��������ʾ
�����ͣ����������
����1����Ҫ������ʾ���ַ�
����2��ÿ����ʾ��ʱ����
==================================== 
*/
void a_word_printf(char * a, int time)						//��������
{
	int i ;
	for (i = 0; a[i] != '\0'; i++)
	{
		printf("%c", a[i]);
		Sleep(time);
	}

	return;
}


/*
======================================= 
���������ã���굽ָ��λ�� 
����1��ָ����x
����2��ָ����y
����3��1��ʾASCLL�� 2��ʾ��ʾ��ASCLL�� 
======================================= 
*/
void gotoxy(int x, int y)								//��굽ָ��λ�� 
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//��ñ�׼��������ľ��
	COORD pos = { x,y };										//��ʾһ���ַ��ڿ���̨��Ļ�ϵ�����(ASCLL����Ϊ1 ��ASCLL����Ϊ2)
	SetConsoleCursorPosition(hOut, pos);				    //��궨λ�ڶ�Ӧ��λ��	
	return;
}


/*
==================================== 
���������ã��ü������ı�
����1 :׼�������������ı�(�ַ���)
==================================== 
*/
void SetClipBoardText(char *message)
{
	HGLOBAL hMemory;
	LPTSTR lpMemory;
	OpenClipboard(NULL);	//�򿪼��а�
	EmptyClipboard();		// ��ռ��а�
	hMemory = GlobalAlloc(GMEM_MOVEABLE, strlen(message) + 1);
	// �Լ��а�����ڴ�
	lpMemory = (LPTSTR)GlobalLock(hMemory);
	// ���ڴ���������
	memcpy(lpMemory, message, strlen(message) + 1);   /*���� memcpy_s(lpMemory, contentSize, content, contentSize);*/
	// �����ݸ��ƽ����ڴ����� 
	GlobalUnlock(hMemory);                  // ����ڴ�����
	SetClipboardData(CF_TEXT, hMemory);
	CloseClipboard();								//�رռ��а�
	return; 
}

