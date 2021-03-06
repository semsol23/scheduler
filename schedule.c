#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "schedule.h"

#define MAX_TYPE		7

extern int errno;

//strings for printing the name of each enum element
//enum type's name
char type_string[MAX_TYPE][20] = 
{
	"drama",
	"movie",
	"advertisement",
	"entertainment",
	"meeting",
	"fitness",
	"privacy"
};

//month's name
char month_string[13][4] = 
{
	"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

//enum definitions
typedef enum scheduleType {
	drama=0, 		//드라마 
	movie, 			//영화 
	advertisement, 	//광고 
	entertainment, 	//예능 
	meeting,		//회의 
	fitness,		//운동 
	privacy			//개인사 
} scheduleType_e;



//structure definition for a schedule info.
typedef struct schedInfo
{
	char name[200];			//schedule name
	scheduleType_e type;	//schedule type
	int month;				//when : month
	int day;				//when : day
	char place[100];		//where
} schedInfo_t;


void sched_printTypes(void) 
{
	int i;
	
	for (i=0;i<MAX_TYPE;i++) {
		printf("- %s\n", type_string[i]);
	}
}

void sched_print(void* obj) 
{
	schedInfo_t* schedPtr = (schedInfo_t*)obj;
	
	if (schedPtr == NULL) {
		printf("[ERROR] failed to print the schedule Info! (object is NULL)\n");
	}
	
	printf("Schedule Name : %s (%s)\n", schedPtr->name, type_string[schedPtr->type]);
	printf("When : %s. %i\n", month_string[schedPtr->month], schedPtr->day);
	printf("Where : %s\n", schedPtr->place);
	
	return;
}









//generating a structure of scheduling information
void* sched_genSchedInfo(char* name, char* place, int type, int month, int day)
{
	//error handler
	// Through errno, handle the error
	schedInfo_t* schedPtr;
	if(errno == 0){
		//allocate memory and set the member variables
		// allocate memory of schedPtr
		schedPtr = malloc(sizeof(struct schedInfo));
		
		// set the member variables
		strcpy(schedPtr->name, name);
		strcpy(schedPtr->place, place);
		schedPtr->type = type;
		schedPtr->month = month;
		schedPtr->day = day;
	}else{
		// If an error occurs by errno, perror function print the error string.
		perror("[ERROR]");
	}
	
	
	return (void*)schedPtr;
}



//get month information from the scheduler info structure
float sched_getMonth(void* obj)
{
	schedInfo_t* schedPtr = (schedInfo_t*)obj; // Casting obj to schedInto_t structure.
	return (float)schedPtr->month; // return month of input obj
}


//get type information from the scheduler info structure
int sched_getType(void* obj)
{
	schedInfo_t* schedPtr = (schedInfo_t*)obj; // Casting obj to schedInto_t structure.
	return schedPtr->type; // return type of input obj
}



//get place string information from the scheduler info structure
char* sched_getPlace(void* obj)
{
	schedInfo_t* schedPtr = (schedInfo_t*)obj; // Casting obj to schedInto_t structure.
	return schedPtr->place; // return type of input obj
}

//convert the name of the type into the enum(integer) value
int sched_convertType(char* typeName)
{
	// Get match type code with user input typeName.
	if(!strcmp("drama",typeName)){
		return 0;
	}else if(!strcmp("movie",typeName)){
		return 1;
	}else if(!strcmp("advertisement",typeName)){
		return 2;
	}else if(!strcmp("entertainment",typeName)){
		return 3;
	}else if(!strcmp("meeting",typeName)){
		return 4;
	}else if(!strcmp("fitness",typeName)){
		return 5;
	}else if(!strcmp("privacy",typeName)){
		return 6;
	}else{
		// If user input typeName isn't included in predefined types, return negative value.
		return -1;
	}
}

