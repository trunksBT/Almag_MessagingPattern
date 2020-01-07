#include "ZMqReqRespCommunicator.hpp"
#include <MessagingPattern/ZeroMqUtils.hpp>
#include <HDLC/HDLCFrameBodyInterpreter.hpp>
#include <Utils/Functions.hpp>
#include <Utils/Utils.hpp>
#include <Utils/PrintUtils.hpp>

using namespace convert;
using namespace printUtils;

ZMqReqRespCommunicator::ZMqReqRespCommunicator(zmq::socket_type messageType)
: ZMqCommunicator{messageType}
, tcpPortAddressHeader{"tcp://127.0.0.1:"}
, tcpPortAddress{defaultVals::FOR_STRING}
{
   LOG(trace);
}

ZMqReqRespCommunicator::~ZMqReqRespCommunicator()
{
   LOG(trace);
}

void ZMqReqRespCommunicator::setupSend(const std::string& address)
{
   tcpPortAddress = tcpPortAddressHeader + address;
   LOG(debug) << "on " << tcpPortAddress;
   socket_.connect(tcpPortAddress);
}

void ZMqReqRespCommunicator::setupReceive(const std::string& address)
{
   tcpPortAddress = tcpPortAddressHeader + address;
   LOG(debug) << "from " << tcpPortAddress;
   socket_.bind (tcpPortAddress);
}

bool ZMqReqRespCommunicator::send(const std::string &address, HDLCFrameBodyPtr frame)
{
   const std::string sentMessage = toString(frame->build());
   LOG(debug) << "Message: " << sentMessage;
   return s_send(socket_, sentMessage);
}

HDLCFramePtr ZMqReqRespCommunicator::receive(const std::string &address)
{
   std::string message = s_recv(socket_);
   auto recFrame{
      std::make_shared<HDLCFrame>(HDLCFrameBodyInterpreter().apply(message)) };
   printFrame("Received Message: ", recFrame->build());
   return recFrame;
}
