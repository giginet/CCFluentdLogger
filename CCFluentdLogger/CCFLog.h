//
//  CCFLog.h
//  CCFluentdLogger
//
//  Created by giginet on 6/6/15.
//
//

#include "cocos2d.h"
#include "CCFluentdMacros.h"

#ifndef __CCFluentdLogger__CCFLog__
#define __CCFluentdLogger__CCFLog__

#define LogDict cocos2d::Map<std::string, cocos2d::Value>

class Log :public cocos2d::Ref {
CC_CONSTRUCTOR_ACCESS:
    Log();
    virtual ~Log();
    bool init();
public:
    CC_SYNTHESIZE(std::string, _tag, Tag);
    CC_SYNTHESIZE(LogDict, _userInfo, UserInfo);
    CC_SYNTHESIZE_READONLY(time_t, _timestamp, TimeStamp);
    CREATE_FUNC(Log);
};

#endif /* defined(__CCFluentdLogger__CCFLog__) */
