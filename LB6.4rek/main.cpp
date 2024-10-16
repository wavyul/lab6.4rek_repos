#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

void create(int* arr, int SIZE, int MIN, int MAX, int i)
{
    if (i < SIZE)
    {
        arr[i] = MIN + rand() % (MAX - MIN + 1);
        create(arr, SIZE, MIN, MAX, ++i);
    }
}

void Print(int* arr, const int SIZE, int i)
{
    cout << setw(4) << arr[i];
    if (i < SIZE - 1)
        Print(arr, SIZE, i + 1);
    else
        cout << endl;
}

int findMinMod(int* arr, int SIZE, int minMod, int i)
{
    if (i < SIZE)
    {
        if (abs(arr[i]) < minMod)
        {
            minMod = abs(arr[i]);
        }
        return findMinMod(arr, SIZE, minMod, ++i);
    }
    else return minMod;
}

int sumModsAfterZero(int* arr, int SIZE, int sum, bool foundZero, int i)
{
    if (i < SIZE)
    {
        if (arr[i] == 0)
        {
            foundZero = true;
        }
        if (foundZero)
        {
            sum += abs(arr[i]);
        }
        return sumModsAfterZero(arr, SIZE, sum, foundZero, ++i);
    }
    return sum;
}

void copyArray(int* arr, int* tempArr, int SIZE, int i)
{
    if (i >= SIZE) {
        return;
    }

    arr[i] = tempArr[i];
    copyArray(arr, tempArr, SIZE, i + 1);
}

void rearrangeArray(int* arr, int SIZE, int* tempArr, int evenIndex, int oddIndex, int i)
{
    if (i < SIZE)
    {
        if (i % 2 == 0)
        {
            tempArr[evenIndex] = arr[i];
            rearrangeArray(arr, SIZE, tempArr, evenIndex + 1, oddIndex, i + 1);
        }
        else
        {
            tempArr[oddIndex] = arr[i];
            rearrangeArray(arr, SIZE, tempArr, evenIndex, oddIndex + 1, i + 1);
        }
    }
    else
    {
        copyArray(arr, tempArr, SIZE, 0);
    }
}

int main()
{
    srand((unsigned)time(NULL));

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int SIZE;
    cout << "Введіть розмір масиву (SIZE): "; cin >> SIZE;

    int MIN = -20, MAX = 20;

    int* arr = new int[SIZE];
    create(arr, SIZE, MIN, MAX, 0);

    Print(arr, SIZE, 0);
    cout << endl;
    cout << "Мінімальний за модулем елемент масиву: " << findMinMod(arr, SIZE, INT_MAX, 0) << endl;
    cout << "Сума модулів елементів масиву, розташованих після першого елементу, рівного нулю: " << sumModsAfterZero(arr, SIZE, 0, false, 0) << endl;

    int* tempArr = new int[SIZE];
    rearrangeArray(arr, SIZE, tempArr, 0, SIZE / 2, 0);

    cout << endl;
    Print(arr, SIZE, 0);

    delete[] arr;
    delete[] tempArr;

    return 0;
}
