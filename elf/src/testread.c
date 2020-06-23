#include <stdio.h>
#include <unistd.h>


int main()
{
    
    FILE * fp = fopen("testread.o", "rb");
    unsigned char buffer[129];
    fread(buffer, 128, 1, fp);
    int offset = 0;
    for (int i = 0; i < 64; ++i)
    {
        if (buffer[i] < 0x10)
        {
            printf("0%x ", buffer[i]);
        }
        else 
        {
            printf("%x ", buffer[i]);
        }
        if (++offset % 16 == 0)
            printf("\n");
    }
    
}