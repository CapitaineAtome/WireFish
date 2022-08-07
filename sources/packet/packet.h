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
    };

} // wirefish::packet

#endif //WIREFISH_PACKET_H
