// Выполнил И. Мадиев, АПО-13
// RunID 1564

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ввод письма
char **input_mail();

// Функция поиска нужных строк
char **filter (char **m, size_t size);

// Вывод результата поиска
void output_result(char **result);

int main()
{
	char **file=input_mail();
	if (file==NULL) return 0;
	size_t size_file = 0;
		while (file[size_file] != NULL) 
			size_file++;
	// Удаление ненужного NULL в конце
	file=(char**)realloc(file, (size_file*sizeof(char*)));
	
	char **result=filter(file, size_file);
	if (result==NULL) return 0;

	output_result(result);

	// очищение массива
	for (size_t j = 0; j < size_file; ++j) {
		free(file[j]);
	}
	free(file);
	free(result);

	return 0;
}

char **input_mail()
{
	size_t size_file = 0;
	char **file = (char**)malloc(sizeof(char*));
	if (file == NULL) { printf("[error]"); return NULL; }
	char buffer[2048];
	//чтение файла
	while (fgets(buffer, 2048, stdin) != NULL)
	{
		size_t size_str = 0;
		while (buffer[size_str] != '\0') 
			size_str++;
		//Т.к. сейчас size_str - индекс последнего символа строки
		size_str++;
		file[size_file] = (char*)malloc(size_str * sizeof(char));
		if (file[size_file]==NULL)
		{
			printf("[error]");
			for (size_t j = 0; j < size_file; ++j) 
			{
				free(file[j]);
			}
			free(file);
			return NULL;
		}
		for (size_t i = 0; i < size_str; i++)
			file[size_file][i] = buffer[i];

		size_file++;
		char **buf = (char**)realloc(file, (size_file + 1) * sizeof(char*));
		if (buf == NULL) 
		{
			printf("[error]"); 
			for (size_t j = 0; j < size_file-1; ++j) 
			{
				free(file[j]);
			}
			free(file);
			return 0; 
		}
		file = buf;
		buf=NULL;
	}
	file[size_file]=NULL;
	//проверка на пустой массив
	if (size_file == 0) { free(file); return NULL; }
	return file;
}

char **filter (char **m, size_t size)
{
	char* str[] = {"Date:", "From:", "To:", "Subject:"};
	char **result=NULL;
	size_t str_num=0;
	size_t buf=6;
	result=(char**)malloc((buf)*sizeof(char*));
	if (result==NULL) {printf ("[error]"); return NULL;}
	for (size_t i=0; i<size; i++)
		if ((strstr(m[i], str[0])==m[i])||(strstr(m[i], str[1])==m[i])||(strstr(m[i], str[2])==m[i])||(strstr(m[i], str[3])==m[i]))
		{
			result[str_num]=m[i];
			str_num++;
			if (str_num==buf)
				{
					buf*=2;
					char **buffer=(char**)realloc(result, (buf)*sizeof(char*));
					if (buffer==NULL) 
					{
						printf ("[error]"); 
						free(result); 
						return 0;
					}
					result=buffer;
				}
		}
	result[str_num]=NULL;
	char **buffer=(char**)realloc(result, (str_num+1)*sizeof(char*));
	if (buffer==NULL) 
	{
		printf ("[error]"); 
		free(result); 
		return 0;
	}
	result=buffer;
	return result;
}

void output_result(char **result)
{
	size_t i=0;
	while (result[i]!=NULL)
	{
		printf("%s", result[i]);
		i++;
	}
}
