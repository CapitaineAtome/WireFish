//
// Created by marmelade on 07/08/22.
//

#ifndef WIREFISH_TCP_H
#define WIREFISH_TCP_H

#include "ethernet.h"
#include "ipv4.h"
#include "ipv6.h"

#include <netinet/tcp.h>

namespace wirefish::protocol {

    class TCP {
    public:
        enum class TCPError {
            NO_ERROR,
            BUFFER_TOO_SMALL
        };

        TCP(const char *buffer, size_t length);
        TCP(const TCP &other);
        TCP(TCP &&other) noexcept;
        ~TCP();

        TCP &operator=(const TCP &other);
        TCP &operator=(TCP &&other) noexcept;

        [[nodiscard]] unsigned short SourcePort() const noexcept;
        [[nodiscard]] unsigned short DestinationPort() const noexcept;
        [[nodiscard]] unsigned int Sequence() const noexcept;
        [[nodiscard]] unsigned int AckSequeunce() const noexcept;
        [[nodiscard]] unsigned int Res1() const noexcept;
        [[nodiscard]] unsigned short DOff() const noexcept;
        [[nodiscard]] unsigned short FIN() const noexcept;
        [[nodiscard]] unsigned short SYN() const noexcept;
        [[nodiscard]] unsigned short RST() const noexcept;
        [[nodiscard]] unsigned short PSH() const noexcept;
        [[nodiscard]] unsigned short ACK() const noexcept;
        [[nodiscard]] unsigned short URG() const noexcept;
        [[nodiscard]] unsigned int Res2() const noexcept;
        [[nodiscard]] unsigned int Window() const noexcept;
        [[nodiscard]] unsigned short Checksum() const noexcept;
        [[nodiscard]] unsigned short URG_PRT() const noexcept;

        [[nodiscard]] TCPError getLastError();

    private:
        struct tcphdr m_tcphdr{};
        TCPError m_last_error{};
    };

} // wirefish::protocol

#endif //WIREFISH_TCP_H
