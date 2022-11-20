#include <stdio.h>
#include "pyramide.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>


Liste *init()
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    if(liste == NULL || element == NULL)

    {
        exit(EXIT_FAILURE);
    }

    element->suivant = NULL;
    element->nombre = 0;
    liste->premier = element;
    printf("init done\n");

    return liste;

}

void insertion (Liste *liste, int nouveauNombre)
{
    Element *nouveau = malloc(sizeof(nouveau));

    if(liste == NULL || nouveau == NULL)

    {
        exit(EXIT_FAILURE);
    }

    nouveau->nombre = nouveauNombre;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;

    printf("ca marche\n");
}

void ajout_milieu(Liste *liste, int nouveauNombre, int position)
{
    int cptDoublon = 0;
    int cptElement = 0;
    int cpt = 0;
    int doublon = 0;
    int doublonPosition = 0;
    
    Element *milieu = malloc(sizeof(milieu));

       if(liste == NULL || milieu == NULL)

    {
        exit(EXIT_FAILURE);
    }

    Element *precedant = liste->premier;


    while (precedant->nombre != NULL)
    {
        cptElement ++;

        if(precedant->nombre == position)
        {
            doublonPosition = cptElement;
            
            
        }

        precedant = precedant->suivant;
    }


    Element *precedant2 = liste->premier;


    while (cpt != doublonPosition - 1)
    {
        precedant2 = precedant2->suivant;
        cpt ++;
    }


    milieu->nombre = nouveauNombre;
    milieu->suivant = precedant2->suivant;
    precedant2->suivant = milieu;


}


void suppression (Liste *liste)
{

    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if(liste->premier != NULL)
    {
        Element *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}


void afficher(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = liste->premier;

    while (actuel != NULL)
    {
        printf("%d ->", actuel->nombre);
        actuel = actuel->suivant;
    }

    printf("NULL\n");
}




void Pyramide()
{
    int cpt = 10;
    int cpt2 = 0;
    int i,j;
    for ( i = 0; i < cpt ; i++ ) 
    {
        for ( j = 0; j <= cpt2 + i ; j++ )
        {
            if( (i > 1 ) && (i < cpt - 1) && (j != 0) && (j != cpt2 + i))
            {
                printf("#");
            }

            else
            {
                printf("*");
            }
            
        }
        printf("\n");
            
    }    
            
}

void Puissance(int a, int b, int* c)
{
    int i =0;
    while ( b >= 1)
    {
        *c *= a;
        b--;
    }

    printf("c vaut : %d\n", *c);

}


// Let us create a global variable to change it in threads
int g = 0;
 
// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    // Store the value argument passed to this thread
    int *myid = (int *)vargp;
 
    // Let us create a static variable to observe its changes
    static int s = 0;
 
    // Change static and global variables
    ++s; ++g;
 
    // Print the argument, static and global variables
    printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);
}

void NProc(void)
{



 int N = 4;
 printf("main pid :%d ", getpid());
 for (int i =0 ; i < N ; i++ ) {
 if (fork() == 0) {
 // code fils
    printf(" fils : %d pid : %d ppid : %d\n", i, getpid(), getppid());
    return i;
    }
 }
 for (int i =0 ; i < N ; i++ ) {
 wait(NULL);
 }
 return 0;
 }



 

void waitProc(void)
{

 int N = 4;
 printf("main pid :%d ", getpid());
 for (int i =0 ; i < N ; i++ ) {
 if (fork() == 0) {
 // code fils
    printf(" fils : %d pid : %d ppid : %d\n", i, getpid(), getppid());
    return i;
    }
 }
 for (int i =0 ; i < N ; i++ ) {
    int status;
    int pid = wait(&status);
    printf("fin du pid %d  return %d status \n",pid,WEXITSTATUS(status));
 }
 return 0;
 }


void waitProcInOrder(void)
{

 int N = 4;
 int pids [N];
 printf("main pid :%d ", getpid());
 for (int i =0 ; i < N ; i++ ) {
    int pid = fork();
 if (pid == 0) {
 // code fils
    printf(" fils : %d pid : %d ppid : %d\n", i, getpid(), getppid());
    return i;
    } else{
        pids[i] = pid;
    }
 }
 for (int i =0 ; i < N ; i++ ) {
    int status;
    int pid = waitpid(pids[i],&status,0);
    printf("fin du pid %d  return %d status \n",pid,WEXITSTATUS(status));
 }
 return 0;
 }

 void NGenerationProc(void)
 {

 int N = 4;
 printf("main pid :%d ", getpid());
 int i = 0;
 for (; i < N ; i++ ) {
    int pid = fork();
 if (pid == 0) {
 // code fils
    printf(" fils : %d pid : %d ppid : %d\n", i, getpid(), getppid());
 }
 else{
    break;
 }
}
 
 if(i != N) {
    int status;
    int pid = wait(&status);
    printf("fin du pid %d  return %d status \n",pid,WEXITSTATUS(status));
 }
 return 0;

 }

volatile sig_atomic_t n_sigusr1=0;
volatile sig_atomic_t n_sigusr2=0;

static void sig_handler(int);

void sign (void)  {


  if(signal(SIGUSR1,sig_handler)==SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }
  int duree=60;
  while(duree>0) {
    printf("Exécution de sleep(%d)\n",duree);
    duree=sleep(duree);
  }
  printf("Fin du processus\n");
  printf("Reçu %d SIGUSR1\n",n_sigusr1);
  return(EXIT_SUCCESS);
}

static void sig_handler(int signum) {

  if(signum==SIGUSR1) {
    n_sigusr1++;
  }
}

void tempo(void) 
{
      char c;
  printf("Tapez return en moins de 5 secondes !\n");
  fflush(stdout);
  if(signal(SIGALRM,sig_handler)==SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }
  // sigalrm interrompt les appels système
  if(siginterrupt(SIGALRM,true)<0) {
    perror("siginterrupt");
    exit(EXIT_FAILURE);
  }
  alarm(5);
  int r=read(STDIN_FILENO,&c,1);
  if((r==1)&&(c=='\n')) {
    alarm(0); // reset timer
    printf("Gagné\n");
    exit(EXIT_SUCCESS);
  }
  printf("Perdu !\n");
  exit(EXIT_FAILURE);
}
 

 void CreatePipe(void)
 {

    int pipefd[2];
    if(pipe(pipefd) == -1)
    {
        printf("an error occured\n");
        return ;

    }
    int pid = fork();

    if (pid == 0)
    {
        close(pipefd[0]);
        printf("I'm the child\n");
        int number;
        printf("Input a number : ");
        scanf("%d",&number);
        write(pipefd[1], &number,sizeof(int));
        close (pipefd[1]);

    }
    else
    {
        close (pipefd[1]);
        int numberRead;
        read(pipefd[0], &numberRead, sizeof(int));
        close(pipefd[0]);
        printf("Got it from our sweety child : %d\n", numberRead);


    }

    return 0;

 }


 void TwoWaysComPipe(void)
 {

    int pipefd[2]; 
    int pipefd2[2];

    if(pipe(pipefd) == -1)
    {
        printf("an error occured\n");
        return 1;

    }
    int pid = fork();

    if(pid == -1) { return 2;}

    if (pid == 0)
    {
        int y;
        if(write(pipefd[1], &y,sizeof(y) == -1)) { return 3;}
        //printf("child Wrote %d\n ", y);

        y = 4 * y;

        if(read(pipefd[0], &y, sizeof(y)) == -1) { return 4;}
        printf(" child Received %d\n", y);
        
    }
    else
    {

        srand(time(NULL));
        int x = rand() % 10;
        if (write(pipefd[1], &x, sizeof(x)) == - 1 ){ return 5;}
        //printf("Parent Wrote %d\n", x);
        if(read(pipefd[0], &x, sizeof(x)) == -1) { return 6;}
        printf("Parent read result is %d\n", x);
        wait(NULL);

    }

    return 0;

 }


 void* routine (void)
 {
    printf("we are in the thread heh\n");
    sleep(3);
    printf("ending\n");

 }


void multithreads(void)
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;


}


void roll_dice (void)
{
    int *res = malloc(sizeof(int));
    srand(time(NULL));
    int value = (rand()%6)+1;
    printf("Thread result is : %p\n", res);
    *res = value;
    return (void*) *res;
}

void return_thread(void)
{

    pthread_t t1;
    int *result;

    if(pthread_create(&t1, NULL, &roll_dice, NULL) != 0)
    {
        return 1;
    }
    if( pthread_join(t1, (void**) &result) != 0)
    {
        return 2;
    }

    printf("Main res : %p\n", result);
    printf(" result is : %d \n",*result);
    free(result);

}

int **return_pointer(void)
{
    int *value;
    int **valuep;
    int val = 7 + 3;
    value = &val;
    valuep = &value;
    return valuep;

}

void passed_pointer(int *p)
{
    *p *=4; 
}


void passed_value (void)
{
    int **valeur = return_pointer();
    int val = 1;
    passed_pointer(&val);
    printf("la valeur de val est : %d", val);
    //printf("la valuer est : %d", **valeur);

}

void modification(void)
{
    printf("do nothing\n");
}