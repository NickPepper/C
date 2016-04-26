//
// reverse.cpp
// превращает строку в "перевёртыш"
//

//
// пример определения длины массива динамически
// (но в данном случае это не сработает корректно):
//
//int n = sizeof(stro) / sizeof(stro[0]);
//int n = sizeof stro / sizeof *stro;
//int n = sizeof(str) / sizeof(char);
//

#include <iostream>

using namespace std;


int main()
{
    void reverse(char*, int); // prototype

    cout << endl;

    //char str[] = "Превед"; // TODO: big troubles with unicode!
    char str[] = "ABCDE";
    const int STRLEN = 5;

    cout << "Входная строка: " << str << endl;

    reverse(str, STRLEN);

    cout << endl;

    cout << "Перевёрнутая строка: " << str << endl;

    cout << endl;

    return 0;
}


void reverse(char *str, int n)
{
    cout << endl;

    int head = 0;
    int middle = n >> 1;
    int tail = --n;

    cout << "middle: " << middle << endl;

    while(head < middle) {
        str[head] = str[head] ^ str[tail];
        str[tail] = str[head] ^ str[tail];
        str[head] = str[head] ^ str[tail];

        ++head;
        --tail;
    }

}
