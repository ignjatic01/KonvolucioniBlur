#include <iostream>
#include <fstream>
#include <vector>
#include "InputFileException.cpp"


using std::ios;
using std::ifstream;
using std::ofstream;
using std::vector;

class BMPFileHandler
{
public:
    BMPFileHandler();

    static unsigned char* readMatrixOpt(char* filein, int& row_num, int& col_num, int flag)
    {
        ifstream file(filein, ios::binary);
        char header[54];
        file.read(header, 54);  //citanje hedera slike
        if(header[28] != 24 && header[0] != 'B' && header[1] != 'M')   //provjera formata
        {
            throw InputFileException();
        }
        int& rows = *(int*)&header[22];
        int& cols = *(int*)&header[18];
        row_num = rows;
        col_num = cols;

        unsigned char* image = new unsigned char[row_num * col_num * 3];
        //Ucitavanje matrice piksela
        
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                unsigned char pixel[3];
                file.read((char *)pixel, 3);
                for(int k = 0; k < 3; k++)
                {
                    image[i*cols*3 + j*3 + k] = pixel[k];
                }
            }
        }

        file.close();
        return image;
    }

    static void printImageOpt(unsigned char* image, int rows, int cols, char* fileOut, int kernel)
    {
        ofstream file(fileOut, ios::binary);

        char header[54];
        for(int i = 0; i < 54; i++)
        {
            header[i] = 0;
        }
        header[0] = 'B';
        header[1] = 'M';
        header[10] = 54;
        header[14] = 40;
        header[26] = 1;
        header[28] = 24;

        int padding;
        if(kernel % 4 == 3)
        {
            padding = kernel + 1;
        }
        else
        {
            padding = kernel - 1;
        }

        *(int*)&header[18] = cols - padding;
        *(int*)&header[22] = rows - padding;

        // Upis veličine fajla u zaglavlje
        int fileSize = 54 + 3 * (rows - padding) * (cols - padding);
        *(int*)&header[2] = fileSize;

        file.write(header, 54);   // Upis zaglavlja u fajl

        // Upis podataka o pikselima u fajl
        for (int i = 0; i < rows - padding; i++) {
            for (int j = 0; j < cols - padding; j++) {
                unsigned char pixel[3] = { image[i*cols*3 + j*3 + 0], image[i*cols*3 + j*3 + 1], image[i*cols*3 + j*3 + 2] };
                file.write((char *)pixel, 3);
            }
        }
        file.close();
    }
};