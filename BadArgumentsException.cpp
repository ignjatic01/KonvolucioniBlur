#include <iostream>
#include <exception>
using std::exception;

class BadArgumentsException : public exception
{
    const char * what () const throw () 
    {
        return "Nedovoljan broj argumenata!";
    }
};