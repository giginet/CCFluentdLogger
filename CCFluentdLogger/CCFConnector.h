//
//  CCFConnector.h
//  CCFluentdLogger
//
//  Created by giginet on 6/6/15.
//
//

#include "CCFluentdMacros.h"
#include "cocos2d.h"
#include "network/HttpClient.h"

#include "CCFLog.h"

#ifndef __CCFluentdLogger__CCFConnector__
#define __CCFluentdLogger__CCFConnector__

NS_LOGGER_BEGIN

class Connector :public cocos2d::Ref {
CC_CONSTRUCTOR_ACCESS:
    bool init(const char* host, int port);
    Connector();
    virtual ~Connector();
private:
    CC_SYNTHESIZE(std::string, _host, Host);
    CC_SYNTHESIZE(int, _port, Port);
    std::string getEndPoint(const char* tag);
public:
    static Connector* create(const char* host, int port);
    bool post(Log* log, const cocos2d::network::ccHttpRequestCallback& callback);
};

NS_LOGGER_END

#endif /* defined(__CCFluentdLogger__CCFConnector__) */
