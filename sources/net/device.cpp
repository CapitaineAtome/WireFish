//
// Created by marmelade on 07/08/22.
//

#include "device.h"

#include <utility>

namespace wirefish::net {

    Device::Device(std::string ifr) : m_interface{std::move(ifr)}, m_socket{}, m_last_error{DevError::NO_ERROR}, m_promiscuous{false}/*, m_buffer{}*/ {

        m_last_error = getPromiscuousSocket();
    }

    Device::Device(Device &&other) noexcept {

        if(this == &other) {

            return ;
        }

        m_interface = other.m_interface;

        m_socket = other.m_socket;
        m_last_error = other.m_last_error;

        m_promiscuous = other.m_promiscuous;

        // size_t _max_byte_to_copy{std::min(sizeof(m_buffer) / sizeof(*m_buffer),
        //                                   sizeof(other.m_buffer) / sizeof(*other.m_buffer))};
        // memcpy(m_buffer, other.m_buffer, _max_byte_to_copy);

        // other.m_interface = "";
        // other.m_socket = 0;
        // other.m_last_error = 0;

        // memset(other.m_buffer, 0, sizeof(other.m_buffer) / sizeof(other.m_buffer[0]));
    }

    Device::~Device() {

        if(m_promiscuous) {

            close(m_socket);
        }
    };

    Device &Device::operator=(Device &&other) noexcept {

        if(this == &other) {

            return *this;
        }

        m_interface = other.m_interface;

        m_socket = other.m_socket;
        m_last_error = other.m_last_error;

        m_promiscuous = other.m_promiscuous;

        // size_t _max_byte_to_copy{std::min(sizeof(m_buffer) / sizeof(*m_buffer),
        //                                   sizeof(other.m_buffer) / sizeof(*other.m_buffer))};
        // memcpy(m_buffer, other.m_buffer, _max_byte_to_copy);

        other.m_interface = "";
        other.m_socket = 0;
        other.m_last_error = DevError::NO_ERROR;
        other.m_promiscuous = false;

        // memset(other.m_buffer, 0, sizeof(other.m_buffer) / sizeof(other.m_buffer[0]));

        return *this;
    }

    Device::DevError Device::capture(packet::Packet &packet) {

        struct sockaddr s_addr{};
        socklen_t s_addr_size = sizeof(struct sockaddr);

        char _buffer[UINT16_MAX]{};

        auto packet_size = recvfrom(m_socket, _buffer, sizeof(_buffer) / sizeof(*_buffer), 0, &s_addr, &s_addr_size);

        m_last_error = DevError::NO_ERROR;

        if(packet_size < 0) {

            PRINT_ERROR("Failed to read a packet");
            m_last_error = DevError::READ_PACKET_ERROR;

            return m_last_error;
        }

        packet.setRaw(_buffer, sizeof(_buffer) / sizeof(*_buffer));

        return m_last_error;
    }

    Device::DevError Device::getLastError() const noexcept {

        return m_last_error;
    }

    // Private Functions
    Device::DevError Device::getPromiscuousSocket() {

        m_last_error = DevError::NO_ERROR;

        m_socket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

        if(m_socket == -1) {

            PRINT_ERROR("Could not create a RAW SOCKET");
            m_last_error = DevError::SOCKET_CREATION_ERROR;

            return m_last_error;
        }

        struct ifreq _ifr{};
        strncpy(static_cast<char*>(_ifr.ifr_name), m_interface.c_str(), IF_NAMESIZE);
        if(ioctl(m_socket, SIOCGIFINDEX, &_ifr) < 0) {

            close(m_socket);
            m_last_error = DevError::INTERFACE_SETTING_ERROR;

            return m_last_error;
        }

        struct packet_mreq _mr{};
        memset(&_mr, 0, sizeof(_mr));

        _mr.mr_ifindex = _ifr.ifr_ifindex;
        _mr.mr_type = PACKET_MR_PROMISC;

        if(setsockopt(m_socket, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &_mr, sizeof(_mr)) < 0) {

            close(m_socket);
            m_last_error = DevError::INTERFACE_SETTING_ERROR;

            return m_last_error;
        }

        _ifr.ifr_flags |= IFF_PROMISC;
        if(ioctl(m_socket, SIOCSIFFLAGS, &_ifr) != 0) {

            close(m_socket);
            m_last_error = DevError::INTERFACE_SETTING_ERROR;

            return m_last_error;
        }

        m_promiscuous = true;

        return m_last_error;
    }

} // wirefish::net