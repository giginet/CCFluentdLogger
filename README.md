# CCFluentdLogger

This is the cocos2d-x plugin to allow sending logs to fluentd easily.

## Requirements

- cocos2d-x 3.0+

## Setup server

You must launch a fluentd endpoint on local or remote.

You can launch local fluentd server in the following way.

### Setup

```sh
$ git clone https://github.com:giginet/CCFluentdLogger.git
$ cd CCFluentdLogger/fluentd
```

### Launch

```sh
$ bundle install
$ bundle exec foreman start
```

Then fluentd runs on `http://127.0.0.1:8888`

## Implement log collecting logic in your Game

Import all h/cpp files under `CCFluentdLogger/` into your project.

And register configuration to the logger.

Typically, you should implement the following logic on `AppDelegate::applicationDidFinishLaunching`.

```cpp
#include "CCFluentdLogger.h"
using namespace ccFluentdLogger;

bool AppDelegate::applicationDidFinishLaunching() {
    // Get shared logger instance
    Logger * logger = Logger::getInstance();
    
    // Get default logger settings
    Configuration config = Logger::getDefaultConfiguration();
    config.host = "http://127.0.0.1";
    config.port = 8888;

    // Set configuration
    logger->setConfiguration(config);
}
```

Implement this snippets to post logs.

```cpp
#include "CCFluentdLogger.h"
using namespace ccFluentdLogger;

void onButtonPressed()
{
    // Something to do

    // Get shared logger instance
    Logger * logger = Logger::getInstance();
    
    // Post log
    logger->postLog("action", json11::Json::object {{"key", "value"}});
}
```

These are all to do to post logs to the remote host.

## Buffering

On above way, Logs are sent sequentially.

This plugin also allows to store logs and post them on specific timings like the game is end.

To buffer the logs, you should execute `Logger::postLog` with third-argument, execute `Logger::postBuffered` to send all buffered logs.


```cpp
#include "CCFluentdLogger.h"
using namespace ccFluentdLogger;

void onButtonPressed()
{
    // Something to do

    // Get shared logger instance
    Logger * logger = Logger::getInstance();
    
    // Add log to buffer
    // Third argument indicates whether to enable buffering or not
    logger->postLog("action", json11::Json::object {{"key", "value"}}, true);
}

void onGameOver()
{
    Logger * logger = Logger::getInstance();

    // Post all buffered logs at one time.
    logger->postBuffered();
}
```

You can set default `postLog` behavior with `Configuration.isBufferingEnabled`.

## Author

giginet <giginet.net@gmail.com>

## License

MIT License
