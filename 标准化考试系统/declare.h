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
* 数据结构
*/
//题库
typedef struct {
	char name[200];//题目名称
	int QuesNum;//题库内的题目数量
}ST_exambank;

//选择题
typedef struct
{
	char ask[200];//题干
	char answer[4][200];//4个选项
	char right[200];//正确答案
}ChooseQues;

//填空题
typedef struct
{
	char ask[200];//题干
	char right[200];//正确答案
}BankQues;


//计算题
typedef struct
{
	char ask[200];//题干
	char right[200];//正确答案
}CalcuQues;

//用户输入的答案
typedef struct {
	char right[200];//用户输入的答案
}AnswerbyUser;

//试卷
typedef struct {
	char name[200];//试卷名称
	int value[3];//试卷题型的分值
	int num;//试卷的编号,随机获取的唯一编号
}ST_test;

//学生
typedef struct {
	char id[20];
	int exams[20];//学生参加的试卷编号
	int exams_score[20];//学生参加试卷的成绩
	int testnumbers;//参加的试卷次数
}ST_student;

typedef struct {
	char usrid[20];
}StudentId;

typedef struct {
	char id[20];
	int socre;
}ST_currenttest_student;


/*
* 函数申明
*/

/*主函数和界面函数*/
int main();
int SelectId();
void MainInt();

/*管理界面*/
void AdminInt();
//题库板块
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

//试卷板块
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

//学生板块
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

/*学生界面*/
void UserInt(char num[20]);

/*退出程序*/
void NormalExitProgram();

/*快速排序算法*/
void QuickSort(ST_currenttest_student currenttest_student[100]);
void Qsort(ST_currenttest_student currenttest_student[100], int low, int high);
int Partition(ST_currenttest_student currenttest_student[100], int low, int high);
void swap(ST_currenttest_student currenttest_student[100], int i, int j);