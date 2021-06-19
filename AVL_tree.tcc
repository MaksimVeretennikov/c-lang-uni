#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    int data;
    unsigned char height;
    struct node* left;
    struct node* right;
};

unsigned char height(struct node * p) {
    return p?p->height:0;
}
    

int bfactor(struct node* p) {
    return height(p->right) - height(p->left);
}

void fixheight(struct node * p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

struct node * rotateright(struct node * p) {
    struct node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

struct node * rotateleft(struct node * q) {
    struct node * p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

struct node * balance(struct node * p) {
    fixheight(p);
    if (bfactor(p)==2){
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 ) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

struct node * fill(int key, int data) {
    struct node * node = malloc(sizeof(struct node));
    node->key = key;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct node * append(struct node * p, int k, int data) {
    if (!p) return fill(k, data);
    if (k<p->key)
        p->left = append(p->left,k, data);
    else if (k == p->key) {
        p->data = data;
        return p;
    }
    else
        p->right = append(p->right,k, data);
    return balance(p);
}


void print(struct node * head) {
    if (!head) {
        return;
    }
    print(head->left);
    printf("%d\n", head->key);
    print(head->right);
}

struct node * search(struct node * head, int key) {
    struct node * current = head;
    while (current) {
        if (key < current->key) {
            current = current->left;
        }
        else if (key == current->key){
            return current;
        }
        else {
            current = current->right;
        }
    }
    return NULL;
}

struct node * search_min(struct node * head) {
    if (!head) return NULL;
    while (head->left) {
        head = head->left;
    }
    return head;
}

struct node * delete_min(struct node * p) {
    if (p->left == NULL) return p->right;
    p->left = delete_min(p->left);
    return balance(p);
}

struct node * delete(struct node * p, int k) {
    if (!p) return NULL;
    if (k < p->key) {
        p->left = delete(p->left,k);
    }
    else if (k > p->key) {
        p->right = delete(p->right,k);
    }
    else {
        struct node * q = p->left;
        struct node * r = p->right;
        free(p);
        if (!r) return q;
        struct node * min = search_min(r);
        min->right = delete_min(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}
 
void free_tree(struct node * head) {
    if (!head) {
        return;
    }
    if (head->left) free_tree(head->left);
    if (head->right) free_tree(head->right);
    free(head);
}

int main(void) {
    struct node * head = NULL;
    char fun;
    int key , data;
    scanf("%c", &fun);
    while(fun != 'F') {
        if (fun == 'A') {
            scanf("%d", &key);
            scanf("%d", &data);
            head = append(head, key, data);
        }
        if (fun == 'S') {
            scanf("%d", &key);
            struct node * answer = search(head, key);
            if (answer) printf("%d %d\n", answer->key, answer->data);
        }
        if (fun == 'D') {
            scanf("%d", &key);
            head = delete(head, key);
        }
        scanf("%c", &fun);
    }
    free_tree(head);
}

