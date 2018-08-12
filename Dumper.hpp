/*
	Dumper.hpp

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

#ifndef DUMPER_HPP
#define DUMPER_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>

#include "Mode.hpp"

class Dumper
{
public:
	Dumper();
	virtual ~Dumper();
	
	void set_file( const std::string& _file );
	void set_output_mode( const Dump::Mode& _mode );
	void set_read_mode();
	void set_read_mode( const size_t& _until );
	void set_read_mode( const size_t& _start,  const size_t& _end );
	void dump();
	const std::string version() const;
	std::streamsize get_size( const std::string& path );		
	
private:
	std::string m_version;
	std::string m_file;
	std::streamsize m_size;
	std::fstream fs;
		
	Read::Mode m_rmode;
	Dump::Mode m_dmode;
	
	size_t m_end;
	size_t m_start;
	 
	size_t m_line;
	size_t m_col;
};

#endif /*DUMPER_HPP*/




