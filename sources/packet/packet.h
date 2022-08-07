//
// Created by marmelade on 07/08/22.
//

#ifndef WIREFISH_PACKET_H
#define WIREFISH_PACKET_H

#include <cstring>
#include <cstdint>

#include <variant>

#include <string>
#include <sstream>

#include <arpa/inet.h>

#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

namespace wirefish::packet {

    class Packet {
    public:
        Packet();
        Packet(const Packet &other)=delete;
        Packet(Packet &&other) noexcept;
        ~Packet();

        Packet &operator=(const Packet &other)=delete;
        Packet &operator=(Packet &&other) noexcept;

        void setRaw(const char *buffer, size_t length);
        void parse();

    private:
        void process_ethernet(std::stringstream &output);
        void process_ipv4(std::stringstream &output);
        void process_ipv6(std::stringstream &output);
        void process_udp(std::stringstream &output);
        void process_tcp(std::stringstream &output);

    private:
        char m_buffer[UINT16_MAX]{};
        size_t m_length{};

        struct ethhdr m_eth;
        std::variant<struct ip, struct ip6_hdr> ip;
        struct udphdr m_udp;
        struct tcphdr m_tcp;
    };

} // wirefish::packet

#endif //WIREFISH_PACKET_H
