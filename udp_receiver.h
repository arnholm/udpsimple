#ifndef UDP_RECEIVER_H
#define UDP_RECEIVER_H

#include "udp_config.h"

#include <iostream>
#include <string>
#include <memory>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include "udp_consumer.h"

/*
// Example use

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
*/

// udp_receiver receives asynchronous UDP messages on a local port in an eternal loop
// and forwards the data to an udp_consumer
class udp_receiver {
public:
   udp_receiver(int udp_port = 10253)
   : m_udp_port(udp_port)
   , m_socket(m_io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), udp_port))
   { }

   void receive(std::shared_ptr<udp_consumer> consumer = nullptr)
   {
      m_consumer = consumer;

      // prepare for first async read
      start_receive();

      // run forever, handle_receive will be called as data come in
      m_io_context.run();
   }

   virtual ~udp_receiver()
   {
      m_socket.close();
   }

private:
  void start_receive()
   {
      // schedule the next asynchronous read
      m_socket.async_receive_from(
         boost::asio::buffer(m_recv_buffer), m_sender_endpoint,
         boost::bind(&udp_receiver::handle_receive, this,
         boost::asio::placeholders::error,
         boost::asio::placeholders::bytes_transferred));
   }

   void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
   {
      if (!error) {
         if(m_consumer.get()) {
            // forward message data to consumer
            m_consumer->consume(&m_recv_buffer[0],bytes_transferred);
         }
         else {
            std::cout << "Received: " << std::string(m_recv_buffer.begin(), m_recv_buffer.begin()+bytes_transferred) << std::endl;
         }

         // prepare for next async read
         start_receive();
      }
      else {
         std::cout << "Receive failed: " << error.message()  << std::endl;
      }
   }

private:
   boost::asio::io_context             m_io_context;
   boost::asio::ip::udp::socket        m_socket;           // socket used for communication
   int                                 m_udp_port;         // local UDP port (on receiving end)
   boost::asio::ip::udp::endpoint      m_sender_endpoint;  // sender endpoint can be anything
   boost::array<unsigned char, 1024>   m_recv_buffer;      // receive buffer of max 1024 bytes
   std::shared_ptr<udp_consumer>       m_consumer;         // messages are delegated to the consumer
};

#endif // UDP_RECEIVER_H


