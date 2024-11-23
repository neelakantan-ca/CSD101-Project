#include <stdio.h>

#define STRING_LENGTH 20

enum gui_options {
    LIST = 1,
    CREATE = 2,
    UPDATE = 3,
    DELETE = 4,
    SAVE = 5,
    ACCEPT = 1,
    REJECT = 0,
};

void gui_create() {

    printf("\n\t[CREATE Entry]\n\n");

    char name[STRING_LENGTH], warehouse[STRING_LENGTH], location[STRING_LENGTH];
    int quantity;
    float price;

input:

    printf("Enter Item Name: ");
    scanf("%s", name);  
    printf("Enter Warehouse: ");
    scanf("%s", warehouse);  
    printf("Enter Location: ");
    scanf("%s", location);  
    printf("Enter Item Quantity: ");
    scanf("%d", &quantity);
    printf("Price of Item: ");
    scanf("%f", &price);
    
    printf("\n\t[CONFIRM DATA]\n");

    printf("Name: %s\n", name);
    printf("Warehouse: %s\n", warehouse);
    printf("Location: %s\n", location);
    printf("Quantity: %d\n", quantity);
    printf("Price: %f\n", price);

    int choice;
    printf("\nIs the data correct (1/0): ");
    scanf("%d", &choice);

    switch (choice) {
        case ACCEPT:
            // Call function to add data to struct
            break;
        case REJECT:
            goto input;
    }
}

int main() {

    printf("\n");

    while (1) {
        int choice;
        printf("\t-[CHOICES]-\n\n");
        printf("\t1. List inventory data\n");
        printf("\t2. Create entry\n");
        printf("\t3. Update entry\n");
        printf("\t4. Delete entry\n");
        printf("\t5. Save entries\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case LIST:
                printf("\n\t[SELECTED OPTION: LIST]\n\n");
                break;
            case CREATE:
                printf("\n\t[SELECTED OPTION: CREATE]\n\n");
                break;
            case UPDATE:
                printf("\n\t[SELECTED OPTION: UPDATE]\n\n");
                break;
            case DELETE:
                printf("\n\t[SELECTED OPTION: DELETE]\n\n");
                break;
            case SAVE:
                printf("\n\t[SELECTED OPTION: SAVE]\n\n");
                break;
            default:
                printf("\n\t[SELECTED OPTION: INVALID CHOICE]\n\n");
        }
    }

    return 0;  
}
