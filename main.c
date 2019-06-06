#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct wagon{
    int destiny;
    struct wagon *next;    
}wagon;

typedef struct{
    wagon *wagons;
    wagon *header;
    int lenght;
}train;

typedef struct{
    int size;
    wagon *wagons;
    wagon *header;
}coutyard;

train* new_train(int lenght){
    train* tr = (train*) malloc( sizeof(train) );
    tr->wagons = (wagon*) malloc( lenght * sizeof(wagon));
    tr->header = (wagon*) malloc( sizeof(wagon) );
    
    if(tr == NULL || tr->wagons == NULL|| tr->header == NULL){
        memoryOverFlow();
        free(tr);
        return NULL;
    }else{
        return tr;
    }
}

coutyard* new_coutyard(int lenght, int size){
    coutyard* ct = (coutyard*) malloc(lenght * sizeof(coutyard));
    
    if(ct == NULL){
        memoryOverFlow();
        free(ct);
        return NULL;
    }else{
        int i;

        for(i=0;i<lenght;i++){
            ct[i].wagons = (wagon*) malloc(size * sizeof(wagon));

            if(ct[i].wagons == NULL){
                memoryOverFlow();
                free(ct);
                return NULL;
            }
        }
        return ct;
    }
}
void isPossible(int wagons, int *lenght, int *size){
    int result = (*lenght)*(*size);

    if(result < (wagons -1) ){
        /*
        *   ceil() retorna o maior valor aproximado do parâmetro passado, exemplo: 12.4 -> 13.0
        *   sqrt() retorna a raiz quadrada do parâmetro
        */
        
        *lenght = (int) ceil( sqrt(wagons - 1) );
        *size = (int) ceil( sqrt(wagons -1) );
    }
}

int main(void){

    return 0;
}