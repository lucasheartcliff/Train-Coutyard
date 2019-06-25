#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//* Define o prop�sito das fun��es e estruturas
//? Explicita o significado das variaveis

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

//* Cria um novo trem
train* newTrain();

//* Insere vag�o no trem
void insertQueue(train *tr, wagon *wg);

//* Remove vag�o do trem
wagon* removeQueue(train *tr);

//* Cria um novo trilho
rail* newRail();

//* Insere um trilho � um p�tio
void insertRail(coutyard *ct, rail * rl);

//* Insere vag�o no trilho
void insertStack(rail *rl , wagon *wg);

//* Remove vag�o da pilha de trilhos
wagon* removeStack(rail *rl);

//* Cria um novo p�tio
coutyard* newCoutyard(int lenght, int size);

//* Verifica se o pr�ximo vag�o ja pode ser inserido direto no trem de sa�da
int canGo(int *this, int *nextToGo);

//* Verifica a sequencia e determina a quantidade m�nima de trilhos necess�ria para a reorganiza��o
void howMany(train *tr, int *lenght, int *size);

//* Entrada da sequencia dos vag�es
void entry(train *tr);

//* Exibe os valores do trem na tela
void echoTrain(train *tr);

//* Exibe os valores da pilha na tela
void echoRail(rail *rl);

//* Realiza a reorganiza��o dos vag�es
train* startSwap(train *tr, coutyard *ct);

//* Mem�ria Indispon�vel
void memoryOverFlow();





//* Mem�ria Indispon�vel
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

//* Insere um trilho � um p�tio
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
        *nextToGo += 1;
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
        //printf("trilho: %i | tamanho: %i | contador: %i | proximo a ir: %i\n", *lenght, *size, count, tr->nextToGo);
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
    }else{
        return NULL;
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
    int value = 1; //? Ir� conter os valores da hierarquia
    int count = 0; //? Contador de Vag�es

    printf("Digite a ordem dos vag�es\n\nObs: Digite qualquer n� negativo para indicar o fim da sequ�ncia.\n\n");
    while(value > 0){
        printf("%i� Vag�o: ", (count+1) );
        scanf("%i",&value);

        if(value > 0){
            insertQueue(tr, newWagon(value)); //? Insere vag�o criado no trem

            if(tr->nextToGo > value || count == 0){ //? Verifica se o valor atual � menor do que os anteriores
                tr->nextToGo = value; //? Recebe o menor valor da hierarquia indicando o que deve sair primeiro
            }
            count++;
        }
    }
}

//* Exibe os valores do trem na tela
void echoTrain(train *tr){
    wagon *pw = tr->header->next;
    int count = 0;
    printf("Destino\tPosi��o\t\n");
    while(pw != tr->header){
        count++;
        printf("%i\t%i�\t\n", pw->destiny,count);
        pw = pw->next;
    }
}

//* Exibe os valores da pilha na tela
void echoRail(rail *rl){
    rail *pr = rl->next;
    wagon *pw = pr->header->next;


    while(pr != rl){
        while(pw != NULL){
            printf("%i ",pw->destiny);
            pw = pw->next;
        }
        pr = pr->next;
        pw = pr->header->next;
        printf("\n");
    }
}

//* Realiza a reorganiza��o dos vag�es
train* startSwap(train *tr, coutyard *ct){
    train *tr_out = newTrain(); //? Trem de sa�da

    int max_wagon = tr->lenght; //? Quantidade total de vag�es

    wagon *wg; //? Vag�o que ser� retirado do trem

    rail *pr; //? Ponteiro para percorrer os trilhos

    int found; //? Indicador se achou um espa�o livre no trilho

    int num_rail; //? Identificador de posi��o do vag�o no trilho

    int count = 0; //? Contador de etapas

    system("cls");
    printf("Iniciando troca... \n");
    printf("\nEtapas\tVag�o\tTrilho\tPosi��o\tEmissor\tDestino\t\n");
    while(tr->lenght > 0){
        pr = ct->rails->next;
        num_rail = 1;

        wg = removeQueue(tr);
        found = 0;

        if( !(wg->destiny == tr->nextToGo ) ){
             while(pr != ct->rails && found == 0){
                if(pr->quantity > 0){
                    if(pr->header->next->destiny > wg->destiny && pr->quantity < ct->size){
                        count++;
                        insertStack(pr, wg);
                        found = 1; //? Se achou espa�o livre que atenda as condi��es muda para 1
                        printf("%i\t%i\t%i\t%i\tTrem\tTrilho\t\n",count,wg->destiny, num_rail, pr->quantity);
                    }else{
                        pr = pr->next;
                        num_rail++;
                    }
                }else{
                     count++;
                     insertStack(pr,wg);
                     found = 1;
                     printf("%i\t%i\t%i\t%i\tTrem\tTrilho\t\n",count,wg->destiny, num_rail, pr->quantity);
                }
            }
        }else{
            if( canGo(&wg->destiny, &tr->nextToGo)){
                insertQueue(tr_out, wg);
            }
        }

    }
    //echoRail(ct->rails);
    while(tr_out->lenght < max_wagon){
        pr = ct->rails->next; //? Aponta o ponteiro para o 1� trilho
        num_rail = 1;

        while(pr != ct->rails){
            if( pr->quantity > 0 && canGo( &pr->header->next->destiny , &tr->nextToGo)){
                count++;
                wg = removeStack(pr);
                insertQueue(tr_out, wg);
                printf("%i\t%i\t%i\t%i\tTrilho\tTrem\t\n",count,wg->destiny, num_rail, (pr->quantity+1) );
            }else{
                pr = pr->next;
                num_rail++;
            }
        }
    }
    printf("\nTrilhos Usados: %i\nQuantidade M�xima de Vag�es/Trilho: %i\n\n",ct->lenght,ct->size);
    //echoTrain(tr_out);
    return tr_out;
}

int main(void){
    setlocale(LC_ALL,"Portuguese");

    train *tr = NULL; //? Trem que ser� reorganizado
    coutyard *ct = NULL; //? P�tio de Troca de Vag�es
    int lenght; //? Quantidade de Trilhos
    int size; //? Quantidade de Vag�es que cada trilho suporta
    int input=0; //? Leitura das op��es escolhidas pelo usu�rio

    while(input != 4){
        system("cls");
        printf("Escolha uma das op��es abaixo\n");
        printf("1 - Inserir a sequ�ncia do trem\n");
        printf("2 - Reordenar o trem\n");
        printf("3 - Exibir o trem\n");
        printf("4 - Sair do Programa\n");

        scanf("%i",&input);

        switch(input){

            case 1:
                system("cls");

                if(tr != NULL){
                    free(tr); //? Libera caso queira entrar novamento com novos dados
                }
                tr = newTrain(); //? Aloca um novo trem
                entry(tr); //? Entrada de dados
                howMany(tr, &lenght, &size); //? Determina quantos trilhos ser�o utilizados
            break;
            case 2:
                if(ct != NULL){
                    free(ct->rails); //? Libera os trilhos usados anteriormente
                    free(ct);  //? Libera o p�tio usado anteriormente
                }
                ct = newCoutyard(lenght, size); //? Aloca um novo p�tio
                tr = startSwap(tr, ct); //? Inicia a troca
                system("pause");
            break;
            case 3:
                system("cls");
                echoTrain(tr); //? Exibe a sequencia do trem na tela
                printf("\n");
                system("pause");
            break;

            default:
            break;
        }
    }
    return 0;
}
