#include "declare.h"

/*�����ⲿ����*/
extern char studentID[20];
extern ST_student student[100];
extern int studentamount;

void QuerybyStuInt() {
	printf("\t**        ������ѯϵͳ���棡\t**        \n\n");
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
		printf("%-13s%-13s%-13s\n", "���", "�Ծ���", "���Գɼ�");
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
			printf("\n��δ�μ��κο��ԣ�\n");
		}
		printf("\n�������ѡ��:\n1 - ������һ��\n2 - ��������\n");
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
}