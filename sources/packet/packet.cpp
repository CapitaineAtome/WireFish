//
// Created by marmelade on 07/08/22.
//

#include "packet.h"

#include <algorithm>

namespace wirefish::net {

    Packet::Packet() : m_buffer{} {

    }

    Packet::Packet(Packet &&other) noexcept {

        if(this == &other) {

            return ;
        }

        size_t _max_byte_to_copy{std::min(sizeof(m_buffer) / sizeof(*m_buffer),
                                          sizeof(other.m_buffer) / sizeof(*other.m_buffer))};
        memcpy(m_buffer, other.m_buffer, _max_byte_to_copy);

        memset(other.m_buffer, 0, sizeof(other.m_buffer) / sizeof(other.m_buffer[0]));


    }

    Packet::~Packet()=default;


    Packet &Packet::operator=(Packet &&other) noexcept {

        if(this == &other) {

            return *this;
        }

        return *this;
    }

    void inline Packet::setRaw(const char *buffer, const size_t length) {

        size_t _nbr_bytes_copy{std::min(sizeof(m_buffer) / sizeof(*m_buffer) - 1U,
                                        length - 1U)};

        memcpy(m_buffer, buffer, _nbr_bytes_copy);

        m_buffer[sizeof(m_buffer) / sizeof(*m_buffer) - 1] = '\0';
    }

    void Packet::parse() {

    }

    // PRIVATE Functions
    void Packet::process_ethernet() {

    }

    void Packet::process_ipv4() {

    }

    void Packet::process_ipv6() {

    }

    void Packet::process_udp() {

    }

    void Packet::process_tcp() {

    }


}