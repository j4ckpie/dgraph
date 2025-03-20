#include <stdio.h>

#include "userdata.h"

// Print data from user input
void print_userdata(userdata *data) {
    printf("--parts k: %d\n--percent x: %d%%\n--filetype: %s\n--input: %s\n",
        data->k, data->x, data->filetype, data->input);
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