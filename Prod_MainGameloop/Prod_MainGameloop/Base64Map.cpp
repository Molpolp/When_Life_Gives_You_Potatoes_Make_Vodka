/***************************************
Gregory Tuosto
Date Completed: March 15, 2025
Description: Base64Map library used to encode and decode using base 64
Version: 1.0
***************************************/

#include "Base64Map.h"

namespace B64
{
    std::unordered_map<char, int> base64CharToVal;

    std::array<char, 64> base64ValToChar;

    void initializeBase64Maps()
    {
        char character = 'A';
    
        for (int itteration = 0; itteration < 26; ++itteration, ++character)
        {
            base64CharToVal[character] = itteration;
        
            base64ValToChar[itteration] = character;
        }

        character = 'a';
        
        for (int itteration = 26; itteration < 52; ++itteration, ++character)
        {
            base64CharToVal[character] = itteration;
        
            base64ValToChar[itteration] = character;
        }

        character = '0';
        
        for (int itteration = 52; itteration < 62; ++itteration, ++character)
        {
            base64CharToVal[character] = itteration;
        
            base64ValToChar[itteration] = character;
        }

        base64CharToVal['+'] = 62;
        
        base64ValToChar[62] = '+';
        
        base64CharToVal['/'] = 63;
        
        base64ValToChar[63] = '/';
    }
}