#include "Trie.h"

namespace
{
    const char FIRST_CHAR = 'a';
    const int MAX_CHILDREN_NUM = 26;
}

Trie::Trie( )
{
    m_isValid = 0;
    for( int i = 0; i<MAX_CHILDREN_NUM; ++i )
        m_children[i] = 0;
}

Trie::~Trie( )
{
    for( int i = 0; i<MAX_CHILDREN_NUM; ++i )
    {
        if( m_children[i] )
            delete m_children[i];
    }
}

void Trie::add( const char* str )
{
    if( *str == '\0' )
        m_isValid = true;
    else
    {
        if( m_children[*str - FIRST_CHAR] == 0 )
            m_children[*str - FIRST_CHAR] = new Trie( );

        m_children[*str - FIRST_CHAR]->add( str + 1 );
    }
}

bool Trie::lookup( const char* str ) const
{
    if( *str == '\0' )
        return m_isValid;
    else
    {
        if( *str == '.' )
        {
            for( int i = 0; i<MAX_CHILDREN_NUM; ++i )
            {
                if( m_children[i] != 0
                    && m_children[i]->lookup( str + 1 ) )
                    return true;
            }
        }
        else if( m_children[*str - FIRST_CHAR] != 0 )
            return m_children[*str - FIRST_CHAR]->lookup( str + 1 );

        return false;
    }
}