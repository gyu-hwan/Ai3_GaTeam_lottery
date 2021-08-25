
#include<stdio.h>
#include <math.h>
#include<stdlib.h>
#include<time.h>

#define YYG_NUM 6  // 추첨할 번호 개수
int YYG_lottonum[YYG_NUM]; //로또 번호를 담는 전역 변수
double YYG_arr[45];


double YYG_Lotto_History(int num);
double YYG_Average(double num[]);   // SSS 45개의 숫자 평균구하는 합수
double YYG_SD(double num[]);        // SSS 평균을 이용하여 표준편차^2 구하는 함수
void YYG_SSSFunction_Lotto();       // SSS 표준편차를 이용하여 로또 뽑는함수 
void YYG_Function_Lotto();
void YYG_Function_Print();
void YJFucntion_Lotto();


int YYG_main() {

    int i = 0;

    while (i < 45) {          //SSS 번호별 당첨횟수 배열 생성
        YYG_arr[i] = YYG_Lotto_History(i + 1);
        i++;
    }

        switch (1) {
        case 1:
            printf("\nYJ의 번호를 생성합니다!\n\n");
            YJFucntion_Lotto();    // YJ코드
            YYG_Function_Print();       // 번호 출력

            break;

        case 2:
            YYG_Function_Lotto(); // 2 선택시 로또 번호 추첨후
            YYG_Function_Print(); // 추첨된 번호 출력

            break;
        case 3:
            exit(0);   //3 선택시 종료
            break;
        default: printf("다시 선택해주세요\n");


        }

    return 0;
}


void YYG_Function_Lotto() {
    // 로또 번호 생성함수
    srand((unsigned)time(NULL)); // rand 함수를 초기화. 초기화 하지 않을시 프로그램 실행시 마다 같은 숫자 뽑힘

    for (int i = 0; i < YYG_NUM; i++) {
        YYG_lottonum[i] = 1 + rand() % 45;

    }
}


void YJFucntion_Lotto() {    //윤영준 코드
    int num = 0;
    srand((unsigned)time(NULL)); //rand 함수 초기화

    while (1) {
        num = 0;
        for (int i = 0; i < YYG_NUM; i++) {
            YYG_lottonum[i] = 1 + rand() % 45;
            if (YYG_lottonum[i] < 10) {
                num++;
            }
        }
        if (num != 6) {
            break;
        }
        printf("\n리셋!\n");
    }
}


void YYG_Function_Print() {
    //로또 번호 출력 함수
    printf("\n***추첨된 번호는 ");

    for (int i = 0; i < YYG_NUM; i++) {
        printf("%d ", YYG_lottonum[i]);
    }
    printf("입니다***\n");
}






double YYG_Average(double num[]) {  //SSS 당첨횟수의 평균 계산

    double result = 0.0;

    for (int i = 0; i < 45; i++)
        result += num[i];

    return result / 45.0;

}


double YYG_SD(double num[]) {   //SSS 당첨횟수의 표준편차 계산

    double result = 0.0;

    for (int i = 0; i < 45; i++)

        result += num[i] * num[i];

    return (result / 45.0) - (YYG_Average(num) * YYG_Average(num));
}

void YYG_SSSFunction_Lotto() {      // SSS 새로운 번호추첨 함수
    // 로또 번호 생성함수
    srand((unsigned)time(NULL));    // rand 함수를 초기화. 초기화 하지 않을시 프로그램 실행시 마다 같은 숫자 뽑힘

    for (int i = 0; i < YYG_NUM; i++) {
        YYG_lottonum[i] = 1 + rand() % 45;
        if ((YYG_Lotto_History(YYG_lottonum[i]) < (YYG_Average(YYG_arr) - sqrt(YYG_SD(YYG_arr))))) {    //SSS 뽑은 번호가 당첨된 횟수가 (평균-표준편차)보다 작으면 
            if (rand() % 2) {                                                   //SSS 1/2확률로 탈락을 결정
                printf("%d번은 최근 %.0lf번 당첨! %lf 보다 적음으로 탈락! \n", YYG_lottonum[i], YYG_Lotto_History(YYG_lottonum[i]), (YYG_Average(YYG_arr) - sqrt(YYG_SD(YYG_arr))));
                i--;
            }
        }
    }
}

double YYG_Lotto_History(int num) {    //SSS 번호별 로또 당첨횟수 677~977회 까지
    switch (num) {
    case 1:
        return 44;
        break;
    case 2:
        return 52;
        break;
    case 3:
        return 49;
        break;
    case 4:
        return 49;
        break;
    case 5:
        return 40;
        break;
    case 6:
        return 49;
        break;
    case 7:
        return 43;
        break;
    case 8:
        return 33;
        break;
    case 9:
        return 43;
        break;
    case 10:
        return 57;
        break;
    case 11:
        return 47;
        break;
    case 12:
        return 62;
        break;
    case 13:
        return 49;
        break;
    case 14:
        return 44;
        break;
    case 15:
        return 46;
        break;
    case 16:
        return 51;
        break;
    case 17:
        return 49;
        break;
    case 18:
        return 54;
        break;
    case 19:
        return 47;
        break;
    case 20:
        return 34;
        break;
    case 21:
        return 54;
        break;
    case 22:
        return 40;
        break;
    case 23:
        return 38;
        break;
    case 24:
        return 51;
        break;
    case 25:
        return 37;
        break;
    case 26:
        return 43;
        break;
    case 27:
        return 40;
        break;
    case 28:
        return 48;
        break;
    case 29:
        return 41;
        break;
    case 30:
        return 52;
        break;
    case 31:
        return 44;
        break;
    case 32:
        return 42;
        break;
    case 33:
        return 53;
        break;
    case 34:
        return 54;
        break;
    case 35:
        return 45;
        break;
    case 36:
        return 52;
        break;
    case 37:
        return 40;
        break;
    case 38:
        return 55;
        break;
    case 39:
        return 54;
        break;
    case 40:
        return 37;
        break;
    case 41:
        return 44;
        break;
    case 42:
        return 51;
        break;
    case 43:
        return 58;
        break;
    case 44:
        return 43;
        break;
    case 45:
        return 49;
        break;
    default:
        return 0;
        break;

    }

}