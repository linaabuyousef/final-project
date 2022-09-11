#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "types.h"
/**
 * @brief 
 * 
 * @return LinkedList* 
 */
LinkedList* newLinkedList();
/**
 * @brief 
 * 
 * @param list 
 * @return int 
 */
int LinkedList_getSize(LinkedList* list);
/**
 * @brief 
 * 
 * @param list 
 * @param data 
 * @return int 
 */
int LinkedList_append(LinkedList* list , void* data);
/**
 * @brief 
 * 
 * @param list 
 * @param data 
 * @return int 
 */
int LinkedList_prepend(LinkedList* list , void* data);
/**
 * @brief 
 * 
 * @param list 
 * @param index 
 * @param data 
 * @return int 
 */
int LinkedList_insert(LinkedList* list , int index , void* data);
/**
 * @brief 
 * 
 * @param list 
 * @return void* 
 */
void* LinkedList_pop(LinkedList* list);
/**
 * @brief 
 * 
 * @param list 
 * @return void* 
 */
void* LinkedList_peak(LinkedList* list);
/**
 * @brief 
 * 
 * @param list 
 * @param index 
 * @return void* 
 */
void* LinkedList_getAtIndex(LinkedList* list , int index);
/**
 * @brief 
 * 
 * @param list 
 * @param index 
 * @return void* 
 */
void* LinkedList_remove(LinkedList* list , int index);
/**
 * @brief 
 * 
 * @param list 
 * @param data 
 * @param compareRoutine 
 * @return int 
 */
int LinkedList_find(LinkedList* list , void* data , int (*compareRoutine)(void* , void*));
/**
 * @brief 
 * 
 * @param list 
 * @param printRoutien 
 */
void LinkedList_print(LinkedList* list , char* (*printRoutien)(void*));
/**
 * @brief 
 * 
 * @param list 
 * @param dataDestroyRoutien 
 */
void LinkedList_destroy(LinkedList* list , void (*dataDestroyRoutien)(void*));

#endif//LINKEDLIST_H_