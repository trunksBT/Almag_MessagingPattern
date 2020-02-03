#include "ZMqReqRepSecondaryStrategy.hpp"
#include <MessagingPattern/ZeroMqUtils.hpp>
#include <HDLC/HDLCFrameBodyInterpreter.hpp>
#include <Utils/Functions.hpp>

using namespace convert;

ZMqReqRepSecondaryStrategy::ZMqReqRepSecondaryStrategy(zmq::socket_type messageType)
   : ZMqCommunicator{messageType}
{
   LOG(trace);
}

ZMqReqRepSecondaryStrategy::~ZMqReqRepSecondaryStrategy()
{
   LOG(trace);
}

void ZMqReqRepSecondaryStrategy::setupSend(const std::string& address)
{
   throw std::runtime_error("Redundant function");
}

void ZMqReqRepSecondaryStrategy::setupReceive(const std::string& address)
{
   tcpPortAddress = tcpPortAddressHeader + address;
   LOG(info) << "from " << tcpPortAddress;
   socket_.bind (tcpPortAddress);
}

bool ZMqReqRepSecondaryStrategy::send(const std::string &address, HDLCFrameBodyPtr frame)
{
   const std::string sentMessage = toString(frame->build());
   LOG(info) << sentMessage;
   return s_send(socket_, sentMessage);
}

HDLCFramePtr ZMqReqRepSecondaryStrategy::receive(const std::string &address)
{
   std::string message = s_recv(socket_);
   auto recFrame{
           std::make_shared<HDLCFrame>(HDLCFrameBodyInterpreter().apply(message)) };
   LOG(info) << toString(recFrame->build());
   return recFrame;
}

HDLCFramePtr ZMqReqRepSecondaryStrategy::communicate(const std::string& address, HDLCFrameBodyPtr frame)
{
   LOG(debug);
   send(tcpPortAddress, frame);
   return nullptr;
}
