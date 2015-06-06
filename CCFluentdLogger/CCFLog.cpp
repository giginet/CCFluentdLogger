//
//  CCFLog.cpp
//  CCFluentdLogger
//
//  Created by giginet on 6/6/15.
//
//

#include "CCFLog.h"

Log::Log()
: _tag(0)
, _timestamp(time(0))
{
}

Log::~Log()
{
    _userInfo.clear();
}

bool Log::init()
{
    return true;
}