// Base64Map.h

// include guard
#ifndef BASE64MAP_H
#define BASE64MAP_H

#include <unordered_map>
#include <array>

namespace B64
{
    extern std::unordered_map<char, int> base64CharToVal;
    
    extern std::array<char, 64> base64ValToChar;
    
    void initializeBase64Maps();
}

#endif