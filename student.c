#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define MAX 100 
//菜单功能 
int menu()
{
	printf("*****************************************\n");
	printf("*         欢迎使用学生管理平台          *\n");
	printf("*****************************************\n");
	printf("*              请选择功能               *\n");
	printf("*****************************************\n");
	printf("*            1.录入学生信息             *\n");
	printf("*            2.打印学生信息             *\n");
	printf("*            3.保存学生信息             *\n");
	printf("*            4.读取学生信息             *\n");
	printf("*            5.统计学生信息             *\n");
	printf("*            6.查找学生信息             *\n");
	printf("*            7.修改学生信息             *\n");
	printf("*            8.删除学生信息             *\n");
	printf("*              0.退出系统               *\n");
	printf("*****************************************\n");
	printf("请选择功能编号: ");
	int select =0;
	scanf("%d", &select);
	printf("select> %d\n", select);
	return select;
}
	void addstudent();
	void printstudent();
	void savestudent();
	void loadstudent();
	void statisticstudent();
	void findstudent();
	void modifystudent();
	void deletestudent();

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(CP_UTF8);//防止乱码
    SetConsoleCP(CP_UTF8);      //防止运行时乱码
	while(1)
	{ 
		switch (menu())
		{
			case 1:
			    addstudent();
			     break;	
            case 2:
			    printstudent();
			     break;
            case 3:
			    savestudent();
			     break;
			case 4:
			    loadstudent();
			     break;
			case 5:
			    statisticstudent();
			     break;
			case 6:
		        findstudent();
			     break;
			case 7:
			    modifystudent();
			     break;
			case 8:
			     deletestudent();
			     break;
			case 0:
			    printf("退出系统\n");
				return 0;
			default:
			    printf("输入错误,请重新选择\n");
				break;	 
			
		}
		    system("pause");  //每次都暂停停留一下
			system("cls");	 //清屏
	}
	return 0;
}

//学生结构
typedef struct student
{
     char number[20];          //学号
	 char name[20];            //姓名
	 float chinese;            //语文成绩
	 float math;               //数学成绩
	 float English;            //英语成绩
}student;
      
    student stu[MAX];          //全局变量，定义最大学生数
	int count = 0;

	void addstudent() 
	{
		student s;

		printf("学号 姓名 语文成绩 数学成绩 英语成绩");
		scanf("%s %s %f %f %f",s.number, s.name, &s.chinese, &s.math, &s.English);
        stu[count] = s;
		count++;

		printf("录入成功，当前共有%d名学生 \n", count);
		if(count >= MAX)
		{
			printf("人数已满（%d人),不能在录入了 \n",MAX);
			return;
		}
	}
void printstudent()
{
	int i = 0;
	printf("%-14s %-10s %-8s %-8s %-8s\n", "学号","姓名","语文","数学","英语");  // - 代表左对齐
	for (i = 0 ;i<count; i++)
    {
	printf("%-14s %-10s %-8.1f %-8.1f %-8.1f\n",
	        stu[i].number,
			stu[i].name,
			stu[i].chinese,
			stu[i].math,
			stu[i].English); 
    }
	printf("共%d名学生", count);
}
void savestudent()
{
//打开文件
   FILE *fp =fopen("student.txt","w");
	if(fp == NULL)
	{
		printf("打开文件失败，无法保存\n");
		return;
	}
	fprintf(fp,"%d\n",count);//往文件里打印

	for(int i = 0; i <count; i++)
	{
		fprintf(fp,"%s %s %f %f %f\n",
		   stu[i].number,
		   stu[i].name,
		   stu[i].chinese,
		   stu[i].math,
		   stu[i].English);
	}
	fclose(fp);
	printf("保存成功，共%d名学生,文件:student.txt\n",count);
}
void loadstudent()
{
   FILE *fp = fopen("student.txt","r");
   fscanf(fp, "%d", &count);
   for(int i = 0; i<count; i++)
   {
	fscanf(fp, "%s %s %f %f %f",
	       stu[i].number,
		   stu[i].name,
		   &stu[i].chinese,
		   &stu[i].math,
		   &stu[i].English);
   }
      fclose(fp);
	  printf("读取成功,共%d名学生\n", count);
}
void statisticstudent()
{
  float s1 = 0, s2 = 0, s3 =0;//s123是累加器 要算三科的成绩总和

  for(int i = 0; i < count; i++)
  {
	s1 = s1+stu[i].chinese;//累加
    s2 = s2+stu[i].math;
    s3 = s3+stu[i].English;
  }
   printf("学生总数 : %d人\n", count);
   printf("语文平均分 : %.1f\n", s1 / count);
   printf("数学平均分 : %.1f\n", s2/ count);
   printf("英语平均分 : %.1f\n", s3 / count);
   printf("三科总平均 : %.1f\n", (s1 + s2 + s3) / count / 3);
}

void findstudent()
{
	char key[20];       //存用户输入的学号
	printf("请输入学号: ");
	scanf("%s", key);

	for(int i = 0; i < count; i++)
	{	if(strcmp(stu[i].number, key) == 0)
        {
           printf("%s %s %f %f %f\n",
		   stu[i].number,
		   stu[i].name,
		   stu[i].chinese,
		   stu[i].math,
		   stu[i].English); 
          
		   return;
		}
	}
	printf("没有找到\n");	
}
void modifystudent()
{
    char key[20];
	printf("请输入要修改的学号： ");
	scanf("%s", key);

	for(int i = 0; i < count; i++)
	{
      if(strcmp(stu[i].number, key) == 0)
	  {
         printf("原来的信息: %s %s %f %f %f\n",
	     stu[i].number,
		 stu[i].name,
		 stu[i].chinese,
		 stu[i].math,
		 stu[i].English);
         
         printf("请输入新的学号 姓名 语文 数学 英语");
		 scanf("%s %s %f %f %f",
		   stu[i].number,
		   stu[i].name,
		   &stu[i].chinese,
		   &stu[i].math,
		   &stu[i].English);

		   printf("修改成功\n");
		   return;
		  }
	}
}
void deletestudent()
{
  char key[20];
  int i, j;
  printf("要删的学号：");
  scanf("%s", key);
  for(i = 0; i< count; i++)
  {
    if(strcmp(stu[i].number,key))
{
      for(j = i; j < count - 1; j++)
	      stu[j] = stu[j + 1];
		  count--;
		  printf("删掉了");
		  return;
}
  }
printf("查无此人\n");
}



