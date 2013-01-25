#ifndef ConvertUTF_h__
#define ConvertUTF_h__
#include "Unicode.h"

namespace UtilInternal
{


    /* ---------------------------------------------------------------------
        The following 4 definitions are compiler-specific.
        The C standard does not guarantee that wchar_t has at least
        16 bits, so wchar_t is no less portable than unsigned short!
        All should be unsigned values to avoid sign extension during
        bit mask & shift operations.
    ------------------------------------------------------------------------ */

typedef unsigned long UTF32; /* at least 32 bits */
typedef unsigned short UTF16; /* at least 16 bits */
typedef unsigned char UTF8; /* typically 8 bits */
typedef unsigned char Boolean; /* 0 or 1 */

    /* Some fundamental constants */
#define UNI_REPLACEMENT_CHAR (UTF32)0x0000FFFD
#define UNI_MAX_BMP (UTF32)0x0000FFFF
#define UNI_MAX_UTF16 (UTF32)0x0010FFFF
#define UNI_MAX_UTF32 (UTF32)0x7FFFFFFF
#define UNI_MAX_LEGAL_UTF32 (UTF32)0x0010FFFF


    ConversionResult ConvertUTF8toUTF16 (
        const UTF8 **sourceStart, const UTF8 *sourceEnd,
		UTF16 **targetStart, UTF16 *targetEnd, Util::ConversionFlags flags);

    ConversionResult ConvertUTF16toUTF8 (
        const UTF16 **sourceStart, const UTF16 *sourceEnd,
        UTF8 **targetStart, UTF8 *targetEnd, Util::ConversionFlags flags);

    ConversionResult ConvertUTF8toUTF32 (
        const UTF8 **sourceStart, const UTF8 *sourceEnd,
        UTF32 **targetStart, UTF32 *targetEnd, Util::ConversionFlags flags);

    ConversionResult ConvertUTF32toUTF8 (
        const UTF32 **sourceStart, const UTF32 *sourceEnd,
        UTF8 **targetStart, UTF8 *targetEnd, Util::ConversionFlags flags);

    ConversionResult ConvertUTF16toUTF32 (
        const UTF16 **sourceStart, const UTF16 *sourceEnd,
        UTF32 **targetStart, UTF32 *targetEnd, Util::ConversionFlags flags);

    ConversionResult ConvertUTF32toUTF16 (
        const UTF32 **sourceStart, const UTF32 *sourceEnd,
        UTF16 **targetStart, UTF16 *targetEnd, Util::ConversionFlags flags);

 
};

#endif // ConvertUTF_h__