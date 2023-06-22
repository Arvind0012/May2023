// # Date String to Structure conversion
// * In a application, the date is stored as a string and for computations, converting the string to number is required.
// * Write a function to convert the string formated date to a structure as per the below code
// * Return appropriate error values if the conversion is not successful

// ## Inptu string format
// ```
//     DD/MM/YYYY
// ```

// ## Output Structure format
// ```
// typedef struct my_date_t
// {
//     uint8_t date;       /*<<< date */
//     uint8_t month;      /*<<< month */
//     uint16_t year;      /*<<< year   */
// }my_date_t;
// ```

// ### Conversion status 
// ```
// typedef enum status_t
// {
//     SUCCESS,                    /**< Function has successfully converted the string to structure */
//     NULL_PTR,                   /**< Function is given NULL pointers to work with */
//     INCORRECT                   /**< Incorrect values for date or month or year */
// }status_t;


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct my_date_t {
    uint8_t date;   // Day
    uint8_t month;  // Month
    uint16_t year;  // Year
} my_date_t;

typedef enum status_t {
    SUCCESS,
    NULL_PTR,
    INCORRECT
} status_t;

status_t str_to_date_converter(char* input_string, my_date_t* result_date) {
    if (input_string == NULL || result_date == NULL) {
        return NULL_PTR;
    }

    size_t input_length = strlen(input_string);
    if (input_length != 10 || input_string[2] != '/' || input_string[5] != '/') {
        return INCORRECT;
    }

    // Extract day, month, and year
    char day_str[3];
    char month_str[3];
    char year_str[5];
    day_str[0] = input_string[0];
    day_str[1] = input_string[1];
    day_str[2] = '\0';
    month_str[0] = input_string[3];
    month_str[1] = input_string[4];
    month_str[2] = '\0';
    year_str[0] = input_string[6];
    year_str[1] = input_string[7];
    year_str[2] = input_string[8];
    year_str[3] = input_string[9];

    // Converting day, month, and year strings to integers using atoi function
    int day = atoi(day_str);
    int month = atoi(month_str);
    int year = atoi(year_str);

    // Check if converted values are valid
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
        return INCORRECT;
    }

    result_date->date = (uint8_t)day;
    result_date->month = (uint8_t)month;
    result_date->year = (uint16_t)year;

    return SUCCESS;
}

int main() {
    char input_string[] = "25/06/2023";  
    my_date_t result_date;                
    status_t conversion_status;           

    // Convert the input string to the result_date structure
    conversion_status = str_to_date_converter(input_string, &result_date);

    // Check the conversion status
    if (conversion_status == SUCCESS) {
        printf("Conversion successful:\n");
        printf("Day: %d\n", result_date.date);
        printf("Month: %d\n", result_date.month);
        printf("Year: %d\n", result_date.year);
    } else if (conversion_status == NULL_PTR) {
        printf("Error: NULL pointer given.\n");
    } else if (conversion_status == INCORRECT) {
        printf("Error: Incorrect date format or values.\n");
    }

    return 0;
}