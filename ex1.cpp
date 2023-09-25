/*

1) strlen - size()
2) Необходимо прописывать самим, аналогов нет
strcpy - string a = "любая строчка"; string b; a = b;
3) strcmp - compare()
4) strcat - strcat()
5) someString[index] - a.at(index) (getting the character at index)
6) Необходимо прописывать самим, аналогов нет
char str[7] = "Hello"; arr[5] = new_value; - push_back
7) Необходимо прописывать самим, аналогов нет
char str[5] = "Hello"; str[strlen(str) - 1] = "\0"; - pop_back 

Разница строк в С и С++: 
В С как таковых строк нет. Строку принято записывать в виде массива элементов типа char. Они заканчиваются нулевым байтом. Управлять 
памятью сложнее.
Строки в C++ реализуются с помощью библиотеки <string>. Их использовать гораздо эффективнее, чем строки С, так как они связаны
с автоматическими функциями управления памятью, что делает их намного безопаснее и проще

*/

#include <iostream>
#include <string>

//объявим функцию для сортировки строки в алфавитном порядке. Я создала отдельную функцию,
//т.к. я рассматриваю случай, когда в строке могут содержаться и большие, и маленькие буквы
//(об этом подробнее ниже). Соответственно, сортировку придется применять два раза: для строки
//с большими буквами и для строки с маленькими. Проще выразить сортировку через функцию, чем 
//прописывать ее два раза.

std::string СombSort(std::string str) { //функция сортировки пузырьком
    char sym;

    if (str.length() == 0) {
        str = "*"; //если строка оказалась пустой, заменим ее на звездочку (если этого не сделать,
        //в дальнейшем будут возникать ошибки
    }

    for (int i = 0; i < str.length() - 1; i++) {
        for (int j = 0; j < str.length() - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                sym = str[j];
                str[j] = str[j + 1];
                str[j + 1] = sym;
            }
        }
    }
    return str;
}

int main()
{
    std::string str;
    char array[] = {',', '-', '.', '?', '!', ':', '"', ' ', ';'}; //массив символов, которые надо исключить
    std::cout << "Enter your string: " << std::endl;
    getline(std::cin, str); //позволяет считать строку с пробелами
    int size_arr = std::size(array); //вычисляет длину массива

    //удаляем лишние символы
    for (int k = 0; k < size_arr; k++) {
        for (int g = 0; g < str.length(); g++) {
            if (array[k] == str[g]) {
                str.erase(g, 1); //удаление символа
            }
        }
    }
    
    //не забудем рассмотреть случай, когда в строке имеются и прописные, и строчные буквы
    //тогда мы создадим 2 новые строки, в одной из которых будут большие буквы, а в другой
    //маленькие

    std::string BIGstr;
    std::string SMALLstr;

    for (int q = 0; q < str.length(); q++) {
        if ((str[q] >= 'A') && (str[q] <= 'Z')) {
            BIGstr.push_back(str[q]); //добавляет в конец строки большую букву
        }
        else {
            SMALLstr.push_back(str[q]); //добавляет в конец строки маленькую букву
        }
    }
    
    std::string sort_BIGstr = СombSort(BIGstr); //отсортированные большие буквы
    std::string sort_SMALLstr = СombSort(SMALLstr); //отсортированные маленькие буквы

    std::string new_result_string; //результирующая строка
    int w = 0;

    while ((sort_BIGstr.length() != 0) || (sort_SMALLstr.length() != 0)) {
        if ((sort_BIGstr.length() != 0) && (sort_SMALLstr.length() != 0)) {
            if (int(sort_BIGstr[w]) == int(sort_SMALLstr[w] - 32)) { //для сравнения используем ASCII
                new_result_string.push_back(sort_BIGstr[w]);
                sort_BIGstr.erase(std::begin(sort_BIGstr));
            }
            else if (int(sort_BIGstr[w]) < int(sort_SMALLstr[w] - 32)) {
                new_result_string.push_back(sort_BIGstr[w]);
                sort_BIGstr.erase(std::begin(sort_BIGstr));
            }
            else {
                new_result_string.push_back(sort_SMALLstr[w]);
                sort_SMALLstr.erase(std::begin(sort_SMALLstr));
            }
        }
        else if ((sort_BIGstr.length() == 0) && (sort_SMALLstr.length() != 0)) {
            new_result_string.push_back(sort_SMALLstr[w]);
            sort_SMALLstr.erase(std::begin(sort_SMALLstr));
        }
        else if ((sort_BIGstr.length() != 0) && (sort_SMALLstr.length() == 0)) {
            new_result_string.push_back(sort_BIGstr[w]);
            sort_BIGstr.erase(std::begin(sort_BIGstr));
        }
    }

    //в начале мы указали, что если строка содержит только большие или только маленькие символы,
    //то мы будем получать звездочку вместо строки с большими или с маленькими символами. 
    // Эта звездочка будет в начале. Уберем ее:
    if (new_result_string[0] == '*') {
        new_result_string.erase(std::begin(new_result_string));
    }

    std::cout << new_result_string << std::endl;

    return 0;
}
