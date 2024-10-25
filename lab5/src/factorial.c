#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <getopt.h>

typedef struct {
    int k;          // Число, факториал которого нужно вычислить
    int pnum;      // Количество потоков
    int mod;       // Модуль
    int thread_id; // ID потока
} ThreadData;

pthread_mutex_t mutex;
long long result = 1; // Общий результат

void *factorial_part(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    long long partial_result = 1;
    
    // Вычисление факториала для диапазона
    for (int i = data->thread_id + 1; i <= data->k; i += data->pnum) {
        partial_result = (partial_result * i) % data->mod;
    }

    // Синхронизация доступа к общему результату
    pthread_mutex_lock(&mutex);
    result = (result * partial_result) % data->mod;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[]) {
    int k = 0, pnum = 1, mod = 1;

    // Обработка аргументов командной строки
    int opt;
    while ((opt = getopt(argc, argv, "k:p:m:")) != -1) {
        switch (opt) {
            case 'k':
                k = atoi(optarg);
                break;
            case 'p':
                pnum = atoi(optarg);
                break;
            case 'm':
                mod = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -k <number> -p <threads> -m <modulus>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (k <= 0 || pnum <= 0 || mod <= 0) {
        fprintf(stderr, "Invalid arguments. Ensure k, pnum, and mod are positive integers.\n");
        return 1;
    }

    // Инициализация мьютекса
    pthread_mutex_init(&mutex, NULL);
    pthread_t *threads = malloc(sizeof(pthread_t) * pnum);
    ThreadData *thread_data = malloc(sizeof(ThreadData) * pnum);

    // Создание потоков
    for (int i = 0; i < pnum; i++) {
        thread_data[i].k = k;
        thread_data[i].pnum = pnum;
        thread_data[i].mod = mod;
        thread_data[i].thread_id = i; // Передаем ID потока
        pthread_create(&threads[i], NULL, factorial_part, &thread_data[i]);
    }

    // Ожидание завершения потоков
    for (int i = 0; i < pnum; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Factorial of %d modulo %d is %lld\n", k, mod, result);

    // Освобождение ресурсов
    pthread_mutex_destroy(&mutex);
    free(threads);
    free(thread_data);
    
    return 0;
}
