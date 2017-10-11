#include "stdafx.h"
#include "Installer.h"
#include <sstream>

const char space()
{
	return ' ';
}

stringstream& space__(stringstream& stream)
{
	stream << ' ';
	return stream;
}

Function(Test_stringstream)
{
	{
		stringstream stream;
		stream << 5;
		AssertTrue(stream.str() == "5");
	}
	
	{
		stringstream stream;
		stream << space();
		AssertTrue(stream.str() == " ");
	}

	{
		stringstream stream;
		stream << space;
		AssertTrue(stream.str() != " ");
	}

}