#include "ZMqPubSubSecondaryStrategy.hpp"
#include <MessagingPattern/ZeroMqUtils.hpp>
#include <HDLC/HDLCFrameBodyInterpreter.hpp>
#include <Utils/Functions.hpp>
#include <Utils/Utils.hpp>
#include <Utils/PrintUtils.hpp>

using namespace convert;
using namespace printUtils;

ZMqPubSubSecondaryStrategy::ZMqPubSubSecondaryStrategy(zmq::socket_type messageType)
        : ZMqCommunicator{messageType}
        , tcpPortAddressHeader{"tcp://127.0.0.1:"}
        , tcpPortAddress{defaultVals::FOR_STRING}
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
   socket_.bind (tcpPortAddress);
   socket_.connect(address);
   socket_.setsockopt(ZMQ_SUBSCRIBE, address.data(), true);
}

bool ZMqPubSubSecondaryStrategy::send(const std::string &address, HDLCFrameBodyPtr frame)
{
   throw std::runtime_error("Redundant function");
}

HDLCFramePtr ZMqPubSubSecondaryStrategy::receive(const std::string &address)
{
   std::string message = s_recv(socket_);
   auto recFrame{
           std::make_shared<HDLCFrame>(HDLCFrameBodyInterpreter().apply(message)) };
   printFrame("Received Message: ", recFrame->build());
   return recFrame;
}

HDLCFramePtr ZMqPubSubSecondaryStrategy::communicate(const std::string& address, HDLCFrameBodyPtr frame)
{
   LOG(info) << "Established 9.6 kbps";
   return nullptr;
}
