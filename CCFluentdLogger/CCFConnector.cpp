//
//  CCFConnector.cpp
//  CCFluentdLogger
//
//  Created by giginet on 6/6/15.
//
//

#include "CCFConnector.h"
#include "network/HttpClient.h"

NS_LOGGER_BEGIN

Connector* Connector::create(const char *host, int port)
{
    Connector* connector = new Connector();
    if (connector && connector->init(host, port)) {
        connector->autorelease();
        return connector;
    }
    CC_SAFE_DELETE(connector);
    return nullptr;
}

Connector::Connector()
: _port(0)
, _host("")
{
}

Connector::~Connector()
{
    
}

bool Connector::init(const char *host, int port)
{
    return true;
}

bool Connector::post(ccFluentdLogger::Log *log)
{
    using namespace cocos2d::network;
    auto request = new HttpRequest();
    std::string url = this->getEndPoint(log->getTag().c_str());
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::POST);
    request->setResponseCallback([this](HttpClient* client, HttpResponse* response){
        if (response->isSucceed()) {
            cocos2d::log("Succeed");
        } else {
            cocos2d::log("Failure");
        }
    });
    
    auto client = HttpClient::getInstance();
    client->enableCookies(NULL);
    client->send(request);
    return true;
}

std::string Connector::getEndPoint(const char *tag)
{
    return cocos2d::StringUtils::format("%s:%d/%s", _host.c_str(), _port, tag);
}

NS_LOGGER_END