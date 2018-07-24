/**
* main.cpp
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/

#include "Tester.h"
#include "LoggerProxy.h"
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>

int main(int argc, char* argv[]) {
    std::stringstream ss;
    ss << "********************* starting " << argv[0] << ". Time: " << boost::posix_time::microsec_clock::local_time() << " ******************" << std::endl;
    ALWLOG << ss.str();

    Tester t;

    ss.str("");
    ss << "********************* Ending " << argv[0] << ". Time: " << boost::posix_time::microsec_clock::local_time() << std::endl;
    ALWLOG << ss.str();
}