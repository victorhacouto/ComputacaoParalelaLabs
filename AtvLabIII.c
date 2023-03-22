/*
    Gabriel Ramires - 42080681
    Mateus Fernandes Castanhare - 32137141
    Victor Hugo Antonio Couto - 32173482

    //Implemente a versão multiprocessada do cálculo do fatorial e compare o tempo de execução com a versão serial.
*/

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

int main()
{
    int i = 1, num, j, middle, result = 1;
    int fd[2];
    if(pipe(fd) == -1)
        return 1;

    printf("Enter the number: ");
    scanf("%d", &num);
    middle = num / 2;
    printf("Valor do meio: %d.\n\n", middle);

    int id = fork();
    if(id == 0)  
    {
        close(fd[0]);
        //printf("\nFilho.\n");
        for(int g = 1; g <= middle; g++)
                i *= g;
                //printf("Valor de i: %d\n", i);
        printf("Resultado do fatorial do processo filho: %d.\n", i);
        write(fd[1], &i, sizeof(int));
        close(fd[1]); 

    }
    else
    {
        wait(NULL);
        read(fd[0], &result, sizeof(int));
        //printf("resultado: %d\n\n", result);
        //printf("Papai.\n");
        for(int h = middle+1; h <= num; h++)
                i *= h;
                //printf("Valor de i: %d\n", i);
        printf("Resultado do fatorial do processo parente: %d.\n", i);
        write(fd[1], &i, sizeof(int));
        close(fd[1]);
        result *= i;
        printf("\nResultado do fatorial de %d: %d.\n\n", num, result);
    }
}
