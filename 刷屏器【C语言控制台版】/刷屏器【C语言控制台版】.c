/*
作者 奥利奥 2783608988      C语言资源共享群 519536269


本程序关键 （下面两个函数） 
void Start_send_messages(void);			//模拟按键发送信息 
void SetClipBoardText(char * message);	//置剪辑版文本 
只要稍加利用 就也可以做出刷屏器 （利用循环） 

本程序大部分是在做效果    其实真正用来刷屏的代码就是上面两个函数 

*/


/*		头文件		*/
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

/*		声明函数		*/
void main_mean(int show);				//主菜单 
void gotoxy(int x,int y);				//光标到指定位置 
void Start_send_messages(void);			//模拟按键发送信息 
void a_word_printf(char * a, int time); //文字渐显 
void SetClipBoardText(char * message);	//置剪辑版文本 

/*		全局变量		*/
int interval = 1000;		//时间间隔
char * text = NULL;			//刷屏内容 

int main(void)
{
	int location = 1 ,setup ;		//选项,设置是否成功 
	
	system("title 刷屏神器【C语言控制台版】");			//改变窗口标题
	system("mode con: cols=38 lines=24");				//设置窗口大小
	
	
	/*				隐藏光标			*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	//获得标准输出设备句柄
	CONSOLE_CURSOR_INFO cci;							//定义光标信息结构体 
	GetConsoleCursorInfo(hConsole, &cci);				//获得当前光标信息 
	cci.bVisible = 0;  									//为0时光标不可见
	SetConsoleCursorInfo(hConsole, &cci);
	
	main_mean(1);		//显示主菜单 
	
	while(1)	//死循环 
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
					/* 画出本次选择痕迹 */
					gotoxy(8,4);
					printf("●"); 
					/* 清除上次选择痕迹 */
					gotoxy(8,7);
					printf("  "); 
				}
				else if( location == 2 )
				{
					/* 画出本次选择痕迹 */
					gotoxy(8,7);
					printf("●"); 
					/* 清除上次选择痕迹 */
					gotoxy(8,10);
					printf("  "); 
				}
				else if( location == 3 )
				{
					/* 画出本次选择痕迹 */
					gotoxy(8,10);
					printf("●"); 
					/* 清除上次选择痕迹 */
					gotoxy(8,13);
					printf("  "); 
				}
				break;
			
			case 'S':case 's':
				location++;
				if( location == 2 )
				{
					/* 画出本次选择痕迹 */
					gotoxy(8,7);
					printf("●"); 
					/* 清除上次选择痕迹 */
					gotoxy(8,4);
					printf("  "); 
				}
				else if( location == 3 )
				{
					/* 画出本次选择痕迹 */
					gotoxy(8,10);
					printf("●"); 
					/* 清除上次选择痕迹 */
					gotoxy(8,7);
					printf("  "); 
				}
				else if( location == 4 )
				{
					/* 画出本次选择痕迹 */
					gotoxy(8,13);
					printf("●");
					/* 清除上次选择痕迹 */ 
					gotoxy(8,10);
					printf("  "); 
				}
				else if( location == 5 )
				{
					location--;
				}	
				break;
			
			case 13:
				//进入当前选项 		回车键:VK_RETURN (13)  
				
				main_mean(0);//显示标题 
			
			if( location == 1 )			/*	选项——【刷屏周期】	*/ 
			{	
				printf("请输入刷屏周期(单位：毫秒)："); 
				scanf_s("%d%*c",&interval);
				setup = 1;	//设置成功
			}
			else if( location == 2 )	/*	选项——【刷屏内容】	*/
			{
				int word_number;    //字符串字数 
			
				printf("\n请输入刷屏内容的大概字数：");
				scanf_s("%d",&word_number);
			
				text = (char *)malloc(word_number*2);	 //字符串文本 
				printf("\n请输入刷屏内容：");
				scanf_s("%s",text);	
				setup = 1;	//设置成功 
		
			}
			else if( location == 3 )	/*	选项——【开始刷屏】	*/
			{
				char ch;
				printf("剪辑版是否已有文本？"
			    	   "     是     否    ");
			    /* 画出痕迹 */
				gotoxy(22,3);
				printf("●"); 
				location = 'l';
				
				ch = getch();
				
				while( ch != 13 )  	//判断用户是否点击确定 
				{
					switch(ch)
					{
					case 'A':case'a':
						location = 'l';
						/* 清除上次选择痕迹 */
						gotoxy(29,3);
						printf("  ");
						/* 画出本次选择痕迹 */
						gotoxy(22,3);
						printf("●"); 
					break; 
					
					case 'D':case 'd':
						location = 'r';
						/* 清除上次选择痕迹 */
						gotoxy(22,3);
						printf("  "); 
						/* 画出本次选择痕迹 */
						gotoxy(29,3);
						printf("●"); 
					break;			
					}
					ch = getch();
				} 
				 if( location == 'r' ) 	//选择【是否有剪辑版文本——否】
				{
					if( text != NULL )	//判断是否设置完刷屏文本 
					{
						SetClipBoardText(text); 
					}
					else
					{
						gotoxy(0,5);
						printf("未设置刷屏内容 请重新设置"); 
						setup = 0 ; //设置不成功 
						break;	//结束switch 
					} 
				}
				printf("\n\n是否开始刷屏？      "
					 "     是     否    ");
		 		/* 画出痕迹	*/
				gotoxy(22,5);
				printf("●");
				location = 'l';
				
				ch = getch();
				
				while( ch != 13 )  	//判断用户是否点击确定 
				{
					switch(ch)
					{
					case 'A':case'a':
						location = 'l';
						/* 清除上次选择痕迹 */
						gotoxy(29,5);
						printf("  ");
						/* 画出本次选择痕迹 */
						gotoxy(22,5);
						printf("●"); 
					break; 
					
					case 'D':case 'd':
						location = 'r';
						/* 清除上次选择痕迹 */
						gotoxy(22,5);
						printf("  "); 
						/* 画出本次选择痕迹 */
						gotoxy(29,5);
						printf("●"); 
					break;			
					}
					ch=getch();
				}
				
				if( location == 'l' ) 		//选择【是否开始刷屏——是】 
				{
					system("cls");
	 				main_mean(0);			//显示标题 
					int time;	
					for( time = 10 ; time >= 0 ; time-- )
					{


						if( time == 10 )
						{
							gotoxy(12, 10);
							printf("10秒后开始刷屏");
						}
					Sleep(1000);
					gotoxy(12, 10);
					printf("%d秒后开始刷屏",time);
					}
					while(1)
					{
						if(_kbhit())		// 检查当前是否有键盘输入
						{
							break; //结束while循环 
						}
							Sleep(interval);
							Start_send_messages();
					}
				}
				else						//选择【是否开始刷屏——否】 
				{
					setup = 0;	 
				} 
		
			} 
			else if( location == 4 )	/*	选项——使用说明	*/
			{
				a_word_printf("●本程序由奥利奥制作[C语言控制台版]，其实在此之前我已经做过刷屏器的窗"
			  "口版,为了方便初学者学习，才做出控制台版的.有需要源码的小伙伴可以加我QQ:"
			  "27836089 88  或者 C语言资源共享群 519536269 .\n\n"
			  "使用说明：刷屏时间——每几毫秒进行一次刷屏（1秒=1000毫秒），默认是1000"
			  "毫秒.\n开始刷屏——成功设置完毕后，请将鼠标移到所要刷屏的窗口，10秒结束"
			  "后将开始自动刷屏.\n" 	
				,50); 
			}
			
			
			SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_INTENSITY); //设置控制台字体颜色
			gotoxy(0,16);
			if( setup == 1 )
			{
				printf("======================================\n提示：\n\n      设置成功，按任意键返回主菜单");
			}
			else if( setup == 0 )
			{
				printf("======================================\n提示：\n\n         sss按任意键返回主菜单");
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
本函数作用：显示界面 
参数1：是否显示菜单（为1显示界面 不为1只显示名称） 
================================================= 
*/
 void main_mean(int show)
 {
 	system("cls");    //清屏 		
	gotoxy(0,0); 
 	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY); //设置控制台字体颜色 
	printf( "                                  \n"
			"   奥利奥刷屏神器【C语言控制台版】\n"
		    "                                  \n"); 
	int line;
	for( line = 0 ; line < 5 ; line++ ) 
	{
		if( show == 1 )
		{
		SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY|COMMON_LVB_GRID_HORIZONTAL); //设置控制台字体颜色 
		printf( "                                     \n" );
		SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //设置控制台字体颜色
		
		
		if( line == 0 )
		{
			if( interval != 1000 )
			{
				printf("             刷屏周期【★】           \n");
			}
			else
			{
				printf("             刷屏周期【默】           \n");
			}
		}
		else if( line == 1 )		
		{ 
			if( text == NULL )
			{
				printf("             刷屏内容【空】           \n");
			}
			else
			{
				printf("             刷屏内容【★】           \n");
			}
		
		} 
		else if( line == 2 )	
		{ 
			printf("               开始刷屏               \n" );
		} 
		else if( line == 3 )	
		{ 
			printf("               使用说明               \n");
		} 
 
		}
	}
	
	
	if( show == 1 )
	{
		
	/*		随机显示提示	*/
	SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_INTENSITY); //设置控制台字体颜色
	srand((unsigned)time(NULL));							//随机数种子	 
	gotoxy(0,16);
	int tips = ( rand() % 7 ) + 1;
	if( tips == 1 ) 
	{
		printf("======================================\n                小提示\n\n           如果刷屏周期太短\n      可能会造成电脑卡或发送失败");
	}
	else if( tips == 2 ) 
	{
		printf("======================================\n                小提示\n\n            1000毫秒=1秒！\n      默认的刷屏周期是1000毫秒哦");
	}
	else if( tips == 3 ) 
	{
		printf("======================================\n                小提示\n\n          作者QQ 2783608988\n        有疑问的小伙伴可以加Q");
	}
	else if( tips == 4 ) 
	{
		printf("======================================\n                小提示\n\n            点击开始刷屏后\n      请把光标移到所要刷屏的窗口");
	}
	else if( tips == 5 ) 
	{
		printf("======================================\n                小提示\n\n        本程序使用C语言制作\n        安全无毒 请放心使用");
	}
	else if( tips == 6 ) 
	{
		printf("======================================\n                小提示\n\n         本程序属于控制台版\n        需要窗口版的可以加我Q");
	}
	else if( tips == 7 ) 
	{
		printf("======================================\n                小提示\n\n 如果想刷图片,可以复制所要刷屏的图片\n 然后选择【是否有剪辑板文本——是】");
	} 
	
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //设置控制台字体颜色
 	gotoxy(8,4);
	printf("●"); 
	}
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); //设置控制台字体颜色

 	return;
 }
 
/*
======================================= 
本函数作用：模拟按键达到发送信息的目的 
原理：利用已有的剪辑文本进行模拟按键，
Ctrl+V[粘贴]
QQ的两种发送快捷键：Ctrl+Enter和Enter
======================================= 
*/
 void Start_send_messages(void)
 {
 	/*
	
	*/
		keybd_event(0x11,0,0,0);					//按下ctrl键
		keybd_event(86,0,0,0);						//按下V键
		keybd_event(86,0,KEYEVENTF_KEYUP,0);		//松开v键
		keybd_event(0x11,0,KEYEVENTF_KEYUP,0);		//松开ctrl键
		keybd_event(0x11,0,0,0);					//按下ctrl键
		keybd_event(0xD,0,0,0);						//按下Enter键
		keybd_event(0xD,0,KEYEVENTF_KEYUP,0);		//松开Enter键　
		keybd_event(0x11,0,KEYEVENTF_KEYUP,0);		//松开ctrl键
		keybd_event(0xD,0,0,0);						//按下Enter键
		keybd_event(0xD,0,KEYEVENTF_KEYUP,0);		//松开Enter键
 	
 	return; 
 } 
 
 
 
 
 /*
==================================== 
本函数作用：让字符串一字一字慢慢显示
【类型：输出函数】
参数1：所要慢慢显示的字符
参数2：每次显示的时间间隔
==================================== 
*/
void a_word_printf(char * a, int time)						//渐显文字
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
本函数作用：光标到指定位置 
参数1：指定列x
参数2：指定行y
参数3：1表示ASCLL码 2表示表示非ASCLL码 
======================================= 
*/
void gotoxy(int x, int y)								//光标到指定位置 
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//获得标准输入输出的句柄
	COORD pos = { x,y };										//表示一个字符在控制台屏幕上的坐标(ASCLL码宽度为1 非ASCLL码宽度为2)
	SetConsoleCursorPosition(hOut, pos);				    //光标定位在对应的位置	
	return;
}


/*
==================================== 
本函数作用：置剪辑板文本
参数1 :准备置入剪辑板的文本(字符串)
==================================== 
*/
void SetClipBoardText(char *message)
{
	HGLOBAL hMemory;
	LPTSTR lpMemory;
	OpenClipboard(NULL);	//打开剪切板
	EmptyClipboard();		// 清空剪切板
	hMemory = GlobalAlloc(GMEM_MOVEABLE, strlen(message) + 1);
	// 对剪切板分配内存
	lpMemory = (LPTSTR)GlobalLock(hMemory);
	// 将内存区域锁定
	memcpy(lpMemory, message, strlen(message) + 1);   /*或者 memcpy_s(lpMemory, contentSize, content, contentSize);*/
	// 将数据复制进入内存区域 
	GlobalUnlock(hMemory);                  // 解除内存锁定
	SetClipboardData(CF_TEXT, hMemory);
	CloseClipboard();								//关闭剪切板
	return; 
}

