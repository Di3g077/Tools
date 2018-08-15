/*
	main.cpp

	Copyright (C) 2010 - 2018 Diego Ferreira

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <iostream>
#include <string>
#include <sstream>

#include "Dumper.hpp"
#include "Mode.hpp"

void usage();
void examples();

int main( int argc, char** argv )
{
	std::string option;
	std::string _file;
	Read::Mode _read_mode;
	Dump::Mode _out_mode;
	size_t _start;
	size_t _end;
	Dumper _dumper;
	std::stringstream convert;
	
	option = argv[ 1 ];
	if( option == "oct" ){ _out_mode = Dump::Mode::Octal; }
	else if( option == "dec" ){ _out_mode = Dump::Mode::Decimal; }
	else if( option == "hex" ){ _out_mode = Dump::Mode::Hexadecimal; }
	else if( option == "ascii" ){ _out_mode = Dump::Mode::ASCII; }
	else if( option == "help" ){ usage(); return 0; }
	else if( option == "version" ){ std::cout << std::endl <<_dumper.version() << std::endl <<std::endl; return 0; }
	else if( option == "size" ){ option = argv[ 2 ]; std::cout << std::endl <<_dumper.get_size( option ) << std::endl <<std::endl; return 0; }
	else if( option == "examples" ){ examples(); return 0; }
	else{ return 0;}
	
	option = argv[ 2 ];
	if( option == "all" )
	{ 
		_read_mode = Read::Mode::Total; 
		_file = argv[ 3 ]; 
		_dumper.set_read_mode();
		_dumper.set_output_mode( _out_mode );
		_dumper.set_file( _file );
	}
	else if( option == "length" )
	{ 
		//option = argv[ 3 ];
		_read_mode = Read::Mode::Until;
		convert << argv[ 3 ];
		convert >> _end;
		convert.clear();
		
		_file = argv[ 4 ];
		_dumper.set_read_mode( _end );
		_dumper.set_output_mode( _out_mode );
		_dumper.set_file( _file );
	} 
	else if( option == "set" )
	{ 
		_read_mode = Read::Mode::ToFrom; 
		
		convert << argv[ 3 ];
		convert >> _start;
		convert.clear(); 
		
		convert << argv[ 4 ];
		convert >> _end;
		convert.clear(); 
		
		_file = argv[ 5 ];
		_dumper.set_read_mode( _start, _end );
		_dumper.set_output_mode( _out_mode );
		_dumper.set_file( _file );
	}
	else { return 0; }
	

	_dumper.dump();
	
	
    return 0;
}

void usage()
{
	std::cout << "\nUsage: dump [output mode] [read mode] <file>" << std::endl << std::endl;
	std::cout << "Displays file contents in hexadecimal, decimal, octal, or ASCII." << std::endl << std::endl;
	std::cout << "Options:" << std::endl << std::endl;
	std::cout << "    Output Mode:" << std::endl << std::endl;
	std::cout << "      oct      -  Displays the output in octal." << std::endl;
	std::cout << "      dec      -  Displays the output in decimal." << std::endl;
	std::cout << "      hex      -  Displays the output in hexadecimal." << std::endl;
	std::cout << "      ascii    -  Displays the output in ascii." << std::endl << std::endl;
	std::cout << "    Read Mode:" << std::endl << std::endl;
	std::cout << "      all      -  Reads the entire file." << std::endl;
	std::cout << "      length   -  Reads from the beginning of the file to the position specified by this option." << std::endl;
	std::cout << "      set      -  Defines where to start and where to finish reading the file." << std::endl << std::endl;
	std::cout << "    Common:" << std::endl << std::endl;
	std::cout << "      help     -  Displays this help." << std::endl;
	std::cout << "      size     -  Displays the file size." << std::endl;
	std::cout << "      examples -  Displays more detailed ways of how to use the dumper" << std::endl; 
	std::cout << "      version  -  Displays dumper version." << std::endl << std::endl;
		
}

void examples()
{
	std::cout << "\nExamples:" << std::endl;
	std::cout << "\tdumper hex all <file>         -  Reads the entire file." << std::endl;
	std::cout << "\tdumper hex length 42 <file>   -  Reads from the beginning of the file to the position 42." << std::endl;
	std::cout << "\tdumper hex set 42 1000 <file> -  Reads from the position 42 of the file, to the 1000 position." << std::endl << std::endl;
}



