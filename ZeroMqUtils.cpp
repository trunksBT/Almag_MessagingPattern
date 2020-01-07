#include "ZeroMqUtils.hpp"

std::string s_recv (zmq::socket_t & socket) {

   zmq::message_t message;
   socket.recv(message, zmq::recv_flags::none);
   return std::string(static_cast<char*>(message.data()), message.size());
}

bool s_send (zmq::socket_t & socket, const std::string & string,
             zmq::send_flags flags) {

   zmq::message_t message(string.size());
   memcpy (message.data(), string.data(), string.size());
   const auto retCode = socket.send (message, flags);
   return retCode.has_value();
}
