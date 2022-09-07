// create an image of the mandelbrot set from scratch
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *image_pgm;
int CreateImageFile(int** image,int width,int height)
{
    image_pgm = fopen("mandelbrot_set_image.pgm", "wb");      // create file
    fprintf(image_pgm, "P2\n");                               // magic number ?
    fprintf(image_pgm, "%d %d\n", width, height);             // width and height
    fprintf(image_pgm, "120\n");                              // max pixel value

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            // Writing the gray values in the 2D array to the file
            fprintf(image_pgm, "%d ", image[x][y]);
        }
        fprintf(image_pgm, "\n");
    }
    fclose(image_pgm);
}

int NumberOfIteration(float x, float y, float w, float h)
{
    int size_change = (w + h)*0.1;
    float z[2] = {0, 0};
    float c[2] = {(y/size_change)-(h/size_change)/2,(x/size_change)-(w/size_change)/2};
    for (int i = 1; i <= 100; i++)
    {
        //z[0] = z[0] * z[0] + c[0];
        //z[1] = z[1] * z[1] + c[1];
        // z² + c

        float tempx = z[0] * z[0] - z[1] * z[1] + c[0];
        z[1] = 2 * z[0] * z[1] + c[1];
        z[0] = tempx;

        if (sqrt(z[0] * z[0] + z[1] * z[1]) > 2)
        {
            return i + 1;
        }
    }
    return -1;
}

int **output_array;
int **CalculateMandelbrotValue(int width, int height)
{
    output_array = malloc(sizeof(int *) * width);
    for (int i = 0; i < height; i++)
    {
        output_array[i] = malloc(sizeof(int) * height);
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < width; y++)
        {
            output_array[x][y] = NumberOfIteration(x, y, width, height);
        }
    }
    return output_array;
}

int main()
{
    printf("%s\n","Mandelbrot Set image creation in progress...");

    int height = 2000;
    int width = 2000;
    printf("%s %dpx %s %dpx.\n","creating image with height",height,"and with width", width);
    
    int **mandelbrot_data = CalculateMandelbrotValue(width, height);
    printf("Calculating pixel data.\n");
    
    CreateImageFile(mandelbrot_data,width,height);
    printf("Creating image as mandelbrot_set_image.pgm");
    
    free(output_array);
    free(mandelbrot_data);
    free(image_pgm);
    return 0;
}
