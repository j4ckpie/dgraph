#include <stdio.h>
#include <string.h>

#include "userdata.h"

// Print data from user input
void print_userdata(userdata *data) {
    printf("--parts k: %d\n--percent x: %d%%\n--filetype: %s\n--input: %s\n",
        data->k, data->x, data->filetype, data->input);
}

// Test user data for any mistakes
int test_userdata(userdata *data) {
    // Bad input
    FILE *in = fopen(data->input, "r");
    if(in == NULL) {
        fprintf(stderr, "[!] Plik wejściowy nie istnieje w podanej lokalizacji. Przerywam działanie.\n");
        return 1;
    }
    // Get number of vertices
    char line[256];
    int n;
    if (fgets(line, sizeof(line), in) != NULL) {
        sscanf(line, "%d", &n);
    } else {
        printf("[!] Plik jest pusty lub wystąpił błąd.\n");
    }
    fclose(in);

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
        fprintf(stderr, "[!] Maksymalna procentowa różnica wielkości podgrafów musi być większa od 0. Wczytano: '%d'. Przyjęto parametr równy 10.\n", data->x);
        data->x = 10;
    } else if(data->x > 100) {
        fprintf(stderr, "[!] Maksymalna procentowa różnica wielkości podgrafów musi być mniejsza lub równa 100. Wczytano: '%d%%'. Przyjęto parametr równy 100.\n", data->x);
        data->x = 100;
    }

    // Bad filetype
    if(strcmp(data->filetype, "text") != 0 && strcmp(data->filetype, "binary") != 0) {
        fprintf(stderr, "[!] Podany format zapisu nie jest prawidłowy. Przyjęto domyślną wartość 'text'.\n");
        data->filetype = "text";
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