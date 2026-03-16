#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MONTHS_NUM 12

/* Prototypes */
void print_month(char *m, int d);

/* Structs */
typedef struct 
{
    char *month_name;
    int num_days;
}Month;

/* Global variables */

static const char *MONTHS_LIST[] = {
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
};

static const int POSSIBLE_DAYS_N [] = {31, 30, 29, 28};
int main()
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    int year = local->tm_year + 1900;

    Month months_array[MONTHS_NUM];

    ///* Populate array*///
   // printf("%-12s %-10s %-2s\n", "INDEX", "NAME", "DAYS");
    for (int i = 0; i < MONTHS_NUM; i++ ) {
        /* assign the name to each month in the correct field of the struct */
        months_array[i].month_name = MONTHS_LIST[i]; 

        /* assign the correct number of days - no leap */
        switch (i)
        {
            case 3:
            case 5:
            case 8:
            case 10:
                months_array[i].num_days = POSSIBLE_DAYS_N[1];
                break;
            case 1:
                months_array[i].num_days = POSSIBLE_DAYS_N[2];
		break;
            default:
                months_array[i].num_days = POSSIBLE_DAYS_N[0];
                break;
        }
        
        //printf("\n %d \t %-10s \t %d \n", i+1, months_array[i].month_name, months_array[i].num_days);



    }

    print_month ( months_array[0].month_name, months_array[0].num_days );

}

void print_menu();



void print_month(char *m, int d) 
{
    int week_days_counter = 1;
    printf("\t\t %s\n"
	   "%s\n", m, "-------------------------------------------------");

    for ( int i = 1 ; i <= d; i++ ) {
	printf("%-8d", i);
	/* Checks for week ending */
	if( week_days_counter == 7 ) {
	    printf("\n");
	    week_days_counter = 1;

	} else {
	    week_days_counter++;
	}



    }
   printf("\n"); 

}


