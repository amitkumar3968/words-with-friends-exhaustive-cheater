#include "Dictionary.h"
#include <fstream>
#include <regex>
#include <sstream>

Dictionary::Dictionary( const std::string& dictFilePath )
 :m_dictionaryFile( )
{
    std::ifstream ifs( dictFilePath );
    if( !ifs )
        throw std::invalid_argument( __FUNCTION__ "invalid dictionary file path " );
    
    std::stringstream ss;
    ss << ifs.rdbuf( );
    m_dictionaryFile = ss.str();

    ifs.close( );
}

bool Dictionary::IsStringValid( const std::string& str ) const 
{
    if( str.size() < 2 )
        return false;
    std::regex ex( std::string("^") + str + "$" );
    return std::regex_search( m_dictionaryFile.begin(),
                              m_dictionaryFile.end(),
                              ex );
}

bool Dictionary::IsSubStringValid( const std::string& str ) const 
{
    if( str.size() < 2 )
        return false;
    std::regex ex( str );
    return std::regex_search( m_dictionaryFile.begin(),
                              m_dictionaryFile.end(),
                              ex );
}
