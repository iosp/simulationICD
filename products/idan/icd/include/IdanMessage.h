#ifndef IDANMESSAGE_H
#define IDANMESSAGE_H

/*
* IdanMessage.h
* IDAN message
* Author: Binyamin Appelbaum
* Date: 20.03.18
*/

#include "IMessage.h"
#include <stdint.h> // uins32_t
#include <map>

typedef uint32_t t_msgID;
class IdanData;

class IdanMessage : public IMessage<IdanData>{
protected:
	// get appropriate val from m by the key
	template <class T, class U>
	U GetValFromMap(const std::map<T, U>& m, const T& key, const U& defVal) const {
		auto it = m.find(key);
		auto val = (it != m.end() ? it->second : defVal);
		return val;
	}
public:
	IdanMessage(int hertz);

	virtual ~IdanMessage() = default;

	virtual t_msgID GetMsgID() const = 0;

};

#endif // IDANMESSAGE_H