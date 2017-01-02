#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <setjmp.h>
#include <time.h>
#include <windows.h>
#include <io.h>



/*
* ���ݽṹ
*/
//���
typedef struct {
	char name[200];//��Ŀ����
	int QuesNum;//����ڵ���Ŀ����
}ST_exambank;

//ѡ����
typedef struct
{
	char ask[200];//���
	char answer[4][200];//4��ѡ��
	char right[200];//��ȷ��
}ChooseQues;

//�����
typedef struct
{
	char ask[200];//���
	char right[200];//��ȷ��
}BankQues;


//������
typedef struct
{
	char ask[200];//���
	char right[200];//��ȷ��
}CalcuQues;

//�û�����Ĵ�
typedef struct {
	char right[200];//�û�����Ĵ�
}AnswerbyUser;

//�Ծ�
typedef struct {
	char name[200];//�Ծ�����
	int value[3];//�Ծ����͵ķ�ֵ
	int num;//�Ծ�ı��,�����ȡ��Ψһ���
}ST_test;

//ѧ��
typedef struct {
	char id[20];
	int exams[20];//ѧ���μӵ��Ծ���
	int exams_score[20];//ѧ���μ��Ծ�ĳɼ�
	int testnumbers;//�μӵ��Ծ����
}ST_student;

typedef struct {
	char usrid[20];
}StudentId;

typedef struct {
	char id[20];
	int socre;
}ST_currenttest_student;


/*
* ��������
*/

/*�������ͽ��溯��*/
int main();
int SelectId();
void MainInt();

/*�������*/
void AdminInt();
//�����
void ExambankInt();
void ExambankNoneInt();
void ExambankHaveInt();
void ExambankCreat();
void ChooseQuesAdd();
void BankQuesAdd();
void CalcuQuesAdd();
int ChooseQuesList();
int BankQuesList();
int CalcuQuesList();
void ExambankOperate();
void ExambankModify();
void ChooseQuesOperate();
void BankQuesOperate();
void CalcuQuesOperate();
void ExambankDelete();
void ExmanbankQuesList();
void ExambankList();
void ChooseQuesModify();
void ChooseQuesDelete();
void BankQuesModify();
void BankQuesDelete();
void CalcuQuesModify();
void CalcuQuesDelete();
void GetCurrent_exambankName(char exambankname[60]);
void InitCurrent_exambank(ST_exambank *current_exambank);
void GetquestionsfileName(char choosequesfilename[60], int n);

//�Ծ���
void TestbankInt();
void TestbankNoneInt(FILE *fp);
void TestbankHaveInt(FILE *fp);
void TestCreat();
int TestList();
void InitCurrent_test(ST_test *current_test);
void ChooseQuesSelect();
void BankQuesSelect();
void CalcuQuesSelect();
void TestOperate();
void TestQuesList();
void TestDelete();
int test_ChooseQuesList();
void test_ChooseQuesOperate();
int test_BankQuesList();
int test_CalcuQuesList();
void test_BankQuesOperate();
void test_CalcuQuesOperate();
void test_GetquestionsfileName(char quesfilename[60], int n);
void test_ChooseQuesDelete();
void test_BankQuesDelete();
void test_CalcuQuesDelete();
int RandomTestnum();
void QuerybyAdminInt();
void QuerybyTest();
void QuerybyStu();

//ѧ�����
void TakingtestInt();
void AnswerChooseques();
void AnswerBankques();
void AnswerCalcuques();
void Evaluateques();
void EvaluateChooseques();
void EvaluateBankques();
void EvaluateCalcuques();
void Gradesave();
int Checkstudentstatus();
void QuerybyStuInt();

/*ѧ������*/
void UserInt(char num[20]);

/*�˳�����*/
void NormalExitProgram();

/*���������㷨*/
void QuickSort(ST_currenttest_student currenttest_student[100]);
void Qsort(ST_currenttest_student currenttest_student[100], int low, int high);
int Partition(ST_currenttest_student currenttest_student[100], int low, int high);
void swap(ST_currenttest_student currenttest_student[100], int i, int j);