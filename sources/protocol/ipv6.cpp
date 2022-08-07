//
// Created by marmelade on 07/08/22.
//

#include "ipv6.h"

namespace wirefish::protocol {

    IPv6::IPv6(const char *buffer, size_t length) {

        size_t _offset = sizeof(struct ethhdr);

        if(length < ( _offset + sizeof(struct ip6_hdr)) ) {

            m_last_error = IPv6Error::BUFFER_TOO_SMALL;
            return ;
        }

        memcpy(&m_iphdr, buffer + _offset, sizeof(m_iphdr));
    }

    IPv6::IPv6(const IPv6 &other) {

        memcpy(&m_iphdr, &(other.m_iphdr), sizeof(m_iphdr));
        m_last_error = other.m_last_error;
    }

    IPv6::IPv6(IPv6 &&other) noexcept {

        if(this == &other) {

            return ;
        }

        memcpy(&m_iphdr, &(other.m_iphdr), sizeof(m_iphdr));
        m_last_error = other.m_last_error;

        memset(&(other.m_iphdr), 0, sizeof(m_iphdr));
        m_last_error = IPv6Error::NO_ERROR;
    }

    IPv6::~IPv6()=default;


    IPv6 &IPv6::operator=(const IPv6 &other) {

        memcpy(&m_iphdr, &(other.m_iphdr), sizeof(m_iphdr));
        m_last_error = other.m_last_error;

        return *this;
    }

    IPv6 &IPv6::operator=(IPv6 &&other) noexcept {

        if(this == &other) {

            return *this;
        }

        memcpy(&m_iphdr, &(other.m_iphdr), sizeof(m_iphdr));
        m_last_error = other.m_last_error;

        memset(&(other.m_iphdr), 0, sizeof(m_iphdr));
        m_last_error = IPv6Error::NO_ERROR;

        return *this;
    }

    unsigned int IPv6::Version() const noexcept {
        return ntohl(m_iphdr.ip6_ctlun.ip6_un1.ip6_un1_flow) & 0xF;
    }

    unsigned int IPv6::TrafficClass() const noexcept {

        return ntohl(m_iphdr.ip6_ctlun.ip6_un1.ip6_un1_flow) & (0xFF << 4U);
    }

    unsigned int IPv6::FlowId() const noexcept {

        return ntohl(m_iphdr.ip6_ctlun.ip6_un1.ip6_un1_flow) & (static_cast<unsigned int>(0xFFFFF << 12U));
    }

    unsigned short IPv6::PayloadLength() const noexcept {

        return ntohs(m_iphdr.ip6_ctlun.ip6_un1.ip6_un1_plen);
    }

    uint8_t IPv6::NextHeader() const noexcept {

        return m_iphdr.ip6_ctlun.ip6_un1.ip6_un1_nxt;
    }

    uint8_t IPv6::HopLimit() const noexcept {

        return m_iphdr.ip6_ctlun.ip6_un1.ip6_un1_hlim;
    }

    void IPv6::SourceAddress(std::string &source) const {
        char _ip6_addr[INET6_ADDRSTRLEN]{};

        inet_ntop(AF_INET6, &(m_iphdr.ip6_src), _ip6_addr, INET6_ADDRSTRLEN);

        source = _ip6_addr;
    }

    void IPv6::DestinationAddress(std::string &dest) const {
        char _ip6_addr[INET6_ADDRSTRLEN]{};

        inet_ntop(AF_INET6, &(m_iphdr.ip6_dst), _ip6_addr, INET6_ADDRSTRLEN);

        dest = _ip6_addr;
    }

    [[nodiscard]] IPv6::IPv6Error IPv6::getLastError() const noexcept {

        return m_last_error;
    }

} // wirefish::packet