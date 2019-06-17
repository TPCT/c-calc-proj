#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

/*Macros*/
#define NEXT *(line + i) // Gives the value of the i's pointer
#define CHUNCK_SIZE 10 // Array chunk size
/*Macros End*/

/* External Data types */
struct Arraydata{
    int StartIndex; // start index of array optional default = 0.
    int EndIndex; // end index of array Required.
    void * array; // pointer to the array must start from the first element of the array -> return_data = Array where Array is your Array
} Default_Array = {0};
typedef struct Arraydata Array;
/* External Data types End*/

/*Structs*/
Array atofl(char *);
Array NumbersSPLITTER(char *); // NumberSplitter function -> extracts integers and doubles from string
Array OperatorsSPLITTER(char *); // OperatorsSplitter function -> extracts operators {*, +, /, -} from mathematical expression
/*Structs end*/

/*Integers*/
int get_line(char **); //get_line function -> readline from input stream without specifying it's length
/*Integers End*/

/*Doubles*/
double pop(void); //pop function -> pops the last element of the array -> return it's value and deletes it {required in numbers array}
int push(double); // push function -> push specific value to the end of the array and return it's index {required in numbers array}
/*Doubles End*/

/*Voids*/
void strcopy(char *, char *);
/*Voids End*/



int main(void) {
    char *line;
    get_line(&line);
    return 0;
}

double push(void){}
double pop(void){}
Array OperatorsSPLITTER(char* line) {
    int i = 0, index = 0, maxsize = CHUNCK_SIZE;
    char temp_char;
    char *Output = (char *) calloc(maxsize, sizeof(double));
    while (NEXT != '\0') {
        if (i >= maxsize) {
            maxsize += CHUNCK_SIZE;
            char *temp_array = (char *) calloc(maxsize, sizeof(double));
            for (int j = 0; j < index; j++)
                *(temp_array + j) = *(Output + j);
            free(Output);
            Output = temp_array;
        }
        temp_char = NEXT;
        switch (temp_char) {
            case '+':
            case '-':
            case '*':
            case '/':
                i++;
                if (NEXT != ' ' && NEXT != '\t' && NEXT == '\0')
                    *(Output + index) = temp_char, index++;
                break;
            default:
                i++;
                break;
        }
    }
    Array return_data = {0, index, Output};
    return return_data;
}
Array NumbersSPLITTER(char* line){
    int counter = 1, index = 0, new_index = 0, maxsize = CHUNCK_SIZE;
    double* Output = (double*)calloc(maxsize, sizeof(double));
    while(new_index != -1){
        if (counter >= maxsize){
            maxsize += CHUNCK_SIZE;
            double* temp_array = (double*)calloc(maxsize, sizeof(double));
            for (int i = 0; i < counter; i++)
                *(temp_array + i) = *(Output + i);
            free(Output);
            Output = temp_array;
        }
        Array return_array = atofl(line + index);
        double *new_ptr = (double *)return_array.array;
        *(Output + maxsize - counter) = *(new_ptr);
        new_index = return_array.EndIndex;
        index += new_index;
        counter++;
    }
    Array return_array = {maxsize - counter + 1, maxsize, Output};
    return return_array;
}
Array atofl(char* line){
    /* this function returns the index of the next invalid digital value in string, and put the value in returnptr
     * 12254 15875887 -> double 12254.00000*/
    int i = 0;
    double number = 0.0, sign = 1.0, power = 1.0;
    for(i = 0;((NEXT != '\0' && !isdigit(NEXT)) && (NEXT == ' ' || NEXT == '\t')) && (NEXT != '+' && NEXT != '-'); i++);
    if (NEXT == '+') ++i;
    else if (NEXT == '-') sign = -1, ++i;
    while (isdigit(NEXT)){
        number = 10.0 * number  + (NEXT - '0');
        ++i;
    }
    if (NEXT == '.') ++i;
    while(isdigit(NEXT)){
        number = 10.0 * number + (NEXT - '0');
        power *= 10.0;
        ++i;
    }
    double value = sign * number / power;
    Array return_data = {0, 0, &value};
    return_data.EndIndex = NEXT == '\0' ? -1 : i;
    return return_data;
}
int get_line(char** line){
    int i = 0, max_length = CHUNCK_SIZE;
    char c;
    char *temp_line = (char *)calloc(max_length, sizeof(char));
    *(temp_line + max_length) = '\0';
    for(;(c = getchar()) != EOF; ++i){
        if (i >= max_length){
            max_length += 10;
            char* new_line = (char*)calloc(max_length, sizeof(char));
            strcopy(temp_line, new_line);
            free(temp_line);
            temp_line = new_line;
            *(temp_line + max_length) = '\0';
        }
        if (c != '\n')
            *(temp_line + i) = c;
        else
            break;
    }
    *line = temp_line;
    return c == EOF ? EOF : i;
}
void strcopy(char* from , char* to){
    int i;
    for (i = 0; *(from+i) != '\0'; ++i){
        *(to+i) = *(from+i);
    }
    *(to+i) = '\0';
}
