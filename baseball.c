#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* timeToString(struct tm *t);

int main() {
    int com[3] = { 0 }; 
    int user[3] = { 0 };
    int str, ball = 0, pan = 0, i, j, sh; // str: ��Ʈ����ũ ���� ball: �� ���� pan: ���� �� ���� i��j: �ݺ��� ���� sh: �޴� �޴� ���� 
    srand((int)time(NULL)); //rand() �Լ������� ������ �� �ɱ�
    struct tm *t;
    time_t timer;
    FILE *fp;

    timer = time(NULL);    // ���� �ð��� �� ������ ���
    t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
    puts("�߱� ����!!!");
menu:
    printf("\n\n\n1.��Ģ����\n2.���ӽ���\n3.��� ����\n");
    scanf("%d", &sh);
    switch (sh)
    {
    case 1 :
        printf("\n\n\n            **��Ģ**\n�� ������ ��ǻ�Ͱ� �� ���ڸ� ���ߴ� �����Դϴ�!\n��ǻ�ʹ� 0 ~ 9 ���� ���� 3���� ���ϴ�!\n���ڸ������� ball!! ��ġ�������� strike!!\n�Է��� ���� ���� ���� �Դϴ�!!\nȣ���ö� ���ذ��ȉ����� �ѹ� �غ�����!\n");
        puts("start game!\n");
        break;
    case 2 :
        puts("�� �����մϴ�!");
        puts("start game!\n");
        break;
    case 3 :
        puts("�÷����� ����Դϴ�!");
        char ch, c, date[20];
        int lpan, com1, com2, com3;
        fp = fopen("playlist.txt", "rt");
        if (fp == NULL){
            puts("����� ���´� �����߽��ϴ�\n �̰� ����� ������? Ȥ�� ���� �÷��������� ���°� �ƴұ��?");
        }else{
            
             while((c = fgetc(fp)) != EOF){
               fseek(fp, -1, SEEK_CUR);
               fscanf(fp, "%d %d %d %d %s", &lpan, &com1, &com2, &com3, date);
               printf("%d�� ���� �̱�̽��ϴ�. ����: %d %d %d %s\n", lpan, com1, com2, com3, date);               
            }
            sh = 0;
        }
        fclose(fp);
        goto menu;
    default:
        printf("���Ҹ��� �𸣰����� �ϴ� ����!!!!!\n");
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
    
    printf("\n3���� ���� �Է�:");
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
    printf("\n%d��° ������ ���: %dstrike, %dball!!!!!!\n", pan, str, ball);
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