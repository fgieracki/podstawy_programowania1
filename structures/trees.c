#include <stdio.h>
#include <stdlib.h>


struct tree_node{
    double val;
    struct tree_node *left, *right;
};

void insert(struct tree_node **begin, double value){
    struct tree_node *new_node, *ws = *begin;
    new_node = malloc(sizeof(struct tree_node));
    new_node -> val = value;
    new_node -> left = new_node -> right = 0;
    if(ws == 0) *begin=new_node;
    else{
        while(1){
            if(value < ws->val){
                if(ws->left == 0){ws->left = new_node; break;}
                else {ws = ws->left;}
            } else{
                if(ws->right==0){ws->right = new_node; break;}
                else {ws = ws->right;}
            }
        }
    }
}

void write(struct tree_node *begin){
    if(begin == 0) return;
    write(begin->left);
    printf("%lf\n", begin->val);
    write(begin->right);
}


struct tree_node *find(struct tree_node *begin, double value){
    if(begin == 0) return 0;
    if(begin -> val == value) return begin;
    else if(begin -> val < value) return find(begin->right, value);
    else return find(begin->left, value);

}



struct tree_node *cpy(struct tree_node *begin){
    if(begin == 0) return 0;

    struct tree_node *copy_node;
    copy_node = malloc(sizeof(struct tree_node));
    copy_node -> left = copy_node -> right = 0;
    copy_node -> val = begin -> val;
    copy_node -> left = cpy(begin->left);
    copy_node -> right = cpy(begin->right);

    return copy_node;
}


void remove_tree(struct tree_node *begin){
    if(begin == 0) return;
    remove_tree(begin->left);
    remove_tree(begin->right);
    free(begin);
}

int main(){
    // Example usage:
    // struct tree_node *o1=0, *o2;

    // insert(&o1, 5);
    // insert(&o1, 9);
    // insert(&o1, 6);
    // write(o1);
    // insert(&o1, 7);
    // o2=cpy(o1);

    // o2 = find(o1, 11);
    // if(o2 == 0) printf("Element not found!\n");
    // else printf("%p\n", o2);

    // printf("\n");
    // write(o2);
    // remove_tree(o2);
    return 0;
}