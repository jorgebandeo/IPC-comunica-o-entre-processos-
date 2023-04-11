#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_ITEMS 500

int esteira1_count = 0;
int esteira2_count = 0;
float peso_total = 0;

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t count_threshold_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t display_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t pesagem_cv = PTHREAD_COND_INITIALIZER;

void *esteira1_thread()
{
    while (1)
    {
        usleep(2000000); // espera 2 segundos
        pthread_mutex_lock(&count_mutex);
        esteira1_count++;
        printf("Item na esteira 1 identificado como seguro!\n");
        if (esteira1_count % MAX_ITEMS == 0 && esteira2_count % MAX_ITEMS == 0)
        {
            pthread_cond_signal(&count_threshold_cv);
        }
        pthread_mutex_unlock(&count_mutex);
    }
    pthread_exit(NULL);
}

void *esteira2_thread()
{
    while (1)
    {
        usleep(1000000); // espera 1 segundo
        pthread_mutex_lock(&count_mutex);
        esteira2_count++;
        printf("Item na esteira 2 identificado como seguro!\n");
        if (esteira1_count % MAX_ITEMS == 0 && esteira2_count % MAX_ITEMS == 0)
        {
            pthread_cond_signal(&count_threshold_cv);
        }
        pthread_mutex_unlock(&count_mutex);
    }
    pthread_exit(NULL);
}

void *display_thread()
{
    while (1)
    {
        usleep(2000000); // espera 2 segundos
        printf("Contagem Esteira 1: %d | Contagem Esteira 2: %d\n", esteira1_count, esteira2_count);
        pthread_cond_signal(&display_cv);
    }
    pthread_exit(NULL);
}

void *pesagem_thread()
{
    while (1)
    {
        pthread_mutex_lock(&count_mutex);
        while ((esteira1_count % MAX_ITEMS) != 0 || (esteira2_count % MAX_ITEMS) != 0)
        {
            pthread_cond_wait(&count_threshold_cv, &count_mutex);
        }
        printf("Iniciando pesagem total de %d itens...\n", MAX_ITEMS * 2);
        peso_total += (esteira1_count * 5) + (esteira2_count * 2);
        printf("Peso total: %.2f kg\n", peso_total);
        esteira1_count = 0;
        esteira2_count = 0;
        pthread_cond_signal(&pesagem_cv);
        pthread_mutex_unlock(&count_mutex);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[4];

    // cria threads
    pthread_create(&threads[0], NULL, esteira1_thread, NULL);
    pthread_create(&threads[1], NULL, esteira2_thread, NULL);
    pthread_create(&threads[2], NULL, display_thread, NULL);
    pthread_create(&threads[3], NULL, pesagem_thread, NULL);

    // espera as threads terminarem
    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // destroi mutex e condicionais
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    pthread_cond_destroy(&display_cv);
    pthread_cond_destroy(&pesagem_cv);

    return 0;
}
