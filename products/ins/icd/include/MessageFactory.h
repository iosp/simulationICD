#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

/*
* MessageFactory.h
* 
* Author: Binyamin Appelbaum
* Date: 28.02.18
*/

enum InsMsgType { _STATUS_MSG_, _NAVIGATION_DATA_MSG_, _ERROR_ESTIMATION_MSG, _INTERNAL_GPS_MSG, _ECHO_MSG_};

class InsMessage;

class MessageFactory {

public:
	static InsMessage* CreateMessage(InsMsgType msgType, int hertz);
};

#endif // MESSAGEFACTORY_H