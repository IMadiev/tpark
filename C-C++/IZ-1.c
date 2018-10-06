// Выполнил И. Мадиев, АПО-13
// RunID 1208

/*
Submit a solution for A- (Variant 9)
Задача A-9. Задача об отображении темы письма
Time limit:	14 s
Memory limit:	64 M

Чтобы показать информацию о пришедшем письме, нужно сначала её найти.
Для этого в файле письма необходимо найти специальные заголовки.

Составить программу построчной фильтрации текста.
Суть фильтра — отбор строк, начинающихся с одного из следующих выражений: «Date:», «From:»,«To:», «Subject:».
Текстовые строки подаются на стандартный ввод программы, результат программы должен подаваться на стандартный вывод.

Процедура фильтрации должна быть оформлена в виде отдельной функции, которой подается на вход массив строк, выделенных в динамической памяти и его длина.
На выходе функция возвращает указатель на NULL-терминированный массив с найденными строками (последним элементом массива добавлен NULL для обозначения, что данных больше нет).

Программа должна уметь обрабатывать возникающие ошибки (например, ошибки выделения памяти). В случае возникновения ошибки нужно вывести в поток стандартного вывода сообщение "[error]" и завершить выполнение программы.

ВАЖНО! Программа в любом случае должна возвращать 0. Не пишите return -1, exit(1) и т.п. Даже если обнаружилась какая-то ошибка, все равно необходимо вернуть 0! (и напечатать [error] в stdout).

*/

// Решение
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
// Функция поиска нужных строк
char **filter (char **m, size_t size)
{
	char str1[] = "From:";
	char str2[] = "To:";
	char str3[] = "Date:";
	char str4[] = "Subject:";
	char **result=NULL;
	size_t str_num=0;
	result=(char**)realloc(result, (str_num+1)*sizeof(char*));
	if (result==NULL) {printf ("[error]"); return 0;}
	for (size_t i=0; i<size; i++)
		if ((strstr(m[i], str1)==m[i])||(strstr(m[i], str2)==m[i])||(strstr(m[i], str3)==m[i])||(strstr(m[i], str4)==m[i]))
		{
			result[str_num]=m[i];
			str_num++;
			result=(char**)realloc(result, (str_num+1)*sizeof(char*));
			if (result==NULL) {printf ("[error]"); return 0;}
		}
	result[str_num]=NULL;
	return result;
}


int main()
{
	size_t size_file = 0;
	char **file = (char**)malloc(sizeof(char*));
	if (file == NULL) { printf("[error]"); return 0; }
	char* buffer = (char*)malloc(2048*sizeof(char));
	if (buffer == NULL) { printf("[error]"); return 0; }
	//чтение файла
	while (fgets(buffer, 2048, stdin) != NULL)
	{
		size_t size_str = 0;
		while (buffer[size_str] != '\0') 
			size_str++;
		size_str++;
		file[size_file] = (char*)malloc(size_str * sizeof(char));
		for (size_t i = 0; i < size_str; i++)
			file[size_file][i] = buffer[i];

		size_file++;
		file = (char**)realloc(file, (size_file + 1) * sizeof(char*));
		if (file == NULL) { printf("[error]"); return 0; }
	}
	//освобождение буфера
	free(buffer);
	//проверка на пустой массив
	if (size_file == 0) { free(file); return 0; }
	//вывод массива
	/*for (size_t i = 0; i < size_file; ++i) 
	{
		printf("%s", file[i]);
	}*/
	
	char **result=filter(file, size_file);
	size_t i=0;
	while (result[i]!=NULL)
	{
		printf("%s", result[i]);
		i++;
	}

	//очищение массива
	for (size_t j = 0; j < size_file; ++j) {
		free(file[j]);
	}
	free(file);
	free(result);

	return 0;
}
