#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// T must have << operator defined!!!
template <typename T>
class IO
{
    private:
        std::string _fname;

    public:
        IO()
            : _fname("")
        {
            //
        }

        IO( std::string fname )
            : _fname(fname)
        {
            //
        }

        /*
        *   @brief Write a vector of vectors elements to a CSV file.
        *   @param cont The container of containers which will be converted into a CSV file.
        *   With the outer and inner containers must have constant iterator methods cbegin() and
        *   cend() defined.
        *   @return True if the operation is successful; false otherwise.
        ***************************************************************************/
        bool write2DArrayToCSV( std::vector<std::vector<T>> cont)
        {
            std::ofstream oStr( _fname );
            if (!oStr.is_open())
                return false;
            for( auto outerItr = cont.cbegin(); outerItr != cont.cend(); outerItr++)
            {
                for( auto innerItr = outerItr->cbegin(); innerItr != outerItr->cend(); innerItr++)
                {
                    oStr << *innerItr << ',';
                }
                oStr << '\n';
            }
            oStr.close();
            return true;
        }
};