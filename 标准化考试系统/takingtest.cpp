#include "declare.h"

/*学生已经参加过的试题不能再次参加！*/

/*申明外部变量*/
extern int testamount;
extern int testnum;
extern ST_test test[20];
extern ST_test current_test;
extern ChooseQues test_chooseques[200];
extern BankQues test_bankques[200];
extern CalcuQues test_calcuques[200];
extern int test_choosequescount;
extern int test_bankquescount;
extern int test_calcuquescount;
extern char studentID[20];


/*该文件下的全局变量*/
int rightchooseques = 0;//答对的选择题
int rightbankques = 0;//答对的填空题
int rightcalcuques = 0;//答对的计算题
int rightamount = 0;//答对的总题目数量
AnswerbyUser choosequesanswer[100];//存储用户输入的选择题答案的数组
AnswerbyUser bankquesanswer[100];//存储用户输入的填空题答案的数组
AnswerbyUser calcuquesanswer[100];//存储用户输入的计算题答案的数组
char correctanswer[40] = "正确";
char falseanswer[40] = "错误";
int studentgrade;//学生该场考试的总成绩
int studentstatus;
int current_studentfilenum;//当前操作的学生在成绩文件中的序号
ST_student student[100];//把学生成绩文件数据存储在该数组里面
int studentamount = 0;//学生成绩文件里面的学生人数

/*界面*/
void TakingtestInt() {
	int result;
	result = TestList();
	if (result == 0) {
		//NormalExitProgram();
	}
	else {
		printf("\n请输入试题序号进入考试：\n");
		int n;
		scanf("%d", &n);
		while (n > testamount || n < 1) {
			printf("请输入正确的试题序号:");
			scanf("%d", &n);
		}
		testnum = n;
		InitCurrent_test(&current_test);
		studentstatus = Checkstudentstatus();
		if (studentstatus == 3) {
			printf("你已经参加了本次考试！请勿重复参加。\n");
			printf("\n输入序号操作:\n1 - 返回上一级\n2 - 结束程序\n");
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
		else {
			AnswerChooseques();
			AnswerBankques();
			AnswerCalcuques();
			Evaluateques();
			Gradesave();
			printf("********************************************\n您的成绩已经存储完毕！\n输入序号操作：\n1 - 返回上一级\n2 - 结束程序\n");
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
			}
		}
	}
}

/*回答问题*/
void AnswerChooseques() {
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 1);//获取该试卷的选择题文件的路径
	if ((fp = fopen(quesfilename, "r")) == NULL) {
		printf("ERROR\n");
		printf("错误路径：%s\n", quesfilename);
		exit(0);
	}
	printf("选择题文件打开成功：%s\n", quesfilename);
	ChooseQues *p1;
	p1 = test_chooseques;
	rewind(fp);//指针归位
	fseek(fp, 0, 2);
	int quesfileend;
	quesfileend = ftell(fp);//记录<questions>文件的尾部
	rewind(fp);//指针归位
	int i;
	i = 1;//输出编号
	int j;//选择题的选项
	if (ftell(fp) == quesfileend) {//该份试卷没有选择题
		fclose(fp);
	}
	else {//该份试卷有选择题的情况下
		printf("\t**        选择题答题界面：\t**        \n\n");
		while (ftell(fp) != quesfileend) {//判断fp指针是否读取到<questions>文件尾部
			fread(p1, sizeof(ChooseQues), 1, fp);
			printf("%d - %s\n", i, p1->ask);
			for (j = 0; j < 4; j++) {
				printf("%c. %s", j + 'A', p1->answer[j]);
				printf("\n");
			}
			printf("\n请输入你的答案：");
			scanf("%s", &choosequesanswer[i - 1].right);
			while (choosequesanswer[i - 1].right[0] < 'A' || choosequesanswer[i - 1].right[0] > 'D')
			{
				printf("您输入的答案不合法！请输入正确的答案: ");
				getchar();
				scanf("%c", &choosequesanswer[i - 1].right);
			}
			if (strcmp(choosequesanswer[i - 1].right, p1->right) == 0)
				rightchooseques++;
			i++;
			p1++;
			test_choosequescount++;
		}
		printf("\n");
		fclose(fp);
	}
}
void AnswerBankques() {
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 2);//获取该试卷的填空题文件的路径
	if ((fp = fopen(quesfilename, "r")) == NULL) {
		printf("ERROR\n");
		printf("错误路径：%s\n", quesfilename);
		exit(0);
	}
	printf("填空题文件打开成功：%s\n", quesfilename);
	BankQues *p2;
	p2 = test_bankques;
	rewind(fp);//指针归位
	fseek(fp, 0, 2);
	int quesfileend;
	quesfileend = ftell(fp);//记录<questions>文件的尾部
	rewind(fp);//指针归位
	int i;
	i = 1;//输出编号
	if (ftell(fp) == quesfileend) {
		fclose(fp);
	}
	else {
		printf("\n\t**        填空题答题界面：\t**        \n\n");
		while (ftell(fp) != quesfileend) {//判断fp指针是否读取到<questions>文件尾部
			fread(p2, sizeof(BankQues), 1, fp);
			printf("%d - %s\n", i, p2->ask);
			printf("\n请输入你的答案:");
			scanf("%s", bankquesanswer[i - 1].right);
			if (strcmp(bankquesanswer[i - 1].right, p2->right) == 0)
				rightbankques++;
			i++;
			p2++;
			test_bankquescount++;
		}
		fclose(fp);
	}
}
void AnswerCalcuques() {
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 3);//获取该试卷的选择题文件的路径
	if ((fp = fopen(quesfilename, "r")) == NULL) {
		printf("ERROR\n");
		printf("错误路径：%s\n", quesfilename);
		exit(0);
	}
	printf("计算题文件打开成功：%s\n", quesfilename);
	CalcuQues *p3;
	p3 = test_calcuques;
	rewind(fp);//指针归位
	fseek(fp, 0, 2);
	int quesfileend;
	quesfileend = ftell(fp);//记录<questions>文件的尾部
	rewind(fp);//指针归位
	int i;
	i = 1;//输出编号
	if (ftell(fp) == quesfileend) {
		fclose(fp);
	}
	else {
		printf("\n\t**        计算题答题界面：\t**        \n\n");
		while (ftell(fp) != quesfileend) {//判断fp指针是否读取到<questions>文件尾部
			fread(p3, sizeof(CalcuQues), 1, fp);
			printf("%d - %s\n", i, p3->ask);
			printf("\n请输入你的答案:");
			scanf("%s", calcuquesanswer[i - 1].right);
			if (strcmp(calcuquesanswer[i - 1].right, p3->right) == 0)
				rightcalcuques++;
			i++;
			p3++;
			test_calcuquescount++;
		}
		fclose(fp);
	}
}


/*评估问题*/
void Evaluateques() {//分析答题的情况并把答题情况存储起来以便后面的查询
	EvaluateChooseques();
	EvaluateBankques();
	EvaluateCalcuques();
}

void EvaluateChooseques() {
	char judge[40];
	printf("\t**        选择题答题情况：\t**        \n\n");
	printf("\n%-13s%-13s%-13s%s\n", "题号", "标准答案", "您的答案", "评价");
	int i;
	int j = 1;//题目编号
	for (i = 0; i < test_choosequescount; i++) {
		if (strcmp(test_chooseques[i].right, choosequesanswer[i].right) == 0)
			strcpy(judge, correctanswer);
		else
			strcpy(judge, falseanswer);
		printf("%-13d%-13s%-13s%s\n", j, test_chooseques[i].right, choosequesanswer[i].right, judge);
		j++;
	}
	printf("\n你答对了%d道选择题 \n\n", rightchooseques);
}
void EvaluateBankques() {
	char judge[40];
	printf("\t**        填空题答题情况：\t**        \n\n");
	printf("\n%-13s%-13s%-13s%s\n", "题号", "标准答案", "您的答案", "评价");
	int i;
	int j = 1;//题目编号
	for (i = 0; i < test_bankquescount; i++) {
		if (strcmp(test_bankques[i].right, bankquesanswer[i].right) == 0)
			strcpy(judge, correctanswer);
		else
			strcpy(judge, falseanswer);
		printf("%-13d%-13s%-13s%s\n", j, test_bankques[i].right, bankquesanswer[i].right, judge);
		j++;
	}
	printf("\n你答对了%d道填空题 \n\n", rightbankques);
}
void EvaluateCalcuques() {
	char judge[40];
	printf("\t**        计算题答题情况：\t**        \n\n");
	printf("\n%-13s%-13s%-13s%s\n", "题号", "标准答案", "您的答案", "评价");
	int i;
	int j = 1;//题目编号
	for (i = 0; i < test_calcuquescount; i++) {
		if (strcmp(test_calcuques[i].right, calcuquesanswer[i].right) == 0)
			strcpy(judge, correctanswer);
		else
			strcpy(judge, falseanswer);
		printf("%-13d%-13s%-13s%s\n", j, test_calcuques[i].right, calcuquesanswer[i].right, judge);
		j++;
	}
	printf("\n你答对了%d道计算题 \n\n", rightcalcuques);
}

void Gradesave() {
	FILE *fp;
	if ((fp = fopen("studentscore.txt", "r+")) == NULL) {//必须使用r+而不能使用a+打开
		printf("error\n");
	}
	ST_student *q;
	studentgrade = rightchooseques*current_test.value[0] + rightbankques*current_test.value[1] + rightcalcuques*current_test.value[2];
	int grade = rightchooseques*current_test.value[0] * test_choosequescount + rightbankques*current_test.value[1] * test_bankquescount + rightcalcuques*current_test.value[2] * test_calcuquescount;
	printf("该份试卷的满分为：%d,你的总分为：%d\n", grade,studentgrade);
	if (studentstatus == 0) {//如果学生成绩文件为空
		strcpy(student[0].id, studentID);
		student[0].exams[0] = current_test.num;
		student[0].exams_score[0] = studentgrade;
		student[0].testnumbers = 1;
		rewind(fp);//把指针移到文件起始处
		q = &student[0];
		fwrite(q, sizeof(ST_student), 1, fp);//重写要修改的学生成绩文件
		fclose(fp);
		//printf("当前学生ID为：%s\n", student[0].id);
	}
	else {//学生成绩文件不为空
		if (studentstatus == 1) {//学生成绩文件并没有该学生！
			strcpy(student[current_studentfilenum].id ,studentID);
			student[current_studentfilenum].exams[0] = current_test.num;
			student[current_studentfilenum].exams_score[0] = studentgrade;
			student[current_studentfilenum].testnumbers = 1;
			fseek(fp, 0, 2);//把指针移到文件尾部
			q = &student[current_studentfilenum];
			fwrite(q, sizeof(ST_student), 1, fp);//重写要修改的学生成绩文件
			fclose(fp);
			//printf("1当前学生ID为：%s\n", student[current_studentfilenum].id);

		}
		else if (studentstatus == 2) {//学生成绩文件已经有该学生了,但该学生没有参加本场考试
			strcpy(student[current_studentfilenum].id ,studentID);
			student[current_studentfilenum].exams[student[current_studentfilenum].testnumbers] = current_test.num;
			student[current_studentfilenum].exams_score[student[current_studentfilenum].testnumbers] = studentgrade;
			student[current_studentfilenum].testnumbers++;
			rewind(fp);
			//printf("当前学生的位置：%d\n", current_studentfilenum);
			fseek(fp, current_studentfilenum * sizeof(ST_student), 0);//把文件指针需要修改的同学的开始
			int pos = ftell(fp);
			//printf("文件指针距离头部的位置%d\n", pos);
			q = &student[current_studentfilenum];
			fwrite(q, sizeof(ST_student), 1, fp);//修改学生成绩文件
			fclose(fp);
			//printf("2当前学生ID为：%s\n", student[current_studentfilenum].id);
		}
		else
			printf("error!!\n");
	}
}

/*
* 0: 学生成绩文件为空
* 1: 学生成绩文件不为空，但学生没有被录入学生成绩文件中
* 2: 学生成绩文件不为空，而且学生被录入学生成绩文件中，但没有参加本场考试
* 3: 学生成绩文件不为空，而且学生被录入学生成绩文件中，并且已经参加本场考试
*/
int Checkstudentstatus() {
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
		current_studentfilenum = 0;
		fclose(fp);
		return 0;//如果学生成绩文件为空
	}
	else {//学生成绩文件不为空
		studentamount = 0;
		while (ftell(fp) != fileend) {//读取学生成绩信息到student数组中
			fread(p, sizeof(ST_student), 1, fp);
			studentamount++;
			p++;
		}
		fclose(fp);//信息录入后立即关闭文件
		int i, j;
		for (i = 0; i < studentamount; i++) {//查询当前学生ID是否已经被录入过
			if (strcmp(studentID,student[i].id)==0) {
				for (j = 0; j < student[i].testnumbers; j++) {
					if (current_test.num == student[i].exams[j])
					{
						return 3;//当前学生在成绩文件中，并且参加了本次试卷
					}
				}
				if (j >= student[i].testnumbers)
				{
					current_studentfilenum = i;
					return 2;//当前学生在成绩文件中，但是本次试卷没有参加
				}
			}
		}
		if (i >= studentamount)
		{
			current_studentfilenum = i;
			return 1;//当前学生不在成绩文件中
		}
	}
}
