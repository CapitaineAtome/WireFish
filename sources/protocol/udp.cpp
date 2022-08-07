//
// Created by marmelade on 07/08/22.
//

#include "udp.h"

namespace wirefish::protocol {

    UDP::UDP(const char *buffer, size_t length) : m_udphdr{}, m_last_error{UDPError::NO_ERROR} {

        Ethernet _eth{buffer, length};

        size_t _ip_hdr_size = (_eth.IsIPv4() ? sizeof(struct iphdr) : sizeof(struct ip6_hdr) );
        size_t _offset = sizeof(struct ethhdr) + _ip_hdr_size;

        if(length < ( _offset + sizeof(struct udphdr)) ) {

            m_last_error = UDPError::BUFFER_TOO_SMALL;
            return ;
        }

        memcpy(&m_udphdr, buffer + _offset, sizeof(m_udphdr));

    }

    UDP::UDP(const UDP &other) {

        memcpy(&m_udphdr, &(other.m_udphdr), sizeof(m_udphdr));
        m_last_error = other.m_last_error;
    }

    UDP::UDP(UDP &&other) noexcept {

        if(this == &other) {

            return ;
        }

        memcpy(&m_udphdr, &(other.m_udphdr), sizeof(m_udphdr));
        m_last_error = other.m_last_error;

        memset(&(other.m_udphdr), 0, sizeof(m_udphdr));
        m_last_error = UDPError::NO_ERROR;
    }

    UDP::~UDP()=default;

    UDP &UDP::operator=(const UDP &other) {

        memcpy(&m_udphdr, &(other.m_udphdr), sizeof(m_udphdr));
        m_last_error = other.m_last_error;

        return *this;
    }

    UDP &UDP::operator=(UDP &&other) noexcept {

        if(this == &other) {

            return *this;
        }

        memcpy(&m_udphdr, &(other.m_udphdr), sizeof(m_udphdr));
        m_last_error = other.m_last_error;

        memset(&(other.m_udphdr), 0, sizeof(m_udphdr));
        m_last_error = UDPError::NO_ERROR;

        return *this;
    }

    unsigned short UDP::SourcePort() const noexcept {

        return ntohs(m_udphdr.source);
    }

    unsigned short UDP::DestinationPort() const noexcept {

        return ntohs(m_udphdr.dest);
    }

    unsigned short UDP::Length() const noexcept {

        return ntohs(m_udphdr.len);
    }

    unsigned short UDP::Checksum() const noexcept {

        return ntohs(m_udphdr.check);
    }


    [[nodiscard]] UDP::UDPError UDP::getLastError() {

        return m_last_error;
    }

} // wirefish::protocol