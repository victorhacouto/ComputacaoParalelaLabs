#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define tamMemCompartilhada sizeof(int)

int main() {
    int idMemCompartilhada, valor = 1, *IntMemComp;
    key_t chave;
    
    chave = 5678; //defina uma chave para a memória compartilhada

    //shmget cria a memoria compartilhada, IPC_CREAT define que caso a memoria compartilhada nao tenha sido criada, ele cria e 0666 define as permissões de acesso a memoria 
  
    if ((idMemCompartilhada = shmget(chave, tamMemCompartilhada, IPC_CREAT | 0666)) < 0){
        perror("Erro ao criar a memória compartilhada");
        exit(1);
    }

    //shmat aloca a memoria compartilhada para o processo
  
    if ((IntMemComp = shmat(idMemCompartilhada, NULL, 0)) == (int*) -1) {
        perror("Erro ao associar a memória compartilhada");
        exit(1);
    }

    *IntMemComp = valor;    //atribui valor a memoria
    
    pid_t pid = fork();    //cria filho

    if (pid == -1) {
        perror("Erro ao criar o processo filho");
        exit(1);
    }

    if (pid == 0) {
        *IntMemComp += 2;
        printf("Valor após o incremento do processo filho: %d\n", *IntMemComp);
        
        if (shmdt(IntMemComp) == -1) {  //shmdt usado para cancelar o acesso a memoria compartilhada
            perror("Erro ao desassociar a memória compartilhada do processo filho");
            exit(1);
        }

        exit(0);
    } 
    else {    //pai
        
        printf("Valor lido pelo processo pai na memória: %d\n", *IntMemComp);
      
        wait(NULL);      //espera filho

        *IntMemComp *= 4;

        printf("Processo pai modifica o valor novamente: %d\n", *IntMemComp);
      
        if (shmdt(IntMemComp) == -1) {
            perror("Erro ao desassociar a memória compartilhada do processo pai");
            exit(1);
        }

        if (shmctl(idMemCompartilhada, IPC_RMID, NULL) == -1) {       //shmctl remove ao 
            perror("Erro ao remover a memória compartilhada");
            exit(1);
        }
    }

    return 0;
}
