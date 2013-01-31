#include "Unicode.h"

using namespace Util;


namespace
{
    template<size_t wcharSize>
    struct WStringHelper
    {
        static ConversionResult toUTF8(const wchar_t *&sourceStart, const wchar_t *sourceEnd, Byte *&targetStart, Byte *targetEnd, ConversionFlags flags);
        static ConversionResult fromUTF8(const Byte *&sourceStart, const Byte *sourceEnd, wchar_t *&targetStart, wchar_t *targetEnd, ConversionFlags flags);

    };
    template<>
    struct WStringHelper<2>
    {
        static ConversionResult toUTF8(const wchar_t *&sourceStart, const wchar_t *sourceEnd, Byte *&targetStart, Byte *targetEnd, ConversionFlags flags)
        {
            return ConvertUTF16toUTF8(reinterpret_cast<const UTF16 **>(&sourceStart), reinterpret_cast<const UTF16 *>(sourceEnd), &targetStart, targetEnd, flags);

        }
        static ConversionResult fromUTF8(const Byte *&sourceStart, const Byte *sourceEnd, wchar_t *&targetStart, wchar_t *targetEnd, ConversionFlags flags)
        {
            return ConvertUTF8toUTF16(&sourceStart, sourceEnd, reinterpret_cast<UTF16 **>(&targetStart), reinterpret_cast<UTF16 *>(targetEnd), flags);
        }

    };

    template<>
    struct WStringHelper<4>
    {
        static ConversionResult toUTF8(const wchar_t *&sourceStart, const wchar_t *sourceEnd, Byte *&targetStart, Byte *targetEnd, ConversionFlags flags)
        {
            return ConvertUTF32toUTF8(reinterpret_cast<const UTF32 **>(&sourceStart), reinterpret_cast<const UTF32 *>(sourceEnd), &targetStart, targetEnd, flags);

        }
               static ConversionResult fromUTF8(const Byte *&sourceStart, const Byte *sourceEnd, wchar_t *&targetStart, wchar_t *targetEnd, ConversionFlags flags)
        {
            return ConvertUTF8toUTF32(&sourceStart, sourceEnd, reinterpret_cast<UTF32 **>(&targetStart), reinterpret_cast<UTF32 *>(targetEnd), flags);

        }

    };


}



namespace Util
{
    ConversionResult convertUTFWstringToUTF8( const wchar_t *&sourceStart, const wchar_t *sourceEnd, Byte *&targetStart, Byte *targetEnd, ConversionFlags flags )
    {
        
		return WStringHelper<sizeof(wchar_t)>::toUTF8(sourceStart,sourceEnd,targetStart,targetEnd,flags);

    }

        ConversionResult convertUTF8ToUTFWstring( const Byte *&sourceStart, const Byte *sourceEnd, wchar_t *&targetStart, wchar_t *targetEnd, ConversionFlags flags )
    {
		return WStringHelper<sizeof(wchar_t)>::fromUTF8(sourceStart,sourceEnd,targetStart,targetEnd,flags);

    }

    ConversionResult convertUTF8ToUTFWstring( const Byte *&sourceStart, const Byte *sourceEnd, std::wstring &target, ConversionFlags flags )
    {
		size_t size = static_cast<size_t>(sourceEnd - sourceStart);
		wchar_t* outBuf = new wchar_t[size];
		wchar_t* targetStart = outBuf; 
		wchar_t* targetEnd = targetStart + size;

		ConversionResult result =  
			convertUTF8ToUTFWstring(sourceStart, sourceEnd, targetStart,
			targetEnd, flags);

		if(result == conversionOK)
		{
			std::wstring s(outBuf, static_cast<size_t>(targetStart - outBuf));
			s.swap(target);
		}
		delete[] outBuf;
		return result;

    }

}

namespace Util
{
	std::string wstringToString( const wstring& wstr, ConversionFlags flags )
	{
		string target;
		
		size_t size =wstr.size()*3*(sizeof(wchar_t)/2);

		Byte* outBuf = new Byte[size];
		Byte* targetStart = outBuf;
		Byte* targetEnd = outBuf + size;

		const wchar_t* sourceStart = wstr.data();

		ConversionResult cr = convertUTFWstringToUTF8(sourceStart,sourceStart+wstr.size(),targetStart,targetEnd,flags);

		if (cr != conversionOK)
		{
			delete [] outBuf;
			//exception handle here!!!
		}

		string s(reinterpret_cast<char*>(outBuf),static_cast<size_t>(targetEnd-targetStart));

		s.swap(target);
		delete outBuf;
		return target;
	}

	std::wstring stringToWstring( const string& str, ConversionFlags flags )
	{

		wstring result;
		const Byte* sourceStart = reinterpret_cast<const Byte*>(str.data());


		ConversionResult cr = convertUTF8ToUTFWstring(sourceStart,sourceStart+str.size(),result,flags);

		if (cr != conversionOK)
		{
			//exception handle here
		}

		return result;

	}
	
}
