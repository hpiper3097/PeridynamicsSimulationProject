#include "parser.h"

Parser::Parser()
{
	init();
	process();
}

Parser::Parser( std::string path )
{
	init( path );
	process();
}

void Parser::init()
{
	input.open( DEFAULT );
}

void Parser::init( std::string path )
{
	input.open( path );
}

void Parser::process() 
{ 
	while (	input >> _K >>_Kic >> _T >> _T >> _dT >> _delta ) {}
}

void Parser::print()
{
	std::cout << K() << " " << Kic() << " " << T() << " " << dT() << " " << delta() << std::endl;
}




