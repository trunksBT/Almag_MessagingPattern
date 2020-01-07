#pragma once

#include <TestUtils/HDLC/DataLinkLayerCommunicators/ZMqCommunicator.hpp>

class ZMqReqRespCommunicator final: public ZMqCommunicator
{
public:
   ZMqReqRespCommunicator(zmq::socket_type messageType);
   bool send(const std::string &address, const HDLCFrameBodyPtr frame) override;
   HDLCFramePtr receive(const std::string &address) override;
   virtual ~ZMqReqRespCommunicator();

private:
   const std::string tcpPortAddressHeader;
   std::string tcpPortAddress;
};
