#include <stdio.h>


unsigned char byte_hexstring_to_int(char * input);


void test_byte_to_hex()
{

    char hex_array[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};



    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            printf("%c%c: ", hex_array[i], hex_array[j]);
            char arr[2] = {hex_array[i], hex_array[j]};
            unsigned char result = byte_hexstring_to_int(arr);
            printf("%d, ", result);
        }
    }




}


int main()
{

    test_byte_to_hex();


}