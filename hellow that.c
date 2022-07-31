include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

#define MAX 25
#define cls system("cls")

int cnt = 0;

typedef struct _student{
	int number;//학번 
	char name[MAX];//이름 
	int kor, eng, any;//점수 
	int sum;
	double avg;
	int rank;
	char r;
} student;

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int comp1(const void *a, const void *b) {//평균점수순 
	student *num1 = (student *)a;
	student *num2 = (student *)b;
	
	if(num1->avg > num2->avg) {//평균점수에 따라 등급이 정해짐 
		return -1;
	} 
	
	if(num1->avg < num2->avg) {
		return 1;
	}
	
	return 0;
}

int comp2(const void *a, const void *b) {//번호순 
	student *num1 = (student *)a;
	student *num2 = (student *)b;
	
	if(num1->number < num2->number) {//순서(1이 첫번째 여야하므로 가장작은수가 먼저 출력됨) 
		return -1;
	} 
	
	if(num1->number > num2->number) {
		return 1;
	}
	
	return 0;
}

int checkFerror(FILE *fp) {
	if(fp == NULL) return 1;
	else return 0;
}

int main() {
	FILE *fin = fopen("rank.txt", "r"), *fout1 = fopen("NumberRank.txt", "w"), *fout2 = fopen("WriteRank.txt", "w"), *fout3 = fopen("Search.txt", "w");
	int n, i, choose;
	int cnt;
	student stu[MAX];//최대 25명의 번호순 값 
	char key[MAX];
	char any;
	int is_find_on = 0;
	
	stu[0].rank = 1;//첫번째 방이 1등 
	
	if(checkFerror(fin) == 0) {
			fscanf(fin, "%d", &n);//n을 입력받음 
			for(i = 0; i < n; i++) {//n명의 학생의 점수들과 이름을 입력받음 
				fscanf(fin, "%d %s %d %d %d", &stu[i].number, stu[i].name, &stu[i].kor, &stu[i].eng, &stu[i].any);
				stu[i].sum = stu[i].kor + stu[i].eng + stu[i].any;
				stu[i].avg = stu[i].sum / 3.0;
			}
			system("cls");
			gotoxy(24, 10);
			printf("1.성적출력(번호순)");
			gotoxy(24, 11);
			printf("2.석차순 출력(정렬)");
			gotoxy(24, 12);
			printf("3.검색(이름 : 홍길동)");
			gotoxy(24, 13);
			printf("4.종료\n");
			scanf("%d", &choose);
			if(choose == 1) {
				qsort(stu, n, sizeof(student), comp2);
				cls;
				printf("처리중...");
				Sleep(1500);
				cls;
				printf("%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "번호", "이름", "국어", "영어", "수학", "총점", "평균", "등급", "등수");
				fprintf(fout1, "%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "번호", "이름", "국어", "영어", "수학", "총점", "평균", "등급", "등수");
				for(i = 0; i < n; i++) {
					if(stu[i].avg >= 10.0 && stu[i].avg <= 30.0) stu[i].r = 'F';
					if(stu[i].avg >= 30.0 && stu[i].avg <= 45.0) stu[i].r = 'E';
					if(stu[i].avg >= 45.0 && stu[i].avg <= 55.0) stu[i].r = 'D';
					if(stu[i].avg >= 55.0 && stu[i].avg <= 70.0) stu[i].r = 'C';
					if(stu[i].avg >= 70.0 && stu[i].avg <= 85.0) stu[i].r = 'B';
					if(stu[i].avg >= 85.0 && stu[i].avg <= 100.0) stu[i].r = 'A';
					printf("%d %s %d %d %d %d %.1lf %c %d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
					fprintf(fout1, "%d %s %d %d %d %d %.1lf %c %5d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
				}
				printf("잠시후 메인으로 돌아갑니다.");
				system("pause");
				system("cls");
				main();//다시 메인으로 돌아감 
			} else if(choose == 2) {
				qsort(stu, n, sizeof(student), comp1);//석차순으로 정렬 
				cls;
				printf("처리중...");
				Sleep(1500);
				cls;
				printf("%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "번호", "이름", "국어", "영어", "수학", "총점", "평균", "등급", "등수");
				for(i = 0; i < n; i++) {
					if(stu[i].avg >= 10.0 && stu[i].avg <= 30.0) stu[i].r = 'F';
					if(stu[i].avg >= 30.0 && stu[i].avg <= 45.0) stu[i].r = 'E';
					if(stu[i].avg >= 45.0 && stu[i].avg <= 55.0) stu[i].r = 'D';
					if(stu[i].avg >= 55.0 && stu[i].avg <= 70.0) stu[i].r = 'C';
					if(stu[i].avg >= 70.0 && stu[i].avg <= 85.0) stu[i].r = 'B';
					if(stu[i].avg >= 85.0 && stu[i].avg <= 100.0) stu[i].r = 'A';
					printf("%d %s %d %d %5d %5d %5d %.1lf %c %5d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
					fprintf(fout2, "%3d %s %5d %5d %5d %5d %.1lf %c %5d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
				}
				printf("아무키나 누르면 메인으로 돌아갑니다.");
				system("pause");
				system("cls");
				main();
			} else if(choose == 3) {
				printf("검색할 사람의 이름 입력 : ");
				scanf("%s", key);
				qsort(stu, n, sizeof(student), comp1);
				for(i = 0; i < n; i++) {
					if(stu[i].avg >= 10.0 && stu[i].avg <= 30.0) stu[i].r = 'F';
					if(stu[i].avg >= 30.0 && stu[i].avg <= 45.0) stu[i].r = 'E';
					if(stu[i].avg >= 45.0 && stu[i].avg <= 55.0) stu[i].r = 'D';
					if(stu[i].avg >= 55.0 && stu[i].avg <= 70.0) stu[i].r = 'C';
					if(stu[i].avg >= 70.0 && stu[i].avg <= 85.0) stu[i].r = 'B';
					if(stu[i].avg >= 85.0 && stu[i].avg <= 100.0) stu[i].r = 'A';
					if(strcmp(stu[i].name, key) == 0) {
						printf("해당사람을 찾았습니다.\n");
						system("pause");
						system("cls");
						printf("%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "번호", "이름", "국어", "영어", "수학", "총점", "평균", "등급", "등수");
						printf("%3d %s %5d %5d %5d %5d %.1lf %c %5d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
						fprintf(fout3, "마지막 검색기록...: %s의 성적", stu[i].name);
						is_find_on = 1;
					}
				}
				if(is_find_on == 0) {
					printf("찾지 못하였습니다..");
					system("pause");
					system("cls");
					main();
				} else {
					system("pause");
					system("cls");
					main();
				}
			} else if(choose == 4) {
				exit(1);
			} else {
				printf("error");
				system("pause");
				system("cls");
				return 0;
			}
		}  else {
		printf("파일이 존재하지 않습니다. rank.txt파일을 해당프로그램의 경로에 만들어서 n값과 그다음줄부터 학번, 이름, 국, 영, 수 순으로 값을 입력해주시기 바랍니다.\n");
		system("pause");
		system("cls");
		exit(1);
	}
	
	fclose(fin);
	fclose(fout1);
	fclose(fout2);
	fclose(fout3);
	
	return 0;
}
