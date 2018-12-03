#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define name 1000
typedef struct node *tree_pointer;

typedef struct node {
    int count;
    char value[name];
    tree_pointer left_child, right_child, parent;
} node2;

tree_pointer search(tree_pointer root, char *key) {
    tree_pointer parent;
    int compare;
    while (root) {
        compare = strcmp(root->value, key);
        if (compare < 0) {
            parent = root;
            root = root->right_child;
            if (root == NULL)return parent;
        } else if (compare == 0) {
            return root;
        } else {
            parent = root;
            root = root->left_child;
            if (root == NULL)return parent;
        }

    }
    return NULL;
}

void insert_node(tree_pointer *root, char *key) {
    tree_pointer search_result, temp;
    temp = malloc(sizeof (struct node));
    temp->count = 1;
    temp->right_child = NULL;
    temp->left_child = NULL;
    strcpy(temp->value, key);
    if (*root) {

        search_result = search(*root, key);
        if (strcmp(search_result->value, key) == 0) {
            search_result->count++;
        } else if (strcmp(search_result->value, key) > 0) {
            search_result->left_child = temp;
            temp->parent = search_result;
        } else {
            search_result->right_child = temp;
            temp->parent = search_result;
        }
    } else {
        *root = temp;
        temp->parent = NULL;
    }

}

void delete_node(tree_pointer *root, tree_pointer search_result) {
    tree_pointer trail = search_result;
    if (trail->left_child == NULL && trail->right_child == NULL) { //要刪的點沒有left_child right_child 
        if (trail->parent == NULL) //刪的是root且這個樹沒有東西了 
            *root = NULL;
        if (trail->parent->left_child == trail)
            trail->parent->left_child = NULL;
        else
            trail->parent->right_child = NULL;


    }
    else if (trail->left_child != NULL) { //有左子樹的情況 
        for (trail = trail->left_child; trail->right_child; trail = trail->right_child);
        if (trail->left_child)
            trail->left_child->parent = trail->parent;
        if (trail->parent->right_child == trail)
            trail->parent->right_child = trail->left_child;
        else
            trail->parent->left_child = trail->left_child;
        search_result->count = trail->count;
        strcpy(search_result->value, trail->value);

    } else if (trail->right_child != NULL) { //有右子樹的情況 


        for (trail = trail->right_child; trail->left_child; trail = trail->left_child);
        if (trail->right_child)
            trail->right_child->parent = trail->parent;
        if (trail->parent->left_child == trail->right_child)
            trail->parent->left_child = trail->right_child;
        else
            trail->parent->right_child = trail->right_child;
        search_result->count = trail->count;
        strcpy(search_result->value, trail->value); //不是直接把node接上去，而是用資料複製的方式 

    }
    free(trail);

}

void minus_count(tree_pointer *root, char *key) {
    tree_pointer search_result;
    search_result = search(*root, key);
    if (strcmp(search_result->value, key) == 0) {
        if (search_result->count == 1) {
            delete_node(root, search_result);
        } else
            search_result->count--;
    }
}

void inoder_traversal(tree_pointer root) {
    if (!root)return;
    inoder_traversal(root->left_child);
    printf("%s %d\n", root->value, root->count);
    inoder_traversal(root->right_child);
}

int main(void) {
    char action, eat;
    char *input = malloc(sizeof (char)*20);
    tree_pointer root = NULL;
    do {
        printf("please input value:\n");
        puts("inputs 0 to end");
        scanf("%c", &action);
        if ((int) (action - '0') == 0)break;
        if ((int) (action - '+') == 0) {
            /*if(strncmp(&action,"+",1)==0){*/
            scanf("%s", input);
            insert_node(&root, input);
        } else {
            scanf("%s", input);
            minus_count(&root, input);
        }
        scanf("%c", &eat);
    } while (1);
    inoder_traversal(root);
    return 0;

}

