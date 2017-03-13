//
// StegoDestroy --- random the last bit of each byte
//

#include "stego.h"

int main(int argc, const char *argv[])
{
    FILE *in,
         *out;

    int i,
        j,
        x,
        ttt,
        shft,
        byteCount,
        moreData,
        moreImage,
        imageBytes,
        dataBytes,
        dataBytesWritten,
        imageBytesWritten;

    char temp;

    char infname[80],
         outfname[80];

    if(argc != 3)
    {
oops:   fprintf(stderr, "\nUsage: %s stegoImage stegkdestroiedImage\n\n", argv[0]);

        exit(0);
    }

    sprintf(infname, argv[1]);
    sprintf(outfname, argv[2]);

    in = fopen(infname, "r");
    if(in == NULL)
    {
        fprintf(stderr, "\nError opening file %s\n\n", infname);
        exit(0);
    }

    imageBytes = 0;
    while(1)
    {
        x = fscanf(in, "%c", &temp);
        if(x != 1)
        {
            break;
        }
        ++imageBytes;
    }
    fclose(in);

    printf("image bytes = %d, capacity = %d bytes\n", imageBytes, imageBytes >> 3);

    in = fopen(infname, "r");
    if(in == NULL)
    {
        fprintf(stderr, "\nError opening file %s\n\n", infname);
        exit(0);
    }

    if((imageBytes - START_FROM - 27 - 64) <= 0)
    {
        fprintf(stderr, "\nImage file %s too small\n\n", infname);
        exit(0);

    }// end if


    out = fopen(outfname, "w");
    if(out == NULL)
    {
        fprintf(stderr, "\nError opening file %s\n\n", outfname);
        exit(0);
    }

    //
    // skip first START_FROM bytes of image file
    //
    imageBytesWritten = 0;
    for(i = 0; i < START_FROM; ++i)
    {
        x = fscanf(in, "%c", &temp);
        if(x != 1)
        {
            fprintf(stderr, "\nError in file %s\n\n", infname);
            exit(0);
        }
        fprintf(out, "%c", temp);
        ++imageBytesWritten;
    }




    moreImage = 1;
    while(moreImage)
    {
//        printf("byteCount = %d\n", byteCount);

        x = fscanf(in, "%c", &temp);
        if(x != 1)
        {
            moreImage = 0;
        }
        else
        {

            temp = temp ^ (rand()%2);


            fprintf(out, "%c", temp);
            ++imageBytesWritten;

        }// end if

    }// end while

    printf("\nimage bytes written = %d\n",
        imageBytesWritten);

    printf("\n");

    fclose(in);
    fclose(out);

}// end main
