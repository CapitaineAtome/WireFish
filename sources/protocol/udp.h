//
// Created by marmelade on 07/08/22.
//

#ifndef WIREFISH_UDP_H
#define WIREFISH_UDP_H

#include "ethernet.h"
#include "ipv4.h"
#include "ipv6.h"

#include <netinet/udp.h>

namespace wirefish::protocol {

    class UDP {
    public:
        enum class UDPError {
            NO_ERROR,
            BUFFER_TOO_SMALL
        };

        UDP(const char *buffer, size_t length);
        UDP(const UDP &other);
        UDP(UDP &&other) noexcept;
        ~UDP();

        UDP &operator=(const UDP &other);
        UDP &operator=(UDP &&other) noexcept;

        [[nodiscard]] unsigned short SourcePort() const noexcept;
        [[nodiscard]] unsigned short DestinationPort() const noexcept;
        [[nodiscard]] unsigned short Length() const noexcept;
        [[nodiscard]] unsigned short Checksum() const noexcept;

        [[nodiscard]] UDPError getLastError();

    private:
        struct udphdr m_udphdr{};
        UDPError m_last_error{};
    };

} // wirefish::protocol

#endif //WIREFISH_UDP_H
