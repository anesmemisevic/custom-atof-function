//
//  main.c
//  Homework1
//
//  Created by Anes Memišević on 11. 4. 2021..
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 250

float myAtof(char *string, char *error);

int main()
{
    char string[SIZE];            // Array declaration.
    float fnum1 = 0;
    float fnum2 = 0;
    float fnum3 = 0;
    char errorState = 0;
    char errorState2 = 0;
    char lefthandside[SIZE];
    char righthandside[SIZE];
    char sign = 0;
    int operatorCounter = 0;
    
    printf("Enter arithmetic operation:\n");
    gets(string);
    
    //checking if there is more than one operator
    int i = 0;
    for (; string[i] != '\0'; i++) {
        if (string[i] == '-' || string[i] == '+' || string[i] == '*' || string[i] == '/')
            operatorCounter++;
    }
    
    
    int left_len = 0;
    i = 0;
    //extracting the sign
    if ((string[0] == '-' || string[0] == '+')){
        i = 1; left_len++;
    }
    //handles +1, 1+, +++ --- +-+ and similar outputs
    if ((string[0] == '-' || string[0] == '+') && operatorCounter == 1){
        i = 0;
        left_len--;
    }
    
    
    for (; string[i] != '+' && string[i] != '-' && string[i] != '*' && string[i] != '/' ; i++) {
        left_len++;
    }
    
    sign = string[i]; //assign extracted sign
    
    i = 0;
    //extract left hand side of the operand
    for (; i < left_len; i++) {
        lefthandside[i] = string[i];
    }
    
    lefthandside[i] = '\0'; //make sure we have the end character at the end of the char array(string) because of partition
    i++;                    // increment i so it points to the next number and not the sign between 2 numbers.
    
    int k = 0;
    for (; (string[i] != '\0'+1); i++) { //limit the loop to go 1 char after the end character because we need the end char inside the string because of partition
        righthandside[k++] = string[i];
    }
    
    //    righthandside[k] = '\0';
    
    fnum1 = myAtof(lefthandside, &errorState);
    fnum2 = myAtof(righthandside, &errorState2);
    
    
    if (errorState==0 && errorState2 == 0){ //if no errors in both numbers continue through the output
        
        if (sign == '/' && fnum2 == 0){
            printf("Cannot divided into 0."); //we cannot divide by 0
            exit(1);                //exit code is 1 => error
        }
        
        if (sign == '+')
            fnum3 = fnum1 + fnum2;
        else if (sign == '-')
            fnum3 = fnum1 - fnum2;
        else if (sign == '*')
            fnum3 = fnum1 * fnum2;
        else
            fnum3 = fnum1 / fnum2;
        
        printf("%.2f %c %.2f = %.2f\n",fnum1,sign,fnum2,fnum3);
        
        
    } else if (errorState == 1 || errorState2 == 1){ //if one number malfunctions, produce an error print.
        printf("Error has been occurred due to inappropriate input!\n");
    }
    
    return 0;
}


float myAtof(char* string, char* error){          // Function to convert string into float.
    *error = 0;
    int sign = 0;
    int i = 0;
    int has_point = 0;
    int numwop = 0;
    int numwp = 0;
    float final_nwp = 0;
    float final_number = 0;
    int point_counter = 0;
    int len = 0;
    int pow_control = 0;
    
   // printf("printing from myatof %s\n\n",string); //used to check if the string from main is correct
    
    //first check if the number is negative
    if (string[0] == '-' || string[0] == '+'){
        sign = 1;
    }
        
    if (sign)
        i = 1;
    
    //then check for invalid char's
    for (; string[i] != '\0'; i++){
        if (string[i] < 46 || string[i] > '9' || string[i] == '/'){ // handles 4a, 123.34a, /asd or any other similar case which isn't a number.
            *error = 1;
            return 0;
        }
    }
    
    if (sign)
        i = 1;
    else
        i = 0;
        
        //determine if point is present in the number
    for (; string[i] != '\0'; i++){
        len++;
        if (string[i] == '.'){
            point_counter++;
            has_point = 1;
        }
    }

    if (point_counter > 1){ //controls if user accidentally types more than one point (.) in the input
        *error = 1;
        return 0;
    }
    
    //if it is an integer, continue as follows
    if (has_point == 0) {
        pow_control = len;
        int j = (sign) ? 1 : 0;
        
        if (!sign)
            for (; j < len; j++)
                numwop += (string[j] - '0') * pow(10,--pow_control);
            
        else
            for (; j <= len; j++)
                numwop += (string[j] - '0') * pow(10,--pow_control);
            
        final_number = numwop;
    }
                //else if its not an integer, do the following
                else if (has_point){
                    //determine len of the left side
                    int left_len = (sign) ? 1 : 0;
                    int d = (sign) ? 1 : 0;
                    
                    for (; string[d] != '.'; d++){
                        left_len++;
                    }
                    
                    int k = (sign) ? 1 : 0; //if there is a negative sign, control string len by k
                    
                    pow_control = left_len - ((sign) ? 1 : 0);
                    
                    for (; string[k] != '.'; k++) {
                        numwop += (string[k] - '0') * pow(10,--pow_control); // left side obtained
                    }

                    //obtain right side of the point, then sum it up to get the full number.
                    int n = left_len + 1;
                    
                    pow_control = len - n + ((sign) ? 1 : 0);
                    int division_control = pow_control;
                    
                    if (!sign)
                        for (; n < len; n++) {
                            numwp += (string[n] - '0') * pow(10,--pow_control); //obtain the right side as an integer
                        }
                    else
                        for (; n <= len; n++) {
                            numwp += (string[n] - '0') * pow(10,--pow_control); //obtain the right side as an integer
                        }
                    
                    //make the right side decimal by dividing it with 10 to pow number of digits+1
                    final_nwp = (float) numwp;
                    final_nwp /= pow(10,division_control);
                    
                    // final number with floating point obtained
                    final_number = final_nwp + numwop;
                }

                if (string[0] == '-')
                    final_number = final_number * (-1); //make it negative if needed
        
    return final_number;
}
