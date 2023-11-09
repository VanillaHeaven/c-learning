#include <stdio.h>
#include <stdlib.h>

static int STACK_INIT_SIZE = 10000;

typedef struct {
    int *data;
    int size;
    int cur;
} Stack;

typedef struct {
    Stack *push;
    Stack *pop;
} CQueue;


void stackInit(Stack **s) {
    *s = (Stack *) malloc(sizeof(Stack));
    (*s)->data = (int *) calloc(STACK_INIT_SIZE, sizeof(int));
    (*s)->size = STACK_INIT_SIZE;
    (*s)->cur = -1;
}

void stackExpansion(Stack *s) {
    s->data = realloc(s->data, s->size * 2 * sizeof(int));
    s->size = s->size * 2;
}

int stackIsEmpty(Stack *s) {
    if (s->cur == -1) { return 1; }

    return 0;
}

int stackIsFull(Stack *s) {
    if (s->cur + 1 == s->size) { return 1; }

    return 0;
}

void stackPush(Stack *s, int value) {
    if (s->cur + 1 >= s->size) {
        stackExpansion(s);
    }

    s->data[++s->cur] = value;
}

int stackPop(Stack *s) {
    if (s->cur == -1) {
        return -1;
    }

    return s->data[s->cur--];
}

void stackFree(Stack *s) {
    free(s->data);
    free(s);
}

CQueue* cQueueCreate() {
    CQueue *q = (CQueue *) malloc(sizeof(CQueue));

    stackInit(&q->push);
    stackInit(&q->pop);

    return q;
}

void stackExport(Stack *from, Stack *to) {
    int value = 0;
    while((value = stackPop(from)) != -1) {
        stackPush(to, value);
    }
}

void cQueueAppendTail(CQueue* obj, int value) {
    // 如果push栈满了, 同时pop栈此时为空,
    // 就统统导出到pop栈, 减少push栈的扩容次数
    if (stackIsFull(obj->push) && stackIsEmpty(obj->pop)) {
        stackExport(obj->push, obj->pop);
    }

    stackPush(obj->push, value);
}

int cQueueDeleteHead(CQueue* obj) {
    // 弹出时, 若pop栈此时没有元素, 就从push栈导入
    if (stackIsEmpty(obj->pop)) { stackExport(obj->push, obj->pop); }

    return stackPop(obj->pop);
}

void cQueueFree(CQueue* obj) {
    stackFree(obj->pop);
    stackFree(obj->push);

    free(obj);
}

/**
 * Your CQueue struct will be instantiated and called as such:
 * CQueue* obj = cQueueCreate();
 * cQueueAppendTail(obj, value);
 
 * int param_2 = cQueueDeleteHead(obj);
 
 * cQueueFree(obj);
*/

void push(CQueue *q, int value) {
    cQueueAppendTail(q, value);
    printf("null ");
}

void pop(CQueue *q) {
    int ret = cQueueDeleteHead(q);
    printf("%d ", ret);
}

int main() {
    CQueue *q = cQueueCreate();

    push(q, 1);
    push(q, 2);
    push(q, 3);
    push(q, 4);
    push(q, 4);
    push(q, 4);
    push(q, 4);
    push(q, 4);
    push(q, 4);
    push(q, 4);
    push(q, 4);
    push(q, 4);
    push(q, 4);
    push(q, 4);
    pop(q);
    pop(q);
    pop(q);
    pop(q);

    return 0;
}