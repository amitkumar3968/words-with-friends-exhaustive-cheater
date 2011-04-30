#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "IDict.h"

class Dictionary : public IDict
{
public:
    explicit Dictionary( const std::string& dictFilePath );

    virtual bool IsStringValid( const std::string& str ) const ;
    virtual bool IsSubStringValid( const std::string& str ) const ;

private:
    std::string    m_dictionaryFile;
};
#endif