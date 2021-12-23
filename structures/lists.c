#include <stdio.h>
#include <stdlib.h>

struct list_element{
    double w;
    struct list_element *next;
};



void free_memory(struct list_element *beg){
    struct list_element *temp, *tmp=beg;
    while(tmp){
        temp = tmp;
        tmp = tmp -> next;
        free(temp);
    }
}

struct list_element *copy_list(struct list_element *beg){
    struct list_element *new_element, *last, *list2 = 0;
    while(beg){
        new_element = malloc(sizeof(struct list_element));
        new_element -> w = beg -> w;
        if(list2 == 0)
            list2 = new_element;
        else last->next=new_element;
        last = new_element;
        beg = beg -> next; 
    }
    if(list2)
        new_element -> next = 0;
    return list2;
}

struct list_element *merge_lists(struct list_element *beg1, struct list_element *beg2){
    struct list_element *copy1, *copy2, *temp;
    copy1 = copy_list(beg1);
    copy2 = copy_list(beg2);

    if(copy1 == 0)
        return copy2;
    
    temp = copy1;
    
    while(temp->next)
        temp = temp -> next;
    temp -> next = copy2;

    return copy1;
}

void add(struct list_element **beg, double value){
    struct list_element *new_element, *tmp=*beg;
    new_element = malloc(sizeof(struct list_element));
    new_element -> w = value;
    new_element -> next = 0;
    if(tmp == 0) *beg = new_element;
    else{
        while(tmp->next) tmp = tmp -> next;
        tmp->next = new_element;
    }
}

void insert(struct list_element **beg, double value){ //add with "sort"
    struct list_element *new_element, *tmp=*beg;
    new_element = malloc(sizeof(struct list_element));
    new_element -> w = value;
    if(tmp == 0 || value < tmp->w){
        new_element -> next = tmp;
        *beg = new_element;
    }
    else{
        while(tmp -> next != 0 && value > tmp -> next -> w){
            tmp = tmp -> next;
        }
        new_element -> next = tmp-> next;
        tmp -> next = new_element;
    }
}

struct list_element *find(struct list_element *beg, double value){
    while(beg && beg->w != value) beg = beg -> next;
    // printf("%p", beg);
    return beg;
}

void remove_element(struct list_element **beg, double value){
    struct list_element *temp, *tmp = *beg;
    if (tmp==0) return;
    if (value == tmp->w){
        *beg = tmp -> next;
        free(tmp);
    }
    else{
        while(tmp -> next != 0 && value != tmp -> next -> w)
            tmp = tmp -> next;

        if(tmp -> next != 0 && value == tmp -> next -> w){
            temp = tmp -> next;
            tmp -> next = tmp -> next -> next;
            free(temp);
        }

        
    }

}


void write(struct list_element *beg){
    while(beg){
        printf("%lf\n", beg->w);
        beg = beg->next;
    }
}


int main(){
    //Example usage: 
    // struct list_element *o1=0, *o2=0, *sum;

    // add(&o1, 5);
    // add(&o1, 7);
    // add(&o1, 9);
    // add(&o1, 10);
    // insert(&o1, 6);
    // write(o1);
    // o2 = find(o1, 6);
    // printf(" %lf", o2 -> w);
    // o2=copy_list(o1);
    
    // sum=merge_lists(o1, o2);
    // write(sum);

    // free_memory(o1);
    return 0;
}