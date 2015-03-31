#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0
#define TRUE 1
#define FALSE 0
#define FATAL_ERROR 2
#define DATE_SIZE 12
#define TAXE_SIZE 9
#define MONTH_SIZE 4
#define MAX_TAXE 1000000
#define AMOUNT_DEBT 5
#define AMOUNT_FIRMS 10
#define SHABLON_NAME_SIZE 15

typedef struct
{
	char* name;
	char taxe[TAXE_SIZE];
	char need_pay_date[DATE_SIZE];
	char real_pay_date[DATE_SIZE];
}firm;

typedef struct
{
	char name[SHABLON_NAME_SIZE];
	char taxe[TAXE_SIZE];
	char need_pay_date[DATE_SIZE];
	char real_pay_date[DATE_SIZE];
}shablon;

void init_firms(firm* firms, int firms_amount);

int get_name(char* str, int name_length);
int get_taxe(char* str);
int get_date(char *str);
int get_month(char* str);
int enter(int* q, int bottom_val, int top_val);

void add_firm_name(firm* firms, char* name);
void add_firm_taxe(firm* rec, char* taxe);
void add_firm_dates(firm* rec, char* real_date_pay, char* need_date_pay);
void enter_firm(firm* firm, int name_length, int firms_amount);
void show_firm(firm* rec);
void show_head(void)
{
	printf("\n Name |\tDeadline     |\tTaxe  |\tDate_pay  |\n");
	printf("\n-------------------------------------------\n");
}

int month_compare(char* month, char* need_pay_date);
void five_debt(firm* firms, char* month_of_deadline, int firms_amount);
void copy_firm(firm* dest, firm* src);
void swap_firms(firm* rec1, firm* rec2);
void swap_str_dynamic(char** str1, char** str2);
void swap_str_static(char* str1, char* str2);

int enter_menu();
void set_shablons(firm* shablons, int shablons_amount);

int main(void)
{
	char month[MONTH_SIZE];

	const int LOWEST_AMOUNT = 1;
	const int RECORD_MAX_AMOUNT = 15;
	const int FIRMS_NAME_SIZE = 30;
	/*	
		SIZE is about bytes,their amount should be (LENGTH + 2), according to functions 
		int get_name(char* str, int name_length);
		int get_taxe(char* str);
		int get_date(char *str);
	*/
	int firm_name_size;
	int firms_amount;
	int i, temp_i = 0, j;
	int choice;
	int shablon_on = 0;
	int firms_amount_temp;

	firm* firms;
	firm* firm_temp;
	
	
	firm* shablons;

	shablons = (firm*)malloc(sizeof(firm)*AMOUNT_FIRMS);
	if(!shablons)
	{
		printf("\nMemory error with shablons\n\n");
		return 1;
	}
	temp_i = 0;
	for(i = 0;i<AMOUNT_FIRMS;++i)
	{
		shablons[i].name = (char*)malloc(sizeof(char)*SHABLON_NAME_SIZE);
		if(!shablons[i].name)
		{
			printf("\nMemmory error with shablons[%d].name\n\n", i);
			for(j = 0;j<temp_i;++j)
			{
				free(shablons[j].name);
			}
			free(shablons);
			return 1;
		}
		++temp_i;
	}
	set_shablons(shablons, AMOUNT_FIRMS);

	printf("Enter amount of firms: ");
	if(enter(&firms_amount, LOWEST_AMOUNT, RECORD_MAX_AMOUNT) == FAIL)
	{
		return 0;
	}

	printf("\n\nEnter the max length of the firm's name: ");
	if(enter(&firm_name_size, LOWEST_AMOUNT, FIRMS_NAME_SIZE)==FAIL)
	{
		return 0;
	}
	else
	{
		firm_name_size+=2;
	}

	firms = (firm*)malloc(sizeof(firm)*firms_amount);
	if(!firms)
	{
		printf("\nMemory error with firms\n\n");
		return 1;
	}
	
	temp_i = 0;
	for(i = 0;i<firms_amount;++i)
	{
		firms[i].name = (char*)malloc(sizeof(char)*firm_name_size);
		if(!firms[i].name)
		{
			printf("\nMemory error with firms[%d].name\n\n", i + 1);
			for(j = 0;j<temp_i;++j)
			{
				free(firms[j].name);
			}
			free(firms);
			return 1;
		}
		++temp_i;
	}

	firms_amount_temp = firms_amount;
	firm_temp = firms;
	init_firms(firms,firms_amount);

	for (;;)
	{
		printf("\n-------------------------------------------\n");
		if(shablon_on == 0)
		{
			printf("\nUSER database is active\n");
		}
		else
		{
			printf("\nSHABLONED database is active\n");
		}
		choice = enter_menu();
		switch (choice)
		{
		case 1:
			enter_firm(firms, firm_name_size, firms_amount);
			break;
		case 2:
			if(firms[0].name[0]=='\0')
			{
				printf("\n-------------------------------------------\n");
				printf("\nDatabase is empty\n");
				break;
			}
			do
			{
				printf("Enter month: ");
			} while (get_month(month) != SUCCESS);
			five_debt(firms, month, firms_amount);
			break;
		case 3:
			i = 0;
			while(firms[i].name[0]!='\0')
				{
					if(i == 0)
					{
						show_head();
					}
					show_firm(&firms[i++]);
					if(i>=firms_amount)
					{
						break;
					}
				}
			if(i == 0)
			{
				printf("\n-------------------------------------------\n");
				printf("\nDatabase is empty\n");
			}
			break;
		case 4:
				//firm_temp - another adress of firms, was initialize after all initializings in the begining
				//first_amount_temp - rezerve copy of firms_amount
				if(shablon_on==0)
				{
					firms = shablons;
					firms_amount = AMOUNT_FIRMS;
					shablon_on = 1;
				}
				else
				{
					firms = firm_temp;
					firms_amount = firms_amount_temp;
					shablon_on = 0;
				}
				printf("\nSwitching databases... Ready\n");
				break;
			
		case 5:
			if(shablon_on = 1)
			{
				firms = firm_temp;
				firms_amount = firms_amount_temp;
				shablon_on = 0;
			}
			for (i = 0; i < firms_amount; ++i)
			{
				free(firms[i].name);
			}
			free(firms);
			for (i = 0; i < AMOUNT_FIRMS; ++i)
			{
				free(shablons[i].name);
			}
			free(shablons);
			return 0;
			break;
		}
	}

	printf("\n\n");
	return 0;
}

void set_shablons(firm* shablons, int shablon_amount)
{
	char shablons_str[AMOUNT_FIRMS][4][15] = 
	{
		//1000,1004,1010,1034,1040,1041,1055,1060,1060
		{ "Town", "1010", "08.07.2014", "08.04.2014" },
		{ "Aow", "1010", "08.03.2014", "08.04.2014" },
		{ "Aawn", "1004", "08.03.2014", "08.04.2014" },
		{ "Town", "1034", "08.04.2014", "08.04.2014" },
		{ "Town", "1040", "08.07.2014", "08.04.2014" },
		{ "Bown", "1080", "08.03.2014", "08.04.2014" },
		{ "Aown", "1070", "08.03.2014", "08.04.2014" },
		{ "Hown", "1055", "08.07.2014", "08.04.2014" },
		{ "Town", "1041", "08.07.2014", "08.04.2014" },
		{ "Lown", "1042", "08.03.2014", "smth" }
	};
	int i,j,k;
	for(i = 0;i<shablon_amount;++i)
	{
		for(j = 0;j<4;++j)
		{
			switch(j)
			{
				case 0:
					for(k = 0;k<4;++k)
					{
						shablons[i].name[k] = shablons_str[i][j][k];
					}
					shablons[i].name[k] = '\0';
					break;
				case 1:
					for(k = 0;k<4;++k)
					{
						shablons[i].taxe[k] = shablons_str[i][j][k];	
					}
					shablons[i].taxe[k] = '\0';
				break;
				case 2:
					for(k = 0;k<10;++k)
					{
						shablons[i].need_pay_date[k] = shablons_str[i][j][k];
					}
					shablons[i].need_pay_date[k] ='\0';
				break;
				case 3:
						for(k = 0;k<10;++k)
					{
						shablons[i].real_pay_date[k] = shablons_str[i][j][k];
					}
						shablons[i].real_pay_date[k] = '\0';
				break;
			}
		}
	}
}

int enter(int* q,int bottom_val,int top_val)
{
	const int TIMES_MAX_AMOUNT = 3;
	int times_amount = 0;
	char ch_temp;

	if(bottom_val>top_val)
	{
		printf("\n\nError in function enter, sorry!\n");
		return FAIL;
	}

	for(;;)
	{
		if(scanf("%d", q)!=1)
		{
			if(times_amount<TIMES_MAX_AMOUNT)
			{
				printf("\nEnter_error, try one more time\n");
				while(getchar()!='\n');
				++times_amount;
				continue;
			}
			else
			{
				printf("\n\nToo many bad values. Good bye!!!\n");
				return FAIL;
			}
		}

		if(*q<bottom_val || *q>top_val)
		{
			if(times_amount<TIMES_MAX_AMOUNT)
			{
				printf("\nBad value, try one more time\n");
				while(getchar()!='\n');
				++times_amount;
				continue;
			}
			else
			{
				printf("\n\nToo many bad values. Good bye!!!\n");
				return FAIL;
			}
		}

		//лишние пробелы не считаются
		ch_temp = ' ';
		while(ch_temp ==' ')
		{
			ch_temp = getchar();
		
			if(ch_temp==' ')
				continue;
			else
				break;
		}

		if(ch_temp!='\n')
		{
			if(times_amount<TIMES_MAX_AMOUNT)
			{
				while(getchar()!='\n');
				printf("\nEnter_error, try one more time\n");
				++times_amount;
				continue;
			}
			else
			{
				printf("\n\nToo many bad values. Good bye!!!\n");
				return FAIL;
			}		
		}

		return SUCCESS;
	}
}

void init_firms(firm* firms, int firms_amount)
{
	int i;
	for(i = 0;i<firms_amount;++i)
	{
		firms[i].name[0] = '\0';
	}
}

int get_name(char* str, int name_length)
{
	int count = 0;
	while (count<name_length - 1)
	{
		if (count!=0 && str[count - 1] == '\n')
			break;
		str[count++] = getchar();
	}

	if (str[count - 1] != '\n')
	{
		printf("Too long name\n\n");
		while (getchar() != '\n');
		return FAIL;
	}
	else
	{
		str[count - 1] = '\0';
		if (count == 1)
		{
			printf("Enter smth:\n\n");
			return FAIL;
		}
		return SUCCESS;
	}
}

int get_taxe(char *str)
{
	int count = 0;
	while (count<TAXE_SIZE - 1)
	{
		if ((str[count - 1]<'0' || str[count - 1]>'9') && (str[count - 1] != '\n') && (count - 1 >= 0))
		{
			printf("Bad value\n\n");
			while (getchar() != '\n');
			return FAIL;
		}

		if (count!= 0 && str[count - 1] == '\n')
			break;

		str[count++] = getchar();
	}


	if (str[count - 1] != '\n')
	{
		printf("Too large taxe\n\n");
		while (getchar() != '\n');
		return FAIL;
	}
	else
	{
		str[count - 1] = '\0';
		if (atoi(str) > MAX_TAXE)
		{
			printf("Too large taxe\n\n");
			return FAIL;
		}
		if (count == 1)
		{
			printf("Enter smth:\n\n");
			return FAIL;
		}
		return SUCCESS;
	}
}

int get_date(char*str)
{
	int count = 0;
	int amount_dodes = 2, day_length = 2, month_length = 2, year_length = 4;
	int active_length = day_length;

	while (count<DATE_SIZE - 1)
	{
		if ((str[count - 1]<'0' || str[count - 1]>'9') && (str[count - 1] != '\n') && (count - 1 >= 0) && (str[count - 1] != '.'))
		{
			printf("Wrong date\n\n");
			while (getchar() != '\n');
			return FAIL;
		}

		if (count!=0 && str[count - 1] == '\n')
			break;

		str[count++] = getchar();
		--active_length;

		if (str[count - 1] == '.')
		{
			--amount_dodes;
			if (active_length != -1)
			{
				printf("Wrong date\n\n");
				while (getchar() != '\n');
				return FAIL;
			}
			else if (amount_dodes == 1)
			{
				active_length = day_length;
			}
			else if (amount_dodes == 0)
			{
				active_length = year_length;
			}
		}
	}

	//0 - значит налог не уплачен, либо неограничен по времени(deadline = 0)
	if (str[0] == '0' && str[1] == '\n')
	{
		str[count - 1] = '\0';
		return SUCCESS;
	}

	if (amount_dodes != 0 || active_length != -1)
	{
		printf("Wrong date\n\n");
		return FAIL;
	}

	if (str[count - 1] != '\n')
	{
		printf("Wrong date\n\n");
		while (getchar() != '\n');
		return FAIL;
	}
	else
	{
		str[count - 1] = '\0';

		if (str[0]<'0' || str[0]>'3')
		{
			printf("Wrong day\n\n");
			return FAIL;
		}
		if ((str[1] > '1' || str[1] < '0') && (str[0] == '3'))
		{
			printf("Wrong day\n\n");
			return FAIL;
		}

		if (str[3]<'0' || str[3]>'1')
		{
			printf("Wrong month\n\n");
			return FAIL;
		}
		if ((str[4] > '2' || str[4] < '0') && (str[3] == '1'))
		{
			printf("Wrong month\n\n");
			return FAIL;
		}

		if (count == 1)
		{
			printf("Enter smth:\n\n");
			return FAIL;
		}
		return SUCCESS;
	}
}

int get_month(char* str)
{
	int count = 0;
	while (count<MONTH_SIZE - 1)
	{
		if ((str[count - 1]<'0' || str[count - 1]>'9') && (str[count - 1] != '\n') && (count - 1 >= 0))
		{
			printf("Wrong month\n\n");
			while (getchar() != '\n');
			return FAIL;
		}

		if (count!= 0 && str[count - 1] == '\n')
			break;
		str[count++] = getchar();
	}



	if (str[count - 1] != '\n')
	{
		printf("Wrong month\n\n");
		while (getchar() != '\n');
		return FAIL;
	}
	else
	{
		str[count - 1] = '\0';
		if (str[0]<'0' || str[0]>'1')
		{
			printf("Wrong month\\n\n");
			return FAIL;
		}
		if ((str[1] > '2' || str[1] < '0') && (str[0] == '1') || (count == 2))
		{
			printf("Wrong month\\n\n");
			return FAIL;
		}
		if (count == 1)
		{
			printf("Enter smth:\n\n");
			return FAIL;
		}
		return SUCCESS;
	}
}

void add_firm_name(firm* firm, char* name)
{
	//записываем имя
	strcpy(firm->name, name);
}

void add_firm_taxe(firm* rec, char* taxe)
{
	strcpy(rec->taxe, taxe);
}

void add_firm_dates(firm* rec, char* need_pay_date, char* datepay)
{
	strcpy(rec->need_pay_date, need_pay_date);
	strcpy(rec->real_pay_date, datepay);
}

void show_firm(firm* rec)
{
	printf("\n %-5s|", rec->name);
	printf("\t%-13s|", rec->need_pay_date);
	printf("\t%-6s|", rec->taxe);
	printf("\t%s|\n", rec->real_pay_date);
	printf("\n-------------------------------------------\n");
}

void enter_firm(firm* firms, int name_length, int firms_amount)
{
	int free = 0;

	char* temp_name;
	char temp_deadline[DATE_SIZE];
	char temp_taxe[TAXE_SIZE];
	char temp_date_pay[DATE_SIZE];

	while (firms[free].name[0] != '\0')
	{
		++free;
		if (free == firms_amount)
		{
			printf("\n-------------------------------------------\n");
			printf("\nDatabase is full\n");
			return;
		}
	}

	temp_name = (char *)malloc(sizeof(char)*name_length);
	do
	{
		printf("Enter name: ");
	} while (get_name(temp_name, name_length) != SUCCESS);

	do
	{
		printf("Enter deadline: ");
	} while (get_date(temp_deadline) != SUCCESS);

	do
	{
		printf("Enter taxe: ");
	} while (get_taxe(temp_taxe) != SUCCESS);

	do
	{
		printf("Enter date_pay: ");
	} while (get_date(temp_date_pay) != SUCCESS);

	add_firm_name(&firms[free], temp_name);
	add_firm_dates(&firms[free], temp_deadline, temp_date_pay);
	add_firm_taxe(&firms[free], temp_taxe);
}

int enter_menu()
{
	int choice;

	printf("\n1.Add firm");
	printf("\n2.Show depts");
	printf("\n3.Show all");
	printf("\n4.Switch database(Your and shabloned)");
	printf("\n5.Exit");
	printf("\n\nChoice: ");

	scanf("%d", &choice);

	while (getchar() != '\n');
	return choice;
}

int month_compare(char* month, char* deadline)
{
	int i = 0;
	int j;
	while (deadline[i++] != '.');
	for (j = 0; j < 2; ++j)
	{
		if (month[j] != deadline[i++])
			return FALSE;
	}
	return TRUE;
}

void five_debt(firm* rec, char* month_of_deadline, int firms_amount)
{
	int i = 0, j = 0;
	int max, ind;
	int find_rec = FALSE;//становится TRUE если найден должник соответсвующий условиям поиска
	int curr_minimas = 0;//кол-во элементов с подходящей датой
	int k = 0;

	while (i<firms_amount)
	{
		if (month_compare(month_of_deadline, rec[i].need_pay_date) == 1)
		{
			find_rec = TRUE;
			break;
		}
		++i;
	}

	//если нету записей
	if (i == 0 && find_rec == FALSE)
	{
		printf("\n-------------------------------------------\n");
		printf("\nError, database is empty\n");
		return;
	}
	//если нету подходящего месяца
	else if (find_rec == FALSE)
	{
		printf("\n-------------------------------------------\n");
		printf("\nNo suitable records\n");
		return;
	}
	//если есть хоть одна запись - задать шапку
	else
	{
		show_head();
		max = atoi(rec[i].taxe);
		ind = i;
	}

	//скидываем в начало массива максимальные задолженности с подходящей датой
	//curr_minimas - покажет их конечное кол-во
	for(i = 0;i<AMOUNT_DEBT;++i)
	{
		if(rec[i].name[0] == '\0' || i>= firms_amount)
		{
			break;
		}

		for(j = curr_minimas;j<firms_amount;++j)
		{
			if(max<atoi(rec[j].taxe) && month_compare(month_of_deadline, rec[j].need_pay_date) == TRUE)
			{
				ind  = j;
				max  = atoi(rec[j].taxe);
				find_rec = TRUE;
			}
		}
		if(find_rec == TRUE)
			{
				find_rec = FALSE;
				swap_firms((rec+curr_minimas),(rec+ind));
				++curr_minimas;
				max = -1;
			}
	}
	//теперь в первых curr_minimas элементах лежат максимальные долги, осортируем первые curr_minimas элементов
	for (i = 0; i < curr_minimas; ++i)
	{

		for (j = i; j < curr_minimas; ++j)
		{
			//если строки равны переходим к следующей итерации
			if (strcmp(rec[i].name, rec[j].name) == 0)
			{
				continue;
			}

			k = 0;
			//проматываем одинаковые элементы
			while (rec[i].name[k] == rec[j].name[k])
			{
				++k;
			}

			//если строка короче, то её поднимаем наверх
			if ((rec[i].name[k] > rec[j].name[k]) || (rec[j].name[k] == '\0'))
			{
				swap_firms(&rec[i], &rec[j]);
			}
		}
	}
	//выведем первые пять элементов
	for (i = 0; i < curr_minimas; ++i)
	{
		show_firm(&rec[i]);
	}
}

void swap_str_dynamic(char **str1,char **str2)
{
	char *temp;
	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

void swap_str_static(char* str1, char* str2)
{
	char temp[SHABLON_NAME_SIZE];
	strcpy(temp,str1);
	strcpy(str1,str2);
	strcpy(str2,temp);
}

void swap_firms(firm* rec1, firm* rec2)
{
	swap_str_dynamic(&rec1->name, &rec2->name);
	swap_str_static(rec1->real_pay_date, rec2->real_pay_date);
	swap_str_static(rec1->need_pay_date, rec2->need_pay_date);
	swap_str_static(rec1->taxe, rec2->taxe);
}
