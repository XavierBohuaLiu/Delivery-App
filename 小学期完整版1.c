#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
struct administrators_information
{
	char ID[12];
	char secret[15];
	char restaurant[15];
	int restaurant_ID;
	char name[10];
	char e_mail[20];
}; 
typedef struct administrators_information Adm;
typedef struct nodea 
{
	Adm adm;
	struct nodea *next;
}Nodea,*pNodea;
typedef struct boxa
{
	pNodea phead;
	pNodea plast;
	pNodea position_adm;
}Boxa;

struct user_information
{
	char ID[12];
	char secret[15];
	char name[10];
	char sex[6];
	char number[14];
	char area[15];
	int location_x;
	int location_y;
	char e_mail[20];
}; 
typedef struct user_information User;
typedef struct nodeu 
{
	User user;
	struct nodeu *next;
}Nodeu,*pNodeu;
typedef struct boxu 
{
	pNodeu phead;
	pNodeu plast;
	pNodeu position_user;
}Boxu;

struct service_Time
{
	int openingtime;
	int closingtime;
	char time[20];
};
struct Restaurant
{
	int ID;
	char name[15];
	char cuisine[5];          //菜系
	float Price;               //起送价
	float fee;                 //配送费
	float arrivingtime;        //平均配送时间
	struct service_Time timing;    //服务时间
	int location_x;            //餐馆x坐标
	int location_y;            //餐馆y坐标
	char location[12];         //地理区域
	float grade;               //评分
	double distance;            //与客户的距离 
	int sell;                  //销量 
	int order_frequency;        //送餐次数 
};


struct meal_information
{	
	int restaurant_ID;
	char name[10];
	double price;
	int recm;//推荐数
	int count;//已售份数 
}; 
typedef struct meal_information Meal;

struct Time
{
	int hour;
	int minute;
};
struct Dish
{
	int dish_amount;
	char dish_name[10];
	char recommend[5];
	double dish_prize;
};
typedef struct user_order
{
	int restaurant_ID;
	char user_ID[12];
	struct Dish dishes[5];
	int type_dish;
	int customer_locaition_x;
	int customer_locaition_y; 
	float evaluation;  //用户评分 
	struct Time delivery_time[15];
	struct Time time;	   //用户下单时间  
	double prize; 
}Order;

void main_menu();//主菜单函数 
void loginmenu_user();//用户登入函数 
void loginmenu_adm();//管理员登入函数
void customer_menu();//用户菜单函数 
void manager_menu();//管理员菜单函数
void order_manage_menu(); 

void loaduser();
void addusernode();//
void checkuser();//用户信息检查函数 
void change_userinformation();
void change_user_secret();
void change_user_e_mail();
void change_user_phone();
void save_userchanged();
void emptylistu(pNodeu plist);//



void loadadm();
void addadmnode();
void checkadm();//管理员信息检查函数 
void change_adminformation();
void change_adm_secret();
void change_adm_e_mail();
void save_admchanged();
void emptylista(pNodea plist);

void customer_menu_1();
void res_viewbyname();//通过餐馆名字查询 
void res_viewbydistance();//通过餐馆距离查询 
void res_viewby_mealtype();//通过菜系查询 
void res_viewbyactivity();//通过有无促销活动查询 
void res_viewbysell();//通过餐馆销量查询 
void res_viewbyspeed();//通过配送速度查询 
void res_viewbygrade(); //通过餐馆评分查询 

void order_meal();//
void meal_menu_customer(int restaurant_ID);
void choose_meal(int restaurant_ID,Meal meal_stored[12],int longofmenu);
void manage_meal(int restaurant_ID);//
void meal_menu_adm(int restaurant_ID);
void add_meal(int restaurant_ID);
void publish_delete_meal(int restaurant_ID);
void publish_meal(int restaurant_ID);
void delete_meal(int restaurant_ID);
FILE *open_restaurantfile1(int restaurant_ID);//
FILE *open_restaurantfile2(int restaurant_ID);//

struct tm *timeof_order();
void add_order(Order order_tempsave);
void time_calculate(int x1,int y1,int x2,int y2,int *phour,int *pminute);
void payof_order();
void recommand_and_evaluate();
void save_paidorder(Order *orderforsave);
void cancel_order();
void delete_stored_order(int ordernum);
void view_orderlist();
void view_nonpayment_orderlist();
void view_orderlist_sortbyprize();
void view_orderlist_sortbygrade(); 


struct Restaurant res[15]={
  {0,"小熊炸鸡","西餐",20,0,30,{11,22,"11:00-22:00"},3,8,"（3，8）",4.8,0,0,2},
  {1,"过桥米线","中餐",15,2,30,{10,21,"10:00-21:00"},4,7,"(4，7)",4.8,0,0,2},
  {2,"超级小炒","中餐",20,1,33,{11,23,"11:00-23:00"},2,7,"(2，7)",4.9,0,0,2},
  {3,"凉皮","中餐",20,2,30,{11,20,"11:00-20:00"},4,6,"(4，6)",4.9,0,0,2},
  {4,"牛牛堡","西餐",20,2,35,{11,20,"11:00-20:00"},5,6,"（5，6）",4.8,0,0,2},
  {5,"京都烧烤","中餐",30,3,40,{15,5,"15:00-5:00"},6,9,"（6，9）",4.8,0,0,2},
  {6,"小牛锅贴","中餐",20,2,35,{0,24,"00:00-24:00"},1,2,"（1，2）",4.7,0,0,2},
  {7,"甜品店","西餐",30,0,30,{10,19,"10:00-19:00"},2,3,"（2，3）",4.8,0,0,2},
  {8,"重庆火锅","中餐",30,3,50,{0,24,"00:00-24:00"},4,1,"（4，1）",4.9,0,0,2},
  {9,"比萨披萨","西餐",30,2,40,{11,24,"11:00-20:00"},8,4,"（8，4）",4.7,0,0,2},
  {10,"肯德基","西餐",15,5,30,{0,24,"00:00-24:00"},7,3,"（7，3）",4.7,0,0,2},
  {11,"茶百道","饮品",20,2.5,40,{11,21,"11:00-21:00"},1,6,"（1，6）",4.8,0,0,2},
  {12,"乐乐茶","饮品",30,6,55,{10,21,"10:00-21:00"},9,7,"（9，7）",4.7,0,0,2},
  {13,"星巴克","饮品",30,5,50,{10,22,"10:00-22:00"},9,2,"（9，2）",5,0,0,2},
  {14,"鱼籽拌饭","中餐",20,3,32,{11,20,"11:00-20:00"},5,3,"（5，3）",4.6,0,0,2},
};
Boxa Lista;
Adm t_adm;
Boxu Listu;
User t_user;
Order stored_order[15];   //存储订单的结构体数组（未付款）
Order stored_paidorder[15];  //存储已付款订单的结构体数组 
Order order_rank[15];
int order_count=0;      //存储的未付款订单的数目 
int paidorder_count=0; 
Meal meal_forpublish[8];
int value=0;
struct Restaurant res_rank[15];


int input_errorcheck(char check[],int num)
{
	if(strlen(check)>=2)
	return -1;
	if(check[0]>=48&&check[0]<=num+48)
		return (int)check[0]-48;
	else return -1;
}

void main_menu() 
{
	printf("****************************\n");
	printf("|                          |\n");
	printf("|欢迎使用订餐系统!         |\n");
	printf("|                          |\n");
	printf("|<1>顾客身份操作           |\n");
	printf("|<2>管理员身份操作         |\n");
	printf("|<0>退出系统               |\n");
	printf("|                          |\n");
	printf("****************************\n");
	printf("请选择：");
	char choice[8];
	while(1)
	{
		scanf("%s",choice); 
		int n=input_errorcheck(choice,2);
		if(n==0)
		exit(0);
		if(n==1)
		loginmenu_user();
		if(n==2)
		loginmenu_adm();
		printf("输入错误，请重新输入\n");
	}
}

void loginmenu_user() 
{
	printf("****************************\n");
	printf("|                          |\n");
	printf("|欢迎使用订餐系统！        |\n");
	printf("|                          |\n");
	printf("|<1>登录                   |\n");
	printf("|<2>注册                   |\n");
	printf("|<3>返回上一级             |\n");
	printf("|<0>退出系统               |\n");
	printf("|                          |\n");
	printf("****************************\n");
	printf("请选择：");
	loaduser();
  	char choice[8];
	while(1)
	{
		scanf("%s",choice); 
		int n=input_errorcheck(choice,3);
		if(n==0)
		exit(0);
		if(n==1)
		{
			checkuser();
			customer_menu();
		}
		if(n==2)
		{
			addusernode();
			loginmenu_user();
		}
		if(n==3)
			main_menu();		
		printf("输入错误，请重新输入\n");
	}
}



void loginmenu_adm() 
{
	printf("****************************\n");
	printf("|                          |\n");
	printf("|欢迎使用订餐系统！        |\n");
	printf("|                          |\n");
	printf("|<1>登录                   |\n");
	printf("|<2>注册                   |\n");
	printf("|<3>返回上一级             |\n");
	printf("|<0>退出系统               |\n");
	printf("|                          |\n");
	printf("****************************\n");
	printf("请选择：");
	loadadm();
	char choice[8];
	while(1)
	{
		scanf("%s",choice); 
		int n=input_errorcheck(choice,3);
		if(n==0)
		exit(0);
		if(n==1)
		{
			checkadm();
  			manager_menu();
		}
		if(n==2)
		{
			addadmnode();
  			loginmenu_adm();
		}
		if(n==3)
			main_menu();		
		printf("输入错误，请重新输入\n");
	}
}




void customer_menu()
{
	
	printf("****************************\n");
	printf("|                          |\n");
	printf("|<1>查看餐馆               |\n");
	printf("|<2>查看订单记录           |\n");
	printf("|<3>订单付款               |\n");
	printf("|<4>取消订单               |\n");
	printf("|<5>个人信息管理           |\n");
	printf("|<6>返回上一级             |\n");
	printf("|<0>退出系统               |\n");
	printf("|                          |\n");
	printf("****************************\n");
	printf("请选择：");
	char choice[8];
	while(1)
	{
		scanf("%s",choice); 
		int n=input_errorcheck(choice,6);
		switch(n)
		{
			case 1:	customer_menu_1();
					break;
			case 2: view_orderlist();
					break;
			case 3: payof_order();
					break;
			case 4: cancel_order();
					break;
			case 5: change_userinformation();
					break;
			case 6:	loginmenu_user();
					break; 
			case 0: exit(0);
			default:
			printf("输入错误，请重新输入\n");	
		}
	}
}


void manager_menu() 
{
	printf("****************************\n");
	printf("|                          |\n");
	printf("|<1>菜品管理               |\n");
	printf("|<2>订单管理               |\n");
	printf("|<3>个人信息管理           |\n");
	printf("|<4>返回上一级             |\n");
	printf("|<0>退出系统               |\n");
	printf("|                          |\n");
	printf("****************************\n");
	printf("请选择：");
	char choice[8];
	while(1)
	{
		scanf("%s",choice); 
		int n=input_errorcheck(choice,4);
		switch(n)
		{
			case 1: manage_meal(t_adm.restaurant_ID);
					break;
			case 2:	order_manage_menu();
					break;
			case 3: change_adminformation();
					break;
			case 4: loginmenu_adm();
					break; 
			case 0:exit(0);
			default:
			printf("输入错误，请重新输入\n");	
		}
	}
	
}


void order_manage_menu()
{
	printf("*******************************\n");
	printf("|                             |\n");
	printf("|<1>未完成订单信息            |\n");    //需按下单时间排序
	printf("|<2>已完成订单(按价格排序）   |\n");    //按价格排序并计算总收入，可按日期分区段进行排序显示
	printf("|<3>已完成订单(按评分排序）   |\n");    //按分数排序，可按日期分区段进行排序显示
	printf("|<4>返回上一级                |\n");
	printf("|<0>退出系统                  |\n");
	printf("|                             |\n");
	printf("*******************************\n");
	printf("请选择：");
	char choice[8];
	while(1)
	{
		scanf("%s",choice); 
		int n=input_errorcheck(choice,4);
		switch(n)
		{
			case 1: view_nonpayment_orderlist();
					break;
			case 2: view_orderlist_sortbyprize();
					break;
			case 3:	view_orderlist_sortbygrade();
					break;
			case 4: manager_menu();
					break;
			case 0: exit(0);
			default:
			printf("输入错误，请重新输入\n");	
		}
	}
}
				


void loaduser()
{
	FILE *fp;
	fp=fopen("user.txt","r");
	if(fp==NULL)
	{
		printf("\nCan't open user.txt");
		exit(0);
	}
	pNodeu current,prev;
	current=prev=NULL;
	current=(pNodeu)malloc(sizeof(Nodeu));
	while(fscanf(fp,"%s%s%s%s%s%d%d%s",current->user.ID,
		current->user.secret,current->user.name,current->user.sex,current->user.number,&current->user.location_x,&current->user.location_y,current->user.e_mail)!=-1) 
	{
		current->next=NULL;
		if(prev==NULL)
			Listu.phead=current;
		else
			prev->next=current;
		prev=current;
		current=(pNodeu)malloc(sizeof(Nodeu));
	}
	free(current);
	Listu.plast=prev;
	fclose(fp);
}



void addusernode()
{
	char *p;
	int state=1,em=0,temp1=0,temp2=0,checkn=0,checkl=0;
	pNodeu current;	
	current=(pNodeu)malloc(sizeof(Nodeu));
	current->next=NULL;
	if(Listu.plast==NULL)
		Listu.phead=current;
	else
	   	Listu.plast->next=current;
   	do
   	{
	printf("请输入用户名（6-10位，由数字、字母混合组成）：\n");
    scanf("%s",current->user.ID);
   	p=current->user.ID;
   	if(strlen(current->user.ID)<6||strlen(current->user.ID)>10)
   	{	
		printf("用户名必须为6-10位，由数字、字母混合组成。\n");
		state=0;
		continue; 
	} 
   	while(*p!='\0')
   	{
	   	if((*p>=48&&*p<=57)||(*p>=65&&*p<=90)||(*p>=97&&*p<=122))
	   	{
			if(*p>=48&&*p<=57)
	   			checkn++;
	   		if((*p>=65&&*p<=90)||(*p>=97&&*p<=122))
	   			checkl++;
	       	*p++;
	    }
	   	else
	    {
		   printf("用户名必须为6-10位，由数字、字母混合组成。\n");
		   state=0;
		   break; 
		}
    }
    if(checkn==strlen(current->user.ID)||checkl==strlen(current->user.ID))
    {
    	printf("用户名不能为纯数字或纯字母\n");
    	checkn=checkl=0;
    	state=0;
    	continue;
    }
    if(*p=='\0')
    	state=1;
    }while(state==0);

  	do
    {
    	printf("请输入密码（8-12位数字）：\n");
   	    scanf("%s",current->user.secret);
   	    p=current->user.secret;
   	    if(strlen(current->user.secret)>12||strlen(current->user.secret)<8)
   	    { 
   			printf("密码需为8-12位数字\n");
		    state=0;
		    continue;
		} 
		while(*p!='\0')
	   	{
		   	if(*p>=48&&*p<=57)
		       *p++;
		   	else
		  	{
			   printf("密码需为8-12位数字\n");
			   state=0;
			   break; 
 			}
 		}
 		if(*p=='\0')
 			state=1;
 	} while(state==0);
 	
 	
   	printf("请输入姓名：\n");
   	scanf("%s",current->user.name);
   	
   	printf("请输入性别：\n");
   	scanf("%s",current->user.sex);

   	
    do
   	{
		printf("请输入电话号码：\n");
   		scanf("%s",current->user.number);
   		p=current->user.number;
   		if(strlen(current->user.number)!=11)
   		{
		   	printf("号码有误，请重新输入。\n");
   			state=0;
   			continue;
   		}
   		while(*p!='\0')
   		{
   			if(*p>=48&&*p<=57)
		       *p++;
		    else
		    {
			   printf("号码有误，请重新输入。\n");
			   state=0;
			   break; 
			}
		}
		if(*p=='\0')
			state=1;
   	}while(state==0);

   	
   	printf("请输入所在地横坐标：\n");
   	scanf("%d",&current->user.location_x);
   	
   	printf("请输入所在地纵坐标：\n");
   	scanf("%d",&current->user.location_y);
	state=0;
	while(state==0)
   	{
   		printf("请输入邮箱：\n");
   		scanf("%s",current->user.e_mail);
   	    for(em=0;em<=strlen(current->user.e_mail);em++)
   	    {
   	    	if(current->user.e_mail[em]==64)
   	    		temp1=em;
   	    	if(current->user.e_mail[em]==46)
   	    		temp2=em;
		}
		if(temp2-temp1>=2)
		{
			if(current->user.e_mail[temp2+1]!='\0'||current->user.e_mail[temp2+2]!='\0')
				state=1;
			else
				printf("邮箱格式有误，请重新输入\n");
		}
		else
			printf("邮箱格式有误，请重新输入\n");
				
	}
   	printf("注册完成!\n");
   	FILE *fp;
	fp=fopen("user.txt","a");
	if(fp==NULL)
	{
		printf("Error!Can't open users'data.");
		exit(0);
	}
	fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%d\t%d\t%s\n",current->user.ID,current->user.secret,current->user.name,current->user.sex,current->user.number,current->user.location_x,current->user.location_y,current->user.e_mail);
	Listu.plast=current;
	fclose(fp);
}


void checkuser()
{
	int state=0;
	char ID[12],secret[15];
	pNodeu p;
	p=Listu.phead;
	while(state==0)
	{
		printf("请输入用户名\n");
		scanf("%s",ID);
		while(p!=NULL)
		{
			if(strcmp(ID,p->user.ID)==0)
			{
				state=1;
				break;
			}
			p=p->next;
		}
		if(p==NULL)
			printf("用户名有误，请重新输入\n"); 
  	}
  	state=0;
  	while(state==0)
	{
		printf("请输入密码\n");
		scanf("%s",secret);
		if(strcmp(secret,p->user.secret)==0)
			break;
		else	
			printf("密码有误，请重新输入\n"); 
  	}
	printf("登录成功\n");
	Listu.position_user=p;
	t_user=p->user;
}

void change_userinformation()
{
	int choice;
	printf("****************************\n");
	printf("|请选择要修改的个人信息    |\n");
	printf("|<1>密码                   |\n");
	printf("|<2>邮箱                   |\n");
	printf("|<3>电话                   |\n");
	printf("|<4>返回上一级             |\n");
	printf("|<0>退出系统               |\n");
	printf("|                          |\n");
	printf("****************************\n");
	printf("请选择：");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: change_user_secret();
				break;
		case 2: change_user_e_mail();
				break;
		case 3: change_user_phone();
				break;
		case 4: customer_menu();
				break;
		case 0: exit(0);
	} 
	
}

void change_user_secret()
{
	int state=0;
	char secret[15];
	char *p;
	while(state==0)
		{
		printf("请输入原密码：");
		scanf("%s",secret);
		if(strcmp(secret,t_user.secret)==0)
			state=1;
		else
			printf("密码有误，请重新输入\n"); 
		}
		
		state=0;
		while(state==0)
    	{
			printf("请输入新密码：");
			scanf("%s",secret);
			p=secret;
	   	    if(strlen(secret)>12||strlen(secret)<8)
	   	    { 
	   			printf("密码需为8-12位数字\n");
			    state=0;
			    continue;
			} 
			while(*p!='\0')
		   	{
			   	if(*p>=48&&*p<=57)
			       *p++;
			   	else
			  	{
				   printf("密码需为8-12位数字\n");
				   state=0;
				   break; 
	 			}
	 		}
	 		if(*p=='\0')
	 			state=1;
 		} 
 		strcpy(Listu.position_user->user.secret,secret);
 		void save_userchanged();
}



 
void change_user_e_mail()
{
	int state=0,em,temp1,temp2;
	char e_mail[20];
	char *p;
		while(state==0)
		{
			printf("请输入新邮箱：");
			scanf("%s",e_mail);
	   	    for(em=0;em<=strlen(e_mail);em++)
	   	    {
	   	    	if(e_mail[em]==64)
	   	    		temp1=em;
	   	    	if(e_mail[em]==46)
	   	    		temp2=em;
			}
			if(temp2-temp1>=2)
			{
				if(e_mail[temp2+1]!='\0'||e_mail[temp2+2]!='\0')
					state=1;
				else
					printf("邮箱格式有误，请重新输入\n");
			}
			else
				printf("邮箱格式有误，请重新输入\n");
 		} 
 		strcpy(Listu.position_user->user.e_mail,e_mail);
 		void save_userchanged();
}


void change_user_phone()
{
	int state=0;
	char number[14];
	char *p;
	while(state==0)
	{
		printf("请输入新电话号码：");
		scanf("%s",number);
   		p=number;
   		if(strlen(number)!=11)
   		{
		   	printf("号码有误，请重新输入。\n");
   			state=0;
   			continue;
   		}
   		while(*p!='\0')
   		{
   			if(*p>=48&&*p<=57)
		       *p++;
		    else
		    {
			   printf("号码有误，请重新输入。\n");
			   state=0;
			   break; 
			}
		}
		if(*p=='\0')
			state=1;
	}
 	strcpy(Listu.position_user->user.number,number);
 	void save_userchanged();
}
 	
 	
void save_userchanged()
{
	pNodeu temp=Listu.phead;
 	FILE *fp;
	fp=fopen("user.txt","w");
	if(fp==NULL)
	{
		printf("Can't open user.txt");
		exit(0);
	}
	while(temp!=NULL)
	{
		
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%d\t%d\t%s\n",temp->user.ID,temp->user.secret,temp->user.name,temp->user.sex,temp->user.number,temp->user.location_x,temp->user.location_y,temp->user.e_mail);
		temp=temp->next;
	}
	printf("修改成功");
	fclose(fp);
}
		


void emptylistu(pNodeu plist)
{
	pNodeu psave;
	if(Listu.phead!=NULL)
	{
		while(plist!=NULL)
		{
			psave=plist->next;
			free(plist);
			plist=psave;
		}
	}
}


void loadadm()
{
	FILE *fp;
	fp=fopen("adm.txt","r");
	if(fp==NULL)
	{
		printf("\nCan't open user.txt");
		exit(0);
	}
	pNodea current,prev;
	current=prev=NULL;
	current=(pNodea)malloc(sizeof(Nodea));
	while(fscanf(fp,"%s%s%s%d%s%s",current->adm.ID,current->adm.secret,
		current->adm.restaurant,&current->adm.restaurant_ID,current->adm.name,current->adm.e_mail)!=-1) 
	{
		current->next=NULL;
		if(prev==NULL)
			Lista.phead=current;
		else
			prev->next=current;
		prev=current;
		current=(pNodea)malloc(sizeof(Nodea));
	}
	free(current);
	Lista.plast=prev;
	fclose(fp);
	
}


void addadmnode()
{
	char *p;
	int state=1,em=0,temp1=0,temp2=0,checkn=0,checkl=0;
	pNodea current;	
	current=(pNodea)malloc(sizeof(Nodea));
	if(Lista.plast==NULL)
   		Lista.phead=current;
   	else
   		Lista.plast->next=current;
   	do
   	{
	printf("请输入用户名（6-10位，由数字、字母混合组成）：\n");
    scanf("%s",current->adm.ID);
   	p=current->adm.ID;
   	if(strlen(current->adm.ID)<6||strlen(current->adm.ID)>10)
   	{	
		printf("用户名必须为6-10位，由数字、字母混合组成。\n");
		state=0;
		continue; 
	} 
   	while(*p!='\0')
   	{
	   if((*p>=48&&*p<=57)||(*p>=65&&*p<=90)||(*p>=97&&*p<=122))
	   {
	   		if(*p>=48&&*p<=57)
	   			checkn++;
	   		if((*p>=65&&*p<=90)||(*p>=97&&*p<=122))
	   			checkl++;
	       *p++;
	   }
	   else
		{
		   printf("用户名必须为6-10位，由数字、字母混合组成。\n");
		   state=0;
		   break; 
		}
    }
    if(checkn==strlen(current->adm.ID)||checkl==strlen(current->adm.ID))
    {
    	printf("用户名不能为纯数字或纯字母\n");
    	checkn=checkl=0;
    	state=0;
    	continue;
    }
    if(*p=='\0')
    	state=1;
    }while(state==0);
    p=current->adm.secret;
    
    
    do
    {
    	printf("请输入密码（8-12位数字）：\n");
   	    scanf("%s",current->adm.secret);
   	    p=current->adm.secret;
   	    if(strlen(current->adm.secret)>12||strlen(current->adm.secret)<8)
   	    { 
   			printf("密码需为8-12位数字\n");
		    state=0;
		    continue;
		} 
		while(*p!='\0')
	   	{
		   if(*p>=48&&*p<=57)
		       *p++;
		   else
		    {
			   printf("密码需为8-12位数字\n");
			   state=0;
			   break; 
			}
 		}
 		if(*p=='\0')
 			state=1;
 	}while(state==0);
 	
 	printf("请输入所属餐馆：\n");
 	scanf("%s",current->adm.restaurant);
 	printf("请输入所属餐馆ID:\n");
 	scanf("%d",&current->adm.restaurant_ID);
   	printf("请输入姓名：\n");
   	scanf("%s",current->adm.name);
   	
	state=0;
   	do
   	{
   		printf("请输入邮箱：\n");
   		scanf("%s",current->adm.e_mail);
   	    for(em=0;em<=strlen(current->adm.e_mail);em++)
   	    {
   	    	if(current->adm.e_mail[em]==64)
   	    		temp1=em;
   	    	if(current->adm.e_mail[em]==46)
   	    		temp2=em;
		}
		if(temp2-temp1>=2)
		{
			if(current->adm.e_mail[temp2+1]!='\0'||current->adm.e_mail[temp2+2]!='\0')
				state=1;
			else
				printf("邮箱格式有误，请重新输入\n");
		}
		else
			printf("邮箱格式有误，请重新输入\n");
	}while(state==0);
   	printf("注册完成!\n");
    FILE *fp;
	fp=fopen("adm.txt","a");
	if(fp==NULL)
	{
		printf("Error!Can't open administrators' data.");
		exit(0);
	}
	fprintf(fp,"%s\t%s\t%s\t%s\t%s\n",current->adm.ID,current->adm.secret,current->adm.restaurant,current->adm.name,current->adm.e_mail);
	Lista.plast=current;
	fclose(fp);
}



void checkadm()
{
	int state=0;
	char ID[12],secret[15];
	pNodea p;
	p=Lista.phead;
	while(state==0)
	{
		printf("请输入用户名\n");
		scanf("%s",ID);
		while(p!=NULL)
		{
			if(strcmp(ID,p->adm.ID)==0)
			{
				state=1;
				break;
			}
			p=p->next;
		}
		if(p==NULL)
			printf("用户名有误，请重新输入\n"); 
  	}
  	
  	state=0;
  	while(state==0)
	{
		printf("请输入密码\n");
		scanf("%s",secret);
		if(strcmp(secret,p->adm.secret)==0)
			break;
		else
			printf("密码有误，请重新输入\n"); 
  	}
	printf("登录成功\n");
	Lista.position_adm=p;
    t_adm=p->adm;
}

void change_adminformation()
{
	int choice;
	printf("****************************\n");
	printf("|请选择要修改的个人信息    |\n");
	printf("|<1>密码                   |\n");
	printf("|<2>邮箱                   |\n");
	printf("|<3>返回上一级             |\n");
	printf("|<0>退出系统               |\n");
	printf("|                          |\n");
	printf("****************************\n");
	printf("请选择：");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: change_adm_secret();
				break;
		case 2: change_adm_e_mail();
				break;
		case 3: manager_menu(); 
				break;
		case 0: exit(0);
	} 
}

void change_adm_secret()
{
	int state=0;
	char secret[15];
	char *p;
	while(state==0)
	{
	printf("请输入原密码：");
	scanf("%s",secret);
	if(strcmp(secret,t_adm.secret)==0)
		state=1;
	else
		printf("密码有误，请重新输入\n"); 
	}
	
	state=0;
	while(state==0)
	{
		printf("请输入新密码：");
		scanf("%s",secret);
		p=secret;
   	    if(strlen(secret)>12||strlen(secret)<8)
   	    { 
   			printf("密码需为8-12位数字\n");
		    state=0;
		    continue;
		} 
		while(*p!='\0')
	   	{
		   	if(*p>=48&&*p<=57)
		       *p++;
		   	else
		  	{
			   printf("密码需为8-12位数字\n");
			   state=0;
			   break; 
 			}
 		}
 		if(*p=='\0')
 			state=1;
	} 
	strcpy(Lista.position_adm->adm.secret,secret);
	save_admchanged();
}
		
		
		
void change_adm_e_mail()
{		
	int state=0,temp1,temp2,em;
	char e_mail[20];
	while(state==0)
	{
		printf("请输入新邮箱：");
		scanf("%s",e_mail);
   	    for(em=0;em<=strlen(e_mail);em++)
   	    {
   	    	if(e_mail[em]==64)
   	    		temp1=em;
   	    	if(e_mail[em]==46)
   	    		temp2=em;
		}
		if(temp2-temp1>=2)
		{
			if(e_mail[temp2+1]!='\0'||e_mail[temp2+2]!='\0')
				state=1;
			else
				printf("邮箱格式有误，请重新输入\n");
		}
		else
			printf("邮箱格式有误，请重新输入\n");
	} 
 	strcpy(Lista.position_adm->adm.e_mail,e_mail);
 	save_admchanged();
}

void save_admchanged()
{
 	FILE *fp;
	fp=fopen("adm.txt","w");
	pNodea temp=Lista.phead;
	if(fp==NULL)
	{
		printf("Can't open user.txt");
		exit(0);
	}
	while(temp!=NULL)
	{
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\n",temp->adm.ID,temp->adm.secret,temp->adm.restaurant,temp->adm.name,temp->adm.e_mail);
		temp=temp->next;
	}
	fclose(fp);
	printf("修改成功");
}



void emptylista(pNodea plist)
{
	pNodea psave;
	if(Lista.plast!=NULL)
	while(plist!=NULL)
	{
		psave=plist->next;
		free(plist);
		plist=psave;
	}
}




void customer_menu_1()
{
	printf("****************************\n");
	printf("|                          |\n");
	printf("|<1>根据餐馆名称查询       |\n");
	printf("|<2>根据地理位置查询       |\n");
	printf("|<3>根据菜系查询           |\n");
	printf("|<4>根据活动查询           |\n");
	printf("|<5>根据销量查询           |\n");   //需排序
	printf("|<6>根据评分查询           |\n");   //需排序
	printf("|<7>根据送餐速度查询       |\n");   //需排序
	printf("|<8>返回上一级             |\n");
	printf("|<0>退出系统               |\n");
	printf("|                          |\n");
	printf("****************************\n");
	printf("请选择：");
	char choice[8];
	while(1)
	{
		scanf("%s",choice); 
		int n=input_errorcheck(choice,8);
		switch(n)
		{
			case 1: res_viewbyname();
					break;
			case 2: res_viewbydistance();
					break;
			case 3: res_viewby_mealtype();
					break;	
			case 4: res_viewbyactivity();
					break;
			case 5: res_viewbysell();
					break;
			case 6: res_viewbygrade();
					break;
			case 7: res_viewbyspeed();
					break;
			case 8: customer_menu();
					break;
			case 0: exit(0);
			default:
			printf("输入错误，请重新输入\n");	
		}
	}
}
			
void res_viewbyname()
{
	struct Restaurant *result;
	int i,state=0,choice;
	while(state==0)
	{
	printf("请输入餐馆名称：\n");
	scanf("%s",result->name);
	for(i=0;i<15;i++)
		if(strcmp(result->name,res[i].name)==0)
		{
			printf("*********************************************您查找的餐馆信息如下****************************************\n");
			printf("|                                                                                                       |\n");
			printf("|  ID     名称       菜系      起送价     配送费     平均送达时间     服务时间     地理区域     评分    |\n");
			printf("|  %d      %s	      %s         %d		    %d      	%dmin		     %d           %s         %f     |\n",
			result->ID, result->name,result->cuisine,result->Price,result->fee, result->arrivingtime, result->timing, 
			result->location, result->grade);
			printf("|                                                                                                       |\n");
			printf("*********************************************************************************************************\n");
			printf("\n");
			state=1;
			break;	
		}
	if(state==0)
		printf("未查询到输入的餐馆\n<1>继续查询 <2>退出\n");
	scanf("%d",&choice);
	if(choice==2)
		customer_menu_1();	
	}
	printf("<1>点菜 <2>返回上一级\n");
	scanf("%d",&choice);
	if(choice==1)
		order_meal();
	if(choice==2)
		customer_menu_1();
}
		
void res_viewbydistance()
{
	int i,j,k;
	int res_dis;
	struct Restaurant resTemp;
	for(i=0;i<15;i++)
		res_rank[i]=res[i];
	for(i=0;i<15;i++)
		res_rank[i].distance=sqrt(pow((t_user.location_x-res_rank[i].location_x),2)+pow((t_user.location_y-res_rank[i].location_y),2));
	for(i=0; i<14; i++)
	{
		for(j=0; j<14-i; j++)	
			if(res_rank[j].distance>res_rank[j+1].distance)
			{
				resTemp = res_rank[j];
				res_rank[j] = res_rank[j+1];
				res_rank[j+1] = resTemp;
			}
	}
	k=0;
			printf("*******************************************您查找的餐馆信息如下*****************************************\n");
	    	printf("|                                                                                                      |\n");
		    printf("|  ID     名称       菜系      起送价     配送费     平均送达时间     服务时间     地理区域     评分   |\n");
			while(k<15)
			{
			printf("|  %d      %s	      %s         %d		    %d      	 %dmin		     %d           %s         %f    |\n",
			res_rank[k].ID, res_rank[k].name,res_rank[k].cuisine,res_rank[k].Price,res_rank[k].fee,res_rank[k].arrivingtime,res_rank[k].timing, 
			res_rank[k].location,res_rank[k].grade);
			k++;
			}
	    	printf("|                                            按距离从小到大                                            |\n");
	    	printf("********************************************************************************************************\n");
	printf("\n");
	order_meal();
}
		    
void res_viewby_mealtype()
{
    int choice,k=0;
    char cuisine[5]="";
    printf("请选择你喜欢的菜系<1>中餐 <2>西餐 <3>饮品\n");
    scanf("%d",&choice);
    switch (choice)
	{
    	case 1://中餐
    		strcpy(cuisine,"中餐");
    		printf("*******************************************您查找的餐馆信息如下*****************************************\n");
	    	printf("|                                                                                                      |\n");
		    printf("|  ID     名称       菜系      起送价     配送费     平均送达时间     服务时间     地理区域     评分   |\n");
			while(k<15)
			{
			if(strcmp(cuisine,res[k].cuisine)==0)
			printf("|  %d      %s	      %s         %d		    %d      	 %dmin		     %d           %s         %f    |\n",
			res[k].ID, res[k].name,res[k].cuisine,res[k].Price,res[k].fee,res[k].arrivingtime,res[k].timing, 
			res[k].location,res[k].grade);
			k++;
			}
	    	printf("|                                                                                                      |\n");
	    	printf("********************************************************************************************************\n");
    	    break;
    	case 2://西餐
    		strcpy(cuisine,"西餐");
		    printf("*******************************************您查找的餐馆信息如下*****************************************\n");
	    	printf("|                                                                                                      |\n");
	    	printf("|  ID     名称       菜系      起送价     配送费     平均送达时间     服务时间     地理区域     评价   |\n");
	    	while(k<15)
			{
			if(strcmp(cuisine,res[k].cuisine)==0)
			printf("|  %d      %s	      %s         %d		    %d      	 %dmin		     %d           %s         %f    |\n",
			res[k].ID, res[k].name,res[k].cuisine,res[k].Price,res[k].fee,res[k].arrivingtime,res[k].timing, 
			res[k].location,res[k].grade);
			k++;
			}
	    	printf("|                                                                                                      |\n");
	    	printf("********************************************************************************************************\n");
    	    break;
    	case 3://饮品
    		strcpy(cuisine,"饮品");
    	    printf("*******************************************您查找的餐馆信息如下*****************************************\n");
	    	printf("|                                                                                                      |\n");
	    	printf("|  ID     名称       菜系      起送价     配送费     平均送达时间     服务时间     地理区域     评价   |\n");
	    	while(k<15)
			{
			if(strcmp(cuisine,res[k].cuisine)==0)
			printf("|  %d      %s	      %s         %d		    %d      	 %dmin		     %d           %s         %f    |\n",
			res[k].ID, res[k].name,res[k].cuisine,res[k].Price,res[k].fee,res[k].arrivingtime,res[k].timing, 
			res[k].location,res[k].grade);
			k++;
			}
	    	printf("|                                                                                                      |\n");
	    	printf("********************************************************************************************************\n");
    	    break;
    	default:printf("输入错误，请在1~3中重新选择");
	}
	system("pause");
	system("cls");
    order_meal();
}
		
void res_viewbyactivity()
{
    printf("*******************************************您查找的餐馆信息如下**************************************************\n");
	printf("|                                                                                                               |\n");
	printf("|  ID     名称       菜系      起送价     配送费     平均送达时间     服务时间     地理区域     评价            |\n");
	printf("|   1   小熊炸鸡     西餐        20         0           30min      11：00-22：00     北城       4.8    满减     |\n");
	printf("|   8    甜品店      西餐        30         0           30min      10：00-19：00     南城       4.8    超时赔付 |\n");
	printf("|                                                                                                               |\n");
	printf("*****************************************************************************************************************\n");
	order_meal();
}    	
 
 

   
void res_viewbysell()
{	
	int i,j,k;	
	struct Restaurant resTemp;
	for(i=0;i<15;i++)
		res_rank[i]=res[i];
	for(i=0; i<14; i++)
	{
		for(int j=0; j<14-i; j++)
			if(res_rank[j].sell < res_rank[j+1].sell )
			{
				resTemp = res_rank[j];
				res_rank[j] = res_rank[j+1];
				res_rank[j+1] = resTemp;
			}
	}
	k=0;
			printf("*******************************************您查找的餐馆信息如下*****************************************\n");
	    	printf("|                                                                                                      |\n");
		    printf("|  ID     名称       菜系      起送价     配送费     平均送达时间     服务时间     地理区域     评分   |\n");
			while(k<15)
			{
			printf("|  %d      %s	      %s         %d		    %d      	 %dmin		     %d           %s         %f    |\n",
			res_rank[k].ID, res_rank[k].name,res_rank[k].cuisine,res_rank[k].Price,res_rank[k].fee,res_rank[k].arrivingtime,res_rank[k].timing, 
			res_rank[k].location,res_rank[k].grade);
			k++;
			}
	    	printf("|                                                                                                      |\n");
	    	printf("********************************************************************************************************\n");
	printf("\n");
	order_meal();
}

       
void res_viewbyspeed()
{
	int i,j,k;
	struct Restaurant resTemp;
	for(i=0;i<15;i++)
		res_rank[i]=res[i];
	for(int i=0; i<14; i++)
	{
		for(int j=0; j<14-i; j++)
			if(res_rank[j].arrivingtime > res_rank[j+1].arrivingtime )
			{
				resTemp = res_rank[j];
				res_rank[j] = res_rank[j+1];
				res_rank[j+1] = resTemp;
			}
	}
	k=0;
			printf("*******************************************您查找的餐馆信息如下*****************************************\n");
	    	printf("|                                                                                                      |\n");
		    printf("|  ID     名称       菜系      起送价     配送费     平均送达时间     服务时间     地理区域     评分   |\n");
			while(k<15)
			{
			printf("|  %d      %s	      %s         %d		    %d      	 %dmin		     %d           %s         %f    |\n",
			res_rank[k].ID, res_rank[k].name,res_rank[k].cuisine,res_rank[k].Price,res_rank[k].fee,res_rank[k].arrivingtime,res_rank[k].timing, 
			res_rank[k].location,res_rank[k].grade);
			k++;
			}
	    	printf("|                                                                                                      |\n");
	    	printf("********************************************************************************************************\n");
	printf("\n");
	order_meal();
}
    
    
void res_viewbygrade()
{
	int i,j,k;
	struct Restaurant resTemp;
	for(i=0;i<15;i++)
		res_rank[i]=res[i];
	for(int i=0; i<14; i++)
	{
		for(int j=0; j<14-i; j++)
			if(res_rank[j].grade < res_rank[j+1].grade )
			{
				resTemp = res_rank[j];
				res_rank[j] = res_rank[j+1];
				res_rank[j+1] = resTemp;
			}
	}
	k=0;
			printf("*******************************************您查找的餐馆信息如下*****************************************\n");
	    	printf("|                                                                                                      |\n");
		    printf("|  ID     名称       菜系      起送价     配送费     平均送达时间     服务时间     地理区域     评分   |\n");
			while(k<15)
			{
			printf("|  %d      %s	      %s         %d		    %d      	 %dmin		     %d           %s         %f    |\n",
			res_rank[k].ID, res_rank[k].name,res_rank[k].cuisine,res_rank[k].Price,res_rank[k].fee,res_rank[k].arrivingtime,res_rank[k].timing, 
			res_rank[k].location,res_rank[k].grade);
			k++;
			}
	    	printf("|                                             评分从高到低                                             |\n");
	    	printf("********************************************************************************************************\n");
	printf("\n");
	order_meal();
}    



void order_meal()
{
	int state=0,choice,restaurant_ID,i;
	printf("<1>点菜 <2>返回上一级\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		while(state==0)
		{
		printf("请选择点菜餐馆的序号：\n");
		scanf("%d",&restaurant_ID);
		for(i=0;i<15;i++)
			if(restaurant_ID==i)
			{
				state=1;
				break;
			}
		if(state==0)
			printf("输入有误，请重新输入\n");
		}
		meal_menu_customer(restaurant_ID);
	}
	if(choice==2)
		customer_menu_1();
}


void meal_menu_customer(int restaurant_ID)
{
	int i=0,longofmenu;
	int sell_meal;
	Meal meal_temp,meal_stored[12];
	FILE *fp;
	fp=open_restaurantfile1(restaurant_ID);
	fseek(fp,0L,SEEK_SET);
	printf("************菜单**************\n");
	printf("                              \n");
    printf("菜名\t价格\t已售份数\t推荐人数\n");
    while(fscanf(fp,"%d%s%lf%d%d",&meal_stored[i].restaurant_ID,meal_stored[i].name,&meal_stored[i].price,&meal_stored[i].recm,&meal_stored[i].count)!=-1)
    {
    printf("%s\t%f\t%d\t%d                \n",meal_stored[i].name,meal_stored[i].price,meal_stored[i].recm,meal_stored[i].count);
    i++;
 	}
	printf("                               \n");
	printf("*******************************\n");
	printf("\n");
	fclose(fp);
	longofmenu=i;
	choose_meal(restaurant_ID,meal_stored,longofmenu);
}




void choose_meal(int restaurant_ID,Meal *meal_stored,int longofmenu)
{
	double prize=0;
	int i=0,j=0,choice,sell_meal,state=0;
	int *phour,*pminute; 
	char choose_meal[10];
	Order order_tempsave; //结构体变量用于暂存订单的数据 
	order_tempsave.restaurant_ID=restaurant_ID;
	order_tempsave.customer_locaition_x=t_user.location_x;
	order_tempsave.customer_locaition_y=t_user.location_y;
	while(1)
	{
	while(state==0)
    {
	printf("请选择菜品：\n");
	scanf("%s",choose_meal);
	for(i=0;i<longofmenu;i++)
		if(strcmp(choose_meal,meal_stored[i].name)==0)
		{
			strcpy(order_tempsave.dishes[j].dish_name,choose_meal);
			j++;
			state=1;
			break;
		}
	if(i==longofmenu)
		printf("未找到此菜品\n");
	}
	printf("请输入份数：\n");
	scanf("%d",&sell_meal);
	meal_stored[i].count=meal_stored[i].count+sell_meal;
	res[restaurant_ID].sell=res[restaurant_ID].sell+sell_meal;
	order_tempsave.dishes[j].dish_amount=sell_meal;
	order_tempsave.dishes[j].dish_prize=meal_stored[i].price;	
	order_tempsave.type_dish++;  
	prize=prize+meal_stored[i].price*sell_meal;
	printf("是否继续点菜：<1>是 <2>否");
	scanf("%d",&choice);
	if(choice==2)
		break;
	}
	order_tempsave.prize=prize;
	printf("下单成功\n");
	time_calculate(t_user.location_x,t_user.location_y,res[restaurant_ID].location_x,
	res[restaurant_ID].location_y,phour,pminute);
	printf("预计%d hour  %d minute 后送达\n");
	*pminute=*pminute+*phour*60;
	res[restaurant_ID].arrivingtime=(res[restaurant_ID].arrivingtime+*pminute)/res[restaurant_ID].order_frequency;
	add_order(order_tempsave);
}

void manage_meal(int restaurant_ID)
{
	int choice;
	for(value;value<8;value++)
		strcpy(meal_forpublish[value].name,"");
	printf("********************************\n");
	printf("|                              |\n");
	printf("|<1>菜品查询                   |\n");
	printf("|<2>添加菜品                   |\n");
	printf("|<3>发布/删除已添加菜品        |\n");
	printf("|<4>返回上一级                 |\n");
	printf("|<0>退出系统                   |\n");
	printf("|                              |\n");
	printf("********************************\n");
	scanf("%d",&choice);
	if(choice==1)
		meal_menu_adm(restaurant_ID);
	if(choice==2)
		add_meal(restaurant_ID);
	if(choice==3)
		publish_delete_meal(restaurant_ID);
	if(choice==4)
		manager_menu();
	if(choice==0)
		exit(0); 
}

void meal_menu_adm(int restaurant_ID)
{
	int i=0,longofmenu;
	int sell_meal;
	Meal meal_temp,meal_stored[12];
	FILE *fp;
	fp=open_restaurantfile1(restaurant_ID);
	fseek(fp,0L,SEEK_SET);
	printf("********************************菜单**********************************\n");
	printf("|                                                                    |\n");
    printf("|     菜名         价格        已售份数         推荐人数             |\n");
    while(fscanf(fp,"%d%s%lf%d%d",meal_stored[i].restaurant_ID,meal_stored[i].name,meal_stored[i].price,meal_stored[i].recm,meal_stored[i].count)!=-1)
    {
    printf("|     %s           %lf            %d               %d",meal_temp.name,meal_temp.price,meal_temp.recm,meal_temp.count);
    i++;
 	}
	printf("|                                                                    |\n");
	printf("**********************************************************************\n");
	printf("\n");
	fclose(fp);
	manage_meal(restaurant_ID);
}


void add_meal(int restaurant_ID)
{
	Meal meal_temp;
	int i=0;
	printf("请输入要添加的菜品信息（菜名，价格）：\n");
	while(scanf("%d %lf",meal_temp.name,meal_temp.price)!=2)
		printf("输入有误，请重新输入：\n");
	meal_temp.count=0;
	meal_temp.restaurant_ID=restaurant_ID;
	meal_temp.recm=0;
  	while(strcmp(meal_forpublish[i].name,"")!=0)
  		i++;
  	meal_forpublish[i]=meal_temp;
  	printf("添加成功\n");
	manage_meal(restaurant_ID);	 
}


void publish_delete_meal(int restaurant_ID)
{
	char mealname[10];
	int choice,i;
	printf("已添加的菜品有：\n");
	while(strcmp(meal_forpublish[i].name,"")!=0)
	{
	printf("%s\n",meal_forpublish[i].name);
	i++;
	}
	printf("<1>发布菜品\n<2>删除菜品\n");
	scanf("%d",&choice);
	if(choice==1)
		publish_meal(restaurant_ID);
	if(choice==2)
		delete_meal(restaurant_ID);
	manage_meal(restaurant_ID);
}


void publish_meal(int restaurant_ID)
{
	char mealname[10];
	int i=0,j,choice;
	FILE *fp;
	printf("已添加的菜品有：\n");
	while(strcmp(meal_forpublish[i].name,"")!=0)
	{
		printf("%s\t",meal_forpublish[i].name);
		i++;
	}
	while(1)
	{ 
		printf("请输入要发布的菜品名(一个)：");
		scanf("%s",mealname);
		while(strcmp(meal_forpublish[j].name,mealname)!=0)
			j++;
		fp=open_restaurantfile1(restaurant_ID);
		fprintf(fp,"%d\t%s\t%lf\t%d\t%d\n",meal_forpublish[j].restaurant_ID,meal_forpublish[j].name,meal_forpublish[j].price,meal_forpublish[j].recm,meal_forpublish[j].count);
		fclose(fp);
		while(strcmp(meal_forpublish[j].name,"")!=0)
		{
			meal_forpublish[j]=meal_forpublish[j+1];
	 		j++;
		}
		printf("是否继续 <1>是 <2>否");
		scanf("%d",&choice);
		if(choice==2)
			break;
	}
	manage_meal(restaurant_ID);
}


void delete_meal(int restaurant_ID)
{
	char mealname[10];
	int i,choice;
	while(1)
	{
		printf("请输入要删除的菜品的名称：\n");
		scanf("%s",mealname);
		while(strcmp(meal_forpublish[i].name,mealname)!=0)
			i++;
		while(strcmp(meal_forpublish[i].name,"")!=0)
		{
			meal_forpublish[i]=meal_forpublish[i+1];
	 		i++;
		}
		printf("删除成功");
		printf("是否继续 <1>是 <2>否");
		scanf("%d",&choice);
		if(choice==2)
			break;
	}
}

FILE *open_restaurantfile1(int restaurant_ID)
{
	FILE *fp;
	if(restaurant_ID==1)fp=fopen("1.txt","a+");
	if(restaurant_ID==2)fp=fopen("2.txt","a+");
	if(restaurant_ID==3)fp=fopen("3.txt","a+");
	if(restaurant_ID==4)fp=fopen("4.txt","a+");
	if(restaurant_ID==5)fp=fopen("5.txt","a+");
	if(restaurant_ID==6)fp=fopen("6.txt","a+");
	if(restaurant_ID==7)fp=fopen("7.txt","a+");
	if(restaurant_ID==8)fp=fopen("8.txt","a+");
	if(restaurant_ID==9)fp=fopen("9.txt","a+");
	if(restaurant_ID==10)fp=fopen("10.txt","a+");
	if(restaurant_ID==11)fp=fopen("11.txt","a+");
	if(restaurant_ID==12)fp=fopen("12.txt","a+");
	if(restaurant_ID==13)fp=fopen("13.txt","a+");
	if(restaurant_ID==14)fp=fopen("14.txt","a+");
	if(restaurant_ID==15)fp=fopen("15.txt","a+");
	if(fp==NULL)
	{
		printf("Can't open meal file");
		exit(0);
	}
	return fp; 
}

FILE *open_restaurantfile2(int restaurant_ID)
{
	FILE *fp;
	if(restaurant_ID==1)fp=fopen("1.txt","w");
	if(restaurant_ID==2)fp=fopen("2.txt","w");
	if(restaurant_ID==3)fp=fopen("3.txt","w");
	if(restaurant_ID==4)fp=fopen("4.txt","w");
	if(restaurant_ID==5)fp=fopen("5.txt","w");
	if(restaurant_ID==6)fp=fopen("6.txt","w");
	if(restaurant_ID==7)fp=fopen("7.txt","w");
	if(restaurant_ID==8)fp=fopen("8.txt","w");
	if(restaurant_ID==9)fp=fopen("9.txt","w");
	if(restaurant_ID==10)fp=fopen("10.txt","w");
	if(restaurant_ID==11)fp=fopen("11.txt","w");
	if(restaurant_ID==12)fp=fopen("12.txt","w");
	if(restaurant_ID==13)fp=fopen("13.txt","w");
	if(restaurant_ID==14)fp=fopen("14.txt","w");
	if(restaurant_ID==15)fp=fopen("15.txt","w");
	if(fp==NULL)
	{
		printf("Can't open meal file");
		exit(0);
	} 
	return fp;
}



struct tm *timeof_order()
{
	time_t timep;
    struct tm *p;
    time (&timep);
    p=localtime(&timep);
    return p;
}


void add_order(Order order_tempsave)      
{
	int i;
	int *p_del_hour,*p_del_min;
	struct tm *order_time=timeof_order();
	stored_order[order_count]=order_tempsave;
	stored_order[order_count].time.hour=order_time->tm_hour;
	stored_order[order_count].time.minute=order_time->tm_min;
	order_count++;
}


void time_calculate(int x1,int y1,int x2,int y2,int *phour,int *pminute)
{
	double x,y;
	int hour,minute;
	x=pow(x1-x2,2);
	y=pow(y1-y2,2);
	minute=(int)5*sqrt(x+y);  //配送一公里需要5分钟
	while(minute>=60)
	{
		hour++;
		minute=minute-60;
	}
	*phour=hour;
	*pminute=minute;
}


void payof_order()
{
	int i=0,j=0,k=0,choice1,choice2,longofmenu,choice_order;
	FILE *fp;
	Meal meal_stored[12];
	printf("*********************您当前未付款的订单**********************\n");
	printf("                                                             \n");
    printf("      菜名        单价        份数           价格            \n");
    for(i=1;i<=order_count;i++)
    {
    	printf("%d\n",i);
    	for(j=0;j<stored_order[i].type_dish;j++)
    		printf("%s",stored_order[i].dishes[j].dish_name);
    		printf("%f",stored_order[i].dishes[j].dish_prize);
    		printf("%d",stored_order[i].dishes[j].dish_amount);
    		printf("%f",stored_order[i].dishes[j].dish_prize*stored_order[i].dishes[j].dish_amount);
    	i++;
	}
	printf("                                                             \n");
	printf("*************************************************************\n");
	printf("\n");
	printf("是否付款\n<1>是\n<2>否");
	scanf("%d",&choice1);
	printf("输入要付款的订单号：\n");
	scanf("%d",&choice2);
	printf("付款成功\n");
	for(i=0;i<stored_order[choice2].type_dish;i++)
		strcpy(stored_order[choice2].dishes[i].recommend,"未推荐"); 
	printf("预计%dhour %dmin后送达\n",stored_order[choice2].delivery_time);
	fp=open_restaurantfile2(stored_order[choice2].restaurant_ID);
	while(fscanf(fp,"%d%s%lf%d%d",meal_stored[k].restaurant_ID,meal_stored[k].name,meal_stored[k].price,meal_stored[k].recm,meal_stored[k].count)!=-1)
		k++;
	for(i=0;i<stored_order[choice2].type_dish;i++)
		for(j=0;j<k;j++)
		if(strcmp(stored_order[choice2].dishes[i].dish_name,meal_stored[j].name)==0)
		{
			meal_stored[j].count=meal_stored[j].count+stored_order[choice2].dishes[i].dish_amount;
			j++;
		}
	fclose(fp);
	fp=open_restaurantfile2(stored_order[choice2].restaurant_ID);
	for(i=0;i<stored_order[choice2].type_dish;i++)
	fprintf(fp,"%d\t%s\t%lf\t%d\t%d\n",meal_stored[i].restaurant_ID,meal_stored[i].name,meal_stored[i].price,meal_stored[i].recm,meal_stored[i].count);
	fclose(fp);
	choice_order=choice2;
	recommand_and_evaluate(choice_order);
}
void recommand_and_evaluate(int choice_order)
{
	char recom[20];
	int choice1,i,longofmenu;
	printf("是否推荐菜品 <1>是 <2>否\n");
	scanf("%d",&choice1);
	if(choice1==1)
	{
		Meal meal_stored[12];
		while(1)
		{
		printf("请输入您推荐的菜品：\n");
		scanf("%s",recom);
		for(i=0;i<stored_order[choice_order].type_dish;i++)
			if(strcmp(recom,stored_order[choice_order].dishes[i].dish_name)==0)
				break;
		strcpy(stored_order[choice_order].dishes[i].recommend,"推荐");
		i=0;
		FILE *fp;
		fp=open_restaurantfile1(stored_order[choice_order].restaurant_ID);
		fseek(fp,0L,SEEK_SET);
		while(fscanf(fp,"%d%s%lf%s%d",meal_stored[i].restaurant_ID,meal_stored[i].name,meal_stored[i].price,meal_stored[i].recm,meal_stored[i].count)!=-1)
			i++;
		longofmenu=i;
		fclose(fp);
		for(i=0;i<longofmenu;i++)
			if(strcmp(recom,meal_stored[i].name)==0)
			{
				meal_stored[i].recm++;
				break;
			}
		fp=open_restaurantfile2(stored_order[choice_order].restaurant_ID);
		for(i=0;i<longofmenu;i++)
			fprintf(fp,"%d%s%lf%s%d",meal_stored[i].restaurant_ID,meal_stored[i].name,meal_stored[i].price,meal_stored[i].recm,meal_stored[i].count);
		fclose(fp);
		printf("是否继续推荐 <1>是 <2>否\n");
		printf("%d",&choice1);
		if(choice1==1)
			break;
		}
		printf("请输入您对此次服务的评分（5分满分）：\n");
		scanf("%f",&stored_order[choice_order].evaluation); 
		save_paidorder(&stored_order[choice_order]);
		delete_stored_order(choice_order);
	}
	if(choice1==2)
		customer_menu();		
}


void save_paidorder(Order *orderforsave)
{
	int i;
	stored_paidorder[i]=*orderforsave;
	strcpy(stored_paidorder[i].user_ID,t_user.ID);
	paidorder_count++;
}

void cancel_order()
{
	int i=0,j=0,choice1;
	printf("*********************您当前未付款的订单**********************\n");
	printf("                                                             \n");
    printf("      菜名        单价        份数           价格            \n");
    for(i=1;i<=order_count;i++)
    {
    	printf("%-d\n",i);
    	for(j=0;j<stored_order[i].type_dish;j++)
    		printf("%s",stored_order[i].dishes[j].dish_name);
    		printf("%f",stored_order[i].dishes[j].dish_prize);
    		printf("%d",stored_order[i].dishes[j].dish_amount);
    		printf("%f",stored_order[i].dishes[j].dish_prize*stored_order[i].dishes[j].dish_amount);
    	i++;
	}
	printf("                                                             \n");
	printf("*************************************************************\n");
	printf("\n");
	while(1)
	{
		printf("请输入您要取消的订单号：\n");
		scanf("%d",&choice1);
		delete_stored_order(choice1);
		printf("取消成功");
		printf("是否继续\n<1>是 <2>否");
		scanf("%d",&choice1);
		if(choice1==2)
			break;
	}
	
}

void delete_stored_order(int ordernum)
{
	int i,j;
	for(i=ordernum;i>=ordernum-1&&i<order_count;i++)
	{
		j=i;
		stored_order[j]=stored_order[j+1];
	}
	order_count--;
}


void view_orderlist()
{
	int i=0,j=0,k;
	printf("**************************已付款******************************\n");
	printf("                                                              \n");
    printf("      菜名        单价        份数           价格             \n");
    while(i<paidorder_count)
    {	
    	if(strcmp(stored_paidorder[i].user_ID,t_user.ID)==0)
    	{
    	printf("%-d\n",i+1);
    	for(k=0;k<stored_paidorder[i].type_dish;k++)
    		printf("%s",stored_paidorder[i].dishes[j].dish_name);
    		printf("%f",stored_paidorder[i].dishes[j].dish_prize);
    		printf("%d",stored_paidorder[i].dishes[j].dish_amount);
    		printf("%f",stored_paidorder[i].dishes[j].dish_prize*stored_order[i].dishes[j].dish_amount);
   		}
   		i++;
	}
	printf("                                                             \n");
	printf("**************************************************************\n");
	printf("\n");
	i=0;
	j=1;
	printf("***************************未付款*****************************\n");
	printf("                                                              \n");
    printf("      菜名        单价        份数           价格             \n");
    while(i<paidorder_count)
    {	
    	if(strcmp(stored_order[i].user_ID,t_user.ID)==0)
    	{
    	printf("%-d\n",i+1);
    	for(k=0;k<stored_order[i].type_dish;k++)
    	{
    		printf("%s",stored_order[i].dishes[j].dish_name);
    		printf("%f",stored_order[i].dishes[j].dish_prize);
    		printf("%d",stored_order[i].dishes[j].dish_amount);
    		printf("%f",stored_order[i].dishes[j].dish_prize*stored_order[i].dishes[j].dish_amount);
   		}
   		i++;
		}
	}
	printf("                                                              \n");
	printf("**************************************************************\n");
	printf("\n");
	printf("<1>返回上一级 <0>退出系统\n");
	scanf("%d",&i);
	if(i==1)
		customer_menu();
	if(i==0)
		exit(0);
}


void view_nonpayment_orderlist()
{
	int i=0,j=1,k;
	Order orderTemp,order_rank[15];
	for(i=0;i<15;i++)
		order_rank[i]=stored_order[i];
	for(i=0; i<14; i++)
	{
		for(j=0; j<14-i; j++)
			if(order_rank[j].time.hour>order_rank[j+1].time.hour)
			{
				orderTemp = order_rank[j];
				order_rank[j] = order_rank[j+1];
				order_rank[j+1] = orderTemp;
			}
			if(order_rank[j].time.hour=order_rank[j+1].time.hour)
			if(order_rank[j].time.minute>order_rank[j+1].time.minute)
				{
					orderTemp = order_rank[j];
					order_rank[j] = order_rank[j+1];
					order_rank[j+1] = orderTemp;
				}
	}
	printf("***************************未付款*****************************\n");
	printf("                                                              \n");
    printf("      菜名        单价        份数           价格             \n");
    while(i<paidorder_count)
    {	
    	if(order_rank[i].restaurant_ID==t_adm.restaurant_ID)
    	{
    	printf("%-d\n",i+1);
    	for(k=0;k<order_rank[i].type_dish;k++)
    	{
    		printf("%s",order_rank[i].dishes[k].dish_name);
    		printf("%f",order_rank[i].dishes[k].dish_prize);
    		printf("%d",order_rank[i].dishes[k].dish_amount);
    		printf("%f",order_rank[i].dishes[k].dish_prize*stored_order[i].dishes[j].dish_amount);
    		printf("%s\n",order_rank[i].dishes[k].recommend);
   		}
   		printf("评分  %f",order_rank[i].evaluation);
   		printf("用户地址  (%d,%d) ",order_rank[i].customer_locaition_x,order_rank[i].customer_locaition_y);
   		i++;
		}
	}
	printf("                                                              \n");
	printf("**************************************************************\n");
	printf("\n");
	printf("<1>返回上一级 <0>退出系统\n");
	scanf("%d",&i);
	if(i==1)
		order_manage_menu();
	if(i==0)
		exit(0);
}


void view_orderlist_sortbyprize()
{
	int i=0,j=1,k;
	Order orderTemp,order_rank[15];
	for(i=0;i<15;i++)
		order_rank[i]=stored_paidorder[i];
	for(i=0; i<14; i++)
	{
		for(j=0; j<14-i; j++)
			if(order_rank[j].prize<order_rank[j+1].prize)
			{
				orderTemp = order_rank[j];
				order_rank[j] = order_rank[j+1];
				order_rank[j+1] = orderTemp;
			}
	}
	printf("**************************已付款订单*****************************************\n");
	printf("                       （按总价格排序）                                      \n");
    printf("    餐馆名           菜名        单价        份数           价格             \n");
    while(i<paidorder_count)
    {	
    	printf("%s",res[order_rank[i].restaurant_ID].name);
    	for(k=0;k<order_rank[i].type_dish;k++)
    	{
    		printf("%s",order_rank[i].dishes[k].dish_name);
    		printf("%f",order_rank[i].dishes[k].dish_prize);
    		printf("%d",order_rank[i].dishes[k].dish_amount);
    		printf("%f",order_rank[i].dishes[k].dish_prize*stored_order[i].dishes[j].dish_amount);
    		printf("%s\n",order_rank[i].dishes[k].recommend);
   		}
   			printf("评分  %f",order_rank[i].evaluation);
   			printf("用户地址  (%d,%d) ",stored_order[i].customer_locaition_x,order_rank[i].customer_locaition_y);
   		i++;
	}
	printf("                                                                            \n");
	printf("****************************************************************************\n");
	printf("\n");
	printf("<1>返回上一级 <0>退出系统\n");
	scanf("%d",&i);
	if(i==1)
		order_manage_menu();
	if(i==0)
		exit(0);
}

void view_orderlist_sortbygrade()
{
	int i=0,j=1,k;
	Order orderTemp,order_rank[15];
	for(i=0;i<15;i++)
		order_rank[i]=stored_paidorder[i];
	for(i=0; i<14; i++)
	{
		for(j=0; j<14-i; j++)
			if(order_rank[j].evaluation<order_rank[j+1].evaluation)
			{
				orderTemp = order_rank[j];
				order_rank[j] = order_rank[j+1];
				order_rank[j+1] = orderTemp;
			}
	}
	printf("****************************已付款订单***************************************\n");
	printf("                         （按总价格排序）                                    \n");
    printf("    餐馆名           菜名        单价        份数           价格             \n");
    while(i<paidorder_count)
    {	  
    	printf("%s",res[order_rank[i].restaurant_ID].name);
    	for(k=0;k<order_rank[i].type_dish;k++)
    	{
    		printf("%s",order_rank[i].dishes[k].dish_name);
    		printf("%f",order_rank[i].dishes[k].dish_prize);
    		printf("%d",order_rank[i].dishes[k].dish_amount);
    		printf("%f",order_rank[i].dishes[k].dish_prize*stored_order[i].dishes[j].dish_amount);
    		printf("%s\n",order_rank[i].dishes[k].recommend);
   		}
   		printf("评分  %f",order_rank[i].evaluation);
   		printf("用户地址  (%d,%d) ",stored_order[i].customer_locaition_x,order_rank[i].customer_locaition_y);
   		i++;
	}
	printf("                                                                             \n");
	printf("*****************************************************************************\n");
	printf("\n");
	printf("<1>返回上一级 <0>退出系统\n");
	scanf("%d",&i);
	if(i==1)
		order_manage_menu();
	if(i==0)
		exit(0);
}

int main()
{
	main_menu();
	emptylistu(Listu.phead);
	emptylista(Lista.phead);
	return 0;
}



