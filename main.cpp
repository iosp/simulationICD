/**
* main.cpp
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/

#include "Tester.h"
#include "LoggerProxy.h"
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>

int main() {
    std::stringstream ss;
    ss << "********************* starting " << __FILE__ << ". Time: " << boost::posix_time::microsec_clock::local_time() << " ******************" << std::endl;
    ALWLOG << ss.str();

    Tester t;

    ss.str("");
    ss << "********************* Ending " << __FILE__ << ". Time: " << boost::posix_time::microsec_clock::local_time() << std::endl;
    ALWLOG << ss.str();
}