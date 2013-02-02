#include "Exception.h"
#if defined(__LINUX)
#  include <execinfo.h>
#  include <cxxabi.h>
#endif

#if defined(__LINUX)
string getStackTrace()
{
    string stackTrace;
    const size_t maxDepth = 100;
    void * stackAddrs[maxDepth];
    size_t stackDepth = backtrace(stackAddrs, maxDepth);
    char ** stackStrings = backtrace_symbols(stackAddrs, stackDepth);
    bool checkException = true;

    for (size_t i = 1; i < stackDepth; i++)
    {
        string line(stackStrings[i]);

        //
        // Don't add the traces for the Exception constructors.
        //
        if (checkException)
        {
            if (line.find("ExceptionC") != string::npos)
            {
                continue;
            }
            else
            {
                checkException = false;
            }
        }
        else
        {
            stackTrace += "\n";
        }

        stackTrace += "  ";
        //
        // For each line attempt to parse the mangled function name as well
        // as the source library/executable.
        //
        string mangled;
        string::size_type openParen = line.find_first_of('(');

        if (openParen != string::npos)
        {
            //
            // Format: "/opt/Ice/lib/libIceUtil.so.33(_ZN7IceUtil9ExceptionC2EPKci+0x51) [0x73b267]"
            //
            string::size_type closeParen = line.find_first_of(')', openParen);

            if (closeParen != string::npos)
            {
                string tmp = line.substr(openParen + 1, closeParen - openParen - 1);
                string::size_type plus = tmp.find_last_of('+');

                if (plus != string::npos)
                {
                    mangled = tmp.substr(0 , plus);
                    stackTrace += line.substr(0, openParen);
                }
            }
        }
        else
        {
            //
            // Format: "1    libIce.3.3.1.dylib   0x000933a1 _ZN7IceUtil9ExceptionC2EPKci + 71"
            //
            string::size_type plus = line.find_last_of('+');

            if (plus != string::npos)
            {
                string tmp = line.substr(0, plus - 1);
                string::size_type space = tmp.find_last_of(" \t");

                if (space != string::npos)
                {
                    tmp = tmp.substr(space + 1, tmp.size() - space);
                    string::size_type start = line.find_first_not_of(" \t", 3);

                    if (start != string::npos)
                    {
                        string::size_type finish = line.find_first_of(" \t", start);

                        if (finish != string::npos)
                        {
                            mangled = tmp;
                            stackTrace += line.substr(start, finish - start);
                        }
                    }
                }
            }
        }

        if (mangled.size() != 0)
        {
            stackTrace += ": ";
            //
            // Unmangle the function name
            //
            int status;
            char * unmangled = abi::__cxa_demangle(mangled.c_str(), 0, 0, &status);

            if (unmangled)
            {
                stackTrace += unmangled;
                free(unmangled);
            }
            else
            {
                stackTrace += mangled;
                stackTrace += "()";
            }
        }
        else
        {
            stackTrace += line;
        }
    }

    free(stackStrings);
    return stackTrace;
}
#endif
namespace Util
{


    Exception::Exception(): _file(0), _line(0)
#if defined(__LINUX)
        , _stackTrace(getStackTrace())
#endif
    {
    }

    Exception::Exception(char * file, int line): _file(file), _line(line)
#if defined(__LINUX)
        , _stackTrace(getStackTrace())
#endif
    {
    }

    Exception::~Exception() throw()
    {
    }

    const char * Exception::what() const throw()
    {
        try
        {
            if (_str.empty())
            {
                stringstream s;
                print(s);
                _str = s.str(); // Lazy initialization.
            }

            return _str.c_str();
        }
        catch (...)
        {
        }

        return " ";
    }

    void Exception::print(ostream & out) const
    {
        if (_file && _line > 0)
        {
            out << _file << ':' << _line << ": ";
        }

        out << exName();
    }

    Exception * Exception::clone() const
    {
        return new Exception(*this);
    }

    void Exception::exThrow() const
    {
        throw(*this);
    }

    int Exception::exLine() const
    {
        return _line;
    }

    const char * Exception::exFile() const
    {
        return _file;
    }

    const string& Exception::stackTrace() const
    {
        return _stackTrace;
    }

    const string Exception::exName() const
    {
        return "Util::Exception";
    }

    ostream & operator<<(ostream & out, const Exception& ex)
    {
        ex.print(out);
        return out;
    }
}