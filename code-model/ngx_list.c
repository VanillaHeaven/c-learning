#include <stdio.h>
#include <stdlib.h>

typedef struct ngx_list_s ngx_list_t;
typedef struct ngx_list_part_s ngx_list_part_t;

struct ngx_list_s
{
    ngx_list_part_t *last;
    ngx_list_part_t  start;
    int size;
    int nalloc;
};

struct ngx_list_part_s
{
    void *elts;
    int nelts;
    ngx_list_t *next;
};

ngx_list_t *ngx_list_create(int size, int nalloc) {
    ngx_list_t *l;

    l = (ngx_list_t *) malloc(sizeof(ngx_list_t));
    if (l == NULL) {
        return NULL;
    }

    l->size = size;
    l->nalloc = nalloc;
    l->last = &l->start;
    l->start.elts = (void *) malloc(size * nalloc);
    l->start.nelts = 0;
    l->start.next = NULL;

    return l;
}