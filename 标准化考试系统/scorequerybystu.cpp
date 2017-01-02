#include "declare.h"

/*申明外部变量*/
extern char studentID[20];
extern ST_student student[100];
extern int studentamount;

void QuerybyStuInt() {
	printf("\t**        分数查询系统界面！\t**        \n\n");
	FILE *fp;
	if ((fp = fopen("studentscore.txt", "a+")) == NULL) {
		printf("error\n");
	}
	rewind(fp);//指针归位
	fseek(fp, 0, 2);//指针移到尾部
					//fseek(fp2, 0, 2);//指针移到尾部
	int fileend;
	fileend = ftell(fp);//记录文件的尾部
	rewind(fp);//指针归位
	ST_student *p;
	p = student;
	if (ftell(fp) == fileend) {
		printf("没有学生参加过考试，学生成绩文件为空\n");
		fclose(fp);
	}
	else {
		studentamount = 0;
		while (ftell(fp) != fileend) {//读取学生成绩信息到student数组中
			fread(p, sizeof(ST_student), 1, fp);
			studentamount++;
			p++;
		}
		fclose(fp);//信息录入后立即关闭文件
		printf("%-13s%-13s%-13s\n", "序号", "试卷编号", "考试成绩");
		int i;
		for (i = 0; i < studentamount; i++) {
			if (strcmp(studentID, student[i].id) == 0) {
				for (int j = 0; j < student[i].testnumbers; j++) {
					printf("%-13d%-13d%-13d\n", j + 1, student[i].exams[j], student[i].exams_score[j]);
				}
				break;
			}
		}
		if (i >= studentamount) {
			printf("\n你未参加任何考试！\n");
		}
		printf("\n输入序号选择:\n1 - 返回上一级\n2 - 结束程序\n");
		char inpute[40];
		while (1) {
			scanf("%s", inpute);
			if (inpute[0] == '1'&& inpute[1] == '\0') {
				printf("正在返回上一级，请等待...\n");
				Sleep(1000);
				system("cls");
				UserInt(studentID);
				break;
			}
			else if (inpute[0] == '2'&& inpute[1] == '\0') {
				NormalExitProgram();
				break;
			}
			else {
				printf("请输入正确的序号！\n");
			}
		}

	}
}