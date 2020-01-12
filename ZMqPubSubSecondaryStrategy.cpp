#include "ZMqPubSubSecondaryStrategy.hpp"
#include <MessagingPattern/ZeroMqUtils.hpp>
#include <HDLC/HDLCFrameBodyInterpreter.hpp>
#include <Utils/Functions.hpp>

using namespace convert;

ZMqPubSubSecondaryStrategy::ZMqPubSubSecondaryStrategy(zmq::socket_type messageType)
   : ZMqCommunicator{messageType}
{
   LOG(trace);
}

ZMqPubSubSecondaryStrategy::~ZMqPubSubSecondaryStrategy()
{
   LOG(trace);
}

void ZMqPubSubSecondaryStrategy::setupSend(const std::string& address)
{
   throw std::runtime_error("Redundant function");
}

void ZMqPubSubSecondaryStrategy::setupReceive(const std::string& address)
{
   tcpPortAddress = tcpPortAddressHeader + address;
   LOG(debug) << "from " << tcpPortAddress;
   socket_.connect(tcpPortAddress);
   socket_.setsockopt(ZMQ_SUBSCRIBE, "dupa", true);
}

bool ZMqPubSubSecondaryStrategy::send(const std::string &address, HDLCFrameBodyPtr frame)
{
   throw std::runtime_error("Redundant function");
}

HDLCFramePtr ZMqPubSubSecondaryStrategy::receive(const std::string &address)
{
   s_recv(socket_);
   std::string message = s_recv(socket_);
   auto recFrame{
           std::make_shared<HDLCFrame>(HDLCFrameBodyInterpreter().apply(message)) };
   LOG(debug) << toString("Received Message: ", recFrame->build());
   return recFrame;
}

HDLCFramePtr ZMqPubSubSecondaryStrategy::communicate(const std::string& address, HDLCFrameBodyPtr frame)
{
   LOG(info) << "Established 9.6 kbps";
   return nullptr;
}
