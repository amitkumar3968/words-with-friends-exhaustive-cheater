#ifndef IDICT_H
#define IDICT_H

#include <string>

class IDict
{
public:

    virtual bool IsStringValid( const std::string& str ) const = 0;

    virtual bool IsSubStringValid( const std::string& str ) const = 0;

    virtual ~IDict( );
};

#endif