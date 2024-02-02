#include <stdio.h>
#include <stdlib.h>


struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode* deleteNode(struct ListNode* head, int val) {
    struct ListNode **indirect = &head;

    while(*indirect && (*indirect)->val != val) {
        indirect = &(*indirect)->next;
    }

    // update *indirect if target is found.
    
    *indirect = *indirect ? (*indirect)->next : NULL;

    return head;
}

int main() {
    int  n = 5, i = 0;
    int  data[5] = {1, 2, 3, 4, 5}; 
    struct ListNode *head = NULL, *node = NULL;

    head = (struct ListNode*) malloc(sizeof(struct ListNode));
    head->val = data[0];
    head->next = NULL;
    node = head;

    for (i = 1; i < n; i++) {
        node->next = (struct ListNode*) malloc(sizeof(struct ListNode));
        node = node->next;
        node->val = data[i];
        node->next = NULL;
    }

    n--;
    deleteNode(head, 3);

    node = head;
    for (i = 0; i < n; i++) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");

    return 0;
}