/*
* IdanMessageGet.cpp
* IDAN message to get
* Author: Binyamin Appelbaum
* Date: 27.03.18
*/

#include "IdanMessageGet.h"
#include "LoggerProxy.h"

IdanMessageGet::IdanMessageGet(int hertz) {
	if (hertz == 0) {
		ERRLOG << "Invalid hertz argument for IDAN message\n";
		return;
	}
	m_sleepTimeBetweenEverySend = 1e6 / (hertz * 10);
}