/*

C - C++:
int *ptr = (int*)malloc(sizeof(int)) - int *ptr = new int
int *ptrArr = (int*)malloc(sizeof(int)*N) - int *ptr = new int[n]
free(ptr) = delete ptr
free(ptrArr) - delete[] ptrArr


1. Да, в С++ необходимо освобождать выделенную память. Зачем? Подробнее почитала об этом в Интернете, где сказано, что
"Никаких причин освобождения памяти перед завершением программы, кроме чисто эстетических, нет. Но если ваш проект большой, то скорее всего 
у вас не будет полного обзора того, что какой модуль делает. В такой ситуации лучше придерживаться дисциплинированного подхода и чистить за 
собой.". 

2. Выделенную память можно освобождать сколько угодно, но это не имеет никакого практического смысла.

3. Нет, нельзя. Delete использует указатели, а указатель на участок памяти, на которой не была выделена памяти, равен NULL

*/

#include <iostream>

int *FibonacciTriangle (int size){ //для расчета треугольника Фибоначчи определим отдельную функцию 

    int* ptrarray = new int[size * size];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) { //если элементы массива по диагонали
                *(ptrarray + i * size + j) = 1;
            }
            else if (i < j) { //если элементы массива выше диагонали
                *(ptrarray + i * size + j) = 0;
            }
            else if (j == 0) {
                *(ptrarray + i * size + j) = *(ptrarray + (i - 1) * size + (j + 1)) * 2;
            }
            else { //если элементы массива ниже диагонали
                if (((i % 2 == 1) && (j % 2 == 1)) || ((i % 2 == 0) && (j % 2 == 0))) {
                    //смотрим четность и нечетность столбцов, чтоб понять, где пропуски
                    *(ptrarray + i * size + j) = *(ptrarray + (i - 1) * size + (j - 1)) + *(ptrarray + (i - 1) * size + (j + 1));
                }
                else {
                    *(ptrarray + i * size + j) = 0;
                }
            }

        }

    }

    return ptrarray;
}

int main()
{
    int size;
    std::cout << "Enter counts of strings for Fibonacci triangle: " << std::endl;
    std::cin >> size;

    int * ptrarray = FibonacciTriangle(size); 

    std::cout << "Fibonacci triangle" << std::endl;

    for (int i = 0; i < size; std::cout << std::endl, i++) {
        for (int j = 0; j < size; j++) {
            if (*(ptrarray + i * size + j) == 0) {
                std::cout << " " << "\t";
            }
            else
                std::cout << *(ptrarray + i * size + j) << "\t";
        }
    }

    delete[] ptrarray; //освобождаем память

    return 0;
}
