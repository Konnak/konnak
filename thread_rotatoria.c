#include<pthread.h>
#include<stdio.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include<time.h>//necessário p/ função time()
#include<stdbool.h>
#define MAX 3


void *Rota(void *param);

pthread_mutex_t mutex;
int vrodovia[4] = {0,0,0,0};

int main(int argc, char *argv[])
{
   int i;
   bool cond = true;
   pthread_t tid[MAX];
   pthread_attr_t attr;
   pthread_attr_init(&attr);
   
   // Cria o mutex
   pthread_mutex_init(&mutex, NULL);
  
  do {
   char *arg;
   for(i=0;i<4;i++) {
	  pthread_create(&tid[i], &attr, Rota, (void *) i);
   }
   
   for(i=0;i<4;i++) {
      pthread_join(tid[i], NULL);
   }
  } while (cond == true);
   // Destroi mutex
   pthread_mutex_destroy(&mutex);
   
}

void *Rota(void *param)
{   
   srand(time(NULL));
   int rodovia = param;
   
   // Sinaliza/obtem o mutex
    pthread_mutex_lock(&mutex);
   
   int random = ((rand() + time(0)) % 5 + 1);  // RAND DE ENTRADA DE VEICULOS
   vrodovia[rodovia]+= random;
   printf("Rodovia %d recebeu %d carros na fila.\n", rodovia, random);
   int rotatoria=0;
   printf("Rodovia %d entrou na rotatoria.\n", rodovia);
   sleep(2);
   rotatoria = ((rand() + time(0)) % 5 + 1); // RAND DE RETIRADA DE VEICULOS
   vrodovia[rodovia]-=rotatoria;        
   
   if (vrodovia[rodovia] == -1){    // VERIFICA SE NÃO TIROU MAIS VEICULOS DO QUE TEM NA FILA
       vrodovia[rodovia] = 0;
       rotatoria -= 1;
   } else if (vrodovia[rodovia] == -2){
             vrodovia[rodovia] = 0;
             rotatoria -= 2;
   } else if (vrodovia[rodovia] == -3){
       vrodovia[rodovia] = 0;
       rotatoria -= 3;
   } else if (vrodovia[rodovia] == -4){
       vrodovia[rodovia] = 0;
       rotatoria -= 4;
   } else if (vrodovia[rodovia] == -5){
       vrodovia[rodovia] = 0;
       rotatoria -= 5;
   }
   
   printf("Rodovia %d passou %d carros pela rotatoria\n", rodovia, rotatoria); 
   printf("Rodovia %d saiu da rotatoria.\n", rodovia);
   printf("Rodovia %d possui %d carros na fila.\n", rodovia, vrodovia[rodovia]);
   pthread_mutex_unlock(&mutex);
   // Libera o mutex
   
   printf("-----------------------------------------------------------------\n");
   pthread_exit(0);

}
