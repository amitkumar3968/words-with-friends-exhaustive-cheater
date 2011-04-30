#include "TrieDictionary.h"

#include <fstream>
#include <string>

TrieDictionary::TrieDictionary( const std::string& dictFilePath )
{
    std::ifstream ifs( dictFilePath );
    if( !ifs )
        throw std::invalid_argument( __FUNCTION__ "invalid TrieDictionary file path " );
    
    std::string s;

    while( std::getline( ifs, s ) )
    {
        if( s.size( ) > 0 )
            m_trie.add( s.c_str( ) );
    }

    ifs.close( );
}

bool TrieDictionary::IsStringValid( const std::string& str ) const 
{
    return m_trie.lookup( str.c_str( ) );
}

bool TrieDictionary::IsSubStringValid( const std::string& str ) const 
{
    return false;
}
