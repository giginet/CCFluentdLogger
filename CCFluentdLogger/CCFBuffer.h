//
//  CCFBuffer.h
//  CCFluentdLogger
//
//  Created by koki-miki on 2015/06/07.
//
//

#ifndef __CCFluentdLogger__CCFBuffer__
#define __CCFluentdLogger__CCFBuffer__

#include "cocos2d.h"
#include "CCFluentdMacros.h"
#include "CCFLog.h"

NS_LOGGER_BEGIN

typedef cocos2d::Vector<Log *> LogVector;

class Buffer :public cocos2d::Ref {
CC_CONSTRUCTOR_ACCESS:
    bool init();
public:
    bool addLog(Log *log);
    void removeLog(Log * log);
    void flush();
    CC_SYNTHESIZE_PASS_BY_REF(LogVector, _logs, Logs);
    CREATE_FUNC(Buffer);
};

NS_LOGGER_END;

#endif /* defined(__CCFluentdLogger__CCFBuffer__) */
