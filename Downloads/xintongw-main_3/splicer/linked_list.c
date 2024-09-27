//
// Created by Alex Brodsky on 2023-09-20.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "linked_list.h"

extern linked_list_t * ll_new() {
    linked_list_t * list = calloc(1,sizeof(linked_list_t));
    return list;
}

extern void ll_destroy(linked_list_t *list) {
    assert(list != NULL);
    while (list->head != NULL) {
        ll_node_t *tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }

    free(list);
}

static ll_node_t *new_node(void *item, ll_node_t *prev, ll_node_t *next) {
    ll_node_t *n = calloc(1, sizeof(ll_node_t));
    if (n != NULL) {
        n->item = item;
        n->prev = prev;
        n->next = next;
    }
    return n;
}


extern int ll_add_front(linked_list_t *list, void *item) {
    assert(list);

    ll_node_t *n = new_node(item,NULL, list->head);
    if (n != NULL) {
        if (list->tail == NULL) {
            list->tail = n;
        } else {
            list->head->prev = n;
        }
        list->head = n;
    }
    list->size++;
    return n != NULL;
}

extern int ll_add_back(linked_list_t *list, void *item) {
    assert(list);

    ll_node_t *n = new_node(item,list->tail, NULL);
    if (n != NULL) {
        if (list->head == NULL) {
            list->head = n;
        } else {
            list->tail->next = n;
        }
        list->tail = n;
    }
    list->size++;
    return n != NULL;
}

extern void * ll_remove_front(linked_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        ll_node_t *n = list->head;
        list->head = list->head->next;
        if (list->head == NULL) {
            list->tail = NULL;
        } else {
            list->head->prev = NULL;
        }

        item = n->item;
        free(n);
    }
    list->size--;
    return item;
}

extern void * ll_remove_back(linked_list_t *list) {
    assert(list);
    
    void *item = NULL;
    if (list->tail != NULL) {
        ll_node_t *n = list->tail;
        list->tail = list->tail->prev;
        if (list->tail == NULL) {
            list->head = NULL;
        } else {
            list->tail->next = NULL;
        }

        item = n->item;
        free(n);
    }
    list->size--;
    return item;
}

extern void * ll_get_front(linked_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->head->item;
    }
    return item;
}

extern void * ll_get_back(linked_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->tail->item;
    }
    return item;
}

extern unsigned int ll_size(linked_list_t *list) {
    assert(list);

    return list->size;
}

extern int ll_is_empty(linked_list_t *list) {
    assert(list);
    return list->head == NULL;
}

extern int ll_insert(linked_list_t *list, ll_node_t *node, void *item) {
    assert(list);
    assert(node);

    if (node->next == NULL) {
        assert(list->tail == node);
        return ll_add_back(list, item);
    } else {
        ll_node_t *n = new_node(item, node, node->next);
        if (n != NULL) {
            node->next->prev = n;
            node->next = n;
        }
        list->size++;
        return n != NULL;
    }
}


extern void * ll_remove(linked_list_t *list, ll_node_t *node) {
    assert(list);
    assert(node);

    if (node->prev == NULL) {
        assert(list->head == node);
        return ll_remove_front(list);
    } else if(node->next == NULL) {
        assert(list->tail == node);
        return ll_remove_back(list);
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        void *item = node->item;
        free(node);
        list->size--;
        return item;
    }
}

/************************************************************************
 * Your code below
 ************************************************************************/

extern unsigned int ll_overlap(linked_list_t *list1, linked_list_t *list2, 
                               int (*compare)(void *, void*)) {//check the number of overlapping elements in two linked lists
   assert(list2);//check if two chains exist
    assert(list1);
    ll_node_t *p=list1->head;//set pointer to traverse linked list
    for(int i=0;i<ll_size(list1);i++){
        unsigned int num=0;
        ll_node_t *p2=list2->head;
        ll_node_t *p3=p;
        while(p2!=NULL){
            if(compare(p3->item,p2->item)==0){
                num++;
                p3=p3->next;
                p2=p2->next;
            }
            else{
                break;
            }
            if(p3==NULL||p2==NULL){
                return num;
            }
        }
        p=p->next;
    }
    return 0;
}

extern void ll_splice(linked_list_t *list1, linked_list_t *list2, 
                      unsigned int overlap) {
   // Your Code Here
   assert(list2);
    assert(list1);//check if two chains exist
    if(overlap!=ll_size(list2)){//if list1 does not contain list2,set pointer to traverse linked list
        ll_node_t *p1=list2->head;
        
        for(int i=0;i<overlap;i++){
            p1=p1->next;
        }//find the next node where list overlaps list1
       
        while(p1!=NULL){
            ll_add_back(list1,p1->item);
            p1=p1->next;
        }//add missing elements after list1
        while (overlap<ll_size(list2)) {
            ll_remove_back(list2);
        }//delete elements of list2
    }
    else{
	    return;}
}
