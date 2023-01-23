#include <stdio.h>

int romanToInt(char * s) {
    int i = -1;
    int result = 0;

    while (s[++i] != '\0') {
        switch (s[i])
        {
        case 'V':
            result += 5;
            break;

        case 'L':
            result += 50;
            break;

        case 'D':
            result += 500;
            break;

        case 'M':
            result += 1000;
            break;

        case 'I':
            switch (s[++i])
            {
            case 'V':
                result += 4;
                break;
                
            case 'X':
                result +=9;
                break;
            
            default:
                result +=1;
                --i;
                break;
            }
            break;

        case 'X':
            switch (s[++i])
            {
            case 'L':
                result += 40;
                break;
                
            case 'C':
                result +=90;
                break;
            
            default:
                result +=10;
                --i;
                break;
            }
            break;

        case 'C':
            switch (s[++i])
            {
            case 'D':
                result += 400;
                break;
                
            case 'M':
                result +=900;
                break;
            
            default:
                result +=100;
                --i;
                break;
            }
            break;
        
        default:
            break;
        }
    }

    return result;
}

int main() {
    char *s = "IX";

    printf("%d\n", romanToInt(s));
    return 0;
}