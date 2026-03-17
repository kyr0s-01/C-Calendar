#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define MONTHS_NUM 12
#define ANSI_RED_COLOR "\033[31m"
#define ANSI_RESET     "\033[0m"

/* Structs */
typedef struct 
{
    char *month_name;
    int num_days;
    int is_sys_month;
}Month;


/* Prototypes */
void print_month( Month current_month, int current_day, int current_year );
int check_leap(int year);

/* Global variables */
static const char *MONTHS_LIST[] = {
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
};

static const int POSSIBLE_DAYS_N [] = {31, 30, 29, 28};

/********/
/* MAIN */
/********/
int main()
{
    time_t now 		= time(NULL);
    struct tm *local 	= localtime(&now);
    int y 		= local->tm_year + 1900;
    int m 		= local->tm_mon;
    int d		= local->tm_mday;
    
    Month months_array[MONTHS_NUM];

    ///* Populate array*///
    for (int i = 0; i < MONTHS_NUM; i++ ) {
        /* assign the name to each month in the correct field of the struct */
        months_array[i].month_name = MONTHS_LIST[i]; 

        /* assign the correct number of days */
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
		/* Check leap year and adjust number of days for february */
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
    months_array[selected_month].is_sys_month = 1; //flag the current system month
    
    
    while (( c = getchar()) != EOF) {
	system("clear");
	print_month( months_array[selected_month], d, y );
	
	/* Read input */
	if ( c == '\x1b') {
	    getchar();
	    char arrow = getchar();
	    if ((arrow == 'C') 
		 && ( selected_month < ( MONTHS_NUM - 1))) selected_month++;
	    if ((arrow == 'D')
		 && ( selected_month > 0 )) selected_month--;
	}
    }
}


/* Function declarations */

/*********************************/
/* PRINT MONTH IN CORRECT FORMAT */
/*********************************/

void print_month( Month current_month, int current_day, int current_year ) 
{
    int week_days_counter = 1;
    printf("\t\t %s\t%d\n"
	   "%s\n", current_month.month_name, current_year, "--------------------------------------------------");

    for ( int i = 1 ; i <= current_month.num_days; i++ ) {
	
	/* check if the i day is the current day in the system */
	if (( i == current_day )
	     && ( current_month.is_sys_month == 1 )) {
		printf(ANSI_RED_COLOR"%-8d"ANSI_RESET, i); //print the current system day in RED and reset 
	} else {
	    printf("%-8d", i);
	}

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

/****************************************/
/* CHECK IF CURRENT YEAR IS A LEAP YEAR */
/****************************************/
/* A Leap year has 366 days. In order to be a leap, an year must be divisible by 4 and not by 100 if not the first year in a century. Otherwise by 400. 
 * The funcion returns 0 if the given year is leap, 1 if not. */

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




















