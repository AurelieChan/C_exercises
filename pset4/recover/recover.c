#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //Check for invalid usage
    if (argc != 2)
    {

        printf("Usage: ./recover image\n");

        return 1;

    }

    //Open memory card
    FILE *file = fopen(argv[1], "r");

    //Declare new JPEG file
    FILE *jpegfile = NULL;

    //Whether a JPEG file is open
    bool fileopen = false;

    //Define filename, gives a name to each new JPEG files
    char *filename = (char *) malloc(7);

    //Counter for JPEG file name
    int filenamecounter = 0;

    //Declare bytesread, reads the bytes one by one
    int bytesread;

    //Repeat until end of card:
    do
    {

        uint8_t buffer[512];

        //Read 512 bytes block into a buffer
        bytesread = fread(buffer, 1, 512, file);

        //If the beginning of a new JPEG file is found
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            if (fileopen)
            {

                //close the currently open JPEG
                fclose(jpegfile);

                filenamecounter++;

            }

            //Name the JPEG file
            sprintf(filename, "%03i.jpg", filenamecounter);

            //Open a new JPEG file
            jpegfile = fopen(filename, "w");

            fileopen = true;

            //Write data to that file
            fwrite(buffer, 1, bytesread, jpegfile);

        }
        else if (fileopen)
        {

            fwrite(buffer, 1, bytesread, jpegfile);
            
        }

    }
    while (bytesread == 512);

    if (fileopen)
    {
    
        fclose(jpegfile);
        
    }

    free(filename);
}
