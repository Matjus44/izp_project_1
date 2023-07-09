#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int print_full_list();
bool is_input_valid(char *argument); // declaration of functions.
int find_contacts(char *input);
void remove_enter(char *name);

char *number_as_chars[] = // I created 2D array into which I placed characters of numbers.
    {
        "+",
        "-",
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz"
    };

int main(int argc, char *argv[])
{
    if (argv == NULL || argc < 1 || argc > 2) // if the amount of argument is higher then 2 or lower then 1 or argument vector equals to null, then we execute the program and print on screen "invalid argument".
    {
        printf("invalid argument");
        return 1;
    }

    if (argc == 1) // if there is only one argument, then print whole file.
    {
        if (print_full_list() == 1) // call function "printf_full_list"
        {
            printf("invalid data");
            return 1;
        }
    }

    if (argc == 2) // There is 1 argument from user (and one argument which is program name)
    {
        char *input = argv[1];
        if (is_input_valid(input) == false) // call function "is_input_valid"
        {
            printf("invalid characters in argument"); // if function "is_input_valid" is false, then print "invalid characters in argument"
            return 1;
        }
        find_contacts(input); // if input is valid and argc is equal to 2 then call function "find_contacts"
    }

    return 0;
}

int print_full_list()
{
    char name[102];
    char number[102];
    while (fgets(name, sizeof name, stdin) != NULL) // we get first line of file which is name.
    {
        fgets(number, sizeof number, stdin);
        if (strlen(name) > 100 || strlen(number) > 100) // if lenght of name or lenght of number is longer then 100 characters, then execute the program, and printf to terminal"invalid data".
        {
            return 1;
        }
        remove_enter(name); // we call function "remove enter"
        printf("%s, %s", name, number);
    }
    return 0;
}

bool is_input_valid(char *argument) // we check if input is valid
{
    if ((argument[0] < '0' || argument[0] > '9') && argument[0] != '+') // if character in input on first place is different from numbers 0 to 9 and different from "+", then return false.
    {
        return false;
    }
    for (size_t i = 1; i < strlen(argument); i++) // we check rest of the characters in input if they are different from numbers.
    {
        if (argument[i] < '0' || argument[i] > '9')
        {
            return false;
        }
    }
    return true; // if characters in input are all numbers, then return true.
}

bool compare_numbers(char *number, char *input, size_t index)
{
    for (size_t j = 0; j < strlen(input); j++) // we loop through input.
    {
        if (input[j] != number[index + j]) // if we find that input differs at any number, we return false.
        {
            return false;
        }
    }
    return true; // if we find that numbers in input are taking same place in number in correct order then we return true.
}

bool find_by_number(char *number, char *input) // in this fucntion I am goin to compare input and number.
{
    int count = (strlen(number) - 1) - (strlen(input) - 1);
    for (int i = 0; i <= count; i++) // looping trough number untill we reach "count" which says that the input can no longer fit into number
    {
        if (compare_numbers(number, input, (size_t)i)) // we call function "compare_numbers"
        {
            return true; // if this function was succesfull, then we return true.
        }
    }
    return false; // if we did not find number match of input and data, then we return false.
}

bool is_element_in_array(char element, char *array)
{
    for (size_t i = 0; i < strlen(array); i++) // we loop trough characters in array which represent number in input and we check if they match with character in name
    {
        if (array[i] == element)
        {
            return true; // if character in array match with letter in name, then return true.
        }
    }
    return false; // otherwise return false.
}

bool compare_strings(char *name, char *input, size_t index)
{
    for (size_t i = 0; i < strlen(input); i++)
    {
        char current_number_from_input = input[i];          // this represents current number in input
        int index_of_keys = (int)current_number_from_input - 48;
        char *keys = number_as_chars[index_of_keys];        // we take first number from input and find its letters.

        char current_letter_from_name = name[index + i];    //for each match of letters, increase index + 1.

        if (is_element_in_array(current_letter_from_name, keys) == false) // calling function "is_element_in_array"
        {
            return false;   // if element is not in array, then return false.
        }
    }

    return true;
}

bool find_by_name(char *name, char *input)
{
    int counter = (strlen(name) - 1) - (strlen(input) - 1); // we loop untill the the lenght of input still fits in name.
    for (int i = 0; i <= counter; i++)
    {
        if (compare_strings(name, input, (size_t)i)) // calling function "compare_strings"
        {
            return true;    //if characters which represent numbers in input are in name, then return true.
        }
    }
    return false;   //otherwise return false.
}

void remove_enter(char *name) // in this function we replace (\n) with (\0)
{
    for (size_t i = 0; i < strlen(name); i++) // we loop trough name until the end of lenght.
    {
        if (name[i] == '\n') // if we find there (\n), then we replace it with (\0).
        {
            name[i] = '\0';
        }
    }
}

char *str_tolower(char *name) // this function changes all characters in array to lower case.
{
    size_t x = strlen(name) - 1;    // (size_t x) is lenght of array
    for (size_t i = 0; i <= x; i++) // we loop trough name.
    {
        name[i] = tolower(name[i]); // every character in position[i] replace with the same character but in lower case.
    }
    return name; // return name in lower case.
}

int find_contacts(char *input)
{
    if (input == NULL) // first we check if input is equal to NULL.
    {
        return 1;
    }

    char name[102]; // we create 3 variabiles to store name, number and amount of found contacts.
    char number[102];
    size_t found_contacts = 0;

    while (fgets(name, sizeof name, stdin) != NULL) // we get first line of file which is name.
    {
        fgets(number, sizeof number, stdin); // we get second line of file which is a number.

        if (strlen(name) > 100 || strlen(number) > 100) // if lenght of name or lenght of number is longer then 100 characters, then execute the program, and printf to terminal"invalid data".
        {
            printf("invalid data");
            return 1;
        }
        if (find_by_number(number, input)) // if lenght of datas is alright, then we can call function "find_by_number".
        {
            remove_enter(name);             // we call function "remove enter"
            printf("%s, %s", name, number); // printf the list of numbers which consist the same numbers as in input in correct order. Also to each number add name which is bounded to it.
            found_contacts++;               // for each correct number u find, increase "found_contacts" + 1.
        }
        else if (find_by_name((str_tolower(name)), input)) // if we didnt find contact by number, we also look for contacts by name, we call function "find_by_name".
        {
            remove_enter(name);             // we again call function "remove_enter", which I already explained above.
            printf("%s, %s", name, number); // again we printf name and its connected number.
            found_contacts++;               // increase found contacts by one.
        }
    }

    if (found_contacts == 0) // if amount of found contacts is equal to 0, then it means we didnt find any contact so we print into terminal "not found".
    {
        printf("not found");
    }

    return 0;
}
