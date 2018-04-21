//////////////////////////////////////////////////////////////////////////////////////////////////
/* **********************************************************************************************
 * 超市库存管理系统
 *
 * 扬州大学信息工程学院软件1502班
 *
 * 指导老师：邹姝稚
 *
 * 版本开发日志:
 *
 * 2015年12月22日 23:06:31    V0.1.0_Build 352
                 完成菜单等基本框架
   2015年12月26日 16:33:21    V0.1.2_Build 402
                 完成密码验证模块
   2015年12月26日 20:54:53    V0.1.5_Build 501
                 完成信息录入功能、菜单颜色设置功能
   2015年12月27日 11:57:33    V0.1.8 Build 788
                 完成信息查询模块 
   2015年12月28日 11:14:37    V0.2.0 Build 925
                 完成销售排行榜
				 修复已知BUG
   2015年12月29日 11:04:35    V0.3.0 Build 967
                 完善信息更新功能
   2015年12月29日 17:19:02    Bata V 1.0.0 Build 1058
                 第一测试版
   2015年12月30日 21:25:02    Bata V 1.5.0 Build 1112
                 改进部分功能代码

 * BY 李敬
 *
 * lijing394@163.com
 *
 * 要求：
 *
 * 1.任务描述:

   开发一个超市库存管理系统，可对商品的库存信息进行日常管理及预警。其中，库存信息包括：商品货号、
   名称、类别、总量、库存上限、库存下限、进货价格、零售价格、进货日期、进货量、生产日期、生产厂
   家、保质期等。主要功能如下：
     ⑴ 库存信息录入：以合理数据结构录入并存储库存信息（提示：结构数组或数据文件）
	 ⑵ 信息更新：能提供信息的插入、删除、修改更新操作。在商品进货时，如是新商品则把新的商品信息
	 添加到库存信息中；如是已有商品则根据商品库存量的上下限确定进货数量，然后根据进货实际情况修
	 改该商品的相关数据。
	 ⑶ 信息查询：提供多种途径的查询功能，如按编号查商品价格和生产日期、某商品库存量、某商品进货量
	 等。
	 ⑷ 库存信息预警：统计出库存量临近上限，需进行库存预警的商品；库存量临近下限，需进行库存预警的
	 商品；保质期低于一周需打折促销的商品。
	 ⑸ 提供排序统计功能：食品有效期排序、商品进货量排序、商品库存量排序等（可自行设计）。

   2.界面设计要求

        ⑴ 系统以菜单驱动方式工作，以方便用户根据需要进行功能选择。
        ⑵ 交互界面设计：要求用户输入数据时，需给出清晰、明确的提示信息，包括输入的数据内容、格式及结束
           方式等、
        ⑶ 输出界面：输出的结果要清晰美观，若以表格形式输出的信息，应上下对齐。

   3.课题完成要求

         ⑴ 可运行的源程序：开发并调试通过，能满足任务书要求的C程序。
         ⑵ 课程设计报告：撰写课程设计报告，能反映课题的总体设计、数据结构设计、详细设计、调试分析过程。
            要求内容基本正确、图表无重大错误。

///////////////////////////////////////////////////////////////////////////////////////////

/**********头文件及宏定义***************/
#include<stdio.h>
#include<stdlib.h> 
#include<windows.h> 
#include<conio.h>
#define NUM 100

/**** 结构体定义 ****/
struct item
{	
//	int   id;      货号
	char  brand[10];  //名称
	int   in_price;  //进价
	int   out_price; //售价
	int   stock_quantity;   //库存总量
	int   purchase_quantity;//进货量
	int   upper_limit; //库存上限
	int   lower_limit; //库存下限
	char  category[8]; //类别
	char  manufacture_factory[8];//生产厂家
	int   expiry_date;//保质期
	int   in_date;//进货日期
	int   manufacture_date;//生产日期
	char  remarks[8];//备注
}goods[NUM];

/*********全局变量*************/
int nn = 0;  //当前商品总个数

/**** 函数声明 ****/
void start();
void loading();
void main_menu();
int  Password_Authentification();
//void Modify_Password();
void establish();
void look_up();
void find_category();
void find_id();
void find_stock_quantity();
void update();
void insert_message();
void del_message();
void revise_message();
void chart();
void sort_amount();
void sort_profit();
void sort_id();
void earlywarning();
void colorsetting();
void indevelopment();
void error();
void gotoxy(int x,int y);
void HideCursor();
void help();
void leave();
void read();
void save();
//int validateID(int id);

/*************主函数*****************/
main()
{
	int choose;
	start();
	while(1)
	{	
    	main_menu();
     	scanf("%d",&choose);
    	switch(choose)
		{
		case 1:
			system("cls");
			establish();break;

		case 2:
			system("cls");
			update();break;

		case 3:
			system("cls");
			look_up();break;

		case 4:
			system("cls");
			earlywarning();break;

		case 5:
			system("cls");
		    chart();break;

		case 6:
			system("cls");
		    read();break;

        case 7:
			system("cls");
			colorsetting();break;

		case 0:
			save();
			printf("已保存!\n");
			leave();

		default:
			system("cls");
            error();break;
		}
		getch();
	}
}

/*************主菜单*****************/
void main_menu()
{
	system("cls");
	printf("\n\n\n");
	printf("\t\t|--------------------------------------------------|");
	printf("\t\t\t\t|\t\t超市库存管理系统\t\t   |\n");
	printf("\t\t|--------------------------------------------------|\n\n\n");
	printf("\t\t|-----------------请选择数字进行操作---------------|\n");
	printf("\t\t|\t\t1.库存信息录入                     |\n");
	printf("\t\t|\t\t2.更新商品信息                     |\n");
	printf("\t\t|\t\t3.商品信息查询                     |\n");
	printf("\t\t|\t\t4.库存信息预警                     |\n");
	printf("\t\t|\t\t5.销售排行总榜                     |\n");
	printf("\t\t|\t\t6.读取商品信息                     |\n");
	printf("\t\t|\t\t7.系统颜色设置                     |\n");
	printf("\t\t|\t\t0.退出系统                         |\n");
	printf("\t\t|-----------------请选择对应数字0--6---------------|\n");
}
/*
int validateID(int id)
	{   
		FILE *fp;
		struct item i;
        fp=fopen("goods.dat","r");
		if(fp==NULL)
		{printf("\t\t\t系统错误，请您重试........");exit(0);}
		fread(&i,sizeof(struct item),1,fp);
		while(!feof(fp))
		{
			if(i.id==id)
			{	fclose(fp);return 1;break;	}
			fread(&i,sizeof(struct item),1,fp);
		}
		fclose(fp);	return 0;
	}
*/

/*************库存信息录入*****************/
void establish()
{       
	if( nn >= NUM-1)
	{printf("商品信息已达上限！\n");system("pause"); return;}
/*labID:		printf("\n\t请您输入要入库物品的信息...\n");
			printf("\t\t\t\t   货号:");
			scanf("%d",&goods[i].id);
			if(validateID(goods[i].id)==1)
			{
				printf("\t\t\t\t此编号已被使用，请您重新输入......");
				goto labID;
			}
	*/
	printf("\n\t最多能输入 %d 个商品信息\n\n\t请依次输入商品信息:\n",NUM);
	printf("----------------------------\n");
	printf("类别: ");fflush(stdin);
	gets(goods[nn+1].category);
	printf("品名: ");fflush(stdin);
	gets(goods[nn+1].brand);
	/*	printf("货号: ");fflush(stdin);
	scanf("%d",&goods[nn+1].id);*/
	printf("进价: ");fflush(stdin);
	scanf("%d",&goods[nn+1].in_price);
	printf("售价: ");fflush(stdin);
	scanf("%d",&goods[nn+1].out_price);
	printf("进货日期: ");fflush(stdin);
	scanf("%d",&goods[nn+1].in_date);
	printf("进货量: ");fflush(stdin);
	scanf("%d",&goods[nn+1].purchase_quantity);
	printf("库存上限: ");fflush(stdin);
	scanf("%d",&goods[nn+1].upper_limit);
	printf("库存下限: ");fflush(stdin);
	scanf("%d",&goods[nn+1].lower_limit);
	printf("生产厂家: ");fflush(stdin);
	scanf("%d",&goods[nn+1].manufacture_factory);
	printf("生产日期: ");fflush(stdin);
	scanf("%d",&goods[nn+1].manufacture_date);
	printf("保质期: ");	fflush(stdin);
	scanf("%d",&goods[nn+1].expiry_date);
	printf("备注: ");fflush(stdin);
	gets(goods[nn+1].remarks);
	nn+=1;
	printf("\n\n");
	printf("编号：%d\n",nn);
	printf("品名：");puts(goods[nn].brand);
	printf("类别：");puts(goods[nn].category);
	printf("进价：%d\n",goods[nn].in_price);
	printf("售价：%d\n",goods[nn].out_price);
	printf("备注：");puts(goods[nn].remarks);
	printf("\n请按任意键继续!\n");
	getch();
}

/**********信息更新函数**********/
void update()
{
	int choose;
    while(1)
	{
		system("cls");
		printf("\n\n\n     *******商品信息更新*******\n\n");
		printf("             1:插入商品信息\n\n");
		printf("             2:删除商品信息\n\n");
		printf("             3:修改商品信息\n\n");
		printf("             0:返回\n\n");
		printf("             请选择(0-3):");
		scanf("%d",&choose);
	    switch(choose)
		{
	       case 1:insert_message();break;
		   case 2:del_message();break;
		   case 3:revise_message();break;
		   case 0:return;
		   default: error(); break;	
		}
		getch();
	}
}


void insert_message()
{	
	int i;char choose;
	printf("\n\t请依次输入插入的商品信息:\n",NUM);
	printf("----------------------------\n");
	for(i=1;i<=NUM;i++)
	{ 
		printf("类别: ");fflush(stdin);
		gets(goods[i].category);
		printf("品名: ");fflush(stdin);
		gets(goods[i].brand);
	/*	printf("货号: ");fflush(stdin);
		scanf("%d",&goods[i].id);*/
		printf("进价: ");fflush(stdin);
		scanf("%d",&goods[i].in_price);
		printf("售价: ");fflush(stdin);
		scanf("%d",&goods[i].out_price);
		printf("进货日期: ");fflush(stdin);
		scanf("%d",&goods[i].in_date);
		printf("进货量: ");fflush(stdin);
		scanf("%d",&goods[i].purchase_quantity);
        printf("库存上限: ");fflush(stdin);
		scanf("%d",&goods[i].upper_limit);
		printf("库存下限: ");fflush(stdin);
		scanf("%d",&goods[i].lower_limit);
		printf("生产厂家: ");fflush(stdin);
		scanf("%d",&goods[i].manufacture_factory);
		printf("生产日期: ");fflush(stdin);
		scanf("%d",&goods[i].manufacture_date);
		printf("保质期: ");fflush(stdin);
		scanf("%d",&goods[i].expiry_date);
		printf("备注: ");fflush(stdin);
		gets(goods[i].remarks);

		printf("\n**** 已经输入 %d 个商品!--\n",i);
		printf("\n\n是否要继续?Y/N?");
		choose=getch();
		if( choose == 'y' || choose == 'Y' ) {printf("\n请继续输入商品信息\n"); continue;}
		else if( choose == 'n' || choose == 'N' ) {printf("\n终止输入商品信息!\n请按任意键返回!\n"); break;}
		else  {printf("\n选择有误!终止输入商品信息!\n请按任意键返回!\n"); break;}
	}
}
 
/***********删除*************/
void del_message()
{ 
	char s[12],c; 
	int i=1,j; 
	printf("请输入想删除的品名:"); 
	fflush(stdin);
	gets(s); 
	while(strcmp(goods[i].brand,s) != 0 && i <= nn) i++; 
	if(i > nn) 
	{		printf("没有此商品!\n");		system("pause"); 	return; 	} 
	printf("该商品信息:\n编号：%d\n",i);
	printf("编号：%d\n",nn);
    printf("品名：");puts(goods[nn].brand);
    printf("类别：");puts(goods[nn].category);
    printf("进价：%d\n",&goods[nn].in_price);
    printf("售价：%d\n",&goods[nn].out_price);
    printf("备注：");puts(goods[nn].remarks);
	printf("是否删除?(输入\"1\"删除，任意非\"1\"键返回)\n");
	fflush(stdin);
	c=getchar();
	if(c=='1')
	{
	    for(j=i;j < nn;j++)
	    { 
	    	strcpy(goods[j].brand,goods[j+1].brand); 
	    	strcpy(goods[j].category,goods[j+1].category);
	    	goods[j].in_price  = goods[j+1].in_price;
	    	goods[j].out_price = goods[j+1].out_price;
	    	strcpy(goods[j].remarks,goods[j+1].remarks);
	    }
	    nn-=1;
	    printf("成功删除!\n");
	    system("pause");
	    return;
	}
	return;
}
	/*
	FILE *fp;
	int del_id,i;
	fp=fopen("goods.dat","rb");
	if(fp == NULL)
	{		printf("读取文件错误!请重试!");exit(0);	}
	for(i=0; i<NUM; i++)
		fscanf(fp,"%s%s%d%d",goods[i].category,goods[i].brand,goods[i].in_price,goods[i].out_price);
	printf("\n --请输入要删除商品的货号:--\n");
	scanf("%d",&del_id);
	for(i=del_id; i<NUM; i++)
		goods[i-1]=goods[i];
		del_id--;
        fp=fopen("porder_list","wb");
	    fwrite(goods,sizeof(struct item),del_id,fp);
	    fclose(fp);
	printf("\t\t\t\t\t物品信息已清除!!!\n");
	*/

/**************修改**************/
void revise_message()
{   
	int i=1,id,choose; 
	printf("请输入想修改的货号:"); 
	fflush(stdin);
	scanf("%d",&id);
	while( i != id  && i <= nn ) i++; 
	if( i > nn ) 
	{ 	printf("没有此商品!\n"); system("pause"); return; 	}  
	printf("\n   ----该商品主要信息----\n");
	printf("货号--品名--类别--进价--售价--保质期\n");
	printf("%d--%d--%5s--%d--%d--%d\n",nn,goods[i].brand,goods[i].category,goods[i].in_price,goods[i].out_price,goods[i].expiry_date);
	printf("\n要修改什么信息?\n      ");
	printf("\n        1:品名\n");
	printf("\n        2:类别\n");
	printf("\n        3:进价\n");
	printf("\n        4:售价\n");
	printf("\n        5:保质期\n");
	printf("\n        0:返回\n");
	printf("\n        please choose(0-5)");
	scanf("%d",&choose);
	switch(choose)
	{
		case 1:printf("\n 修改后的品名是?:  "); gets(goods[i].brand);break;
		case 2:printf("\n 修改后的类别是?:  "); gets(goods[i].category);break;
		case 3:printf("\n 修改后的进价是?:  "); scanf("%d",&goods[i].in_price);break;
		case 4:printf("\n 修改后的售价是?:  "); scanf("%d",&goods[i].out_price);break;
		case 5:printf("\n 修改后的保质期是?:"); scanf("%d",&goods[i].expiry_date);break;
		case 0: return;
		default: error(); break;
	}
	printf("修改成功!\n");
	printf("\n请按任意键返回\n");
	getch();
}


/*****************查询*******************/
void look_up()
{
	int choose;
	while(1)
	{
		system("cls");
		printf("\n\n\n\t\t请选择操作\n");
		printf("\t\t|----------------------------------|\n");
		printf("\t\t|\t1.按类别查询商品信息       |\n");
		printf("\t\t|\t2.按货号查询商品信息       |\n");
		printf("\t\t|\t3.按库存查询商品信息       |\n");
		printf("\t\t|\t0.返回                     |\n");
		printf("\t\t|----------------------------------|\n\n");
		scanf("%d",&choose);
		switch(choose)
		{
	       case 1:find_category();break;
		   case 2:find_id();break;
		   case 3:find_stock_quantity();break;
		   case 0:return;
		   default: error(); break;	
		}
		getch();
	}
}

/************按类别查**********/
void find_category()
{
    char s[12]; 
	int i=1; 
	printf("请输入想查询的种类:"); 	fflush(stdin);
	gets(s); 
	while(strcmp( goods[i].category,s) != 0 && i <= nn ) i++; 
	if( i > nn ) 
	{		printf("没有此类商品!\n"); return; 	} 
	printf("-------商品信息------\n");
//	printf("货号：");printf("%d",&goods[i].id);
	printf("品名：");puts(goods[i].brand);
	printf("种类：");puts(goods[i].category);
	printf("进价：");printf("%d",&goods[i].in_price);
	printf("售价：");printf("%d",&goods[i].out_price);
	printf("备注：");puts(goods[i].remarks);
	getch(); 
	return;
}

/************按货号查*********/
void find_id()
{
    int i; 
	printf("请输入商品货号:"); 
	scanf("%d",&i); 
	if( i > nn) 
	{printf("没有此纪录!\n"); system("pause"); return; } 
//	printf("货号：");printf("%d",&goods[i].id);
	printf("品名：");puts(goods[i].brand);
	printf("种类：");puts(goods[i].category);
	printf("进价：");printf("%d",&goods[i].in_price);
	printf("售价：");printf("%d",&goods[i].out_price);
	printf("备注：");puts(goods[i].remarks);
	system("pause"); 
	return;
} 

/************按库存查*********/
void find_stock_quantity()
{
	indevelopment();
/*
	struct item *p,*q[NUM];
    int i,j,k;
	system("cls");
	printf("\n            按库存量查找 \n");
	printf("     ------------------------------------------------------\n");
	printf("\n      rank     id     name     kind     stock_quantity\n");
	p=goods;
	for(i=0;i<NUM;i++)
		q[i]=p++;
	for(i=0;i<NUM-1;i++)
	{k=i;
	for(j=i+1;j<NUM;j++)
		if((q[k]->stock_quantity)<(q[j]->stock_quantity))  k=j;
		if(k!=i)
		{p=q[i];q[i]=q[k];q[k]=p;}}
	for(i=0;i<NUM;i++)
		printf("\n   %6d     %6d    %8s     %8s     %5d\n",i+1,q[i]->id,q[i]->category,q[i]->out_price-q[i]->in_price);
	getch();
	*/
}

/*****************库存预警******************/
void earlywarning()
{
	int i,page=1,max; char c;
	max=(nn+9)/10;
	do
	{
		system("cls");                      
     	printf("\n           库存量不足的商品 \n");
    	printf("     ------------------------------------------------------\n");
	    printf("\n    id     name     kind     stock_quantity      \n");
		if(page<max)
    	{
    		for(i=page*10-9;i<=page*10;i++)                                                            
        	{ 
        		printf("     %-3d%-12s%-12s%-10d",i,goods[i].brand,goods[i].category,goods[i].stock_quantity);
				if(i%10!=0)printf("\n"); 
        	}
		}
    	else if(page==max)
    	{
    		for(i=page*10-9;i<=nn;i++)                                                            
        	{ 
        		printf("     %-3d%-12s%-12s%-10d",i,goods[i].brand,goods[i].category,goods[i].stock_quantity);
        		if(i%10!=0)printf("\n"); 
        	}
		}
		printf("-------------------------------------------------------------------------------\n");
        printf("1:下一页                            2:上一页                             0:返回\n");
        printf("请您选择(0-2):");
		fflush(stdin);
      	c=getchar();
    	if(c=='1')
		{
		    if(page<max)page+=1;
			else{printf("已是最后一页!");system("pause");}
		}
    	else if(c=='2')
		{
		    if(page>1)page-=1;
			else{printf("已是第一页!");system("pause");}
		}
	}while(c!='0');

}


/******************排行榜*******************/
void chart()
{
   int choose;
   while(1)
   {
	   system("cls");
	   printf("\n\n          **********销售排行总榜**********\n\n");
	   printf("                 1:按库存排序\n\n");
	   printf("                 2:按利润排序\n\n"); 
	   printf("                 3:按货号排序\n\n"); 
	   printf("                 0:返回\n\n");
	   printf("                 请选择(0-3):");
	   scanf("%d",&choose);
	   switch(choose)
	   {
	   case 1:sort_amount(); break;
	   case 2:sort_profit(); break;
	   case 3:sort_id(); break;
	   case 0: return;
	   default: error(); break;
	   }
	   getch();
   }
}

/**********按库存排*************/
void sort_amount()
{
	indevelopment();
/*
	struct item *p,*q[NUM];
    int i,j,k;
	system("cls");
	printf("\n            按库存量排序 \n");
	printf("     ------------------------------------------------------\n");
	printf("\n      rank     id     name     kind     stock_quantity\n");
	p=goods;
	for(i=0;i<NUM;i++)
		q[i]=p++;
	for(i=0;i<NUM-1;i++)
	{k=i;
	for(j=i+1;j<NUM;j++)
		if((q[k]->stock_quantity)<(q[j]->stock_quantity))  k=j;
		if(k!=i)
		{p=q[i];q[i]=q[k];q[k]=p;}}
	for(i=0;i<NUM;i++)
		printf("\n        %6d     %8s     %8s     %5d\n",i+1,q[i]->category,q[i]->out_price-q[i]->in_price);
	getch();
*/
}

/****************按利润排*************/
void sort_profit()
{
    indevelopment();
/*
	struct item *p,*q[NUM];
	int i,j,k;
	system("cls");
	printf("/n            按利润排序 \n");
	printf("     ------------------------------------------------------\n");
	printf("\n      rank    id    brand    category    profit\n");
	p=goods;
	for(i=0;i<NUM;i++)
		q[i]=p++;
	for(i=0;i<NUM-1;i++)
	{
		k=i;
	for(j=i+1;j<NUM;j++)
		if((q[k]->out_price-q[k]->in_price)<(q[i]->out_price-q[j]->in_price))  k=j;
		if(k!=i)
		{p=q[i];q[i]=q[k];q[k]=p;}}
	for(i=0;i<NUM;i++)
		printf("\n   %6d   %8s     %8s     %5d\n",i+1,q[i]->category,q[i]->out_price-q[i]->in_price);
	getch();
*/
}

/*************按货号排*************/
void sort_id()
{
	int i,page=1,max; char c;
	max=(nn+9)/10;
	do
	{
		system("cls");                      
    	printf("     ------------------------------------------------------\n");
	    printf("\n    id     name     kind  \n");
		if(page<max)
    	{
    		for(i=page*10-9;i<=page*10;i++)                                                            
        	{ 
        		printf("     %-3d%-12s%-12s",i,goods[i].brand,goods[i].category);
				if(i%10!=0)printf("\n"); 
        	}
		}
    	else if(page==max)
    	{
    		for(i=page*10-9;i<=nn;i++)                                                            
        	{ 
        		printf("     %-3d%-12s%-12s",i,goods[i].brand,goods[i].category);
        		if(i%10!=0)printf("\n"); 
        	}
		}
		printf("-------------------------------------------------------------------------------\n");
        printf("1:下一页                            2:上一页                             0:返回\n");
        printf("请您选择(0-2):");
		fflush(stdin);
      	c=getchar();
    	if(c=='1')
		{
		    if(page<max)page+=1;
			else{printf("已是最后一页!");system("pause");}
		}
    	else if(c=='2')
		{
		    if(page>1)page-=1;
			else{printf("已是第一页!");system("pause");}
		}
	}while(c!='0');
/*
	int i,j;
	struct item temp;
	system("cls");
	printf("\n            按货号排序 \n");
	printf("     ------------------------------------------------------\n");
	printf("\n  rank     id     name     kind     stock_quantity     in_price   out_price\n");
	for(i=0; i<NUM-1; i++)
		for(j=i+1;j < NUM; j++)
		{  
		     if(goods[i].id < goods[j].id)
			 {
		     temp=goods[i];
		     goods[i]=goods[j];
		     goods[j]=temp;
			 }
		}
  for(i=0;i < NUM ;i++)
       printf("%-2d  %-2d   %-6s  %-2d  %-2d  %-2d\n",i,goods[i].brand,goods[i].category,goods[i].stock_quantity,goods[i].in_price,goods[i].out_price);
  printf("请输入任意键返回!");
  getch();
  */
}


/*****************选择错误提示*****************/
void error()
{
	printf("\n\n\n\n\n\t\t|\t\t选择错误!请重新选择\t\t|\n");
	printf("\n\n\n\t\t\t    请输入任意键返回上一级菜单\n");
}


/****************研发中提示*********************/
void indevelopment()
{
	system("cls");
	printf("\n\n\n\n\n\n\tLoading....\t\n\n\n\n");
	printf("\n\n\n\t\t\t请输入任意键返回上一级菜单\n");
}

/**********开始界面**********/
void start()
{
	int m=28,n=12;
	char c1;
	system("color F0");
    printf("╔══════════════════════════════════════╗");
	printf("║20151230_Bata_V2.2                                                          ║");
	printf("║                                                                            ║");
	printf("║  　┐┌┬─┐　┌──╮　┌─┴──┐┌├───┐┌┬╮─┬╮┌┬┌─┬╮  ║");
	printf("║  ┌├　│　│└──┬─┘│┌─├─　╭┘───┐┌──┴─┐　││　││  ║");
	printf("║  ┌├╰╯└┘┌──├─┐│╭─╯　　││　　　│┌────┐╭├├─├┤  ║");
	printf("║  　├┌──┐│　　│　││└─├─　││　　┌╯├────╯　│└─├┘  ║");
	printf("║  ││└──┘│　　│　││──├─┘││──├┐├────┐　│└─├╯  ║");
	printf("║  └╰───┘└　　┘　╯╯　　┘　　╰└　╰┘　└────╯╰┴╰─┴┘  ║");
	printf("║                                                                            ║");
	printf("║                                                                            ║");
	printf("║                              ┏━━━━┓                                  ║");
	printf("║                     ①   ★  ┃进    入┃                                  ║");
	printf("║                              ┗━━━━┛                                  ║");
	printf("║                              ┏━━━━┓                                  ║");
	printf("║                     ②       ┃关    于┃                                  ║");
	printf("║                              ┗━━━━┛                                  ║");
	printf("║                              ┏━━━━┓                                  ║");
	printf("║                     ③       ┃退    出┃                                  ║");
	printf("║                              ┗━━━━┛                                  ║");
	printf("║                                                                            ║");
	printf("║                                                         Copyright   @Lixeon║");
	printf("║                                                          lijing394@163.com ║");
	printf("╚══════════════════════════════════════╝");
	HideCursor();
	gotoxy(m,n);
    while(1)
	{
		c1=getch();
		switch(c1)
		{
		case 72 :  //UP
			printf("  ");
			n-=3;
			if(n<12)n=18;
			gotoxy(m,n);
			printf("★");
			gotoxy(m-1,n);
			break;
		case 80 :   //DOWN
   			printf("  ");
			n+=3;
			if(n>18)n=12;
			gotoxy(m,n);
			printf("★");
			gotoxy(m-1,n);
			break;
		case'\r':   //ENTER
			if(18==n)
				leave();
			if(15==n)
			{
				system("cls");
			    help();
				while(getch()){system("cls");start();}
			}
			if(12==n)
			{	
				system("cls");
				loading();
				return;
				/*
				switch ( Password_Authentification() )
				{
				  case 0:
					system("color 4E");
					printf("\n\n\n\n\t\t\t    密码错误，即将退出系统!\n\n\n"); 
					Sleep(1000);
				    exit(0);
				  case 1:
					printf("\n\n\n\n\t\t\t    正在进入，欢迎管理员!\n\n\n"); 
					Sleep(1000);
					return;
				}
				*/
			}
			break;
		}
	}
}

/*
/**************密码验证*****************
int Password_Authentification()
{
	char password[]="admin12345",temp_password[16];//用来存放用户输入的密码
    printf("\n");
	printf("\n\n\n\n\t\t\t*****欢迎登入超市库存管理系统*****\n");
    printf("\n\n\n\n\t\t\t请输入密码:");
    gets(temp_password);
	if(strcmp(password,temp_password)==0)//比较密码
		return 1;
	else
		return 0;
}
/**************修改密码*********/  //不超过 16个字符
/*
   void Modify_Password()
   FILE *fp;
   char temp_mima[20],temp1[20],temp2[20];temp_mima[20]//用来存放用户输入的密码，temp1[20],temp2[20]分别用来存放用户输入的两次修改的密码
   printf("\n");
    printf("\t\t         ======================        \n");
    printf("\t\t                 修改密码                 \n");
    printf("\t\t         ======================        \n");
    printf("\n");
	printf("\t\t           请输入原始密码:");
	scanf("\t\t%s",temp_mima);
    while(1)
    {
	if(strcmp(temp_mima,mima)==0)//比较密码
	{
		printf("\t请输入新密码:");
		scanf("%s",temp1);
		printf("\t请再输入一次:");
		scanf("%s",temp2);
		if(strcmp(temp1,temp2)==0)//如果输入的两次新密码都相同
		{
			printf("\t修改密码成功!!请记牢密码,任意键返回...");
			strcpy(mima,temp1);
			getch();break;
		}
		else
		{
			printf("\t输入两次密码不相同，修改失败!任意键返回...");
			getch();break;
		}
	}
	else
	{
		printf("\t密码错误!您不能进行密码修改!任意键返回...");
		getch();break;
	}
*/

/************关于**************/
void help()
{
	system("color 5A");
	printf("                    ★☆★☆★☆★☆★☆★☆★☆★☆★☆              \n");
	printf("                    ☆    超 市 库 存 管 理 系 统     ★              \n");
    printf("                    ★          Bata 1.5              ☆              \n");
    printf("                    ☆     关               于        ★              \n");
	printf("                    ★                                ☆              \n");
	printf("                    ☆★☆★☆★☆★☆★☆★☆★☆★☆★              \n");
	printf("                                                                      \n");
	printf("                                                                      \n");
	printf("                           这是第一次测试版，                         \n");
	printf("         UP                很多功能还不完善。                         \n");
	printf("         ↑                 而且bug仍然略多，                         \n");
	printf("                           经过不断调试开发。                         \n");
	printf("                     ┌──────────────┐    ┏━━┓     \n");
	printf("   ←   扬大   →    │相信我们的系统会越来越完善 !│    ┃确认┃     \n");
	printf("                     └──────────────┘    ┗━━┛     \n");
	printf("                               版本开发日志：                         \n");
	printf("         ↓            2015.12.24 V0.1.0  完成基本框架     回车       \n");
	printf("        DOWN           2015.12.26 V0.3.0  完成基本功能                \n");
	printf("                       2015.12.27 V1.0.0   Bata测试版                 \n");
	printf("                       2015.12.30 V1.5.0   测试版修正                 \n");
	printf("                              持续开发更新                            \n");
	printf("                                                  《C语言课程设计》   \n");
	printf("                             请按任意键返回        软件1502   李敬    \n");
}

/**********加载界面**********/
void loading()
{
    int i=0,m=4,n=3;
	printf("╔══════════════════════════════════════╗");
    printf("║                                                                            ║");
    printf("║  ╱▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏▔◥║");
    printf("║  ▏                                                                  ▏%%  ║");
    printf("║  ╲▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▏▁◢║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                     　┏　　　　┏┣━┏╭┓┏━┣━━┓                   ║");
    printf("║                     ┏┣━┓┏┓┏┻━┣━┓┃　┃　　┃                   ║");            
    printf("║                     　┃　┃┃┃┏┣━╰╮┓┃　┃　　┃                   ║");
    printf("║                     　┃　┃┃┃　┗┣╯┃┃┃　┃　　┃                   ║");
    printf("║                     　┃　┃┃┃┗━┣┛┣╯┗━┣━━╯                   ║");
    printf("║                     ┗╯┗╯┗╯╰━┛　╰┛　　┗　　　                   ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("╚══════════════════════════════════════╝");
    while(1)
	{
		  Sleep(50);
		  gotoxy(m+=2,n);
		  printf("■");
		  gotoxy(76,n);
		  printf("%2d",i+=3);
		  if(i==99)
		  {Sleep(1000);break;}
	}
	system("cls");
}

void gotoxy(int x,int y)//将光标移动到坐标为(x,y)的地方
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;                            
    HANDLE hConsoleOut;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
    csbiInfo.dwCursorPosition.X = x;                                    
    csbiInfo.dwCursorPosition.Y = y;                                    
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);  
}

void HideCursor()//隐藏光标
{
     CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
     SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


/*****************读取数据******************/
void read()
{
	FILE *fp;
	char name[10];                    
	printf("请输入所写入的数据文件名:"); 
	scanf("%s",name); 
	printf("正在导入数据.......:\n");
	Sleep(555);
	fp=fopen(name,"rb");
	if(fp == NULL)                   
	{ printf("打开文件错误...\n"); system("pause"); return; } 
	fread(&nn,sizeof(int),1,fp);
	fread(goods,sizeof(struct item),nn+1,fp);
	fclose(fp);
	printf("导入成功!\n");
	printf("请按任意键返回主菜单");
	getchar();
}


/*************系统颜色设置*************/
void colorsetting()
{
	int choose_1; char choose_2;
	system("cls");
	printf("\n\n\t\t选择以下方案\n");
	printf("\n\n\t\t1**************红底黑字\n");
	printf("\n\n\t\t2**************白底黑字\n");
	printf("\n\n\t\t3**************黑底红字\n");
	printf("\n\n\t\t4**************绿底蓝字\n");
	printf("\n\n\t\t5**************黄底紫字\n");
	printf("\n\n\t\t6**************系统默认\n");
	printf("\n\n\t\t\t\t\t请挑选您喜爱的颜色<1-5>......");
	scanf("%d",&choose_1);
	switch(choose_1)
	{
			case 1:	system("color 40");	break;
			case 2:	system("color 70");	break;
			case 3:	system("color 04");	break;
			case 4:	system("color 21"); break;
			case 5:	system("color 65");	break;
			case 6:	system("color 3f");	break;
			default:system("cls");error();getch();return;
	}
	printf("\n选择的颜色您还满意吗?(y返回主菜单/n继续选择)");
    scanf("%c",&choose_2); 
    if(choose_2=='Y'|| choose_2=='y') { system("cls"); main_menu();}
    else    colorsetting(); 
}


/****************保存数据********************/
void save()
{
	FILE *fp;
	fp=fopen("data.dat","wb");
	fwrite(&nn,sizeof(int),1,fp);
	fwrite(goods,sizeof(struct item),nn+1,fp);
	fclose(fp);
}

/*******生成文件****************
void WritetoText()
{
	int i=0; 
	FILE *fp;                                     
	char filename[30];                              
	printf("写入到文件:\n");                     
	printf("请输入所写入的文件名:"); 
	scanf("%s",filename); 
	if((fp=fopen(filename,"w"))==NULL)                   
	{ 
		printf("无法打开文件\n"); 
		system("pause"); 
		return; 
	} 
	fprintf(fp,"-------------------------------------------------------------------------------\n");                         
	fprintf(fp,"编号 姓名        电话            邮件                公司                分类  \n"); 
	fprintf(fp,"-------------------------------------------------------------------------------\n"); 
	for(i=1;i<=n;i++)                                                            
	{ 
		fprintf(fp,"%-3d  %-12s%-16s%-20s%-20s%-8s\n",i,per[i].name,per[i].tel,per[i].email,per[i].company,per[i].classify); 
		if(i>1&&i%10==0)                                                          
		{
			fprintf(fp,"-------------------------------------------------------------------------------\n");
		} 
	}
    fprintf(fp,"-------------------------------------------------------------------------------\n");
	fclose(fp);                                         //关闭文件 
	printf("写入成功!\n");
	system("pause"); 
}
*/
/************退出系统****************/
void leave()
{
			system("cls");
			printf("\n\n\n\n\n\n\n\n\t\t|--------感谢使用，再见!------|\t\n\n\n\n\n");
			exit(0);
}