#ifndef TRIE_H
#define TRIE_H

class Trie
{
public:
    Trie( );
    virtual ~Trie( );

    void add( const char* );
    bool lookup( const char* str ) const;

private:
    Trie* m_children[26];
    bool  m_isValid;
};

#endif