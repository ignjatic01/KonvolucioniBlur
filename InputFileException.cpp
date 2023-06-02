#include <iostream>
#include <exception>
using std::exception;

class InputFileException : public exception
{
    const char * what () const throw () 
    {
        return "Ulazna datoteka moze biti samo BMP 24-bitnog formata!";
    }
};