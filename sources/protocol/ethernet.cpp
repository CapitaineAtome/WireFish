//
// Created by marmelade on 07/08/22.
//

#include "ethernet.h"

namespace wirefish::protocol {

    Ethernet::Ethernet(const char *buffer, size_t length) : m_ethdr{}, m_last_error{EthError::NO_ERROR}{

        if(length < sizeof(m_ethdr)) {

            m_last_error = EthError::BUFFER_TOO_SMALL;
            return ;
        }

        memcpy(&m_ethdr, buffer, sizeof(m_ethdr));

    }

    Ethernet::Ethernet(const Ethernet &other) {

        memcpy(&m_ethdr, &(other.m_ethdr), sizeof(m_ethdr));
        m_last_error = other.m_last_error;

    }

    Ethernet::Ethernet(Ethernet &&other) noexcept {

        if(this == &other) {

            return ;
        }

        memcpy(&m_ethdr, &(other.m_ethdr), sizeof(m_ethdr));
        m_last_error = other.m_last_error;

        memset(&(other.m_ethdr), 0, sizeof(m_ethdr));
        m_last_error = EthError::NO_ERROR;
    }

    Ethernet::~Ethernet()=default;

    Ethernet &Ethernet::operator=(const Ethernet &other) {

        memcpy(&m_ethdr, &(other.m_ethdr), sizeof(m_ethdr));
        m_last_error = other.m_last_error;

        return *this;
    }

    Ethernet &Ethernet::operator=(Ethernet &&other) noexcept {

        if(this == &other) {

            return *this;
        }

        memcpy(&m_ethdr, &(other.m_ethdr), sizeof(m_ethdr));
        m_last_error = other.m_last_error;

        memset(&(other.m_ethdr), 0, sizeof(m_ethdr));
        m_last_error = EthError::NO_ERROR;

        return *this;
    }

    bool Ethernet::SourceAddress(char *buffer, const size_t length) {

        if(length < ETH_ALEN) {

            m_last_error = EthError::BUFFER_TOO_SMALL;
            return true;
        }

        memcpy(buffer, m_ethdr.h_source, ETH_ALEN);

        return false;
    }

    bool Ethernet::DestinationAddress(char *buffer, const size_t length) {

        if(length < ETH_ALEN) {

            m_last_error = EthError::BUFFER_TOO_SMALL;
            return true;
        }

        memcpy(buffer, m_ethdr.h_dest, ETH_ALEN);

        return false;
    }

    unsigned short Ethernet::IPProtocol() const noexcept {

        return ntohs(m_ethdr.h_proto);
    }

    bool Ethernet::IsIPv4() const noexcept {

        return IPProtocol() == ETH_P_IP;
    }

    bool Ethernet::IsIPv6() const noexcept {

        return IPProtocol() == ETH_P_IPV6;
    }

    Ethernet::EthError Ethernet::getLastError() const noexcept {

        return m_last_error;
    }

} // wirefish::packet