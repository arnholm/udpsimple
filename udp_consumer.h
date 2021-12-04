#ifndef UDP_CONSUMER_H
#define UDP_CONSUMER_H

#include <cstddef> // size_t
#include <memory>
#include <iostream>

// udp_consumer can be used to consume messages from the udp_receiver.
// derived classes can override consume() to do special message handling
class udp_consumer {
public:
   udp_consumer() {}
   virtual ~udp_consumer() {}

   // virtual method called by udp_receiver
   virtual void consume(const unsigned char* data, size_t bytes_transferred)
   {
      // default consumer implementation
      std::cout << "udp_consumer: " << std::string(data,data+bytes_transferred) << std::endl;
   }

};

#endif // UDP_CONSUMER_H
