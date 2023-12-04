#include<stdio.h>
#include<stdlib.h>


int digit(int n) {
    int res = 0;
    while (n > 0) {
        res += n % 10;
        n /= 10;
    }
    return res;
}


int wardrobeFinishing(int m, int n, int cnt) {
    if (cnt == 0) return 1;

    int i = 0, j = 0;
    int count = 0;
    char **wardrobe = NULL;

    // init wardrobe
    wardrobe = (char **) malloc(m * sizeof(char *));
    for (i = 0; i < m; i++) {
        wardrobe[i] = (char *) calloc(n, sizeof(char));
    }

    wardrobe[0][0] = 1;
    count = 1;

    // travel wardrobe
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (digit(i) + digit(j) <= cnt) {
                if (j - 1 >= 0 && wardrobe[i][j - 1] == 1) {
                    wardrobe[i][j] = 1;
                    count++;
                } else if (i - 1 >= 0 && wardrobe[i - 1][j] == 1) {
                    wardrobe[i][j] = 1;
                    count++;
                }
            }
        }
    }

    // travel wardrobe
    printf("   ");
    for (j = 0; j < n; j ++) {
        printf("%3d", j);
    }
    printf("\n");

    for (i = 0; i < m; i++) {
        printf("%3d", i);
        for (j = 0; j < n; j++) {
            printf("%3d", wardrobe[i][j]);
        }
        printf("\n");
    }

    return count;
}


int main() {
    int m = 38;
    int n = 15;
    int cnt = 9;

    printf("%d\n", wardrobeFinishing(m, n, cnt));
    return 0;
}