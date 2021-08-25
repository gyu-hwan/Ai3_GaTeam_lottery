#define _CRT_SECURE_NO_WARNINGS

#define BJY_NUM 6
int BJY_isAllOdd = 0;
int BJY_isAllEven = 0;
int BJYlottonum[BJY_NUM];

void BJY_function_lotto()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < BJY_NUM; i++) {
		BJYlottonum[i] = 1 + rand() % 45;
		for (int j = 0; j < i; j++) { //중복확인
			if (BJYlottonum[i] == BJYlottonum[j]) {
				i--; //중복 발생 시 i번째 난수 재생성
				break;
			}
		}

	}
	for (int k = 0; k < BJY_NUM; k++) //오름차순정렬
	{
		for (int i = 0; i < BJY_NUM - 1; i++) {
			if (BJYlottonum[i] > BJYlottonum[i + 1]) {
				int tmp = BJYlottonum[i];
				BJYlottonum[i] = BJYlottonum[i + 1];
				BJYlottonum[i + 1] = tmp;
			}
		}
	}
}

void BJY_function_print()
{
	printf("추첨된 번호는 ");
	for (int i = 0; i < BJY_NUM; i++)
	{
		printf("%d ", BJYlottonum[i]);
	}
	printf("입니다.\n");
}
void BJY_function_checkOddEven() // 전체 짝수 혹은 홀수 판단함수
{
	for (int i = 0; i < BJY_NUM; i++)
	{
		BJYlottonum[i] = 1 + rand() % 45;
		if (BJYlottonum[i] % 2 == 1) // 홀수라면 isAllOdd가 1증가
			BJY_isAllOdd++;

		else if (BJYlottonum[i] % 2 == 0) // 짝수라면 isAllOdd가 1증가
			BJY_isAllEven++;
	}
}
int BJY_main()
{
	Sleep(1);
	int modesel = 1;
	switch (modesel) {
	case 1:
		BJY_function_lotto();
		BJY_function_checkOddEven();
		if (BJY_isAllOdd == 6 || BJY_isAllEven == 6)//isAllOdd가 6이되면 전체홀수, isAllEven이 6이라면 전체 짝수
		{
			BJY_function_lotto(); // 전체 홀수거나 짝수면 재시행
			printf("재생성되었습니다.\n");
			BJY_function_print();
		}
		else
			BJY_function_print();
		break;
	case 2:
		exit(0);
		break;
	default: printf("다시 선택해주세요\n");

		BJYlottonum[0] == BJYlottonum[0];
	}
}