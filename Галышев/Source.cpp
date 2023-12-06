/*Бинарные файлы.
  Ввод/вывод с использованием функций библиотек языка C
  Программа работы с базой данных "Телефонной сети;"
  Создание базы
  Добавление новых записей
  Просмотр базы
  Поиск телефонных разговоров по номеру телефону с созданием файла выборки
  Сортировка телефонных разговоров по стоимости тарифа
  Удаление всех данных.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#define FNAME_city "./city2.dat"	//имя файла с исходной базой
#define FNAME_call "./call2.dat"	//имя файла с исходной базой
#define FNAME_tarif "./tarif2.dat"	//имя файла с исходной базой
#define FNAME_R "./poisknumber.dat" 	//имя файла с результатами поиска
int proverka_file(const char*, const char*);	//проверка наличия файла
void dobavkacall(const char* fname, const char* fname2, const char* fname3);
void  dobavkacity(const char* fname1);
void  dobavkatarif(const char* fname1);

void zagcalls();
void zagapoisknumber();
void zagcity();
void zagtarif();

void prosmotrbdcity(const char* fname);
void prosmotrbdtarif(const char* fname);
void prosmotrbdcall(const char* fname, const char* fname2, const char* fname3);
void prosmotrbdpoisnumber(const char* fname, const char* fname2, const char* fname3);
void poiskphonenumber(const char* fname1, const char* fname2);
void sort_tarifprice(const char* fname);

const char PR_R[] = "rb";	//признак открытия бинарного файла на чтение
const char PR_S[] = "r+b";	//признак открытия файла на чтение и запись
const char PR_W[] = "wb";	//признак открытия файла на запись
const char PR_A[] = "ab";	//признак открытия файла на добавление
typedef struct calls {

	int idPhone;            //ключ
	char surname[20];      //Фамилия 
	char name[15];         //Имя
	char patronymic[20];   //Отчество
	int idcallcyty;         //ключ города
	char phonenumber[8];	//номер телефона
	char date[11];	        //Дата разговора
	int tarifcall;          //Ключ тарифа
	int monthspay;         //Абонентская плата 

}tripcalls;
typedef struct city {

	int idcodecity;         //
	char cityname[50];      //Название города
	int codeccity;      //код города 

}tripcity;
typedef struct tarif {

	int idtarif;
	char tarifname[50];      //название тарифа

}triptarif;

//main_Begin______________________________________________________________
int main()
{
	char name[50];
	int var = 0;
	char otv;
	char fname_call[60] = FNAME_call;
	char fname_r[60] = FNAME_R;
	char fname_city[60] = FNAME_city;
	char fname_tarif[60] = FNAME_tarif;
	setlocale(LC_ALL, "Russian");
	for (; ;)
	{//Выбор вида действия
		printf("\n    Вид действия:\n");
		printf("  1 - Создание базы данных\n");
		printf("  2 - Добавление новых записей в базу данных \n");
		printf("  3 - Просмотр данных в базу данных \n");;
		printf("  4 - Поиск данных по номеру телефона\n");
		printf("  5 - Просмотр информации по поиску телефона\n");
		printf("  6 - Сортировка телефонных разговоров по стоимости тарифа \n");
		printf("  7 - Удалить данные из базы данных. \n");
		printf("  8 - Выход из программы\n");
		printf("  Введите вид действия ->");
		scanf("%i", &var);
		switch (var)
		{
		default:break;
		case 1: 
			if (proverka_file(fname_call, PR_R) && proverka_file(fname_city, PR_R) && proverka_file(fname_tarif, PR_R)) {
				printf(" Создаём файл с новым именем? [Y/N] ");
				while ((otv = getchar()) == '\n');
				if (otv == 'Y' || otv == 'y') {
				printf(" Задайте имя создаваемого файла: ");
				scanf("%s", fname_call);
				} else {
				printf(" Задайте имя  базы: ");
				scanf("%s", fname_call);
				break;
				}
			}
			if (proverka_file(fname_call, PR_W) && proverka_file(fname_city, PR_W) && proverka_file(fname_tarif, PR_W)) {
				printf(" Создаем базу ", fname_call);
				getchar();
				printf("\n Создание базы закончено.\n");
				FILE* file = fopen(fname_city, PR_W);
				FILE* file2 = fopen(fname_tarif, PR_W);
				fclose(file);
				fclose(file2);
			} else {
				printf("\n Ошибка открытия файла для записи\n");
				break;
			}

			if ((proverka_file(fname_call, PR_R) && proverka_file(fname_city, PR_R) && proverka_file(fname_tarif, PR_R))) {
				printf(" База данных готова к работе\n");
			} else printf("\n база не создана\n");

			break;

		case 2: 
			if (proverka_file(fname_call, PR_R) && proverka_file(fname_city, PR_R) && proverka_file(fname_tarif, PR_R)) {
				int vibors = 0;
				printf("\n    Выберите таблицу:\n");
				printf("  1 - Город\n");
				printf("  2 - Тариф\n");
				printf("  3 - Разговоры\n");
				printf("  4 - Вернуться назад\n");
				printf("  Введите вид действия ->");
				scanf("%i", &vibors);
				if (vibors == 1) {
					dobavkacity(fname_city);
					break;
				}
				else if (vibors == 2) {
					dobavkatarif(fname_tarif);
					break;
				} else if (vibors == 3) {
					dobavkacall(fname_call, fname_city, fname_tarif);
					break;
				} else {
					break;
				}
				printf("\n Ошибка открытия файла для чтения\n");
				break;
			}

		case 3: 
			if (proverka_file(fname_call, PR_S) && proverka_file(fname_city, PR_S) && proverka_file(fname_tarif, PR_S)) {
				int vibors = 0;
				printf("\n    Выберите таблицу:\n");
				printf("  1 - Город\n");
				printf("  2 - Тариф\n");
				printf("  3 - Разговоры\n");
				printf("  4 - Вернуться назад\n");
				printf("  Введите вид действия ->");
				scanf("%i", &vibors);
				if (vibors == 1) {
					prosmotrbdcity(fname_city);
					break;
				}
				else if (vibors == 2) {
					prosmotrbdtarif(fname_tarif);
					break;
				}
				else if (vibors == 3) {
					prosmotrbdcall(fname_call, fname_city, fname_tarif);
					break;
				}
				else {
					break;
				}
			}
			printf("\n Ошибка открытия файла для чтения и записи\n");
			break;

		case 4: 
			if (!proverka_file(fname_call, PR_R)) {
				printf("\n Ошибка открытия файла для чтения\n");
				break;
			}
			if (!proverka_file(fname_r, PR_W)) {
				printf("\n Ошибка открытия файла для записи\n");
				break;
			}
			poiskphonenumber(fname_call, fname_r);
			printf("\n Поиск по номеру телефону закончен.\n");
			break;

		case 5: 
			if (!proverka_file(fname_r, PR_R)) {
				printf("\n Ошибка открытия файла для чтения\n");
				break;
			}
			prosmotrbdpoisnumber(fname_r, fname_city, fname_tarif);
			break;

		case 6: 
			if (!proverka_file(fname_call, PR_S) && !proverka_file(fname_city, PR_S) && !proverka_file(fname_tarif, PR_S)) {
				printf("\n Ошибка открытия файла для чтения и записи\n");
				break;
			}
			sort_tarifprice(fname_call);
			printf("\n Сортировка по стоимости тарифа закончена.\n");
			break;

		case 7: 
			if (proverka_file(fname_call, PR_S) && proverka_file(fname_city, PR_S) && proverka_file(fname_tarif, PR_S)) {
				printf("\n Вы уверены в том,что хотите удалить все данные из базы данных ? [Y/N] ");
				while ((otv = getchar()) == '\n');
				if (otv == 'Y' || otv == 'y') {
					FILE* file = fopen(fname_city, PR_W);
					FILE* file2 = fopen(fname_call, PR_W);
					FILE* file3 = fopen(fname_tarif, PR_W);
					FILE* file4 = fopen(fname_r, PR_W);
					fclose(file);
					fclose(file2);
					fclose(file3);
					fclose(file4);
					printf(" \nДанные успешно удалены!\n ");
					break;
				}
				else  if (otv == 'N' || otv == 'n') {
					break;
				}
			}
			printf("\n Ошибка открытия файла для чтения\n");
			break;

		case 8: return 0;
		}
	}
}

//Добавление новых элементов в таблицу Разговоры в базу данных
void dobavkacall(const char* fname, const char* fname2, const char* fname3) {
	int i = 0;
	FILE* baza, * cityprosmotr, * tarifprosmotr;
	baza = fopen(fname, PR_S);
	cityprosmotr = fopen(fname2, PR_R);
	tarifprosmotr = fopen(fname3, PR_R);
	char otv = 'NULL';
	calls call;
	city cit;
	tarif tarifs;

	int callKeyArr[10] = {};
	int	countElementsCall = -1;
	int id = 0;
	int countcall = 0;

	string cityKeyArr[10] = {};
	int	countElementscity = -1;
	int countcity = 0;
	int idcity = 0;

	string tarifKeyArr[10] = {};
	int	countElementstarif = -1;
	int counttarif = 0;
	int idtarif = 0;
	string tarifnames;

	char nsme[50];
	char nsmeyatif[50];
	string cityname;

	rewind(baza);
	do {
		while (fread(&call, sizeof(call), 1, baza) > 0) {
			countElementsCall++;
			countcall++;
			callKeyArr[countElementsCall] = call.idPhone;
		}
		while (fread(&cit, sizeof(cit), 1, cityprosmotr) > 0) {
			countElementscity++;
			countcity++;
			cityname = cit.cityname;
			cityKeyArr[countElementscity] = cityname;
		}
		while (fread(&tarifs, sizeof(tarifs), 1, tarifprosmotr) > 0) {
			countElementstarif++;
			counttarif++;
			tarifnames = tarifs.tarifname;
			tarifKeyArr[countElementstarif] = tarifnames;
			int idst = 0;
			idst = tarifs.idtarif;
		}
		if (countcall == 0) {
			id = id++;
			call.idPhone = id;
		} else {
			id = ++countcall;
			call.idPhone = id;
		}

		printf("Фамилия:  ");
		scanf("%s", &call.surname);

		printf("Имя:  ");
		scanf("%s", &call.name);

		printf("Отчество:  ");
		scanf("%s", &call.patronymic);

		printf("Номер телефона:  ");
		scanf("%s", &call.phonenumber);

		printf("Название тарифа:  ");
		scanf("%s", nsmeyatif);
		if (counttarif != 0) {
			for (int i = 0; i < counttarif; i++) {
				if (tarifKeyArr[i] == nsmeyatif) {
					idtarif = ++i;
					call.tarifcall = idtarif;
				}
			}
			if (idtarif == 0) {
				printf("\nОшибка! Сперва введите данные Тарифа\n");
				return;
			}
		} else {
			printf("\nОшибка! Сперва введите данные Тарифа\n");
			return;
		}

		printf("Абонентская плата :  ");
		scanf("%i", &call.monthspay);

		printf("Дата разговора  ");
		scanf("%s", &call.date);

		printf("Город ");
		scanf("%s", nsme);

		if (countcity != 0) {
			for (int i = 0; i < countcity; i++) {
				if (cityKeyArr[i] == nsme) {
					idcity = ++i;
					call.idcallcyty = idcity;
				}
			}

			if (idcity == 0) {
				printf("\nОшибка! Сперва введите данные города\n");
				return;
			}
		} else {
			printf("\nОшибка! Сперва введите данные города\n");
			return;
		}

		fwrite(&call, sizeof(call), 1, baza);//запись

		printf("\n Продолжать?[Y/N]");
		while ((otv = getchar()) == '\n');

	} while (otv == 'Y' || otv == 'y' || otv == 'H' || otv == 'н');

	fclose(baza);
	printf("\nДобавление данных в таблицу Разговор закончено.\n");
	return;
}

//Добавление новых элементов в таблицу Тариф в базу данных
void dobavkatarif(const char* fname1) {
	int tarifKeyArr[10] = {};
	string tarifnameArr[10] = {};
	int	countElementstarif = -1;
	int counttarif = 0;
	int idtarif = 0;
	int id = 0;
	FILE* baz;
	baz = fopen(fname1, PR_S);
	char otv1 = 'NULL';
	char name[50];
	tarif tarifs;

	rewind(baz);
	do {
		while (fread(&tarifs, sizeof(tarifs), 1, baz) > 0) {
			countElementstarif++;
			counttarif++;
			tarifKeyArr[countElementstarif] = tarifs.idtarif;
			tarifnameArr[countElementstarif] = tarifs.tarifname;
		}
		if (counttarif == 0) {
			id = id++;
			tarifs.idtarif = id;
		} else {
			id = ++counttarif;
			tarifs.idtarif = id;
		}

		printf("Название тарифа  ");
		scanf("%s", tarifs.tarifname);
		if (counttarif != 0) {
			for (int i = 0; i < counttarif; i++) {
				if (tarifnameArr[i] == tarifs.tarifname) {
					id = ++i;
					printf("\nОшибка даный тариф уже был создан под id:");
					printf("%d", id);
					return;
				}
			}
			if (idtarif == 0) {
				fwrite(&tarifs, sizeof(tarifs), 1, baz);//запись
			}
		} else fwrite(&tarifs, sizeof(tarifs), 1, baz);//запись

		printf("\n Продолжать?[Y/N]");
		while ((otv1 = getchar()) == '\n');
	} while (otv1 == 'Y' || otv1 == 'y' || otv1 == 'H' || otv1 == 'н');
	fclose(baz);

	printf("\nДобавление данных в таблицу Тариф закончено.\n");
	return;
}

//Добавление новых элементов в таблицу Город в базу данных
void dobavkacity(const char* fname1) {
	int cityKeyArr[10] = {};
	string citynameArr[10] = {};
	int	countElementscity = -1;
	int countcity = 0;
	int idcity = 0;
	int id = 0;

	FILE* baz;
	baz = fopen(fname1, PR_S);

	char otv1 = 'NULL';
	char name[50];
	city citys;

	rewind(baz);
	do {
		while (fread(&citys, sizeof(citys), 1, baz) > 0) {
			countElementscity++;
			countcity++;
			cityKeyArr[countElementscity] = citys.idcodecity;
			citynameArr[countElementscity] = citys.cityname;
		}
		if (countcity == 0) {
			id = id++;
			citys.idcodecity = id;
		} else {
			id = ++countcity;
			citys.idcodecity = id;
		}

		printf("Город  ");
		scanf("%s", citys.cityname);
		if (countcity != 0) {
			for (int i = 0; i < countcity; i++) {
				if (citynameArr[i] == citys.cityname) {
					id = ++i;
					printf("\nОшибка даный город уже был создан под id:");
					printf("%d", id);
					return;
				}
			}
			if (idcity == 0) {

				printf("Код города  ");
				scanf("%i", &citys.codeccity);
				fwrite(&citys, sizeof(citys), 1, baz);//запись
			}
		} else {
			printf("код города  ");
			scanf("%i", &citys.codeccity);
			fwrite(&citys, sizeof(citys), 1, baz);//запись
		}

		printf("\n Продолжать?[Y/N]");
		while ((otv1 = getchar()) == '\n');
	} while (otv1 == 'Y' || otv1 == 'y' || otv1 == 'H' || otv1 == 'н');
	fclose(baz);

	printf("\nДобавление данных в таблицу Город закончено.\n");
	return;
}

//Вывод заголовка при просмотре данных таблицы Разговор 
void zagcalls() {
	int i;

	printf("\n");
	for (i = 1; i <= 125; i++)
		printf("-");
	printf("\n");
	printf("|%10s|%10s|%10s|%18s|%10s|%15s|%15s|%10s|%15s|\n", "Id звонка", "Фамилия ", "Имя ",
		"Отчество", "Город ", "Номер телефона ", "Название тарифа ",
		"Абон.плата ", "Дата.разгов ");
	for (i = 1; i <= 125; i++)
		printf("-");
	return;
}

//Вывод заголовка при просмотре данных по поиску телефона 
void zagpoisknumber() {
	int i;

	printf("\n");
	for (i = 1; i <= 125; i++)
		printf("-");
	printf("\n");
	printf("|%10s|%10s|%10s|%18s|%10s|%15s|%15s|%10s|%15s|\n", "Id звонка", "Фамилия ", "Имя ",
		"Отчество", "Город ", "Номер телефона ", "Название тарифа ",
		"Абон.плата ", "Дата.разгов ");
	for (i = 1; i <= 125; i++)
		printf("-");
	return;
}

//Вывод заголовка при просмотре данных в таблице Город
void zagcity() {
	int i;

	printf("\n");
	for (i = 1; i <= 49; i++)
		printf("-");
	printf("\n");
	printf("|%15s|%15s|%15s|\n", "Id города", "Город ",
		"Код города ");
	for (i = 1; i <= 49; i++)
		printf("-");
	return;
}

//Вывод заголовка при просмотре данных в таблице Тариф
void zagtarif() {
	int i;

	printf("\n");
	for (i = 1; i <= 33; i++)
		printf("-");
	printf("\n");
	printf("|%15s|%15s|\n", "Id тарифа", "Тариф ");
	for (i = 1; i <= 33; i++)
		printf("-");
	return;
}

//Просмотр данных в таблице Разговор
void prosmotrbdcall(const char* fname, const char* fname2, const char* fname3) {
	int callKeyArr[10] = {};
	int	countElementsCall = -1;
	int id = 0;
	int countcall = 0;
	int x = 0;
	int tarifcall[15] = {};

	string tarifnameArr[10] = {};
	int	countElementstarif = -1;
	int counttarif = 0;
	int idtarif = 0;
	int tarifid[15] = {};
	string tarifname;

	string citynameArr[10] = {};
	int	countElementscity = -1;
	int countcity = 0;
	int cityid[10] = {};
	int idcity = 0;
	string cityname;

	char name[50];
	FILE* baz, * namecitys, * nametarif;
	baz = fopen(fname, PR_R);
	namecitys = fopen(fname2, PR_R);
	nametarif = fopen(fname3, PR_R);
	city cit;
	calls call;
	tarif tarifs;
	zagcalls();

	while (fread(&tarifs, sizeof(tarifs), 1, nametarif) > 0) {
		countElementstarif++;
		counttarif++;
		tarifname = tarifs.tarifname;
		tarifnameArr[countElementstarif] = tarifs.tarifname;
		tarifid[countElementstarif] = tarifs.idtarif;
	}

	while (fread(&cit, sizeof(cit), 1, namecitys) > 0) {
		countElementscity++;
		countcity++;
		cityname = cit.cityname;
		citynameArr[countElementscity] = cit.cityname;
		cityid[countElementscity] = cit.idcodecity;
	}

	while (fread(&call, sizeof(call), 1, baz) > 0) {
		countElementsCall++;
		countcall++;

		int idcity = call.idcallcyty;
		int idtarif = call.tarifcall;
		for (int i = 0; i < countcity; ++i) {
			if (cityid[i] == idcity) {
				for (int j = 0; j < counttarif; ++j) {
					if (tarifid[j] == idtarif) {
						string nametarif = tarifnameArr[j];
						string names = citynameArr[i];
						printf("\n|%10i|%10s|%10s|%18s|%10s|%15s|%16s|%11i|%15s|",
							call.idPhone, call.surname,
							call.name, call.patronymic,
							names.c_str(), call.phonenumber,
							nametarif.c_str(), call.monthspay,
							call.date);
					}
				}

			}
		}

	}

	printf("\n");
	for (x = 1; x <= 125; x++)
		printf("-");

	return;
}

//Просмотр данных по поиску телефону
void prosmotrbdpoisnumber(const char* fname, const char* fname2, const char* fname3) {

	int callKeyArr[10] = {};
	int	countElementsCall = -1;
	int id = 0;
	int countcall = 0;
	int x = 0;
	int tarifcall[15] = {};

	string tarifnameArr[10] = {};
	int	countElementstarif = -1;
	int counttarif = 0;
	int idtarif = 0;
	int tarifid[15] = {};
	string tarifname;

	string citynameArr[10] = {};
	int	countElementscity = -1;
	int countcity = 0;
	int cityid[10] = {};
	int idcity = 0;
	string cityname;

	char name[50];
	int i = 0;
	FILE* baz, * namecitys, * nametarif;
	baz = fopen(fname, PR_R);
	namecitys = fopen(fname2, PR_R);
	nametarif = fopen(fname3, PR_R);
	city cit;
	calls call;
	tarif tarifs;

	printf("\n  База данных поиска Телефонные сети по номеру телефону\n");
	zagpoisknumber();

	while (fread(&tarifs, sizeof(tarifs), 1, nametarif) > 0) {
		countElementstarif++;
		counttarif++;
		tarifname = tarifs.tarifname;
		tarifnameArr[countElementstarif] = tarifs.tarifname;
		tarifid[countElementstarif] = tarifs.idtarif;
	}
	while (fread(&cit, sizeof(cit), 1, namecitys) > 0) {
		countElementscity++;
		countcity++;
		cityname = cit.cityname;
		citynameArr[countElementscity] = cit.cityname;
		cityid[countElementscity] = cit.idcodecity;
	}

	while (fread(&call, sizeof(call), 1, baz) > 0) {
		countElementsCall++;
		countcall++;

		int idcity = call.idcallcyty;
		int idtarif = call.tarifcall;
		for (int i = 0; i < countcity; ++i) {
			if (cityid[i] == idcity) {
				for (int j = 0; j < counttarif; ++j) {
					if (tarifid[j] == idtarif) {
						string nametarif = tarifnameArr[j];
						string names = citynameArr[i];
						printf("\n|%10i|%10s|%10s|%18s|%10s|%15s|%16s|%11i|%15s|",
							call.idPhone, call.surname,
							call.name, call.patronymic,
							names.c_str(), call.phonenumber,
							nametarif.c_str(), call.monthspay,
							call.date);
					}
				}

			}
		}

	}

	printf("\n");
	for (x = 1; x <= 125; x++)
		printf("-");
	return;
}

//Просмотр данных из таблицы Город
void prosmotrbdcity(const char* fname) {
	int i = 0;
	FILE* baz;
	baz = fopen(fname, PR_R);
	city   citys;

	zagcity();
	while (fread(&citys, sizeof(citys), 1, baz) > 0) {
		printf("\n|%15i|%16s|%14i|", citys.idcodecity, citys.cityname, citys.codeccity);
	}
	printf("\n");
	for (i = 1; i <= 49; i++)
		printf("-");
	fclose(baz);
	return;
}

//Просмотр данных из таблицы Тариф
void prosmotrbdtarif(const char* fname) {
	int i = 0;
	FILE* baz;
	baz = fopen(fname, PR_R);
	tarif   tarifs;

	zagtarif();
	while (fread(&tarifs, sizeof(tarifs), 1, baz) > 0) {
		printf("\n|%15i|%15s|", tarifs.idtarif, tarifs.tarifname);
	}
	printf("\n");
	for (i = 1; i <= 33; i++)
		printf("-");
	fclose(baz);
	return;
}

//Поиск телефонных разговоров по номеру телефону
void poiskphonenumber(const char* fname1, const char* fname2) {
	char phonenumber[15];
	calls call;
	FILE* in,					//исходный файл
		* out;				//файл результатов поиска
	in = fopen(fname1, PR_R);		//открываем файл на чтение
	out = fopen(fname2, PR_W);		//открываем файл на запись
	printf("\n Номер телефона для поиска? ");
	scanf("%s", &phonenumber);
	while (fread(&call, sizeof(call), 1, in) > 0)
		if (strncmp(call.phonenumber, phonenumber, 15) == 0)
			fwrite(&call, sizeof(call), 1, out);
	fclose(out);
	fclose(in);
	return;

}

//Сортировка данных из таблицы Разговоры по стоимости тарифа
void sort_tarifprice(const char* fname) {
	int i;
	int fl;
	calls ppp, call;
	FILE* baza;
	baza = fopen(fname, PR_S);	//открываем файл на чтение и запись
	do {
		rewind(baza);
		fl = 0;
		for (i = 0; fread(&call, sizeof(call), 1, baza) > 0; i += sizeof(call), fseek(baza, i, SEEK_SET)) {
			if (fread(&ppp, sizeof(call), 1, baza) > 0) {
				if (call.monthspay > ppp.monthspay) {
					fseek(baza, i, SEEK_SET);	//позиция i от НАЧАЛА файла
					fwrite(&ppp, sizeof(call), 1, baza);
					fwrite(&call, sizeof(call), 1, baza);
					fl = 1;
				}
			}
		}
	} while (fl);
	fclose(baza);
	return;
}

//проверка наличия физического файла
int proverka_file(const char* fname, const char* pr) {//Открываем файл
	if (!(fopen(fname, pr)))		//файл не существует
		return(0);
	return(1);
}