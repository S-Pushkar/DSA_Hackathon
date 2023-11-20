#include <stdio.h>

typedef struct driver {
    char name[20];
    char car[20];
    int available;
    int latitude;
    int longitude;
} driver;

typedef struct allDrivers {
    driver curr;
    struct allDrivers* next;
} allDrivers;

typedef struct passenger {
    char name[20];
    int latitude;
    int longitude;
} passenger;

typedef struct allPassengers {
    passenger curr;
    struct allPassengers* next;
} allPassengers;

int main() {
    while(1) {
        printf("Are you a driver or a passenger?\n");
        printf("Press 1 for driver.\n");
        printf("Press 2 for passenger.\n");
        int 
    }
    return 0;
}