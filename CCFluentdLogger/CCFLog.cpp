//
//  CCFLog.cpp
//  CCFluentdLogger
//
//  Created by giginet on 6/6/15.
//
//

#include "CCFLog.h"

NS_LOGGER_BEGIN

Log* Log::create(const char *tag, json11::Json json)
{
    Log *log = new Log(tag, json);
    if (log) {
        log->autorelease();
        return log;
    }
    CC_SAFE_DELETE(log);
    return nullptr;
}

Log::Log(const char* tag, json11::Json json)
: _tag(tag)
, _timestamp(time(0))
, _json(json)
{
    _json = json;
}

Log::~Log()
{
}

bool Log::init()
{
    return true;
}

std::string Log::dump()
{
    auto dumped = _json.dump();
    return cocos2d::StringUtils::format("json=%s", dumped.c_str());
}

NS_LOGGER_END