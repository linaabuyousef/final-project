#include "../../../header/utility/linkedList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{

    void* data;
    struct Node* next;
    struct Node* prev;

}Node;

typedef struct _linkedList{

    Node* head;
    Node* tail;
    int size;
    
}LinkedList;

LinkedList* newLinkedList(){

    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if(list == NULL){
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;

}

Node* _newNode(void* data){
    
    Node* _newNode = (Node*)malloc(sizeof(Node));
    if(_newNode == NULL){
        return NULL;
    }
    _newNode->data = data;
    _newNode->next = NULL;
    _newNode->prev = NULL;

    return _newNode;
}

int LinkedList_getSize(LinkedList* list){
    
    return list->size;

}

void* LinkedList_getAtIndex(LinkedList* list , int index){
    
    if(index == 0){
    
        return list->head->data;

    }else if(index == list->size-1){
        
        return list->tail->data;
    
    }else if (index < 0 || index >= list->size){
        
        return NULL;
    
    }

    Node* currNode = list->head;
    
    for(int i = 1 ; i <=index ; i++){
    
        currNode = currNode->next;
    
    }

    return currNode->data;
}

int LinkedList_append(LinkedList* list , void* data){
    
    if(list == NULL){
        return -1;
    }

    if(list->size == 0){
        
        list->head = _newNode(data);
        if(list->head == NULL){
            return -1;
        }
        list->tail = list->head;
        list->size++;
        
        return 0;
    }

    list->tail->next = _newNode(data);

    if(list->tail->next == NULL){
        return -1;
    }

    list->tail->next->prev = list->tail;
    list->tail = list->tail->next;
    list->size++;

    return 0;
}

int LinkedList_prepend(LinkedList* list , void* data){

    if(list == NULL){
        return -1;
    }

    if(list->size == 0){
        
        list->head = _newNode(data);
        if(list->head == NULL){
            return -1;
        }
        list->tail = list->head;
        list->size++;
        
        return 0;
    }

    list->head->prev = _newNode(data);

    if(list->head->prev == NULL){
        return -1;
    }

    list->head->prev->next = list->head;
    list->head = list->head->prev;
    list->size++;

    return 0;
}

int LinkedList_insert(LinkedList* list , int index , void* data){
    
    if(list == NULL){
        return -1;
    }
    
    if(index == 0 || list->size == 0){
    
        return LinkedList_prepend(list,data);
    
    }else if(index == list->size){
    
        return LinkedList_append(list,data);
    
    }else{
        
        Node* currNode = list->head;
        
        for (int i = 1 ; i<=index ; i++){
        
            currNode = currNode->next;

        }

        Node* prevNode = currNode->prev;
        
        Node* newNode = _newNode(data);
        
        if(newNode == NULL){
        
            return -1;
        
        }

        prevNode->next = newNode;
        newNode->prev = prevNode;

        newNode->next = currNode;
        currNode->prev = newNode;

        list->size++;
        
        return 0;

    }
}

void* LinkedList_pop(LinkedList* list){
    
    if(list == NULL || list->size == 0){
        return NULL;
    }
    
    Node* headptr = list->head;

    void* data = headptr->data;

    list->head = headptr->next;

    if(list->head != NULL){
    
        list->head->prev = NULL;
    
    }

    free(headptr);

    list->size--;

    return data;
}

void* LinkedList_peak(LinkedList* list){
    
    if(list == NULL || list->size == 0){
        return NULL;
    }
    return list->head->data;
}

void* LinkedList_remove(LinkedList* list , int index){
        
    Node* NodeToDel;

    if(index == 0 && list->size > 0){
        
        NodeToDel = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        
    }else if(index == list->size-1){
        
        NodeToDel = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    
    }else if (index < 0 || index >= list->size){
        
        return NULL;
    
    }else{
    
        NodeToDel = list->head;
       
        for(int i = 1 ; i <=index ; i++){
            
            NodeToDel = NodeToDel->next;

        }
        
        Node* nextNode = NodeToDel->next;
        Node* prevNode = NodeToDel->prev;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

    }

    void* data = NodeToDel->data;
    free(NodeToDel);
    list->size--;
    
    return data;
}

int LinkedList_find(LinkedList* list , void* data , int (*compareRoutine)(void* , void*)){
    
    Node* currNode = list->head;

    for(int i = 0 ; i < list->size ; i++){
        
        if(compareRoutine(data,currNode->data)==0){
        
            return i;

        }

        currNode = currNode->next;
    
    }
    
    return -1;
}

void LinkedList_print(LinkedList* list , char* (*printRoutien)(void*)){

    char* printBuffer;
    Node* currNode = list->head;
    for(int i = 0 ; i < list->size ; i++){
        printBuffer = printRoutien(currNode->data);
        printf("%s->",printBuffer);
        free(printBuffer);
        currNode = currNode->next;
    }
    printf("\n");

}

void LinkedList_destroy(LinkedList* list , void (*dataDestroyRoutien)(void*)){
    
    if(list == NULL){
        return;
    }
    
    Node* currNode = list->head;
    Node* nextNode = currNode->next;
    
    for(int i = 0; i < list->size ; i++){
        
        if(dataDestroyRoutien != NULL){
        
            dataDestroyRoutien(currNode->data);

        }

        free(currNode);

        currNode = nextNode;
        if(nextNode != NULL){
        
            nextNode = currNode->next;
        
        }
    
    }
}
