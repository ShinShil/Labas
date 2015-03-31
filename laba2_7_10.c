#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAIL 0
#define LINE printf("\n---------------------------------\n");
#define SLASH printf("\n/////////////////////////////////\n");
#define CIRCLE 1
#define TRIANGLE 2
#define TRAPECIYA 3
#define EMPTY -1
#define PI 3.14

typedef struct
{
	union
	{
		struct 
		{
			int radius;
		}circle;
		
		struct
		{
			int side;
			int height;
		}triangle;

		struct
		{
			int medium_line;
			int height;
		}trapeciya;
	}type_db;

	int type;
	double square;
}figure;

int enter(int* q,int bottom_val,int top_val);

void enter_menu(void);

void init_figs(figure* figs, int figs_amount);
void fig_enter(figure* figs, int figs_amount);
void figs_show_one(figure* figs);
void figs_show_all(figure* figs, int figs_amount);
void figs_remove_last_add(figure* figs, int figs_amount);

int main(void)
{
	const int FIGS_MAX = 10;
	
	int figs_amount;
	int choice;
	
	figure* figs;
	
	printf("Enter the amount of figures(10 is maximum): ");
	enter(&figs_amount,1,FIGS_MAX);
	figs = (figure*)malloc(sizeof(figure)*figs_amount);
	if(!figs)
	{
		printf("Memory error with figs.\n");
		return 1;
	}
	init_figs(figs,figs_amount);

	for(;;)
	{
		SLASH
		enter_menu();
		printf("Your choice: ");
		enter(&choice,1,4);

		switch(choice)
		{
		case 1:
			fig_enter(figs,figs_amount);
			break;
		case 2:
			figs_show_all(figs, figs_amount);
			break;
		case 3:
			figs_remove_last_add(figs, figs_amount);
			break;
		case 4:
			free(figs);
			return 0;
			break;
		}
	}

	printf("\n\n");
	return 0;
}

void init_figs(figure* figs, int figs_amount)
{
	int i;

	for(i = 0;i<figs_amount;++i)
	{
		figs[i].type = EMPTY;
	}
}

int enter(int* q,int bottom_val,int top_val)
{
	const int TIMES_MAX_AMOUNT = 3;
	int times_amount = 0;
	char ch_temp;

	if(bottom_val>top_val)
	{
		printf("\nError in function enter, sorry!\n");
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
				exit(0);
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
				exit(0);
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

void enter_menu(void)
{
	printf("1.Add figure\n");
	printf("2.Show all added figures\n");
	printf("3.Remove last added figure\n");
	printf("4.Exit\n");
}

void fig_enter(figure* figs, int figs_amount)
{
	int curr = 0;
	int choice;
	int par1, par2;//for radius, height, etc.

	while(figs[curr].type!=EMPTY && curr<figs_amount)
	{
		++curr;
	}
	if(curr >= figs_amount)
	{
		printf("\nToo many figures\n");
		return;
	}

	printf("\n1.Circle\n");
	printf("2.Triangle\n");
	printf("3.Trapeciya\n");
	printf("Enter the type of figure: ");
	enter(&choice,1,3);
	switch(choice)
	{
	case CIRCLE:
		printf("Enter radius(between 0 and 15): ");
		enter(&par1,0,15);
		figs[curr].type_db.circle.radius = par1;
		figs[curr].square = par1*par1*PI;		
		break;
	case TRIANGLE:
		printf("Enter height(between 0 and 15): ");
		enter(&par1,0,15);
		printf("Enter side(between 0 and 15): ");
		enter(&par2,0,15);
		figs[curr].type_db.triangle.height = par1;
		figs[curr].type_db.triangle.side = par2;
		figs[curr].square = par1*par2/2;
		break;
	case TRAPECIYA:
		printf("Enter medium line(between 0 and 15): ");
		enter(&par1,0,15);
		printf("Enter height(between 0 and 15): ");
		enter(&par2,0,15);
		figs[curr].type_db.trapeciya.medium_line = par1;
		figs[curr].type_db.trapeciya.height = par2;
		figs[curr].square = par1*par2;
		break;
	}
	figs[curr].type = choice;
}

void figs_show_one(figure* fig)
{
	char str[3][15] = {"Circle","Triangle", "Trapeciya"};
	LINE
	printf("FIGURE: %s\n",str[fig->type - 1]);
	switch(fig->type)
	{
	case CIRCLE:
		printf("Radius %d\n", fig->type_db.circle.radius);
		break;
	case TRIANGLE:
		printf("Height: %d\n", fig->type_db.triangle.height);
		printf("Side: %d\n", fig->type_db.triangle.side);
		break;
	case TRAPECIYA:
		printf("Height: %d\n", fig->type_db.trapeciya.height);
		printf("Medium line: %d", fig->type_db.trapeciya.medium_line);
		break;
	}
	printf("The square: %lf",fig->square);
	LINE
	
}

void figs_show_all(figure* figs, int figs_amount)
{
	int i;
	if(figs[0].type == EMPTY)
	{
		LINE
			printf("No figures at all");
		LINE
	}
	for(i = 0;i<figs_amount &&figs[i].type!=EMPTY;++i)
	{
		figs_show_one(&figs[i]);
	}
}

void figs_remove_last_add(figure* figs,int figs_amount)
{
	int curr = 0;
	while(figs[curr].type!=EMPTY && curr<figs_amount)
	{
		++curr;
	}
	--curr;

	figs[curr].type = EMPTY;
}