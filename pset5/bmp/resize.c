/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#include "bmp.h"
int n;
int main(int argc, char* argv[])
{


    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    

 n = atoi(argv[1]);
     if(n <= 0 || n > 100)
     {
            printf("./resize n(positive integer <=100), infile outfile\n");
            return 1;
     }
 
     

    /*
        Remember filenames
    */
    char* infile = argv[2];
    char* outfile = argv[3];

    /*
        Open input file 
    */     
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    /*
       Open output file
    */
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    /*
       Read infile's BITMAPFILEHEADER
    */
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    /*
       Read infile's BITMAPINFOHEADER
    */
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    /*
       Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    */
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    /*
        Calculate the new bfsize by multipilying bi.biSizeImage by n
        Copy the value of bi.biWidth and bi.biHeight in a new variable (representing the " old " situation
    */
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (bi.biSizeImage * n);
    
    LONG biHeight = bi.biHeight;
    LONG biWidth = bi.biWidth;
    
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    bi.biSizeImage = bi.biSizeImage *n;
    
    
    /* 
        Padding_new works with the new bi.biwidth necessary for the output file.
    */
    int padding =  (4 - (biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_new =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    /* 
        Write outfile's BITMAPFILEHEADER
    */
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    /*
        Write outfile's BITMAPINFOHEADER
    */
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    int absoluteBiHeight = abs(biHeight);

    /*
        Iterate over infile's scanlines
    */
    for (int i = 0; i < absoluteBiHeight; i++)
    {
    
        for (int seek = 0; seek < n; seek++)
        {   
            fseek(inptr, (54 + ((biWidth * 3 + padding) * i)), SEEK_SET);
        
            /*
                Iterate over pixels in scanline
            */
            for (int j = 0; j < biWidth; j++)
            {
                RGBTRIPLE triple;

                /*
                    Read RGB triple from infile
                 */
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
            /*  
                Write RGB triple to outfile
                Write every biWidth pixel n times (for example n was 3 it will write that pixel 3 times)
            */
            for(int m = 0; m < n; m++) 
			
			    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
			}

            fseek(inptr, padding, SEEK_CUR);

            /*
              Add padding
            */
            for (int k = 0; k < padding_new; k++)
            {
                fputc(0x00, outptr);
            }
            
            
         }
             
    }

    /*
    Close infile
    */
    fclose(inptr);

    /*
    Close outfile
    */
    fclose(outptr);

    // that's all folks
    return 0;
}
