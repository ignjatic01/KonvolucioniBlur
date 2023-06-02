#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

#include "BMPFileHandler.cpp"
#include "ConvolutionBlur.cpp"
#include "BadArgumentsException.cpp"
#include "BadKernelException.cpp"

using std::vector;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    try
    {
        if(argc < 3)
        {
            throw BadArgumentsException();
        }
        int KERNEL_SIZE;
        if(argc == 3)
        {
            KERNEL_SIZE = 5;
        }
        else
        {
            int test = atoi(argv[3]);
            if(test % 2 == 0 || test < 1)
                throw BadKernelException();
            KERNEL_SIZE = test;
        }

        int row, col;
        

        clock_t start = clock(), diff;
        unsigned char* image = BMPFileHandler::readMatrixOpt(argv[1], row, col, 0);
        diff = clock() - start;
        int msec = diff * 1000 / CLOCKS_PER_SEC; 
        std::cout << "Vrijeme: "<< msec << " ms" << std::endl;

        double itime, ftime, exec_time;

        itime = omp_get_wtime();
        unsigned char* imageOut = ConvolutionBlur::blurImage(image, row, col, KERNEL_SIZE);
        ftime = omp_get_wtime();
        exec_time = ftime - itime;
        std::cout << "Vrijeme: "<< exec_time * 1000<< " ms" << std::endl;

        itime = omp_get_wtime();
        imageOut = ConvolutionBlur::blurImageKes(image, row, col, KERNEL_SIZE);
        ftime = omp_get_wtime();
        exec_time = ftime - itime;
        std::cout << "Vrijeme: "<< exec_time * 1000<< " ms" << std::endl;

        BMPFileHandler::printImageOpt(imageOut, row, col, argv[2], KERNEL_SIZE);
        delete[] image;
        delete[] imageOut;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}