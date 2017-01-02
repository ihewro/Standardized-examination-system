#include "declare.h"

/*声明外部变量*/
extern int testnum;
extern int testamount;
extern ST_test test[20];
extern ST_test current_test;
extern int studentstatus;
extern int current_studentfilenum;
extern ST_student student[100];
extern int studentamount;

/*该文件下的全局变量*/
int currenttest_studentamount=0;//参加该份试卷的学生人数
ST_currenttest_student currenttest_student[100];//存储了参加该份试卷的学生信息


void QuerybyAdminInt() {
	printf("\t**        分数查询系统界面！\t**        \n\n");
	printf("请输入序号操作:\n1 - 按试卷查询\n2 - 按学生查询\n3 - 返回上一级\n4 - 退出程序\n");
	char inpute[40];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {
			QuerybyTest();
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {
			QuerybyStu();
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {
			printf("正在返回上一级，请等待...\n");
			Sleep(1000);
			system("cls");
			AdminInt();
			break;

		}
		else if (inpute[0] == '4'&& inpute[1] == '\0') {
			NormalExitProgram();
			break;
		}
		else {
			printf("请输入正确的序号！\n");
		}
	}
}


void QuerybyTest() {
	char inpute[40];
	TestList();
	printf("输入序号操作：\n1 - 查询成绩\n2 - 返回上一级\n3 - 结束程序\n");
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {
			printf("输入试卷序号，查看该份试卷的学生成绩信息：\n");
			scanf("%d", &testnum);//输入要操作的试卷序号
			while (testnum > testamount) {
				printf("不存在该试卷，请重新输入:\n");
				scanf("%d", &testnum);
			}
			InitCurrent_test(&current_test);//初始化当前操作的试卷信息
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
				currenttest_studentamount = 0;
				studentamount = 0;
				while (ftell(fp) != fileend) {//读取学生成绩信息,边读取，变查询该学生是否参加当前试卷，如果是，输出成绩和ID。
					fread(p, sizeof(ST_student), 1, fp);
					for (int j = 0; j < p->testnumbers; j++) {
						if (current_test.num == p->exams[j])
						{
							strcpy(currenttest_student[currenttest_studentamount].id, p->id);
							currenttest_student[currenttest_studentamount].socre = p->exams_score[j];
							currenttest_studentamount++;
						}
					}
					studentamount++;
					p++;
				}
				//printf("成绩文件中共有%d个学生信息\n", studentamount);
				fclose(fp);
				printf("%-13s%-13s%-13s\n", "名次", "学生ID", "学生成绩");
				//快速排序算法：对学生的成绩进行排序
				QuickSort(currenttest_student);
				for (int i = 0; i < currenttest_studentamount; i++)
				{
					printf("%-13d%-13s%-13d\n", i + 1, currenttest_student[currenttest_studentamount - i - 1].id, currenttest_student[currenttest_studentamount - i - 1].socre);
				}
				printf("********************************************\n输入序号操作:\n1 - 返回上一级\n2 - 结束程序\n");
				while (1) {
					scanf("%s", inpute);
					if (inpute[0] == '1'&& inpute[1] == '\0') {
						printf("正在返回上一级，请等待...\n");
						Sleep(1000);
						system("cls");
						QuerybyTest();
						break;
					}
					else if (inpute[0] == '2'&& inpute[1] == '\0') {
						NormalExitProgram();
						break;
					}
				}
			}
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {
			QuerybyTest();
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {
			NormalExitProgram();
			break;
		}
		else {
			printf("请输入正确的序号:\n");
		}

	}
}

void QuerybyStu() {
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
		printf("输入序号操作：\n1 - 查询学生成绩\n2 - 输出参加过考试的学生\n3 - 返回上一级\n4 - 结束程序\n");
		char inpute[40];
		while (1) {
			scanf("%s", inpute);
			if (inpute[0] == '1'&& inpute[1] == '\0') {
				printf("请输入要查询的学生学号:\n");
				char inpute[20];
				scanf("%s", inpute);
				printf("%-13s%-13s%-13s\n", "序号", "试卷编号", "考试成绩");
				int i;
				for (i = 0; i < studentamount; i++) {
					if (strcmp(inpute, student[i].id) == 0) {
						for (int j = 0; j < student[i].testnumbers; j++) {
							printf("%-13d%-13d%-13d\n", j + 1, student[i].exams[j], student[i].exams_score[j]);
						}
						break;
					}
				}
				if (i >= studentamount) {
					printf("该学号对应的学生未参加任何考试！\n");
				}
				break;
			}
			else if (inpute[0] == '2'&& inpute[1] == '\0') {
				printf("%-13s%-13s%-13s\n", "序号", "学生ID", "参加次数");
				for (int i = 0; i < studentamount; i++) {
					printf("%-13d%-13s%-13d\n", i + 1, student[i].id, student[i].testnumbers);
				}
				break;
			}
			else if (inpute[0] == '3'&& inpute[1] == '\0') {
				QuerybyAdminInt();
				break;
			}
			else if (inpute[0] == '4'&& inpute[1] == '\0') {
				NormalExitProgram();
				break;
			}
			else {
				printf("请输入正确的序号：\n");
			}
		}
		printf("********************************************");
		printf("输入序号操作：\n1 - 返回上一级\n2 - 结束程序\n");
		while (1) {
			scanf("%s", inpute);
			if (inpute[0] == '1'&& inpute[1] == '\0') {
				QuerybyStu();
				break;
			}
			else if (inpute[0] == '2'&& inpute[1] == '\0') {
				NormalExitProgram();

			}
			else {
				printf("请输入正确的序号:\n");
			}
		}
	}
}




/*快速排序算法*/
void QuickSort(ST_currenttest_student currenttest_student[100]) {
	Qsort(currenttest_student,0, currenttest_studentamount-1);
}

void Qsort(ST_currenttest_student currenttest_student[100],int low,int high) {
	int pivot;
	if (low < high) {
		pivot = Partition(currenttest_student, low, high);
		Qsort(currenttest_student, low, pivot - 1);
		Qsort(currenttest_student, pivot + 1,high);
	}
}

int Partition(ST_currenttest_student currenttest_student[100], int low, int high) {
	int pivotkey;
	pivotkey = currenttest_student[low].socre;
	while (low < high) {
		while (low < high && currenttest_student[high].socre >= pivotkey)
			high--;
		swap(currenttest_student, low, high);
		while (low < high && currenttest_student[low].socre <= pivotkey)
			low++;
		swap(currenttest_student, low, high);
	}
	return low;
}

void swap(ST_currenttest_student currenttest_student[100], int i,int j) {
	int tempsocre = currenttest_student[i].socre;
	char tempid[20];strcpy(tempid, currenttest_student[i].id);
	currenttest_student[i].socre = currenttest_student[j].socre;
	strcpy(currenttest_student[i].id, currenttest_student[j].id);
	currenttest_student[j].socre = tempsocre;
	strcpy(currenttest_student[j].id, tempid);
}
