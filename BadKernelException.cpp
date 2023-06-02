#include <iostream>
#include <exception>
using std::exception;

class BadKernelException : public exception
{
    const char * what () const throw () 
    {
        return "Izabrani kernel nije validan (Moguc je samo prirodan neparan broj)";
    }
};