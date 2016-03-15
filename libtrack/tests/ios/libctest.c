#include <stdio.h>

static int k;

//__attribute__((visibility("hidden")))
void fff(void)
{
    int a=1;
    a++;
    printf("ORIGINAL:a is:%d\n", a);
}

//__attribute__((visibility("hidden"))) void ctest1(int *a){
void ctest1(int *a){
    fff();
    printf("ORIGINAL:\"a\" value is:%d\n",*a);
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
