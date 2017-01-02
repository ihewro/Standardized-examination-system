#include "declare.h"

/*ѧ���Ѿ��μӹ������ⲻ���ٴβμӣ�*/

/*�����ⲿ����*/
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


/*���ļ��µ�ȫ�ֱ���*/
int rightchooseques = 0;//��Ե�ѡ����
int rightbankques = 0;//��Ե������
int rightcalcuques = 0;//��Եļ�����
int rightamount = 0;//��Ե�����Ŀ����
AnswerbyUser choosequesanswer[100];//�洢�û������ѡ����𰸵�����
AnswerbyUser bankquesanswer[100];//�洢�û�����������𰸵�����
AnswerbyUser calcuquesanswer[100];//�洢�û�����ļ�����𰸵�����
char correctanswer[40] = "��ȷ";
char falseanswer[40] = "����";
int studentgrade;//ѧ���ó����Ե��ܳɼ�
int studentstatus;
int current_studentfilenum;//��ǰ������ѧ���ڳɼ��ļ��е����
ST_student student[100];//��ѧ���ɼ��ļ����ݴ洢�ڸ���������
int studentamount = 0;//ѧ���ɼ��ļ������ѧ������

/*����*/
void TakingtestInt() {
	int result;
	result = TestList();
	if (result == 0) {
		//NormalExitProgram();
	}
	else {
		printf("\n������������Ž��뿼�ԣ�\n");
		int n;
		scanf("%d", &n);
		while (n > testamount || n < 1) {
			printf("��������ȷ���������:");
			scanf("%d", &n);
		}
		testnum = n;
		InitCurrent_test(&current_test);
		studentstatus = Checkstudentstatus();
		if (studentstatus == 3) {
			printf("���Ѿ��μ��˱��ο��ԣ������ظ��μӡ�\n");
			printf("\n������Ų���:\n1 - ������һ��\n2 - ��������\n");
			char inpute[40];
			while (1) {
				scanf("%s", inpute);
				if (inpute[0] == '1'&& inpute[1] == '\0') {
					printf("���ڷ�����һ������ȴ�...\n");
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
					printf("��������ȷ����ţ�\n");
				}
			}
		}
		else {
			AnswerChooseques();
			AnswerBankques();
			AnswerCalcuques();
			Evaluateques();
			Gradesave();
			printf("********************************************\n���ĳɼ��Ѿ��洢��ϣ�\n������Ų�����\n1 - ������һ��\n2 - ��������\n");
			char inpute[40];
			while (1) {
				scanf("%s", inpute);
				if (inpute[0] == '1'&& inpute[1] == '\0') {
					printf("���ڷ�����һ������ȴ�...\n");
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

/*�ش�����*/
void AnswerChooseques() {
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
	if (ftell(fp) == quesfileend) {//�÷��Ծ�û��ѡ����
		fclose(fp);
	}
	else {//�÷��Ծ���ѡ����������
		printf("\t**        ѡ���������棺\t**        \n\n");
		while (ftell(fp) != quesfileend) {//�ж�fpָ���Ƿ��ȡ��<questions>�ļ�β��
			fread(p1, sizeof(ChooseQues), 1, fp);
			printf("%d - %s\n", i, p1->ask);
			for (j = 0; j < 4; j++) {
				printf("%c. %s", j + 'A', p1->answer[j]);
				printf("\n");
			}
			printf("\n��������Ĵ𰸣�");
			scanf("%s", &choosequesanswer[i - 1].right);
			while (choosequesanswer[i - 1].right[0] < 'A' || choosequesanswer[i - 1].right[0] > 'D')
			{
				printf("������Ĵ𰸲��Ϸ�����������ȷ�Ĵ�: ");
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
	test_GetquestionsfileName(quesfilename, 2);//��ȡ���Ծ��������ļ���·��
	if ((fp = fopen(quesfilename, "r")) == NULL) {
		printf("ERROR\n");
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
		fclose(fp);
	}
	else {
		printf("\n\t**        ����������棺\t**        \n\n");
		while (ftell(fp) != quesfileend) {//�ж�fpָ���Ƿ��ȡ��<questions>�ļ�β��
			fread(p2, sizeof(BankQues), 1, fp);
			printf("%d - %s\n", i, p2->ask);
			printf("\n��������Ĵ�:");
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
		fclose(fp);
	}
	else {
		printf("\n\t**        �����������棺\t**        \n\n");
		while (ftell(fp) != quesfileend) {//�ж�fpָ���Ƿ��ȡ��<questions>�ļ�β��
			fread(p3, sizeof(CalcuQues), 1, fp);
			printf("%d - %s\n", i, p3->ask);
			printf("\n��������Ĵ�:");
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


/*��������*/
void Evaluateques() {//���������������Ѵ�������洢�����Ա����Ĳ�ѯ
	EvaluateChooseques();
	EvaluateBankques();
	EvaluateCalcuques();
}

void EvaluateChooseques() {
	char judge[40];
	printf("\t**        ѡ������������\t**        \n\n");
	printf("\n%-13s%-13s%-13s%s\n", "���", "��׼��", "���Ĵ�", "����");
	int i;
	int j = 1;//��Ŀ���
	for (i = 0; i < test_choosequescount; i++) {
		if (strcmp(test_chooseques[i].right, choosequesanswer[i].right) == 0)
			strcpy(judge, correctanswer);
		else
			strcpy(judge, falseanswer);
		printf("%-13d%-13s%-13s%s\n", j, test_chooseques[i].right, choosequesanswer[i].right, judge);
		j++;
	}
	printf("\n������%d��ѡ���� \n\n", rightchooseques);
}
void EvaluateBankques() {
	char judge[40];
	printf("\t**        �������������\t**        \n\n");
	printf("\n%-13s%-13s%-13s%s\n", "���", "��׼��", "���Ĵ�", "����");
	int i;
	int j = 1;//��Ŀ���
	for (i = 0; i < test_bankquescount; i++) {
		if (strcmp(test_bankques[i].right, bankquesanswer[i].right) == 0)
			strcpy(judge, correctanswer);
		else
			strcpy(judge, falseanswer);
		printf("%-13d%-13s%-13s%s\n", j, test_bankques[i].right, bankquesanswer[i].right, judge);
		j++;
	}
	printf("\n������%d������� \n\n", rightbankques);
}
void EvaluateCalcuques() {
	char judge[40];
	printf("\t**        ��������������\t**        \n\n");
	printf("\n%-13s%-13s%-13s%s\n", "���", "��׼��", "���Ĵ�", "����");
	int i;
	int j = 1;//��Ŀ���
	for (i = 0; i < test_calcuquescount; i++) {
		if (strcmp(test_calcuques[i].right, calcuquesanswer[i].right) == 0)
			strcpy(judge, correctanswer);
		else
			strcpy(judge, falseanswer);
		printf("%-13d%-13s%-13s%s\n", j, test_calcuques[i].right, calcuquesanswer[i].right, judge);
		j++;
	}
	printf("\n������%d�������� \n\n", rightcalcuques);
}

void Gradesave() {
	FILE *fp;
	if ((fp = fopen("studentscore.txt", "r+")) == NULL) {//����ʹ��r+������ʹ��a+��
		printf("error\n");
	}
	ST_student *q;
	studentgrade = rightchooseques*current_test.value[0] + rightbankques*current_test.value[1] + rightcalcuques*current_test.value[2];
	int grade = rightchooseques*current_test.value[0] * test_choosequescount + rightbankques*current_test.value[1] * test_bankquescount + rightcalcuques*current_test.value[2] * test_calcuquescount;
	printf("�÷��Ծ������Ϊ��%d,����ܷ�Ϊ��%d\n", grade,studentgrade);
	if (studentstatus == 0) {//���ѧ���ɼ��ļ�Ϊ��
		strcpy(student[0].id, studentID);
		student[0].exams[0] = current_test.num;
		student[0].exams_score[0] = studentgrade;
		student[0].testnumbers = 1;
		rewind(fp);//��ָ���Ƶ��ļ���ʼ��
		q = &student[0];
		fwrite(q, sizeof(ST_student), 1, fp);//��дҪ�޸ĵ�ѧ���ɼ��ļ�
		fclose(fp);
		//printf("��ǰѧ��IDΪ��%s\n", student[0].id);
	}
	else {//ѧ���ɼ��ļ���Ϊ��
		if (studentstatus == 1) {//ѧ���ɼ��ļ���û�и�ѧ����
			strcpy(student[current_studentfilenum].id ,studentID);
			student[current_studentfilenum].exams[0] = current_test.num;
			student[current_studentfilenum].exams_score[0] = studentgrade;
			student[current_studentfilenum].testnumbers = 1;
			fseek(fp, 0, 2);//��ָ���Ƶ��ļ�β��
			q = &student[current_studentfilenum];
			fwrite(q, sizeof(ST_student), 1, fp);//��дҪ�޸ĵ�ѧ���ɼ��ļ�
			fclose(fp);
			//printf("1��ǰѧ��IDΪ��%s\n", student[current_studentfilenum].id);

		}
		else if (studentstatus == 2) {//ѧ���ɼ��ļ��Ѿ��и�ѧ����,����ѧ��û�вμӱ�������
			strcpy(student[current_studentfilenum].id ,studentID);
			student[current_studentfilenum].exams[student[current_studentfilenum].testnumbers] = current_test.num;
			student[current_studentfilenum].exams_score[student[current_studentfilenum].testnumbers] = studentgrade;
			student[current_studentfilenum].testnumbers++;
			rewind(fp);
			//printf("��ǰѧ����λ�ã�%d\n", current_studentfilenum);
			fseek(fp, current_studentfilenum * sizeof(ST_student), 0);//���ļ�ָ����Ҫ�޸ĵ�ͬѧ�Ŀ�ʼ
			int pos = ftell(fp);
			//printf("�ļ�ָ�����ͷ����λ��%d\n", pos);
			q = &student[current_studentfilenum];
			fwrite(q, sizeof(ST_student), 1, fp);//�޸�ѧ���ɼ��ļ�
			fclose(fp);
			//printf("2��ǰѧ��IDΪ��%s\n", student[current_studentfilenum].id);
		}
		else
			printf("error!!\n");
	}
}

/*
* 0: ѧ���ɼ��ļ�Ϊ��
* 1: ѧ���ɼ��ļ���Ϊ�գ���ѧ��û�б�¼��ѧ���ɼ��ļ���
* 2: ѧ���ɼ��ļ���Ϊ�գ�����ѧ����¼��ѧ���ɼ��ļ��У���û�вμӱ�������
* 3: ѧ���ɼ��ļ���Ϊ�գ�����ѧ����¼��ѧ���ɼ��ļ��У������Ѿ��μӱ�������
*/
int Checkstudentstatus() {
	FILE *fp;
	if ((fp = fopen("studentscore.txt", "a+")) == NULL) {
		printf("error\n");
	}
	rewind(fp);//ָ���λ
	fseek(fp, 0, 2);//ָ���Ƶ�β��
					//fseek(fp2, 0, 2);//ָ���Ƶ�β��
	int fileend;
	fileend = ftell(fp);//��¼�ļ���β��
	rewind(fp);//ָ���λ
	ST_student *p;
	p = student;
	if (ftell(fp) == fileend) {
		current_studentfilenum = 0;
		fclose(fp);
		return 0;//���ѧ���ɼ��ļ�Ϊ��
	}
	else {//ѧ���ɼ��ļ���Ϊ��
		studentamount = 0;
		while (ftell(fp) != fileend) {//��ȡѧ���ɼ���Ϣ��student������
			fread(p, sizeof(ST_student), 1, fp);
			studentamount++;
			p++;
		}
		fclose(fp);//��Ϣ¼��������ر��ļ�
		int i, j;
		for (i = 0; i < studentamount; i++) {//��ѯ��ǰѧ��ID�Ƿ��Ѿ���¼���
			if (strcmp(studentID,student[i].id)==0) {
				for (j = 0; j < student[i].testnumbers; j++) {
					if (current_test.num == student[i].exams[j])
					{
						return 3;//��ǰѧ���ڳɼ��ļ��У����Ҳμ��˱����Ծ�
					}
				}
				if (j >= student[i].testnumbers)
				{
					current_studentfilenum = i;
					return 2;//��ǰѧ���ڳɼ��ļ��У����Ǳ����Ծ�û�вμ�
				}
			}
		}
		if (i >= studentamount)
		{
			current_studentfilenum = i;
			return 1;//��ǰѧ�����ڳɼ��ļ���
		}
	}
}
