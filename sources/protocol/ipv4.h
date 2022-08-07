//
// Created by marmelade on 07/08/22.
//

#ifndef WIREFISH_IPV4_H
#define WIREFISH_IPV4_H

#include "ethernet.h"

#include <cstring>
#include <cstdint>

#include <netinet/ip.h>
#include <arpa/inet.h>

namespace wirefish::protocol {

    class IPv4 {
    public:
        enum class IPv4Error {
            NO_ERROR,
            BUFFER_TOO_SMALL
        };

        IPv4(const char *buffer, size_t length);
        IPv4(const IPv4 &other);
        IPv4(IPv4 &&other) noexcept;
        ~IPv4();

        IPv4 &operator=(const IPv4 &other);
        IPv4 &operator=(IPv4 &&other) noexcept;

        [[nodiscard]] unsigned int HeaderLength() const noexcept;
        [[nodiscard]] unsigned int Version() const noexcept;
        [[nodiscard]] uint8_t TypeOfService() const noexcept;
        [[nodiscard]] unsigned short TotalLength() const noexcept;
        [[nodiscard]] unsigned short Identification() const noexcept;
        [[nodiscard]] unsigned short FragmentOffset() const noexcept;
        [[nodiscard]] uint8_t TimeToLive() const noexcept;
        [[nodiscard]] uint8_t Protocol() const noexcept;
        [[nodiscard]] unsigned int Checksum() const noexcept;
        void SourceAddress(std::string &source) const;
        void DestinationAddress(std::string &dest) const;

        [[nodiscard]] IPv4Error getLastError() const noexcept;

    private:
        struct iphdr m_iphdr{};
        IPv4Error m_last_error{};
    };

} // wirefish::packet

#endif //WIREFISH_IPV4_H
