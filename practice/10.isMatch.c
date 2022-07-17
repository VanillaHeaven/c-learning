#include <stdio.h>
#include <stdlib.h>

#define TEST              1
#define DP_SIZE           4

#define S_UMATCH          0b0000
#define S_USED            0b0001
#define S_UNUSED          0b0010
#define P_UNUSED          0b0100

#define TYPE_MASK         0b10000000
#define NORMAL_CHAR(x)    (x & TYPE_MASK) != TYPE_MASK
#define WILDCARD_CHAR(x)  (x & TYPE_MASK) == TYPE_MASK
#define CHAR_EQUAL(x, y)  ((x & 0b01111111) == y || (x & 0b01111111) == '.')


typedef u_char      u_char;
typedef struct test_case_s test_case_t;

struct test_case_s
{
    char *s;
    char *r;
    int   a;
};

typedef struct dp_s dp_t;
typedef void   (*dp_init)(dp_t *dp, int i, int j, int size);
typedef u_char (*dp_get)(dp_t *dp, int i, int j);
typedef void   (*dp_set)(dp_t *dp, int i, int j, int value);
typedef void   (*dp_free)(dp_t *dp);

struct dp_s
{
    u_char  *buf;
    int      row;
    u_char   size;
    u_char   mask;
    dp_init  init;
    dp_get   get;
    dp_set   set;
    dp_free  free;
};

int     isMatch(char *, char *);
u_char *regexComjle(char *, int *);
void    init(dp_t *dp, int i, int j, int size);
u_char  get(dp_t *dp, int i, int j);
void    set(dp_t *dp, int i, int j, int value);
void    clean(dp_t *dp);
int     my_pow(int x, int n);
#if (TEST)
int     get_binary(int n);
#endif


void
main(int argc, void **argv) {

    test_case_t test_cases[] = {
        {"aa", "a", 1},
        {NULL, NULL, 0}
    };

    int i = 0;

    for(; test_cases[i].s != NULL; i++) {
        printf("测试用例: %s\n", test_cases[i].s);
        printf("是否匹配: %d\n", isMatch(test_cases[i].s, test_cases[i].r));
        printf("\n");
    }

    return;
}


int
isMatch(char *s, char *p)
{
    u_char         *pt    = NULL;
    int             pl    = 0;
    int             sl    = -1;
    int             i     = -1;
    int             j     = -1;
    dp_t            dp;

    pt = regexComjle(p, &pl);

    while (s[++sl]);

    dp.init = init;
    dp.set  = set;
    dp.get  = get;
    dp.free = clean;

    dp.init(&dp, pl, sl, DP_SIZE);

    j = -1;
    while (++j < sl)
    {
#if (TEST)
        printf("_%c_", s[j]);
#endif
        i = -1;
        while (++i < pl) {
            if (dp.get(&dp, i, j - 1) & P_UNUSED) {
                if CHAR_EQUAL(pt[i], s[j]) {
                    dp.set(&dp, i, j, P_UNUSED | S_UNUSED);
                } else {
                    dp.set(&dp, i, j, S_UNUSED);
                }
            }

            if (dp.get(&dp, i - 1, j) & (S_USED | P_UNUSED)) {
                if (WILDCARD_CHAR(pt[i])) {
                    dp.set(&dp, i, j, P_UNUSED);
                }
            }
            
            if ((dp.get(&dp, i - 1, j) & S_UNUSED)
                || (dp.get(&dp, i - 1, j - 1) & S_USED)
               )
            {
                if (NORMAL_CHAR(pt[i]) && CHAR_EQUAL(pt[i], s[j])) {
                    dp.set(&dp, i, j, S_USED);
                } else if (WILDCARD_CHAR(pt[i]) && CHAR_EQUAL(pt[i], s[j])) {
                    dp.set(&dp, i, j, P_UNUSED | S_UNUSED);
                } else if (WILDCARD_CHAR(pt[i])) {
                    dp.set(&dp, i, j, S_UNUSED);
                }
            }

#if (TEST)
            printf("|_%03d_", get_binary(dp.get(&dp, i, j)));
#endif
        }
#if (TEST)
        printf("\n");
#endif
    }

#if (TEST)
    printf("\n");
#endif

    if (dp.get(&dp, pl - 1, sl - 1) & (P_UNUSED | S_USED)) {
        dp.free(&dp);
        return 1;
    }

    dp.free(&dp);
    return 0;
}


u_char *
regexComjle(char *p, int *len)
{
    int            i = -1;
    int            j = -1;
    int            pl = -1;
    u_char        *pt = NULL;

    while (p[++pl] != '\0')
        if (p[pl] != '*') (*len)++;

    pt = (char *) calloc(*len, 1);
    
#if (TEST)
    printf("___");
#endif

    while (p[++i] != '\0') {
        pt[++j] = p[i];

        if (i + 1 < pl && p[i + 1] == '*') {
            pt[j] = pt[j] | TYPE_MASK;
            i++;
        }

#if (TEST)
        if (NORMAL_CHAR(pt[j])) {
            printf("|__%c__", (TYPE_MASK - 1) & pt[j]);
        } else {
            printf("|__%c*_", (TYPE_MASK - 1) & pt[j]);
        }
#endif
    }
    
#if (TEST)
    printf("\n");
#endif
    return pt;
}


void
init(dp_t *dp, int i, int j, int size)
{
    dp->size = size;
    dp->row  = i;
    dp->mask = my_pow(2, size) - 1;
    dp->buf  = (u_char *) calloc((i * j * size + 7) / 8, 1);
}


u_char
get(dp_t *dp, int i, int j)
{
    if (i < 0 && j < 0) return 1;
    if (i < 0 || j < 0) return 0;

    int    bits   = (i + dp->row * j) * dp->size;
    size_t align  = (size_t) (dp->buf + bits / 8);
    u_char offset = my_pow(2, bits % 8);
    u_char mask   = dp->mask * offset;
    return (*(u_char *) align & mask) / offset;
}


void
set(dp_t *dp, int i, int j, int value)
{
    int    bits   = (i + dp->row * j) * dp->size;
    size_t align  = (size_t) (dp->buf + bits / 8);
    u_char offset = my_pow(2, bits % 8);
    *(u_char *) align |= value * offset;
}


void
clean(dp_t *dp)
{
    free(dp->buf);
}


int
my_pow(int x, int n)
{
    int a = 1;

    while (n--) a *= x;

    return a;
}


#if (TEST)
int
get_binary(int n) 
{ 
	if(n > 1) 
		return get_binary(n / 2) * 10 + n % 2; 
	else 
		return n; 
}  
#endif