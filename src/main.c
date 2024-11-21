#include <stdio.h>
#define STRING_LENGTH 20
int create(char name[STRING_LENGTH], char warehouse[STRING_LENGTH], char location[STRING_LENGTH], int quantity, float price) {
    // Simulated creation function
    return 0; // For now,returning 0 as a placeholder
}
int gui_user_input_print_confirm(char iname[STRING_LENGTH], char wh[STRING_LENGTH], char loc[STRING_LENGTH], int iquant, float iprice) {
    char confirm;
    int k;
    //Printing of Items for user confirmation
    printf("Item name: %s \n", iname);
    printf("Item quantity: %d \n", iquant);
    printf("Warehouse: %s \n", wh);
    printf("Location: %s \n", loc);
    printf("Price: %f \n", iprice);
    
    printf("Press Y to confirm, Press N to cancel: ");
    scanf(" %c", &confirm);  
    //If confirmed,create function gets called
    if (confirm == 'Y' || confirm == 'y') {
        k = create(iname, wh, loc, iquant, iprice);
        //Confirmation message for Data Saving
        if (k == 0) {
            printf("Error Saving Data in File!\n");
        } else if (k == 1) {
            printf("Data Saved Successfully!\n");
        }
    } else if (confirm == 'N' || confirm == 'n') {
        return 0;
    } else {
        printf("Invalid Confirmation! Please try again.\n");
    }
    return 1;
}
int main() {
    char item_name[STRING_LENGTH], whouse[STRING_LENGTH], locat[STRING_LENGTH];
    int item_quant;
    float item_price;
//user input
    printf("Enter Item Name: ");
    scanf("%s", item_name);  
    printf("Enter Item Quantity: ");
    scanf("%d", &item_quant);
    printf("Enter Warehouse: ");
    scanf("%s", whouse);  
    printf("Enter Location: ");
    scanf("%s", locat);  
    printf("Price of Item: ");
    scanf("%f", &item_price);
    // Call the function to print the items and confirm if they are correct as per the user requirements
    gui_user_input_print_confirm(item_name, whouse, locat, item_quant, item_price);
    return 0;  
}
