//
//  CCFLog.h
//  CCFluentdLogger
//
//  Created by giginet on 6/6/15.
//
//

#include "cocos2d.h"
#include "CCFluentdMacros.h"
#include "json11.hpp"

#ifndef __CCFluentdLogger__CCFLog__
#define __CCFluentdLogger__CCFLog__

NS_LOGGER_BEGIN

//#define LogDict cocos2d::Map<std::string, cocos2d::Value>

class Log :public cocos2d::Ref {
CC_CONSTRUCTOR_ACCESS:
    Log(const char* tag, json11::Json);
    virtual ~Log();
    bool init();
private:
    json11::Json _json;
public:
    static Log* create(const char* tag, json11::Json json);
    std::string dump();
    CC_SYNTHESIZE(std::string, _tag, Tag);
    CC_SYNTHESIZE_READONLY(time_t, _timestamp, TimeStamp);
};

NS_LOGGER_END

#endif /* defined(__CCFluentdLogger__CCFLog__) */
