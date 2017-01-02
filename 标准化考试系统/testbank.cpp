#include "declare.h"
jmp_buf j4;

/*删除的一个优化：如果没有文件，就直接跳过删除。先查询有没有该文件*/
/*优化：返回上一级有问题*/

/*申明外部变量*/
extern ST_exambank current_exambank;
extern int exambanknum;
extern int choosequescount;
extern int bankquescount;
extern int calcuquescount;
extern ChooseQues chooseques[200];
extern BankQues bankques[200];
extern CalcuQues calcuques[200];
extern int eaxmbankamount;

/*该文件下的全局变量*/
ST_test test[20];//从TestInfoOverview.txt文件中读取试卷并且存储到该数组中
ST_test current_test; //当前操作的试卷
int testnum = -1;//当前操作的试卷序号
int testamount = 0; //试卷的数量,初始化为0

ChooseQues test_chooseques[200];//当前试卷的选择题数据存储到该数组中
BankQues test_bankques[200];//当前试卷的填空题数据存储到该数组中
CalcuQues test_calcuques[200];//当前试卷的计算题数据存储到该数组中

int test_choosequescount = 0;//试卷中选择题目的数量
int test_bankquescount = 0;//试卷中填空题目的数量
int test_calcuquescount = 0;//试卷中计算题目的数量


/*界面*/
void TestbankInt() {
	printf("\t**        试卷管理系统界面！\t**        \n\n");
	char ch;
	FILE *fp;
	if (_access("testbank", 0)) {
		_mkdir("testbank");
	}
	if ((fp = fopen("testbank/TestInfoOverview.txt", "a+")) == NULL) {
		printf("路径文件 testbank/TestInfoOverview.txt 打开失败，检查是否有权限操作\n");
		printf("error\n");
		exit(0);
	}
	ch = fgetc(fp);
	if (ch == EOF)
		TestbankNoneInt(fp);
	else
		TestbankHaveInt(fp);
}
void TestbankHaveInt(FILE * fp)
{
	printf("输入数字操作\n1 - 输出试卷列表\n2 - 创建新试卷\n3 - 返回上一级\n4 - 结束程序\n");
	char inpute[40];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {//输出试卷列表
			TestList();
			TestOperate();
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//创建新试卷
			TestCreat();
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {//返回上一级
			printf("正在返回上一级，请等待...\n");
			Sleep(1000);
			system("cls");
			AdminInt();
		}
		else if (inpute[0] == '4'&& inpute[1] == '\0') {//结束程序
			NormalExitProgram();
		}
		else {
			printf("请输入正确的序号:\n");
		}
	}
}
void TestbankNoneInt(FILE * fp)
{
	int n;
	fclose(fp);
	printf("\t          当前系统试卷为空\n\t          是否需要命制一份试卷?\n\n输入序号操作\n1 - 创新新试卷 \n2 - 返回上一级 \n");
	scanf("%d", &n);
	if (n == 1) {
		TestCreat();
	}
	else if (n == 2)
		AdminInt();
}


/*对试卷操作*/
void GetCurrent_testName(char testname[60]) {
	char testprefix[60] = "testbank/";
	strcpy(testname, testprefix);
	strcat(testname,current_test.name);
}
void InitCurrent_test(ST_test *current_test) {
	strcpy(current_test->name, test[testnum - 1].name);
	current_test->num = test[testnum - 1].num;
	for (int i = 0; i < 3; i++) {
		current_test->value[i] = test[testnum - 1].value[i];
	}
}
void TestOperate() {
	printf("输入相应的序号，进行操作：\n");
	scanf("%d", &testnum);//输入要操作的试卷编号
	while (testnum > testamount) {
		printf("不存在该试卷，请重新输入:\n");
		scanf("%d", &testnum);
	}
	InitCurrent_test(&current_test);//初始化当前操作的试卷信息
	printf("\n输入数字操作\n1 - 输出试卷的所有题目\n2 - 删除该试卷\n3 - 返回上一级\n4 - 结束程序\n");
	char inpute[40];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {//输出试卷的所有题目
			TestQuesList();
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//删除试卷
			TestDelete();
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {//返回上一级
			printf("正在返回上一级，请等待...\n");
			Sleep(1000);
			system("cls");
			TestbankInt();
			break;
		}
		else if (inpute[0] == '4'&& inpute[1] == '\0') {//结束程序
			NormalExitProgram();
			break;
		}
		else {
			printf("请输入正确的序号:\n");
		}
	}
}

void TestCreat() {
	FILE *fp;
	printf("请命名试卷的名称:");
	scanf("%s", current_test.name);
	int status;//文件夹路径创建状态
	char strtestfilefoleder[40];
	GetCurrent_testName(strtestfilefoleder);
	status = _mkdir(strtestfilefoleder);
	if (status != 0)
		printf("试卷对应的文件夹创建失败！可能是没有权限或者文件夹冲突。检查当前路径%s是否正确！\n", strtestfilefoleder);
	else {//试卷名称对应的文件夹创建成功
		current_test.num = RandomTestnum();
		printf("该份试卷获取到的唯一编号为：%d\n", current_test.num);
		printf("输入选择题每题的分值：");
		scanf("%d",&current_test.value[0]);
		printf("\n输入填空题每题的分值：");
		scanf("%d", &current_test.value[1]);
		printf("\n输入计算题每题的分值：");
		scanf("%d", &current_test.value[2]);
		printf("\n");
		testnum = 1;
		ChooseQuesSelect();
		BankQuesSelect();
		CalcuQuesSelect();
		if ((fp = fopen("testbank/TestInfoOverview.txt", "a+")) == NULL) {
			printf("打开试卷库信息文件失败。错误路径：testbank/TestInfoOverview.txt\n");
			exit(0);
		}
		fwrite(&current_test, sizeof(ST_test), 1, fp);
		fclose(fp);
		printf("试卷创建成功，是否返回试卷操作界面?\n输入1返回，其他数字退出程序\n");
		int n;
		scanf("%d", &n);
		if (n == 1) {
			TestbankInt();
		}
		else {
			NormalExitProgram();
		}
	}

}

int RandomTestnum() {
	int tmp, num;
	FILE *fp2;
	int list[100], i = 0, testnumamount=0,j;
	if ((fp2 = fopen("testbank/alltestnum.txt", "a+")) == NULL)
		printf("error\n");
	rewind(fp2);//指针归位
	fseek(fp2, 0, 2);
	int fileend;
	fileend = ftell(fp2);//记录文件的尾部
	rewind(fp2);//指针归位
	while (ftell(fp2) != fileend) {//读取所有的题库编号
		fscanf(fp2, "%d\n", &list[i]);
		i++;
		testnumamount++;
	}
	srand((unsigned)time(NULL));//初始化随机种子
	while (1) {
		tmp = rand() % 10;//生成个位上的随机数
		num = tmp;
		tmp = rand() % 10;//生成十位上的随机数
		num = num + tmp * 10;
		tmp = rand() % 10;//生成百分上的随机数
		num = num + tmp * 100;
		for (j = 0; j < testnumamount; j++) {//查找试卷编号是否重复
			if (list[j] == num)
				break;
		}
		if (j >= testnumamount) {
			fprintf(fp2, "%d\n", num);
			fclose(fp2);
			return num;
		}
	}
}
void TestDelete() {
	char testname[60];
	GetCurrent_testName(testname);//获取当前试卷的路径
	char choosequesfilename[60];
	test_GetquestionsfileName(choosequesfilename, 1);//获取该试卷的选择题文件的路径
	char bankquesfilename[60];
	test_GetquestionsfileName(bankquesfilename, 2);//获取该试卷的填空题文件的路径
	char calcufilename[60];
	test_GetquestionsfileName(calcufilename, 3);//获取该试卷的计算题文件的路径
	//Sleep(5000);
	if (remove(choosequesfilename) == 0) {
		printf("该试卷选择题删除完成\n");
	}
	else {
		printf("当前删除文件夹为:%s\n", choosequesfilename);
		//printf("%d", testnum);
		printf("该试卷选择题删除失败，请联系管理员ihewro@163.com\n");
		perror("remove");
		exit(0);
	}
	if (remove(bankquesfilename) == 0) {
		printf("该试卷填空题删除完成\n");
	}
	else {
		printf("当前删除文件夹为：%s", bankquesfilename);
		printf("该试卷填空题删除失败，请联系管理员ihewro@163.com\n");
		exit(0);
	}
	if (remove(calcufilename) == 0) {
		printf("该试卷计算题删除完成\n");
	}
	else {
		printf("当前删除文件夹为：%s", calcufilename);
		printf("该试卷计算题删除失败，请联系管理员ihewro@163.com\n");
		exit(0);
	}
	if (_rmdir(testname) == 0) {
		int i;
		for (i = testnum; i <= testamount - 1; i++) {
			test[i - 1] = test[i];
		}
		FILE *fp;
		ST_test *p;
		if ((fp = fopen("testbank/TestInfoOverview.txt", "w")) == NULL) {//已只写方式打开文件
			printf("打开试卷信息文件失败。错误路径：testbank/TestInfoOverview.txt\n");
			printf("error\n");
			exit(0);
		}
		p = test;
		for (i = 0; i <= testamount - 2; i++, p++) {//把新的试卷信息写入TestInfoOverview.txt中
			fwrite(p, sizeof(ST_test), 1, fp);
		}
		fclose(fp);

		printf("该试卷删除成功，是否返回上一级，输入1返回，输入其他结束程序\n");
	}
	else {
		printf("当前删除文件夹为：%s", testname);
		printf("该试卷删除失败，请联系管理员ihewro@163.com\n");
		exit(0);
	}
	int n;
	scanf("%d", &n);
	if (n == 1) {
		TestbankInt();
	}
	else {
		printf("谢谢你的使用，程序已经退出\n");
		exit(0);
	}
}
int TestList() {
	FILE *fp;
	if ((fp = fopen("testbank/TestInfoOverview.txt", "a+")) == NULL) {
		printf("路径文件 testbank/TestInfoOverview.txt 打开失败，检查是否有权限操作\n");
		printf("error\n");
		return 0;
	}
	else {
		rewind(fp);//指针归位
		fseek(fp, 0, 2);
		int fileend;
		fileend = ftell(fp);//记录文件的尾部
		rewind(fp);//指针归位
		printf("\t**        目前的试卷列表有：\t**        \n\n");
		printf("%-13s%-13s%-13s\n", "序号", "试卷编号", "试卷名称");
		ST_test *p;//最多20份试卷
		p = test;
		int i = 1;

		while (ftell(fp) != fileend) {//判断fp指针是否读取到文件尾部
			fread(p, sizeof(ST_test), 1, fp);
			printf("%-13d%-13d%-13s\n", i++, p->num, p->name);
			p++;
			testamount++;
		}
		printf("\n");
		fclose(fp);
		return 1;
	}
}
void TestQuesList() {
	setjmp(j4);
	test_choosequescount = 0; test_bankquescount = 0; test_calcuquescount = 0;
	printf("\n选择输出该试卷下的相应题型的题目:\n1 - 选择题\n2 - 填空题\n3 - 计算题\n4 - 返回上一级\n5 - 退出程序\n");
	char inpute[40];
	char str[40] = "testbank/";
	strcat(str, test[testnum - 1].name);//字符串连接
	int result;
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {//输出试卷的选择题
			result = test_ChooseQuesList();
			if (result) {
				test_ChooseQuesOperate();
			}
			else {//选择题为空
				printf("输入序号\n1 - 增加试题\n2 - 返回上一级\n3 - 退出程序\n");
				int n;
				scanf("%d", &n);
				if (n == 1) {
					ChooseQuesSelect();
				}
				if (n == 2) {
					TestQuesList();
				}
				if (n == 3) {
					NormalExitProgram();
				}
			}
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//输出试卷的填空题
			result = test_BankQuesList();
			if (result) {
				test_BankQuesOperate();
			}
			else {//填空题为空
				printf("输入序号：1. 增加试题 2. 返回上一级 3.退出程序\n");
				int n;
				scanf("%d", &n);
				if (n == 1) {//添加填空题
					BankQuesSelect();
				}
				if (n == 2) {//返回上一级
					TestQuesList();
				}
				if (n == 3) {//退出程序
					NormalExitProgram();
				}
			}
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {//输出试卷的计算题
			result = test_CalcuQuesList();
			if (result) {
				test_CalcuQuesOperate();
			}
			else {//计算题题为空
				printf("输入序号：1. 增加试题 2. 返回上一级 3.退出程序\n");
				int n;
				scanf("%d", &n);
				if (n == 1) {//添加选择题
					CalcuQuesSelect();
				}
				if (n == 2) {//返回上一级
					TestQuesList();
				}
				if (n == 3) {//退出程序
					NormalExitProgram();
				}
			}
			break;
		}
		else if (inpute[0] == '4'&& inpute[1] == '\0') {//返回上一级
			TestList();
			TestOperate();
			break;
		}
		else if (inpute[0] == '5'&& inpute[1] == '\0') {//退出程序
			NormalExitProgram();
			break;
		}
		else {
			printf("请输入正确的序号:\n");
		}
	}
}


/*对试卷的题目的操作*/
void test_GetquestionsfileName(char quesfilename[60], int n) {
	char testbankprefix[60] = "testbank/";
	char choosequessuffix[60] = "/chooseques.txt";
	char bankquessuffix[60] = "/bankques.txt";
	char calcuquessuffix[60] = "/calcuques.txt";
	if (n == 1) {
		strcpy(quesfilename, testbankprefix);
		strcat(quesfilename, current_test.name);
		strcat(quesfilename, choosequessuffix);
	}
	if (n == 2) {
		strcpy(quesfilename, testbankprefix);
		strcat(quesfilename, current_test.name);
		strcat(quesfilename, bankquessuffix);
	}
	if (n == 3) {
		strcpy(quesfilename, testbankprefix);
		strcat(quesfilename, current_test.name);
		strcat(quesfilename, calcuquessuffix);
	}
}

//选择题
int test_ChooseQuesList() {
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
	if (ftell(fp) == quesfileend) {
		printf("选择题为空！\n");
		fclose(fp);
		return 0;
	}
	else {
		printf("\n\t**        该试卷的选择题列表：\t**        \n\n");
		while (ftell(fp) != quesfileend) {//判断fp指针是否读取到<questions>文件尾部
			fread(p1, sizeof(ChooseQues), 1, fp);
			printf("\t          %d - %s\n", i, p1->ask);
			for (j = 0; j < 4; j++) {
				printf("\t          %c. %s", j + 'A', p1->answer[j]);
				printf("\n");
			}
			printf("\t          %s\n", p1->right);
			i++;
			p1++;
			test_choosequescount++;
		}
		printf("\n");
		fclose(fp);
		return 1;
	}
}
void test_ChooseQuesOperate() {
	printf("输入序号操作\n1 - 增加试题 \n2 - 删除试题 \n3 - 返回上一级\n");
	int n;
	scanf("%d", &n);

	if (n == 1) {
		ChooseQuesSelect();
		//TestbankModify();
	}
	if (n == 2) {
		test_ChooseQuesDelete();
		//TestbankModify();
	}
	if (n == 3) {
		longjmp(j4, 1);
	}

	printf("输入1返回上一级，其他结束程序\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j4, 1);
	}
	else {
		NormalExitProgram();
	}
}

void ChooseQuesSelect() {
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 1);
	if ((fp = fopen(quesfilename, "a+")) == NULL) {
		printf("打开选择题文件失败，错误路径：%s\n", quesfilename);
		printf("error\n");
		exit(0);
	}
	ExambankList();
	printf("\n输入题库序号来添加选择题\n");
	printf("题库的数量为：%d\n", eaxmbankamount);
	int n;
	scanf("%d", &n);
	while (n > eaxmbankamount || n < 1) {
		printf("请输入正确的题库编号:\n");
		scanf("%d", &n);
	}
	exambanknum = n;//赋值给当前操作的试卷编号
	InitCurrent_exambank(&current_exambank);
	ChooseQuesList();
	printf("\n输入选择题的题目编号来添加对应的题目\n每个序号之间用空格隔开,输入-1结束添加\n");
	//int choosequesnum[100];//把添加的编号存储到数组里面
	int i = 0;
	int num;
	ChooseQues q;
	while (1) {
		scanf("%d", &num);
		if (num > choosequescount) {
			printf("输入的题目编号错误！请重新输入，或者输入-1结束添加\n");
		}
		else {//前提是输入的编号是正确的
			  //choosequesnum[i] = num;
			if (num == -1)
				break;
			else {
				q = chooseques[num - 1];
				printf("当前题目的题干为：%s\n", q.ask);
				fwrite(&q, sizeof(ChooseQues), 1, fp);
				i++;
			}
		}
	}
	fclose(fp);
}
void test_ChooseQuesDelete()
{
	printf("输入要删除的题目的序号\n");
	int num;
	scanf("%d", &num);
	while (num > test_choosequescount || num < 1) {
		printf("输入正确的题目编号\n");
		scanf("%d", &num);
	}
	for (int i = num; i < test_choosequescount; i++) {
		test_chooseques[i - 1] = test_chooseques[i];
	}
	test_choosequescount--;
	ChooseQues *p;
	p = test_chooseques;
	char choosequesfilename[60];
	test_GetquestionsfileName(choosequesfilename, 1);//获取该试卷的选择题文件的路径

	FILE *fp;
	if ((fp = fopen(choosequesfilename, "w")) == NULL) {
		printf("打开%s文件失败\n", choosequesfilename);
		exit(0);
	}
	//printf("打开%s文件成功\n", choosequesfilename);
	printf("当前选择题数量为：%d\n", test_choosequescount);
	for (int i = 0; i < test_choosequescount; i++) {
		fwrite(p, sizeof(ChooseQues), 1, fp);
		p++;
	}
	//current_test.QuesNum = current_test.QuesNum - 1;
	fclose(fp);
}

//填空题
int test_BankQuesList(){
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 2);//获取该试卷的填空题文件的路径
	if ((fp = fopen(quesfilename, "r")) == NULL) {
		printf("ERROR？？？\n");
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
		printf("填空题为空！\n");
		fclose(fp);
		return 0;
	}
	else {
		printf("\n\t**        该试卷的填空题列表：\t**        \n\n");
		while (ftell(fp) != quesfileend) {//判断fp指针是否读取到<questions>文件尾部
			fread(p2, sizeof(BankQues), 1, fp);
			printf("\t          %d - %s\n", i, p2->ask);
			printf("\t          %s\n", p2->right);
			i++;
			p2++;
			test_bankquescount++;
		}
		fclose(fp);
		return 1;
	}
}
void test_BankQuesOperate(){
	printf("输入序号操作\n1 - 增加试题\n2 - 删除试题\n3 - 返回上一级\n");
	int n;
	scanf("%d", &n);
	if (n == 1) {
		BankQuesSelect();
		//ExambankModify();
	}
	if (n == 2) {
		test_BankQuesDelete();
		//ExambankModify();
	}
	if (n == 3) {
		longjmp(j4, 1);
	}
	printf("输入1返回上一级，其他结束程序\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j4, 1);
	}
	else {
		printf("谢谢你的使用，程序已经结束\n");
		exit(0);
	}
}

void BankQuesSelect() {
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 2);
	if ((fp = fopen(quesfilename, "a+")) == NULL) {
		printf("打开填空题文件失败，错误路径：%s\n", quesfilename);
		printf("error\n");
		exit(0);
	}
	ExambankList();
	printf("\n输入题库序号来添加填空题\n");
	int n;
	scanf("%d", &n);
	while (n > eaxmbankamount || n < 1) {
		printf("请输入正确的题库编号:\n");
		scanf("%d", &n);
	}
	exambanknum = n;//赋值给当前操作的试卷编号
	InitCurrent_exambank(&current_exambank);
	BankQuesList();
	printf("\n输入填空题的题目编号来添加对应的题目\n每个序号之间用空格隔开,输入-1结束添加\n");
	//int bankquesnum[100];//把添加的编号存储到数组里面
	int i = 0;
	int num;
	BankQues q;
	while (1) {
		scanf("%d", &num);
		if (num > bankquescount) {
			printf("输入的题目编号错误！请重新输入，或者输入-1结束添加\n");
		}
		else {//前提是输入的编号是正确的
			  //bankquesnum[i] = num;
			if (num == -1)
				break;
			else {
				q = bankques[num-1];
				printf("当前题目的题干为：%s\n", q.ask);
				fwrite(&q, sizeof(BankQues), 1, fp);
				i++;
			}
		}
	}
	fclose(fp);
}
void test_BankQuesDelete() {
	printf("输入要删除的题目的序号\n");
	int num;
	scanf("%d", &num);
	while (num > test_bankquescount || num < 1) {
		printf("输入正确的题目编号\n");
		scanf("%d", &num);
	}
	for (int i = num; i < test_bankquescount; i++) {
		test_bankques[i - 1] = test_bankques[i];
	}
	test_bankquescount--;
	BankQues *p;
	p = test_bankques;
	char bankquesfilename[60];
	test_GetquestionsfileName(bankquesfilename, 2);//获取该试卷的计算题文件的路径

	FILE *fp;
	if ((fp = fopen(bankquesfilename, "w")) == NULL) {
		printf("打开%s文件失败\n", bankquesfilename);
		exit(0);
	}
	//printf("打开%s文件成功\n", bankquesfilename);
	for (int i = 0; i < test_bankquescount; i++) {
		fwrite(p, sizeof(BankQues), 1, fp);
		p++;
	}
	//current_exambank.QuesNum = current_exambank.QuesNum - 1;
	fclose(fp);
}

//计算题
int test_CalcuQuesList(){
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
		printf("计算题为空！\n");
		fclose(fp);
		return 0;
	}
	else {
		printf("\n\t**        该试卷的计算题列表：\t**        \n\n");
		while (ftell(fp) != quesfileend) {//判断fp指针是否读取到<questions>文件尾部
			fread(p3, sizeof(CalcuQues), 1, fp);
			printf("\t          %d - %s\n", i, p3->ask);
			printf("\t          %s\n", p3->right);
			i++;
			p3++;
			test_calcuquescount++;
		}
		fclose(fp);
		return 1;
	}
}
void test_CalcuQuesOperate(){
	printf("输入序号操作\n1 - 增加试题\n2 - 删除试题\n3 - 返回上一级\n");
	int n;
	scanf("%d", &n);
	if (n == 1) {
		CalcuQuesSelect();
		//ExambankModify();
	}
	if (n == 2) {
		test_CalcuQuesDelete();
		//ExambankModify();
	}
	if (n == 3) {
		longjmp(j4, 1);
	}
	printf("输入1返回上一级，其他结束程序\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j4, 1);
	}
	else {
		printf("谢谢你的使用，程序已经结束\n");
		exit(0);
	}
}

void CalcuQuesSelect() {
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 3);
	if ((fp = fopen(quesfilename, "a+")) == NULL) {
		printf("打开计算题文件失败，错误路径：%s\n", quesfilename);
		printf("error\n");
		exit(0);
	}
	ExambankList();
	printf("\n输入题库序号来添加计算题\n");
	int n;
	scanf("%d", &n);
	while (n > eaxmbankamount || n < 1) {
		printf("请输入正确的题库编号:\n");
		scanf("%d", &n);
	}
	exambanknum = n;//赋值给当前操作的试卷编号
	InitCurrent_exambank(&current_exambank);
	CalcuQuesList();
	printf("\n输入填空题的题目编号来添加对应的题目\n每个序号之间用空格隔开,输入-1结束添加\n");
	//int bankquesnum[100];//把添加的编号存储到数组里面
	int i = 0;
	int num;
	CalcuQues q;
	while (1) {
		scanf("%d", &num);
		if (num > calcuquescount) {
			printf("输入的题目编号错误！请重新输入，或者输入-1结束添加\n");
		}
		else {//前提是输入的编号是正确的
			  //calcuquesnum[i] = num;
			if (num == -1)
				break;
			else {
				q = calcuques[num-1];
				printf("当前题目的题干为：%s\n", q.ask);
				fwrite(&q, sizeof(CalcuQues), 1, fp);
				i++;
			}
		}
	}
	fclose(fp);
}
void test_CalcuQuesDelete() {
	printf("输入要删除的题目的序号\n");
	int num;
	scanf("%d", &num);
	while (num > test_calcuquescount || num < 1) {
		printf("输入正确的题目编号\n");
		scanf("%d", &num);
	}
	for (int i = num; i < test_calcuquescount; i++) {
		test_calcuques[i - 1] = test_calcuques[i];
	}
	test_calcuquescount--;
	CalcuQues *p;
	p = test_calcuques;
	char calcuquesfilename[60];
	test_GetquestionsfileName(calcuquesfilename, 3);//获取该试卷的计算题文件的路径

	FILE *fp;
	if ((fp = fopen(calcuquesfilename, "w")) == NULL) {
		printf("打开%s文件失败\n", calcuquesfilename);
		exit(0);
	}
	//printf("打开%s文件成功\n", bankquesfilename);
	for (int i = 0; i < test_calcuquescount; i++) {
		fwrite(p, sizeof(CalcuQues), 1, fp);
		p++;
	}
	//current_exambank.QuesNum = current_exambank.QuesNum - 1;
	fclose(fp);
}