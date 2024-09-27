#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "linked_list.h"
static int compare(void *s1, void *s2) {
    return strcmp(s1, s2);
}//add comparison function
void printList(ll_node_t *pp, int size){
    int length=0;//caculate the length of sentence
	ll_node_t *p=pp;//Prevent the original linked list pointer from being moved
        for(int i=0;i<size;i++){
            length+=(strlen((char *)p->item)+1);
            if(length<=30){
                printf("%s ",(char *)p->item);
            }
            else{
                printf("%s\n",(char *)p->item);
                length=0;
            }
            p=p->next;
        }
}//Output every 30 characters
linked_list_t* builtlist(void);
linked_list_t* builtlist(){//create linked list
    char *ch=calloc(100, sizeof(char));
    linked_list_t *List=ll_new();//Initialize linked list
    scanf("%s",ch);
    if(strcmp(ch,"EOS")==0){//check whether the first item in the linked list is EOS
	   			 //Here EOS is also used as a linked list and as a stop character
        ll_add_back(List, ch);
        return List;
    }else{
        ll_add_back(List, ch);
        ll_node_t *ptr=List->head;
        while(strcmp(ptr->item,"EOS")){
            char *che=calloc(100, sizeof(char));
            scanf("%s",che);
            ll_add_back(List,che);
            ptr=ptr->next;
        }
        ll_remove_back(List);

        return List;
    }
}
int IS_in(linked_list_t *A,void *value){
    if(A==NULL||A->size==0){
        return 0;
    }
    ll_node_t *p=A->head;
    while(p!=NULL){
        if(p->item==value){
            return 1;
        }
        p=p->next;
    }
    return 0;
}//check if the element in the array
linked_list_t * Max(linked_list_t *ll,linked_list_t *m){
    assert(ll);//Check that the linked list is not empty
    linked_list_t *MM=ll_new();//Place the returned linked list
    int overlap=0;
    linked_list_t *Head=ll->head->item;//Place the first element of the sentence list
    ll_node_t *p=ll->head->next;//Pointer for traversing linked list
    linked_list_t *B=p->item;//Item of linked list
    while(strcmp(B->head->item,"EOS")!=0){
        linked_list_t *ptr=p->item;
        if(IS_in(m,ptr)!=1){
            int number1=ll_overlap(Head,ptr,&compare);
            int number2=ll_overlap(ptr,Head,&compare);
            int number=number1>number2 ?number1:number2;
            if(number>overlap){
                overlap=number;
                MM=ptr;
            }//The detection only looks for the largest overlap among unmerged sentences.
        }
        p=p->next;
        B=p->item;
    }
    return MM;
}//find the linked list with maximum overlap
int main() {
    // insert code here...
    linked_list_t *L=ll_new();
    linked_list_t *str=builtlist();//built new linked list to be the item of L
    ll_add_back(L,str);
    while(strcmp(str->head->item,"EOS")!=0){
        linked_list_t *Str=builtlist();
        ll_add_back(L,Str);
        str=Str;
    }
   //Create a linked list and specify the items of the new linked list as linked lists 
    linked_list_t *Head=L->head->item;
    if(strcmp(Head->head->item,"EOS")!=0){
        linked_list_t *k=ll_new();
	ll_node_t *U=L->head->next;//Pointer to traverse linked list
        linked_list_t *U2=U->item;//item of the node
        while(strcmp(U2->head->item,"EOS")!=0){
            linked_list_t *value=Max(L,k);
            if(value->head!=NULL){//Splice two linked lists
                ll_add_back(k,value);
                int Over1=ll_overlap(Head,value,&compare);
                int Over2=ll_overlap(value,Head,&compare);
                int Over=Over1>Over2? Over1:Over2;
		
                if(Over==Over1){
                    ll_splice(Head,value,Over);
                    // printList(L[0]->head,L[0]->size);
                }
                else{
                    linked_list_t *term=value;
                    value=Head;
                    Head=term;
                    ll_splice(Head,value,Over);
                }
		L->head->item=Head;

           }
            U=U->next;
            U2=U->item;
        }
    }
    if(strcmp(Head->head->item,"EOS")!=0){
        ll_node_t *P=Head->head;
        printList(P,Head->size);
    }//call output function
    return 0;
}
