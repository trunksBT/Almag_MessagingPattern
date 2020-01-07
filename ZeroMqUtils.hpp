#pragma once

#include <zmq.hpp>
#include <string>

std::string s_recv (zmq::socket_t & socket);
bool s_send (zmq::socket_t & socket, const std::string & string,
             zmq::send_flags flags=zmq::send_flags::none);
