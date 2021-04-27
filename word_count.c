#include "word_count.h"

int file_index(char* argv[], int argc){
 int index_of_file = 0;
 int counter = 0;
 while (counter < argc){
    if (strstr(argv[counter],".txt") != NULL){
        index_of_file = counter;
        return counter;
    }
    counter++;
 }

return -7;

}

void free_word(myWord_node** list){
       myWord_node* current;    
       myWord_node* Me; 
       for (current = (*list); current != NULL;){
            free(current->word);
            Me = current;
            current = current->next;
            free(Me);
       } 


}

void free_linked_list(my_list** list){
     my_list* current;
     my_list* Me;
     for (current = *list; current!=NULL;){
          myWord_node** head = &(current->list_head);
          free_word(head);  
          Me = current;  
          current = current->next;
          free(Me);  
     }

}
void print_inside(myWord_node* list){
      for(myWord_node* current = list; current!=NULL; current = current->next){
             printf("\"%s\"", current->word);
             if(current->next == NULL){
                break;     
             }else if (current->next->next == NULL){
                 printf(" and ");
            }else{ printf(", ");}
         }   
 
 }
 
 void print_normal(my_list* list){
      for(my_list* current = list; current!=NULL; current = current->next){
           printf("Count[%02d]=%02d;", current->word_len, current->number_of_words);
           printf(" (words: ");
           print_inside(current->list_head);  
           printf(")\n");  
       }   
 }
 
 void print_reveresed(my_list* list){
      for(my_list* current = list ; current != NULL ; current = current->next){
           printf("Count[%02d]=%02d;", current->word_len, current->number_of_words);
           printf(" (words: ");
           myWord_node* bef = NULL;
           myWord_node* aft = NULL;
           myWord_node* cur = current->list_head;
           while(cur != NULL){
                 aft = cur->next;
                 cur->next = bef;
                 bef = cur;
                 cur = aft;
           }
           current->list_head = bef;
           print_inside(current->list_head);
           printf(")\n");   
      }
 
 }
   
 
 
 int is_sorted_there (int argc, char* argv[]){
     for (int i = 0 ; i < argc ; i++){
         if(strcmp("--sort", argv[i]) == 0){
             return 1;

         }
 
 
     }
 
 return -7;
 }



int 
main(int argc, char *argv[]) {

    //Finding the index of the text file
    int index_of_file = file_index(argv, argc); 
 

    //The program exits with code 1 if the text file is not in the argument.
    if (index_of_file == -7){
        fprintf(stderr, "program : missing '--infile <filename> [--sort]'\n");
        exit(1);
    }


    // the program exits with code 2 if the file given is empty.
    FILE* my_input = fopen(argv[index_of_file], "r");
    if (my_input == NULL){
       fprintf(stderr, "unable to open '%s' for reading\n", argv[index_of_file]);
       exit(2);
    }


    char* my_line = NULL;
    size_t my_size = 0;
    ssize_t length = getline(&my_line , &my_size, my_input);
    my_list* list = NULL;
    //char* string_spaced = {'\0'};
    while (length >= 0){
       char* string_spaced = strtok(my_line , " ");
      if(string_spaced != NULL){
         char* temp;
        
       while (string_spaced != NULL){
           temp = (char*)calloc(1, strlen(string_spaced) * sizeof(char)+1);
           int counter = 0;
           for (char* m = string_spaced; *m; m++){     
               if(isalpha(*m)){
                  temp[counter++] = *m;
               }
           }        
           temp[counter] = '\0';
         //  printf("%s  ", temp); 
           int length  = counter;
           if (strlen(temp) != 0){ 
           add_to_end(&list, length, temp);
           }
           free(temp); 
           string_spaced = strtok(NULL, " "); 
       }

    
        }
        length = getline(&my_line , &my_size, my_input);

    }




   if (is_sorted_there(argc, argv) == 1){
       print_reveresed(list);
   }else{
       print_normal(list);     
   }

     free_linked_list(&list);

     free(my_line);




   fclose(my_input);

   return 0;
}

