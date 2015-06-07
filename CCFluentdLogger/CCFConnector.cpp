//
//  CCFConnector.cpp
//  CCFluentdLogger
//
//  Created by giginet on 6/6/15.
//
//

#include "CCFConnector.h"

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
    _host = host;
    _port = port;
    return true;
}

bool Connector::post(ccFluentdLogger::Log *log, const cocos2d::network::ccHttpRequestCallback &callback)
{
    using namespace cocos2d::network;
    auto request = new HttpRequest();
    std::string url = this->getEndPoint(log->getTag().c_str());
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::POST);
    auto dumped = log->dump().c_str();
    request->setRequestData(dumped, strlen(dumped));
    request->setResponseCallback(callback);
    
    auto client = HttpClient::getInstance();
    client->enableCookies(NULL);
    client->send(request);
    
    request->release();
    return true;
}

std::string Connector::getEndPoint(const char *tag)
{
    return cocos2d::StringUtils::format("%s:%d/%s", _host.c_str(), _port, tag);
}

NS_LOGGER_END