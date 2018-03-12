#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define M 36
//1002672  1002700

struct city//定义相关结构体
{
    char type_name[60];//品牌名
    char fcity_name[60];//出发城市名
    char tcity_name[60];//到达城市名
    int time;//时效
    char way_type[60];//线路类型
    float h_price;//重货价格
    float h_discount;//重货折扣
    float l_price;//轻货价格
    float l_discount;//轻货折扣
};

struct city c[100];//定义结构体;

int main()
{
    clock_t start, finish;
     double Total_time1,Total_time2,Total_time3;
     printf("欢迎来到物流管理系统！\n");
     printf("_________________________________________________________________________________________\n");
     FILE *fp;
     char filename[40];
     printf("请输入文件名:\n");
     gets(filename);
     fp=fopen(filename,"r");//打开文件
     fseek(fp,72L,SEEK_SET);//从文件第二行开始读取

     int i;
     printf("请输入所在城市:\n");
     for(i=0;i<100;i++)
     {
            fscanf(fp,"%s%s%s%d%s%f%f%f%f",c[i].type_name,c[i].fcity_name,c[i].tcity_name,
                   &c[i].time,c[i].way_type,&c[i].h_price,&c[i].h_discount,&c[i].l_price,&c[i].l_discount);
     }
     fclose(fp);

     printf("**************************************功能一************************************************\n");
     start=clock();
     printf("您输入城市的物流公司有:\n");
     char zfcity_name[60];//应找寻城市
     scanf("%s",zfcity_name);
     int d,b;
     char tt[1000][50];
     for(i=0,d=0;i<M;i++)
    {
        if(strcmp(zfcity_name,c[i].fcity_name)==0)//比较出发城市
        {
            d++;
            if(d==1)
            {
                printf("%s\n",tt[1]);
            }
            else
            {
              for(b=1;b<d;b++)
              {
                if((strcmp(c[i].type_name,tt[b]))==0)
                {
                   break;
                }
              }
              if(b>=d)
              {
                  strcpy(tt[b],c[i].type_name);
                  printf("%s\n",tt[b]);
              }
            }
        }
    }
     finish = clock();
     Total_time1= (double)(finish-start) / CLOCKS_PER_SEC;
     printf( "%f seconds/n", Total_time1);//输出功能一用时
     printf("\n");

     printf("****************************************功能二**********************************************\n");
     start = clock();
     printf("请输入包裹到达城市:\n");
     char ztcity_name[60];
     scanf("%s",ztcity_name);
     printf("-----------------------------------------------------------------------------------------\n");
     printf("品牌      |线路类型             |重货单价               |轻货单价\n");
     printf("-----------------------------------------------------------------------------------------\n");
     for(i=0;i<M;i++)
     {
         if(strcmp(zfcity_name,c[i].fcity_name)==0)
         if(strcmp(ztcity_name,c[i].tcity_name)==0)
         {
             printf("%-10s| %-20s|%-10f\t|%-10f\n",
                    c[i].type_name,c[i].way_type,c[i].h_price*c[i].h_discount/10,c[i].l_price*c[i].l_discount/10);
             printf("-----------------------------------------------------------------------------------------\n");
         }
     }
     finish = clock();
     Total_time2= (double)(finish-start) / CLOCKS_PER_SEC;
     printf( "%f seconds/n", Total_time2);//输出功能二用时
     printf("\n");

     printf("****************************************功能三**********************************************\n");
     start = clock();
     printf("请输入包裹重量:\n");
     int weight;//定义包裹重量
     scanf("%d kg",&weight);
     printf("请输入包裹类型:\n");
     char type[10];//定义包裹类型
     scanf("%s",type);
     printf("------------------------------------------------------------\n");
     printf("品牌      |线路类型             |价格\n");
     printf("------------------------------------------------------------\n");
     for(i=0;i<M;i++)//在已知出发城市与到达城市的条件下，输出运送价格。
     {
         if(strcmp(zfcity_name,c[i].fcity_name)==0)
         if(strcmp(ztcity_name,c[i].tcity_name)==0)
         {
             if(strcmp(type,"重货")==0)
             {
                  printf("%-10s| %-20s|%-10f\n",c[i].type_name,c[i].way_type,weight*c[i].h_price*c[i].h_discount/10);
                  printf("------------------------------------------------------------\n");
             }

             else if(strcmp(type,"轻货")==0)
                printf("%s  在您选择 %s  类型下,运送价格为:%f\n",c[i].type_name,c[i].way_type,weight*c[i].l_price*c[i].l_discount/10);
             else
                printf("没有这种类型的货物哦\n");
         }
     }
     finish = clock();
     Total_time3= (double)(finish-start) / CLOCKS_PER_SEC;
     printf( "%f seconds/n", Total_time3);//输出功能三用时
     printf("\n");

     printf("********************************选做功能一*****************************************************\n");
     start=clock();
     double Total_time4,Total_time5;
     printf("您是否要获得最佳物流方式推荐？\n");
     char w[4];
     scanf("%s",w);
     if(strcmp(w,"No")==0) return 0;
     else ;
     float price[50]={0};
     int count=0;
     for(i=0;i<M;i++)
     {
         if(strcmp(zfcity_name,c[i].fcity_name)==0)
         if(strcmp(ztcity_name,c[i].tcity_name)==0)
         {
             if(strcmp(type,"重货")==0)
             {
                 price[i]=weight*c[i].h_price*c[i].h_discount/10;
                 count++;
             }
             if(strcmp(type,"轻货")==0)
             {
                 price[i]=weight*c[i].l_price*c[i].l_discount/10;
                 count++;
             }
         }
     }
     int k=0;
     for(i=0;i<M;i++)
     {
         if(strcmp(zfcity_name,c[i].fcity_name)==0)
         if(strcmp(ztcity_name,c[i].tcity_name)==0)
         {
             k=i;
             break;
         }
     }
     float min;
     for(i=k;i<count;i++)
        if(min>price[i])
            min=price[i];
     printf("经系统计算判断，您的最佳方案是：%s品牌  %s线路类型\n",c[i].type_name,c[i].way_type);
     finish = clock();
     Total_time4= (double)(finish-start) / CLOCKS_PER_SEC;
     printf( "%f seconds/n", Total_time4);//输出选做功能一用时
     printf("\n");

     printf("********************************选做功能二*****************************************************\n");
     start = clock();
     printf("您是否要进行时效优化？\n");
     char m[4];
     scanf("%s",m);
     if(strcmp(m,"No")==0) return 0;
     else ;
     int t=10000;
     for(i=k;i<count;i++);
         if((t>c[i].time)&&(c[i].time!=0))
            t=c[i].time;
     printf("时效最优时为%d，此时您的最佳选择是：%s品牌  %s线路类型\n",c[i].time,c[i].type_name,c[i].way_type);
     finish = clock();
     Total_time5= (double)(finish-start) / CLOCKS_PER_SEC;
     printf( "%f seconds/n", Total_time5);//输出选做功能二用时
     printf("\n");
     system("pause");
return 0;
}
