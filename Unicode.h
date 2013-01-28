#include "Config.h"
#include "ConvertUTF.h"

namespace Util
{
	typedef enum
	{
		strictConversion = 0,
		lenientConversion
	} ConversionFlags;

	std::string wstringToString(const std::wstring &, ConversionFlags flags= lenientConversion);
	std::wstring stringToWstring(const std::string &, ConversionFlags flags= lenientConversion);

	typedef unsigned char Byte;



	enum ConversionError
	{
		partialCharacter,
		badEncoding
	};

}

namespace UtilInternal
{

    typedef enum
    {
        /* conversion successful */
        conversionOK,
        /* partial character in source, but hit end */
        sourceExhausted,
        /* insuff. room in target for conversion */
        targetExhausted,
        /* source sequence is illegal/malformed */
        sourceIllegal
    } ConversionResult;

    ConversionResult
    convertUTFWstringToUTF8(const wchar_t *&sourceStart, const wchar_t *sourceEnd,
                            Util::Byte *&targetStart, Util::Byte *targetEnd, Util::ConversionFlags flags);

    ConversionResult
    convertUTF8ToUTFWstring(const Util::Byte *&sourceStart, const Util::Byte *sourceEnd,
                            wchar_t *&targetStart, wchar_t *targetEnd, Util::ConversionFlags flags);

    ConversionResult
    convertUTF8ToUTFWstring(const Util::Byte *&sourceStart, const Util::Byte *sourceEnd,
                            std::wstring &target, Util::ConversionFlags flags);



}
