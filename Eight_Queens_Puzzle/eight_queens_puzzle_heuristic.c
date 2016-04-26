/*
 * eight_queens_puzzle_heuristic.c
 *
 *  Created on: Apr 17, 2015
 *  Author: Nick Pershin
 *
 *  Last edited on: Apr 18, 2015
 *  Editor: Nick Pershin
 *
 *
 * Альтернативный подход
 * ---------------------
 *
 * https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BE_%D0%B2%D0%BE%D1%81%D1%8C%D0%BC%D0%B8_%D1%84%D0%B5%D1%80%D0%B7%D1%8F%D1%85#.D0.9E.D1.81.D0.BE.D0.B1.D0.B5.D0.BD.D0.BD.D0.BE.D1.81.D1.82.D0.B8_.D1.80.D0.B5.D1.88.D0.B5.D0.BD.D0.B8.D1.8F
 * 
 * http://www.forum.loveorigami.info/viewtopic.php?f=21&t=564&start=30#p6321
 *
 * About vec.c see: https://github.com/rxi/vec
 *
 *
 * Если решать более общую задачу об N ферзях при помощи описанного выше алгоритма, 
 * то такой перебор вариантов даже с использованием описанных выше сокращений 
 * будет весьма долго работать уже при N = 20, так как 20! = 2.433·10^18.
 * Поэтому представляет особенный интерес следующий эвристический алгоритм, решающий задачу об N ферзях на поле размером N x N. 
 * Он работает для всех N ≥ 4 или N = 1.
 *
 * 
 * BUILD DEBUG:
 *  gcc -std=c99 -I../.. -Wall -g -o eight_queens_puzzle_heuristic utils/vec/vec.c eight_queens_puzzle_heuristic.c
 * BUILD RELEASE:
 *  gcc -std=c99 -I../.. -Wall -O3 -o eight_queens_puzzle_heuristic utils/vec/vec.c eight_queens_puzzle_heuristic.c
 *
 * RUN: 
 *      ./eight_queens_puzzle_heuristic
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "utils/vec/vec.h"


#define LIMIT 99999999 // for 64-bit MAC OS X

#define ANSI_COLOR_RESET        "\x1b[0m"
#define ANSI_COLOR_BLACK        "\x1b[30m"
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_BLUE         "\x1b[34m"
#define ANSI_COLOR_MAGENTA      "\x1b[35m"
#define ANSI_COLOR_CYAN         "\x1b[36m"
#define ANSI_COLOR_WHITE        "\x1b[37m"
#define ANSI_COLOR_B_BLACK      "\x1b[30;1m"
#define ANSI_COLOR_B_RED        "\x1b[31;1m"
#define ANSI_COLOR_B_GREEN      "\x1b[32;1m"
#define ANSI_COLOR_B_YELLOW     "\x1b[33;1m"
#define ANSI_COLOR_B_BLUE       "\x1b[34;1m"
#define ANSI_COLOR_B_MAGENTA    "\x1b[35;1m"
#define ANSI_COLOR_B_CYAN       "\x1b[36;1m"
#define ANSI_COLOR_B_WHITE      "\x1b[37;1m"
#define ANSI_BG_BLACK           "\x1b[40m"
#define ANSI_BG_RED             "\x1b[41m"
#define ANSI_BG_GREEN           "\x1b[42m"
#define ANSI_BG_YELLOW          "\x1b[43m"
#define ANSI_BG_BLUE            "\x1b[44m"
#define ANSI_BG_MAGENTA         "\x1b[45m"
#define ANSI_BG_CYAN            "\x1b[46m"
#define ANSI_BG_WHITE           "\x1b[47m"


int main(int argc, char **argv)
{
    double start, end;
    int mod, idx1, idx3;
    unsigned int N;
    char resp;

/*
    printf(ANSI_COLOR_BLACK     "This text is BLACK"        ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_RED       "This text is RED"          ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_GREEN     "This text is GREEN"        ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW    "This text is YELLOW"       ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_BLUE      "This text is BLUE"         ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_MAGENTA   "This text is MAGENTA"      ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_CYAN      "This text is CYAN"         ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_WHITE     "This text is WHITE"        ANSI_COLOR_RESET "\n");
    printf("\n");
    printf(ANSI_COLOR_B_BLACK   "This text is BOLD BLACK"   ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_B_RED     "This text is BOLD RED"     ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_B_GREEN   "This text is BOLD GREEN"   ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_B_YELLOW  "This text is BOLD YELLOW"  ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_B_BLUE    "This text is BOLD BLUE"    ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_B_MAGENTA "This text is BOLD MAGENTA" ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_B_CYAN    "This text is BOLD CYAN"    ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_B_WHITE   "This text is BOLD WHITE"   ANSI_COLOR_RESET "\n");
    printf("\n");
    printf(ANSI_BG_BLACK        "Background is BLACK"       ANSI_COLOR_RESET "\n");
    printf(ANSI_BG_RED          "Background is RED"         ANSI_COLOR_RESET "\n");
    printf(ANSI_BG_GREEN        "Background is GREEN"       ANSI_COLOR_RESET "\n");
    printf(ANSI_BG_YELLOW       "Background is YELLOW"      ANSI_COLOR_RESET "\n");
    printf(ANSI_BG_BLUE         "Background is BLUE"        ANSI_COLOR_RESET "\n");
    printf(ANSI_BG_MAGENTA      "Background is MAGENTA"     ANSI_COLOR_RESET "\n");
    printf(ANSI_BG_CYAN         "Background is CYAN"        ANSI_COLOR_RESET "\n");
    printf(ANSI_BG_WHITE        "Background is WHITE"       ANSI_COLOR_RESET "\n");
*/

    printf(ANSI_COLOR_B_BLACK"\n\tЗдравствуй, мой повелитель!\n\tЯ - джинн, который умеет решать задачу про шахматных ферзей (и только).\n\n\tИсходная формулировка задачи:\n\t«Расставить на стандартной 64-клеточной шахматной доске 8 ферзей так, чтобы ни один из них не находился под боем другого».\n\tПодразумевается, что ферзь бьёт все клетки, расположенные по вертикалям, горизонталям и обеим диагоналям.\n\tОбобщение задачи — расставить максимальное количество взаимно не бьющих друг друга ферзей на прямоугольном поле (в частности, квадратном поле) со стороной N.\n\n\tДля решения этой задачи я использую эвристический алгоритм.\n\tМой алгоритм пока что решает эту задачу только для квадратных полей.\n\n\tОкажи любезность, введи, пожалуйста, длину стороны квадрата шахматной доски (целое число: единица либо большее трёх, но не более %d): "ANSI_COLOR_RESET, LIMIT);

    scanf("%d", &N);

    if (N > LIMIT) {
        printf(ANSI_COLOR_B_RED"\n\tИЗВИНИ: число не должно быть больше %d, мой повелитель!\n\tДо новых встреч...\n\n"ANSI_COLOR_RESET, LIMIT);
        return -1;
    }

    if (N < 4 && N != 1) {
        // this algorythm works only for N ≥ 4 or N = 1
        printf(ANSI_COLOR_B_RED"\n\tИЗВИНИ: целое число должно быть больше трёх, либо единицей, мой повелитель!\n\tДо новых встреч...\n\n"ANSI_COLOR_RESET);
        return -1;
    }

    printf(ANSI_COLOR_B_BLACK"\n\tСлушаюсь и вычисляю для квадрата со стороной %u, о господин мой...\n\n"ANSI_COLOR_RESET, N);

    start = clock();

    // create & init a vector of integers
    vec_uint_t L;
    vec_init(&L);

    // 1) 
    // Разделить N на 12 и запомнить остаток (N будет равно 8 для задачи о восьми ферзях)
    mod = N % 12;

    // 2) 
    // Занести в список все четные числа от 2 до N по порядку
    for (int x = 2; x <= N; x += 2) {
        vec_push(&L, x);
    }

    // 3)
    // Если остаток равен 3 или 9, перенести 2 в конец списка
    if (mod == 3 || mod == 9) {
        vec_push(&L, 2);
        vec_splice(&L, 0, 1);
    }

    // 4)
    // Добавить в список все нечетные числа от 1 до N по порядку, но, 
    // если остаток равен 8, перевернуть пары соседних чисел (например: 3, 1, 7, 5, 11, 9, …).
    if (mod == 8)
    {
        vec_uint_t V;
        vec_init(&V);
        for (int x = 1; x <= N; x += 2) {
            vec_push(&V, x);
        }
        for (int i = 1; i < V.length; i += 2) {
            V.data[i]   = V.data[i] ^ V.data[i-1];
            V.data[i-1] = V.data[i] ^ V.data[i-1];
            V.data[i]   = V.data[i] ^ V.data[i-1];
        }
        for (int i = 0; i < V.length; ++i) {
            vec_push(&L, V.data[i]);
        }
        vec_free(&V);

    } else {
        for (int x = 1; x <= N; x += 2) {
            vec_push(&L, x);
        }
    }

    // 5)
    // Если остаток равен 2 и N ≥ 3, поменять местами 1 и 3
    if (mod == 2 && N > 2) {
        vec_find(&L, 1, idx1);
        vec_find(&L, 3, idx3);
        L.data[idx1] = L.data[idx1] ^ L.data[idx3];
        L.data[idx3] = L.data[idx1] ^ L.data[idx3];
        L.data[idx1] = L.data[idx1] ^ L.data[idx3];

        // 5a)
        // если N ≥ 5, перенести 5 в конец списка
        if (N > 4) {
            vec_find(&L, 5, idx1);
            vec_splice(&L, idx1, 1);
            vec_push(&L, 5);
        }
    }

    // 6)
    // Если остаток равен 3 или 9, переместить 1 и 3 в конец списка
    // (именно в этом порядке, а не в котором они сейчас)
    if (mod == 3 || mod == 9) {
        vec_find(&L, 1, idx1);
        vec_splice(&L, idx1, 1);
        vec_push(&L, 1);

        vec_find(&L, 3, idx3);
        vec_splice(&L, idx3, 1);
        vec_push(&L, 3);
    }
    
    end = clock();
    
    printf(ANSI_COLOR_GREEN"\tЗадача решена всего лишь за %.6lf секунды! Кол-во ферзей = %d\n"ANSI_COLOR_RESET, (end-start)/CLOCKS_PER_SEC, L.length);

    printf(ANSI_COLOR_B_BLACK"\tВывести решение в консоль? (y/n): "ANSI_COLOR_RESET);
    while(getchar()!='\n');
    scanf("%c", &resp);
    resp = tolower(resp);    
    if(resp == 'y') {
        printf("\n\t"ANSI_COLOR_GREEN);
        for (int i = 0; i < L.length; ++i) {
            printf("%u ", L.data[i]);
        }
        printf(ANSI_COLOR_RESET"\n\n");
        printf(ANSI_COLOR_B_BLACK"\tДо свидания, повелитель!\n\n"ANSI_COLOR_RESET);
    } else {
        printf(ANSI_COLOR_B_BLACK"\tДо свидания, повелитель!\n\n"ANSI_COLOR_RESET);
    }

    // 7) 
    // Разместить ферзя в первом столбце и в строке с номером, равным первому элементу списка, 
    // затем поместить следующего ферзя во втором столбце и в строке с номером, 
    // равным второму элементу списка, и т. д.
    // TODO: implementation (!)
    
    // free the vector
    vec_free(&L);

    return 0;
}
