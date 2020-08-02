  
/*
  这个程序只是闲来无事写着玩的，可能还有很多BUG没有发现，如果你在代码运行过程中发现了bug或error可以联系我改一下。
  本来打算是在一千行内写完的，结果写着写着就失控了，直接堆到了1700多行（无奈），也是学艺不精，很多地方使用了简单
且冗长的结构让人贻笑大方，不过总归是第一次写自己的程序，后面想到更好的结构也会改进的。*/ 

//头文件区 
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h> 
#include<stdlib.h>

//菜单函数区 
void title();//过度界面 
void menu1();//主菜单 
void menu2();//会员管理菜单
void menu3();//管理员登录菜单  
 
//工具函数区 
void transit();//过度函数 
void goto_xy(int,int);//光标移动函数 
void draw_member();//画空白半框函数
void draw_query();//画空白框函数 
void draw_book();//画书籍信息框 
void draw_memberinfor();//画会员信息框 
void draw_sign();//画注册会员框 
int member_sign();//注册会员函数 

//会员信息层函数
int member_login(char number[15]); 
void lend_book(char ar[],char ad[]);//借书登记函数 
int member_possword(char ar[]);//密码比对函数 
int query_book(char ar[]);//查找图书函数 
void return_book(char ar[],char ad[]);//书籍归还函数 
void member_information(char ar[]);//查询个人信息函数 
void revise_infor(char ar[]);//修改个人信息函数 
void print_library();//打印所有书籍信息函数

//管理员信息层信息 
void admin_system();//管理员登录函数 
int query_member(char ar[]);//查找会员函数
void change_book();//书籍修改函数 
void add_book();//增添书籍函数 
void delete_book();//删除书籍函数 
void draw_memberinfor1();//会员信息框函数 
void print_member();//打印所有会员信息函数 
void delete_member();//删除会员信息函数 
void print_borrow();//打印所有借阅信息函数 
void draw_borrow();//借阅信息框 函数 
int admin_borrow();//管理借阅信息函数 

//宏定义区
#define ADMIN_password "12345"//管理员登录密码 

//结构体声明区
typedef struct library_book//系统中的图书信息
{
	char ID[15];//图书编号 
	char name[30];//书籍名称 
	char writer[20];//书籍作者
	char position[15];//书籍存放地点 
	char type[10];//书籍类型
	int quantity;//馆内总收藏量 
	int lend;//已借出数量 
}LIBRARY_BOOK; 

typedef struct lend/*会员借出的书籍信息*/ 
{
	char number[15];//图书编号
    char name[20];//书籍名称
    char writer[20];//作者
    char type[10]; //书籍类型 
 	char account[30];//借书者ID
}LEND;

typedef struct member//会员个人信息 
{
	char name[15];//会员用户名 
	char ID[15]; //会员登录账号
	char password[15];//会员登录密码
	char sex[5];//会员性别 
	int old_year;//会员年龄 
	char password_key[20]; //找回密码的密保  
}MEMBER;



 
int main()
{
	FILE *w1,*w2,*w3;
	char choose1,choose2,choose3;
	system("title *gzhmt能动182  黄志睿*");
	int flag=0,flag1,flag2,mark=1,decide;
	
	if((w1=fopen("library.txt","r"))==NULL)//w1是书籍信息文件指针 
	{
		w1=fopen("library.txt","w");
		fclose(w1);
	}
	if((w2=fopen("information.txt","r"))==NULL)//w2是会员个人信息文件指针 
	{
		w2=fopen("information.txt","w");
		fclose(w2);
	}
	if((w3=fopen("borrow.txt","r"))==NULL)//w3是会员借阅书籍的图书信息指针 
	{
		w3=fopen("borrow.txt","w");
		fclose(w3);
	}
	
	transit();//加载画面的过渡程序 
	while(mark) 
	{
		system("cls");
		menu1();
		printf("请选择1~4：");
		choose1='0';
		fflush(stdin);
		choose1=getche();
		while(choose1!='1'&&choose1!='2'&&choose1!='3'&&choose1!='4')//判断输入是否为1-4
			choose1=getche();
		fflush(stdin);
		flag=0;
		switch(choose1)
		{
			case '1':
				while(flag==0)
				{
					system("cls");
					char member_account[15]={0},acc;
					int i=0;
					draw_member();
					goto_xy(40,7);
					printf("登录账号：");
					fflush(stdin);			
					while((acc=getch())!=13)//未输入回车时循环 
					{
						if(acc==27)//esc键退出 
							break;
						if(acc==8)//输入退格符时清除前一个数 
						{
							printf("\b \b");
							i--;
						}
						if(acc!=8)
						{
							member_account[i]=acc;
							putchar(acc);
							i++;
						}
					}
				if(acc==27)//esc键退出 
					break;		
				else 
					flag=member_login(member_account);//账号登陆函数 
				if(flag==2)
					mark=1;
				while(flag==1)
				{
					flag1=1;
					system("cls");
					menu2();
					printf("请选择1~6");
					fflush(stdin);	
					choose2=getche();
					while(choose1!='1'&&choose1!='2'&&choose1!='3'&&choose1!='4'&&choose1!='5'&&choose1!='6')//判断输入是否为1-6
						choose2=getche();
					fflush(stdin);
					switch(choose2)
					{
						case '1'://查询书籍 
							while(flag1)
							{	
								i=0;
								char book_query[30]={0},input;
								draw_query();
								goto_xy(35, 8);
								printf("请输入查询书籍名称或ID：");
								fflush(stdin);
								gets(book_query);
	
					flag2=query_book(book_query);
					if(flag2==0)
					{
						printf("查询失败，请按任意键后重试...");
						getch();
					}
					if(flag2==1)	
					{
						printf("\n您需要借出此书吗？Y/N\n"); 
						fflush(stdin);
						flag2=getche();
						while(flag2!='Y'&&flag2!='y'&&flag2!='N'&&flag2!='n')//判断输入是否为y或n 
      				    	flag2=getch();
						if(flag2=='Y'||flag2=='y')
						{
							lend_book(book_query,member_account);
							printf("\n继续查询请按 Y ,结束请按 N\n");
						}
						if(flag2=='n'||flag2=='N')
							printf("\n继续查询请按 Y ,结束请按 N\n");
							
						fflush(stdin);
						input=getch();
						while(input!='Y'&&input!='y'&&input!='N'&&input!='n')
      				    	input=getch();
						if(input=='y'||input=='Y')
							flag1=1;
						else
							flag1=0;
					}
							}
							break;
						case '2':
							while(flag1)//借出书籍 
							{
								char book_name[30],input;
								draw_query();
								goto_xy(35, 8);
								printf("书籍编号/书名：");
								fflush(stdin);
								gets(book_name);
								lend_book(book_name,member_account);
								printf("\n继续借书请按 Y ,结束请按 N\n");
								fflush(stdin);
								input=getch();
								while(input!='Y'&&input!='y'&&input!='N'&&input!='n')
      						    	input=getch();
								if(input=='y'||input=='Y')
									flag1=1;
								else
									flag1=0;
							}
							break;
						case '3'://书籍归还 
							while(flag1)
							{
								char book_return[30],input;
								draw_query();
								goto_xy(36, 8);
								printf("请输入归还书籍编号：");
								fflush(stdin);
								gets(book_return);
								return_book(book_return,member_account);
								printf("\n继续还书请按 Y ,结束请按 N\n");
								fflush(stdin);
								input=getch();
								while(input!='Y'&&input!='y'&&input!='N'&&input!='n')
      						    	input=getch();
								if(input=='y'||input=='Y')
									flag1=1;
								else
									flag1=0;
							 } 
							break;
						case '4'://查询账号信息
							while(flag1)
							{
								char input;
								member_information(member_account);
								printf("\n\n\n是否需要修改个人信息，Y修改，N退出。\nY/N\n");
								fflush(stdin);
								input=getch();
								while(input!='Y'&&input!='y'&&input!='N'&&input!='n')
      						    	input=getch();
								if(input=='N'||input=='n')
									flag1=0;
								else
									revise_infor(member_account);//修改个人信息 
							}
								break;
						case '5'://打印全部书籍信息 	
							print_library();
							printf("按任意键退出...");
							getch();
							break;
						case '6':
							flag=0;
					}	
				}
			
				}
				break;
			case '2':
				decide=member_sign();
				if(decide)//判断是否注册 
					printf("\n\n注册成功\n任意键返回主菜单\n");
				else
					printf("\n按任意键返回主菜单\n");
				getche();
				fflush(stdin);
				break;
			case '3'://管理员信息层
			 while(flag==0)
			 {
			 
				draw_member();
				char adm,admin_sign[15],choice;
				int i=0,num,flag1,flag2,flag3,fun;
				flag1=flag2=flag3=fun=1;
				goto_xy(40,7);
				printf("请输入管理员密码："); 
				fflush(stdin);
				num=member_possword(ADMIN_password);

			if(num==1) 
			{
				while(fun)
				{
					flag1=1;
					system("cls");
					menu3();
					printf("\n\n请选择1~6："); 
					fflush(stdin);
					choice=getche();
					switch(choice)
					{
						case '1'://查询图书信息 
							while(flag1)
							{	
								i=0;
								char book_query[30]={0},input;
								draw_query();
								goto_xy(35, 8);
								printf("请输入查询书籍名称或ID：");
								fflush(stdin);
								gets(book_query);
	
					flag2=query_book(book_query);
					if(flag2==0)
					{
						printf("查询失败，请按任意键后重试...");
						getch();
					}
					if(flag2==1)	
					{
						printf("\n\n继续查询请按 Y ,结束请按 N\n");	
						fflush(stdin);
						input=getch();
						while(input!='Y'&&input!='y'&&input!='N'&&input!='n')
      				    	input=getch();
						if(input=='y'||input=='Y')
							flag1=1;
						else
							flag1=0;
					}
				}
					break;
						case '2'://查询会员信息 
							while(flag1)
							{
								
								i=0;
								char members[15],input;
								draw_query();
								printf("ESC返回"); 
								goto_xy(35, 8);
								printf("请输入查询会员名称或ID：");
								while((input=getch())!=13)//未输入回车时循环 
								{
									if(input==27)//esc键退出 
										break;
									if(input==8)//输入退格符时清除前一个数 
									{
										printf("\b \b");
										i--;
									}
									if(input!=8)
									{
										members[i]=input;
										putchar(input);
										i++;
									}
								}
								if(input==27)//esc键退出 
										break;
	
					flag2=query_member(members);
					if(flag2==0)
					{
						printf("\n\n查询失败，请按任意键后重试...");
						getch();
					}
					if(flag2==1)	
					{				
						printf("\n\n继续查询请按 Y ,结束请按 N\n");
						fflush(stdin);
						input=getch();
						while(input!='Y'&&input!='y'&&input!='N'&&input!='n')
      				    	input=getch();
						if(input=='y'||input=='Y')
							flag1=1;
						else
							flag1=0;
					
								}
							}
						break;
						case '3':
							while(flag1)
							{
								char choice1;
								print_library();
								printf("\n按ESC退出\n更改书籍请按'1'\n增添书籍请按'2'\n删除书籍请按'3'：");
								fflush(stdin);
								choice1=getche();
									if(choice1=='1')
										change_book(); 
									if(choice1=='2')
										add_book();	
									if(choice1=='3')
										delete_book();
									if(choice1==27)
										break;
							}
							break;
						case '4'://管理会员信息 
							while(flag1)
							{
								char choice1;
								int cnd; 
								print_member();
								printf("\n按ESC退出\n按'1'更改会员信息\n按'2'增加会员\n按'3'删除会员：");
								fflush(stdin);
								choice1=getche();
									if(choice1=='1')
									{
										char member_i[15];
										printf("\n请输入需要修改的会员账号或用户名");
										gets(member_i);
										revise_infor(member_i); 
									}
									if(choice1=='2')
									{ 
										cnd=member_sign();	
										if(cnd==1)
											printf("\n已添加新用户。任意键返回");
										else
											break;
										getch();
									} 
									if(choice1=='3')
										delete_member();
									if(choice1==27)
										break;
							 } 
							break;
						case '5'://管理借阅信息 
							while(flag1)
							{
								char choice1;
								print_borrow();//打印所有借阅信息 
								flag1=admin_borrow();//管理借阅信息 		
							}
							break;
						case '6':
							fun=0; 
					}
				}
			}
				else if(num==0)
				{
						printf("密码错误，请重试。"); 
						getchar();
				}
				else
					flag=1;
			}
				break;
			case '4':
				mark=0;
			
	}
	
	}
	fflush(stdin);
	system("cls");
	printf("你已经退出系统!(按任意键关闭界面)\n\n\t欢迎您的再次使用!\n");
	getch();
	return 0;
}
void title()
{
	system("color E4");
	printf("\n\n\n\n");
	printf("\t\t\t\t == == == == == == =*= == == == == == == ==\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|         欢迎使用图书管理系统         |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t == == == == == == =*= == == == == == == ==\n");
	printf("\n\n\n");
}
void menu1()
{
	printf("\n\n\n\n");
	printf("\t\t\t\t == == == == == == =*= == == == == == == ==\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|      Library Management System       |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|   (1).会员登录                       |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|   (2).会员注册                       |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|   (3).管理员登录                     |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|   (4).退出系统                       |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t == == == == == == =*= == == == == == == ==\n");
	printf("\n\n\n");
}
void menu2()
{
	printf("\n\n\n\n");
	printf("\t\t\t\t == == == == == == == == == == == == == ==\n");
	printf("\t\t\t\t|*|                                     |*|\n");
	printf("\t\t\t\t|*|         * | 会-员-界-面 | *         |*|\n");
	printf("\t\t\t\t|*|                                     |*|\n");
	printf("\t\t\t\t|*|   (1).查找图书信息                  |*|\n");
	printf("\t\t\t\t|*|   (2).借阅图书                      |*|\n");
	printf("\t\t\t\t|*|   (3).归还图书                      |*|\n");
	printf("\t\t\t\t|*|   (4).账号信息                      |*|\n");
	printf("\t\t\t\t|*|   (5).所有图书信息                  |*|\n");
	printf("\t\t\t\t|*|   (6).账号登出                      |*|\n");
	printf("\t\t\t\t|*|                                     |*|\n");
	printf("\t\t\t\t|*|                                     |*|\n");
	printf("\t\t\t\t == == == == == == == == == == == == == ==\n");
	printf("\n\n\n");
}
void menu3()
{
	printf("\n\n\n\n");
	printf("\t\t\t\t ^== == == == == == == == == == == == == ==^\n");
	printf("\t\t\t\t|*|                                        |*|\n");
	printf("\t\t\t\t|*|         * | 管-理-员-界-面 | *         |*|\n");
	printf("\t\t\t\t|*|                                        |*|\n");
	printf("\t\t\t\t|*|   (1).查找图书                         |*|\n");
	printf("\t\t\t\t|*|   (2).查找会员                         |*|\n");
	printf("\t\t\t\t|*|   (3).管理图书信息                     |*|\n");
	printf("\t\t\t\t|*|   (4).管理会员信息                     |*|\n");
	printf("\t\t\t\t|*|   (5).管理借阅信息                     |*|\n");
	printf("\t\t\t\t|*|   (6).退出管理员账号                   |*|\n");
	printf("\t\t\t\t|*|                                        |*|\n");
	printf("\t\t\t\t|*|                                        |*|\n");
	printf("\t\t\t\t ^== == == == == == == == == == == == == ==^\n");
	printf("\n\n\n");
	
}
void draw_member()//会员登录图框 
{
	system("cls");
	printf("按ESC键退出\n"); 
	printf("\n\n\n\n");
	printf("\t\t\t\t == == == == ==*==*==*==*==*== == == == ==\n");
	printf("\t\t\t\t|*|                                     |*|\n");
	printf("\t\t\t\t|*|                                     |*|\n");
	printf("\t\t\t\t|*|                                     |*|\n");
	printf("\t\t\t\t|*|                                     |*|\n");
}

void draw_query() 
{
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t == == == == == ==*==*==*==*==*== == == == == ==\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t == == == ==&=#=*==*==*=+=*==*=#=&== == == == ==\n"); 
}

void draw_sign()
{
	
	printf("\n\n\n\n");
	printf("\t\t\t\t == == == == == ==*==*==*==*==*== == == == == ==\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t|*|                                           |*|\n");
	printf("\t\t\t\t == == == ==&=#=*==*==*=+=*==*=#=&== == == == ==\n");
	
 } 
void draw_book()
{
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t  == == == == == ==*==*==*==*==*== == == == == == ==*==*==*==*==*== == == == == == ==\n");
	printf("\t\t\t|*|  书籍编号 |*|   书名    |*|    作者   |*|    位置   |*|   类型   |*|馆藏|*|借出|*|\n");
	printf("\t\t\t|*|~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~|*|~~~~|*|~~~~|*|\n");
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|          |*|    |*|    |*|\n");	
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|          |*|    |*|    |*|\n");
	printf("\t\t\t  == == == == == ==*==*==*==*==*== == == == == == ==*==*==*==*==*== == == == == == ==\n");	
}

void draw_book1()
{
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t  == == == == == ==*==*==*==*==*== == == == == == ==*==*==*==*==*== == == == == == ==\n");
	printf("\t\t\t|*|  书籍编号 |*|   书名    |*|    作者   |*|    位置   |*|   类型   |*|馆藏|*|借出|*|\n");
	printf("\t\t\t|*|~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~|*|~~~~|*|~~~~|*|\n");
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|          |*|    |*|    |*|\n");	
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|          |*|    |*|    |*|\n");
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|          |*|    |*|    |*|\n");	
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|          |*|    |*|    |*|\n");
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|          |*|    |*|    |*|\n");	
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|          |*|    |*|    |*|\n");
	
} 

void draw_borrow()
{
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t  == == == == == ==*==*==*==*==*== == == == == == ==*==*==*==*==*== == ==\n");
	printf("\t\t\t|*|  书籍编号 |*|   书名    |*|    作者   |*|    类型   |*|   借书人   |*|\n");
	printf("\t\t\t|*|~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~~~|*|\n");
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|            |*|\n");	
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|            |*|\n");
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|            |*|\n");	
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|            |*|\n");
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|            |*|\n");	
	printf("\t\t\t|*|           |*|           |*|           |*|           |*|            |*|\n");
	
 } 

void draw_memberinfor()
{
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t  == == == == == ==*==*==*==*==*== == == == == == ==*==*==*==*==*== == == == == == ==\n");
	printf("\t\t\t|*|  用户名  |*|    账号    |*|    密码   |*|    性别   |*|   年龄   |*|    密保    |*|\n");
	printf("\t\t\t|*|~~~~~~~~~~|*|~~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~|*|~~~~~~~~~~~~|*|\n");
	printf("\t\t\t|*|          |*|            |*|           |*|           |*|          |*|            |*|\n");	
	printf("\t\t\t|*|          |*|            |*|           |*|           |*|          |*|            |*|\n");
	printf("\t\t\t  == == == == == ==*==*==*==*==*== == == == == == ==*==*==*==*==*== == == == == == ==\n");
}

void draw_memberinfor1()
{
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t  == == == == == ==*==*==*==*==*== == == == == == ==*==*==*==*==*== == == == == == ==\n");
	printf("\t\t\t|*|  用户名  |*|    账号    |*|    密码   |*|    性别   |*|   年龄   |*|    密保    |*|\n");
	printf("\t\t\t|*|~~~~~~~~~~|*|~~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~~|*|~~~~~~~~~~|*|~~~~~~~~~~~~|*|\n");
	printf("\t\t\t|*|          |*|            |*|           |*|           |*|          |*|            |*|\n");	
	printf("\t\t\t|*|          |*|            |*|           |*|           |*|          |*|            |*|\n");
	printf("\t\t\t|*|          |*|            |*|           |*|           |*|          |*|            |*|\n");	
	printf("\t\t\t|*|          |*|            |*|           |*|           |*|          |*|            |*|\n");
	printf("\t\t\t|*|          |*|            |*|           |*|           |*|          |*|            |*|\n");	
	printf("\t\t\t|*|          |*|            |*|           |*|           |*|          |*|            |*|\n");
}
int member_login(char member_account[15])
{
	FILE *fp;
	MEMBER member[50]={0};
	int number,n,flag1=0,flag2=1,flag;
	char choice;
	number=0;
	fp=fopen("information.txt","r");
	
	while(!feof(fp))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp,"%s %s %s %s %d %s\n",member[number].name,member[number].ID,member[number].password,member[number].sex,&member[number].old_year,member[number].password_key);
		number++;
	}
	
	fclose(fp);
	for(n=0;n<number;n++)//验证账号是否存在 
		if((strcmp(member[n].name,member_account))==0||(strcmp(member[n].ID,member_account))==0)
			{
				flag1=1;
				break;
				
			}
			
	if(flag1)
	{
		printf("\n\n\t\t\t\t\t登录密码：");
		while(flag2)
		{
			flag2=member_possword(member[n].password);
			if(flag2==1)
			{	
				printf("\n>>>验证成功\n>>>正在加载中...\n");
				return 1; 
			}
			else if(flag2==0) 
			{
				printf("\n	密码验证失败,是否使用密保(Y/N):");
				choice=getche();
				while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      				choice=getche();
 				if(choice=='Y'||choice=='y')
				{
					printf("\n\t\t\t\t\t密保登录：");
					flag=member_possword(member[n].password_key);
					if(flag==1)
						return 1;
					if(flag==2)
						return 2;
				}
				else
					printf("\n\t\t\t\t\t登录密码：");
				flag2=1;
			}
			else if(flag2==2) 
			{
				return 2;
			}
		}
	}
	else
	{
		printf("\n未找到您的账号或用户名，请切换大小写后重试\n点击任意重试");
		getch();
		return 0; 
	}
	
}


int member_possword(char member_possword[15])//密码比对函数 
{
	char account[15]={0},num;
	int i=0;
	fflush(stdin);
	while((num=getch())!=13)//未输入回车时循环 
	{
		if(num==27)//esc键退出 
		{
			return 2;
		}
		if(num==8)//输入退格符时清除前一个数 
		{
			printf("\b \b");
			i--;
		}
		if(num!=8)
		{
			account[i]=num;
			i++;
			putchar('*');
		}
	}
	if(strcmp(member_possword,account)==0)
	{
		printf("\a");
		return 1; 
	}
	else
	{
		printf("\a");
		return 0;
	}
}

int query_book(char name_id[30])//查找图书信息 
{
	FILE *bk;
	LIBRARY_BOOK books[150]={0};
	int number=0,n,flag1=0,flag2;
	
	bk=fopen("library.txt","r");
	while(!feof(bk))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(bk,"%s %s %s %s %s %d %d\n",books[number].ID,books[number].name,books[number].writer,books[number].position,books[number].type,&books[number].quantity,&books[number].lend);
		number++;
	}	
	fclose(bk);
	for(n=0;n<number;n++)
		if((strcmp(books[n].ID,name_id))==0||(strcmp(books[n].name,name_id))==0)//对比是否有此书籍信息 
		{
			flag1=1;
			break;
		}
	
	if(flag1)
	{
		draw_book();
		goto_xy(27,7);		
		printf("%8s %13s %14s %12s %13s %7d %6d\n\n",books[n].ID,books[n].name,books[n].writer,books[n].position,books[n].type,books[n].quantity,books[n].lend);
		return 1;
	}
	
	return 0;
}

void lend_book(char book_name[30],char member_id[15])//书籍借出函数 
{
	FILE *bk,*p1,*p2,*br;
	LIBRARY_BOOK books[150];
	LEND lend_book[200]={0};
	int number,n,i,flag0,flag1,flag2=1,number1;
	number=number1=flag1=0;
	
	bk=fopen("library.txt","r");
	while(!feof(bk))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(bk,"%s %s %s %s %s %d %d\n",books[number].ID,books[number].name,books[number].writer,books[number].type,books[number].position,&books[number].quantity,&books[number].lend);
		number++;
	}	
	fclose(bk);
	for(n=0;n<number;n++)
		if((strcmp(books[n].ID,book_name))==0||(strcmp(books[n].name,book_name))==0)
		{
			flag1=1;
			break;
		}
		
		if(flag1==0)
		{
			printf("\n借出失败，查无此书\n");
			return;
		}

		p1=fopen("borrow.txt","r");
		while(!feof(p1))//把文件中的数据导入所创建的结构体中 
		{
			fscanf(p1,"%s %s %s %s %s\n",lend_book[number1].number,lend_book[number1].name,lend_book[number1].writer,lend_book[number1].type,lend_book[number1].account);
			number1++;
		}	
		fclose(p1);
		for(i=0;i<number1;i++)//查询是否重复借阅 
			if(((strcmp(lend_book[i].number,book_name))==0||(strcmp(lend_book[i].name,book_name))==0)&&(strcmp(lend_book[i].account,member_id))==0)
			{
				flag2=0;
				printf("\n\n\n\n\n借书失败，您已借阅此书，请勿重复操作\n"); 
				break;
			}
		
		p2=fopen("borrow.txt","a");
		if(flag2)
		{
	        fprintf(p2,"%s %s %s %s %s\n",books[n].ID,books[n].name,books[n].writer,books[n].type,member_id);
	        fclose(p1);
        	printf("\n\n\n\n您已成功借阅此书，请在15天内归还或续借\n");
        	flag0=1;
        }
        fclose(p2);
        if(flag0)
        {
        	books[n].lend--;
	        bk=fopen("library.txt","w");
			for(i=0;i<number;i++)//把文件中的数据导入所创建的结构体中 
			{
				fprintf(bk,"%s %s %s %s %s %d %d\n",books[i].ID,books[i].name,books[i].writer,books[i].type,books[i].position,books[i].quantity,books[i].lend);
				
			}	
			fclose(bk);
		}
 } 

void return_book(char book_return[30],char member_id[15])//书籍归还函数 
{
	FILE *fp1,*fp2,*bk;
	LEND lend_books[150];
	LIBRARY_BOOK books[150];
	int flag0,flag1,number,number1,i,n,k;
	flag1=number=number1=i=0;
	
	fp1=fopen("borrow.txt","r");
	while(!feof(fp1))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp1,"%s %s %s %s %s\n",lend_books[number].number,lend_books[number].name,lend_books[number].writer,lend_books[number].type,lend_books[number].account);
		number++;
	}	
	fclose(fp1);
	
	for(i=0;i<number;i++)//查询是否借阅 
		if(((strcmp(lend_books[i].number,book_return))==0||(strcmp(lend_books[i].name,book_return))==0)&&(strcmp(lend_books[i].account,member_id))==0)
		{
			flag1=1;
			break;
		}
	
	
 
	bk=fopen("library.txt","r");//为了修改馆内剩余书籍数据 
	while(!feof(bk))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(bk,"%s %s %s %s %s %d %d\n",books[number1].ID,books[number1].name,books[number1].writer,books[number1].type,books[number1].position,&books[number1].quantity,&books[number1].lend);
		number1++;
	}	
	fclose(bk);
	for(k=0;k<number1;k++)
		if((strcmp(books[k].ID,book_return))==0||(strcmp(books[k].name,book_return))==0)
			break;
		
	if(flag1)//覆盖写入borrow文件 
	{
		fp2=fopen("borrow.txt","w");
		for(n=0;n<number;n++)
		{
			if(n!=i)	
				fprintf(fp2,"%s %s %s %s %s\n",lend_books[n].number,lend_books[n].name,lend_books[n].writer,lend_books[n].type,lend_books[n].account);
		}
		fclose(fp2);
		printf("\n\n\n还书成功\n");
		flag0=1;
	}
	if(flag1==0)
	{
		printf("\n\n\n还书失败，未查询到曾借阅此书\n");
		printf("请尝试重试或询问图书管理员\n");
	}
	
	if(flag0)
        {
        	books[k].lend++;
	        bk=fopen("library.txt","w");
			for(i=0;i<number1;i++)//把文件中的数据导入所创建的结构体中 
			{
				fprintf(bk,"%s %s %s %s %s %d %d\n",books[i].ID,books[i].name,books[i].writer,books[i].type,books[i].position,books[i].quantity,books[i].lend);
				
			}	
			fclose(bk);
		}
}

void member_information(char member_id[15])//显示会员个人信息 
{
	FILE *fp;
	int n,i,number=0,flag1=0;
	MEMBER member_infor[150];
	
	fp=fopen("information.txt","r");
	while(!feof(fp))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp,"%s %s %s %s %d %s\n",member_infor[number].name,member_infor[number].ID,member_infor[number].password,member_infor[number].sex,&member_infor[number].old_year,member_infor[number].password_key);
		number++;
	}	
	fclose(fp);
	
	for(i=0;i<number;i++)//定位个人信息 
		if((strcmp(member_infor[i].name,member_id))==0||(strcmp(member_infor[i].ID,member_id))==0)
		{
			flag1=1;
			break;
		}
	
	if(flag1)
	{
		draw_memberinfor();
		goto_xy(27,7);
		printf("%8s %13s %12s %13s %12d %12s",member_infor[i].name,member_infor[i].ID,member_infor[i].password,member_infor[i].sex,member_infor[i].old_year,member_infor[i].password_key);
	}
}

void revise_infor(char member_ID[15])//修改个人信息函数 
{
	FILE *fp,*p1;
	int n,i,number=0,flag1=0;
	MEMBER revise_infor[150];
	char cho;
	
	fp=fopen("information.txt","r");
	while(!feof(fp))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp,"%s %s %s %s %d %s\n",revise_infor[number].name,revise_infor[number].ID,revise_infor[number].password,revise_infor[number].sex,&revise_infor[number].old_year,revise_infor[number].password_key);
		number++;
	}	
	fclose(fp);
	
	for(i=0;i<number;i++)//定位个人信息 
		if((strcmp(revise_infor[i].name,member_ID))==0||(strcmp(revise_infor[i].ID,member_ID))==0)
		{
			flag1=1;
			break;
		}
	
	if(flag1)
	{
		printf("\n\n你要修改用户名吗？Y/N\n");
		fflush(stdin);
		cho=getch();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getch();
		if(cho=='Y'||cho=='y')
		{
			printf("\n请输入新用户名：");
			scanf("%s",&revise_infor[i].name);
			printf("\n修改成功");
		}
		
		printf("\n\n你要修改账号吗？Y/N\n");
		fflush(stdin);
		cho=getch();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getch();
		if(cho=='Y'||cho=='y')
		{
			printf("\n请输入新账号：");
			scanf("%s",&revise_infor[i].ID);
			printf("\n修改成功");
		}
		
		printf("\n你要修改登陆密码吗？Y/N\n");
		fflush(stdin);
		cho=getche();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getche();
		if(cho=='Y'||cho=='y')
		{
			printf("\n请输入新密码：");
			scanf("%s",&revise_infor[i].password);
			printf("\n修改成功");
		}
		
		printf("\n你要修改性别吗？Y/N\n");
		fflush(stdin);
		cho=getche();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getche();
		if(cho=='Y'||cho=='y')
		{
			printf("\n'man' or 'woman'\n");
			scanf("%s",&revise_infor[i].sex);
			printf("\n修改成功\n");
		}
		
		printf("\n你要修改年龄吗？Y/N\n");
		fflush(stdin);
		cho=getche();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getche();
		if(cho=='Y'||cho=='y')
		{
			printf("\n请输入新年龄：");
			scanf("%s",&revise_infor[i].old_year);
			printf("\n修改成功\n");
		}
		
		printf("\n你要修改密保吗？Y/N\n");
		fflush(stdin);
		cho=getche();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getche();
		if(cho=='Y'||cho=='y')
		{
			printf("\n请输入新密保：");
			scanf("%s",&revise_infor[i].password_key);
			printf("\n修改成功\n");
		}
		
		p1=fopen("information.txt","w");
			for(n=0;n<number;n++)
				fprintf(p1,"%s %s %s %s %d %s\n",revise_infor[n].name,revise_infor[n].ID,revise_infor[n].password,revise_infor[n].sex,revise_infor[n].old_year,revise_infor[n].password_key);

		fclose(p1);
	}
} 

void print_library()//打印所有书籍信息 
{
	FILE *fp;
	LIBRARY_BOOK book_s[150];
	int n,i,number;
	number=i=0;
	n=7; 
	
	fp=fopen("library.txt","r");
	while(!feof(fp))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp,"%s %s %s %s %s %d %d\n",book_s[number].ID,book_s[number].name,book_s[number].writer,book_s[number].position,book_s[number].type,&book_s[number].quantity,&book_s[number].lend);
		number++;
	}	
	fclose(fp);
	
	
	draw_book1(); 
	while(i<number)
	{	
		goto_xy(27,n);	
		printf("%8s %13s %14s %12s %13s %7d %6d\n",book_s[i].ID,book_s[i].name,book_s[i].writer,book_s[i].position,book_s[i].type,book_s[i].quantity,book_s[i].lend);
		i++;
		n++;
	}
 } 

int member_sign()//会员注册函数 
{
	FILE *fp;
	MEMBER member_infor[150];
	int number,i,n,flag1,flag2,flag3,flag4,old;
	char member_name[15],member_id[15],member_password[15],member_sex[5],member_passwordkey[20],num;
	i=number=flag4=0;
	
	fp=fopen("information.txt","r");
	while(!feof(fp))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp,"%s %s %s %s %d %s\n",member_infor[number].name,member_infor[number].ID,member_infor[number].password,member_infor[number].sex,&member_infor[number].old_year,member_infor[number].password_key);
		number++;
	}	
	fclose(fp);
	
	while(flag1)
	{
		system("cls");
		printf("按ESC键退出\n");
		i=0;
		flag1=flag2=1;
		draw_sign();
		goto_xy(36,7);
		printf("用户名：             ");
		goto_xy(43,7);
		fflush(stdin); 
		while((num=getche())!=13)//未输入回车时循环 
		{
			if(num==27)//esc键退出 
			{
				return 0;
			}
			if(num==8)//输入退格符时清除前一个数 
			{
				printf(" \b");
				i--;
			}
			if(num!=8)
			{
				member_name[i]=num;
				i++;	
			}
		}
		
		for(n=0;n<number;n++){
			if(strcmp(member_infor[n].name,member_name)==0)
			{
				printf("\n用户名已存在，按任意键后重新输入");
				getch(); 
				flag2=0;
				break; 	
			}
			else
				flag1=0;
				} 
		if(flag2==0)
			flag1=1;
		
		while(flag2)
		{
			i=0;
			flag2=flag3=1;
			goto_xy(36,9);
			printf("账号：             ");
			goto_xy(43,9); 
			fflush(stdin); 
			while((num=getche())!=13)//未输入回车时循环 
			{
				if(num==27)//esc键退出 
				{
					return 0;
				}
				if(num==8)//输入退格符时清除前一个数 
				{
					printf(" \b");
					i--;
				}
				if(num!=8)
				{
					member_id[i]=num;
					i++;
				}
			}
		
		for(n=0;n<number;n++)
			if(strcmp(member_infor[n].ID,member_id)==0)
			{
				printf("\n账号已存在，按任意键后重新输入");
				getch(); 
				flag3=0;
				break; 	
			}
			else 
				flag2=0;
			
		if(flag3==0)
			flag2=1;
		
		while(flag3)	
		{
			i=0;
			flag3=1;
			goto_xy(36,11); 
			printf("密码：             ");
			goto_xy(43,11);
			fflush(stdin); 
			while((num=getche())!=13)//未输入回车时循环 
			{
				if(num==27)//esc键退出 
				{
					return 0;
				}
				if(num==8)//输入退格符时清除前一个数 
				{
					printf(" \b");
					i--;
				}
				if(num!=8)
				{
					member_password[i]=num;
					i++;
				}
			}
			
		for(n=0;n<number;n++)
			if(strcmp(member_infor[n].password,member_password)==0)
			{
				printf("\n密码已存在，按任意键后重新输入");
				getch();
				flag3=1;
				break; 	
			}
			else
				flag3=0;
		}	}	}
	
	if(flag1==0&&flag2==0&&flag3==0)
		flag4=1;
		
	if(flag4)
	{
		i=0;
		goto_xy(36,13);
		printf("性别：         (man or woman)");
		goto_xy(43,13);
		fflush(stdin); 
		while((num=getche())!=13)//未输入回车时循环 
		{
			if(num==27)//esc键退出 
			{
				return 0;
			}
			if(num==8)//输入退格符时清除前一个数 
			{
				printf(" \b");
				i--;
			}
			if(num!=8)
			{
				member_sex[i]=num;
				i++;
			}
		}
		
		i=0;
		goto_xy(36,15);
		printf("年龄：         ");
		goto_xy(43,15);
		fflush(stdin); 
		scanf("%d",&old);
		
			i=0;
			goto_xy(36,17);
			printf("密保(备用密码)：             "); 
			goto_xy(49,17);
			fflush(stdin); 
			while((num=getche())!=13)//未输入回车时循环 
			{
				if(num==27)//esc键退出 
				{
					return 0;
				}
				if(num==8)//输入退格符时清除前一个数 
				{
					printf(" \b");
					i--;
				}
				if(num!=8)
				{
					member_passwordkey[i]=num;
					i++;
				}
			}

		fp=fopen("information.txt","w");
		for(i=0;i<number;i++)
			fprintf(fp,"%s %s %s %s %d %s\n",member_infor[i].name,member_infor[i].ID,member_infor[i].password,member_infor[i].sex,member_infor[i].old_year,member_infor[i].password_key);
		fclose(fp);
		fp=fopen("information.txt","a");
		fprintf(fp,"%s %s %s %s %d %s\n",member_name,member_id,member_password,member_sex,old,member_passwordkey);
		fclose(fp);
		return 1;
	}	
} 

int query_member(char member_id[15])//查找会员信息 
{
	FILE *mk;
	MEMBER members[150]={0};
	int number=0,n,flag1=0,flag2;
	
	mk=fopen("information.txt","r");
	while(!feof(mk))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(mk,"%s %s %s %s %d %s\n",members[number].name,members[number].ID,members[number].password,members[number].sex,&members[number].old_year,members[number].password_key);
		number++;
	}	
	fclose(mk);
	for(n=0;n<number;n++)
		if((strcmp(members[n].ID,member_id))==0||(strcmp(members[n].name,member_id))==0)//对比是否有此书籍信息 
		{
			flag1=1;
			break;
		}
	
	if(flag1)
	{
		draw_memberinfor();
		goto_xy(27,7);		
		printf("%8s %13s %12s %13s %12d %12s",members[n].name,members[n].ID,members[n].password,members[n].sex,members[n].old_year,members[n].password_key);
		return 1;
	}
	
	return 0;
 } 

void change_book()
{
	FILE *fp,*p1;
	LIBRARY_BOOK book_change[150];
	char change[15],choice1,choice2,choice3,choice4,choice5,choice6,choice7;
	int n,i,number,flag1;
	number=i=flag1=0;
	n=7; 
	
	fp=fopen("library.txt","r");
	while(!feof(fp))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp,"%s %s %s %s %s %d %d\n",book_change[number].ID,book_change[number].name,book_change[number].writer,book_change[number].position,book_change[number].type,&book_change[number].quantity,&book_change[number].lend);
		number++;
	}	
	fclose(fp);
	printf("\n请输入要更改书籍的编号：");
	gets(change);
	for(n=0;n<number;n++)//对比是否有此书籍信息
		if((strcmp(book_change[n].ID,change))==0||(strcmp(book_change[n].name,change))==0) 
		{
			flag1=1;
			break;
		}
	
	if(flag1)
	{
		printf("是否更改书籍编号(Y/N)：");
		fflush(stdin); 
		fflush(stdin);
		choice1=getche();
		while(choice1!='Y'&&choice1!='y'&&choice1!='N'&&choice1!='n')
      		choice1=getche();
      	if(choice1=='Y'||choice1=='y')
      	{
		  	printf("\n请输入新编号：");
      		gets(book_change[n].ID);
      	}
      	
      	printf("\n是否更改书籍名(Y/N)：");
      	fflush(stdin);
      	choice2=getche(); 
		while(choice2!='Y'&&choice2!='y'&&choice2!='N'&&choice2!='n')
      		choice2=getche();
      	if(choice2=='Y'||choice2=='y')
      	{
			 printf("\n请输入新书籍名：");
      		gets(book_change[n].name);
      	}
      	
      	printf("\n是否更改书籍作者(Y/N)：");
      	fflush(stdin);
      	choice3=getche(); 
		while(choice3!='Y'&&choice3!='y'&&choice3!='N'&&choice3!='n')
      		choice3=getche();
      	if(choice3=='Y'||choice3=='y')
      	{
		  	printf("\n请输入新作者名：");
      		gets(book_change[n].writer);
      	}
      	
      	printf("\n是否更改书籍存放位置(Y/N)：");
      	fflush(stdin);
      	choice4=getche(); 
		while(choice4!='Y'&&choice4!='y'&&choice4!='N'&&choice4!='n')
      		choice4=getche();
      	if(choice4=='Y'||choice4=='y')
      	{
			printf("\n请输入新位置：");
      		gets(book_change[n].position);
      	}
      	
      	printf("\n是否更改书籍类型(Y/N)：");
      	fflush(stdin);
      	choice5=getche(); 
		while(choice5!='Y'&&choice5!='y'&&choice5!='N'&&choice5!='n')
      		choice5=getche();
      	if(choice5=='Y'||choice5=='y')
      	{
      		printf("\n请输入新书籍类型：");
      		gets(book_change[n].type);
      	}
      	
      	printf("\n是否更改馆藏量(Y/N)：");
      	fflush(stdin);
      	choice6=getche(); 
		while(choice6!='Y'&&choice6!='y'&&choice6!='N'&&choice6!='n')
      		choice6=getche();
      		
      	if(choice6=='Y'||choice6=='y')
      	{ 
      		printf("\n请输入更新后馆藏量：");
      		scanf("%d",&book_change[n].quantity);
      	}	
      	
      	printf("\n是否更改馆内剩余数量(Y/N)：");
      	fflush(stdin);
      	choice7=getche(); 
		while(choice7!='Y'&&choice7!='y'&&choice7!='N'&&choice7!='n')
      		choice7=getche();
      	if(choice7=='Y'||choice7=='y')
      	{
		 	printf("\n请输入更新后剩余数量：");
      		scanf("%d",&book_change[n].lend);	
		}		
		printf("\n更改完成\n");
		getch();		
	} 
	
	p1=fopen("library.txt","w");
	for(i=0;i<number;i++)//覆盖写入书籍信息 
		fprintf(p1,"%s %s %s %s %s %d %d\n",book_change[i].ID,book_change[i].name,book_change[i].writer,book_change[i].position,book_change[i].type,book_change[i].quantity,book_change[i].lend);	
	fclose(p1);	
}

void add_book()
{
	FILE *fp;
	char choice;
	int number=0;
	LIBRARY_BOOK addbook[10];
	
	printf("\n请输入书籍编号：");
    gets(addbook[0].ID);
    printf("\n请输入书籍名称：");
    gets(addbook[0].name);
	printf("\n请输入书籍作者：");
    gets(addbook[0].writer);
    printf("\n请输入书籍存放位置：");
    gets(addbook[0].position);
    printf("\n请输入书籍类型：");
    gets(addbook[0].type);
    printf("\n请输入书籍馆藏量：");
    scanf("%d",&addbook[0].quantity);
    addbook[0].lend=0;
    
    printf("确实导入此书籍信息吗?(Y/N)：");
    fflush(stdin);
    choice=getche();
   	while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      	choice=getche();
    if(choice=='Y'||choice=='y')
    {	
		fp=fopen("library.txt","a");
		fprintf(fp,"%s %s %s %s %s %d %d\n",addbook[0].ID,addbook[0].name,addbook[0].writer,addbook[0].position,addbook[0].type,addbook[0].quantity,addbook[0].lend);	
		fclose(fp);
		printf("\n导入成功。\n");
		getchar();
	}
}

void delete_book()
{
	FILE *fp,*p1;
	LIBRARY_BOOK delete_book[150];
	int number,n,flag1,i;
	char dele[30];
	number=flag1=i=0;
		
	fp=fopen("library.txt","r");
	while(!feof(fp))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp,"%s %s %s %s %s %d %d\n",delete_book[number].ID,delete_book[number].name,delete_book[number].writer,delete_book[number].position,delete_book[number].type,&delete_book[number].quantity,&delete_book[number].lend);
		number++;
	}	
	fclose(fp);
	printf("\n请输入要删除的书籍编号：");
	gets(dele);
	for(n=0;n<number;n++)//对比是否有此书籍信息
		if((strcmp(delete_book[n].ID,dele))==0||(strcmp(delete_book[n].name,dele))==0) 
		{
			flag1=1;
			break;
		}
	if(flag1)
	{
		p1=fopen("library.txt","w");
	for(i=0;i<number;i++)
	{
		if(i!=n)
			fprintf(p1,"%s %s %s %s %s %d %d\n",delete_book[i].ID,delete_book[i].name,delete_book[i].writer,delete_book[i].position,delete_book[i].type,delete_book[i].quantity,delete_book[i].lend);
	}
	fclose(p1);
	printf("\n删除成功。任意键返回\n");
	getch();
	}
}
void print_member()//打印所有会员信息 
{
	FILE *fp;
	MEMBER members[150];
	int n,i,number;
	number=i=0;
	n=7; 
	
	fp=fopen("information.txt","r");
	while(!feof(fp))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp,"%s %s %s %s %d %s\n",members[number].name,members[number].ID,members[number].password,members[number].sex,&members[number].old_year,members[number].password_key);
		number++;
	}	
	fclose(fp);
	
	draw_memberinfor1();
	while(i<number)
	{	
		goto_xy(27,n);	
		printf("%8s %13s %12s %13s %12d %12s",members[i].name,members[i].ID,members[i].password,members[i].sex,members[i].old_year,members[i].password_key);
		i++;
		n++;
	}
} 

void delete_member()//删除会员 
{
	FILE *fp,*p1;
	MEMBER members[150];
	char member_d[15],input;
	int n,i,number,flag;
	number=flag=0;
	
	fp=fopen("information.txt","r");
	while(!feof(fp))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp,"%s %s %s %s %d %s\n",members[number].name,members[number].ID,members[number].password,members[number].sex,&members[number].old_year,members[number].password_key);
		number++;
	}	
	fclose(fp);
	printf("\n请输入要删除的会员账号或用户名:");
	gets(member_d);
	for(n=0;n<number;n++)
		if((strcmp(members[n].ID,member_d))==0||(strcmp(members[n].name,member_d))==0)//对比是否有此书籍信息 
			break;
	
	printf("\n确定删除该会员信息吗？(Y/N)");
	fflush(stdin);
	input=getche();
	while(input!='Y'&&input!='y'&&input!='N'&&input!='n')
   	   	input=getche();
	if(input=='y'||input=='Y')
		flag=1;
   	if(flag)
	{	   	
		p1=fopen("information.txt","w");
		for(i=0;i<number;i++)
			if(i!=n)
				fprintf(p1,"%s %s %s %s %d %s\n",members[i].name,members[i].ID,members[i].password,members[i].sex,members[i].old_year,members[i].password_key);
		fclose(p1);
	}
}

void print_borrow()//打印所有借阅信息 
{
	FILE *fp;
	LEND lend_books[150];
	int n,i,number;
	number=i=0;
	n=7; 
	
	fp=fopen("borrow.txt","r");
	while(!feof(fp))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp,"%s %s %s %s %s\n",lend_books[number].number,lend_books[number].name,lend_books[number].writer,lend_books[number].type,lend_books[number].account);
		number++;
	}	
	fclose(fp);

	draw_borrow(); 
	while(i<number)
	{	
		goto_xy(27,n);	
		printf("%8s %13s %14s %12s %13s\n",lend_books[i].number,lend_books[i].name,lend_books[i].writer,lend_books[i].type,lend_books[i].account);
		i++;
		n++;
	}
	
}

int admin_borrow()//管理借阅信息函数 
{
	FILE *fp,*p1;
	LEND borrows[150];
	char choice1,name_id[15],book_id[15],choice;
	int number,i,n,flag1;
	number=i=n=flag1=0;
	
	printf("\n按ESC退出\n按'1'修改借阅信息\n按'2'删除借阅信息：");
	choice1=getche();
	while(choice1!='1'&&choice1!='2'&&choice1!=27)
    	choice1=getche();
    if(choice1=='1')
    {
    	printf("\n请输入需要修改的书籍编号和借阅人\n");
		printf("\n书籍编号：");
		gets(name_id);
		printf("\n借阅人");
		gets(book_id); 
		
		fp=fopen("borrow.txt","r");
		while(!feof(fp))//把文件中的数据导入所创建的结构体中 
		{
			fscanf(fp,"%s %s %s %s %s\n",borrows[number].number,borrows[number].name,borrows[number].writer,borrows[number].type,borrows[number].account);
			number++;
		}	
		fclose(fp);
		
		for(i=0;i<number;i++)//定位借阅信息 
		if((strcmp(borrows[i].number,name_id))==0&&(strcmp(borrows[i].account,book_id))==0)
		{
			flag1=1;
			break;
		}
		
	if(flag1) 
	{
		printf("\n是否更改书籍编号(Y/N)：");
      	fflush(stdin);
      	choice=getche(); 
		while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      		choice=getche();
      	if(choice=='Y'||choice=='y')
      	{
		  	printf("\n请输入新书籍编号：");
      		gets(borrows[i].number);
      	}
      	
      	printf("\n是否更改书籍名(Y/N)：");
      	fflush(stdin);
      	choice=getche(); 
		while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      		choice=getche();
      	if(choice=='Y'||choice=='y')
      	{
		  	printf("\n请输入新书籍名：");
      		scanf("%s",&borrows[i].name);
      	}
      	
      	printf("\n是否更改书籍作者(Y/N)：");
      	fflush(stdin);
      	choice=getche(); 
		while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      		choice=getche();
      	if(choice=='Y'||choice=='y')
      	{
		  	printf("\n请输入新书籍作者：");
      		scanf("%s",&borrows[i].writer);
      	}
      	
      	printf("\n是否更改书籍类型(Y/N)：");
      	fflush(stdin);
      	choice=getche(); 
		while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      		choice=getche();
      	if(choice=='Y'||choice=='y')
      	{
		  	printf("\n请输入新书籍类型：");
      		gets(borrows[i].type);
      	}
      	
      	printf("\n是否更改借阅人(Y/N)：");
      	fflush(stdin);
      	choice=getche(); 
		while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      		choice=getche();
      	if(choice=='Y'||choice=='y')
      	{
		  	printf("\n请输入新借阅人：");
      		gets(borrows[i].account);
      	}
      	
      	p1=fopen("borrow.txt","w");
		for(n=0;n<number;n++)
			fprintf(p1,"%s %s %s %s %s\n",borrows[n].number,borrows[n].name,borrows[n].writer,borrows[n].type,borrows[n].account);	
		fclose(p1);	
		return 1;  	
    }
	}
	if(choice1=='2')
	{
		printf("\n请输入需要删除的书籍编号和借阅人\n");
		printf("\n书籍编号：");
		gets(name_id);
		printf("\n借阅人");
		gets(book_id); 
		
		fp=fopen("borrow.txt","r");
	while(!feof(fp))//把文件中的数据导入所创建的结构体中 
	{
		fscanf(fp,"%s %s %s %s %s\n",borrows[number].number,borrows[number].name,borrows[number].writer,borrows[number].type,borrows[number].account);
		number++;
	}	
	fclose(fp);
	
	for(i=0;i<number;i++)//定位借阅信息 
		if((strcmp(borrows[i].number,name_id))==0&&(strcmp(borrows[i].account,book_id))==0)
		{
			flag1=1;
			break;
		}
	
	if(flag1)
	{
		p1=fopen("borrow.txt","w");
		for(n=0;n<number;n++)
		{
			if(n!=i)
				fprintf(p1,"%s %s %s %s %s\n",borrows[n].number,borrows[n].name,borrows[n].writer,borrows[n].type,borrows[n].account);
		}	
		fclose(p1);	
	}
	return 1;
	 } 
	 if(choice1==27)
		return 0;
	
}

void transit()//过渡函数 
{
	title();
	printf("\n正在努力加载中...."); 
	Sleep(1500);
	printf("\n载入完成...");
	Sleep(750);
 } 
 
void goto_xy(int x, int y)//定位光标位置到指定坐标
{   
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x,y };
    SetConsoleCursorPosition(hOut, pos);
}
