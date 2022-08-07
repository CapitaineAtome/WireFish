//
// Created by marmelade on 07/08/22.
//

#include "device.h"

#include <utility>

namespace wirefish::net {

    Device::Device(std::string ifr) : m_interface{std::move(ifr)}, m_socket{}, m_last_error{}/*, m_buffer{}*/ {

        m_last_error = getPromiscuousSocket();
    }

    Device::Device(Device &&other) noexcept {

        if(this == &other) {

            return ;
        }

        m_interface = other.m_interface;

        m_socket = other.m_socket;
        m_last_error = other.m_last_error;

        // size_t _max_byte_to_copy{std::min(sizeof(m_buffer) / sizeof(*m_buffer),
        //                                   sizeof(other.m_buffer) / sizeof(*other.m_buffer))};
        // memcpy(m_buffer, other.m_buffer, _max_byte_to_copy);

        // other.m_interface = "";
        // other.m_socket = 0;
        // other.m_last_error = 0;

        // memset(other.m_buffer, 0, sizeof(other.m_buffer) / sizeof(other.m_buffer[0]));
    }

    Device::~Device()=default;

    Device &Device::operator=(Device &&other) noexcept {

        if(this == &other) {

            return *this;
        }

        m_interface = other.m_interface;

        m_socket = other.m_socket;
        m_last_error = other.m_last_error;

        // size_t _max_byte_to_copy{std::min(sizeof(m_buffer) / sizeof(*m_buffer),
        //                                   sizeof(other.m_buffer) / sizeof(*other.m_buffer))};
        // memcpy(m_buffer, other.m_buffer, _max_byte_to_copy);

        other.m_interface = "";
        other.m_socket = 0;
        other.m_last_error = 0;

        // memset(other.m_buffer, 0, sizeof(other.m_buffer) / sizeof(other.m_buffer[0]));

        return *this;
    }

    void Device::capture(packet::Packet &packet) {

        struct sockaddr s_addr{};
        socklen_t s_addr_size = sizeof(struct sockaddr);

        char _buffer[UINT16_MAX]{};

        auto packet_size = recvfrom(m_socket, _buffer, sizeof(_buffer) / sizeof(*_buffer), 0, &s_addr, &s_addr_size);
        if(packet_size < 0) {

            PRINT_ERROR("Failed to read a packet");
            m_last_error = errno;
            return ;
        }

        packet.setRaw(_buffer, sizeof(_buffer) / sizeof(*_buffer));

    }

    int Device::getLastError() const noexcept {

        return m_last_error;
    }

    // Private Functions
    int Device::getPromiscuousSocket() {

        int m_sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

        if(m_sock == -1) {

            return -(m_last_error = errno);
        }

        struct ifreq _ifr{};
        strncpy((char*)_ifr.ifr_name, m_interface.c_str(), IF_NAMESIZE);
        if(ioctl(m_sock, SIOCGIFINDEX, &_ifr) < 0) {

            close(m_sock);
            return -(m_last_error = errno);
        }

        struct packet_mreq _mr{};
        memset(&_mr, 0, sizeof(_mr));

        _mr.mr_ifindex = _ifr.ifr_ifindex;
        _mr.mr_type = PACKET_MR_PROMISC;

        if(setsockopt(m_sock, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &_mr, sizeof(_mr)) < 0) {

            close(m_sock);

            m_last_error = errno;
            return -errno;
        }

        _ifr.ifr_flags |= IFF_PROMISC;
        if(ioctl(m_sock, SIOCSIFFLAGS, &_ifr) != 0) {

            close(m_sock);
            return -(m_last_error = errno);
        }

        return 0;
    }

} // wirefish::net