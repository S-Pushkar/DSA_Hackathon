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
    driver curDr;
    struct allDrivers* next;
} allDrivers;

typedef struct passenger {
    char name[20];
    int latitude;
    int longitude;
    long long phone;
} passenger;

typedef struct allPassengers {
    passenger curDr;
    struct allPassengers* next;
} allPassengers;

allDrivers *driverList = NULL;
allPassengers *passList = NULL;

allDrivers* driverExists(driver d) {
    allDrivers *tmp = driverList;

    while (tmp != NULL) {
        int cmp = strcmp((tmp -> curDr).car, d.car);
        if (cmp == 0) {
            return tmp;
        }

        tmp = tmp -> next;
    }
    
    return NULL;
}

int passExists(passenger d) {
    allPassengers *tmp = passList;

    while (tmp != NULL) {
        if ((tmp -> curDr).phone == d.phone) {
            return 1;
        }

        tmp = tmp -> next;
    }
    
    return 0;
}

void deletePassenger(passenger curP) {
    allPassengers *cur = passList;
    allPassengers *prev = NULL;

    while (cur != NULL) {
        if ((cur -> curDr).phone == curP.phone) {
            prev -> next = cur -> next;
            break;
        }

        cur = cur -> next;
        prev = prev -> next;
    }   
}

void addDriver(driver d) {  
    allDrivers *node = (allDrivers*) malloc(sizeof(allDrivers));    
    node -> curDr = d;
    node -> next = NULL;

    allDrivers *tail = driverList;
    while (tail != NULL && tail -> next != NULL) {
        tail = tail -> next;
    } 

    tail -> next = node;
}

void addPassenger(passenger p) {
    allPassengers *node = (allPassengers*) malloc(sizeof(allPassengers));    
    node -> curDr = p;
    node -> next = NULL;

    allPassengers *tail = passList;
    while (tail != NULL && tail -> next != NULL) {
        tail = tail -> next;
    } 

    tail -> next = node;
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
                driver curD;
                printf("Enter your name (less than 20 characters): ");
                scanf("%s", curD.name);

                printf("Enter your car number: ");
                scanf("%s", curD.car);

                allDrivers *t = driverExists(curD);
                if (t != NULL) {
                    int isAvail = (t -> curDr).isAvailable;
                    if (isAvail) {
                        printf("We are looking for passengers. Hold on!\n");
                        break;
                    }

                    // Check for bill or something

                } else {
                    addDriver(curD);
                }
                break;

            case '2':
                passenger curP;
                printf("Enter your name: ");
                scanf("%s", curP.name);

                printf("Enter your latitude: ");
                scanf("%d", curP.latitude);

                printf("Enter your longitude: ");
                scanf("%d", curP.longitude);

                // Check if the passenger exists
                int exist = passExists(curP);
                if (exist) {
                    printf("We are still working to find drivers for the ride. Please wait.\n");
                    printf("Enter 0 to wait.\nEnter 1 to cancel.\n");
                    int cancel = 0;
                    scanf("%d", &cancel);

                    if (cancel) {
                        deletePassenger(curP);
                    }
                } else {
                    addPassenger(curP);
                }
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