/*
	Dumper.cpp

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

#include "Dumper.hpp"

Dumper::Dumper() :
m_version( "Dumper version: 0.1.0" ),
m_file( "" ),
m_size( 0 ),
m_start( 0 ),
m_end( 0 ),
m_line( 0 ),
m_col( 0 ){}

Dumper::~Dumper(){}

void Dumper::set_file( const std::string& _file )
{
	m_size = get_size( _file );
	if( m_size > 0 ){ m_file = _file; }
	else 
	{ 
		std::cerr << "Dumper: error reading file. " << _file << std::endl; 
		std::exit( EXIT_FAILURE );
	}
}

void Dumper::set_output_mode( const Dump::Mode& _mode ){ m_dmode = _mode; }

void Dumper::set_read_mode()
{
	m_rmode = Read::Mode::Total;
	m_start = 0;
	m_end   = 0;
}

void Dumper::set_read_mode( const size_t& _until )
{
	m_rmode = Read::Mode::Until;
	m_start = 0;
	m_end   = _until;
	if( m_end == 0 )
	{
		std::cerr << "Dumper: the value must be larger than zero. " << std::endl; 
		std::exit( EXIT_FAILURE );
	}
}

void Dumper::set_read_mode( const size_t& _start,  const size_t& _end )
{
	m_rmode = Read::Mode::ToFrom;
	m_start = _start;
	m_end   = _end;
	
	if( m_start > m_end )
	{ 
		std::cerr << "Dumper: the 'end' must be larger than 'start'. " << std::endl;
		std::exit( EXIT_FAILURE );
	}
}

void Dumper::dump()
{	
	//In case of setter functions is not called, do this verification
	if( m_file.empty() || m_size == 0 ){ std::cerr << "Dumper: file is not defined. " << std::endl; }
	else if( m_end > m_size ){ std::cerr << "Dumper: the 'end' position is larger than the file size. " << std::endl; }
	else
	{			
		//Column info
		size_t aux = 0;
		char c;
		long long int ll_aux;
		
		fs.open ( m_file, std::ios_base::in | std::ios_base::binary );
		if( !fs.is_open() ){ std::cerr << "Dumper: read error" << std::endl; std::terminate(); }	
		else
		{
			std::cout << std::endl << "Dumping File: " << m_file << std::endl << std::endl;
			
			switch( static_cast<int>( m_rmode ) )
			{
				case static_cast<int>( Read::Mode::Total ) :
					while( !fs.eof() )
					{
						if( m_line == m_start )
						{ 
							std::cout <<" ["<< std::setfill( '0' ) << std::uppercase << std::hex << std::setw( 8 ) 
							<< m_line << "] - "; 
							
							m_line += 16;
						}
						if( m_col == 8 ){ std::cout << "  "; }						
						else if ( m_col == 16 )
						{ 
							std::cout << std::endl << " [" << std::setfill( '0' ) << std::uppercase << std::hex << std::setw( 8 ) 
							<< m_line << "] - "; 
							
							m_col = 0; 
							m_line += 16; 
						}
						 
						fs.get( c );
						ll_aux = static_cast<long long int>( c );
						if( ll_aux < 0 ){ ll_aux*= -1; }
						
						if( m_dmode == Dump::Mode::Octal )
						{
							std::cout << std::oct << std::setfill( '0' ) << std::setw( 4 ) <<  ll_aux  << ' '; 
						} 
						else if( m_dmode == Dump::Mode::Decimal )
						{
							std::cout << std::dec << std::setfill( '0' ) << std::setw( 4 ) <<  ll_aux  << ' '; 
						}
						else if( m_dmode == Dump::Mode::Hexadecimal )
					    {
					    	std::cout << std::uppercase << std::hex << std::setfill( '0' ) << std::setw( 4 ) <<  ll_aux  << ' '; 
					    }
						else if( m_dmode == Dump::Mode::ASCII ){
						
							if( static_cast<int>( c ) > 255  ||
								static_cast<int>( c ) == 127 || 
								static_cast<int>( c ) < 32  )
							{  
								std::cout << ". ";
							}
							else{ std::cout << c << ' '; }
						}
						m_col++; 
						
					}
					break;
				case static_cast<int>( Read::Mode::Until ):
					aux = 0;
					while( aux < m_end )
					{
						if( m_line == m_start )
						{ 
							std::cout << " [" << std::setfill( '0' ) << std::uppercase << std::hex << std::setw( 8 ) 
							<< m_line << "] - "; 
							
							m_line += 16;
						}
						if( m_col == 8 ){ std::cout << "  "; }
						else if ( m_col == 16 )
						{
							std::cout << std::endl << " [" << std::setfill( '0' ) << std::uppercase << std::hex << std::setw( 8 ) 
							<< m_line << "] - "; 
							
							m_col = 0; 
							m_line += 16;
						}
						
						fs.get( c );
						ll_aux = static_cast<long long int>( c );
						if( ll_aux < 0 ){ ll_aux*= -1; }
						
						if( m_dmode == Dump::Mode::Octal )
						{
							std::cout << std::oct << std::setfill( '0' ) << std::setw( 4 ) <<  ll_aux  << ' '; 
						} 
						else if( m_dmode == Dump::Mode::Decimal )
						{
							std::cout << std::dec << std::setfill( '0' ) << std::setw( 4 ) <<  ll_aux  << ' '; 
						}
						else if( m_dmode == Dump::Mode::Hexadecimal )
					    {
					    	std::cout << std::uppercase << std::hex << std::setfill( '0' ) << std::setw( 4 ) <<  ll_aux  << ' '; 
					    }
						else if( m_dmode == Dump::Mode::ASCII ){
						
							if( static_cast<int>( c ) > 255  ||
								static_cast<int>( c ) == 127 || 
								static_cast<int>( c ) < 32  )
							{  
								std::cout << ". ";
							}
							else{ std::cout << c << ' '; }
						}
						m_col++;						
						aux++;
					}
					break;
				case static_cast<int>( Read::Mode::ToFrom ):
					fs.seekg( m_start );
					aux = m_start;
					m_line = m_start;
					while( aux < m_end )
					{
						if( m_line == m_start )
						{ 
							std::cout << " [" << std::setfill( '0' ) << std::uppercase << std::hex << std::setw( 8 ) 
							<< m_line << "] - "; 
							
							m_line += 16;
						}
						if( m_col == 8 ){ std::cout << "  "; }
						else if ( m_col == 16 )
						{
							std::cout << std::endl << " [" << std::setfill( '0' ) << std::uppercase << std::hex << std::setw( 8 ) 
							<< m_line << "] - "; 
							
							m_col = 0; 
							m_line += 16;
						}
						
						fs.get( c );
						ll_aux = static_cast<long long int>( c );
						if( ll_aux < 0 ){ ll_aux*= -1; }
						
						if( m_dmode == Dump::Mode::Octal )
						{
							std::cout << std::oct << std::setfill( '0' ) << std::setw( 4 ) <<  ll_aux  << ' '; 
						} 
						else if( m_dmode == Dump::Mode::Decimal )
						{
							std::cout << std::dec << std::setfill( '0' ) << std::setw( 4 ) <<  ll_aux  << ' '; 
						}
						else if( m_dmode == Dump::Mode::Hexadecimal )
					    {
					    	std::cout << std::uppercase << std::hex << std::setfill( '0' ) << std::setw( 4 ) <<  ll_aux  << ' '; 
					    }
						else if( m_dmode == Dump::Mode::ASCII ){
						
							if( static_cast<int>( c ) > 255  ||
								static_cast<int>( c ) == 127 || 
								static_cast<int>( c ) < 32  )
							{  
								std::cout << ". ";
							}
							else{ std::cout << c << ' '; }
						}
						m_col++;						
						aux++;
					}
					break;
				default:
					std::cerr << "Dumper: read mode error (default)" << std::endl;
					std::exit( EXIT_FAILURE );
					break;
			}
		}
		std::cout << std::endl << std::endl;
	}
}

const std::string Dumper::version() const { return m_version; }

std::streamsize Dumper::get_size( const std::string& path )
{
	std::ifstream in;
	std::streamsize _size = 0;
	
	in.open( path, std::ios_base::binary );
	if( !in.is_open() ){ return _size; }
	in.ignore( std::numeric_limits< std::streamsize >::max() );
	_size = in.gcount();
	in.seekg( 0, std::ios_base::beg );
	
	return _size;
}


