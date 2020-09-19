#include<stdio.h>
using namespace std;


void my_getc(){
    int ch;
    printf("please input a charactor\n");
    ch=getc(stdin);
    printf("your input is : %c\n", ch);
    return;
}

void my_getchar(){
    int ch;
    ch=getchar();
    printf("your input is : %c\n", ch);
}

int main(){
    my_getc();
}