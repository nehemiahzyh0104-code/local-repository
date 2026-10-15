#include <stdio.h>

typedef struct
{
    char *name;
    char *num;
    float score;
} Exam;

Exam createstu(char *n,char* nu,float s){
    Exam stu = {n,nu,s};
    return stu;
}

int
main()
{
    Exam stu=createstu("Tom","31",60);
    printf("%s's score is %.1f.",stu.name,stu.score);
    return 0;
}
