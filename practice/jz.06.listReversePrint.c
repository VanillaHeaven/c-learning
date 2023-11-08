#include <stdio.h>
#include <stdlib.h>

typedef struct single_list_node_s single_list_node;
typedef struct single_list_s single_list;

struct single_list_node_s {
    int               value;
    single_list_node *next;
};

struct single_list_s {
    single_list_node *head;
};

typedef struct double_list_node_s double_list_node;

struct double_list_node_s {
    int              value;
    double_list_node *prev;
    double_list_node *next;
};

// 遍历一遍链表，获取链表长度，创建数组
// 第二次遍历链表，从尾到头插入数组
int *single_list_reverse_print(single_list_node **sl) {
    int *res = NULL;
    int  i = 0;
    int  len = 0;

    single_list_node *sln = *sl;

    for (; sln != NULL; sln = sln->next) len++;

    res = (int *) calloc(len, sizeof(int));

    for (sln = *sl, i = 1; sln != NULL; sln = sln->next, i++) {
        res[len - i] = sln->value;
    }

    return res;
}

void single_list_push_head(single_list_node **sl, int value) {
    single_list_node *sln = (single_list_node *) malloc(sizeof(single_list_node));
    sln->value = value;
    sln->next = *sl;
    *sl = sln;
}

void single_list_push_tail(single_list_node **sl, int value) {
    single_list_node *sln = *sl;

    if (sln == NULL) {
        *sl = (single_list_node *) malloc(sizeof(single_list_node));
        (*sl)->value = value;
        (*sl)->next = NULL;
        return;
    }

    while (sln->next) {
        sln = sln->next;
    }

    sln->next = (single_list_node *) malloc(sizeof(single_list_node));
    sln = sln->next;
    sln->value = value;
    sln->next = NULL;
}

void single_list_insert(single_list_node **sl, int value) {
    single_list_node *nsln = (single_list_node *) malloc(sizeof(single_list_node));
    nsln->value = value;
    nsln->next = (*sl)->next;
    (*sl)->next = nsln;
}

void single_list_free(single_list_node **sl) {
    single_list_node *sln = *sl;

    while (sln) {
        *sl = (*sl)->next;
        free(sln);
        sln = *sl;
    }
}

void double_list_push_tail(double_list_node *dl, int value) {
    double_list_node *dln = (double_list_node *) malloc(sizeof(double_list_node));
    dln->value = value;
    dln->next = dl;
    dln->prev = dl->prev;
    dl->prev->next = dln;
    dl->prev = dln;
}

void double_list_push_head(double_list_node *dl, int value) {
    double_list_node *dln = (double_list_node *) malloc(sizeof(double_list_node));
    dln->value = value;
    dln->next = dl->next;
    dln->prev = dl;
    dl->next->prev = dln;
    dl->next = dln;
}

void double_list_free(double_list_node *dl) {
    double_list_node *dln = NULL;

    while (dl->next != dl) {
        dln = dl->next;
        dl->next = dl->next->next;
        dl->next->prev = dl;
        free(dln);
    }
}

int *double_list_reverse_print(double_list_node *dl) {
    int *res = NULL;
    int  i = 0;
    int  len = 0;

    double_list_node *dln = dl->next;

    while (dln != dl) {
        len++;
        dln = dln->next;
    }

    res = (int *) calloc(len, sizeof(int));

    for (dln = dl->prev, i = 0; dln != dl; dln = dln->prev, i++) {
        res[i] = dln->value;
    }

    return res;
}

int main() {
    int     *res = NULL;
    int     len = 10;
    int       i = 0;
    int  data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    single_list_node *sl;
    single_list_node **slnpp = &sl;

    for (i = 0; i < len; i++) {
        single_list_push_tail(&sl, data[i]);
    }

    res = single_list_reverse_print(&sl);

    for (i = 0; i < len; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free(res);
    single_list_free(&sl);

    double_list_node *dl = NULL;
    dl = (double_list_node *) malloc(sizeof(double_list_node));
    dl->value = 0;
    dl->next = dl;
    dl->prev = dl;

    for (i = 0; i < len; i++) {
        double_list_push_tail(dl, data[i]);
    }

    res = double_list_reverse_print(dl);
    for (i = 0; i < len; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free(res);
    double_list_free(dl);

    return 0;
}