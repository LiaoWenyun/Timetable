//examples in config.txt file
//ENG422(A)  Mon 9:30am-10:30am  Wed 3:00pm-4:30pm
//SNEG422(B)  Mon 1:30pm-3:30pm 
//CSC455(A)  Wed 10:30am-11:30am 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct Class{
	char* class_name;
	char* day;
	int start_time;
	int length;
};                 


char* get_today();
void yellow();
void reset();
void read_file();
void print_array(struct Class*);
int parse_time(char* );
int parse_length(char*);
int map_time(char*); 		
void insert_empty_class( struct Class*, struct Class* , struct Class*, struct Class*, struct Class*);
int schedule(struct Class*, struct Class*, struct Class*, struct Class*, struct Class*, struct Class*);
char* space(char*);
void print_schedule(struct Class*, struct Class*, struct Class* , struct Class* , struct Class*);


/**
/* Gets the local current date 
/* @param none 
/* @return pointer to char string today, which will be Mon/Tus/Wed/Thu/Fri 
**/
char* get_today(){
  	char* rest;
	time_t now;    // time_t is arithmetic time type
	time(&now);    //get the current time 
	char *today = strtok_r(ctime(&now)," ",&rest);	
	return today;
}


/**
/* Sets the charactors to be yellow when printing 
/* @param none
/* @return none
**/
void yellow(){
	printf("\033[0;33m");
}


/**
/* Reset the charactor color
/* @param none
/* @return none
**/
void reset(){
	printf("\033[0m");
}


/**
/* Open a file and parse the lines
/* @param pointer to a Class array class_list
/* @return none
**/
void read_file(struct Class* class_list){
	FILE *file; 
	char buffer[150]; 								 	//buffer to store the line
	char* path_to_file = getenv("HOME");				//get the environment variable which refer to the home directory  	
	char* f_name =  "/.config/timetable/config.txt";
	strcat( path_to_file , f_name );
	file = fopen(path_to_file , "r");
	if(file ==NULL){
		printf("ERROR: no config file found");
		exit(1);
	}else{
		int class_position = 0;
		while(fgets(buffer, sizeof(buffer), file)){	   //iterate through the file line by line 	
			int len = strlen(buffer);
			if( buffer[len-1] == '\n' ){ buffer[len-1] = 0;} //remove the "\n"
			int count = 0;
			char *name;
			char *end_str;
			char *token = strtok_r(buffer," ",&end_str);  	    //get the class name here. I use strtok_r() function instead of strtok() function, because strtok() does not allow tokenizing substrings.
			name = token;							//assign the obtained class name to the name variable 		
			while(token != NULL){					//	
				if(count ==0){
					*name=*token ;
				}else{
					if((count%2) == 1){
						struct Class class;
						class_list[class_position] = class;
						class_list[class_position].class_name= strdup(name);    //shallow copy the content in name variable, because *a = *b failed on this one.
						class_list[class_position].day= strdup(token);          //shallow copy the content of the token, same reason.
					}else {
						class_list[class_position].start_time = parse_time(token);
						class_list[class_position].length =parse_length(token);		
						class_position++;	
					}
				}
				token = strtok_r(NULL, " ",&end_str);	
				count++;
			}
		}	
	}
}


/**
/* Function prints out the content of each element in a Class array 
/* @param pointer to a Class array class_list 
/* @return none
**/
void print_array(struct Class* class_list){
	int i =0;
	for(i=0; i<30;i++){
		printf("node: %d, class name: %s, class day: %s , class time: %d, class length: %d \n ", i, class_list[i].class_name, class_list[i].day, class_list[i].start_time, class_list[i].length);
		}
}


/**
/* parse the time from the lines 
/* @param pointer to char token
/* @return integer type
**/
int parse_time(char* token){
	char* time;
	time = strdup(token);
	char *end_token;
	char* start_time = strtok_r(time, "-", &end_token);   
	return map_time(start_time);
}


/**
/* calculate the length of each class 
/* @param pointer to char token
/* @return integer type 
**/
int parse_length(char *token){
	char* time;
	time = strdup(token);
	char* end_time;
	char* start_time = strtok_r(time,"-",&end_time);
	return map_time(end_time) - map_time(start_time);
}


/**
/* map the time string to an integer 
/* @param pointer to char time 
/* @return integer type
**/
int map_time(char *time){
	int result = 0;
	if( strcmp(time,"8:30am") == 0){result = 0;}
	else if( strcmp(time, "8:50am")==0){ result =20;}  
	else if( strcmp(time, "9:00am")==0){ result =30;}
   	else if( strcmp(time, "9:20am")==0){ result =50;}
	else if( strcmp(time, "9:30am")==0){ result =60;}
	else if( strcmp(time,"9:50am")==0){ result =80;}
	else if( strcmp(time,"10:00am")==0){ result =90;}
	else if( strcmp(time,"10:20am")==0){ result =110;}					
	else if( strcmp(time,"10:30am")==0){ result =120;}
	else if( strcmp(time,"10:50am")==0){ result =140;}
	else if( strcmp(time,"11:00am")==0){ result =150;}
	else if( strcmp(time,"11:20am")==0){ result =170;}				 		
	else if( strcmp(time,"11:30am")==0){ result =180;}
	else if( strcmp(time,"11:50am")==0){ result =200;}	
	else if( strcmp(time,"12:00pm")==0){ result =210;}	
	else if( strcmp(time,"12:20pm")==0){ result =230;}	
	else if( strcmp(time,"12:30pm")==0){ result =240;}
	else if( strcmp(time,"12:50pm")==0){ result =260;}	
	else if( strcmp(time,"1:00pm")==0){ result =270;}
	else if( strcmp(time,"1:20pm")==0){ result =290;}	
	else if( strcmp(time,"1:30pm")==0){ result =300;}
	else if( strcmp(time,"1:50pm")==0){ result =320;}
	else if( strcmp(time,"2:00pm")==0){ result =330;}	
	else if( strcmp(time,"2:20pm")==0){ result =350;}	
	else if( strcmp(time,"2:30pm")==0){ result =360;}	
	else if( strcmp(time,"2:50pm")==0){ result =380;}
	else if( strcmp(time,"3:00pm")==0){ result =390;}	
	else if( strcmp(time,"3:20pm")==0){ result =410;}	
	else if( strcmp(time,"3:30pm")==0){ result =420;}
	else if( strcmp(time,"3:50pm")==0){ result =440;}
	else if( strcmp(time,"4:00pm")==0){ result =450;}
	else if( strcmp(time,"4:20pm")==0){ result =470;}
   	else if( strcmp(time,"4:30pm")==0){ result =480;}
   	else if( strcmp(time,"4:50pm")==0){ result =500;}
	else if( strcmp(time,"5:00pm")==0){ result =510;}   
	else if( strcmp(time,"5:20pm")==0){ result =530;}
	else if( strcmp(time,"5:30pm")==0){ result =540;}
	else if( strcmp(time,"5:50pm")==0){ result =560;}
	else if( strcmp(time,"6:00pm")==0){ result =570;}
	else if( strcmp(time,"6:20pm")==0){ result =590;}	
	else if( strcmp(time,"6:30pm")==0){ result =600;}				
	else if( strcmp(time,"6:50pm")==0){ result =620;}	
	else if( strcmp(time,"7:00pm")==0){ result =630;}	
	else if( strcmp(time,"7:20pm")==0){ result =650;}	
	else if( strcmp(time,"7:30pm")==0){ result =660;}	
	else if( strcmp(time,"7:50pm")==0){ result =680;}	
	else if( strcmp(time,"8:00pm")==0){ result =690;}
	else if( strcmp(time,"8:20pm")==0){ result =710;}	
	else if( strcmp(time,"8:30pm")==0){ result =720;}	
	else if( strcmp(time,"8:50pm")==0){ result =740;}	
	else if( strcmp(time,"9:00pm")==0){ result =750;}	
	else if( strcmp(time,"9:20pm")==0){ result =770;}	
	else if( strcmp(time,"9:30pm")==0){ result =780;}
	else if( strcmp(time,"9:50pm")==0){ result =800;}	
	else if( strcmp(time,"10:00pm")==0){ result =810;}
	else if( strcmp(time,"10:20pm")==0){ result =830;}
	else if( strcmp(time,"10:30pm")==0){ result =840;}
	else if( strcmp(time,"10:50pm")==0){ result =860;}	 
	else if( strcmp(time,"11:00pm")==0){ result =870;}
	else if( strcmp(time,"11:20pm")==0){ result =890;}	 
	else if( strcmp(time,"11:30pm")==0){ result =900;}
	else{  
		printf("no time found \n");
	}   
	return result;
}



/**
/* Scheduler, distribute the class node to appropriate array and arrage the array  
/* @param pointer to a Class array class_list, M_class, T_class, W_class, Th_class, F_class
/* @return integer type
**/
int schedule(struct Class* class_list, struct Class* M_class, struct Class* T_class, struct Class* W_class, struct Class* Th_class, struct Class* F_class){
	int i ;
	int conflict = 0;
	for(i=0; i<30;i++){
			int num_nodes = (class_list[i].length+10)/30;  //calculate how many nodes this class will need
			int j;
			for(j=0; j<num_nodes; j++){
				struct Class class = { class_list[i].class_name , class_list[i].day , class_list[i].start_time + 30*j ,30};
				if(strcmp(class_list[i].day,"M")==0){
						if(strcmp(M_class[class_list[i].start_time/30 + j].class_name,"          ")!=0){
							printf("time conflict between class: %s and %s \n ",M_class[class_list[i].start_time/30 + j].class_name, class.class_name);
							conflict = 1;		
						}else{
								M_class[class_list[i].start_time/30 + j] = class;
						}
				 }else if(strcmp(class_list[i].day,"T")==0){
						if(strcmp(T_class[class_list[i].start_time/30 + j].class_name,"          ")!=0){
							printf("time conflict between class: %s and %s \n ",T_class[class_list[i].start_time/30 + j].class_name, class.class_name);
							conflict = 1;
						}else{
						 T_class[class_list[i].start_time/30 + j] = class;
						}
				 }else if(strcmp(class_list[i].day,"W")==0){
						if(strcmp(W_class[class_list[i].start_time/30 + j].class_name,"          ")!=0){
							printf("time conflict between class: %s and %s \n ",W_class[class_list[i].start_time/30 + j].class_name, class.class_name);
							conflict = 1;
						}else{
						 W_class[class_list[i].start_time/30 + j] = class;
						}
				 }else if(strcmp(class_list[i].day,"Th")==0){
						if(strcmp(Th_class[class_list[i].start_time/30 + j].class_name,"          ")!=0){
							printf("time conflict between class: %s and %s \n ",Th_class[class_list[i].start_time/30 + j].class_name, class.class_name);
							conflict = 1;
						}else{
						 Th_class[class_list[i].start_time/30 + j] = class;
						}
				 }else if(strcmp(class_list[i].day,"F")==0){
						 if(strcmp(F_class[class_list[i].start_time/30 + j].class_name,"          ")!=0){
						 	printf("time conflict between class: %s and %s \n ",F_class[class_list[i].start_time/30 + j].class_name, class.class_name);
						 	conflict = 1;
						 }else{
							F_class[class_list[i].start_time/30 + j] = class;
						 }	
				 }else{ return conflict;
				      }		 
			}
	}
	return conflict;
}



/**
/* Insert empty classes into the five arrays
/* @param pointer to a Class array M_class, T_class, W_class, Th_class, F_class
/* @return none
**/
void insert_empty_class( struct Class* M_class, struct Class* T_class, struct Class* W_class, struct Class* Th_class, struct Class* F_class){
	int i ;
	int tmp_start_time = 0;
	for (i=0; i<30;i++){
		struct Class class = {"          "," ",tmp_start_time+30*i, 30};
		M_class[i] = class;
		T_class[i] = class;
		W_class[i] = class;
		Th_class[i] = class;
		F_class[i] = class;
	}
}


/**
/* format the diaplayed class name to be 10 space
/* @param pointer to a char array name
/* @return pointer to a char array (with formated length)
**/
char* space(char* name){
	char* tmp_name;
	if(strlen(name)==10){
		return name;
	}else if(strlen(name)==9){
		tmp_name = " ";
		strncat(name, tmp_name, 1); 		
	}else if(strlen(name)==8){
		tmp_name = "  ";
		strncat(name,tmp_name, 1);
	}else if(strlen(name)==7){
		tmp_name ="   ";
		strncat(name,tmp_name, 1);
	}else if(strlen(name)==6){
		tmp_name ="    ";
		strncat(name,tmp_name, 1);
	}else{
		return name;
	}
	return name;
}


/**
/* Prints out the time table
/* @param pointer to a Class array class_list, M_class, T_class, W_class, Th_class, F_class
/* @return none
**/
void print_schedule(struct Class* M_class, struct Class* T_class, struct Class* W_class, struct Class* Th_class, struct Class* F_class){
	char* today = get_today();
	printf(" ----------------------------------------------------------------------------------------------\n");		
	printf("|         |" );
	if(strcmp(today,"Mon")==0){
		yellow();
		printf("     Monday     ");
		reset();
	}else{
		printf("     Monday     ");
	}
	printf("|");
	if(strcmp(today,"Tue")==0){
		yellow();
		printf("     Tuesday    ");
		reset();	
	}else{
		printf("     Tuesday    ");
	}
	printf("|");
	if(strcmp(today,"Wed")==0){
		yellow();
		printf("    Wednesday   ");
		reset();
	}else{
		printf("    Wednesday   ");
	}
	printf("|");
	if(strcmp(today,"Thu")==0){
		yellow();
		printf("    Thursday    ");
		reset();
	}else{
		printf("    Thursday    ");
	}
	printf("|");
	if(strcmp(today,"Fri")==0){
		yellow();
		printf("     Friday     ");
		reset();
	}else{
		printf("     Friday     ");
	}
	printf("|\n");
	printf("|----------------------------------------------------------------------------------------------|\n");
	int i;
	for(i=0; i<30; i++){
		int hour = 8.5+i*0.5;
		char* unit="am";
		if(hour<10){
			unit = " am";
		}
		if(hour > 12){
			hour = hour%12;
			unit = "pm";
			if(hour<10){
				unit = " pm";
			}
		}
		int min = ((i+1)%2)*3; 
		printf("|%d:%d0%s -|----------------|----------------|----------------|----------------|----------------|\n", hour,min,unit);
		printf("|         |   %s   |   %s   |   %s   |   %s   |   %s   |\n",space(M_class[i].class_name),space(T_class[i].class_name),space(W_class[i].class_name),space(Th_class[i].class_name),space(F_class[i].class_name) );
	}
	printf(" ----------------------------------------------------------------------------------------------\n");
}



int main(){
	struct Class class_list[31];    //give it a random size	
	struct Class M_class[37];
	struct Class T_class[37];
	struct Class W_class[37];
	struct Class Th_class[37];
	struct Class F_class[37];
	read_file(class_list);          //parse the file, and atore all the Class structs into the class list 
	insert_empty_class(M_class, T_class, W_class, Th_class, F_class);
	int conflict = schedule(class_list,M_class, T_class, W_class, Th_class, F_class); 
	if(conflict ==0){print_schedule(M_class, T_class, W_class, Th_class, F_class);}	
	return 0;
}
