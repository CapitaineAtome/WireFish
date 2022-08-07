//
// Created by marmelade on 07/08/22.
//

#ifndef WIREFISH_PACKET_H
#define WIREFISH_PACKET_H


#include <cstring>
#include <cstdint>

namespace wirefish::net {

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
        void process_ethernet();
        void process_ipv4();
        void process_ipv6();
        void process_udp();
        void process_tcp();

    private:
        char m_buffer[UINT16_MAX]{};
    };

}

#endif //WIREFISH_PACKET_H
