//
// Created by marmelade on 07/08/22.
//

#include <iostream>

#include "net/interface.h"
#include "net/device.h"
#include "protocol/ethernet.h"
#include "protocol/ipv4.h"
#include "protocol/ipv6.h"

int main() {

    const size_t nbr_captures{10};
    std::string _buffer_string;

    auto capture_device{wirefish::net::Device("wlo1")};
    auto packet{wirefish::packet::Packet()};

    for(size_t i{0}; i < nbr_captures; i++) {

        if(capture_device.capture(packet) != wirefish::net::Device::DevError::NO_ERROR) {

            continue;
        }

        if(packet.GetEthernet().has_value()) {

            char _eth_addr_buffer[ETH_ALEN];
            wirefish::protocol::Ethernet _eth_proto{packet.GetEthernet().value()};

            std::cout << "Ethernet Frame:\n" << std::endl;

            if(!_eth_proto.SourceAddress(_eth_addr_buffer, ETH_ALEN)) {

                std::cout << std::hex << std::uppercase
                          << "\tSource Address: "
                          << static_cast<int16_t>(_eth_addr_buffer[0]) << ":" << static_cast<int16_t>(_eth_addr_buffer[1]) << ":" << static_cast<int16_t>(_eth_addr_buffer[2]) << ":"
                          << static_cast<int16_t>(_eth_addr_buffer[3]) << ":" << static_cast<int16_t>(_eth_addr_buffer[4]) << ":" << static_cast<int16_t>(_eth_addr_buffer[5])
                          << std::endl;
            }


            if(!_eth_proto.DestinationAddress(_eth_addr_buffer, ETH_ALEN)) {

                std::cout << std::hex << std::uppercase
                          << "\tSource Address: "
                          << static_cast<int16_t>(_eth_addr_buffer[0]) << ":" << static_cast<int16_t>(_eth_addr_buffer[1]) << ":" << static_cast<int16_t>(_eth_addr_buffer[2]) << ":"
                          << static_cast<int16_t>(_eth_addr_buffer[3]) << ":" << static_cast<int16_t>(_eth_addr_buffer[4]) << ":" << static_cast<int16_t>(_eth_addr_buffer[5])
                          << std::endl;
            }


            std::cout
                    << "\tIP Protocol: IPv" << (_eth_proto.IsIPv4() ? "4" : "6")
                    << "\n";
        } else {

            std::cout << "Couldn't find " << std::endl;
        }

        std::cout << "-------------------------------------" << std::endl;

    }

    return 0;
}