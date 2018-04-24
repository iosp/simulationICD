/*
* IdanMessageGet.cpp
* IDAN message to get
* Author: Binyamin Appelbaum
* Date: 27.03.18
*/

#include "IdanMessageGet.h"
#include "LoggerProxy.h"

IdanMessageGet::IdanMessageGet(float hertz) : IdanMessage(hertz) {
	m_sleepTimeBetweenEverySend /= 10; // reduce time to sleep, in order to get all the messages
}