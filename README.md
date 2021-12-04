# udpsimple
Simple UDP send/receive C++ header only library using boost

## udp_sender example
```cpp
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "udp_sender.h"

int main()
{
   // send message to 127.0.0.1 port 10253
   udp_sender udp("127.0.0.1", 10253);

   // just loop and send a message every second forever
   size_t counter=0;
   while(true) {
      udp.send("udp_sender " + std::to_string(++counter));
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   }
}
```


## udp_receiver example

Derive from udp_consumer to customize handling of received messages
```cpp
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "udp_receiver.h.h"
#include "udp_consumer.h"

int main()
{
   // receive messages on local port 10253
   udp_receiver udp(10253);

   // receive multiple messages
   udp.receive(std::make_shared<udp_consumer>());
}
```
