/*
    ROT 13 
*/

#include <iostream>
#include <string>
#include <iomanip>

std::string rot13( const std::string& input );

int main( int argc, char** argv )
{
    if( argc < 2 || argc > 2 ){ std::cout << "\nusage: rot13 <message> "<< std::endl; }
    else
    {
        std::string input = argv[ 1 ];
        std::string output = rot13( input );
        
        std::cout << output << std::endl;        
    }
    
    return 0;
}

std::string rot13( const std::string& input )
{
    std::string output;
    int aux;                          
    
    for( size_t i = 0; i < input.size(); i++ )
    {
         if( isupper( input[ i ] ) )
         { 
             aux = static_cast<int>( input[ i ] );
	     if( aux - 64 <= 13 ){ aux += 13; }
	     else{ aux = ( ( ( aux - 64 ) + 13 ) % 26 ) + 64; }
	     output+= static_cast<char>( aux );
        }
        else if( islower( input[ i ] ) )
        {
            aux = static_cast<int>( input[ i ] );
	    if( aux - 96 <= 13 ){ aux += 13; }
	    else{ aux = ( ( ( aux - 96 ) + 13 ) % 26 ) + 96; }
            output+= static_cast<char>( aux );
        }
	else{ output+= input[ i ]; }        
    }
    
    return output;
}
