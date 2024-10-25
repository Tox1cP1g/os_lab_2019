#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    // Создаем новый аргумент для передачи в программу sequential_min_max
    char *args[] = {"./sequential_min_max", "42", "10", NULL}; // Обратите внимание на './'

    // Запускаем sequential_min_max в отдельном процессе
    if (execvp(args[0], args) == -1) {
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }

    return 0; // Эта строка никогда не будет достигнута, если exec успешен
}
