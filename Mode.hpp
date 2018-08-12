/*
	Modes.hpp - Read/Dump modes

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

#ifndef MODES_HPP
#define MODES_HPP

namespace Dump
{
	enum class Mode
	{
		Octal		 = 0x08,
		Decimal 	 = 0x0A,
		Hexadecimal  = 0x10,
		ASCII	 	 = 0x11,
	};
}

namespace Read
{
	enum class Mode
	{
		Total		= 0x2A,
		Until		= 0x2B,
		ToFrom		= 0x2C,
	};
}

#endif /*MODES_HPP*/




