#pragma once

#include <MessagingPattern/ZMqCommunicator.hpp>

class ZMqPubSubCommunicator final: public ZMqCommunicator
{
public:
   ZMqPubSubCommunicator(zmq::socket_type messageType);
   virtual ~ZMqPubSubCommunicator();

   void setupSend(const std::string& address) override;
   void setupReceive(const std::string& address) override;
   bool send(const std::string &address, HDLCFrameBodyPtr frame) override;
   HDLCFramePtr receive(const std::string &address) override;
};
