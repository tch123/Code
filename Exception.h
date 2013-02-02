#pragma once
#include "Config.h"
namespace Util
{


    class Exception: public exception
    {
    public:
        Exception();
        Exception(char * file, int line);
        virtual ~Exception()throw();

        virtual const char * what() const throw();
        virtual void print(ostream & os)const;
        virtual Exception * clone()const;
        virtual void exThrow()const;
        virtual const string exName()const;

        int exLine()const;
        const char * exFile()const;
        const string& stackTrace()const;


    private:
        const char * _file;
        int _line;
        static const char * _name;
        const std::string _stackTrace;
        mutable ::std::string _str; // Initialized lazily in what().
    };

}
