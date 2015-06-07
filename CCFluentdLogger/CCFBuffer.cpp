//
//  CCFBuffer.cpp
//  CCFluentdLogger
//
//  Created by koki-miki on 2015/06/07.
//
//

#include "CCFBuffer.h"

NS_LOGGER_BEGIN

bool Buffer::init()
{
    return true;
}

bool Buffer::addBuffer(Log * log)
{
    _logs.pushBack(log);
    return true;
}

void Buffer::flush()
{
    _logs.clear();
}

void Buffer::removeLog(Log * log)
{
    _logs.eraseObject(log);
}

NS_LOGGER_END