
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STRING_LENGTH 20
#define FILE_LOCATION "data.dat"

struct item_data {
    size_t name_size;
    char (*name)[STRING_LENGTH];
    char (*warehouse)[STRING_LENGTH];
    size_t warehouse_size;
    char (*location)[STRING_LENGTH];
    size_t location_size;
    int *quantity;
    size_t quantity_size;
    int *price;
    size_t price_size;
};

enum gui_options {
    LIST = 1,
    CREATE = 2,
    UPDATE = 3,
    DELETE = 4,
    SAVE = 5,
    QUIT = 6,
    ACCEPT = 1,
    REJECT = 0,
};

int save_data(struct item_data *data) {
    FILE *file = fopen(FILE_LOCATION, "wb");

    if (file == NULL) {
        perror("Error opening file to write");
        return 0;
    }

    // Writing names

    if (fwrite(&(data->name_size), sizeof(size_t), 1, file) != 1) {
        perror("Error writing no. of bytes for name array");
        fclose(file);
        return 0;
    }
    for (size_t i = 0; i < data->name_size; i++) {
        if (fwrite(data->name + i, sizeof(char) * STRING_LENGTH, 1, file) != 1) {
            perror("Error writing name data to array");
            fclose(file);
            return 0;
        }
    }

    // Writing warehouses 

    if (fwrite(&(data->warehouse_size), sizeof(size_t), 1, file) != 1) {
        perror("Error writing no. of bytes for warehouse array");
        fclose(file);
        return 0;
    }
    for (size_t i = 0; i < data->warehouse_size; i++) {
        if (fwrite(data->warehouse + i, sizeof(char) * STRING_LENGTH, 1, file) != 1) {
            perror("Error writing warehouse data to array");
            fclose(file);
            return 0;
        }
    }

    // Writing location 

    if (fwrite(&(data->location_size), sizeof(size_t), 1, file) != 1) {
        perror("Error writing no. of bytes for location array");
        fclose(file);
        return 0;
    }
    for (size_t i = 0; i < data->location_size; i++) {
        if (fwrite(data->location + i, sizeof(char) * STRING_LENGTH, 1, file) != 1) {
            perror("Error writing location data to array");
            fclose(file);
            return 0;
        }
    }

    // Write Quantity
    if (fwrite(&(data->quantity_size), sizeof(size_t), 1, file) != 1) {
        perror("Error writing no. of bytes for quantity array");
        fclose(file);
        return 0;
    }
    for (size_t i = 0; i < data->quantity_size; i++) {
        if (fwrite(data->quantity + i, sizeof(int), 1, file) != 1) {
            perror("Error writing quantity data");
            fclose(file);
            return 0;
        }
    }

    // Write price
    if (fwrite(&(data->price_size), sizeof(size_t), 1, file) != 1) {
        perror("Error writing no. of bytes for price array");
        fclose(file);
        return 0;
    }
    for (size_t i = 0; i < data->price_size; i++) {
        if (fwrite(data->price + i, sizeof(int), 1, file) != 1) {
            perror("Error writing price data");
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;

}

int read_data(struct item_data *data) {
    FILE *file = fopen(FILE_LOCATION, "rb");

    if (file == NULL) {
        perror("Error opening file to read");
        return 0;
    }


    // Read names
    if (fread(&(data->name_size), sizeof(size_t), 1, file) != 1) {
        perror("Error reading no. of bytes for name array");
        fclose(file);
        return 0;
    }
    // TODO: Rewrite function to read array
    data->name = calloc(data->name_size, sizeof(*data->name));
    for (size_t i = 0; i < data->name_size; i++) {
        if (fread(data->name + i, sizeof(char) * STRING_LENGTH, 1, file) != 1) {
            perror("Error reading name data");
            fclose(file);
            return 0;
        }
    }

    // Read warehouses
    if (fread(&(data->warehouse_size), sizeof(size_t), 1, file) != 1) {
        perror("Error reading no. of bytes for warehouse array");
        fclose(file);
        return 0;
    }
    data->warehouse = calloc(data->warehouse_size, STRING_LENGTH);
    for (size_t i = 0; i < data->warehouse_size; i++) {
        if (fread(data->warehouse + i, sizeof(char) * STRING_LENGTH, 1, file) != 1) {
            perror("Error reading warehouse data");
            fclose(file);
            return 0;
        }
    }

    // Read location
    if (fread(&(data->location_size), sizeof(size_t), 1, file) != 1) {
        perror("Error reading no. of bytes for location array");
        fclose(file);
        return 0;
    }
    data->location = calloc(data->location_size, STRING_LENGTH);
    for (size_t i = 0; i < data->location_size; i++) {
        if (fread(data->location + i, sizeof(char) * STRING_LENGTH, 1, file) != 1) {
            perror("Error reading location data");
            fclose(file);
            return 0;
        }
    }

    // Read quantity
    if (fread(&(data->quantity_size), sizeof(size_t), 1, file) != 1) {
        perror("Error reading no. of bytes for quantity array");
        fclose(file);
        return 0;
    }
    data->quantity = calloc(data->quantity_size, sizeof(int));
    for (size_t i = 0; i < data->quantity_size; i++) {
        if (fread(data->quantity + i, sizeof(int), 1, file) != 1) {
            perror("Error reading quantity data");
            fclose(file);
            return 0;
        }
    }

    // Read price
    if (fread(&(data->price_size), sizeof(size_t), 1, file) != 1) {
        perror("Error reading no. of bytes for price array");
        fclose(file);
        return 0;
    }
    data->price = calloc(data->price_size, sizeof(int));
    for (size_t i = 0; i < data->price_size; i++) {
        if (fread(data->price + i, sizeof(int), 1, file) != 1) {
            perror("Error reading price data");
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int add_data_to_struct(struct item_data *data, char name[STRING_LENGTH], char warehouse[STRING_LENGTH], char location[STRING_LENGTH], int quantity, int price) {

    data->name_size += 1;
    data->warehouse_size += 1;
    data->location_size += 1;
    data->quantity_size += 1;
    data->price_size += 1;

    // BUG: If realloc fails, pointer to original data is lost. Rewrite using a temp pointer first.
    data->name = realloc(data->name, data->name_size * STRING_LENGTH * sizeof(char));
    data->warehouse = realloc(data->warehouse, data->warehouse_size * STRING_LENGTH * sizeof(char));
    data->location = realloc(data->location, data->location_size * STRING_LENGTH * sizeof(char));
    data->quantity = realloc(data->quantity, data->quantity_size * sizeof(int));
    data->price = realloc(data->price, data->price_size * sizeof(int));

    if (data->name == NULL || data->warehouse == NULL || data->location == NULL || data->quantity == NULL || data->price == NULL) {
        data->name_size -= 1;
        data->warehouse_size -= 1;
        data->location_size -= 1;
        data->quantity_size -= 1;
        data->price_size -= 1;
        return 0;
    }

    // BUG: Use strncpy instead of strcpy to avoid buffer overflows
    strcpy(data->name[data->name_size - 1], name);
    strcpy(data->warehouse[data->warehouse_size - 1], warehouse);
    strcpy(data->location[data->location_size - 1], location);
    data->quantity[data->quantity_size - 1] = quantity;
    data->price[data->price_size - 1] = price;
    return 1;
}

void delete_data_from_struct(struct item_data *data, int index) {
    for (int i = index; i < (int) data->name_size - 1; i++) {
        // BUG: Checek if index within bounds
        strcpy(data->name[i],  data->name[i + 1]);
    }
    for (int i = index; i < (int) data->warehouse_size - 1; i++) {
        strcpy(data->warehouse[i],  data->warehouse[i + 1]);
    }
    for (int i = index; i < (int) data->location_size - 1; i++) {
        strcpy(data->location[i],  data->location[i + 1]);
    }
    for (int i = index; i < (int) data->quantity_size - 1; i++) {
        data->quantity[i] = data->quantity[i + 1];
    }
    for (int i = index; i < (int) data->price_size - 1; i++) {
        data->price[i] = data->price[i + 1];
    }
    data->name_size -= 1;
    data->warehouse_size -= 1;
    data->location_size -= 1;
    data->quantity_size -= 1;
    data->price_size -= 1;
}

void update_data_in_struct(struct item_data *data, int index, char name[STRING_LENGTH], char warehouse[STRING_LENGTH], char location[STRING_LENGTH], int quantity, int price) {
    strcpy(data->name[index], name);
    strcpy(data->warehouse[index], warehouse);
    strcpy(data->location[index], location);
    data->quantity[index] = quantity;
    data->price[index] = price;
}

void print_padded_string(char *data) {
    int length = (int) strlen(data) + 2;
    int padding = ((STRING_LENGTH - length) / 2);
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s", data);
    if (length + 2*padding < 20) {
        padding += 1;
    }
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
}

int countDigits(int n) {
    if (n == 0) return 1;
    return (n / 10 == 0) ? 1 : 1 + countDigits(n / 10);
}

void print_padded_integer(int n) {
    int length = countDigits(n) + 2;
    int padding = (STRING_LENGTH - length) / 2;
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%d", n);
    if (length + 2*padding < 20) {
        padding += 1;
    }
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
}

void list_struct(struct item_data *data) {

    int table_width = 5 * (STRING_LENGTH + 2);

    char headers[6][10] = {"INDEX", "NAME", "WAREHOUSE", "LOCATION", "QUANTITY", "PRICE"};

    printf("|");
    // table_width + 5 to include length of columns and -3 to remove already printed columns
    for (int i = 0; i < (table_width + 3); i++) {
        printf("-");
    }
    printf("|\n");

    for (int i = 0; i < 6; i++) {
        printf("|");
        print_padded_string(headers[i]);
    }
    printf("|\n");
    for (size_t i = 0; i < data->name_size; i++) {
        printf("|");
        print_padded_integer((int)(i + 1));
        printf("|");
        print_padded_string(data->name[i]);
        printf("|");
        print_padded_string(data->warehouse[i]);
        printf("|");
        print_padded_string(data->location[i]);
        printf("|");
        print_padded_integer(data->quantity[i]);
        printf("|");
        print_padded_integer(data->price[i]);
        printf("|\n");
    }
    printf("|");
    for (int i = 0; i < (table_width + 3); i++) {
        printf("-");
    }
    printf("|\n\n");
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void gui_create(struct item_data *data) {

    printf("\n\t[CREATE Entry]\n\n");

    char name[STRING_LENGTH], warehouse[STRING_LENGTH], location[STRING_LENGTH];
    int quantity;
    int price;

input:
    clearInputBuffer();
    // BUG: Add input validation
    printf("Enter Item Name: ");
    fgets(name, STRING_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter Warehouse: ");
    fgets(warehouse, STRING_LENGTH, stdin);
    warehouse[strcspn(warehouse, "\n")] = '\0';
    printf("Enter Location: ");
    fgets(location, STRING_LENGTH, stdin);
    location[strcspn(location, "\n")] = '\0';
    printf("Enter Item Quantity: ");
    scanf("%d", &quantity);
    printf("Price of Item: ");
    scanf("%d", &price);

    printf("\n\t[CONFIRM DATA]\n\n");

    printf("Name: %s\n", name);
    printf("Warehouse: %s\n", warehouse);
    printf("Location: %s\n", location);
    printf("Quantity: %d\n", quantity);
    printf("Price: %d\n", price);

    int choice;
    int result;
    printf("\nIs the data correct (1/0): ");
    scanf("%d", &choice);

    printf("\n");

    switch (choice) {
        case ACCEPT:
            result = add_data_to_struct(data, name, warehouse, location, quantity, price);
            if (result == 1) {
                printf("Data appended successfully !!\n\n");
            } else {
                printf("Not able to add data\n\n");
            }
            break;
        case REJECT:
            goto input;
    }
}

void gui_update(struct item_data *data) {

    printf("\n\t[UPDATE Entry]\n\n");

    int index;

    list_struct(data);

    printf("\n\nEnter the index of the entry to update: ");
    scanf("%d", &index);

    index--;

    char name[STRING_LENGTH], warehouse[STRING_LENGTH], location[STRING_LENGTH];
    int quantity;
    int price;

update:
    clearInputBuffer();
    // BUG: Add input validation
    printf("Enter Item Name: ");
    fgets(name, STRING_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter Warehouse: ");
    fgets(warehouse, STRING_LENGTH, stdin);
    warehouse[strcspn(warehouse, "\n")] = '\0';
    printf("Enter Location: ");
    fgets(location, STRING_LENGTH, stdin);
    location[strcspn(location, "\n")] = '\0';
    printf("Enter Item Quantity: ");
    scanf("%d", &quantity);
    printf("Price of Item: ");
    scanf("%d", &price);

    printf("\n\t[CONFIRM DATA]\n\n");

    printf("Name: %s\n", name);
    printf("Warehouse: %s\n", warehouse);
    printf("Location: %s\n", location);
    printf("Quantity: %d\n", quantity);
    printf("Price: %d\n", price);

    int choice;
    printf("\nIs the data correct (1/0): ");
    scanf("%d", &choice);

    printf("\n");

    switch (choice) {
        case ACCEPT:
            update_data_in_struct(data, index, name, warehouse, location, quantity, price);
            break;
        case REJECT:
            goto update;
    }

}

void gui_delete(struct item_data *data) {

    printf("\n\t[DELETE Entry]\n\n");

    int index;

    list_struct(data);

    printf("\n\nEnter the index of the entry to delete: ");
    scanf("%d", &index);

    index--;

    delete_data_from_struct(data, index);

    printf("Successfully Deleted!!!\n\n");
}

int main(void) {

    struct item_data data;

    if (access(FILE_LOCATION, F_OK) == 0) {
        read_data(&data);
    } else {
        data.name_size = 0;
        data.warehouse_size = 0;
        data.location_size = 0;
        data.quantity_size = 0;
        data.price_size = 0;
        data.name = NULL;
        data.warehouse = NULL;
        data.location = NULL;
        data.quantity = NULL;
        data.price = NULL;
    }

    printf("\n");

    while (1) {
        int choice;
        printf("\t-[CHOICES]-\n\n");
        printf("\t1. List inventory data\n");
        printf("\t2. Create entry\n");
        printf("\t3. Update entry\n");
        printf("\t4. Delete entry\n");
        printf("\t5. Save entries\n");
        printf("\t6. Quit\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case LIST:
                printf("\n\t[SELECTED OPTION: LIST]\n\n");
                list_struct(&data);
                break;
            case CREATE:
                printf("\n\t[SELECTED OPTION: CREATE]\n\n");
                gui_create(&data);
                break;
            case UPDATE:
                printf("\n\t[SELECTED OPTION: UPDATE]\n\n");
                gui_update(&data);
                break;
            case DELETE:
                printf("\n\t[SELECTED OPTION: DELETE]\n\n");
                gui_delete(&data);
                break;
            case SAVE:
                printf("\n\t[SELECTED OPTION: SAVE]\n\n");
                save_data(&data);
                break;
            case QUIT:
                free(data.name);
                free(data.warehouse);
                free(data.location);
                free(data.quantity);
                free(data.price);
                return 0;
            default:
                printf("\n\t[SELECTED OPTION: INVALID CHOICE]\n\n");
        }
    }
}
