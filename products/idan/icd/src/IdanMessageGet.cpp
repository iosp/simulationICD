/*
* IdanMessageGet.cpp
* IDAN message to get
* Author: Binyamin Appelbaum
* Date: 27.03.18
*/

#include "IdanMessageGet.h"
#include "LoggerProxy.h"

IdanMessageGet::IdanMessageGet(float hertz) {
	m_sleepTimeBetweenEverySend = (hertz != 0 ) ? (1e5 / hertz) : 0;  // reduce time to sleep, in order to get all the messages
}