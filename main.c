#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct wagon{
    int destiny;
    struct wagon *next;
    struct wagon *back;
}wagon;

typedef struct{
    wagon *wagons;
    wagon *header;
    int lenght;
    int smaller;
}train;

typedef struct{
    int quantity;
    wagon *wagons;
    wagon *header;
}rail;

typedef struct{
    rail *rails;
    int num_rails;
    int size;
}coutyard;

void memoryOverFlow(){
    printf("Memoria Cheia");
}

train* newTrain(int lenght){
    train* tr = (train*) malloc( sizeof(train) );
    tr->wagons = (wagon*) malloc( lenght * sizeof(wagon));
    tr->header = (wagon*) malloc( sizeof(wagon) );
    
    if(tr == NULL || tr->wagons == NULL|| tr->header == NULL){
        memoryOverFlow();
        free(tr);
        return NULL;
    }else{
        tr->lenght = lenght;
        return tr;
    }
}

coutyard* newCoutyard(int lenght, int size){
    coutyard* ct = (coutyard*) malloc(sizeof(coutyard));
    
    if(ct == NULL){
        memoryOverFlow();
        free(ct);
        return NULL;
    }else{
        ct->rails = (rail*) malloc( lenght * sizeof(rail));

        if(ct->rails == NULL){
            memoryOverFlow();
            free(ct);
            return NULL;
        }else{
            int i;

            for(i=0;i<lenght;i++){
                ct->rails[i].wagons = (wagon*) malloc(size * sizeof(wagon));

                if(ct->rails[i].wagons == NULL){
                    memoryOverFlow();
                    free(ct);
                    return NULL;
                }else{
                    ct->rails[i].quantity = 0;
                }
            }
            ct->size = size;
            ct->num_rails = lenght;
            return ct;
        }
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
        *size = (int) ceil( sqrt(wagons - 1) );
    }
}

int removeStack(rail *rl){
    if(rl->quantity > 0){
        wagon *this = rl->header->next;
        int value = this->destiny;

        rl->header->next = this->next;

        free(this);
        return value;
    }
}

int removeQueue(train *tr){
    if(tr->lenght > 0){
        wagon *this = tr->header->next;
        int value = tr->header->next->destiny;
        
        tr->header->next = this->next;

        free(this);
        return value;
    }else{
        return NULL;
    }
}

void insertQueue(){

}
int main(void){

    return 0;
}