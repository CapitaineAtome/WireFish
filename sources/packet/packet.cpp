//
// Created by marmelade on 07/08/22.
//

#include "packet.h"

#include <algorithm>

namespace wirefish::packet {

    Packet::Packet() : m_buffer{}, m_length{} {

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

    void Packet::setRaw(const char *buffer, const size_t length) {

        m_length = std::min(sizeof(m_buffer) / sizeof(*m_buffer) - 1U, length - 1U);

        memcpy(m_buffer, buffer, m_length);

        m_buffer[sizeof(m_buffer) / sizeof(*m_buffer) - 1] = '\0';
    }

    void Packet::parse() {

    }

    // PRIVATE Functions
    void Packet::process_ethernet(std::stringstream &output) {

        (void) output;

        /*if(m_length < sizeof(struct ethhdr)) {

            return ;
        }

        auto *_eth_hdr = reinterpret_cast<struct ethhdr *>(m_buffer);

        output << "IPv4 Header:" << std::endl;

        output << std::hex << std::uppercase << "\t"
                  << static_cast<int16_t>(_eth_hdr->h_source[0]) << ":" << static_cast<int16_t>(_eth_hdr->h_source[1]) << ":" << static_cast<int16_t>(_eth_hdr->h_source[2]) << ":"
                  << static_cast<int16_t>(_eth_hdr->h_source[3]) << ":" << static_cast<int16_t>(_eth_hdr->h_source[4]) << ":" << static_cast<int16_t>(_eth_hdr->h_source[5])
                  << std::endl;

        output << std::hex << std::uppercase << "\t"
                  << static_cast<int16_t>(_eth_hdr->h_source[0]) << ":" << static_cast<int16_t>(_eth_hdr->h_source[1]) << ":" << static_cast<int16_t>(_eth_hdr->h_source[2]) << ":"
                  << static_cast<int16_t>(_eth_hdr->h_source[3]) << ":" << static_cast<int16_t>(_eth_hdr->h_source[4]) << ":" << static_cast<int16_t>(_eth_hdr->h_source[5])
                  << std::endl;

        output << "\t";
        switch(ntohs(_eth_hdr->h_proto)) {
            case ETH_P_IP:
                output << "IP (";
                break;

            case ETH_P_IPV6:
                output << "IPv6 (";
                break;

            default:
                output << "UNKNOWN_PROTOCOL (";
        }

        output << ntohs(_eth_hdr->h_proto) << ")\n" << std::endl;*/
    }

    void Packet::process_ipv4(std::stringstream &output) {

        (void) output;

        /*if( m_length < (sizeof(struct ethhdr) + sizeof(struct ip)) ) {

            return ;
        }

        auto _ip_hdr = reinterpret_cast<struct ip *>(m_buffer + sizeof(struct ethhdr));
        char _ip_addr_s[INET_ADDRSTRLEN]{};
        char _ip_addr_d[INET_ADDRSTRLEN]{};

        inet_ntop(AF_INET, &(_ip_hdr->ip_src), _ip_addr_s, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(_ip_hdr->ip_dst), _ip_addr_d, INET_ADDRSTRLEN);

        output << "IPv4 Header";

        output
                << "\n\tHeader Length\t\t: " << (static_cast<unsigned int>(_ip_hdr->ip_hl) * 4)
                << "\n\tVersion\t\t\t: " << static_cast<unsigned int>(_ip_hdr->ip_v)
                << "\n\tType of Service\t\t: " << static_cast<unsigned int>(_ip_hdr->ip_tos)
                << "\n\tTotal Length\t\t: " << static_cast<unsigned int>(_ip_hdr->ip_len)
                << "\n\tIdentification\t\t: " << ntohs(_ip_hdr->ip_id)
                << "\n\tFragment Offset\t\t: " << static_cast<unsigned int>(_ip_hdr->ip_off)
                << "\n\tTime To Live\t\t: " << static_cast<unsigned int>(_ip_hdr->ip_ttl)
                << "\n\tProtocol\t\t: " << static_cast<unsigned int>(_ip_hdr->ip_p)
                << "\n\tChecksum\t\t: " << ntohs(_ip_hdr->ip_sum)
                << "\n\tSource Address\t\t: " << _ip_addr_s
                << "\n\tDestination Address\t: " << _ip_addr_d
                << "\n" << std::endl;

        // return _ip_hdr->ip_p;*/
    }

    void Packet::process_ipv6(std::stringstream &output) {

        (void) output;

        /*if(m_length < (sizeof(struct ethhdr) + sizeof(struct ip6_hdr))) {

            return ;
        }

        auto _ip6_hdr = reinterpret_cast<struct ip6_hdr *>(m_buffer + sizeof(struct ethhdr));
        char _ip6_addr_s[INET6_ADDRSTRLEN]{};
        char _ip6_addr_d[INET6_ADDRSTRLEN]{};

        inet_ntop(AF_INET6, &(_ip6_hdr->ip6_src), _ip6_addr_s, INET6_ADDRSTRLEN);
        inet_ntop(AF_INET6, &(_ip6_hdr->ip6_dst), _ip6_addr_d, INET6_ADDRSTRLEN);

        output << "IPv6 Header";

        output
                << "\n\tVersion\t\t\t: " << (ntohl(_ip6_hdr->ip6_ctlun.ip6_un1.ip6_un1_flow) & 0xF)
                << "\n\tTraffic Class\t\t: " << (ntohl(_ip6_hdr->ip6_ctlun.ip6_un1.ip6_un1_flow) & (0xFF << 4U))
                << "\n\tFlow ID\t\t\t: " << (ntohl(_ip6_hdr->ip6_ctlun.ip6_un1.ip6_un1_flow) & (static_cast<unsigned int>(0xFFFFF << 12U)))
                << "\n\tPayload Length\t\t: " << ntohs(_ip6_hdr->ip6_ctlun.ip6_un1.ip6_un1_plen)
                << "\n\tNext Header\t\t: " << static_cast<uint32_t>(_ip6_hdr->ip6_ctlun.ip6_un1.ip6_un1_nxt)
                << "\n\tHop Limit\t\t: " << static_cast<uint32_t>(_ip6_hdr->ip6_ctlun.ip6_un1.ip6_un1_hlim)
                << "\n\tSource Address\t\t: " << _ip6_addr_s
                << "\n\tDestination Address\t: " << _ip6_addr_d
                << "\n" << std::endl;

        // return _ip6_hdr->ip6_ctlun.ip6_un1.ip6_un1_nxt;*/
    }

    void Packet::process_udp(std::stringstream &output) {

        (void) output;

        /*size_t _ip_hdr_size = (ip_protocol ? sizeof(struct iphdr) : sizeof(struct ip6_hdr) );

        if( m_length < (sizeof(struct ethhdr) + _ip_hdr_size + sizeof(struct udphdr)) ) {

            return ;
        }

        auto _udp_hdr = reinterpret_cast<struct udphdr *>(m_buffer + sizeof(struct ethhdr) + (ip_protocol ? sizeof(struct iphdr) : sizeof(struct ip6_hdr ) ));

        output << "UDP Header";
        output
                << "\n\tSource Port\t\t: " << ntohs(_udp_hdr->source)
                << "\n\tDestination Port\t: " << ntohs(_udp_hdr->dest)
                << "\n\tLength\t\t\t: " << ntohs(_udp_hdr->len)
                << "\n\tChecksum\t: " << ntohs(_udp_hdr->check)
                << "\n" << std::endl;*/

    }

    void Packet::process_tcp(std::stringstream &output) {

        (void) output;
        /*size_t _ip_hdr_size = (ip_protocol ? sizeof(struct iphdr) : sizeof(struct ip6_hdr) );

        if( m_length < (sizeof(struct ethhdr) + _ip_hdr_size + sizeof(struct tcphdr)) ) {

            return ;
        }

        auto _tcp_hdr = reinterpret_cast<struct tcphdr *>(m_buffer + sizeof(struct ethhdr) + _ip_hdr_size );

        output << "TCP Header";
        output
                << "\n\tSource Port\t\t: " << ntohs(_tcp_hdr->source)
                << "\n\tDestination Port\t: " << ntohs(_tcp_hdr->dest)
                << "\n\tSequence\t\t: " << ntohl(_tcp_hdr->seq)
                << "\n\tAck Sequance\t\t: " << ntohl(_tcp_hdr->ack_seq)
                << "\n\tRes1\t\t: " << ntohl(_tcp_hdr->res1)
                << "\n\tD OFF\t\t: " << _tcp_hdr->doff * 4
                << "\n\tFIN\t\t: " << static_cast<uint32_t>(_tcp_hdr->fin)
                << "\n\tSYN\t\t: " << static_cast<uint32_t>(_tcp_hdr->syn)
                << "\n\tRST\t\t: " << static_cast<uint32_t>(_tcp_hdr->rst)
                << "\n\tPSH\t\t: " << static_cast<uint32_t>(_tcp_hdr->psh)
                << "\n\tACK\t\t: " << static_cast<uint32_t>(_tcp_hdr->ack)
                << "\n\tURG\t\t: " << static_cast<uint32_t>(_tcp_hdr->urg)
                << "\n\tRes2\t\t: " << ntohl(_tcp_hdr->res1)
                << "\n\tWindow\t\t: " << ntohl(_tcp_hdr->window)
                << "\n\tChecksum\t: " << ntohs(_tcp_hdr->check)
                << "\n\tURG PRT\t\t: " << ntohs(_tcp_hdr->urg_ptr)
                << "\n" << std::endl;*/
    }
    
} // wirefish::packet