  
/*
  �������ֻ����������д����ģ����ܻ��кܶ�BUGû�з��֣�������ڴ������й����з�����bug��error������ϵ�Ҹ�һ�¡�
  ������������һǧ����д��ģ����д��д�ž�ʧ���ˣ�ֱ�Ӷѵ���1700���У����Σ���Ҳ��ѧ�ղ������ܶ�ط�ʹ���˼�
���߳��Ľṹ������Ц�󷽣������ܹ��ǵ�һ��д�Լ��ĳ��򣬺����뵽���õĽṹҲ��Ľ��ġ�*/ 

//ͷ�ļ��� 
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h> 
#include<stdlib.h>

//�˵������� 
void title();//���Ƚ��� 
void menu1();//���˵� 
void menu2();//��Ա����˵�
void menu3();//����Ա��¼�˵�  
 
//���ߺ����� 
void transit();//���Ⱥ��� 
void goto_xy(int,int);//����ƶ����� 
void draw_member();//���հװ����
void draw_query();//���հ׿��� 
void draw_book();//���鼮��Ϣ�� 
void draw_memberinfor();//����Ա��Ϣ�� 
void draw_sign();//��ע���Ա�� 
int member_sign();//ע���Ա���� 

//��Ա��Ϣ�㺯��
int member_login(char number[15]); 
void lend_book(char ar[],char ad[]);//����ǼǺ��� 
int member_possword(char ar[]);//����ȶԺ��� 
int query_book(char ar[]);//����ͼ�麯�� 
void return_book(char ar[],char ad[]);//�鼮�黹���� 
void member_information(char ar[]);//��ѯ������Ϣ���� 
void revise_infor(char ar[]);//�޸ĸ�����Ϣ���� 
void print_library();//��ӡ�����鼮��Ϣ����

//����Ա��Ϣ����Ϣ 
void admin_system();//����Ա��¼���� 
int query_member(char ar[]);//���һ�Ա����
void change_book();//�鼮�޸ĺ��� 
void add_book();//�����鼮���� 
void delete_book();//ɾ���鼮���� 
void draw_memberinfor1();//��Ա��Ϣ���� 
void print_member();//��ӡ���л�Ա��Ϣ���� 
void delete_member();//ɾ����Ա��Ϣ���� 
void print_borrow();//��ӡ���н�����Ϣ���� 
void draw_borrow();//������Ϣ�� ���� 
int admin_borrow();//���������Ϣ���� 

//�궨����
#define ADMIN_password "12345"//����Ա��¼���� 

//�ṹ��������
typedef struct library_book//ϵͳ�е�ͼ����Ϣ
{
	char ID[15];//ͼ���� 
	char name[30];//�鼮���� 
	char writer[20];//�鼮����
	char position[15];//�鼮��ŵص� 
	char type[10];//�鼮����
	int quantity;//�������ղ��� 
	int lend;//�ѽ������ 
}LIBRARY_BOOK; 

typedef struct lend/*��Ա������鼮��Ϣ*/ 
{
	char number[15];//ͼ����
    char name[20];//�鼮����
    char writer[20];//����
    char type[10]; //�鼮���� 
 	char account[30];//������ID
}LEND;

typedef struct member//��Ա������Ϣ 
{
	char name[15];//��Ա�û��� 
	char ID[15]; //��Ա��¼�˺�
	char password[15];//��Ա��¼����
	char sex[5];//��Ա�Ա� 
	int old_year;//��Ա���� 
	char password_key[20]; //�һ�������ܱ�  
}MEMBER;



 
int main()
{
	FILE *w1,*w2,*w3;
	char choose1,choose2,choose3;
	system("title *gzhmt�ܶ�182  ��־�*");
	int flag=0,flag1,flag2,mark=1,decide;
	
	if((w1=fopen("library.txt","r"))==NULL)//w1���鼮��Ϣ�ļ�ָ�� 
	{
		w1=fopen("library.txt","w");
		fclose(w1);
	}
	if((w2=fopen("information.txt","r"))==NULL)//w2�ǻ�Ա������Ϣ�ļ�ָ�� 
	{
		w2=fopen("information.txt","w");
		fclose(w2);
	}
	if((w3=fopen("borrow.txt","r"))==NULL)//w3�ǻ�Ա�����鼮��ͼ����Ϣָ�� 
	{
		w3=fopen("borrow.txt","w");
		fclose(w3);
	}
	
	transit();//���ػ���Ĺ��ɳ��� 
	while(mark) 
	{
		system("cls");
		menu1();
		printf("��ѡ��1~4��");
		choose1='0';
		fflush(stdin);
		choose1=getche();
		while(choose1!='1'&&choose1!='2'&&choose1!='3'&&choose1!='4')//�ж������Ƿ�Ϊ1-4
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
					printf("��¼�˺ţ�");
					fflush(stdin);			
					while((acc=getch())!=13)//δ����س�ʱѭ�� 
					{
						if(acc==27)//esc���˳� 
							break;
						if(acc==8)//�����˸��ʱ���ǰһ���� 
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
				if(acc==27)//esc���˳� 
					break;		
				else 
					flag=member_login(member_account);//�˺ŵ�½���� 
				if(flag==2)
					mark=1;
				while(flag==1)
				{
					flag1=1;
					system("cls");
					menu2();
					printf("��ѡ��1~6");
					fflush(stdin);	
					choose2=getche();
					while(choose1!='1'&&choose1!='2'&&choose1!='3'&&choose1!='4'&&choose1!='5'&&choose1!='6')//�ж������Ƿ�Ϊ1-6
						choose2=getche();
					fflush(stdin);
					switch(choose2)
					{
						case '1'://��ѯ�鼮 
							while(flag1)
							{	
								i=0;
								char book_query[30]={0},input;
								draw_query();
								goto_xy(35, 8);
								printf("�������ѯ�鼮���ƻ�ID��");
								fflush(stdin);
								gets(book_query);
	
					flag2=query_book(book_query);
					if(flag2==0)
					{
						printf("��ѯʧ�ܣ��밴�����������...");
						getch();
					}
					if(flag2==1)	
					{
						printf("\n����Ҫ���������Y/N\n"); 
						fflush(stdin);
						flag2=getche();
						while(flag2!='Y'&&flag2!='y'&&flag2!='N'&&flag2!='n')//�ж������Ƿ�Ϊy��n 
      				    	flag2=getch();
						if(flag2=='Y'||flag2=='y')
						{
							lend_book(book_query,member_account);
							printf("\n������ѯ�밴 Y ,�����밴 N\n");
						}
						if(flag2=='n'||flag2=='N')
							printf("\n������ѯ�밴 Y ,�����밴 N\n");
							
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
							while(flag1)//����鼮 
							{
								char book_name[30],input;
								draw_query();
								goto_xy(35, 8);
								printf("�鼮���/������");
								fflush(stdin);
								gets(book_name);
								lend_book(book_name,member_account);
								printf("\n���������밴 Y ,�����밴 N\n");
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
						case '3'://�鼮�黹 
							while(flag1)
							{
								char book_return[30],input;
								draw_query();
								goto_xy(36, 8);
								printf("������黹�鼮��ţ�");
								fflush(stdin);
								gets(book_return);
								return_book(book_return,member_account);
								printf("\n���������밴 Y ,�����밴 N\n");
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
						case '4'://��ѯ�˺���Ϣ
							while(flag1)
							{
								char input;
								member_information(member_account);
								printf("\n\n\n�Ƿ���Ҫ�޸ĸ�����Ϣ��Y�޸ģ�N�˳���\nY/N\n");
								fflush(stdin);
								input=getch();
								while(input!='Y'&&input!='y'&&input!='N'&&input!='n')
      						    	input=getch();
								if(input=='N'||input=='n')
									flag1=0;
								else
									revise_infor(member_account);//�޸ĸ�����Ϣ 
							}
								break;
						case '5'://��ӡȫ���鼮��Ϣ 	
							print_library();
							printf("��������˳�...");
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
				if(decide)//�ж��Ƿ�ע�� 
					printf("\n\nע��ɹ�\n������������˵�\n");
				else
					printf("\n��������������˵�\n");
				getche();
				fflush(stdin);
				break;
			case '3'://����Ա��Ϣ��
			 while(flag==0)
			 {
			 
				draw_member();
				char adm,admin_sign[15],choice;
				int i=0,num,flag1,flag2,flag3,fun;
				flag1=flag2=flag3=fun=1;
				goto_xy(40,7);
				printf("���������Ա���룺"); 
				fflush(stdin);
				num=member_possword(ADMIN_password);

			if(num==1) 
			{
				while(fun)
				{
					flag1=1;
					system("cls");
					menu3();
					printf("\n\n��ѡ��1~6��"); 
					fflush(stdin);
					choice=getche();
					switch(choice)
					{
						case '1'://��ѯͼ����Ϣ 
							while(flag1)
							{	
								i=0;
								char book_query[30]={0},input;
								draw_query();
								goto_xy(35, 8);
								printf("�������ѯ�鼮���ƻ�ID��");
								fflush(stdin);
								gets(book_query);
	
					flag2=query_book(book_query);
					if(flag2==0)
					{
						printf("��ѯʧ�ܣ��밴�����������...");
						getch();
					}
					if(flag2==1)	
					{
						printf("\n\n������ѯ�밴 Y ,�����밴 N\n");	
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
						case '2'://��ѯ��Ա��Ϣ 
							while(flag1)
							{
								
								i=0;
								char members[15],input;
								draw_query();
								printf("ESC����"); 
								goto_xy(35, 8);
								printf("�������ѯ��Ա���ƻ�ID��");
								while((input=getch())!=13)//δ����س�ʱѭ�� 
								{
									if(input==27)//esc���˳� 
										break;
									if(input==8)//�����˸��ʱ���ǰһ���� 
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
								if(input==27)//esc���˳� 
										break;
	
					flag2=query_member(members);
					if(flag2==0)
					{
						printf("\n\n��ѯʧ�ܣ��밴�����������...");
						getch();
					}
					if(flag2==1)	
					{				
						printf("\n\n������ѯ�밴 Y ,�����밴 N\n");
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
								printf("\n��ESC�˳�\n�����鼮�밴'1'\n�����鼮�밴'2'\nɾ���鼮�밴'3'��");
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
						case '4'://�����Ա��Ϣ 
							while(flag1)
							{
								char choice1;
								int cnd; 
								print_member();
								printf("\n��ESC�˳�\n��'1'���Ļ�Ա��Ϣ\n��'2'���ӻ�Ա\n��'3'ɾ����Ա��");
								fflush(stdin);
								choice1=getche();
									if(choice1=='1')
									{
										char member_i[15];
										printf("\n��������Ҫ�޸ĵĻ�Ա�˺Ż��û���");
										gets(member_i);
										revise_infor(member_i); 
									}
									if(choice1=='2')
									{ 
										cnd=member_sign();	
										if(cnd==1)
											printf("\n��������û������������");
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
						case '5'://���������Ϣ 
							while(flag1)
							{
								char choice1;
								print_borrow();//��ӡ���н�����Ϣ 
								flag1=admin_borrow();//���������Ϣ 		
							}
							break;
						case '6':
							fun=0; 
					}
				}
			}
				else if(num==0)
				{
						printf("������������ԡ�"); 
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
	printf("���Ѿ��˳�ϵͳ!(��������رս���)\n\n\t��ӭ�����ٴ�ʹ��!\n");
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
	printf("\t\t\t\t|*|         ��ӭʹ��ͼ�����ϵͳ         |*|\n");
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
	printf("\t\t\t\t|*|   (1).��Ա��¼                       |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|   (2).��Աע��                       |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|   (3).����Ա��¼                     |*|\n");
	printf("\t\t\t\t|*|                                      |*|\n");
	printf("\t\t\t\t|*|   (4).�˳�ϵͳ                       |*|\n");
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
	printf("\t\t\t\t|*|         * | ��-Ա-��-�� | *         |*|\n");
	printf("\t\t\t\t|*|                                     |*|\n");
	printf("\t\t\t\t|*|   (1).����ͼ����Ϣ                  |*|\n");
	printf("\t\t\t\t|*|   (2).����ͼ��                      |*|\n");
	printf("\t\t\t\t|*|   (3).�黹ͼ��                      |*|\n");
	printf("\t\t\t\t|*|   (4).�˺���Ϣ                      |*|\n");
	printf("\t\t\t\t|*|   (5).����ͼ����Ϣ                  |*|\n");
	printf("\t\t\t\t|*|   (6).�˺ŵǳ�                      |*|\n");
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
	printf("\t\t\t\t|*|         * | ��-��-Ա-��-�� | *         |*|\n");
	printf("\t\t\t\t|*|                                        |*|\n");
	printf("\t\t\t\t|*|   (1).����ͼ��                         |*|\n");
	printf("\t\t\t\t|*|   (2).���һ�Ա                         |*|\n");
	printf("\t\t\t\t|*|   (3).����ͼ����Ϣ                     |*|\n");
	printf("\t\t\t\t|*|   (4).�����Ա��Ϣ                     |*|\n");
	printf("\t\t\t\t|*|   (5).���������Ϣ                     |*|\n");
	printf("\t\t\t\t|*|   (6).�˳�����Ա�˺�                   |*|\n");
	printf("\t\t\t\t|*|                                        |*|\n");
	printf("\t\t\t\t|*|                                        |*|\n");
	printf("\t\t\t\t ^== == == == == == == == == == == == == ==^\n");
	printf("\n\n\n");
	
}
void draw_member()//��Ա��¼ͼ�� 
{
	system("cls");
	printf("��ESC���˳�\n"); 
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
	printf("\t\t\t|*|  �鼮��� |*|   ����    |*|    ����   |*|    λ��   |*|   ����   |*|�ݲ�|*|���|*|\n");
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
	printf("\t\t\t|*|  �鼮��� |*|   ����    |*|    ����   |*|    λ��   |*|   ����   |*|�ݲ�|*|���|*|\n");
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
	printf("\t\t\t|*|  �鼮��� |*|   ����    |*|    ����   |*|    ����   |*|   ������   |*|\n");
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
	printf("\t\t\t|*|  �û���  |*|    �˺�    |*|    ����   |*|    �Ա�   |*|   ����   |*|    �ܱ�    |*|\n");
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
	printf("\t\t\t|*|  �û���  |*|    �˺�    |*|    ����   |*|    �Ա�   |*|   ����   |*|    �ܱ�    |*|\n");
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
	
	while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(fp,"%s %s %s %s %d %s\n",member[number].name,member[number].ID,member[number].password,member[number].sex,&member[number].old_year,member[number].password_key);
		number++;
	}
	
	fclose(fp);
	for(n=0;n<number;n++)//��֤�˺��Ƿ���� 
		if((strcmp(member[n].name,member_account))==0||(strcmp(member[n].ID,member_account))==0)
			{
				flag1=1;
				break;
				
			}
			
	if(flag1)
	{
		printf("\n\n\t\t\t\t\t��¼���룺");
		while(flag2)
		{
			flag2=member_possword(member[n].password);
			if(flag2==1)
			{	
				printf("\n>>>��֤�ɹ�\n>>>���ڼ�����...\n");
				return 1; 
			}
			else if(flag2==0) 
			{
				printf("\n	������֤ʧ��,�Ƿ�ʹ���ܱ�(Y/N):");
				choice=getche();
				while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      				choice=getche();
 				if(choice=='Y'||choice=='y')
				{
					printf("\n\t\t\t\t\t�ܱ���¼��");
					flag=member_possword(member[n].password_key);
					if(flag==1)
						return 1;
					if(flag==2)
						return 2;
				}
				else
					printf("\n\t\t\t\t\t��¼���룺");
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
		printf("\nδ�ҵ������˺Ż��û��������л���Сд������\n�����������");
		getch();
		return 0; 
	}
	
}


int member_possword(char member_possword[15])//����ȶԺ��� 
{
	char account[15]={0},num;
	int i=0;
	fflush(stdin);
	while((num=getch())!=13)//δ����س�ʱѭ�� 
	{
		if(num==27)//esc���˳� 
		{
			return 2;
		}
		if(num==8)//�����˸��ʱ���ǰһ���� 
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

int query_book(char name_id[30])//����ͼ����Ϣ 
{
	FILE *bk;
	LIBRARY_BOOK books[150]={0};
	int number=0,n,flag1=0,flag2;
	
	bk=fopen("library.txt","r");
	while(!feof(bk))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(bk,"%s %s %s %s %s %d %d\n",books[number].ID,books[number].name,books[number].writer,books[number].position,books[number].type,&books[number].quantity,&books[number].lend);
		number++;
	}	
	fclose(bk);
	for(n=0;n<number;n++)
		if((strcmp(books[n].ID,name_id))==0||(strcmp(books[n].name,name_id))==0)//�Ա��Ƿ��д��鼮��Ϣ 
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

void lend_book(char book_name[30],char member_id[15])//�鼮������� 
{
	FILE *bk,*p1,*p2,*br;
	LIBRARY_BOOK books[150];
	LEND lend_book[200]={0};
	int number,n,i,flag0,flag1,flag2=1,number1;
	number=number1=flag1=0;
	
	bk=fopen("library.txt","r");
	while(!feof(bk))//���ļ��е����ݵ����������Ľṹ���� 
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
			printf("\n���ʧ�ܣ����޴���\n");
			return;
		}

		p1=fopen("borrow.txt","r");
		while(!feof(p1))//���ļ��е����ݵ����������Ľṹ���� 
		{
			fscanf(p1,"%s %s %s %s %s\n",lend_book[number1].number,lend_book[number1].name,lend_book[number1].writer,lend_book[number1].type,lend_book[number1].account);
			number1++;
		}	
		fclose(p1);
		for(i=0;i<number1;i++)//��ѯ�Ƿ��ظ����� 
			if(((strcmp(lend_book[i].number,book_name))==0||(strcmp(lend_book[i].name,book_name))==0)&&(strcmp(lend_book[i].account,member_id))==0)
			{
				flag2=0;
				printf("\n\n\n\n\n����ʧ�ܣ����ѽ��Ĵ��飬�����ظ�����\n"); 
				break;
			}
		
		p2=fopen("borrow.txt","a");
		if(flag2)
		{
	        fprintf(p2,"%s %s %s %s %s\n",books[n].ID,books[n].name,books[n].writer,books[n].type,member_id);
	        fclose(p1);
        	printf("\n\n\n\n���ѳɹ����Ĵ��飬����15���ڹ黹������\n");
        	flag0=1;
        }
        fclose(p2);
        if(flag0)
        {
        	books[n].lend--;
	        bk=fopen("library.txt","w");
			for(i=0;i<number;i++)//���ļ��е����ݵ����������Ľṹ���� 
			{
				fprintf(bk,"%s %s %s %s %s %d %d\n",books[i].ID,books[i].name,books[i].writer,books[i].type,books[i].position,books[i].quantity,books[i].lend);
				
			}	
			fclose(bk);
		}
 } 

void return_book(char book_return[30],char member_id[15])//�鼮�黹���� 
{
	FILE *fp1,*fp2,*bk;
	LEND lend_books[150];
	LIBRARY_BOOK books[150];
	int flag0,flag1,number,number1,i,n,k;
	flag1=number=number1=i=0;
	
	fp1=fopen("borrow.txt","r");
	while(!feof(fp1))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(fp1,"%s %s %s %s %s\n",lend_books[number].number,lend_books[number].name,lend_books[number].writer,lend_books[number].type,lend_books[number].account);
		number++;
	}	
	fclose(fp1);
	
	for(i=0;i<number;i++)//��ѯ�Ƿ���� 
		if(((strcmp(lend_books[i].number,book_return))==0||(strcmp(lend_books[i].name,book_return))==0)&&(strcmp(lend_books[i].account,member_id))==0)
		{
			flag1=1;
			break;
		}
	
	
 
	bk=fopen("library.txt","r");//Ϊ���޸Ĺ���ʣ���鼮���� 
	while(!feof(bk))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(bk,"%s %s %s %s %s %d %d\n",books[number1].ID,books[number1].name,books[number1].writer,books[number1].type,books[number1].position,&books[number1].quantity,&books[number1].lend);
		number1++;
	}	
	fclose(bk);
	for(k=0;k<number1;k++)
		if((strcmp(books[k].ID,book_return))==0||(strcmp(books[k].name,book_return))==0)
			break;
		
	if(flag1)//����д��borrow�ļ� 
	{
		fp2=fopen("borrow.txt","w");
		for(n=0;n<number;n++)
		{
			if(n!=i)	
				fprintf(fp2,"%s %s %s %s %s\n",lend_books[n].number,lend_books[n].name,lend_books[n].writer,lend_books[n].type,lend_books[n].account);
		}
		fclose(fp2);
		printf("\n\n\n����ɹ�\n");
		flag0=1;
	}
	if(flag1==0)
	{
		printf("\n\n\n����ʧ�ܣ�δ��ѯ�������Ĵ���\n");
		printf("�볢�����Ի�ѯ��ͼ�����Ա\n");
	}
	
	if(flag0)
        {
        	books[k].lend++;
	        bk=fopen("library.txt","w");
			for(i=0;i<number1;i++)//���ļ��е����ݵ����������Ľṹ���� 
			{
				fprintf(bk,"%s %s %s %s %s %d %d\n",books[i].ID,books[i].name,books[i].writer,books[i].type,books[i].position,books[i].quantity,books[i].lend);
				
			}	
			fclose(bk);
		}
}

void member_information(char member_id[15])//��ʾ��Ա������Ϣ 
{
	FILE *fp;
	int n,i,number=0,flag1=0;
	MEMBER member_infor[150];
	
	fp=fopen("information.txt","r");
	while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(fp,"%s %s %s %s %d %s\n",member_infor[number].name,member_infor[number].ID,member_infor[number].password,member_infor[number].sex,&member_infor[number].old_year,member_infor[number].password_key);
		number++;
	}	
	fclose(fp);
	
	for(i=0;i<number;i++)//��λ������Ϣ 
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

void revise_infor(char member_ID[15])//�޸ĸ�����Ϣ���� 
{
	FILE *fp,*p1;
	int n,i,number=0,flag1=0;
	MEMBER revise_infor[150];
	char cho;
	
	fp=fopen("information.txt","r");
	while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(fp,"%s %s %s %s %d %s\n",revise_infor[number].name,revise_infor[number].ID,revise_infor[number].password,revise_infor[number].sex,&revise_infor[number].old_year,revise_infor[number].password_key);
		number++;
	}	
	fclose(fp);
	
	for(i=0;i<number;i++)//��λ������Ϣ 
		if((strcmp(revise_infor[i].name,member_ID))==0||(strcmp(revise_infor[i].ID,member_ID))==0)
		{
			flag1=1;
			break;
		}
	
	if(flag1)
	{
		printf("\n\n��Ҫ�޸��û�����Y/N\n");
		fflush(stdin);
		cho=getch();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getch();
		if(cho=='Y'||cho=='y')
		{
			printf("\n���������û�����");
			scanf("%s",&revise_infor[i].name);
			printf("\n�޸ĳɹ�");
		}
		
		printf("\n\n��Ҫ�޸��˺���Y/N\n");
		fflush(stdin);
		cho=getch();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getch();
		if(cho=='Y'||cho=='y')
		{
			printf("\n���������˺ţ�");
			scanf("%s",&revise_infor[i].ID);
			printf("\n�޸ĳɹ�");
		}
		
		printf("\n��Ҫ�޸ĵ�½������Y/N\n");
		fflush(stdin);
		cho=getche();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getche();
		if(cho=='Y'||cho=='y')
		{
			printf("\n�����������룺");
			scanf("%s",&revise_infor[i].password);
			printf("\n�޸ĳɹ�");
		}
		
		printf("\n��Ҫ�޸��Ա���Y/N\n");
		fflush(stdin);
		cho=getche();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getche();
		if(cho=='Y'||cho=='y')
		{
			printf("\n'man' or 'woman'\n");
			scanf("%s",&revise_infor[i].sex);
			printf("\n�޸ĳɹ�\n");
		}
		
		printf("\n��Ҫ�޸�������Y/N\n");
		fflush(stdin);
		cho=getche();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getche();
		if(cho=='Y'||cho=='y')
		{
			printf("\n�����������䣺");
			scanf("%s",&revise_infor[i].old_year);
			printf("\n�޸ĳɹ�\n");
		}
		
		printf("\n��Ҫ�޸��ܱ���Y/N\n");
		fflush(stdin);
		cho=getche();
		while(cho!='Y'&&cho!='y'&&cho!='N'&&cho!='n')
	     	cho=getche();
		if(cho=='Y'||cho=='y')
		{
			printf("\n���������ܱ���");
			scanf("%s",&revise_infor[i].password_key);
			printf("\n�޸ĳɹ�\n");
		}
		
		p1=fopen("information.txt","w");
			for(n=0;n<number;n++)
				fprintf(p1,"%s %s %s %s %d %s\n",revise_infor[n].name,revise_infor[n].ID,revise_infor[n].password,revise_infor[n].sex,revise_infor[n].old_year,revise_infor[n].password_key);

		fclose(p1);
	}
} 

void print_library()//��ӡ�����鼮��Ϣ 
{
	FILE *fp;
	LIBRARY_BOOK book_s[150];
	int n,i,number;
	number=i=0;
	n=7; 
	
	fp=fopen("library.txt","r");
	while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
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

int member_sign()//��Աע�ắ�� 
{
	FILE *fp;
	MEMBER member_infor[150];
	int number,i,n,flag1,flag2,flag3,flag4,old;
	char member_name[15],member_id[15],member_password[15],member_sex[5],member_passwordkey[20],num;
	i=number=flag4=0;
	
	fp=fopen("information.txt","r");
	while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(fp,"%s %s %s %s %d %s\n",member_infor[number].name,member_infor[number].ID,member_infor[number].password,member_infor[number].sex,&member_infor[number].old_year,member_infor[number].password_key);
		number++;
	}	
	fclose(fp);
	
	while(flag1)
	{
		system("cls");
		printf("��ESC���˳�\n");
		i=0;
		flag1=flag2=1;
		draw_sign();
		goto_xy(36,7);
		printf("�û�����             ");
		goto_xy(43,7);
		fflush(stdin); 
		while((num=getche())!=13)//δ����س�ʱѭ�� 
		{
			if(num==27)//esc���˳� 
			{
				return 0;
			}
			if(num==8)//�����˸��ʱ���ǰһ���� 
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
				printf("\n�û����Ѵ��ڣ������������������");
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
			printf("�˺ţ�             ");
			goto_xy(43,9); 
			fflush(stdin); 
			while((num=getche())!=13)//δ����س�ʱѭ�� 
			{
				if(num==27)//esc���˳� 
				{
					return 0;
				}
				if(num==8)//�����˸��ʱ���ǰһ���� 
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
				printf("\n�˺��Ѵ��ڣ������������������");
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
			printf("���룺             ");
			goto_xy(43,11);
			fflush(stdin); 
			while((num=getche())!=13)//δ����س�ʱѭ�� 
			{
				if(num==27)//esc���˳� 
				{
					return 0;
				}
				if(num==8)//�����˸��ʱ���ǰһ���� 
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
				printf("\n�����Ѵ��ڣ������������������");
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
		printf("�Ա�         (man or woman)");
		goto_xy(43,13);
		fflush(stdin); 
		while((num=getche())!=13)//δ����س�ʱѭ�� 
		{
			if(num==27)//esc���˳� 
			{
				return 0;
			}
			if(num==8)//�����˸��ʱ���ǰһ���� 
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
		printf("���䣺         ");
		goto_xy(43,15);
		fflush(stdin); 
		scanf("%d",&old);
		
			i=0;
			goto_xy(36,17);
			printf("�ܱ�(��������)��             "); 
			goto_xy(49,17);
			fflush(stdin); 
			while((num=getche())!=13)//δ����س�ʱѭ�� 
			{
				if(num==27)//esc���˳� 
				{
					return 0;
				}
				if(num==8)//�����˸��ʱ���ǰһ���� 
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

int query_member(char member_id[15])//���һ�Ա��Ϣ 
{
	FILE *mk;
	MEMBER members[150]={0};
	int number=0,n,flag1=0,flag2;
	
	mk=fopen("information.txt","r");
	while(!feof(mk))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(mk,"%s %s %s %s %d %s\n",members[number].name,members[number].ID,members[number].password,members[number].sex,&members[number].old_year,members[number].password_key);
		number++;
	}	
	fclose(mk);
	for(n=0;n<number;n++)
		if((strcmp(members[n].ID,member_id))==0||(strcmp(members[n].name,member_id))==0)//�Ա��Ƿ��д��鼮��Ϣ 
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
	while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(fp,"%s %s %s %s %s %d %d\n",book_change[number].ID,book_change[number].name,book_change[number].writer,book_change[number].position,book_change[number].type,&book_change[number].quantity,&book_change[number].lend);
		number++;
	}	
	fclose(fp);
	printf("\n������Ҫ�����鼮�ı�ţ�");
	gets(change);
	for(n=0;n<number;n++)//�Ա��Ƿ��д��鼮��Ϣ
		if((strcmp(book_change[n].ID,change))==0||(strcmp(book_change[n].name,change))==0) 
		{
			flag1=1;
			break;
		}
	
	if(flag1)
	{
		printf("�Ƿ�����鼮���(Y/N)��");
		fflush(stdin); 
		fflush(stdin);
		choice1=getche();
		while(choice1!='Y'&&choice1!='y'&&choice1!='N'&&choice1!='n')
      		choice1=getche();
      	if(choice1=='Y'||choice1=='y')
      	{
		  	printf("\n�������±�ţ�");
      		gets(book_change[n].ID);
      	}
      	
      	printf("\n�Ƿ�����鼮��(Y/N)��");
      	fflush(stdin);
      	choice2=getche(); 
		while(choice2!='Y'&&choice2!='y'&&choice2!='N'&&choice2!='n')
      		choice2=getche();
      	if(choice2=='Y'||choice2=='y')
      	{
			 printf("\n���������鼮����");
      		gets(book_change[n].name);
      	}
      	
      	printf("\n�Ƿ�����鼮����(Y/N)��");
      	fflush(stdin);
      	choice3=getche(); 
		while(choice3!='Y'&&choice3!='y'&&choice3!='N'&&choice3!='n')
      		choice3=getche();
      	if(choice3=='Y'||choice3=='y')
      	{
		  	printf("\n����������������");
      		gets(book_change[n].writer);
      	}
      	
      	printf("\n�Ƿ�����鼮���λ��(Y/N)��");
      	fflush(stdin);
      	choice4=getche(); 
		while(choice4!='Y'&&choice4!='y'&&choice4!='N'&&choice4!='n')
      		choice4=getche();
      	if(choice4=='Y'||choice4=='y')
      	{
			printf("\n��������λ�ã�");
      		gets(book_change[n].position);
      	}
      	
      	printf("\n�Ƿ�����鼮����(Y/N)��");
      	fflush(stdin);
      	choice5=getche(); 
		while(choice5!='Y'&&choice5!='y'&&choice5!='N'&&choice5!='n')
      		choice5=getche();
      	if(choice5=='Y'||choice5=='y')
      	{
      		printf("\n���������鼮���ͣ�");
      		gets(book_change[n].type);
      	}
      	
      	printf("\n�Ƿ���Ĺݲ���(Y/N)��");
      	fflush(stdin);
      	choice6=getche(); 
		while(choice6!='Y'&&choice6!='y'&&choice6!='N'&&choice6!='n')
      		choice6=getche();
      		
      	if(choice6=='Y'||choice6=='y')
      	{ 
      		printf("\n��������º�ݲ�����");
      		scanf("%d",&book_change[n].quantity);
      	}	
      	
      	printf("\n�Ƿ���Ĺ���ʣ������(Y/N)��");
      	fflush(stdin);
      	choice7=getche(); 
		while(choice7!='Y'&&choice7!='y'&&choice7!='N'&&choice7!='n')
      		choice7=getche();
      	if(choice7=='Y'||choice7=='y')
      	{
		 	printf("\n��������º�ʣ��������");
      		scanf("%d",&book_change[n].lend);	
		}		
		printf("\n�������\n");
		getch();		
	} 
	
	p1=fopen("library.txt","w");
	for(i=0;i<number;i++)//����д���鼮��Ϣ 
		fprintf(p1,"%s %s %s %s %s %d %d\n",book_change[i].ID,book_change[i].name,book_change[i].writer,book_change[i].position,book_change[i].type,book_change[i].quantity,book_change[i].lend);	
	fclose(p1);	
}

void add_book()
{
	FILE *fp;
	char choice;
	int number=0;
	LIBRARY_BOOK addbook[10];
	
	printf("\n�������鼮��ţ�");
    gets(addbook[0].ID);
    printf("\n�������鼮���ƣ�");
    gets(addbook[0].name);
	printf("\n�������鼮���ߣ�");
    gets(addbook[0].writer);
    printf("\n�������鼮���λ�ã�");
    gets(addbook[0].position);
    printf("\n�������鼮���ͣ�");
    gets(addbook[0].type);
    printf("\n�������鼮�ݲ�����");
    scanf("%d",&addbook[0].quantity);
    addbook[0].lend=0;
    
    printf("ȷʵ������鼮��Ϣ��?(Y/N)��");
    fflush(stdin);
    choice=getche();
   	while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      	choice=getche();
    if(choice=='Y'||choice=='y')
    {	
		fp=fopen("library.txt","a");
		fprintf(fp,"%s %s %s %s %s %d %d\n",addbook[0].ID,addbook[0].name,addbook[0].writer,addbook[0].position,addbook[0].type,addbook[0].quantity,addbook[0].lend);	
		fclose(fp);
		printf("\n����ɹ���\n");
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
	while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(fp,"%s %s %s %s %s %d %d\n",delete_book[number].ID,delete_book[number].name,delete_book[number].writer,delete_book[number].position,delete_book[number].type,&delete_book[number].quantity,&delete_book[number].lend);
		number++;
	}	
	fclose(fp);
	printf("\n������Ҫɾ�����鼮��ţ�");
	gets(dele);
	for(n=0;n<number;n++)//�Ա��Ƿ��д��鼮��Ϣ
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
	printf("\nɾ���ɹ������������\n");
	getch();
	}
}
void print_member()//��ӡ���л�Ա��Ϣ 
{
	FILE *fp;
	MEMBER members[150];
	int n,i,number;
	number=i=0;
	n=7; 
	
	fp=fopen("information.txt","r");
	while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
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

void delete_member()//ɾ����Ա 
{
	FILE *fp,*p1;
	MEMBER members[150];
	char member_d[15],input;
	int n,i,number,flag;
	number=flag=0;
	
	fp=fopen("information.txt","r");
	while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(fp,"%s %s %s %s %d %s\n",members[number].name,members[number].ID,members[number].password,members[number].sex,&members[number].old_year,members[number].password_key);
		number++;
	}	
	fclose(fp);
	printf("\n������Ҫɾ���Ļ�Ա�˺Ż��û���:");
	gets(member_d);
	for(n=0;n<number;n++)
		if((strcmp(members[n].ID,member_d))==0||(strcmp(members[n].name,member_d))==0)//�Ա��Ƿ��д��鼮��Ϣ 
			break;
	
	printf("\nȷ��ɾ���û�Ա��Ϣ��(Y/N)");
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

void print_borrow()//��ӡ���н�����Ϣ 
{
	FILE *fp;
	LEND lend_books[150];
	int n,i,number;
	number=i=0;
	n=7; 
	
	fp=fopen("borrow.txt","r");
	while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
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

int admin_borrow()//���������Ϣ���� 
{
	FILE *fp,*p1;
	LEND borrows[150];
	char choice1,name_id[15],book_id[15],choice;
	int number,i,n,flag1;
	number=i=n=flag1=0;
	
	printf("\n��ESC�˳�\n��'1'�޸Ľ�����Ϣ\n��'2'ɾ��������Ϣ��");
	choice1=getche();
	while(choice1!='1'&&choice1!='2'&&choice1!=27)
    	choice1=getche();
    if(choice1=='1')
    {
    	printf("\n��������Ҫ�޸ĵ��鼮��źͽ�����\n");
		printf("\n�鼮��ţ�");
		gets(name_id);
		printf("\n������");
		gets(book_id); 
		
		fp=fopen("borrow.txt","r");
		while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
		{
			fscanf(fp,"%s %s %s %s %s\n",borrows[number].number,borrows[number].name,borrows[number].writer,borrows[number].type,borrows[number].account);
			number++;
		}	
		fclose(fp);
		
		for(i=0;i<number;i++)//��λ������Ϣ 
		if((strcmp(borrows[i].number,name_id))==0&&(strcmp(borrows[i].account,book_id))==0)
		{
			flag1=1;
			break;
		}
		
	if(flag1) 
	{
		printf("\n�Ƿ�����鼮���(Y/N)��");
      	fflush(stdin);
      	choice=getche(); 
		while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      		choice=getche();
      	if(choice=='Y'||choice=='y')
      	{
		  	printf("\n���������鼮��ţ�");
      		gets(borrows[i].number);
      	}
      	
      	printf("\n�Ƿ�����鼮��(Y/N)��");
      	fflush(stdin);
      	choice=getche(); 
		while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      		choice=getche();
      	if(choice=='Y'||choice=='y')
      	{
		  	printf("\n���������鼮����");
      		scanf("%s",&borrows[i].name);
      	}
      	
      	printf("\n�Ƿ�����鼮����(Y/N)��");
      	fflush(stdin);
      	choice=getche(); 
		while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      		choice=getche();
      	if(choice=='Y'||choice=='y')
      	{
		  	printf("\n���������鼮���ߣ�");
      		scanf("%s",&borrows[i].writer);
      	}
      	
      	printf("\n�Ƿ�����鼮����(Y/N)��");
      	fflush(stdin);
      	choice=getche(); 
		while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      		choice=getche();
      	if(choice=='Y'||choice=='y')
      	{
		  	printf("\n���������鼮���ͣ�");
      		gets(borrows[i].type);
      	}
      	
      	printf("\n�Ƿ���Ľ�����(Y/N)��");
      	fflush(stdin);
      	choice=getche(); 
		while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
      		choice=getche();
      	if(choice=='Y'||choice=='y')
      	{
		  	printf("\n�������½����ˣ�");
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
		printf("\n��������Ҫɾ�����鼮��źͽ�����\n");
		printf("\n�鼮��ţ�");
		gets(name_id);
		printf("\n������");
		gets(book_id); 
		
		fp=fopen("borrow.txt","r");
	while(!feof(fp))//���ļ��е����ݵ����������Ľṹ���� 
	{
		fscanf(fp,"%s %s %s %s %s\n",borrows[number].number,borrows[number].name,borrows[number].writer,borrows[number].type,borrows[number].account);
		number++;
	}	
	fclose(fp);
	
	for(i=0;i<number;i++)//��λ������Ϣ 
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

void transit()//���ɺ��� 
{
	title();
	printf("\n����Ŭ��������...."); 
	Sleep(1500);
	printf("\n�������...");
	Sleep(750);
 } 
 
void goto_xy(int x, int y)//��λ���λ�õ�ָ������
{   
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x,y };
    SetConsoleCursorPosition(hOut, pos);
}
