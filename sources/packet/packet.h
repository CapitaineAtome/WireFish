//
// Created by marmelade on 07/08/22.
//

#ifndef WIREFISH_PACKET_H
#define WIREFISH_PACKET_H

#include <cstring>
#include <cstdint>

#include <optional>

#include <string>
#include <sstream>

#include "../protocol/ethernet.h"
#include "../protocol/ipv4.h"
#include "../protocol/ipv6.h"
#include "../protocol/tcp.h"
#include "../protocol/udp.h"

namespace wirefish::packet {

    class Packet {
    public:

        enum class PacketType {
            ETHERNET,
            IPV4,
            IPV6,
            TCP,
            UDP,
        };

        Packet();
        Packet(const Packet &other)=delete;
        Packet(Packet &&other) noexcept;
        ~Packet();

        Packet &operator=(const Packet &other)=delete;
        Packet &operator=(Packet &&other) noexcept;

        void setRaw(const char *buffer, size_t length);

        std::optional<protocol::Ethernet> GetEthernet();
        std::optional<protocol::IPv4> GetIPv4();
        std::optional<protocol::IPv6> GetIPv6();
        std::optional<protocol::TCP> GetTCP();
        std::optional<protocol::UDP> GetUDP();

        bool isOfType(PacketType type);

    private:
        void process_ethernet(std::stringstream &output);
        void process_ipv4(std::stringstream &output);
        void process_ipv6(std::stringstream &output);
        void process_udp(std::stringstream &output);
        void process_tcp(std::stringstream &output);

    private:
        char m_buffer[UINT16_MAX]{};
        size_t m_length{};
    };

} // wirefish::packet

#endif //WIREFISH_PACKET_H
