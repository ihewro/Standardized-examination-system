#define _CRT_SECURE_NO_WARNINGS
/*
 * 作者：何炜（计科1501班）（2015014278）
 * 运行环境：windows + vs 2015
 */
#include "declare.h"

jmp_buf j2;
jmp_buf j3;

char studentID[20];

/*
 * 算法部分
 */

//主函数
int main() {
	MainInt();
	setjmp(j2);
	int n;
	n = SelectId();
	if (n == 1)
		AdminInt();
	else if (n == 0)
	{
		Sleep(1000);
		system("cls");
		main();

	}
	else 
		UserInt(studentID);
	return 1;
}

int SelectId() {
	setjmp(j3);
	char inpute[40];//身份选择
	while (1) {
		int count = 1;
		int count2 = 5;
		scanf("%s", inpute);
		FILE *fp;
		if (inpute[0] == '1'&& inpute[1] == '\0') {//管理员
			if ((fp = fopen("password.txt", "r")) == NULL||_access("password.txt", 0) == -1) {
				printf("管理员信息配置有误！请联系管理员ihewro@163.com\n");
				//NormalExitProgram();
			}
			else {
				char pas2[100];
				fscanf(fp, "%s", pas2);
				fclose(fp);
				printf("请输入管理员密码：\n");
				char pas[100];
				scanf("%s", pas);
				while (strcmp(pas, pas2)) {
					count++;
					count2--;
					if (count > 5)
						break;//错误5次，退出输出循环
					printf("密码输入错误！你还有%d次机会\n", count2);
					scanf("%s", pas);
				}
				if (count > 5) {
					printf("密码输入错误5次，即将为你跳转到选择身份界面...\n");
					return 0;
				}
				else {
					printf("登录成功！\n\n");
					return 1;//返回1,证明是管理员身份
				}
			}
			//break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//学生
			FILE *fp;
			if ((fp = fopen("user.txt", "r")) == NULL|| _access("user.txt", 0) == -1) {
				printf("学生信息配置错误，请联系系统管理员！\n");
				//NormalExitProgram();
			}
			else {
				StudentId user[100];
				int fileend;
				fseek(fp, 0, 2);
				fileend = ftell(fp);
				rewind(fp);
				int i = 0;
				int usern = 0;
				while (ftell(fp) != fileend) {
					fscanf(fp, "%s\n", user[i].usrid);
					i++;
					usern++;
				}
				fclose(fp);
				printf("请输入你的学号\n");
				char num[20];
				scanf("%s", num);
				int errors = 1;
				int errors2 = 4;
				while (1) {
					if (errors > 4) {
						printf("密码输入错误5次，即将为你跳转到选择身份界面\n");
						return 0;//0返回到重新选择身份界面
					}
					for (i = 0; i < usern; i++) {
						if (strcmp(num, user[i].usrid) == 0) {
							printf("登录成功\n");//用户登录成功
							break;
						}
					}
					if (i >= usern) {//一共16个学生
						printf("学号无法与学生库信息匹配，你还有%d次机会\n", errors2);
						scanf("%s", &num);
						errors++;
						errors2--;
					}
					if (i < usern)
					{
						strcpy(studentID, num);
						return 2;//返回2，证明是学生身份
					}
				}
			}
			//break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {
			NormalExitProgram();
			break;
		}
		else {
			printf("输入序号有误，请重新输入！\n");
			longjmp(j3, 1);
		}
	}
	

}