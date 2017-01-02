/*ɾ����һ���Ż������û���ļ�����ֱ������ɾ�����Ȳ�ѯ��û�и��ļ�*/
/*��Ŀ���޸��Ż���������д�ļ��������޸��ļ�*/
/*exambank�ļ��д����Ż�������һ��ʼ�����ã��������û�п����Զ�����*/
#include "declare.h"
jmp_buf j1;
ST_exambank exambank[20];//��ExamInfoOverview.txt�ļ��ж�ȡ�����Ϣ���Ҵ洢����������
ST_exambank current_exambank;//��ǰ���������
int exambanknum = -1;//��ǰ�����������
int eaxmbankamount=0; //��������

ChooseQues chooseques[200];//��ǰ����ѡ�������ݴ洢����������
BankQues bankques[200];//��ǰ������������ݴ洢����������
CalcuQues calcuques[200];//��ǰ���ļ��������ݴ洢����������

int choosequescount = 0;//�����ѡ����Ŀ������
int bankquescount = 0;//����������Ŀ������
int calcuquescount = 0;//����м�����Ŀ������

//����
void ExambankInt() {
	printf("\t**        ������ϵͳ���棡\t**        \n\n");
	char ch;
	FILE *fp;
	if (_access("exambank", 0)) {
		_mkdir("exambank");
	}
	if ((fp = fopen("exambank/ExamInfoOverview.txt", "a+")) == NULL) {
		printf("·���ļ� exambank/ExamInfoOverview.txt ��ʧ�ܣ�����Ƿ���Ȩ�޲���\n");
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
	printf("\t          ��ǰϵͳ���Ϊ��\n\t          �Ƿ���Ҫ�������?\n\n������Ų���\n1 - ��������� \n2 - ������һ�� \n");
	scanf("%d", &n);
	if (n == 1) {
		ExambankCreat();
	}
	else if(n==2)
		AdminInt();
}
void ExambankHaveInt() {
	printf("�������ֲ���\n1 - �������б�\n2 - ���������\n3 - ������һ��\n4 - ��������\n");
	char inpute[200];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {//�������б�
			ExambankList();
			ExambankOperate();
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//���������
			ExambankCreat();
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {
			printf("���ڷ�����һ������ȴ�...\n");
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
			printf("��������ȷ����ţ�\n");
		}
	}
}

//�����Ĳ���
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
	printf("������Ų���:\n1 - �������\n2 - ������һ��\n3 - ��������\n");
	char inpute[40];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {
			printf("���ڷ�����һ������ȴ�...\n");
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
			printf("��������ȷ����ţ�\n");
		}
	}
	printf("������Ӧ������ţ�������������\n");
	scanf("%d", &exambanknum);//����Ҫ�����������
	InitCurrent_exambank(&current_exambank);//��ʼ����ǰ�����������Ϣ
	while (exambanknum > eaxmbankamount) {
		printf("�����ڸ���⣬����������:\n");
		scanf("%d", &exambanknum);
	}
	printf("\n�������ֲ���\n1 - �������������Ŀ\n2 - ɾ�������\n3 - ������һ�� \n4 - �������� \n");
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
	printf("�������������:");
	scanf("%s", current_exambank.name);
	current_exambank.QuesNum = 0;
	printf("\n��ǰ�������Ϊ��%s\n\n", current_exambank.name);
	int status;//�ļ���·������״̬
	char streaxmfilefoleder[40];
	GetCurrent_exambankName(streaxmfilefoleder);
	status = _mkdir(streaxmfilefoleder);
	if (status != 0)
		printf("����ļ��д���ʧ�ܣ���鵱ǰ·��%s�Ƿ���ȷ��\n", streaxmfilefoleder);
	else {//������ƶ�Ӧ���ļ��д����ɹ�
		exambanknum = 1;
		ChooseQuesAdd();
		BankQuesAdd();
		CalcuQuesAdd();

		if ((fp = fopen("exambank/ExamInfoOverview.txt", "a+")) == NULL) {
			printf("�������Ϣ�ļ�ʧ�ܡ�����·����exambank/ExamInfoOverview.txt\n");
			exit(0);
		}
		fwrite(&current_exambank, sizeof(ST_exambank), 1, fp);
		fclose(fp);
		printf("��ⴴ���ɹ����Ƿ񷵻�����������?\n����1���أ����������˳�����\n");
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
	GetCurrent_exambankName(exambankname);//��ȡ��ǰ����·��
	char choosequesfilename[60];
	GetquestionsfileName(choosequesfilename, 1);//��ȡ������ѡ�����ļ���·��
	char bankquesfilename[60];
	GetquestionsfileName(bankquesfilename, 2);//��ȡ������������ļ���·��
	char calcufilename[60];
	GetquestionsfileName(calcufilename, 3);//��ȡ�����ļ������ļ���·��
	if (remove(choosequesfilename) == 0) {
		printf("�����ѡ����ɾ�����\n");
	}
	else {
		printf("��ǰɾ���ļ���Ϊ��%s", choosequesfilename);
		printf("�����ѡ����ɾ��ʧ�ܣ�����ϵ����Աihewro@163.com\n");
		exit(0);
	}
	if (remove(bankquesfilename) == 0) {
		printf("����������ɾ�����\n");
	}
	else {
		printf("��ǰɾ���ļ���Ϊ��%s", bankquesfilename);
		printf("����������ɾ��ʧ�ܣ�����ϵ����Աihewro@163.com\n");
		exit(0);
	}
	if (remove(calcufilename) == 0) {
		printf("����������ɾ�����\n");
	}
	else {
		printf("��ǰɾ���ļ���Ϊ��%s", calcufilename);
		printf("����������ɾ��ʧ�ܣ�����ϵ����Աihewro@163.com\n");
		exit(0);
	}
	if (_rmdir(exambankname) == 0) {
		int i;
		for (i = exambanknum; i <= eaxmbankamount - 1; i++) {
			exambank[i - 1] = exambank[i];
		}
		FILE *fp;
		ST_exambank *p;
		if ((fp = fopen("exambank/ExamInfoOverview.txt", "w")) == NULL) {//��ֻд��ʽ���ļ�
			printf("�������Ϣ�ļ�ʧ�ܡ�����·����exambank/ExamInfoOverview.txt\n");
			printf("error\n");
			exit(0);
		}
		p = exambank;
		for (i = 0; i <= eaxmbankamount - 2; i++, p++) {//���µ������Ϣд��ExamInfoOverview.txt��
			fwrite(p, sizeof(ST_exambank), 1, fp);
		}
		fclose(fp);

		printf("�����ɾ���ɹ����Ƿ񷵻���һ��������1���أ�����������������\n");
	}
	else {
		printf("��ǰɾ���ļ���Ϊ��%s", exambankname);
		printf("�����ɾ��ʧ�ܣ�����ϵ����Աihewro@163.com\n");
		exit(0);
	}

	int n;
	scanf("%d", &n);
	if (n == 1) {
		ExambankInt();
	}
	else {
		printf("лл���ʹ�ã������Ѿ��˳�\n");
		exit(0);
	}
}
void ExambankList() {//�������б��ͬʱ����ʼ������������Ϣ����������Ϣ�洢����exambank[20]���������ˣ�
	eaxmbankamount = 0;//��ʼ��Ϊ0��
	FILE *fp;
	if ((fp = fopen("exambank/ExamInfoOverview.txt", "a+")) == NULL) {
		printf("·���ļ� exambank/ExamInfoOverview.txt ��ʧ�ܣ�����Ƿ���Ȩ�޲���\n");
		printf("error\n");
		exit(0);
	}
	rewind(fp);//ָ���λ
	fseek(fp, 0, 2);
	int fileend;
	fileend = ftell(fp);//��¼�ļ���β��
	rewind(fp);//ָ���λ
	printf("\t**        Ŀǰ������б��У�\t**        \n\n");
	printf("%-13s%-13s%-13s\n","���","�������","��Ŀ����");
	ST_exambank *p;//���20�����
	p = exambank;
	int i = 1;

	while (ftell(fp) != fileend) {//�ж�fpָ���Ƿ��ȡ���ļ�β��
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
	printf("\nѡ�����[�����]�µ���Ӧ���͵���Ŀ:\n1 - ѡ����\n2 - �����\n3 - ������\n4 - ������һ��\n5 - �˳�����\n");
	int n;
	scanf("%d", &n);
	char str[40] = "exambank/";
	strcat(str, exambank[exambanknum - 1].name);//�ַ�������
	int result;
	if (n == 1) {//���ѡ����
		result= ChooseQuesList();
		if (result) {
			ChooseQuesOperate();
		}
		else {//ѡ����Ϊ��
			printf("�������\n1 - ��������\n2 - ������һ��\n3 - �˳�����\n");
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
	else if (n == 2) {//��������
		result=BankQuesList();
		if (result) {
			BankQuesOperate();
		}
		else {//�����Ϊ��
			printf("������ţ�\n1 - ��������\n2 - ������һ��\n3 - �˳�����\n");
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
	else if (n == 3) {//���������
		result= CalcuQuesList();
		if (result) {
			CalcuQuesOperate();
		}
		else {//��������Ϊ��
			printf("������ţ�1. �������� 2. ������һ�� 3.�˳�����\n");
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
	else if (n == 4) {//������һ��
		ExambankOperate();
	}
	else if (n == 5) {//��������
		NormalExitProgram();
	}
	printf("����1������һ����������������\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j1, 1);
	}
	else {
		printf("лл���ʹ�ã������Ѿ�����\n");
		exit(0);
	}
}
void ExambankModify() {
	FILE *fp;
	if ((fp = fopen("exambank/ExamInfoOverview.txt", "r+")) == NULL) {
		printf("�������Ϣ�ļ�ʧ�ܡ�����·����exambank/ExamInfoOverview.txt\n");
		printf("error\n");
		exit(0);
	}
	rewind(fp);
	fseek(fp,(exambanknum-1)*sizeof(ST_exambank), 0);//���ļ�ָ���Ƶ�Ҫ�޸ĵ����ط�
	ST_exambank *p;
	p = &current_exambank;
	fwrite(p, sizeof(ST_exambank),1,fp);//��дҪ�޸ĵ������Ϣ
	fclose(fp);
}



//����Ŀ�Ĳ���

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

/*ѡ����*/
int ChooseQuesList() {
	FILE *fp;
	char choosequesfilename[60];
	GetquestionsfileName(choosequesfilename,1);//��ȡ������ѡ�����ļ���·��
	if ((fp = fopen(choosequesfilename, "r")) == NULL) {
		printf("ERROR\n");
		printf("����·����%s\n", choosequesfilename);
		exit(0);
	}
	ChooseQues *q1;
	q1 = chooseques;
	rewind(fp);//ָ���λ
	fseek(fp, 0, 2);
	int quesfileend;
	quesfileend = ftell(fp);//��¼<questions>�ļ���β��
	rewind(fp);//ָ���λ
	int i;
	i = 1;//������
	int j;//ѡ�����ѡ��
	if (ftell(fp) == quesfileend) {
		printf("ѡ����Ϊ�գ�\n");
		fclose(fp);
		return 0;
	}
	else {
		printf("\n\t**        ������ѡ�����б�\t**        \n\n");
		while (ftell(fp) != quesfileend) {//�ж�fpָ���Ƿ��ȡ��<questions>�ļ�β��
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
	printf("������Ų���\n1 - �޸�����\n2 - �������� \n3 - ɾ������ \n4 - ������һ��\n");
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

	printf("����1������һ����������������\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j1, 1);
	}
	else {
		printf("лл���ʹ�ã������Ѿ�����\n");
		exit(0);
	}
}

void ChooseQuesAdd() {
	int n1;
	printf("������<ѡ����>����Ŀ����(����0�������������Ŀ)��");
	scanf("%d", &n1);
	FILE *fp;
	char choosequesfilename[60];
	GetquestionsfileName(choosequesfilename, 1);//��ȡ������ѡ�����ļ���·��
	if ((fp = fopen(choosequesfilename, "a+")) == NULL) {
		printf("��ѡ�����ļ�ʧ�ܣ�����·����%s\n", choosequesfilename);
		printf("error\n");
		exit(0);
	}
	//printf("��ѡ�����ļ��ɹ���·����%s\n", choosequesfilename);
	for (int i = 0; i < n1; i++) {
		ChooseQues ques;
		printf("�����%d��ѡ��������:\n", i + 1);
		getchar();//���������\n
		gets_s(ques.ask,200);
		int j = 0;
		while (j < 4)
		{
			printf("������ѡ��%c�Ĵ�:\n", j + 'A');
			gets_s(ques.answer[j++],200);
		}
		printf("��������ȷ�Ĵ�:");
		char inpute[200];
		gets_s(inpute,200);
		while (inpute[0] < 'A' || inpute[0] > 'D'||inpute[1] != '\0')
		{
			printf("������Ĵ𰸲��Ϸ�����������ȷ�Ĵ�:");
			gets_s(inpute);
		}
		strcpy(ques.right, inpute);
		fwrite(&ques, sizeof(ChooseQues), 1, fp);
	}
	current_exambank.QuesNum = current_exambank.QuesNum + n1;
	fclose(fp);
	/*ѡ�������!!!*/
}
void ChooseQuesModify()
{
	//printf("ѡ������ĿΪ��%d\n", choosequescount);
	printf("����������ţ�\n");
	int num;
	scanf("%d", &num);
	while (num > choosequescount || num < 1) {
		printf("������ȷ����Ŀ���\n");
		scanf("%d", &num);
	}
	char judge[4] = "no";
	char input[200];
	printf("����õ�ѡ�������(����no�����޸Ĵ���):\n");
	getchar();//���������\n
	gets_s(input, 200);
	if (strcmp(input, judge) != 0) {
		strcpy(chooseques[num - 1].ask, input);
	}
	printf("����õ�ѡ�����ѡ�\n");
	int j = 0;
	while (j < 4)
	{
		printf("������ѡ��%c�Ĵ�(����no�����޸Ĵ���):\n", j + 'A');
		//getchar();//���������\n
		gets_s(input, 200);
		if (strcmp(input, judge) != 0) {
			strcpy(chooseques[num - 1].answer[j], input);
		}
		j++;
	}
	printf("��������ȷ�Ĵ�(����no�����޸Ĵ���): ");
	gets_s(input, 200);
	if (strcmp(input,judge)!=0) {
		while (input[0] < 'A' || input[0] > 'D' || input[1] != '\0')
		{
			printf("������Ĵ𰸲��Ϸ�����������ȷ�Ĵ�:");
			gets_s(input, 200);
		}
		strcpy(chooseques[num - 1].right, input);
	}

	ChooseQues *p;
	p = chooseques;
	char choosequesfilename[60];
	GetquestionsfileName(choosequesfilename, 1);//��ȡ������ѡ�����ļ���·��

	FILE *fp;
	if ((fp = fopen(choosequesfilename, "w")) == NULL) {
		printf("��%s�ļ�ʧ��\n", choosequesfilename);
		exit(0);
	}
	//printf("��%s�ļ��ɹ�\n", choosequesfilename);
	for (int i=0; i < choosequescount; i++) {
		fwrite(p, sizeof(ChooseQues), 1, fp);
		p++;
	}
	fclose(fp);
}
void ChooseQuesDelete()
{
	printf("����Ҫɾ������Ŀ�����\n");
	int num;
	scanf("%d", &num);
	while (num > choosequescount || num < 1) {
		printf("������ȷ����Ŀ���\n");
		scanf("%d", &num);
	}
	for (int i = num; i < choosequescount; i++) {
		chooseques[i-1] = chooseques[i];
	}
	choosequescount--;
	ChooseQues *p;
	p = chooseques;
	char choosequesfilename[60];
	GetquestionsfileName(choosequesfilename, 1);//��ȡ������ѡ�����ļ���·��

	FILE *fp;
	if ((fp = fopen(choosequesfilename, "w")) == NULL) {
		printf("��%s�ļ�ʧ��\n", choosequesfilename);
		exit(0);
	}
	//printf("��%s�ļ��ɹ�\n", choosequesfilename);
	for (int i = 0; i < choosequescount; i++) {
		fwrite(p, sizeof(ChooseQues), 1, fp);
		p++;
	}
	current_exambank.QuesNum = current_exambank.QuesNum - 1;
	fclose(fp);
}

/*�����*/
int BankQuesList() {
	FILE *fp;
	char bankquesfilename[60];
	GetquestionsfileName(bankquesfilename, 2);//��ȡ������������ļ���·��
	if ((fp = fopen(bankquesfilename, "r")) == NULL) {
		printf("ERROR\n");
		printf("����·����%s\n", bankquesfilename);
		exit(0);
	}
	BankQues *q2;
	q2 = bankques;
	rewind(fp);//ָ���λ
	fseek(fp, 0, 2);
	int quesfileend;
	quesfileend = ftell(fp);//��¼<questions>�ļ���β��
	rewind(fp);//ָ���λ
	int i = 1;//������
	if (ftell(fp) == quesfileend) {
		printf("�����Ϊ�գ�\n");
		fclose(fp);
		return 0;
	}
	else {
		printf("\n\t**        ������������б�\t**        \n\n");
		while (ftell(fp) != quesfileend) {//�ж�fpָ���Ƿ��ȡ��<questions>�ļ�β��
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
	printf("������Ų���\n1 - �޸�����\n2 - ��������\n3 - ɾ������\n4 - ������һ��\n");
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
	printf("����1������һ����������������\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j1, 1);
	}
	else {
		printf("лл���ʹ�ã������Ѿ�����\n");
		exit(0);
	}
}

void BankQuesAdd() {
	/*����⿪ʼ*/
	int n2;
	printf("������<�����>����Ŀ����(����0�������������Ŀ)��");
	scanf("%d", &n2);
	FILE *fp;
	char bankquesfilename[60];
	GetquestionsfileName(bankquesfilename, 2);//��ȡ������������ļ���·��
	if ((fp = fopen(bankquesfilename, "a+")) == NULL) {
		printf("error\n");
		exit(0);
	}
	for (int i = 0; i < n2; i++) {
		BankQues ques;
		printf("����%d����������ɣ�\n", i + 1);
		getchar();//���������\n
		gets_s(ques.ask, 200);
		printf("��������ȷ�Ĵ�: ");
		gets_s(ques.right, 200);
		fwrite(&ques, sizeof(BankQues), 1, fp);
	}
	current_exambank.QuesNum = current_exambank.QuesNum + n2;
	fclose(fp);
	/*��������!!!*/
}
void BankQuesModify()
{
	printf("������Ҫ�޸ĵ�������ţ�\n");
	int num;
	scanf("%d", &num);
	while (num > bankquescount || num < 1) {
		printf("������ȷ����Ŀ���\n");
		scanf("%d", &num);
	}
	char judge[4] = "no";
	char input[200];
	printf("��������������(����no�����޸Ĵ���)��\n");
	getchar();//���������\n
	gets_s(input, 200);
	if (strcmp(input, judge) != 0) {
		strcpy(bankques[num - 1].ask, input);
	}
	printf("������������Ĵ�(����no�����޸Ĵ���):\n");
	//getchar();//���������\n
	gets_s(input, 200);
	if (strcmp(input, judge) != 0) {
		strcpy(bankques[num - 1].right, input);
	}
	BankQues *p;
	p = bankques;
	char bankquesfilename[60];
	GetquestionsfileName(bankquesfilename, 2);//��ȡ�������������ļ���·��

	FILE *fp;
	if ((fp = fopen(bankquesfilename, "w")) == NULL) {
		printf("��%s�ļ�ʧ��\n", bankquesfilename);
		exit(0);
	}
	//printf("��%s�ļ��ɹ�\n", bankquesfilename);
	for (int i = 0; i < bankquescount; i++) {
		fwrite(p, sizeof(BankQues), 1, fp);
		p++;
	}
	fclose(fp);
}
void BankQuesDelete()
{
	printf("����Ҫɾ������Ŀ�����\n");
	int num;
	scanf("%d", &num);
	while (num > bankquescount || num < 1) {
		printf("������ȷ����Ŀ���\n");
		scanf("%d", &num);
	}
	for (int i = num; i < bankquescount; i++) {
		bankques[i - 1] = bankques[i];
	}
	bankquescount--;
	BankQues *p;
	p = bankques;
	char bankquesfilename[60];
	GetquestionsfileName(bankquesfilename, 2);//��ȡ�����ļ������ļ���·��

	FILE *fp;
	if ((fp = fopen(bankquesfilename, "w")) == NULL) {
		printf("��%s�ļ�ʧ��\n", bankquesfilename);
		exit(0);
	}
	//printf("��%s�ļ��ɹ�\n", bankquesfilename);
	for (int i = 0; i < bankquescount; i++) {
		fwrite(p, sizeof(BankQues), 1, fp);
		p++;
	}
	current_exambank.QuesNum = current_exambank.QuesNum - 1;
	fclose(fp);
}

/*������*/
int CalcuQuesList() {
	FILE *fp;
	char calcufilename[60];
	GetquestionsfileName(calcufilename, 3);//��ȡ�����ļ������ļ���·��
	if ((fp = fopen(calcufilename, "r")) == NULL) {
		printf("ERROR\n");
		printf("����·����%s\n", calcufilename);
		exit(0);
	}
	CalcuQues *q3;
	q3 = calcuques;
	rewind(fp);//ָ���λ
	fseek(fp, 0, 2);
	int quesfileend;
	quesfileend = ftell(fp);//��¼<questions>�ļ���β��
	rewind(fp);//ָ���λ
	int i = 1;//������
	if (ftell(fp) == quesfileend) {
		printf("���������Ϊ�գ�\n");
		fclose(fp);
		return 0;
	}
	else {
		printf("\n\t**        �����ļ������б�\t**        \n\n");
		while (ftell(fp) != quesfileend) {//�ж�fpָ���Ƿ��ȡ��<questions>�ļ�β��
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
	printf("������Ų���\n1 - �޸�����\n2 - ��������\n3 - ɾ������\n4 - ������һ��\n");
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
	printf("����1������һ����������������\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j1, 1);
	}
	else {
		printf("лл���ʹ�ã������Ѿ�����\n");
		exit(0);
	}
}

void CalcuQuesAdd() {
	/*�����⿪ʼ*/
	//printf("���뵽���������\n");
	int n3;
	printf("������<�������>����Ŀ����(����0�������������Ŀ)��");
	scanf("%d", &n3);
	FILE *fp;
	char calcufilename[60];
	GetquestionsfileName(calcufilename, 3);//��ȡ������������ļ���·��
	if ((fp = fopen(calcufilename, "a+")) == NULL) {
		printf("error\n");
		exit(0);
	}
	for (int i = 0; i < n3; i++) {
		CalcuQues ques;
		printf("����%d�����������ɣ�\n", i + 1);
		getchar();//���������\n
		gets_s(ques.ask, 200);
		printf("��������ȷ�Ĵ�: ");
		gets_s(ques.right, 200);
		fwrite(&ques, sizeof(CalcuQues), 1, fp);
	}
	current_exambank.QuesNum = current_exambank.QuesNum + n3;
	fclose(fp);
	/*���������!!!*/
}
void CalcuQuesModify()
{
	printf("������Ҫ�޸ĵ�������ţ�\n");
	int num;
	scanf("%d", &num);
	while (num > calcuquescount || num < 1) {
		printf("������ȷ����Ŀ���\n");
		scanf("%d", &num);
	}
	char judge[4] = "no";
	char input[200];
	printf("����ü���������(����no�����޸Ĵ���)��\n");
	getchar();//���������\n
	gets_s(input, 200);
	if (strcmp(input, judge) != 0) {
		strcpy(calcuques[num - 1].ask, input);
	}
	printf("������ü�����Ĵ�(����no�����޸Ĵ���):\n");
	//getchar();//���������\n
	gets_s(input, 200);
	if (strcmp(input, judge) != 0) {
		strcpy(calcuques[num - 1].right, input);
	}
	CalcuQues *p;
	p = calcuques;
	char calcuquesfilename[60];
	GetquestionsfileName(calcuquesfilename, 3);//��ȡ�����ļ�������ļ���·��

	FILE *fp;
	if ((fp = fopen(calcuquesfilename, "w")) == NULL) {
		printf("��%s�ļ�ʧ��\n", calcuquesfilename);
		exit(0);
	}
	//printf("��%s�ļ��ɹ�\n", calcuquesfilename);
	for (int i = 0; i < calcuquescount; i++) {
		fwrite(p, sizeof(CalcuQues), 1, fp);
		p++;
	}
	fclose(fp);
}
void CalcuQuesDelete()
{
	printf("����Ҫɾ������Ŀ�����\n");
	int num;
	scanf("%d", &num);
	while (num > calcuquescount || num < 1) {
		printf("������ȷ����Ŀ���\n");
		scanf("%d", &num);
	}
	for (int i = num; i < calcuquescount; i++) {
		calcuques[i - 1] = calcuques[i];
	}
	calcuquescount--;
	CalcuQues *p;
	p = calcuques;
	char calcuquesfilename[60];
	GetquestionsfileName(calcuquesfilename, 3);//��ȡ�����ļ������ļ���·��

	FILE *fp;
	if ((fp = fopen(calcuquesfilename, "w")) == NULL) {
		printf("��%s�ļ�ʧ��\n", calcuquesfilename);
		exit(0);
	}
	//printf("��%s�ļ��ɹ�\n", calcuquesfilename);
	for (int i = 0; i < calcuquescount; i++) {
		fwrite(p, sizeof(CalcuQues), 1, fp);
		p++;
	}
	current_exambank.QuesNum = current_exambank.QuesNum - 1;
	fclose(fp);
}