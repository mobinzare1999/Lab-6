#include <stdio.h>
#include <string.h>


#define M_T 1000
#define M_S 30

typedef struct {
    char code_route[M_S];
    char departure[M_S];
    char destination[M_S];
    char date[M_S];
    char time_departure[M_S];
    char time_arrival[M_S];
    int delay;
} Trips;
enum t_command {c_date = 1 ,c_departure,c_destination,c_delay,c_tot_delay,c_end};
void list_date(Trips trips[], int num, char start[], char end[]);
void list_departure(Trips trips[], int num, char departure[]);
void list_destination(Trips trips[], int num, char destination[]);
void list_late(Trips trips[], int num, char start[], char end[]);
void list_total_delay(Trips trips[], int num, char code_route[]);
int main() {
    char start[M_S], end[M_S], departure[M_S], destination[M_S], code_route[M_S];
    int input;
    enum t_command cmd;
    Trips trips[M_T];
    FILE *fp;
    fp = fopen("log.txt","r");
    int num;
    if(fp == NULL){
        printf("error");
        return 0;
    }
    fscanf(fp,"%d",&num);
    while (!feof(fp)) {
        for (int i = 0; i < num; ++i) {
            fscanf(fp,"%s %s %s %s %s %s %d",
                   trips[i].code_route,
                   trips[i].departure,
                   trips[i].destination,
                   trips[i].date,
                   trips[i].time_departure,
                   trips[i].time_arrival,
                   &trips[i].delay);
        }
    }
    do{
        printf("\n\nSelect an option:\n");
        printf("1. list all rides departed within a certain interval of dates\n"
               "2. list all the trips starting from a given departure\n"
               "3. list all the trips with a given destination\n"
               "4. list all trips that reached their destination late, within a given interval of dates\n"
               "5. list the overall delay accumulated by the trips that are identified by a given route code\n"
               "6. terminate the program\n");
        scanf("%d",&input);
        switch (input) {
            case 1:
                cmd = c_date;
                break;
            case 2:
                cmd = c_departure;
                break;
            case 3:
                cmd = c_destination;
                break;
            case 4:
                cmd = c_delay;
                break;
            case 5:
                cmd = c_tot_delay;
                break;
            case 6:
                cmd = c_end;
                break;
            default:
                printf("invalid input\n");
                return -1;
        }
        switch (cmd) {
            case c_date:
                printf("\nEnter start date (yyyy/mm/dd): ");
                scanf("%s", start);
                printf("Enter end date (yyyy/mm/dd): ");
                scanf("%s", end);
                list_date(trips, num, start, end);
                break;
            case c_departure:
                printf("\nEnter departure point: ");
                scanf("%s", departure);
                list_departure(trips, num, departure);
                break;
            case c_destination:
                printf("\nEnter destination: ");
                scanf("%s", destination);
                list_destination(trips, num, destination);
                break;
            case c_delay:
                printf("\nEnter start date (yyyy/mm/dd): ");
                scanf("%s", start);
                printf("Enter end date (yyyy/mm/dd): ");
                scanf("%s", end);
                list_late(trips, num, start, end);
                break;
            case c_tot_delay:
                printf("\nEnter route code: ");
                scanf("%s", code_route);
                list_total_delay(trips, num, code_route);
                break;
            case c_end:
                printf("\nProgram terminated.\n");
                break;
            default:
                printf("\nnot correct input\n");
        }
    } while (cmd != c_end);

    return 0;
}

void list_date(Trips trips[], int num, char start[], char end[]) {
    for (int i = 0; i < num; i++) {
        if (strcmp(trips[i].date, start) >= 0 && strcmp(trips[i].date, end) <= 0) {
            printf("%s %s %s %s %s %s %d\n", trips[i].code_route, trips[i].departure,
                   trips[i].destination, trips[i].date, trips[i].time_departure,
                   trips[i].time_arrival, trips[i].delay);
        }
    }
}

void list_departure(Trips trips[], int num, char departure[]){
    for (int i = 0; i < num; ++i) {
        if(strcmp(trips[i].departure,departure)== 0){
            printf("%s %s %s %s %s %s %d\n", trips[i].code_route, trips[i].departure,
                   trips[i].destination, trips[i].date, trips[i].time_departure,
                   trips[i].time_arrival, trips[i].delay);
        }
    }
}

void list_destination(Trips trips[], int num, char destination[]){
    for (int i = 0; i < num; ++i) {
        if(strcmp(trips[i].destination,destination)== 0){
            printf("%s %s %s %s %s %s %d\n", trips[i].code_route, trips[i].departure,
                   trips[i].destination, trips[i].date, trips[i].time_departure,
                   trips[i].time_arrival, trips[i].delay);
        }
    }
}

void list_late(Trips trips[], int num, char start[], char end[]){
    for (int i = 0; i < num; i++) {
        if (strcmp(trips[i].date, start) >= 0 && strcmp(trips[i].date, end) <= 0) {
            if (trips[i].delay > 0) {
                printf("%s %s %s %s %s %s %d\n", trips[i].code_route, trips[i].departure,
                       trips[i].destination, trips[i].date, trips[i].time_departure,
                       trips[i].time_arrival, trips[i].delay);
            }
        }
    }
}

void list_total_delay(Trips trips[], int num, char code_route[]){
    int t_delay = 0;
    for (int i = 0; i < num; ++i) {
        if(strcmp(trips[i].code_route,code_route)== 0){
            t_delay = t_delay + trips[i].delay;
            printf("%s %s %s %s %s %s %d\n", trips[i].code_route, trips[i].departure,
                   trips[i].destination, trips[i].date, trips[i].time_departure,
                   trips[i].time_arrival, trips[i].delay);
        }
    }
    printf("total delay is :%d\n",t_delay);
}
