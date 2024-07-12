#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_STATES 50

struct climate_info { //Struct that will contain all the information of the weather
    char code[3];
    unsigned long num_records;
    long double sum_temperature; //Degrees are converted from Kelvin to Fahrenheit
    long double sum_humidity;
    float max_temp;
    float min_temp;
    long int max_temp_time;
    long int min_temp_time;
    unsigned int lightning;
    unsigned int snow;
    long double sum_cloud;
};

void analyze_file(FILE *file, struct climate_info *states[], int num_states);
void print_report(struct climate_info *states[], int num_states);

int main(int argc, char *argv[]){ 

    if (argc < 2){ //If there is not more than 2 arguments, this will fail
        printf("Usage: %s tdv_file1 tdv_file2 ... tdv_fileN \n", argv[0]);
        return EXIT_FAILURE;
    }

    struct climate_info *states[NUM_STATES] = {NULL};

    int i;
    for (i = 1; i < argc; ++i) { //Creates a file that opens and reads them, if there is an error, it will not close it
        FILE *fp = fopen(argv[i],"r");

        if(fp != NULL){
            printf("Opening file: %s\n", argv[i]);
            analyze_file(fp, states, NUM_STATES);
            fclose(fp);   
        }else{
            printf("Failed to open file: %s\n",argv[i]);
        }
    }

    print_report(states, NUM_STATES);
    
    return 0;
}

void analyze_file(FILE *file, struct climate_info **states, int num_states) { //Used to look through the files to collect the data that is needed
    const int line_sz = 100;
    char line[line_sz];
    while (fgets(line, line_sz, file) != NULL) {
        char *token = strtok(line, "\t\n");
        char *tokenList[9];
        int index = 0;
        while(token != NULL && index < 9){
            tokenList[index] = token;
            token = strtok(NULL, "\t\n");
            index++;
        }

        struct climate_info *primary_state = malloc(sizeof(struct climate_info)); //Creates a dynamic memory to store the information

        strncpy(primary_state->code, tokenList[0],2); //Goes through each line and every "\t" to gain information depending on location fills in the variable
        primary_state->num_records = 1;
        primary_state->min_temp_time = (atof(tokenList[1]))/1000; 
        primary_state->max_temp_time = (atof(tokenList[1]))/1000;
        primary_state->sum_humidity = (atof(tokenList[3]));
        primary_state->snow = (atof(tokenList[4]));
        primary_state->sum_cloud = (atof(tokenList[5]));
        primary_state->lightning = (atof(tokenList[6]));
        primary_state->min_temp = ((atof(tokenList[8])) * (1.8) - 459.67); //Converts the weather to Fahrenheit
        primary_state->max_temp = ((atof(tokenList[8])) * (1.8) - 459.67);
        primary_state->sum_temperature = ((atof(tokenList[8])) * (1.8) - 459.67);

        char *code = primary_state->code; //Basic state

        for(int i = 0; i < num_states; i++){
            if(states[i] == NULL){
                states[i] = primary_state;
                break;
            }else if(strcmp(states[i]->code,code) == 0){ //Inputs the information through a repeated for loop
                states[i]->num_records++;
                states[i]->sum_humidity += primary_state->sum_humidity;
                states[i]->snow += primary_state->snow;
                states[i]->sum_cloud += primary_state->sum_cloud;
                states[i]->lightning += primary_state->lightning;
                states[i]->sum_temperature += primary_state->sum_temperature;

                if(states[i]->max_temp <= primary_state->sum_temperature){
                    states[i]->max_temp = primary_state->sum_temperature;
                    states[i]->max_temp_time = primary_state->max_temp_time;
                }

                if(states[i]->min_temp >= primary_state->sum_temperature){
                    states[i]->min_temp = primary_state->sum_temperature;
                    states[i]->min_temp_time = primary_state->min_temp_time;
                }
                break;
            }
    }
    }
}

void print_report(struct climate_info *states[], int num_states) { //Prints the report
    printf("States found:\n");
    int i;
    for (i = 0; i < num_states; ++i) {
        if (states[i] != NULL) {
            struct climate_info *info = states[i];
            printf("%s ", info->code);
        }
    }
    printf("\n");

    for(i = 0; i < num_states; ++i){
        if(states[i] != NULL){
            struct climate_info *info = states[i];
            printf("-- State: %s --\n",info->code);
            printf("Number of Records: %lu\n",info->num_records);
            printf("Average Humidity: %.1Lf%%\n",(info->sum_humidity / info->num_records));
            printf("Average Temperature: %.1LfF\n", (info->sum_temperature / info->num_records));
            printf("Max Temperature: %.1fF\n",info->max_temp);
            printf("Max Temperature on: %s", ctime(&info->max_temp_time)); //Changes the time and expresses as a Unix timestamp
            printf("Min Temperature: %.1fF\n",info->min_temp);
            printf("Min Temperature on: %s", ctime(&info->min_temp_time)); //Changes the time and expresses as a Unix timestamp
            printf("Lightning Strikes: %d\n",info->lightning);
            printf("Records with Snow Cover: %d\n",info->snow);
            printf("Average Cloud Cover: %.1Lf%%\n", (info->sum_cloud / info->num_records));
        }
    }
}