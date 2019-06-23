#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//* Defina a hierarquia dos vag�es de entrada
//?
//!

//* Estrutura do Vag�o
typedef struct wagon{
    int destiny; //? N�mero da hierarquia de destino
    struct wagon *next; //? Ponteiro para o pr�ximo vag�o
    struct wagon *back; //? Ponteiro para o vag�o anterior
}wagon;

//* Estrutura do Trem
typedef struct{
    wagon *header; //? Cabe�alho que ir� conter o endere�o do 1� e do ultimo vag�o
    int lenght; //? Tamanho do trem
    int nextToGo; //? Pr�ximo a ser despachado para o trem de sa�da
}train;

//* Estrutura do Trilho
typedef struct rail{
    int quantity; // Quantidade de vag�es presentes
    struct rail *next; //? Ponteiro para o pr�ximo trilho
    wagon *header; //? Cabe�alho para o 1� vag�o
}rail;

//* Estrutura do P�tio de Trilhos
typedef struct{
    rail *rails; //? Ponteiro para os trilhos
    int lenght; //? Quantos trilhos o p�tio possui
    int size; //? Quantos vag�es os trilhos comportam
}coutyard;


//* Cria um novo vag�o
wagon* newWagon(int value);

void memoryOverFlow(){
    printf("Memoria Cheia");
}

//* Cria um novo trem
train* newTrain(){
    train* tr = (train*) malloc( sizeof(train) );

    if(tr == NULL){
        memoryOverFlow();
        free(tr);
        return NULL;
    }else{
        tr->lenght = 0;
        tr->header = newWagon(0);
        return tr;
    }
}

//* Cria um novo vag�o
wagon* newWagon(int value){
    wagon *wg = (wagon*)malloc( sizeof(wagon) );

    if(wg == NULL){
        memoryOverFlow();
        free(wg);
        return NULL;
    }else{
        wg->destiny = value;
        return wg;
    }
}

//* Cria um novo trilho
rail* newRail(){
    rail *rl = (rail*)malloc( sizeof(rail) );

    if(rl == NULL){
        memoryOverFlow();
        free(rl);
        return NULL;
    }else{
        rl->quantity = 0;
        rl->header = newWagon(0);
        return rl;
    }
}

void insertRail(coutyard *ct, rail * rl){
    if(ct != NULL && rl != NULL){
        if(ct->lenght == 0){
            ct->rails->next = rl;

            rl->next = ct->rails;
        }else{
            rl->next = ct->rails->next;
            ct->rails->next = rl;
        }
    }
}

//* Cria um novo p�tio
coutyard* newCoutyard(int lenght, int size){
    coutyard* ct = (coutyard*) malloc(sizeof(coutyard));

    if(ct == NULL){
        memoryOverFlow();
        free(ct);
        return NULL;
    }else{
        ct->lenght = 0;
        ct->rails = newRail();

        while(ct->lenght < lenght){
            insertRail(ct, newRail() );
            ct->lenght++;
        }

        ct->lenght = lenght;
        ct->size = size;

        return ct;
    }
}

//* Verifica se o pr�ximo vag�o ja pode ser inserido direto no trem de sa�da
int canGo(int *this, int *nextToGo){
    if(*this == *nextToGo){
        *nextToGo++;
        return 1;
    }else{
        return 0;
    }
}

//* Verifica a sequencia e diz a quantidade m�nima de trilhos necess�ria para a reorganiza��o
void howMany(train *tr, int *lenght, int *size){
    wagon *pw = tr->header->next;

    int nextToGo = tr->nextToGo; //? Indicador de qual vag�o pode ser inserido diretamente no trem de sa�da
    int count = 1; //? Contador para verificar a quantidade de casos de empilhamento

    *lenght = 0; //? Trilhos
    *size = 0; //? Capacidade dos Trilhos

    while(pw != tr->header){
        if( !canGo( &pw->destiny, &nextToGo )){ //? Se o vag�o n�o pode ir direto para o outro trem
            if(pw->destiny < pw->back->destiny){ //? Se o grau de hierarquia do anterior for menor ao atual
                count++;
                if(count > *size){
                    *size = count;
                }

                if(*lenght == 0){
                    *lenght = 1;
                }
            }else{
                *lenght += 1;
                count = 1;
            }
        }
        //printf("trilho: %i | tamanho: %i | contador: %i\n", *lenght, *size, count);
        pw = pw->next;
    }
}
//* Remove vag�o da pilha de trilhos
wagon* removeStack(rail *rl){
    if(rl != NULL && rl->quantity > 0){
        wagon *this = rl->header->next;

        rl->header->next = this->next;

        this->back = NULL;
        this->next = NULL;

        rl->quantity--;

        return this;
    }
}

//* Remove vag�o do trem
wagon* removeQueue(train *tr){
    if(tr != NULL && tr->lenght > 0 ){
        wagon *this = tr->header->next;

        tr->header->next = this->next;

        this->next = NULL;
        this->back = NULL;

        tr->lenght -= 1; //? Decrementa a quantidade de vag�es no trem

        return this;
    }else{
        return NULL;
    }
}

//* Insere vag�o no trem
void insertQueue(train *tr, wagon *wg){
    if(tr != NULL && wg != NULL){
        if(tr->lenght == 0){
            tr->header->next = wg;
            tr->header->back = wg;

            wg->back = tr->header;
            wg->next = tr->header;
        }else{
            wg->back = tr->header->back;
            wg->next = tr->header->back->next;

            tr->header->back->next = wg;
            tr->header->back = wg;
        }
        tr->lenght++; //? Incrementa a quantidade de vag�es no trem
    }
}

//* Insere vag�o no trilho
void insertStack(rail *rl , wagon *wg){
    if(rl != NULL && wg != NULL){
        if(rl->quantity == 0){
            rl->header->next = wg;

            wg->next = NULL;
        }else{
            wg->next = rl->header->next;

            rl->header->next = wg;
        }
        rl->quantity++; //? Incrementa a quantidade de vag�es no trilho
    }
}

//* Entrada da sequencia dos vag�es
void entry(train *tr){
    int value = 0; //? Ir� conter os valores da hierarquia
    int count = 0; //? Contador de Vag�es

    while(value >= 0){
        printf("Digite a hierarquia do %i vagao: ", (count+1) );
        scanf("%i",&value);

        if(value >= 0){
            insertQueue(tr, newWagon(value)); //? Insere vag�o criado no trem

            if(tr->nextToGo > value || count == 0){ //? Verifica se o valor atual � menor do que os anteriores
                tr->nextToGo = value; //? Recebe o menor valor da hierarquia indicando o que deve sair primeiro
            }
            count++;
        }
    }
}

void echoTrain(train *tr){
    wagon *pw = tr->header->next;

    while(pw != tr->header){
        printf("%i\n", pw->destiny);
        pw = pw->next;
    }
}

train* startSwap(train *tr, coutyard *ct){
    train *tr_out = newTrain(); //? Trem de sa�da

    int max_wagon = tr->lenght; //? Quantidade total de vag�es

    wagon *wg; //? Vag�o que ser� retirado do trem

    rail *pr; //? Ponteiro para percorrer os trilhos

    int found; //? Indicador se achou um espa�o livre no trilho

    int num_rail;

    while(tr->lenght >0){
        pr = ct->rails->next;
        num_rail = 1;
        printf("\nPr�ximo a ir %i\n", tr->nextToGo);

        if(tr->lenght > 0){
            wg = removeQueue(tr);
            found = 0;

            if( !canGo(&wg->destiny, &tr->nextToGo) ){
                while(pr != ct->rails && found == 0){
                    if(pr->quantity > 0){
                        if(pr->header->next->destiny > wg->destiny && pr->quantity < ct->size){
                            insertStack(pr, wg);
                            found = 1;

                            printf("Vag�o %i saiu do Trem Trilho %i - %i� Posi��o\n",wg->destiny, num_rail, pr->quantity);
                        }else{
                            pr = pr->next;
                            num_rail++;
                        }
                    }else{
                        insertStack(pr,wg);
                        found = 1;

                        printf("Vag�o %i saiu do Trem para o Trilho %i - %i� Posi��o\n",wg->destiny, num_rail, pr->quantity);
                    }
                }
            }else{
                insertQueue(tr_out,wg);

                 while(pr != ct->rails){
                    if( canGo( &pr->header->next->destiny, &tr->nextToGo ) ){
                        wg = removeStack(pr);
                        insertQueue(tr_out, wg);
                        printf("Vag�o %i saiu do Trilho %i para o Trem de sa�da\n",wg->destiny, num_rail);
                    }else{
                        pr = pr->next;
                    }
                }
            }
        }else{
            printf("Aqui");
            while(pr != ct->rails){
                if( canGo( &pr->header->next->destiny, &tr->nextToGo ) ){
                    wg = removeStack(pr);
                    insertQueue(tr_out, wg);
                    printf("Vag�o %i saiu do Trilho %i para o Trem de sa�da\n",wg->destiny, num_rail);
                }else{
                    pr = pr->next;
                }
            }
        }
    }
    return tr_out;
}

int main(void){
    setlocale(LC_ALL,"Portuguese");

    train *tr = newTrain();
    int lenght;
    int size;

    entry(tr);
    howMany(tr, &lenght, &size);

    coutyard *ct = newCoutyard(lenght, size);

    printf("%i",tr->lenght);
    system("pause");
    tr = startSwap(tr, ct);

    //echoTrain(tr);
    return 0;
}
