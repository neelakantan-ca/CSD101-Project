
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LENGTH 20

struct item_data {
    size_t name_size;
    char (*name)[20];
    // char *warehouse[ARRAY_SIZE];
    // size_t warehouse_size;
    // char *location[ARRAY_SIZE];
    // size_t location_size;
    // int *quantity;
    // size_t quantity_size;
    // int *price;
    // size_t price_size;
};

void save_data(struct item_data *data) {
    FILE *file = fopen("data.dat", "wb");

    if (file == NULL) {
        perror("Error opening file to write");
        return;
    }

    printf("Writing number of names: %zu\n", data->name_size);
    if (fwrite(&(data->name_size), sizeof(size_t), 1, file) != 1) {
        perror("Error writing no. of bytes for name array");
        fclose(file);
        return;
    }
    for (size_t i = 0; i < data->name_size; i++) {
        int status = fwrite(data->name + i, sizeof(char) * STRING_LENGTH, 1, file);
        // printf("Write status: %d\n", status);
        if (status != 1) {
            perror("Error writing name data to array");
            fclose(file);
            return;
        }
    }

    fclose(file);

}

void read_data(struct item_data *data) {
    FILE *file = fopen("data.dat", "rb");

    if (file == NULL) {
        perror("Error opening file to read");
        return;
    }


    if (fread(&(data->name_size), sizeof(size_t), 1, file) != 1) {
        perror("Error reading no. of bytes for name array");
        fclose(file);
        return;
    }

    char *name = calloc(data->name_size, STRING_LENGTH);

    for (size_t i = 0; i < data->name_size; i++) {
        if (fread(name + i, sizeof(char) * STRING_LENGTH, 1, file) != 1) {
            perror("Error reading name data"); fclose(file);
            return;
        }
        printf("Read names: %s\n", name + i);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {

    size_t count = 5; // Number of strings we want to store

    // Create the structure
    struct item_data data;
    data.name_size = count;

    // Dynamically allocate memory for the array of strings
    data.name = malloc(count * STRING_LENGTH);
    if (!data.name) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Initialize the strings
    strncpy(data.name[0], "Hello", STRING_LENGTH);
    strncpy(data.name[1], "World", STRING_LENGTH);
    strncpy(data.name[2], "Example", STRING_LENGTH);
    strncpy(data.name[3], "Dynamic", STRING_LENGTH);
    strncpy(data.name[4], "Strings", STRING_LENGTH);

    save_data(&data);
    read_data(&data);

    // Free the allocated memory
    free(data.name);

}
