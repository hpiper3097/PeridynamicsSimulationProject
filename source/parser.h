#pragma once

#include <fstream>
#include <string>
#include <iostream>

#define DEFAULT "../config.dat"

class Parser
{
	private:
		std::ifstream input;
		double _K, _Kic, _T, _dT, _delta;

		void init();
		void init( std::string path );

		void process();
	public:
		Parser();
		Parser( std::string path );

		void print();

		inline auto K() { return _K; }
		inline auto Kic() { return _Kic; }
		inline auto T() { return _T; }
		inline auto dT() { return _dT; }
		inline auto delta() { return _delta; }
};
