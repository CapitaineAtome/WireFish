//
// Created by marmelade on 07/08/22.
//

#include "tcp.h"

namespace wirefish::protocol {

    TCP::TCP(const char *buffer, size_t length) : m_tcphdr{}, m_last_error{TCPError::NO_ERROR} {

        Ethernet _eth{buffer, length};

        size_t _ip_hdr_size = (_eth.IsIPv4() ? sizeof(struct iphdr) : sizeof(struct ip6_hdr) );
        size_t _offset = sizeof(struct ethhdr) + _ip_hdr_size;

        if(length < ( _offset + sizeof(struct tcphdr)) ) {

            m_last_error = TCPError::BUFFER_TOO_SMALL;
            return ;
        }

        memcpy(&m_tcphdr, buffer + _offset, sizeof(m_tcphdr));

    }

    TCP::TCP(const TCP &other) {

        memcpy(&m_tcphdr, &(other.m_tcphdr), sizeof(m_tcphdr));
        m_last_error = other.m_last_error;
    }

    TCP::TCP(TCP &&other) noexcept {

        if(this == &other) {

            return ;
        }

        memcpy(&m_tcphdr, &(other.m_tcphdr), sizeof(m_tcphdr));
        m_last_error = other.m_last_error;

        memset(&(other.m_tcphdr), 0, sizeof(m_tcphdr));
        m_last_error = TCPError::NO_ERROR;
    }

    TCP::~TCP()=default;

    TCP &TCP::operator=(const TCP &other) {

        memcpy(&m_tcphdr, &(other.m_tcphdr), sizeof(m_tcphdr));
        m_last_error = other.m_last_error;

        return *this;
    }

    TCP &TCP::operator=(TCP &&other) noexcept {

        if(this == &other) {

            return *this;
        }

        memcpy(&m_tcphdr, &(other.m_tcphdr), sizeof(m_tcphdr));
        m_last_error = other.m_last_error;

        memset(&(other.m_tcphdr), 0, sizeof(m_tcphdr));
        m_last_error = TCPError::NO_ERROR;

        return *this;
    }

    unsigned short TCP::SourcePort() const noexcept {

        return ntohs(m_tcphdr.source);
    }
    unsigned short TCP::DestinationPort() const noexcept {

        return ntohs(m_tcphdr.dest);
    }
    unsigned int TCP::Sequence() const noexcept {

        return ntohl(m_tcphdr.seq);
    }
    unsigned int TCP::AckSequeunce() const noexcept {

        return ntohl(m_tcphdr.ack_seq);
    }
    unsigned int TCP::Res1() const noexcept {

        return ntohl(m_tcphdr.res1);
    }
    unsigned short TCP::DOff() const noexcept {

        return m_tcphdr.doff * 4;
    }
    unsigned short TCP::FIN() const noexcept {

        return m_tcphdr.fin;
    }
    unsigned short TCP::SYN() const noexcept {

        return m_tcphdr.syn;
    }
    unsigned short TCP::RST() const noexcept {

        return m_tcphdr.rst;
    }
    unsigned short TCP::PSH() const noexcept {

        return m_tcphdr.psh;
    }
    unsigned short TCP::ACK() const noexcept {

        return m_tcphdr.ack;
    }
    unsigned short TCP::URG() const noexcept {

        return m_tcphdr.urg;
    }
    unsigned int TCP::Res2() const noexcept {

        return ntohl(m_tcphdr.res2);
    }
    unsigned int TCP::Window() const noexcept {

        return ntohl(m_tcphdr.window);
    }
    unsigned short TCP::Checksum() const noexcept {

        return ntohs(m_tcphdr.check);
    }
    unsigned short TCP::URG_PRT() const noexcept {

        return ntohs(m_tcphdr.urg_ptr);
    }

    [[nodiscard]] TCP::TCPError TCP::getLastError() {

        return m_last_error;
    }
    
} // wirefish::protocol