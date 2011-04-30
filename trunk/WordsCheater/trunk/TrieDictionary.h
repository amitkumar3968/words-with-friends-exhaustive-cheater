#ifndef TRIEDICTIONARY_H
#define TRIEDICTIONARY_H

#include "IDict.h"
#include "Trie.h"

class TrieDictionary : public IDict
{
public:
    TrieDictionary(void);


public:
    explicit TrieDictionary( const std::string& dictFilePath );

    virtual bool IsStringValid( const std::string& str ) const ;
    virtual bool IsSubStringValid( const std::string& str ) const ;

private:
    Trie m_trie;
};

#endif