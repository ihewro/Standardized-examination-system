#include "declare.h"
void MainInt() {
	printf("\t********************************************\n");
	printf("\t********************************************\n");
	printf("\t**  欢迎登陆自动判分一体化流程考试系统    **\n");
	printf("\t**                                        **\n");
	printf("\t**                                        **\n");
	printf("\t********************************************\n");
	printf("\t**            选择你的身份                **\n");
	printf("\t**                                        **\n");
	printf("\t**              1 - 管理员                **\n");
	printf("\t**              2 - 用户                  **\n");
	printf("\t**              3 - 退出                  **\n");
	printf("\t********************************************\n");
	printf("\t********************************************\n");
	printf("\t**        制作：  何炜 2015014278         **\n");
	printf("\t**                 ***                    **\n");
}

void AdminInt() {
	printf("\t**        欢迎进入管理界面！\t**        \n\n");
	printf("输入序号操作\n1 - 题库板块\n2 - 试卷板块\n3 - 学生板块\n4 - 返回上一级\n5 - 结束程序\n");
	char inpute[40];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {//学生板块
			ExambankInt();
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//试卷板块
			TestbankInt();
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {//学生板块
			QuerybyAdminInt();
			break;
		}
		else if (inpute[0] == '4'&& inpute[1] == '\0') {//返回上一级
			printf("正在返回上一级，请等待...\n");
			Sleep(1000);
			system("cls");
			main();
			break;
		}
		else if (inpute[0] == '5'&& inpute[1] == '\0') {//结束程序
			NormalExitProgram();
		}
		else {
			printf("输入错误，请重新输入正确的序号\n");
		}
	}
}
void UserInt(char num[20]) {
	printf("\t**        %s,您好！欢迎来到学生界面\t**        \n\n", num);
	printf("1 - 查询成绩\n2 - 进入考试\n3 - 返回上一级\n4 - 结束程序\n");
	char inpute[40];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {
			QuerybyStuInt();
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {
			TakingtestInt();
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {
			printf("正在返回上一级，请等待...\n");
			Sleep(1000);
			system("cls");
			main();
			break;
		}
		else if (inpute[0] == '4'&& inpute[1] == '\0') {
			NormalExitProgram();
			break;
		}
		else {
			printf("输入错误，请重新输入正确的序号\n");
		}
	}
}
void NormalExitProgram() {
	printf("\t    谢谢使用该程序！程序已经正常退出\n");
	exit(0);
}


