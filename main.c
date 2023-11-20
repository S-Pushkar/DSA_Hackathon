#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct driver {
    char name[20];
    char car[20];
    int isAvailable;
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

allDrivers *driverList = NULL;
allPassengers *passList = NULL;

allDrivers* driverExists(driver d) {
    allDrivers *tmp = driverList;

    while (tmp != NULL) {
        int cmp = strcmp((tmp -> curr).car, d.car);
        if (cmp == 0) {
            return tmp;
        }

        tmp = tmp -> next;
    }
    
    return NULL;
}

int main() {
    int flag = 1;
    while(flag) {
        printf("Are you a driver or a passenger?\n");
        printf("Press 1 for driver.\n");
        printf("Press 2 for passenger.\n");
        printf("Press q to quit.\n");
        
        char isDriver;
        scanf("%c", isDriver);

        switch(isDriver) {
            case '1':
                driver cur;
                printf("Enter your name (less than 20 characters): ");
                scanf("%s", cur.name);

                printf("Enter your car number: ");
                scanf("%s", cur.car);

                allDrivers *t = driverExists(cur);
                if (t != NULL) {
                    int isAvail = (t -> curr).isAvailable;
                    if (isAvail) {
                        printf("We are looking for passengers. Hold on!\n");
                        break;
                    }

                    // Check for bill or something
                } else {
                    addPerson();
                }
                break;

            case '2':

                break;

            case 'q':
                printf("Sayonara!!\n");
                flag = 0;
                break;

            default: 
                printf("Invalid input.\n");
                break;
        }
    }
    return 0;
}