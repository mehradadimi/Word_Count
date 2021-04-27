/*
 * linkedlist.h
 *
 * This header file contains examples of how to:
 *
 * a) Dynamically allocate memory in a function
 * b) Free memory used by a linked list
 * c) Print the contents of a linked list 
 * d) Apply a function to a linked list
 *
 * All the linked lists are set to void*.  You may replace them
 * with your own struct typedefs.
 */
#define  _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define EXAMPLE_ERROR_CODE 1


typedef struct myWord_node {
    char* word;
    struct myWord_node* next;
    struct myWord_node* previous;
}myWord_node;


typedef struct my_list{
    int number_of_words;
    int word_len;
    struct myWord_node* list_head;
    struct myWord_node* list_tail;
    struct my_list* next;
    struct my_list* previous;
}my_list;


myWord_node* allocate_word_node (){
     myWord_node* news = (myWord_node*)malloc(sizeof(myWord_node));
     return news;
}


my_list* create_new_list(){
    my_list* new_list = (my_list*)calloc(1, sizeof(my_list));
    return new_list;
}



int is_word_there(myWord_node* list, char* new_word){
     myWord_node* current = list;
     for (current = list ; current != NULL ; current = current->next){
           if (strcmp(current->word, new_word) == 0){
                return 1;
           }  
     }

     return -1;

}
int in_order(char* new_word, myWord_node* current , int position){
    if (*(new_word+position) == *((current->word)+ position)){
        return in_order(new_word, current, position+1);    
    }else if (*(new_word+position) < *((current->word)+ position)){
        return 1;
    }else{
        return -7;
    }
}


void add_word_to_list (myWord_node** list, char* new_word){
     if(is_word_there(*list, new_word) == 1){
         return;
     }else{

         myWord_node* news = allocate_word_node();
         if (news == NULL){
             fprintf(stderr, "memory allocation error");
         }   
         int length = strlen(new_word);
         news->word = (char*)calloc(1, length * sizeof(char)+1);
         strncpy(news->word, new_word, length);
         news->next = NULL;

         if (*list == NULL){
            *list = news;
            return;
         }

         if (*new_word < *((*list)->word)){
             news->next = *list;
             *list = news;
         }else if (*new_word == *((*list)->word)){
             if(in_order(new_word, *list, 1) == 1){
                news->next = *list;
                *list = news;
                return;
             }
                
         }
      
        myWord_node* previous = *list;
        for (myWord_node* current = (*list)->next ; current!=NULL; current = current->next){
              if(*new_word < *(current->word)){
                     previous -> next = news;
                     news->next = current;
                     return;
                }else if (*new_word == *(current->word)){
                      if(in_order(new_word, current, 1) == 1){
                         previous->next = news;
                         news->next = current;
                         return;
                      }
                }
              previous = current;
         }
         
         previous->next = news;
      }

}



int length_already_exists (my_list* list, int length){
    my_list* current = list;
    for(current = list; current!=NULL; current = current->next ){
        if(current->word_len == length){
         return 1;
        }
    }
    return -1;
}

void add_to_end (my_list** list, int length, char* new_word){
     if(length_already_exists(*list, length) == 1){
        my_list* current = *list; 
        for (current = *list; current->word_len!=length; current = current->next);

        add_word_to_list(&(current->list_head), new_word);
        current->number_of_words = current->number_of_words + 1;
     }else{

        my_list* new_list = create_new_list();
        if (new_list == NULL){
           fprintf(stderr, "memory allocation error");
           exit(3);
        }
        new_list->word_len = length;
        add_word_to_list(&(new_list->list_head), new_word);
       
        new_list->next= NULL;
        new_list->number_of_words=1;
        if (*list == NULL){
            *list = new_list;
            return;
        }
        if (new_list->word_len < (*list)->word_len){
            new_list->next = (*list);
            (*list) = new_list;
            return;
        }
        my_list* previous = *list;
        my_list* current = NULL;
        for (current = (*list)->next ; current!=NULL; current = current->next){
             if(new_list->word_len < current->word_len){
                    previous -> next = new_list;
                    new_list->next = current;
                    return;
                }
             previous = current;
        }
    
        previous->next = new_list;
        return;



     }
}















