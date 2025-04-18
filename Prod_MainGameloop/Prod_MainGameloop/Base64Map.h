// Base64Map.h

#ifndef BASE64MAP_H
#define BASE64MAP_H

#include <unordered_map>

namespace B64
{
    extern std::unordered_map<char, int> base64CharToVal;
    
    extern char base64ValToChar[64];

    void initializeBase64Maps();
}

#endif