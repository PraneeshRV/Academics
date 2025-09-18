#include<stdio.h>
char low_to_upper(char c1)
{
        char c2;
        c2=(c1>='a'&& c1<='z')?('A'+c1-'a'):c1;
        return(c2);
}
int main()
{
        char l,u;
        scanf("%c", &l);
        u=low_to_upper(l);
        printf("%c",u);
}