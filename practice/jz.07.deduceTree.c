#include <stdio.h>
#include <stdlib.h>


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


struct TreeNode* deduceTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    if (inorderSize <= 0) { return NULL; }

    // 根据根节点, 找到左右子树分界
    int i = 0;
    struct TreeNode *tn = NULL;

    // TODO: 一定能找到对应节点, 这里先忽略异常情况
    for (; i < inorderSize; i++)
        if (inorder[i] == *preorder) { break; }

    // 创建节点
    tn = (struct TreeNode *) malloc(sizeof(struct TreeNode));
    tn->val = inorder[i];

    // 递归建立左子树
    tn->left = deduceTree(preorder + 1, i, inorder, i);
    // 递归建立右子树
    tn->right = deduceTree(preorder + (i + 1), preorderSize - (i + 1), inorder + i + 1, inorderSize - (i + 1));

    return tn;
}

typedef struct listnode_s listnode;

struct listnode_s {
    struct TreeNode *tn;
    listnode *next;
};

typedef struct list_s list;

struct list_s
{
    listnode *head;
    listnode *tail;
};

void listInsertTail(list *l, struct TreeNode *tn) {
    listnode *ln = (listnode *) malloc(sizeof(listnode));
    ln->tn = tn;
    ln->next = NULL;

    if (l->tail != NULL) {
        l->tail->next = ln;
    } else {
        l->head = ln;
    }

    l->tail = ln;
}

struct TreeNode *listDeleteHead(list *l) {
    listnode *ln = l->head;
    struct TreeNode *tn = NULL;

    if (l->head != NULL) {
        l->head = l->head->next;
        if (l->head == NULL) {
            l->tail = NULL;
        }
        tn = ln->tn;
        free(ln); 
    }
    
    return tn;
}

list *listCreate() {
    list *l = (list *) malloc(sizeof(list));
    l->head = NULL;
    l->tail = NULL;

    return l;
}

int listNotEmpty(list *l) {
    if (l->head != NULL) {
        return 1;
    }

    return 0;
}

void printTreeNode(struct TreeNode * root) {
    struct TreeNode *tn = NULL;
    list *l = listCreate();

    listInsertTail(l, root);

    while (listNotEmpty(l)) {
        tn = listDeleteHead(l);
        printf("%d ", tn->val);

        if (tn->left) {
            listInsertTail(l, tn->left);
        }

        if (tn->right) {
            listInsertTail(l, tn->right);
        }
    }

} 

int main() {
    int len = 5;
    int preorder[] = {3,9,20,15,7};
    int inorder[] = {9,3,15,20,7};

    struct TreeNode *root = deduceTree(preorder, len, inorder, len);

    printTreeNode(root);

    return 0;
} 