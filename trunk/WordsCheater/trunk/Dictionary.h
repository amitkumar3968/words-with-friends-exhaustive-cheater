#ifndef DICTIONARY_H
#define DICTIONARY_H


#include <string>

class Dictionary
{
public:
    explicit Dictionary( const std::string& dictFilePath );

    bool IsStringValid( const std::string& str );
    bool IsSubStringValid( const std::string& str );

private:
    std::string    m_dictionaryFile;
};
#endif