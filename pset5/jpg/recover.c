
       
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*use card.raw as input file*/
/*
    To do:Open memory card file
    Find beginning of jpg
    Open a new jpg file
    Write 512 bytes until new jpg is reached
    Detect end of file
    Start of a jpg is either 0xff 0xd8 0xff 0xe0 or 0xff 0xd8 0xff 0xe1
    When first jpg is found the next one is found 512 bytes away. Even if the jpg that is found is much smaller than that.
    Make a new jpg ###.jpg, named in the order in which they are found so keep track. First jpg will be 000.jpg
    sprintf(title, "%d.jpg", 2);
    title: char array to store the resultant string
    modify the placeholder to give it the correct name
    FILE* img = fopen(title, "a")
    pseudocode:
    -open card file
    -repeat until end of card
        -read 512 bytes into a buffer
        -start of a new jpg
        -yes or no ...
    -already found a jpg?
        -no
        -yes
    -close any remaining files
*/
 

int main (void)
{
    // remember filenames
    char* card_raw = "card.raw";

    // open input file 
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", card_raw);
        return 2;
    }
    
    FILE* output = NULL;
       
    int jpgNumber = 0; //counts the number of jpgs
    uint8_t buffer[512]; //reserve 512 byte spaces
    char jpgName[8]; //001.jpg\0 for example
       
    while (!feof(file))//while end of file is not reached continue 
    {
        //read 512 bytes into a buffer 
        fread(buffer, sizeof(buffer), 1, file);

        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            /*
              If output != NULL and a block with the start of a jpg is found it will automatically close the file that was still open for writing.
              This will automatically determine the end of the previous JPG file and the start of a new JPG file.
            */
                
            if(output != NULL)
            {
                fclose(output);
                output = NULL;
            }
            
            /*
              Make name %03d equals 000 in the file name. 
              JpgNumber links to the filename starting with 0 and incrementing everytime a new jpg is found.
            */
            
            sprintf(jpgName, "%03d.jpg", jpgNumber);
             
            /*
             Increment counter
            */ 
            jpgNumber++;
            
            /*
            Open a new file called like the jpgName created in the previous line of code and say that you want to write to that file
            */
            output = fopen(jpgName, "w");
            
         } 
         
         
         if (output != NULL)
         {
            fwrite(buffer, sizeof(buffer), 1, output);
         }  
     }
    
    /*
     Close the last file
    */
    if(output != NULL)
    {
        fclose(output);
    }

    //close card file
    fclose(file);
    
    return 0;
}
