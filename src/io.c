#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "userdata.h"
#include "filetype.h"

// Print data from user input
void print_userdata(UserData *data) {
    printf("--parts k: %d\n--percent x: %.2f%%\n--filetype: %s\n--input: %s\n",
        data->k, data->x, filetype_to_string(data->filetype), data->input);
}

// Test user data for any mistakes
int test_userdata(UserData *data, int n) {
    // Bad file input
    if(strcmp(data->input, "Undefined") == 0) {
        fprintf(stderr, "[!] Brak argumentu dla pliku wejściowego. Przerywam działanie.\n");
        return 1;
    }
    FILE *in = fopen(data->input, "r");
    if(in == NULL) {
        fprintf(stderr, "[!] Plik wejściowy nie istnieje w podanej lokalizacji. Przerywam działanie.\n");
        return 1;
    }

    // Bad number of parts
    if(data->k <= 0) {
        fprintf(stderr, "[!] Liczba docelowych podgrafów musi być większa od 0. Wczytano: '%d'. Przyjęto parametr równy 2.\n", data->k);
        data->k = 2;
    } else if(data->k > n) {
        fprintf(stderr, "[!] Liczba docelowych podgrafów musi być mniejsza od liczby wierzchołków grafu. Wczytano: '%d'. Przyjęto parametr równy liczbie wierzchołków w grafie.\n", data->k);
        data->k = n;
    }

    // Bad number of percent margin
    if(data->x <= 0) {
        fprintf(stderr, "[!] Maksymalna procentowa różnica wielkości podgrafów musi być większa od 0. Wczytano: '%f'. Przyjęto parametr równy 10.\n", data->x);
        data->x = 10;
    } else if(data->x > 100) {
        fprintf(stderr, "[!] Maksymalna procentowa różnica wielkości podgrafów musi być mniejsza lub równa 100. Wczytano: '%f'. Przyjęto parametr równy 100.\n", data->x);
        data->x = 100;
    }

    // Bad filetype
    if(data->filetype == UNKNOWN) {
        fprintf(stderr, "[!] Podany format zapisu nie jest prawidłowy. Przyjęto domyślną wartość 'text'.\n");
        data->filetype = TEXT;
    }

    return 0;
}

// Print available flags
void print_help() {
    printf("--help: wyświetla krótką instrukcję dotyczącą użycia programu oraz dostępnych argumentów;\n"
        "--parts k: określa liczbę podgrafów, na które ma zostać podzielony graf wczytany przez użytkownika; domyślna wartość k = 2;\n"
        "--percent x: określa maksymalną procentową różnicę wielkości szukanych podgrafów; domyślna wartość x = 10;\n"
        "--filetype text|binary: pozwala użytkownikowi wybrać format pliku wyjściowego, "
        "w którym zostaną zapisane znalezione podgrafy (tekstowy lub binarny); domyślna wartość text;\n"
        "--input: filename określa ścieżkę do pliku wejściowego;\n");
}

int *parse_line_to_ints(char *str, const char *delim, int *count) {
    int capacity = 10;
    int cnt = 0;
    int *arr = malloc(capacity * sizeof(int));
    char *token = strtok(str, delim);
    while(token) {
        if(cnt >= capacity) {
            capacity *= 2;
            arr = realloc(arr, capacity * sizeof(int));
        }
        arr[cnt++] = atoi(token);
        token = strtok(NULL, delim);
    }
    *count = cnt;
    return arr;
}