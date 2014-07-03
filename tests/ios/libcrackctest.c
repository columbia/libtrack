#include <stdio.h>

static int k;

void fff(void)
{
    int a=1;
    a++;
    printf("CRACKED-fff: a is:%d\n", a);
}

void ctest1(int *a){
    printf("CRACKED: \"a\" value is:%d\n",*a);
    *a = 666;
}

int main(int argc, char** argv)
{
    printf("ds");
    fff();
    k=0;
    k++;
    return k;
}
