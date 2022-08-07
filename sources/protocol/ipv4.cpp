//
// Created by marmelade on 07/08/22.
//

#include "ipv4.h"

namespace wirefish::protocol {

    IPv4::IPv4(const char *buffer, size_t length) : m_iphdr{}, m_last_error{IPv4Error::NO_ERROR}{

        size_t _offset = sizeof(struct ethhdr);

        if(length < ( _offset + sizeof(struct iphdr)) ) {

            m_last_error = IPv4Error::BUFFER_TOO_SMALL;
            return ;
        }

        memcpy(&m_iphdr, buffer + _offset, sizeof(m_iphdr));

    }
    IPv4::IPv4(const IPv4 &other) {

        memcpy(&m_iphdr, &(other.m_iphdr), sizeof(m_iphdr));
        m_last_error = other.m_last_error;
    }

    IPv4::IPv4(IPv4 &&other) noexcept {

        if(this == &other) {

            return ;
        }

        memcpy(&m_iphdr, &(other.m_iphdr), sizeof(m_iphdr));
        m_last_error = other.m_last_error;

        memset(&(other.m_iphdr), 0, sizeof(m_iphdr));
        m_last_error = IPv4Error::NO_ERROR;
    }

    IPv4::~IPv4()=default;

    IPv4 &IPv4::operator=(const IPv4 &other) {

        memcpy(&m_iphdr, &(other.m_iphdr), sizeof(m_iphdr));
        m_last_error = other.m_last_error;

        return *this;
    }

    IPv4 &IPv4::operator=(IPv4 &&other) noexcept {

        if(this == &other) {

            return *this;
        }

        memcpy(&m_iphdr, &(other.m_iphdr), sizeof(m_iphdr));
        m_last_error = other.m_last_error;

        memset(&(other.m_iphdr), 0, sizeof(m_iphdr));
        m_last_error = IPv4Error::NO_ERROR;

        return *this;
    }

    unsigned int IPv4::HeaderLength() const noexcept {

        return static_cast<unsigned int>(m_iphdr.ihl * 4);
    }

    unsigned int IPv4::Version() const noexcept {

        return static_cast<unsigned int>(m_iphdr.version);
    }

    uint8_t IPv4::TypeOfService() const noexcept {

        return m_iphdr.tos;
    }

    unsigned short IPv4::TotalLength() const noexcept {

        return ntohs(m_iphdr.tot_len);
    }

    unsigned short IPv4::Identification() const noexcept {

        return ntohs(m_iphdr.id);
    }

    unsigned short IPv4::FragmentOffset() const noexcept {

        return ntohs(m_iphdr.frag_off);
    }

    uint8_t IPv4::TimeToLive() const noexcept {

        return m_iphdr.ttl;
    }

    uint8_t IPv4::Protocol() const noexcept {

        return m_iphdr.protocol;
    }

    unsigned int IPv4::Checksum() const noexcept {

        return static_cast<unsigned int>(ntohs(m_iphdr.check));
    }

    void IPv4::SourceAddress(std::string &source) const {

        char _ip_addr[INET_ADDRSTRLEN]{};

        inet_ntop(AF_INET, &(m_iphdr.saddr), _ip_addr, INET_ADDRSTRLEN);

        source = _ip_addr;
    }

    void IPv4::DestinationAddress(std::string &dest) const {
        char _ip_addr[INET_ADDRSTRLEN]{};
        inet_ntop(AF_INET, &(m_iphdr.daddr), _ip_addr, INET_ADDRSTRLEN);

        dest = _ip_addr;
    }


    IPv4::IPv4Error IPv4::getLastError() const noexcept {

        return m_last_error;
    }

} // wirefish::packet