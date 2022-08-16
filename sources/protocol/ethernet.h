//
// Created by marmelade on 07/08/22.
//

#ifndef WIREFISH_ETHERNET_H
#define WIREFISH_ETHERNET_H

#include <cstring>

#include <string>

#include <netinet/ether.h>
#include <netinet/in.h>

namespace wirefish::protocol {

        class Ethernet {
        public:

            enum class EthError {
                NO_ERROR,
                BUFFER_TOO_SMALL
            };

            Ethernet(const char *buffer, size_t length);
            Ethernet(const Ethernet &other);
            Ethernet(Ethernet &&other) noexcept;
            ~Ethernet();

            Ethernet &operator=(const Ethernet &other);
            Ethernet &operator=(Ethernet &&other) noexcept;

            bool SourceAddress(char *buffer, size_t length);

            bool DestinationAddress(char *buffer, size_t length);

            [[nodiscard]] unsigned short IPProtocol() const noexcept;

            [[nodiscard]] bool IsIPv4() const noexcept;
            [[nodiscard]] bool IsIPv6() const noexcept;

            [[nodiscard]] EthError getLastError() const noexcept;

        private:
            struct ethhdr m_ethdr{};
            EthError m_last_error;
        };

} // wirefish::packet

#endif //WIREFISH_ETHERNET_H
