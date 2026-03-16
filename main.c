#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MONTHS_NUM 12
#define RED "\033[31m" 

/* Prototypes */
void print_month(char *current_month, int total_days, int current_day, int current_year);
int check_leap(int year);
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
    time_t now 		= time(NULL);
    struct tm *local 	= localtime(&now);
    int y 		= local->tm_year + 1900;
    int m 		= local->tm_mon;
    int d		= local->tm_mday;
    Month months_array[MONTHS_NUM];

    ///* Populate array*///
   // printf("%-12s %-10s %-2s\n", "INDEX", "NAME", "DAYS");
    for (int i = 0; i < MONTHS_NUM; i++ ) {
        /* assign the name to each month in the correct field of the struct */
        months_array[i].month_name = MONTHS_LIST[i]; 

        /* assign the correct number of days - no leap */
        switch (i)
        {
	    /* Months with 31 days */
            case 3:
            case 5:
            case 8:
            case 10:
                months_array[i].num_days = POSSIBLE_DAYS_N[1];
                break;
	    /* February */
            case 1:
		if((check_leap(y)) == 0 ) {
                months_array[i].num_days = POSSIBLE_DAYS_N[2];
		} else {
		    months_array[i].num_days = POSSIBLE_DAYS_N[3];
		}
		break;
	    /* Months with 30 days */
            default:
                months_array[i].num_days = POSSIBLE_DAYS_N[0];
                break;
        }
        

    }

    
    /* Print selected month */
    int c;
    int selected_month = m;
    while (( c = getchar()) != EOF) {
	system("clear");
	print_month( months_array[selected_month].month_name, months_array[selected_month].num_days, d, y);
	
	if ( c == '\x1b') {
	    getchar();
	    char arrow = getchar();
	    if ((arrow == 'C') 
		 && ( selected_month < ( MONTHS_NUM - 1))) selected_month++;
	    if ((arrow == 'D')
		 && ( selected_month > 0 )) selected_month--;
	}
    }
    /*
    int current_month = 0;
    while (current_month < MONTHS_NUM) {
	print_month ( months_array[current_month].month_name, months_array[current_month].num_days, year );
	puts(" ");
	current_month++;
    }


    printf("%s\n"
	   "%d", asctime(local), month);
*/

}


/* Function declarations */


void print_calendar();


/* Print months in a correct format */
void print_month(char *current_month, int total_days, int current_day, int current_year) 
{
    int week_days_counter = 1;
    printf("\t\t %s\t%d\n"
	   "%s\n", current_month, current_year, "---------------------------------------------");

    for ( int i = 1 ; i <= total_days; i++ ) {
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

/* Function to check if the current year is a leap year*/
int check_leap(int year)
{
    if (( year % 400 ) == 0) {
	return 0;
    }
    if ((( year % 4 ) == 0 ) 
	   && (!(( year % 100 ) == 0 ))) {
	return 0;
} else {
	return 1;
    }
}




















