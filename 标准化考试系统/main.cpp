#define _CRT_SECURE_NO_WARNINGS
/*
 * ���ߣ���쿣��ƿ�1501�ࣩ��2015014278��
 * ���л�����windows + vs 2015
 */
#include "declare.h"

jmp_buf j2;
jmp_buf j3;

char studentID[20];

/*
 * �㷨����
 */

//������
int main() {
	MainInt();
	setjmp(j2);
	int n;
	n = SelectId();
	if (n == 1)
		AdminInt();
	else if (n == 0)
	{
		Sleep(1000);
		system("cls");
		main();

	}
	else 
		UserInt(studentID);
	return 1;
}

int SelectId() {
	setjmp(j3);
	char inpute[40];//���ѡ��
	while (1) {
		int count = 1;
		int count2 = 5;
		scanf("%s", inpute);
		FILE *fp;
		if (inpute[0] == '1'&& inpute[1] == '\0') {//����Ա
			if ((fp = fopen("password.txt", "r")) == NULL||_access("password.txt", 0) == -1) {
				printf("����Ա��Ϣ������������ϵ����Աihewro@163.com\n");
				//NormalExitProgram();
			}
			else {
				char pas2[100];
				fscanf(fp, "%s", pas2);
				fclose(fp);
				printf("���������Ա���룺\n");
				char pas[100];
				scanf("%s", pas);
				while (strcmp(pas, pas2)) {
					count++;
					count2--;
					if (count > 5)
						break;//����5�Σ��˳����ѭ��
					printf("������������㻹��%d�λ���\n", count2);
					scanf("%s", pas);
				}
				if (count > 5) {
					printf("�����������5�Σ�����Ϊ����ת��ѡ����ݽ���...\n");
					return 0;
				}
				else {
					printf("��¼�ɹ���\n\n");
					return 1;//����1,֤���ǹ���Ա���
				}
			}
			//break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//ѧ��
			FILE *fp;
			if ((fp = fopen("user.txt", "r")) == NULL|| _access("user.txt", 0) == -1) {
				printf("ѧ����Ϣ���ô�������ϵϵͳ����Ա��\n");
				//NormalExitProgram();
			}
			else {
				StudentId user[100];
				int fileend;
				fseek(fp, 0, 2);
				fileend = ftell(fp);
				rewind(fp);
				int i = 0;
				int usern = 0;
				while (ftell(fp) != fileend) {
					fscanf(fp, "%s\n", user[i].usrid);
					i++;
					usern++;
				}
				fclose(fp);
				printf("���������ѧ��\n");
				char num[20];
				scanf("%s", num);
				int errors = 1;
				int errors2 = 4;
				while (1) {
					if (errors > 4) {
						printf("�����������5�Σ�����Ϊ����ת��ѡ����ݽ���\n");
						return 0;//0���ص�����ѡ����ݽ���
					}
					for (i = 0; i < usern; i++) {
						if (strcmp(num, user[i].usrid) == 0) {
							printf("��¼�ɹ�\n");//�û���¼�ɹ�
							break;
						}
					}
					if (i >= usern) {//һ��16��ѧ��
						printf("ѧ���޷���ѧ������Ϣƥ�䣬�㻹��%d�λ���\n", errors2);
						scanf("%s", &num);
						errors++;
						errors2--;
					}
					if (i < usern)
					{
						strcpy(studentID, num);
						return 2;//����2��֤����ѧ�����
					}
				}
			}
			//break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {
			NormalExitProgram();
			break;
		}
		else {
			printf("��������������������룡\n");
			longjmp(j3, 1);
		}
	}
	

}