#include "declare.h"
jmp_buf j4;

/*ɾ����һ���Ż������û���ļ�����ֱ������ɾ�����Ȳ�ѯ��û�и��ļ�*/
/*�Ż���������һ��������*/

/*�����ⲿ����*/
extern ST_exambank current_exambank;
extern int exambanknum;
extern int choosequescount;
extern int bankquescount;
extern int calcuquescount;
extern ChooseQues chooseques[200];
extern BankQues bankques[200];
extern CalcuQues calcuques[200];
extern int eaxmbankamount;

/*���ļ��µ�ȫ�ֱ���*/
ST_test test[20];//��TestInfoOverview.txt�ļ��ж�ȡ�Ծ��Ҵ洢����������
ST_test current_test; //��ǰ�������Ծ�
int testnum = -1;//��ǰ�������Ծ����
int testamount = 0; //�Ծ������,��ʼ��Ϊ0

ChooseQues test_chooseques[200];//��ǰ�Ծ��ѡ�������ݴ洢����������
BankQues test_bankques[200];//��ǰ�Ծ����������ݴ洢����������
CalcuQues test_calcuques[200];//��ǰ�Ծ�ļ��������ݴ洢����������

int test_choosequescount = 0;//�Ծ���ѡ����Ŀ������
int test_bankquescount = 0;//�Ծ��������Ŀ������
int test_calcuquescount = 0;//�Ծ��м�����Ŀ������


/*����*/
void TestbankInt() {
	printf("\t**        �Ծ����ϵͳ���棡\t**        \n\n");
	char ch;
	FILE *fp;
	if (_access("testbank", 0)) {
		_mkdir("testbank");
	}
	if ((fp = fopen("testbank/TestInfoOverview.txt", "a+")) == NULL) {
		printf("·���ļ� testbank/TestInfoOverview.txt ��ʧ�ܣ�����Ƿ���Ȩ�޲���\n");
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
	printf("�������ֲ���\n1 - ����Ծ��б�\n2 - �������Ծ�\n3 - ������һ��\n4 - ��������\n");
	char inpute[40];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {//����Ծ��б�
			TestList();
			TestOperate();
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//�������Ծ�
			TestCreat();
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {//������һ��
			printf("���ڷ�����һ������ȴ�...\n");
			Sleep(1000);
			system("cls");
			AdminInt();
		}
		else if (inpute[0] == '4'&& inpute[1] == '\0') {//��������
			NormalExitProgram();
		}
		else {
			printf("��������ȷ�����:\n");
		}
	}
}
void TestbankNoneInt(FILE * fp)
{
	int n;
	fclose(fp);
	printf("\t          ��ǰϵͳ�Ծ�Ϊ��\n\t          �Ƿ���Ҫ����һ���Ծ�?\n\n������Ų���\n1 - �������Ծ� \n2 - ������һ�� \n");
	scanf("%d", &n);
	if (n == 1) {
		TestCreat();
	}
	else if (n == 2)
		AdminInt();
}


/*���Ծ����*/
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
	printf("������Ӧ����ţ����в�����\n");
	scanf("%d", &testnum);//����Ҫ�������Ծ���
	while (testnum > testamount) {
		printf("�����ڸ��Ծ�����������:\n");
		scanf("%d", &testnum);
	}
	InitCurrent_test(&current_test);//��ʼ����ǰ�������Ծ���Ϣ
	printf("\n�������ֲ���\n1 - ����Ծ��������Ŀ\n2 - ɾ�����Ծ�\n3 - ������һ��\n4 - ��������\n");
	char inpute[40];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {//����Ծ��������Ŀ
			TestQuesList();
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//ɾ���Ծ�
			TestDelete();
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {//������һ��
			printf("���ڷ�����һ������ȴ�...\n");
			Sleep(1000);
			system("cls");
			TestbankInt();
			break;
		}
		else if (inpute[0] == '4'&& inpute[1] == '\0') {//��������
			NormalExitProgram();
			break;
		}
		else {
			printf("��������ȷ�����:\n");
		}
	}
}

void TestCreat() {
	FILE *fp;
	printf("�������Ծ������:");
	scanf("%s", current_test.name);
	int status;//�ļ���·������״̬
	char strtestfilefoleder[40];
	GetCurrent_testName(strtestfilefoleder);
	status = _mkdir(strtestfilefoleder);
	if (status != 0)
		printf("�Ծ��Ӧ���ļ��д���ʧ�ܣ�������û��Ȩ�޻����ļ��г�ͻ����鵱ǰ·��%s�Ƿ���ȷ��\n", strtestfilefoleder);
	else {//�Ծ����ƶ�Ӧ���ļ��д����ɹ�
		current_test.num = RandomTestnum();
		printf("�÷��Ծ��ȡ����Ψһ���Ϊ��%d\n", current_test.num);
		printf("����ѡ����ÿ��ķ�ֵ��");
		scanf("%d",&current_test.value[0]);
		printf("\n���������ÿ��ķ�ֵ��");
		scanf("%d", &current_test.value[1]);
		printf("\n���������ÿ��ķ�ֵ��");
		scanf("%d", &current_test.value[2]);
		printf("\n");
		testnum = 1;
		ChooseQuesSelect();
		BankQuesSelect();
		CalcuQuesSelect();
		if ((fp = fopen("testbank/TestInfoOverview.txt", "a+")) == NULL) {
			printf("���Ծ����Ϣ�ļ�ʧ�ܡ�����·����testbank/TestInfoOverview.txt\n");
			exit(0);
		}
		fwrite(&current_test, sizeof(ST_test), 1, fp);
		fclose(fp);
		printf("�Ծ����ɹ����Ƿ񷵻��Ծ��������?\n����1���أ����������˳�����\n");
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
	rewind(fp2);//ָ���λ
	fseek(fp2, 0, 2);
	int fileend;
	fileend = ftell(fp2);//��¼�ļ���β��
	rewind(fp2);//ָ���λ
	while (ftell(fp2) != fileend) {//��ȡ���е������
		fscanf(fp2, "%d\n", &list[i]);
		i++;
		testnumamount++;
	}
	srand((unsigned)time(NULL));//��ʼ���������
	while (1) {
		tmp = rand() % 10;//���ɸ�λ�ϵ������
		num = tmp;
		tmp = rand() % 10;//����ʮλ�ϵ������
		num = num + tmp * 10;
		tmp = rand() % 10;//���ɰٷ��ϵ������
		num = num + tmp * 100;
		for (j = 0; j < testnumamount; j++) {//�����Ծ����Ƿ��ظ�
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
	GetCurrent_testName(testname);//��ȡ��ǰ�Ծ��·��
	char choosequesfilename[60];
	test_GetquestionsfileName(choosequesfilename, 1);//��ȡ���Ծ��ѡ�����ļ���·��
	char bankquesfilename[60];
	test_GetquestionsfileName(bankquesfilename, 2);//��ȡ���Ծ��������ļ���·��
	char calcufilename[60];
	test_GetquestionsfileName(calcufilename, 3);//��ȡ���Ծ�ļ������ļ���·��
	//Sleep(5000);
	if (remove(choosequesfilename) == 0) {
		printf("���Ծ�ѡ����ɾ�����\n");
	}
	else {
		printf("��ǰɾ���ļ���Ϊ:%s\n", choosequesfilename);
		//printf("%d", testnum);
		printf("���Ծ�ѡ����ɾ��ʧ�ܣ�����ϵ����Աihewro@163.com\n");
		perror("remove");
		exit(0);
	}
	if (remove(bankquesfilename) == 0) {
		printf("���Ծ������ɾ�����\n");
	}
	else {
		printf("��ǰɾ���ļ���Ϊ��%s", bankquesfilename);
		printf("���Ծ������ɾ��ʧ�ܣ�����ϵ����Աihewro@163.com\n");
		exit(0);
	}
	if (remove(calcufilename) == 0) {
		printf("���Ծ������ɾ�����\n");
	}
	else {
		printf("��ǰɾ���ļ���Ϊ��%s", calcufilename);
		printf("���Ծ������ɾ��ʧ�ܣ�����ϵ����Աihewro@163.com\n");
		exit(0);
	}
	if (_rmdir(testname) == 0) {
		int i;
		for (i = testnum; i <= testamount - 1; i++) {
			test[i - 1] = test[i];
		}
		FILE *fp;
		ST_test *p;
		if ((fp = fopen("testbank/TestInfoOverview.txt", "w")) == NULL) {//��ֻд��ʽ���ļ�
			printf("���Ծ���Ϣ�ļ�ʧ�ܡ�����·����testbank/TestInfoOverview.txt\n");
			printf("error\n");
			exit(0);
		}
		p = test;
		for (i = 0; i <= testamount - 2; i++, p++) {//���µ��Ծ���Ϣд��TestInfoOverview.txt��
			fwrite(p, sizeof(ST_test), 1, fp);
		}
		fclose(fp);

		printf("���Ծ�ɾ���ɹ����Ƿ񷵻���һ��������1���أ�����������������\n");
	}
	else {
		printf("��ǰɾ���ļ���Ϊ��%s", testname);
		printf("���Ծ�ɾ��ʧ�ܣ�����ϵ����Աihewro@163.com\n");
		exit(0);
	}
	int n;
	scanf("%d", &n);
	if (n == 1) {
		TestbankInt();
	}
	else {
		printf("лл���ʹ�ã������Ѿ��˳�\n");
		exit(0);
	}
}
int TestList() {
	FILE *fp;
	if ((fp = fopen("testbank/TestInfoOverview.txt", "a+")) == NULL) {
		printf("·���ļ� testbank/TestInfoOverview.txt ��ʧ�ܣ�����Ƿ���Ȩ�޲���\n");
		printf("error\n");
		return 0;
	}
	else {
		rewind(fp);//ָ���λ
		fseek(fp, 0, 2);
		int fileend;
		fileend = ftell(fp);//��¼�ļ���β��
		rewind(fp);//ָ���λ
		printf("\t**        Ŀǰ���Ծ��б��У�\t**        \n\n");
		printf("%-13s%-13s%-13s\n", "���", "�Ծ���", "�Ծ�����");
		ST_test *p;//���20���Ծ�
		p = test;
		int i = 1;

		while (ftell(fp) != fileend) {//�ж�fpָ���Ƿ��ȡ���ļ�β��
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
	printf("\nѡ��������Ծ��µ���Ӧ���͵���Ŀ:\n1 - ѡ����\n2 - �����\n3 - ������\n4 - ������һ��\n5 - �˳�����\n");
	char inpute[40];
	char str[40] = "testbank/";
	strcat(str, test[testnum - 1].name);//�ַ�������
	int result;
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {//����Ծ��ѡ����
			result = test_ChooseQuesList();
			if (result) {
				test_ChooseQuesOperate();
			}
			else {//ѡ����Ϊ��
				printf("�������\n1 - ��������\n2 - ������һ��\n3 - �˳�����\n");
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
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//����Ծ�������
			result = test_BankQuesList();
			if (result) {
				test_BankQuesOperate();
			}
			else {//�����Ϊ��
				printf("������ţ�1. �������� 2. ������һ�� 3.�˳�����\n");
				int n;
				scanf("%d", &n);
				if (n == 1) {//��������
					BankQuesSelect();
				}
				if (n == 2) {//������һ��
					TestQuesList();
				}
				if (n == 3) {//�˳�����
					NormalExitProgram();
				}
			}
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {//����Ծ�ļ�����
			result = test_CalcuQuesList();
			if (result) {
				test_CalcuQuesOperate();
			}
			else {//��������Ϊ��
				printf("������ţ�1. �������� 2. ������һ�� 3.�˳�����\n");
				int n;
				scanf("%d", &n);
				if (n == 1) {//���ѡ����
					CalcuQuesSelect();
				}
				if (n == 2) {//������һ��
					TestQuesList();
				}
				if (n == 3) {//�˳�����
					NormalExitProgram();
				}
			}
			break;
		}
		else if (inpute[0] == '4'&& inpute[1] == '\0') {//������һ��
			TestList();
			TestOperate();
			break;
		}
		else if (inpute[0] == '5'&& inpute[1] == '\0') {//�˳�����
			NormalExitProgram();
			break;
		}
		else {
			printf("��������ȷ�����:\n");
		}
	}
}


/*���Ծ����Ŀ�Ĳ���*/
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

//ѡ����
int test_ChooseQuesList() {
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 1);//��ȡ���Ծ��ѡ�����ļ���·��
	if ((fp = fopen(quesfilename, "r")) == NULL) {
		printf("ERROR\n");
		printf("����·����%s\n", quesfilename);
		exit(0);
	}
	printf("ѡ�����ļ��򿪳ɹ���%s\n", quesfilename);
	ChooseQues *p1;
	p1 = test_chooseques;
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
		printf("\n\t**        ���Ծ��ѡ�����б�\t**        \n\n");
		while (ftell(fp) != quesfileend) {//�ж�fpָ���Ƿ��ȡ��<questions>�ļ�β��
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
	printf("������Ų���\n1 - �������� \n2 - ɾ������ \n3 - ������һ��\n");
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

	printf("����1������һ����������������\n");
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
		printf("��ѡ�����ļ�ʧ�ܣ�����·����%s\n", quesfilename);
		printf("error\n");
		exit(0);
	}
	ExambankList();
	printf("\n���������������ѡ����\n");
	printf("��������Ϊ��%d\n", eaxmbankamount);
	int n;
	scanf("%d", &n);
	while (n > eaxmbankamount || n < 1) {
		printf("��������ȷ�������:\n");
		scanf("%d", &n);
	}
	exambanknum = n;//��ֵ����ǰ�������Ծ���
	InitCurrent_exambank(&current_exambank);
	ChooseQuesList();
	printf("\n����ѡ�������Ŀ�������Ӷ�Ӧ����Ŀ\nÿ�����֮���ÿո����,����-1�������\n");
	//int choosequesnum[100];//����ӵı�Ŵ洢����������
	int i = 0;
	int num;
	ChooseQues q;
	while (1) {
		scanf("%d", &num);
		if (num > choosequescount) {
			printf("�������Ŀ��Ŵ������������룬��������-1�������\n");
		}
		else {//ǰ��������ı������ȷ��
			  //choosequesnum[i] = num;
			if (num == -1)
				break;
			else {
				q = chooseques[num - 1];
				printf("��ǰ��Ŀ�����Ϊ��%s\n", q.ask);
				fwrite(&q, sizeof(ChooseQues), 1, fp);
				i++;
			}
		}
	}
	fclose(fp);
}
void test_ChooseQuesDelete()
{
	printf("����Ҫɾ������Ŀ�����\n");
	int num;
	scanf("%d", &num);
	while (num > test_choosequescount || num < 1) {
		printf("������ȷ����Ŀ���\n");
		scanf("%d", &num);
	}
	for (int i = num; i < test_choosequescount; i++) {
		test_chooseques[i - 1] = test_chooseques[i];
	}
	test_choosequescount--;
	ChooseQues *p;
	p = test_chooseques;
	char choosequesfilename[60];
	test_GetquestionsfileName(choosequesfilename, 1);//��ȡ���Ծ��ѡ�����ļ���·��

	FILE *fp;
	if ((fp = fopen(choosequesfilename, "w")) == NULL) {
		printf("��%s�ļ�ʧ��\n", choosequesfilename);
		exit(0);
	}
	//printf("��%s�ļ��ɹ�\n", choosequesfilename);
	printf("��ǰѡ��������Ϊ��%d\n", test_choosequescount);
	for (int i = 0; i < test_choosequescount; i++) {
		fwrite(p, sizeof(ChooseQues), 1, fp);
		p++;
	}
	//current_test.QuesNum = current_test.QuesNum - 1;
	fclose(fp);
}

//�����
int test_BankQuesList(){
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 2);//��ȡ���Ծ��������ļ���·��
	if ((fp = fopen(quesfilename, "r")) == NULL) {
		printf("ERROR������\n");
		printf("����·����%s\n", quesfilename);
		exit(0);
	}
	printf("������ļ��򿪳ɹ���%s\n", quesfilename);
	BankQues *p2;
	p2 = test_bankques;
	rewind(fp);//ָ���λ
	fseek(fp, 0, 2);
	int quesfileend;
	quesfileend = ftell(fp);//��¼<questions>�ļ���β��
	rewind(fp);//ָ���λ
	int i;
	i = 1;//������
	if (ftell(fp) == quesfileend) {
		printf("�����Ϊ�գ�\n");
		fclose(fp);
		return 0;
	}
	else {
		printf("\n\t**        ���Ծ��������б�\t**        \n\n");
		while (ftell(fp) != quesfileend) {//�ж�fpָ���Ƿ��ȡ��<questions>�ļ�β��
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
	printf("������Ų���\n1 - ��������\n2 - ɾ������\n3 - ������һ��\n");
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
	printf("����1������һ����������������\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j4, 1);
	}
	else {
		printf("лл���ʹ�ã������Ѿ�����\n");
		exit(0);
	}
}

void BankQuesSelect() {
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 2);
	if ((fp = fopen(quesfilename, "a+")) == NULL) {
		printf("��������ļ�ʧ�ܣ�����·����%s\n", quesfilename);
		printf("error\n");
		exit(0);
	}
	ExambankList();
	printf("\n��������������������\n");
	int n;
	scanf("%d", &n);
	while (n > eaxmbankamount || n < 1) {
		printf("��������ȷ�������:\n");
		scanf("%d", &n);
	}
	exambanknum = n;//��ֵ����ǰ�������Ծ���
	InitCurrent_exambank(&current_exambank);
	BankQuesList();
	printf("\n������������Ŀ�������Ӷ�Ӧ����Ŀ\nÿ�����֮���ÿո����,����-1�������\n");
	//int bankquesnum[100];//����ӵı�Ŵ洢����������
	int i = 0;
	int num;
	BankQues q;
	while (1) {
		scanf("%d", &num);
		if (num > bankquescount) {
			printf("�������Ŀ��Ŵ������������룬��������-1�������\n");
		}
		else {//ǰ��������ı������ȷ��
			  //bankquesnum[i] = num;
			if (num == -1)
				break;
			else {
				q = bankques[num-1];
				printf("��ǰ��Ŀ�����Ϊ��%s\n", q.ask);
				fwrite(&q, sizeof(BankQues), 1, fp);
				i++;
			}
		}
	}
	fclose(fp);
}
void test_BankQuesDelete() {
	printf("����Ҫɾ������Ŀ�����\n");
	int num;
	scanf("%d", &num);
	while (num > test_bankquescount || num < 1) {
		printf("������ȷ����Ŀ���\n");
		scanf("%d", &num);
	}
	for (int i = num; i < test_bankquescount; i++) {
		test_bankques[i - 1] = test_bankques[i];
	}
	test_bankquescount--;
	BankQues *p;
	p = test_bankques;
	char bankquesfilename[60];
	test_GetquestionsfileName(bankquesfilename, 2);//��ȡ���Ծ�ļ������ļ���·��

	FILE *fp;
	if ((fp = fopen(bankquesfilename, "w")) == NULL) {
		printf("��%s�ļ�ʧ��\n", bankquesfilename);
		exit(0);
	}
	//printf("��%s�ļ��ɹ�\n", bankquesfilename);
	for (int i = 0; i < test_bankquescount; i++) {
		fwrite(p, sizeof(BankQues), 1, fp);
		p++;
	}
	//current_exambank.QuesNum = current_exambank.QuesNum - 1;
	fclose(fp);
}

//������
int test_CalcuQuesList(){
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 3);//��ȡ���Ծ��ѡ�����ļ���·��
	if ((fp = fopen(quesfilename, "r")) == NULL) {
		printf("ERROR\n");
		printf("����·����%s\n", quesfilename);
		exit(0);
	}
	printf("�������ļ��򿪳ɹ���%s\n", quesfilename);
	CalcuQues *p3;
	p3 = test_calcuques;
	rewind(fp);//ָ���λ
	fseek(fp, 0, 2);
	int quesfileend;
	quesfileend = ftell(fp);//��¼<questions>�ļ���β��
	rewind(fp);//ָ���λ
	int i;
	i = 1;//������
	if (ftell(fp) == quesfileend) {
		printf("������Ϊ�գ�\n");
		fclose(fp);
		return 0;
	}
	else {
		printf("\n\t**        ���Ծ�ļ������б�\t**        \n\n");
		while (ftell(fp) != quesfileend) {//�ж�fpָ���Ƿ��ȡ��<questions>�ļ�β��
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
	printf("������Ų���\n1 - ��������\n2 - ɾ������\n3 - ������һ��\n");
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
	printf("����1������һ����������������\n");
	scanf("%d", &n);
	if (n == 1) {
		longjmp(j4, 1);
	}
	else {
		printf("лл���ʹ�ã������Ѿ�����\n");
		exit(0);
	}
}

void CalcuQuesSelect() {
	FILE *fp;
	char quesfilename[60];
	test_GetquestionsfileName(quesfilename, 3);
	if ((fp = fopen(quesfilename, "a+")) == NULL) {
		printf("�򿪼������ļ�ʧ�ܣ�����·����%s\n", quesfilename);
		printf("error\n");
		exit(0);
	}
	ExambankList();
	printf("\n��������������Ӽ�����\n");
	int n;
	scanf("%d", &n);
	while (n > eaxmbankamount || n < 1) {
		printf("��������ȷ�������:\n");
		scanf("%d", &n);
	}
	exambanknum = n;//��ֵ����ǰ�������Ծ���
	InitCurrent_exambank(&current_exambank);
	CalcuQuesList();
	printf("\n������������Ŀ�������Ӷ�Ӧ����Ŀ\nÿ�����֮���ÿո����,����-1�������\n");
	//int bankquesnum[100];//����ӵı�Ŵ洢����������
	int i = 0;
	int num;
	CalcuQues q;
	while (1) {
		scanf("%d", &num);
		if (num > calcuquescount) {
			printf("�������Ŀ��Ŵ������������룬��������-1�������\n");
		}
		else {//ǰ��������ı������ȷ��
			  //calcuquesnum[i] = num;
			if (num == -1)
				break;
			else {
				q = calcuques[num-1];
				printf("��ǰ��Ŀ�����Ϊ��%s\n", q.ask);
				fwrite(&q, sizeof(CalcuQues), 1, fp);
				i++;
			}
		}
	}
	fclose(fp);
}
void test_CalcuQuesDelete() {
	printf("����Ҫɾ������Ŀ�����\n");
	int num;
	scanf("%d", &num);
	while (num > test_calcuquescount || num < 1) {
		printf("������ȷ����Ŀ���\n");
		scanf("%d", &num);
	}
	for (int i = num; i < test_calcuquescount; i++) {
		test_calcuques[i - 1] = test_calcuques[i];
	}
	test_calcuquescount--;
	CalcuQues *p;
	p = test_calcuques;
	char calcuquesfilename[60];
	test_GetquestionsfileName(calcuquesfilename, 3);//��ȡ���Ծ�ļ������ļ���·��

	FILE *fp;
	if ((fp = fopen(calcuquesfilename, "w")) == NULL) {
		printf("��%s�ļ�ʧ��\n", calcuquesfilename);
		exit(0);
	}
	//printf("��%s�ļ��ɹ�\n", bankquesfilename);
	for (int i = 0; i < test_calcuquescount; i++) {
		fwrite(p, sizeof(CalcuQues), 1, fp);
		p++;
	}
	//current_exambank.QuesNum = current_exambank.QuesNum - 1;
	fclose(fp);
}