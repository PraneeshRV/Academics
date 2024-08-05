#include <stdio.h>
#include <stdbool.h>
 
int main(void)
{
    char a = 'C';                                           // single character  %c
    char b[] = "Bro";                                       // array of characters  %s

    float c = 3.141592;                                     // 4 bytes (32 bits of precision) 6 - 7 digits  %f
    double d = 3.141592653589793;                           // 8 bytes (64 bits of precision) 15 - 16 digits  %lf

    bool e = false;                                         // 1 byte (true = 1 or false = 0)  %d

    char f = 100;                                           // 1 byte (-128 to +127)  %d or %c
    unsigned char g = 255;                                  // 1 byte (0 to +255)  %d or %c

    short h = 32767;                                        // 2 bytes (-32,768 to +32,767)  %d
    unsigned short i = 65535;                               // 2 bytes (0 to +65,535)  %d

    int j = 2147483647;                                     // 4 bytes (-2,147,483,648 to +2,147,483,647) %d
    unsigned int k = 4294967295;                            // 4 bytes (0 to +4,294,967,295) %d

    long long int l = 9223372036854775807;                  // 8 bytes (-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807) %lld
    unsigned long long int m = 18446744073709551615U;        // 8 bytes (0 to 18,446,744,073,709,551,615) %llu


    printf("%c\n", a);
    printf("%s\n", b);
    printf("%f\n", c);
    printf("%0.15lf\n", d);         // float starts to lose its precision after 6 - 7 digits
                                    // and the 0.15 denotes number of digits after decimal point

    printf("%d\n", e);
    printf("%c\n", f);              // using %d prints the decimal value and using %c converts the number
                                    // to hexadecimal, and then prints the ASCII character corresponding to
                                    // the hexadecimal number

    printf("%d\n", g);              // when the value exceeds the higher limit, we get a overflow warning and the 
                                    // minimum value is printed

    printf("%d\n", h);
    printf("%d\n", i);
    printf("%d\n", j);
    printf("%d\n", k);
    printf("%lld\n", l);
    printf("%llu\n", m);

}