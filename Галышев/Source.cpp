/*�������� �����.
  ����/����� � �������������� ������� ��������� ����� C
  ��������� ������ � ����� ������ "���������� ����;"
  �������� ����
  ���������� ����� �������
  �������� ����
  ����� ���������� ���������� �� ������ �������� � ��������� ����� �������
  ���������� ���������� ���������� �� ��������� ������
  �������� ���� ������.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#define FNAME_city "./city2.dat"	//��� ����� � �������� �����
#define FNAME_call "./call2.dat"	//��� ����� � �������� �����
#define FNAME_tarif "./tarif2.dat"	//��� ����� � �������� �����
#define FNAME_R "./poisknumber.dat" 	//��� ����� � ������������ ������
int proverka_file(const char*, const char*);	//�������� ������� �����
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

const char PR_R[] = "rb";	//������� �������� ��������� ����� �� ������
const char PR_S[] = "r+b";	//������� �������� ����� �� ������ � ������
const char PR_W[] = "wb";	//������� �������� ����� �� ������
const char PR_A[] = "ab";	//������� �������� ����� �� ����������
typedef struct calls {

	int idPhone;            //����
	char surname[20];      //������� 
	char name[15];         //���
	char patronymic[20];   //��������
	int idcallcyty;         //���� ������
	char phonenumber[8];	//����� ��������
	char date[11];	        //���� ���������
	int tarifcall;          //���� ������
	int monthspay;         //����������� ����� 

}tripcalls;
typedef struct city {

	int idcodecity;         //
	char cityname[50];      //�������� ������
	int codeccity;      //��� ������ 

}tripcity;
typedef struct tarif {

	int idtarif;
	char tarifname[50];      //�������� ������

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
	{//����� ���� ��������
		printf("\n    ��� ��������:\n");
		printf("  1 - �������� ���� ������\n");
		printf("  2 - ���������� ����� ������� � ���� ������ \n");
		printf("  3 - �������� ������ � ���� ������ \n");;
		printf("  4 - ����� ������ �� ������ ��������\n");
		printf("  5 - �������� ���������� �� ������ ��������\n");
		printf("  6 - ���������� ���������� ���������� �� ��������� ������ \n");
		printf("  7 - ������� ������ �� ���� ������. \n");
		printf("  8 - ����� �� ���������\n");
		printf("  ������� ��� �������� ->");
		scanf("%i", &var);
		switch (var)
		{
		default:break;
		case 1: 
			if (proverka_file(fname_call, PR_R) && proverka_file(fname_city, PR_R) && proverka_file(fname_tarif, PR_R)) {
				printf(" ������ ���� � ����� ������? [Y/N] ");
				while ((otv = getchar()) == '\n');
				if (otv == 'Y' || otv == 'y') {
				printf(" ������� ��� ������������ �����: ");
				scanf("%s", fname_call);
				} else {
				printf(" ������� ���  ����: ");
				scanf("%s", fname_call);
				break;
				}
			}
			if (proverka_file(fname_call, PR_W) && proverka_file(fname_city, PR_W) && proverka_file(fname_tarif, PR_W)) {
				printf(" ������� ���� ", fname_call);
				getchar();
				printf("\n �������� ���� ���������.\n");
				FILE* file = fopen(fname_city, PR_W);
				FILE* file2 = fopen(fname_tarif, PR_W);
				fclose(file);
				fclose(file2);
			} else {
				printf("\n ������ �������� ����� ��� ������\n");
				break;
			}

			if ((proverka_file(fname_call, PR_R) && proverka_file(fname_city, PR_R) && proverka_file(fname_tarif, PR_R))) {
				printf(" ���� ������ ������ � ������\n");
			} else printf("\n ���� �� �������\n");

			break;

		case 2: 
			if (proverka_file(fname_call, PR_R) && proverka_file(fname_city, PR_R) && proverka_file(fname_tarif, PR_R)) {
				int vibors = 0;
				printf("\n    �������� �������:\n");
				printf("  1 - �����\n");
				printf("  2 - �����\n");
				printf("  3 - ���������\n");
				printf("  4 - ��������� �����\n");
				printf("  ������� ��� �������� ->");
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
				printf("\n ������ �������� ����� ��� ������\n");
				break;
			}

		case 3: 
			if (proverka_file(fname_call, PR_S) && proverka_file(fname_city, PR_S) && proverka_file(fname_tarif, PR_S)) {
				int vibors = 0;
				printf("\n    �������� �������:\n");
				printf("  1 - �����\n");
				printf("  2 - �����\n");
				printf("  3 - ���������\n");
				printf("  4 - ��������� �����\n");
				printf("  ������� ��� �������� ->");
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
			printf("\n ������ �������� ����� ��� ������ � ������\n");
			break;

		case 4: 
			if (!proverka_file(fname_call, PR_R)) {
				printf("\n ������ �������� ����� ��� ������\n");
				break;
			}
			if (!proverka_file(fname_r, PR_W)) {
				printf("\n ������ �������� ����� ��� ������\n");
				break;
			}
			poiskphonenumber(fname_call, fname_r);
			printf("\n ����� �� ������ �������� ��������.\n");
			break;

		case 5: 
			if (!proverka_file(fname_r, PR_R)) {
				printf("\n ������ �������� ����� ��� ������\n");
				break;
			}
			prosmotrbdpoisnumber(fname_r, fname_city, fname_tarif);
			break;

		case 6: 
			if (!proverka_file(fname_call, PR_S) && !proverka_file(fname_city, PR_S) && !proverka_file(fname_tarif, PR_S)) {
				printf("\n ������ �������� ����� ��� ������ � ������\n");
				break;
			}
			sort_tarifprice(fname_call);
			printf("\n ���������� �� ��������� ������ ���������.\n");
			break;

		case 7: 
			if (proverka_file(fname_call, PR_S) && proverka_file(fname_city, PR_S) && proverka_file(fname_tarif, PR_S)) {
				printf("\n �� ������� � ���,��� ������ ������� ��� ������ �� ���� ������ ? [Y/N] ");
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
					printf(" \n������ ������� �������!\n ");
					break;
				}
				else  if (otv == 'N' || otv == 'n') {
					break;
				}
			}
			printf("\n ������ �������� ����� ��� ������\n");
			break;

		case 8: return 0;
		}
	}
}

//���������� ����� ��������� � ������� ��������� � ���� ������
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

		printf("�������:  ");
		scanf("%s", &call.surname);

		printf("���:  ");
		scanf("%s", &call.name);

		printf("��������:  ");
		scanf("%s", &call.patronymic);

		printf("����� ��������:  ");
		scanf("%s", &call.phonenumber);

		printf("�������� ������:  ");
		scanf("%s", nsmeyatif);
		if (counttarif != 0) {
			for (int i = 0; i < counttarif; i++) {
				if (tarifKeyArr[i] == nsmeyatif) {
					idtarif = ++i;
					call.tarifcall = idtarif;
				}
			}
			if (idtarif == 0) {
				printf("\n������! ������ ������� ������ ������\n");
				return;
			}
		} else {
			printf("\n������! ������ ������� ������ ������\n");
			return;
		}

		printf("����������� ����� :  ");
		scanf("%i", &call.monthspay);

		printf("���� ���������  ");
		scanf("%s", &call.date);

		printf("����� ");
		scanf("%s", nsme);

		if (countcity != 0) {
			for (int i = 0; i < countcity; i++) {
				if (cityKeyArr[i] == nsme) {
					idcity = ++i;
					call.idcallcyty = idcity;
				}
			}

			if (idcity == 0) {
				printf("\n������! ������ ������� ������ ������\n");
				return;
			}
		} else {
			printf("\n������! ������ ������� ������ ������\n");
			return;
		}

		fwrite(&call, sizeof(call), 1, baza);//������

		printf("\n ����������?[Y/N]");
		while ((otv = getchar()) == '\n');

	} while (otv == 'Y' || otv == 'y' || otv == 'H' || otv == '�');

	fclose(baza);
	printf("\n���������� ������ � ������� �������� ���������.\n");
	return;
}

//���������� ����� ��������� � ������� ����� � ���� ������
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

		printf("�������� ������  ");
		scanf("%s", tarifs.tarifname);
		if (counttarif != 0) {
			for (int i = 0; i < counttarif; i++) {
				if (tarifnameArr[i] == tarifs.tarifname) {
					id = ++i;
					printf("\n������ ����� ����� ��� ��� ������ ��� id:");
					printf("%d", id);
					return;
				}
			}
			if (idtarif == 0) {
				fwrite(&tarifs, sizeof(tarifs), 1, baz);//������
			}
		} else fwrite(&tarifs, sizeof(tarifs), 1, baz);//������

		printf("\n ����������?[Y/N]");
		while ((otv1 = getchar()) == '\n');
	} while (otv1 == 'Y' || otv1 == 'y' || otv1 == 'H' || otv1 == '�');
	fclose(baz);

	printf("\n���������� ������ � ������� ����� ���������.\n");
	return;
}

//���������� ����� ��������� � ������� ����� � ���� ������
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

		printf("�����  ");
		scanf("%s", citys.cityname);
		if (countcity != 0) {
			for (int i = 0; i < countcity; i++) {
				if (citynameArr[i] == citys.cityname) {
					id = ++i;
					printf("\n������ ����� ����� ��� ��� ������ ��� id:");
					printf("%d", id);
					return;
				}
			}
			if (idcity == 0) {

				printf("��� ������  ");
				scanf("%i", &citys.codeccity);
				fwrite(&citys, sizeof(citys), 1, baz);//������
			}
		} else {
			printf("��� ������  ");
			scanf("%i", &citys.codeccity);
			fwrite(&citys, sizeof(citys), 1, baz);//������
		}

		printf("\n ����������?[Y/N]");
		while ((otv1 = getchar()) == '\n');
	} while (otv1 == 'Y' || otv1 == 'y' || otv1 == 'H' || otv1 == '�');
	fclose(baz);

	printf("\n���������� ������ � ������� ����� ���������.\n");
	return;
}

//����� ��������� ��� ��������� ������ ������� �������� 
void zagcalls() {
	int i;

	printf("\n");
	for (i = 1; i <= 125; i++)
		printf("-");
	printf("\n");
	printf("|%10s|%10s|%10s|%18s|%10s|%15s|%15s|%10s|%15s|\n", "Id ������", "������� ", "��� ",
		"��������", "����� ", "����� �������� ", "�������� ������ ",
		"����.����� ", "����.������ ");
	for (i = 1; i <= 125; i++)
		printf("-");
	return;
}

//����� ��������� ��� ��������� ������ �� ������ �������� 
void zagpoisknumber() {
	int i;

	printf("\n");
	for (i = 1; i <= 125; i++)
		printf("-");
	printf("\n");
	printf("|%10s|%10s|%10s|%18s|%10s|%15s|%15s|%10s|%15s|\n", "Id ������", "������� ", "��� ",
		"��������", "����� ", "����� �������� ", "�������� ������ ",
		"����.����� ", "����.������ ");
	for (i = 1; i <= 125; i++)
		printf("-");
	return;
}

//����� ��������� ��� ��������� ������ � ������� �����
void zagcity() {
	int i;

	printf("\n");
	for (i = 1; i <= 49; i++)
		printf("-");
	printf("\n");
	printf("|%15s|%15s|%15s|\n", "Id ������", "����� ",
		"��� ������ ");
	for (i = 1; i <= 49; i++)
		printf("-");
	return;
}

//����� ��������� ��� ��������� ������ � ������� �����
void zagtarif() {
	int i;

	printf("\n");
	for (i = 1; i <= 33; i++)
		printf("-");
	printf("\n");
	printf("|%15s|%15s|\n", "Id ������", "����� ");
	for (i = 1; i <= 33; i++)
		printf("-");
	return;
}

//�������� ������ � ������� ��������
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

//�������� ������ �� ������ ��������
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

	printf("\n  ���� ������ ������ ���������� ���� �� ������ ��������\n");
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

//�������� ������ �� ������� �����
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

//�������� ������ �� ������� �����
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

//����� ���������� ���������� �� ������ ��������
void poiskphonenumber(const char* fname1, const char* fname2) {
	char phonenumber[15];
	calls call;
	FILE* in,					//�������� ����
		* out;				//���� ����������� ������
	in = fopen(fname1, PR_R);		//��������� ���� �� ������
	out = fopen(fname2, PR_W);		//��������� ���� �� ������
	printf("\n ����� �������� ��� ������? ");
	scanf("%s", &phonenumber);
	while (fread(&call, sizeof(call), 1, in) > 0)
		if (strncmp(call.phonenumber, phonenumber, 15) == 0)
			fwrite(&call, sizeof(call), 1, out);
	fclose(out);
	fclose(in);
	return;

}

//���������� ������ �� ������� ��������� �� ��������� ������
void sort_tarifprice(const char* fname) {
	int i;
	int fl;
	calls ppp, call;
	FILE* baza;
	baza = fopen(fname, PR_S);	//��������� ���� �� ������ � ������
	do {
		rewind(baza);
		fl = 0;
		for (i = 0; fread(&call, sizeof(call), 1, baza) > 0; i += sizeof(call), fseek(baza, i, SEEK_SET)) {
			if (fread(&ppp, sizeof(call), 1, baza) > 0) {
				if (call.monthspay > ppp.monthspay) {
					fseek(baza, i, SEEK_SET);	//������� i �� ������ �����
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

//�������� ������� ����������� �����
int proverka_file(const char* fname, const char* pr) {//��������� ����
	if (!(fopen(fname, pr)))		//���� �� ����������
		return(0);
	return(1);
}