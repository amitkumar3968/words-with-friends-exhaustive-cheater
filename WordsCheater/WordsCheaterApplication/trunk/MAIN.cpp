
#include "MoveOptimalizer.h"

#include <fstream>
#include <iostream>

int main( int argc, const char* argv[] )
{
    // exe [dictPath] [boardPath]
    if( argc != 4 )
    {
        std::cout<< "invalid args: " << argv[0] << " [dictPath] [boardPath] " << std::endl;
        return -1;
    }

    std::string dictPath( argv[1] );
    std::string boardPath( argv[2] );
    std::string resultPath( argv[3] );

    MoveOptimalizer* core;

    try
    {
	    core = new MoveOptimalizer( dictPath, boardPath );
    }
    catch( std::invalid_argument e )
    {
        std::cout<< "invalid args: " << e.what() << std::endl;
        return -1;
    }
    catch( std::runtime_error e )
    {
        std::cout<< "runtime error: " << e.what() << std::endl;
        return -1;
    }


    std::cout << "Welcome to Words With Friends Exhaustive Cheater" << std::endl;
    while( 1 )
    {
        std::cout<< "Please input 7 characters to start: ";

        std::string tilesToPlace;
        std::cin >> tilesToPlace;

        std::cout << "tilesToPlace: " << tilesToPlace << std::endl;

        try
        {
            core->OptimizeMove( tilesToPlace );

            std::ofstream resultFile;
            resultFile.open( resultPath );

            core->printResultToStream( resultFile );

            resultFile.close();
        }
        catch( std::invalid_argument e )
        {
            std::cout<< "invalid args: " << e.what() << std::endl;
        }
        catch( std::runtime_error e )
        {
            std::cout<< "runtime error: " << e.what() << std::endl;
        }
    }
}