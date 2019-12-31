#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* timeToString(struct tm *t);

int main() {
    int com[3] = { 0 }; 
    int user[3] = { 0 };
    int str, ball = 0, pan = 0, i, j, sh; // str: 스트라이크 변수 ball: 볼 변수 pan: 라운드 수 변수 i와j: 반복문 변수 sh: 메뉴 받는 변수 
    srand((int)time(NULL)); //rand() 함수를위한 임의의 수 심기
    struct tm *t;
    time_t timer;
    FILE *fp;

    timer = time(NULL);    // 현재 시각을 초 단위로 얻기
    t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기
    puts("야구 게임!!!");
menu:
    printf("\n\n\n1.규칙보기\n2.게임시작\n3.기록 보기\n");
    scanf("%d", &sh);
    switch (sh)
    {
    case 1 :
        printf("\n\n\n            **규칙**\n이 게임은 컴퓨터가 고른 숫자를 맞추는 게임입니다!\n컴퓨터는 0 ~ 9 까지 숫자 3개를 고릅니다!\n숫자만맞으면 ball!! 위치도맞으면 strike!!\n입력은 숫자 숫자 숫자 입니다!!\n호옥시라도 이해가안됬으면 한번 해보세요!\n");
        puts("start game!\n");
        break;
    case 2 :
        puts("네 시작합니다!");
        puts("start game!\n");
        break;
    case 3 :
        puts("플레이한 기록입니다!");
        char ch, c, date[20];
        int lpan, com1, com2, com3;
        fp = fopen("playlist.txt", "rt");
        if (fp == NULL){
            puts("기록을 여는대 실패했습니다\n 이게 어찌된 일이죠? 혹시 전에 플래이한적이 없는것 아닐까요?");
        }else{
            
             while((c = fgetc(fp)) != EOF){
               fseek(fp, -1, SEEK_CUR);
               fscanf(fp, "%d %d %d %d %s", &lpan, &com1, &com2, &com3, date);
               printf("%d판 만에 이기셨습니다. 정답: %d %d %d %s\n", lpan, com1, com2, com3, date);               
            }
            sh = 0;
        }
        fclose(fp);
        goto menu;
    default:
        printf("뭔소린진 모르겠지만 일단 시작!!!!!\n");
        break;
    }
    for(i=0; i<3;i++){

        com[i] = rand()%10;      
        if( i == 1 && (com[0]==com[1])){
            i--;
        } else if ( i ==2 && ((com[0]==com[2]) || (com[1]==com[2])))
            i--;
    }
start:
    pan++;
    str = 0;
    ball = 0;
    
    printf("\n3개의 숫자 입력:");
    scanf("%d %d %d", &user[0], &user[1], &user[2]);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (user[i] == com[i]) {
                str++;
                break;
            }
            else if (user[i] == com[j]) {
                ball++;
                break;
            }
        }
    }
    printf("\n%d번째 도전의 결과: %dstrike, %dball!!!!!!\n", pan, str, ball);
    if (str == 3) {
        fp = fopen("playlist.txt ", "at");
        fprintf(fp, "%d %d %d %d %s\n", pan, com[0], com[1], com[2], timeToString(t));
        fclose(fp);
        printf("GAME OVER\n");
        system("pause");
        return 0;
    }
    else
        goto start;

}

char* timeToString(struct tm *t) {
  static char s[20];

  sprintf(s, "%04d/%02d/%02d-%02d:%02d:%02d",
              t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
              t->tm_hour, t->tm_min, t->tm_sec
          );

  return s;
}