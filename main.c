#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

    if (driverList == NULL) {
        driverList = node;
        return;
    }

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

    if (passList == NULL) {
        passList = node;
        return;
    }

    allPassengers *tail = passList;
    while (tail != NULL && tail -> next != NULL) {
        tail = tail -> next;
    } 

    tail -> next = node;
}

float generateBill(int curLati, int curLongi, int destLati, int destLongi) {
    float base = 50.12421;
    float bill = base + sqrt((curLati - destLati) * (curLati - destLati) + (curLongi - destLongi) * (curLongi - destLongi)) * 10;
    return bill;
}

int main() {
    int flag = 1;
    while(flag) {
        printf("Are you a driver or a passenger?\n");
        printf("Press 1 for driver.\n");
        printf("Press 2 for passenger.\n");
        printf("Press any other number to quit.\n");
        
        int isDriver;
        scanf("%d\n", &isDriver);

        if (isDriver != 1 && isDriver != 2) {
            printf("Shutting down the service...\n");
            break;
        }

        switch(isDriver) {
            case 1:
                driver curD;
                printf("Enter your name (less than 20 characters): ");
                scanf("%s", &curD.name[0]);

                printf("Enter your car number: ");
                scanf("%s", &curD.car[0]);

                allDrivers *t = driverExists(curD);
                if (t != NULL) {
                    int isAvail = (t -> curDr).isAvailable;
                    if (isAvail) {
                        printf("We are looking for passengers. Hold on!\n");
                        break;
                    }

                    // Check for bill or something
                    printf("Type 1 to confirm ride complete.\n");
                    int endRide = 0;
                    scanf("%d", &endRide); 

                    if (endRide != 1) {
                        printf("Continue to ride...\n");
                        break;
                    } 

                    int destLatitude, destLongitude;

                    printf("Ending ride...\n");
                    printf("Enter your current latitude: ");
                    scanf("%d", &destLatitude);

                    printf("Enter your current longitude: ");
                    scanf("%d", &destLongitude);

                    printf("Generating bill...\n");
                    printf("From: \n");
                    printf("Latitude: %d\n", (t -> curDr).latitude);
                    printf("Longitude: %d\n", (t -> curDr).longitude);
                    printf("To: \n");
                    printf("Latitude: %d\n", destLatitude);
                    printf("Longitude: %d\n", destLongitude);

                    float bill = generateBill((t -> curDr).latitude, (t -> curDr).longitude, destLatitude, destLongitude);
                    printf("Bill is %f\n", bill);

                    printf("You are now available for new rides.\n");
                    (t -> curDr).isAvailable = 1;
                } else {
                    addDriver(curD);
                }
                break;

            case 2:
                passenger curP;
                printf("Enter your name: ");
                scanf("%s", &curP.name[0]);

                printf("Enter your latitude: ");
                scanf("%d", &curP.latitude);

                printf("Enter your longitude: ");
                scanf("%d", &curP.longitude);

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

            default: 
                printf("Shutting down the service...\n");
                flag = 0;
                break;
        }
    }
    return 0;
}