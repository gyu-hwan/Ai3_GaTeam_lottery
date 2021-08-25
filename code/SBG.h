#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#define SBG_NUM 6		// 추첨할 번호 개수
int SBGlottonum[SBG_NUM];	//로또 번호를 담는 전역 변수
int Seq = 0;


void SBG_function_lotto() {
	// 로또 번호 생성함수
	srand((unsigned)time(NULL));	// rand 함수를 초기화. 초기화 하지 않을시 프로그램 실행시 마다 같은 숫자 뽑힘

	for (int i = 0; i < SBG_NUM; i++) {
		SBGlottonum[i] = 1 + rand() % 45;
		for (int j = 0; j < i; j++) { //중복확인
			if (SBGlottonum[i] == SBGlottonum[j]) {
				i--; //중복 발생 시 i번째 난수 재생성
				break;
			}
		}
	}
	for (int k = 0; k < SBG_NUM; k++) //오름차순정렬
	{
		for (int i = 0; i < SBG_NUM - 1; i++) {
			if (SBGlottonum[i] > SBGlottonum[i + 1]) {
				int tmp = SBGlottonum[i];
				SBGlottonum[i] = SBGlottonum[i + 1];
				SBGlottonum[i + 1] = tmp;
			}
		}
	}

}
void SBG_Count() // 연속된 수가 3번이상 나올때 다시 추첨
{
	for (int i = 1; i < SBG_NUM; i++)
	{

		if ((SBGlottonum[i + 1] - SBGlottonum[i]) - (SBGlottonum[i] - SBGlottonum[i - 1]) == 0)
			Seq++;
	}
}


void SBG_function_print() {
	//로또 번호 출력 함수
	printf("추첨된 번호는 ");

	for (int i = 0; i < SBG_NUM; i++) {
		printf("%d ", SBGlottonum[i]);
	}
	printf("입니다\n");
}
int SBG_main() {

	int modesel = 1;	// 1 로또 생성, 2 프로그램 종료


	switch (modesel) {
	case 1:
		SBG_function_lotto();	// 1 선택시 로또 번호 추첨후

		SBG_Count();
		if (Seq > 1) {
			SBG_function_lotto();
		}

		SBG_function_print();

		break;

	case 2:
		exit(0);
		break;
	default: printf("다시 선택해주세요\n");


	}


	return 0;
}

