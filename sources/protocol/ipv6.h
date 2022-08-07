//
// Created by marmelade on 07/08/22.
//

#ifndef WIREFISH_IPV6_H
#define WIREFISH_IPV6_H

#include "ethernet.h"

#include <cstring>
#include <cstdint>

#include <netinet/ip6.h>
#include <arpa/inet.h>

namespace wirefish::protocol {

    class IPv6 {

        enum class IPv6Error {
            NO_ERROR,
            BUFFER_TOO_SMALL
        };

        IPv6(const char *buffer, size_t length);
        IPv6(const IPv6 &other);
        IPv6(IPv6 &&other) noexcept;
        ~IPv6();

        IPv6 &operator=(const IPv6 &other);
        IPv6 &operator=(IPv6 &&other) noexcept;

        [[nodiscard]] unsigned int Version() const noexcept;
        [[nodiscard]] unsigned int TrafficClass() const noexcept;
        [[nodiscard]] unsigned int FlowId() const noexcept;
        [[nodiscard]] unsigned short PayloadLength() const noexcept;
        [[nodiscard]] uint8_t  NextHeader() const noexcept;
        [[nodiscard]] uint8_t  HopLimit() const noexcept;
        void SourceAddress(std::string &source) const;
        void DestinationAddress(std::string &dest) const;

        [[nodiscard]] IPv6Error getLastError() const noexcept;

    private:
        struct ip6_hdr m_iphdr{};
        IPv6Error m_last_error{};
    };

} // wirefish::packet

#endif //WIREFISH_IPV6_H
