#include <vector>
#include <iostream>
#include <omp.h>
using std::vector;

class ConvolutionBlur
{
public:
    static unsigned char* blurImageKes(unsigned char* image, int rows, int cols, int KERNEL_SIZE)
    {
        unsigned char* imageOut = new unsigned char[rows * cols * 3];
        for (int i = (KERNEL_SIZE-1)/2; i < rows - (KERNEL_SIZE-1)/2; i++) 
        {
            for (int j = (KERNEL_SIZE-1)/2; j < cols - (KERNEL_SIZE-1)/2; j++) 
            {
                int sumR = 0;
                int sumB = 0;
                int sumG = 0;
                for(int x = -(KERNEL_SIZE - 1)/2; x <= (KERNEL_SIZE - 1)/2; x++)
                {
                    for(int z = -(KERNEL_SIZE - 1)/2; z <= (KERNEL_SIZE - 1)/2; z++)
                    {
                        sumR+=(int)image[(i+x)*cols*3 + (j+z)*3 + 0];
                        sumB+=(int)image[(i+x)*cols*3 + (j+z)*3 + 1];
                        sumG+=(int)image[(i+x)*cols*3 + (j+z)*3 + 2];
                    }
                }                   
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 0] = sumR/(KERNEL_SIZE*KERNEL_SIZE);
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 1] = sumB/(KERNEL_SIZE*KERNEL_SIZE);
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 2] = sumG/(KERNEL_SIZE*KERNEL_SIZE);
            }
        }
        return imageOut;
    }

    static unsigned char* blurImage(unsigned char* image, int rows, int cols, int KERNEL_SIZE)
    {
        unsigned char* imageOut = new unsigned char[rows * cols * 3];
        for (int j = (KERNEL_SIZE-1)/2; j < cols - (KERNEL_SIZE-1)/2; j++) 
        {
            for (int i = (KERNEL_SIZE-1)/2; i < rows - (KERNEL_SIZE-1)/2; i++) 
            {
                int sumR = 0;
                int sumB = 0;
                int sumG = 0;
                for(int z = -(KERNEL_SIZE - 1)/2; z <= (KERNEL_SIZE - 1)/2; z++)
                {
                    for(int x = -(KERNEL_SIZE - 1)/2; x <= (KERNEL_SIZE - 1)/2; x++)
                    {
                        sumR+=(int)image[(i+x)*cols*3 + (j+z)*3 + 0];
                        sumB+=(int)image[(i+x)*cols*3 + (j+z)*3 + 1];
                        sumG+=(int)image[(i+x)*cols*3 + (j+z)*3 + 2];
                    }
                }                   
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 0] = sumR/(KERNEL_SIZE*KERNEL_SIZE);
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 1] = sumB/(KERNEL_SIZE*KERNEL_SIZE);
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 2] = sumG/(KERNEL_SIZE*KERNEL_SIZE);
            }
        }
        return imageOut;
    }

    static unsigned char* blurImageOpenMP(unsigned char* image, int rows, int cols, int KERNEL_SIZE)
    {
        unsigned char* imageOut = new unsigned char[rows * cols * 3];
        #pragma omp parallel for
        for (int j = (KERNEL_SIZE-1)/2; j < cols - (KERNEL_SIZE-1)/2; j++) 
        {
            for (int i = (KERNEL_SIZE-1)/2; i < rows - (KERNEL_SIZE-1)/2; i++) 
            {
                int sumR = 0;
                int sumB = 0;
                int sumG = 0;
                for(int z = -(KERNEL_SIZE - 1)/2; z <= (KERNEL_SIZE - 1)/2; z++)
                {
                    for(int x = -(KERNEL_SIZE - 1)/2; x <= (KERNEL_SIZE - 1)/2; x++)
                    {
                        sumR+=(int)image[(i+x)*cols*3 + (j+z)*3 + 0];
                        sumB+=(int)image[(i+x)*cols*3 + (j+z)*3 + 1];
                        sumG+=(int)image[(i+x)*cols*3 + (j+z)*3 + 2];
                    }
                }                   
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 0] = sumR/(KERNEL_SIZE*KERNEL_SIZE);
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 1] = sumB/(KERNEL_SIZE*KERNEL_SIZE);
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 2] = sumG/(KERNEL_SIZE*KERNEL_SIZE);
            }
        }
        return imageOut;
    }

    static unsigned char* blurImageKesOpenMP(unsigned char* image, int rows, int cols, int KERNEL_SIZE)
    {
        unsigned char* imageOut = new unsigned char[rows * cols * 3];
        #pragma omp parallel for
        for (int i = (KERNEL_SIZE-1)/2; i < rows - (KERNEL_SIZE-1)/2; i++) 
        {
            for (int j = (KERNEL_SIZE-1)/2; j < cols - (KERNEL_SIZE-1)/2; j++) 
            {
                int sumR = 0;
                int sumB = 0;
                int sumG = 0;
                for(int x = -(KERNEL_SIZE - 1)/2; x <= (KERNEL_SIZE - 1)/2; x++)
                {
                    for(int z = -(KERNEL_SIZE - 1)/2; z <= (KERNEL_SIZE - 1)/2; z++)
                    {
                        sumR+=(int)image[(i+x)*cols*3 + (j+z)*3 + 0];
                        sumB+=(int)image[(i+x)*cols*3 + (j+z)*3 + 1];
                        sumG+=(int)image[(i+x)*cols*3 + (j+z)*3 + 2];
                    }
                }                   
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 0] = sumR/(KERNEL_SIZE*KERNEL_SIZE);
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 1] = sumB/(KERNEL_SIZE*KERNEL_SIZE);
                imageOut[(i - (KERNEL_SIZE - 1)/2)*cols*3 + (j - (KERNEL_SIZE - 1)/2)*3 + 2] = sumG/(KERNEL_SIZE*KERNEL_SIZE);
            }
        }
        return imageOut;
    }    
};