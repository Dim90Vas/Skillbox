#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROGRAM 1 //выбор программы для компиляции

#if PROGRAM==1 //запуск первой программы
#define MAX_SIZE 100 //максимальное количество учеников
#define M 30 //Размер массива

struct student_data { //{"vas","dim","val",'m',7,"matem",5},{"pet","art","ser",'m',7,"matem",4},{"gor","ale","geo",'m',7,"matem",2},{"brt","eka","vik",'w',7,"matem",3},
    char surname[M];  //{"kar","ele","vas",'w',7,"matem",2},{"mar","lud","igo",'w',7,"matem",3},{"pis","mix","evg",'m',7,"matem",2},{"mis","nat","iva",'w',7,"matem",4},
    char name[M];     //{"kar","uli","pet",'w',7,"matem",3},{"fro","and","iva",'m',7,"matem",4},{"loz","vyc","vyc",'m',7,"matem",4},{"hra","tat","nik",'w',7,"matem",4},
    char patronymic[M];
    char gender;
    int training_class;
    char item_name[M];
    int diagnostic;
};

// Функция для удаления символа новой строки из строки
void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Заполнение журнала и возврат количества учеников
int filling_journal(struct student_data person[]) {
    int numStudents = 0;
    printf("Enter people details (press ENTER to finish)\n");
    while (numStudents < MAX_SIZE) {
        printf("Enter your last name: ");
        fgets(person[numStudents].surname, M, stdin);
        remove_newline(person[numStudents].surname); // Удаляем символ новой строки
        // Проверка на окончание ввода
        if (strlen(person[numStudents].surname) == 0) {
            return numStudents;
        }
        printf("Enter your first name: ");
        fgets(person[numStudents].name, M, stdin);
        remove_newline(person[numStudents].name);
        printf("Enter your middle name: ");
        fgets(person[numStudents].patronymic, M, stdin);
        remove_newline(person[numStudents].patronymic);
        printf("Enter gender (m/f): ");
        scanf(" %c", &person[numStudents].gender); // Пробел перед %c игнорирует пробельные символы
        getchar(); // Убираем символ новой строки из буфера
        printf("Enter training class: ");
        scanf("%d", &person[numStudents].training_class);
        getchar(); // Убираем символ новой строки из буфера
        printf("Enter item name: ");
        fgets(person[numStudents].item_name, M, stdin);
        remove_newline(person[numStudents].item_name);
        printf("Enter diagnostic: ");
        scanf("%d", &person[numStudents].diagnostic);
        getchar(); // Убираем символ новой строки из буфера
        numStudents++;
    }
    return numStudents;
}

//средний балл всех учеников
float average_score_students(struct student_data person[], int numStudents) {
    int n=0;
    for(int i=0; i<numStudents; i++) {
        n+=person[i].diagnostic;
    }
    return (float)n/numStudents;
}

//ввспомогательная функция для сортировки по успеваемости
int compareStudents(const void* a, const void* b) {
    return ((struct student_data*)a)->diagnostic - ((struct student_data*)b)->diagnostic;
}

int main() {                                    //для проверки
    struct student_data person[MAX_SIZE];/*={{"vas","dim","val",'m',7,"matem",5},{"pet","art","ser",'m',7,"matem",4},{"gor","ale","geo",'m',7,"matem",2},
                                          {"brt","eka","vik",'f',7,"matem",3},{"kar","ele","vas",'f',7,"matem",2},{"mar","lud","igo",'f',7,"matem",3},
                                          {"pis","mix","evg",'m',7,"matem",2},{"mis","ana","iva",'m',7,"matem",4},{"kar","uli","pet",'f',7,"matem",3},
                                          {"fro","and","iva",'m',7,"matem",4},{"loz","vyc","vyc",'m',7,"matem",4},{"hra","tat","nik",'f',7,"matem",4}};*/
    int numStudents = filling_journal(person);
    printf("Number of students in a class: %d\n",numStudents);
    printf("Average score of students: %0.2f\n",average_score_students(person,numStudents));
    qsort(person, numStudents, sizeof(struct student_data), compareStudents); //сортировка по успеваемости
    for(int i=numStudents-1; i>=0; i--) {
        printf("%s %s %s %c %d %s %d\n",person[i].surname,person[i].name,person[i].patronymic,person[i].gender,person[i].training_class,person[i].item_name,person[i].diagnostic);
    }

    int male=0, female=0;
    float sr_male=0, sr_female=0;
    for(int i=numStudents-1; i>=0; i--) {
        if(person[i].gender=='m') {
            sr_male+=person[i].diagnostic;
            male++;
        } else {
            sr_female+=person[i].diagnostic;
            female++;
        }
    }
    printf("Average score of all in the class: %0.2f\n",sr_male/male);
    printf("Average score of all girls in the class: %0.2f\n",sr_female/female);
    return 0;
}
//=====================================================================================================================================================

#elif PROGRAM==2 //запуск второй программы
#define STR_LEN 60
#define SIZE_LIBRARY 15

struct biblio {
    char fio[STR_LEN]; //фио автора
    char title[STR_LEN]; //название книги
    char isbn[STR_LEN]; //издание
    int year_publication; //год издания
};

int main() {
    setlocale(0,"Russian");
    struct biblio book[SIZE_LIBRARY] = {{"Пушкин Александр Сергеевич", "Стихи и сказки для взрослых", "Блок-Принт", 2025},
                              {"Дюма Александр", "Граф Монте-Кристо", "Азбука", 2023},
                              {"Пелевин Виктор Олегович", "Generation П", "Эксмо", 2020},
                              {"Достоевский Федор Михайлович", "Преступление и наказание", "АСТ", 2015},
                              {"Булгаков Михаил Афанасьевич", "Мастер и Маргарита", "Азбука", 2024},
                              {"Дойл Артур Конан", "Приключения Шерлока Холмса", "Эксмо", 2022},
                              {"Грибоедов Александр Сергеевич", "Горе от ума", "Азбука", 2024},
                              {"Лермонтов Михаил Юрьевич", "Герой нашего времени", "АСТ", 2023},
                              {"Гончаров Иван Александрович", "Обломов", "Альпина. Проза", 2023},
                              {"Гоголь Николай Васильевич", "Мертвые души", "АСТ", 2024},
                              {"Уайльд Оскар", "Портрет Дориана Грея", "Эксмо", 2024},
                              {"Леонардо да Винчи", "О науке и искусстве", "АСТ", 2024},
                              {"Паланик Чак", "Бойцовский клуб", "АСТ", 2024},
                              {"Толстой Лев Николаевич", "Война и мир", "Азбука", 2021},
                              {"Иванов Анатолий Степанович", "Тени исчезают в полдень", "Азбука", 2024}};
    char cmp[STR_LEN];
    scanf("%s", cmp);
    int count = sizeof(book)/sizeof(book[0]);
    for(int i=0; i<count; i++) {
        if(strstr(book[i].title, cmp)) {
            printf("%s\t%s\t%s\t%d\n", book[i].title, book[i].isbn, book[i].fio, book[i].year_publication);
        }
    }
    return 0;
}
//=====================================================================================================================================================
#elif PROGRAM==3 //запуск третьей программы
#define STAFF 15 //общее число сотрудников
#define M 50

//структура компании
struct employee_data {
    char fio[M];
    int age;
    char gender;
    char post[M];
};

//подсчет мужчин
int counting_men(struct employee_data company[]) {
    int count_m = 0;
    for(int i=0; i<STAFF; i++) {
        if(company[i].gender=='M')
            count_m++;
    }
    return count_m;
}

//высчитываем средний возраст
int average_employees(struct employee_data company[], int employees) {
    int sr = 0;
    for(int i=0; i<employees; i++) {
        sr += company[i].age;
    }
    return sr/employees;
}

//медианный возраст
int median_age(struct employee_data company[], int employees) {
    int massage[employees];
    for(int i=0; i<employees; i++) { //переносим в отдельный массив возроста всех сотрудников
        massage[i]=company[i].age;
    }
    for(int i = 0 ; i < employees - 1; i++) { //сортируем элементы массива по возрастанию
       for(int j = 0 ; j < employees - i - 1 ; j++) {
           if(massage[j] > massage[j+1]) {
              int tmp = massage[j];
              massage[j] = massage[j+1] ;
              massage[j+1] = tmp;
           }
        }
    }
    return massage[employees/2]; //возвращаем медианный возраст
}

//деление по половому признаку
void divide_by_gender(struct employee_data company[],struct employee_data gender[], char gend) {
    int n=0;
    for(int i=0; i<STAFF; i++) {
        if(company[i].gender==gend) {
            gender[n].age=company[i].age;
            n++;
        }
    }
}

int main() {
    struct employee_data company[STAFF] = {{"Kipling Carter", 39, 'M', "manager"},
                                           {"Hall Caroline", 28, 'W', "manager"},
                                           {"Ackart Gavin", 33, 'M', "manager"},
                                           {"Patton Grace", 28, 'W', "manager"},
                                           {"Ace Gabriel", 22, 'M', "manager"},
                                           {"Acheson Gladys", 23, 'W', "manager"},
                                           {"Haley Agatha", 35, 'W', "manager"},
                                           {"Ackerley Jordan", 28, 'M', "manager"},
                                           {"Langhorn Catherine", 31, 'W', "manager"},
                                           {"Hale Lucas", 28, 'M', "manager"},
                                           {"Kinsley Adelina", 27, 'W', "secretary"},
                                           {"Kirby Mason", 28, 'M', "manager"},
                                           {"Patrick Nicholas", 45, 'M', "director"},
                                           {"Langley Neil", 28, 'M', "manager"},
                                           {"Langston Caleb", 40, 'M', "engineer"}};
    int mens = counting_men(company);
    int womens = STAFF-mens;
    printf("Number of men in the company: %d\n", mens);
    printf("Number of women in the company: %d\n", womens);
    struct employee_data men[mens];
    divide_by_gender(company, men, 'M');
    struct employee_data women[womens];
    divide_by_gender(company, women, 'W');
    printf("Average age of employees: %d\n", average_employees(company, STAFF));
    printf("Median age of employees: %d\n", median_age(company, STAFF));
    printf("Average age of mens: %d\n", average_employees(men, mens));
    printf("Median age of mens: %d\n", median_age(men, mens));
    printf("Average age of womens: %d\n", average_employees(women, womens));
    printf("Median age of womens: %d\n", median_age(women, womens));
    return 0;
}
#endif
