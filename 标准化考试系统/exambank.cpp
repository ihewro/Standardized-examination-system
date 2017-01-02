/*删除的一个优化：如果没有文件，就直接跳过删除。先查询有没有该文件*/
/*题目的修改优化，不是重写文件，而是修改文件*/
/*exambank文件夹创建优化，不是一开始创建好，而是如果没有可以自动创建*/
#include "declare.h"
jmp_buf j1;
ST_exambank exambank[20];//从ExamInfoOverview.txt文件中读取题库信息并且存储到该数组中
ST_exambank current_exambank;//当前操作的题库
int exambanknum = -1;//当前操作的题库编号
int eaxmbankamount=0; //题库的数量

ChooseQues chooseques[200];//当前题库的选择题数据存储到该数组中
BankQues bankques[200];//当前题库的填空题数据存储到该数组中
CalcuQues calcuques[200];//当前题库的计算题数据存储到该数组中

int choosequescount = 0;//题库中选择题目的数量
int bankquescount = 0;//题库中填空题目的数量
int calcuquescount = 0;//题库中计算题目的数量

//界面
void ExambankInt() {
	printf("\t**        题库管理系统界面！\t**        \n\n");
	char ch;
	FILE *fp;
	if (_access("exambank", 0)) {
		_mkdir("exambank");
	}
	if ((fp = fopen("exambank/ExamInfoOverview.txt", "a+")) == NULL) {
		printf("路径文件 exambank/ExamInfoOverview.txt 打开失败，检查是否有权限操作\n");
		printf("error\n");
		exit(0);
	}
	ch = fgetc(fp);
	if (ch == EOF) {
		fclose(fp);
		ExambankNoneInt();
	}
	else {
		fclose(fp);
		ExambankHaveInt();
	}
}
void ExambankNoneInt() {
	int n;
	printf("\t          当前系统题库为空\n\t          是否需要创建题库?\n\n输入序号操作\n1 - 创新新题库 \n2 - 返回上一级 \n");
	scanf("%d", &n);
	if (n == 1) {
		ExambankCreat();
	}
	else if(n==2)
		AdminInt();
}
void ExambankHaveInt() {
	printf("输入数字操作\n1 - 输出题库列表\n2 - 创建新题库\n3 - 返回上一级\n4 - 结束程序\n");
	char inpute[200];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {//输出题库列表
			ExambankList();
			ExambankOperate();
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//创建新题库
			ExambankCreat();
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

//对题库的操作
void GetCurrent_exambankName(char exambankname[60]) {
	char exambankprefix[60] = "exambank/";
	strcpy(exambankname, exambankprefix);
	strcat(exambankname,current_exambank.name);
}
void InitCurrent_exambank(ST_exambank *current_exambank) {
	strcpy(current_exambank->name, exambank[exambanknum - 1].name);
	current_exambank->QuesNum = exambank[exambanknum - 1].QuesNum;
}
void ExambankOperate(){
	printf("输入序号操作:\n1 - 操作题库\n2 - 返回上一级\n3 - 结束程序\n");
	char inpute[40];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {
			printf("正在返回上一级，请等待...\n");
			Sleep(1000);
			system("cls");
			ExambankInt();
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {
			NormalExitProgram();
			break;
		}
		else {
			printf("请输入正确的序号！\n");
		}
	}
	printf("输入相应的题库编号，进行题库操作：\n");
	scanf("%d", &exambanknum);//输入要操作的题库编号
	InitCurrent_exambank(&current_exambank);//初始化当前操作的题库信息
	while (exambanknum > eaxmbankamount) {
		printf("不存在该题库，请重新输入:\n");
		scanf("%d", &exambanknum);
	}
	printf("\n输入数字操作\n1 - 输出题库的所有题目\n2 - 删除该题库\n3 - 返回上一级 \n4 - 结束程序 \n");
	int n;
	scanf("%d", &n);
	if (n == 1) {
		 ExmanbankQuesList();
	}
	else if (n == 2) {
		ExambankDelete();
	} 
	else if (n == 3) {
		ExambankOperate();
	}
	else if (n == 4) {
		NormalExitProgram();
	}
}

void ExambankCreat() {
	FILE *fp;
	printf("请输入题库名称:");
	scanf("%s", current_exambank.name);
	current_exambank.QuesNum = 0;
	printf("\n当前题库名称为：%s\n\n", current_exambank.name);
	int status;//文件夹路径创建状态
	char streaxmfilefoleder[40];
	GetCurrent_exambankName(streaxmfilefoleder);
	status = _mkdir(streaxmfilefoleder);
	if (status != 0)
		printf("题库文件夹创建失败！检查当前路径%s是否正确！\n", streaxmfilefoleder);
	else {//题库名称对应的文件夹创建成功
		exambanknum = 1;
		ChooseQuesAdd();
		BankQuesAdd();
		CalcuQuesAdd();

		if ((fp = fopen("exambank/ExamInfoOverview.txt", "a+")) == NULL) {
			printf("打开题库信息文件失败。错误路径：exambank/ExamInfoOverview.txt\n");
			exit(0);
		}
		fwrite(&current_exambank, sizeof(ST_exambank), 1, fp);
		fclose(fp);
		printf("题库创建成功，是否返回题库操作界面?\n输入1返回，其他数字退出程序\n");
		int n;
		scanf("%d", &n);
		if (n == 1) {
			ExambankInt();
		}
		else {
			NormalExitProgram();
		}
	}
}
void ExambankDelete() {
	char exambankname[60];
	GetCurrent_exambankName(exambankname);//获取当前题库的路径
	char choosequesfilename[60];
	GetquestionsfileName(choosequesfilename, 1);//获取该题库的选择题文件的路径
	char bankquesfilename[60];
	GetquestionsfileName(bankquesfilename, 2);//获取该题库的填空题文件的路径
	char calcufilename[60];
	GetquestionsfileName(calcufilename, 3);//获取该题库的计算题文件的路径
	if (remove(choosequesfilename) == 0) {
		printf("该题库选择题删除完成\n");
	}
	else {
		printf("当前删除文件夹为：%s", choosequesfilename);
		printf("该题库选择题删除失败，请联系管理员ihewro@163.com\n");
		exit(0);
	}
	if (remove(bankquesfilename) == 0) {
		printf("该题库填空题删除完成\n");
	}
	else {
		printf("当前删除文件夹为：%s", bankquesfilename);
		printf("该题库填空题删除失败，请联系管理员ihewro@163.com\n");
		exit(0);
	}
	if (remove(calcufilename) == 0) {
		printf("该题库计算题删除完成\n");
	}
	else {
		printf("当前删除文件夹为：%s", calcufilename);
		printf("该题库计算题删除失败，请联系管理员ihewro@163.com\n");
		exit(0);
	}
	if (_rmdir(exambankname) == 0) {
		int i;
		for (i = exambanknum; i <= eaxmbankamount - 1; i++) {
			exambank[i - 1] = exambank[i];
		}
		FILE *fp;
		ST_exambank *p;
		if ((fp = fopen("exambank/ExamInfoOverview.txt", "w")) == NULL) {//已只写方式打开文件
			printf("打开题库信息文件失败。错误路径：exambank/ExamInfoOverview.txt\n");
			printf("error\n");
			exit(0);
		}
		p = exambank;
		for (i = 0; i <= eaxmbankamount - 2; i++, p++) {//把新的题库信息写入ExamInfoOverview.txt中
			fwrite(p, sizeof(ST_exambank), 1, fp);
		}
		fclose(fp);

		printf("该题库删除成功，是否返回上一级，输入1返回，输入其他结束程序\n");
	}
	else {
		printf("当前删除文件夹为：%s", exambankname);
		printf("该题库删除失败，请联系管理员ihewro@163.com\n");
		exit(0);
	}

	int n;
	scanf("%d", &n);
	if (n == 1) {
		ExambankInt();
	}
	else {
		printf("谢谢你的使用，程序已经退出\n");
		exit(0);
	}
}
void ExambankList() {//输出题库列表的同时，初始化题库的所有信息（把题库的信息存储到了exambank[20]数组里面了）
	eaxmbankamount = 0;//初始化为0；
	FILE *fp;
	if ((fp = fopen("exambank/ExamInfoOverview.txt", "a+")) == NULL) {
		printf("路径文件 exambank/ExamInfoOverview.txt 打开失败，检查是否有权限操作\n");
		printf("error\n");
		exit(0);
	}
	rewind(fp);//指针归位
	fseek(fp, 0, 2);
	int fileend;
	fileend = ftell(fp);//记录文件的尾部
	rewind(fp);//指针归位
	printf("\t**        目前的题库列表有：\t**        \n\n");
	printf("%-13s%-13s%-13s\n","序号","题库名称","题目数量");
	ST_exambank *p;//最多20个题库
	p = exambank;
	int i = 1;

	while (ftell(fp) != fileend) {//判断fp指针是否读取到文件尾部
		fread(p, sizeof(ST_exambank), 1, fp);
		printf("%-13d%-13s%-13d\n", i++, p->name, p->QuesNum);
		p++;
		eaxmbankamount++;
	}
	printf("\n");
	fclose(fp);
}
void ExmanbankQuesList()
{
	setjmp(j1);
	choosequescount = 0; bankquescount = 0; calcuquescount = 0;
	printf("\n选择输出[该题库]下的相应题型的题目:\n1 - 选择题\n2 - 填空题\n3 - 计算题\n4 - 返回上一级\n5 - 退出程序\n");
	int n;
	scanf("%d", &n);
	char str[40] = "exambank/";
	strcat(str, exambank[exambanknum - 1].name);//字符串连接
	int result;
	if (n == 1) {//输出选择题
		result= ChooseQuesList();
		if (result) {
			ChooseQuesOperate();
		}
		else {//选择题为空
			printf("输入序号\n1 - 增加试题\n2 - 返回上一级\n3 - 退出程序\n");
			int n;
			scanf("%d", &n);
			if (n == 1) {
				ChooseQuesAdd();
				ExambankModify();
			}
			if (n == 2) {
				ExmanbankQuesList();
			}
			if (n == 3) {
				NormalExitProgram();
			}
		}
	}
	else if (n == 2) {//输出填空题
		result=BankQuesList();
		if (result) {
			BankQuesOperate();
		}
		else {//填空题为空
			printf("输入序号：\n1 - 增加试题\n2 - 返回上一级\n3 - 退出程序\n");
			int n;
			scanf("%d", &n);
			if (n == 1) {
				BankQuesAdd();
				ExambankModify();
			}
			if (n == 2) {
				ExmanbankQuesList();
			}
			if (n == 3) {
				NormalExitProgram();
			}
		}
	}
	else if (n == 3) {//输出计算题
		result= CalcuQuesList();
		if (result) {
			CalcuQuesOperate();
		}
		else {//计算题题为空
			printf("输入序号：1. 增加试题 2. 返回上一级 3.退出程序\n");
			int n;
			scanf("%d", &n);
			if (n == 1) {
				CalcuQuesAdd();
				ExambankModify();
			}
			if (n == 2) {
				ExmanbankQuesList();
			}
			if (n == 3) {
				NormalExitProgram();
			}
		}
	}
	else if (n == 4) {//返回上一级
		ExambankOperate();
	}
	else if (n == 5) {//结束程序
		NormalExitProgram();
	}
	printf("输入1返回上一级，其他结束程序\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j1, 1);
	}
	else {
		printf("谢谢你的使用，程序已经结束\n");
		exit(0);
	}
}
void ExambankModify() {
	FILE *fp;
	if ((fp = fopen("exambank/ExamInfoOverview.txt", "r+")) == NULL) {
		printf("打开题库信息文件失败。错误路径：exambank/ExamInfoOverview.txt\n");
		printf("error\n");
		exit(0);
	}
	rewind(fp);
	fseek(fp,(exambanknum-1)*sizeof(ST_exambank), 0);//把文件指针移到要修改的题库地方
	ST_exambank *p;
	p = &current_exambank;
	fwrite(p, sizeof(ST_exambank),1,fp);//重写要修改的题库信息
	fclose(fp);
}



//对题目的操作

void GetquestionsfileName(char quesfilename[60],int n) {
	char exambankprefix[60] = "exambank/";
	char choosequessuffix[60] = "/chooseques.txt";
	char bankquessuffix[60] = "/bankques.txt";
	char calcuquessuffix[60] = "/calcuques.txt";
	if (n == 1) {
		strcpy(quesfilename, exambankprefix);
		strcat(quesfilename, current_exambank.name);
		strcat(quesfilename, choosequessuffix);
	}
	if (n == 2) {
		strcpy(quesfilename, exambankprefix);
		strcat(quesfilename, current_exambank.name);
		strcat(quesfilename, bankquessuffix);
	}
	if (n == 3) {
		strcpy(quesfilename, exambankprefix);
		strcat(quesfilename, current_exambank.name);
		strcat(quesfilename, calcuquessuffix);
	}
}

/*选择题*/
int ChooseQuesList() {
	FILE *fp;
	char choosequesfilename[60];
	GetquestionsfileName(choosequesfilename,1);//获取该题库的选择题文件的路径
	if ((fp = fopen(choosequesfilename, "r")) == NULL) {
		printf("ERROR\n");
		printf("错误路径：%s\n", choosequesfilename);
		exit(0);
	}
	ChooseQues *q1;
	q1 = chooseques;
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
		printf("\n\t**        该题库的选择题列表：\t**        \n\n");
		while (ftell(fp) != quesfileend) {//判断fp指针是否读取到<questions>文件尾部
			fread(q1, sizeof(ChooseQues), 1, fp);
			printf("\t          %d - %s\n", i, q1->ask);
			for (j = 0; j < 4; j++) {
				printf("\t          %c. %s", j + 'A', q1->answer[j]);
				printf("\n");
			}
			printf("\t          %s\n", q1->right);
			i++;
			q1++;
			choosequescount++;
		}
		printf("\n");
		fclose(fp);
		return 1;
	}
}
void ChooseQuesOperate() {
	printf("输入序号操作\n1 - 修改试题\n2 - 增加试题 \n3 - 删除试题 \n4 - 返回上一级\n");
	int n;
	scanf("%d", &n);

	if (n == 1) {
		ChooseQuesModify();
		
	}
	if (n == 2) {
		ChooseQuesAdd();
		ExambankModify();
	}
	if (n == 3) {
		ChooseQuesDelete();
		ExambankModify();
	}
	if (n == 4) {
		longjmp(j1, 1);
	}

	printf("输入1返回上一级，其他结束程序\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j1, 1);
	}
	else {
		printf("谢谢你的使用，程序已经结束\n");
		exit(0);
	}
}

void ChooseQuesAdd() {
	int n1;
	printf("请输入<选择题>的题目数量(输入0则不输入该类型题目)：");
	scanf("%d", &n1);
	FILE *fp;
	char choosequesfilename[60];
	GetquestionsfileName(choosequesfilename, 1);//获取该题库的选择题文件的路径
	if ((fp = fopen(choosequesfilename, "a+")) == NULL) {
		printf("打开选择题文件失败，错误路径：%s\n", choosequesfilename);
		printf("error\n");
		exit(0);
	}
	//printf("打开选择题文件成功，路径：%s\n", choosequesfilename);
	for (int i = 0; i < n1; i++) {
		ChooseQues ques;
		printf("输入第%d道选择题的题干:\n", i + 1);
		getchar();//接收上面的\n
		gets_s(ques.ask,200);
		int j = 0;
		while (j < 4)
		{
			printf("请输入选项%c的答案:\n", j + 'A');
			gets_s(ques.answer[j++],200);
		}
		printf("请输入正确的答案:");
		char inpute[200];
		gets_s(inpute,200);
		while (inpute[0] < 'A' || inpute[0] > 'D'||inpute[1] != '\0')
		{
			printf("您输入的答案不合法！请输入正确的答案:");
			gets_s(inpute);
		}
		strcpy(ques.right, inpute);
		fwrite(&ques, sizeof(ChooseQues), 1, fp);
	}
	current_exambank.QuesNum = current_exambank.QuesNum + n1;
	fclose(fp);
	/*选择题结束!!!*/
}
void ChooseQuesModify()
{
	//printf("选择题数目为：%d\n", choosequescount);
	printf("输入试题序号：\n");
	int num;
	scanf("%d", &num);
	while (num > choosequescount || num < 1) {
		printf("输入正确的题目编号\n");
		scanf("%d", &num);
	}
	char judge[4] = "no";
	char input[200];
	printf("输入该道选择题题干(输入no，则不修改此项):\n");
	getchar();//接收上面的\n
	gets_s(input, 200);
	if (strcmp(input, judge) != 0) {
		strcpy(chooseques[num - 1].ask, input);
	}
	printf("输入该道选择题的选项：\n");
	int j = 0;
	while (j < 4)
	{
		printf("请输入选项%c的答案(输入no，则不修改此项):\n", j + 'A');
		//getchar();//接收上面的\n
		gets_s(input, 200);
		if (strcmp(input, judge) != 0) {
			strcpy(chooseques[num - 1].answer[j], input);
		}
		j++;
	}
	printf("请输入正确的答案(输入no，则不修改此项): ");
	gets_s(input, 200);
	if (strcmp(input,judge)!=0) {
		while (input[0] < 'A' || input[0] > 'D' || input[1] != '\0')
		{
			printf("您输入的答案不合法！请输入正确的答案:");
			gets_s(input, 200);
		}
		strcpy(chooseques[num - 1].right, input);
	}

	ChooseQues *p;
	p = chooseques;
	char choosequesfilename[60];
	GetquestionsfileName(choosequesfilename, 1);//获取该题库的选择题文件的路径

	FILE *fp;
	if ((fp = fopen(choosequesfilename, "w")) == NULL) {
		printf("打开%s文件失败\n", choosequesfilename);
		exit(0);
	}
	//printf("打开%s文件成功\n", choosequesfilename);
	for (int i=0; i < choosequescount; i++) {
		fwrite(p, sizeof(ChooseQues), 1, fp);
		p++;
	}
	fclose(fp);
}
void ChooseQuesDelete()
{
	printf("输入要删除的题目的序号\n");
	int num;
	scanf("%d", &num);
	while (num > choosequescount || num < 1) {
		printf("输入正确的题目编号\n");
		scanf("%d", &num);
	}
	for (int i = num; i < choosequescount; i++) {
		chooseques[i-1] = chooseques[i];
	}
	choosequescount--;
	ChooseQues *p;
	p = chooseques;
	char choosequesfilename[60];
	GetquestionsfileName(choosequesfilename, 1);//获取该题库的选择题文件的路径

	FILE *fp;
	if ((fp = fopen(choosequesfilename, "w")) == NULL) {
		printf("打开%s文件失败\n", choosequesfilename);
		exit(0);
	}
	//printf("打开%s文件成功\n", choosequesfilename);
	for (int i = 0; i < choosequescount; i++) {
		fwrite(p, sizeof(ChooseQues), 1, fp);
		p++;
	}
	current_exambank.QuesNum = current_exambank.QuesNum - 1;
	fclose(fp);
}

/*填空题*/
int BankQuesList() {
	FILE *fp;
	char bankquesfilename[60];
	GetquestionsfileName(bankquesfilename, 2);//获取该题库的填空题文件的路径
	if ((fp = fopen(bankquesfilename, "r")) == NULL) {
		printf("ERROR\n");
		printf("错误路径：%s\n", bankquesfilename);
		exit(0);
	}
	BankQues *q2;
	q2 = bankques;
	rewind(fp);//指针归位
	fseek(fp, 0, 2);
	int quesfileend;
	quesfileend = ftell(fp);//记录<questions>文件的尾部
	rewind(fp);//指针归位
	int i = 1;//输出编号
	if (ftell(fp) == quesfileend) {
		printf("填空题为空！\n");
		fclose(fp);
		return 0;
	}
	else {
		printf("\n\t**        该题库的填空题列表：\t**        \n\n");
		while (ftell(fp) != quesfileend) {//判断fp指针是否读取到<questions>文件尾部
			fread(q2, sizeof(BankQues), 1, fp);
			printf("\t          %d - %s\n", i, q2->ask);
			printf("\t          %s\n", q2->right);
			i++;
			q2++;
			bankquescount++;
		}
		fclose(fp);
		return 1;
	}
}
void BankQuesOperate() {
	printf("输入序号操作\n1 - 修改试题\n2 - 增加试题\n3 - 删除试题\n4 - 返回上一级\n");
	int n;
	scanf("%d", &n);
	if (n == 1) {
		BankQuesModify();
	}
	if (n == 2) {
		BankQuesAdd();
		ExambankModify();
	}
	if (n == 3) {
		BankQuesDelete();
		ExambankModify();
	}
	if (n == 4) {
		longjmp(j1, 1);
	}
	printf("输入1返回上一级，其他结束程序\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j1, 1);
	}
	else {
		printf("谢谢你的使用，程序已经结束\n");
		exit(0);
	}
}

void BankQuesAdd() {
	/*填空题开始*/
	int n2;
	printf("请输入<填空题>的题目数量(输入0则不输入该类型题目)：");
	scanf("%d", &n2);
	FILE *fp;
	char bankquesfilename[60];
	GetquestionsfileName(bankquesfilename, 2);//获取该题库的填空题文件的路径
	if ((fp = fopen(bankquesfilename, "a+")) == NULL) {
		printf("error\n");
		exit(0);
	}
	for (int i = 0; i < n2; i++) {
		BankQues ques;
		printf("输入%d道填空题的题干：\n", i + 1);
		getchar();//接收上面的\n
		gets_s(ques.ask, 200);
		printf("请输入正确的答案: ");
		gets_s(ques.right, 200);
		fwrite(&ques, sizeof(BankQues), 1, fp);
	}
	current_exambank.QuesNum = current_exambank.QuesNum + n2;
	fclose(fp);
	/*填空题结束!!!*/
}
void BankQuesModify()
{
	printf("输入需要修改的试题序号：\n");
	int num;
	scanf("%d", &num);
	while (num > bankquescount || num < 1) {
		printf("输入正确的题目编号\n");
		scanf("%d", &num);
	}
	char judge[4] = "no";
	char input[200];
	printf("输入该填空题的题干(输入no，则不修改此项)：\n");
	getchar();//接收上面的\n
	gets_s(input, 200);
	if (strcmp(input, judge) != 0) {
		strcpy(bankques[num - 1].ask, input);
	}
	printf("请输入该填空题的答案(输入no，则不修改此项):\n");
	//getchar();//接收上面的\n
	gets_s(input, 200);
	if (strcmp(input, judge) != 0) {
		strcpy(bankques[num - 1].right, input);
	}
	BankQues *p;
	p = bankques;
	char bankquesfilename[60];
	GetquestionsfileName(bankquesfilename, 2);//获取该题库的填空题的文件的路径

	FILE *fp;
	if ((fp = fopen(bankquesfilename, "w")) == NULL) {
		printf("打开%s文件失败\n", bankquesfilename);
		exit(0);
	}
	//printf("打开%s文件成功\n", bankquesfilename);
	for (int i = 0; i < bankquescount; i++) {
		fwrite(p, sizeof(BankQues), 1, fp);
		p++;
	}
	fclose(fp);
}
void BankQuesDelete()
{
	printf("输入要删除的题目的序号\n");
	int num;
	scanf("%d", &num);
	while (num > bankquescount || num < 1) {
		printf("输入正确的题目编号\n");
		scanf("%d", &num);
	}
	for (int i = num; i < bankquescount; i++) {
		bankques[i - 1] = bankques[i];
	}
	bankquescount--;
	BankQues *p;
	p = bankques;
	char bankquesfilename[60];
	GetquestionsfileName(bankquesfilename, 2);//获取该题库的计算题文件的路径

	FILE *fp;
	if ((fp = fopen(bankquesfilename, "w")) == NULL) {
		printf("打开%s文件失败\n", bankquesfilename);
		exit(0);
	}
	//printf("打开%s文件成功\n", bankquesfilename);
	for (int i = 0; i < bankquescount; i++) {
		fwrite(p, sizeof(BankQues), 1, fp);
		p++;
	}
	current_exambank.QuesNum = current_exambank.QuesNum - 1;
	fclose(fp);
}

/*计算题*/
int CalcuQuesList() {
	FILE *fp;
	char calcufilename[60];
	GetquestionsfileName(calcufilename, 3);//获取该题库的计算题文件的路径
	if ((fp = fopen(calcufilename, "r")) == NULL) {
		printf("ERROR\n");
		printf("错误路径：%s\n", calcufilename);
		exit(0);
	}
	CalcuQues *q3;
	q3 = calcuques;
	rewind(fp);//指针归位
	fseek(fp, 0, 2);
	int quesfileend;
	quesfileend = ftell(fp);//记录<questions>文件的尾部
	rewind(fp);//指针归位
	int i = 1;//输出编号
	if (ftell(fp) == quesfileend) {
		printf("计算题题库为空！\n");
		fclose(fp);
		return 0;
	}
	else {
		printf("\n\t**        该题库的计算题列表：\t**        \n\n");
		while (ftell(fp) != quesfileend) {//判断fp指针是否读取到<questions>文件尾部
			fread(q3, sizeof(CalcuQues), 1, fp);
			printf("\t          %d - %s\n", i, q3->ask);
			printf("\t          %s\n", q3->right);
			i++;
			q3++;
			calcuquescount++;
		}
		fclose(fp);
		return 1;
	}
}
void CalcuQuesOperate() {
	printf("输入序号操作\n1 - 修改试题\n2 - 增加试题\n3 - 删除试题\n4 - 返回上一级\n");
	int n;
	scanf("%d", &n);
	if (n == 1) {
		CalcuQuesModify();
	}
	if (n == 2) {
		CalcuQuesAdd();
		ExambankModify();
	}
	if (n == 3) {
		CalcuQuesDelete();
		ExambankModify();
	}
	if (n == 4) {
		longjmp(j1, 1);
	}
	printf("输入1返回上一级，其他结束程序\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j1, 1);
	}
	else {
		printf("谢谢你的使用，程序已经结束\n");
		exit(0);
	}
}

void CalcuQuesAdd() {
	/*计算题开始*/
	//printf("进入到计算题界面\n");
	int n3;
	printf("请输入<填计算题>的题目数量(输入0则不输入该类型题目)：");
	scanf("%d", &n3);
	FILE *fp;
	char calcufilename[60];
	GetquestionsfileName(calcufilename, 3);//获取该题库的填空题文件的路径
	if ((fp = fopen(calcufilename, "a+")) == NULL) {
		printf("error\n");
		exit(0);
	}
	for (int i = 0; i < n3; i++) {
		CalcuQues ques;
		printf("输入%d道计算题的题干：\n", i + 1);
		getchar();//接收上面的\n
		gets_s(ques.ask, 200);
		printf("请输入正确的答案: ");
		gets_s(ques.right, 200);
		fwrite(&ques, sizeof(CalcuQues), 1, fp);
	}
	current_exambank.QuesNum = current_exambank.QuesNum + n3;
	fclose(fp);
	/*计算题结束!!!*/
}
void CalcuQuesModify()
{
	printf("输入需要修改的试题序号：\n");
	int num;
	scanf("%d", &num);
	while (num > calcuquescount || num < 1) {
		printf("输入正确的题目编号\n");
		scanf("%d", &num);
	}
	char judge[4] = "no";
	char input[200];
	printf("输入该计算题的题干(输入no，则不修改此项)：\n");
	getchar();//接收上面的\n
	gets_s(input, 200);
	if (strcmp(input, judge) != 0) {
		strcpy(calcuques[num - 1].ask, input);
	}
	printf("请输入该计算题的答案(输入no，则不修改此项):\n");
	//getchar();//接收上面的\n
	gets_s(input, 200);
	if (strcmp(input, judge) != 0) {
		strcpy(calcuques[num - 1].right, input);
	}
	CalcuQues *p;
	p = calcuques;
	char calcuquesfilename[60];
	GetquestionsfileName(calcuquesfilename, 3);//获取该题库的计算题的文件的路径

	FILE *fp;
	if ((fp = fopen(calcuquesfilename, "w")) == NULL) {
		printf("打开%s文件失败\n", calcuquesfilename);
		exit(0);
	}
	//printf("打开%s文件成功\n", calcuquesfilename);
	for (int i = 0; i < calcuquescount; i++) {
		fwrite(p, sizeof(CalcuQues), 1, fp);
		p++;
	}
	fclose(fp);
}
void CalcuQuesDelete()
{
	printf("输入要删除的题目的序号\n");
	int num;
	scanf("%d", &num);
	while (num > calcuquescount || num < 1) {
		printf("输入正确的题目编号\n");
		scanf("%d", &num);
	}
	for (int i = num; i < calcuquescount; i++) {
		calcuques[i - 1] = calcuques[i];
	}
	calcuquescount--;
	CalcuQues *p;
	p = calcuques;
	char calcuquesfilename[60];
	GetquestionsfileName(calcuquesfilename, 3);//获取该题库的计算题文件的路径

	FILE *fp;
	if ((fp = fopen(calcuquesfilename, "w")) == NULL) {
		printf("打开%s文件失败\n", calcuquesfilename);
		exit(0);
	}
	//printf("打开%s文件成功\n", calcuquesfilename);
	for (int i = 0; i < calcuquescount; i++) {
		fwrite(p, sizeof(CalcuQues), 1, fp);
		p++;
	}
	current_exambank.QuesNum = current_exambank.QuesNum - 1;
	fclose(fp);
}