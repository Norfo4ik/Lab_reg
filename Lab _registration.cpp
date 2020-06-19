#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string> 
#include <regex>
#include <fstream>
#include <vector>
using namespace std; // Обьявляем пространство имен STD
int try_ = 3; // Переменная наших попыток
bool flag; // Флаг для проверки правильности входа
void menu() { // Функция меню
    system("cls"); // Очистка консоли перед выводом
    cout << "\n Регистрация и вход пользователя.";
    cout << "\n 1. Регистрация.";
    cout << "\n 2. Вход.";
    cout << "\n 3. Выход.";
}

int get_variant(int count) { // Функция выбора меню
    int variant;
    char s[10]; 
    cout << "\n>>> ";
    scanf("%s", s); // Считываем выбраный вариант
    cin.ignore(); // Сьедаем ентер, т.к он помешает вводу на следующих переменных

 
    while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) { // Проверка на правильность ввода
        cout << "Введено неверное значение! Пожалуйста, повторите ввод.";
        cout << "\n>>> ";
        scanf("%s", s); 
        cin.ignore();// То же самое
    }

    return variant; // Возвращаем полученый вариант
}

int check_login(string login) { // Проверка правильности ввода логина
    cmatch result; // Используем библиотеку регулярных выражений, если интересно, загугли
    regex regular("([\\w\\s]{1,15})"); // Регулярное выражение, по которому проверяем правильность ввода
    if (regex_match(login.c_str(), result, regular)) // Если соответствует правилам
        return true; //Правда
    else {
        cout << "\n Логин не соответсвует параметрам!"; // Нет
        return false; // Ложь
    }
}

int check_pass(string password) {// Проверка правильности ввода пароля
    cmatch result;
    regex regular("([\\w\\d@#]{7,15})"); // То же самое
    if (regex_match(password.c_str(), result, regular))
        return true;
    else {
        cout << "\n Пароль не соответсвует параметрам!";
        return false;
    }
}
string random_pass() { // Генерация случайного пароля
    string pass; // Инициализируем строку
    srand(time(NULL)); // Чтоб каждый раз генерировало случайные числа
    const char alph[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9','@','#','_' };
    for (int i=0; i < 12; i++) { // Исходя из алфавита генерируем случайный пароль функцией псевдорандома
        pass += alph[rand() % 63+1]; // Конкатенация
    }
    return pass;
}
void regestration() { // Функция регистрации
    bool choose; // Переменная выбора генерации пароля
    bool log = false; // Переменные правильности ввода пароля, логина
    bool pass = false;
    string login; // Строки куда вводим пароль и логин
    string password;
    cout << "\n Регистрация нового пользователя.";
    cout << "\n Логин должен состоять только из латинских букв, циф и нижнего подчеркивания.";
    cout << "\n Минимальна длинна пароля - 7 символов, он должен состоять из латинских букв, цифр, и могут быть включены спец знаки: \"@,#,_\"";
    cout << "\n Введите логин"; 
    cout << "\n >>>  ";
    getline(cin, login); // Считываем логин
    log = check_login(login); // Проеверяем
    while (log == false) { // Пока не правильно, просим ввести заново
        cout << "\n Логин введен не правильно!"; 
        cout << "\n Введите логин";
        cout << "\n >>>  ";
        cin.ignore();
        getline(cin, login);
        log = check_login(login); // Так же проверяем правильность входа
    }
    cout << "\nCгенерировать случайный пароль? 1 - Да, 0 - Нет: ";
    cin >> choose;
    if (choose) password = random_pass(); // Генерируем случайный пароль, если запросили
    else {
        cout << "\n Введите пароль:"; // Или пишем свой
        cout << "\n >>>  ";
        cin.ignore();
        getline(cin, password); 
    }
    pass = check_pass(password); // Точно так же проверяем
    while (pass == false) { // Пока не введен правильный пароль просим ввести правилиьный
        cout << "\n Пароль ввден не правильно!";
        cout << "\n Введите пароль:";
        cout << "\n >>>  ";
        getline(cin, password);
        pass = check_pass(password); // Так же его проверяем
    }
            ofstream out; // Ели все ОК, записываем файл
            out.open("D:\\Log_list.txt", ios::app); // Сюда напиши свой путь к файлу, Открываем поток записи и параметр запись в конец файла
            if (out.is_open()) { // Если файл открылся 
                out << "login:" << endl; // Все записываем в файл
                out << login;
                out << "\npassword:" << endl; 
                out << password;
                out << endl;
                out.close(); // Закрываем поток записи
            }
            else {
                cout << "\n Не удается открыть файл!"; // Или выводи ошибку записи в файл
            }

            cout << "\n Поздравляем, вы успешно зарегестрировались!"; // Вывод об успешной регистрации
            cout << "\n Логин: " << login << " Пароль: " << password;
            cout << endl;
            system("pause");
}

void entering() { // Фенкция входа
    string login; // То же, что и в функции регистрации
    string password;
    vector<string> data; // Вектор для выгрузки наших логинов и паролей из файла
    string buf; // Буфферная переменная для записи в файл.
    ifstream in; // Открываем поток чтения
    in.open("D:\\Log_list.txt"); // Сюда нипиши свой путь к файлу
    if (in.is_open()) { //Если файл открыт
        while (!in.eof()) { // Считываем пока не найдем конец файла
            getline(in, buf);
            if (buf == "login:" || buf == "password:" || buf == ""); // Отсеиваем строки, которые нужны для удобства чтения в файле
            else  data.push_back(buf); // Нужное запихиваем в вектор
        }
    }
    else
        cout << "\nОшибка открытия файла!";  // Если не удалось открыть файл
    in.close(); // Закрываем поток чтения

    cout << "\nВведите логин" << endl; // Вводим данные для входа
    cout << ">>> ";
    getline(cin, login);
    cout << "\n Введите пароль: " << endl;
    cout << ">>> ";
    getline(cin, password);
    auto i = data.begin(); // Итератор вектора
    for (i; i < data.end(); ++i) { // Ищем нужные совпаления
        if (*i == login && *(i + 1) == password) // Если все совпадает
        {
            cout << "\nПриветствую, " << login << endl; // Выводим приветствие 
            flag = false; // Флаг не трогаем 
            system("pause");
            break;
        }
        else { // Если не нашли
            flag = true; // Меняем флаг
        }
        if (i < data.end()) ++i; // Пока не конец вектора, Заранее увеличиваем і, потому что логин и пароль в паре находяться в векторе, т.е і - логин, і+1 - пароль 

    }

    while (flag && try_ != 1) { // Пока флаг и попытки есть
        cout << "\nВведен непрвильный логин или пароль! Осталось " << try_ - 1 << " попыток"; //Вводим новый пароль
        try_--; // Уменьшаем попытки
        entering(); // Заново вызываем нашу функцию 
    }

}


int main()
{
    int variant; //Выбор варианта
    setlocale(LC_ALL, "rus"); // Локализируем на русский
    do { // Пока все ок вызываем меню
        menu(); 

        variant = get_variant(3); // Считываем вариант

        switch (variant) { //Выбираем пункт по введенному варианту
        case 1:
            system("cls"); // Очищаем
            regestration(); // Вызываем регистрацию
            system("cls"); // Очищаем
            break;

        case 2:
            system("cls"); // Очищаем
            try_ = 3; // Перед каждым вызовом входа обновляем значение, иначе после первых 3х попыток будет сразу выкидывать
            entering(); // Вызываем вход
            if (try_ == 1) { // Если кол-во попыток исчерпали, говорим пока
                cout << "\n Превышено попыток ввода, попробуйте позже!" << endl;
                system("pause");
            }
            break;

        case 3:
            system("cls"); // Выход из проги
            cout << "\n Завершение работы....." << endl;
            system("pause");
            break;
        }
    } while (variant != 3); // Пока не введем пункт выхода

    return 0;
}
