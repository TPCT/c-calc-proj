#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <limits.h>
#include <ctype.h>

#define Maxline_Length 256
#define NEXT *(line + i)


void strcopy(char *, char *);
int atofi(char *, double *);
int NumbersSPLITTER(char *, double**);
int OperatorsSPLITTER(char *, char**);
int getline(char **);

int main(void) {
    char* line = "11 22 44 55 63.1 54885 88745 96.25 36.5575458 + + - -";
    char* Output;
    int data = OperatorsSPLITTER(line, &Output);
    for (int i = 0; i < 10; i++){
        printf("%c\n", *(Output+i));
    }
}

double calculate(char *line){
    double sum = 0.0;

}
int OperatorsSPLITTER(char* line, char** array) {
    int i = 0, index = 0, maxsize = 10;
    char temp_char;
    char *Output = (char *) calloc(maxsize, sizeof(double));
    while (NEXT != '\0') {
        if (i >= maxsize) {
            maxsize += i;
            char *temp_array = (char *) calloc(maxsize, sizeof(double));
            for (int j = 0; j < index; j++)
                *(temp_array + j) = *(Output + j);
            free(Output);
            Output = temp_array;
        }
        temp_char = NEXT;
        switch (NEXT) {
            case '+':
            case '-':
            case '*':
            case '/':
                i++;
                if (!isdigit(NEXT))
                    *(Output + index) = temp_char, index++;
                else if (NEXT == '\n')
                break;
            default:
                i++;
                break;
        }
    }
    *array = Output;
    return index;
}
int NumbersSPLITTER(char* line, double** array){
    int counter = 1, index = 0, new_index = 0, maxsize = 10;
    double* Output = (double*) calloc(maxsize, sizeof(double));
    while(new_index != -1){
        if (counter >= maxsize){
            maxsize += counter;
            double* temp_array = (double*)calloc(maxsize, sizeof(double));
            for (int i = 0; i < counter; i++)
                *(temp_array + i) = *(Output + i);
            free(Output);
            Output = temp_array;
        }
        new_index = atofi(line+index, Output + maxsize - counter);
        index += new_index;
        counter++;
    }
    *array = Output;
    return counter;
}
int atofi(char* line, double* returnptr){
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
    *returnptr = sign * number / power;
    if (NEXT == '\0')
        return -1;
    return i;
}
int get_line(char** line){
    int i = 0, max_length;
    char c;
    *line = (char *)calloc(Maxline_Length, sizeof(char));
    *(*line + Maxline_Length) = '\0';
    for(;(c = getchar()) != EOF; ++i){
        if (i == Maxline_Length){
            max_length += i;
            char* new_line = (char*)calloc(max_length, sizeof(char));
            strcopy(*line, new_line);
            free(*line);
            *line = new_line;
            *(*line + max_length) = '\0';
        }
        if (c != '\n')
            *(*line + i) = c;
        else
            break;
    }
    return c == EOF ? EOF : i;
}
void strcopy(char* from , char* to){
    int i;
    for (i = 0; *(from+i) != '\0'; ++i){
        *(to+i) = *(from+i);
    }
    *(to+i) = '\0';
}
