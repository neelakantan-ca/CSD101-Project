
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
    data->name = calloc(data->name_size, STRING_LENGTH);
    for (size_t i = 0; i < data->name_size; i++) {
        if (fread(data->name + i, sizeof(char) * STRING_LENGTH, 1, file) != 1) {
            perror("Error reading name data"); fclose(file);
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
            perror("Error reading warehouse data"); fclose(file);
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

    strcpy(data->name[data->name_size - 1], name);
    strcpy(data->warehouse[data->warehouse_size - 1], warehouse);
    strcpy(data->location[data->location_size - 1], location);
    data->quantity[data->quantity_size - 1] = quantity;
    data->price[data->price_size - 1] = price;
    return 1;
}

void delete_data_from_struct(struct item_data *data, int index) {
    for (int i = index; i < (int) data->name_size - 1; i++) {
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

    printf("|");
    // table_width + 5 to include length of columns and -3 to remove already printed columns
    for (int i = 0; i < (table_width + 3); i++) {
        printf("-");
    }
    printf("|\n");

    printf("|");
    print_padded_string("INDEX");
    printf("|");
    print_padded_string("NAME");
    printf("|");
    print_padded_string("WAREHOUSE");
    printf("|");
    print_padded_string("LOCATION");
    printf("|");
    print_padded_string("QUANTITY");
    printf("|");
    print_padded_string("PRICE");
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
    printf("|\n");
}

int main(int argc, char *argv[]) {

    struct item_data data;

    // Check if data.dat exists previously, if so load into memory
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

    // Run main program


    // Save data, free memory and exit program
    save_data(&data);
    free(data.name);
    free(data.warehouse);
    free(data.location);
    free(data.quantity);
    free(data.price);
    return 0;
}


// size_t count = 5; // Number of strings we want to store
//
// // Create the structure
// struct item_data data;
// data.name_size = count;
// data.warehouse_size = count;
// data.location_size = count;
// data.quantity_size = count;
// data.price_size = count;
//
// // Dynamically allocate memory for the array of strings
// data.name = malloc(count * STRING_LENGTH * sizeof(char));
// data.warehouse = malloc(count * STRING_LENGTH * sizeof(char));
// data.location = malloc(count * STRING_LENGTH * sizeof(char));
// data.quantity = malloc(count * sizeof(int));
// data.price = malloc(count * sizeof(int));
// if (!data.name) {
//     perror("Failed to allocate memory");
//     return 1;
// }
//
// // Initialize the strings
// strncpy(data.name[0], "Hello", STRING_LENGTH);
// strncpy(data.name[1], "World", STRING_LENGTH);
// strncpy(data.name[2], "Example", STRING_LENGTH);
// strncpy(data.name[3], "Dynamic", STRING_LENGTH);
// strncpy(data.name[4], "Strings", STRING_LENGTH);
//
// // Initialize warehouse
// strncpy(data.warehouse[0], "Hello", STRING_LENGTH);
// strncpy(data.warehouse[1], "World", STRING_LENGTH);
// strncpy(data.warehouse[2], "Example", STRING_LENGTH);
// strncpy(data.warehouse[3], "Dynamic", STRING_LENGTH);
// strncpy(data.warehouse[4], "Strings", STRING_LENGTH);
//
// // Initialize location
// strncpy(data.location[0], "Hello", STRING_LENGTH);
// strncpy(data.location[1], "World", STRING_LENGTH);
// strncpy(data.location[2], "Example", STRING_LENGTH);
// strncpy(data.location[3], "Dynamic", STRING_LENGTH);
// strncpy(data.location[4], "Strings", STRING_LENGTH);
//
// // Initialize quantity
// for (int i = 0; i < 5; i++) {
//     data.quantity[i] = i;
// }
//
// // Initialize quantity
// for (int i = 0; i < 5; i++) {
//     data.price[i] = (int)i;
// }
//
// char name[20] = "Test name";
// char warehouse[20] = "Test name";
// char location[20] = "Test name";
//
// add_data_to_struct(&data, name, warehouse, location, 5, 14.5);
// delete_data_from_struct(&data, 2);
//
// save_data(&data);
// struct item_data data_read;
// read_data(&data_read);
//
// // Free the allocated memory
// free(data.name);
