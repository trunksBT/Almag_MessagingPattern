#include "ZMqReqRepSecondaryStrategy.hpp"
#include <MessagingPattern/ZeroMqUtils.hpp>
#include <HDLC/HDLCFrameBodyInterpreter.hpp>
#include <Utils/Functions.hpp>
#include <Utils/Utils.hpp>

using namespace convert;

ZMqReqRepSecondaryStrategy::ZMqReqRepSecondaryStrategy(zmq::socket_type messageType)
        : ZMqCommunicator{messageType}
        , tcpPortAddressHeader{"tcp://127.0.0.1:"}
        , tcpPortAddress{defaultVals::FOR_STRING}
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
   LOG(debug) << "from " << tcpPortAddress;
   socket_.bind (tcpPortAddress);
}

bool ZMqReqRepSecondaryStrategy::send(const std::string &address, HDLCFrameBodyPtr frame)
{
   const std::string sentMessage = toString(frame->build());
   LOG(debug) << "Message: " << sentMessage;
   return s_send(socket_, sentMessage);
}

HDLCFramePtr ZMqReqRepSecondaryStrategy::receive(const std::string &address)
{
   std::string message = s_recv(socket_);
   auto recFrame{
           std::make_shared<HDLCFrame>(HDLCFrameBodyInterpreter().apply(message)) };
   LOG(debug) << toString("Received Message: ", recFrame->build());
   return recFrame;
}

HDLCFramePtr ZMqReqRepSecondaryStrategy::communicate(const std::string& address, HDLCFrameBodyPtr frame)
{
   LOG(debug);
   send(tcpPortAddress, frame);
   return nullptr;
}
