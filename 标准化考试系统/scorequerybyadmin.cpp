#include "declare.h"

/*�����ⲿ����*/
extern int testnum;
extern int testamount;
extern ST_test test[20];
extern ST_test current_test;
extern int studentstatus;
extern int current_studentfilenum;
extern ST_student student[100];
extern int studentamount;

/*���ļ��µ�ȫ�ֱ���*/
int currenttest_studentamount=0;//�μӸ÷��Ծ��ѧ������
ST_currenttest_student currenttest_student[100];//�洢�˲μӸ÷��Ծ��ѧ����Ϣ


void QuerybyAdminInt() {
	printf("\t**        ������ѯϵͳ���棡\t**        \n\n");
	printf("��������Ų���:\n1 - ���Ծ��ѯ\n2 - ��ѧ����ѯ\n3 - ������һ��\n4 - �˳�����\n");
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


void QuerybyTest() {
	char inpute[40];
	TestList();
	printf("������Ų�����\n1 - ��ѯ�ɼ�\n2 - ������һ��\n3 - ��������\n");
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {
			printf("�����Ծ���ţ��鿴�÷��Ծ��ѧ���ɼ���Ϣ��\n");
			scanf("%d", &testnum);//����Ҫ�������Ծ����
			while (testnum > testamount) {
				printf("�����ڸ��Ծ�����������:\n");
				scanf("%d", &testnum);
			}
			InitCurrent_test(&current_test);//��ʼ����ǰ�������Ծ���Ϣ
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
				printf("û��ѧ���μӹ����ԣ�ѧ���ɼ��ļ�Ϊ��\n");
				fclose(fp);
			}
			else {
				currenttest_studentamount = 0;
				studentamount = 0;
				while (ftell(fp) != fileend) {//��ȡѧ���ɼ���Ϣ,�߶�ȡ�����ѯ��ѧ���Ƿ�μӵ�ǰ�Ծ�����ǣ�����ɼ���ID��
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
				//printf("�ɼ��ļ��й���%d��ѧ����Ϣ\n", studentamount);
				fclose(fp);
				printf("%-13s%-13s%-13s\n", "����", "ѧ��ID", "ѧ���ɼ�");
				//���������㷨����ѧ���ĳɼ���������
				QuickSort(currenttest_student);
				for (int i = 0; i < currenttest_studentamount; i++)
				{
					printf("%-13d%-13s%-13d\n", i + 1, currenttest_student[currenttest_studentamount - i - 1].id, currenttest_student[currenttest_studentamount - i - 1].socre);
				}
				printf("********************************************\n������Ų���:\n1 - ������һ��\n2 - ��������\n");
				while (1) {
					scanf("%s", inpute);
					if (inpute[0] == '1'&& inpute[1] == '\0') {
						printf("���ڷ�����һ������ȴ�...\n");
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
			printf("��������ȷ�����:\n");
		}

	}
}

void QuerybyStu() {
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
		printf("û��ѧ���μӹ����ԣ�ѧ���ɼ��ļ�Ϊ��\n");
		fclose(fp);
	}
	else {
		studentamount = 0;
		while (ftell(fp) != fileend) {//��ȡѧ���ɼ���Ϣ��student������
			fread(p, sizeof(ST_student), 1, fp);
			studentamount++;
			p++;
		}
		fclose(fp);//��Ϣ¼��������ر��ļ�
		printf("������Ų�����\n1 - ��ѯѧ���ɼ�\n2 - ����μӹ����Ե�ѧ��\n3 - ������һ��\n4 - ��������\n");
		char inpute[40];
		while (1) {
			scanf("%s", inpute);
			if (inpute[0] == '1'&& inpute[1] == '\0') {
				printf("������Ҫ��ѯ��ѧ��ѧ��:\n");
				char inpute[20];
				scanf("%s", inpute);
				printf("%-13s%-13s%-13s\n", "���", "�Ծ���", "���Գɼ�");
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
					printf("��ѧ�Ŷ�Ӧ��ѧ��δ�μ��κο��ԣ�\n");
				}
				break;
			}
			else if (inpute[0] == '2'&& inpute[1] == '\0') {
				printf("%-13s%-13s%-13s\n", "���", "ѧ��ID", "�μӴ���");
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
				printf("��������ȷ����ţ�\n");
			}
		}
		printf("********************************************");
		printf("������Ų�����\n1 - ������һ��\n2 - ��������\n");
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
				printf("��������ȷ�����:\n");
			}
		}
	}
}




/*���������㷨*/
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
