#pragma once
#include "Config.h"
#include "ConvertUTF.h"

namespace Util
{


	std::string wstringToString(const std::wstring &, ConversionFlags flags);
	std::wstring stringToWstring(const std::string &, ConversionFlags flags);

	
    ConversionResult
    convertUTFWstringToUTF8(const wchar_t *&sourceStart, const wchar_t *sourceEnd,
                            Byte *&targetStart, Byte *targetEnd, ConversionFlags flags);

    ConversionResult
    convertUTF8ToUTFWstring(const Byte *&sourceStart, const Byte *sourceEnd,
                            wchar_t *&targetStart, wchar_t *targetEnd, ConversionFlags flags);

    ConversionResult
    convertUTF8ToUTFWstring(const Byte *&sourceStart, const Byte *sourceEnd,
                            std::wstring &target, ConversionFlags flags);



};
