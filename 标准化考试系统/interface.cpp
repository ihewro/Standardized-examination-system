#include "declare.h"
void MainInt() {
	printf("\t********************************************\n");
	printf("\t********************************************\n");
	printf("\t**  ��ӭ��½�Զ��з�һ�廯���̿���ϵͳ    **\n");
	printf("\t**                                        **\n");
	printf("\t**                                        **\n");
	printf("\t********************************************\n");
	printf("\t**            ѡ��������                **\n");
	printf("\t**                                        **\n");
	printf("\t**              1 - ����Ա                **\n");
	printf("\t**              2 - �û�                  **\n");
	printf("\t**              3 - �˳�                  **\n");
	printf("\t********************************************\n");
	printf("\t********************************************\n");
	printf("\t**        ������  ��� 2015014278         **\n");
	printf("\t**                 ***                    **\n");
}

void AdminInt() {
	printf("\t**        ��ӭ���������棡\t**        \n\n");
	printf("������Ų���\n1 - �����\n2 - �Ծ���\n3 - ѧ�����\n4 - ������һ��\n5 - ��������\n");
	char inpute[40];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {//ѧ�����
			ExambankInt();
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {//�Ծ���
			TestbankInt();
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {//ѧ�����
			QuerybyAdminInt();
			break;
		}
		else if (inpute[0] == '4'&& inpute[1] == '\0') {//������һ��
			printf("���ڷ�����һ������ȴ�...\n");
			Sleep(1000);
			system("cls");
			main();
			break;
		}
		else if (inpute[0] == '5'&& inpute[1] == '\0') {//��������
			NormalExitProgram();
		}
		else {
			printf("�������������������ȷ�����\n");
		}
	}
}
void UserInt(char num[20]) {
	printf("\t**        %s,���ã���ӭ����ѧ������\t**        \n\n", num);
	printf("1 - ��ѯ�ɼ�\n2 - ���뿼��\n3 - ������һ��\n4 - ��������\n");
	char inpute[40];
	while (1) {
		scanf("%s", inpute);
		if (inpute[0] == '1'&& inpute[1] == '\0') {
			QuerybyStuInt();
			break;
		}
		else if (inpute[0] == '2'&& inpute[1] == '\0') {
			TakingtestInt();
			break;
		}
		else if (inpute[0] == '3'&& inpute[1] == '\0') {
			printf("���ڷ�����һ������ȴ�...\n");
			Sleep(1000);
			system("cls");
			main();
			break;
		}
		else if (inpute[0] == '4'&& inpute[1] == '\0') {
			NormalExitProgram();
			break;
		}
		else {
			printf("�������������������ȷ�����\n");
		}
	}
}
void NormalExitProgram() {
	printf("\t    ллʹ�øó��򣡳����Ѿ������˳�\n");
	exit(0);
}


