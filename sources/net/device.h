//
// Created by marmelade on 07/08/22.
//

#ifndef C_DEVICE_H
#define C_DEVICE_H

#include <sys/ioctl.h>
#include <unistd.h>

#include <linux/if_packet.h>
#include <net/if.h>
#include <linux/if_ether.h>

#include "interface.h"
#include "../packet/packet.h"

namespace wirefish::net {
    class Device {
    public:

        enum class DevError {
            NO_ERROR,
            SOCKET_CREATION_ERROR,
            READ_PACKET_ERROR,
            INTERFACE_SETTING_ERROR,
        };
        explicit Device(std::string ifr);

        Device(Device &other)=delete;
        Device(Device &&other) noexcept;
        ~Device();

        Device &operator=(const Device &other)=delete;
        Device &operator=(Device &&other) noexcept;

        [[nodiscard]] DevError capture(packet::Packet &raw_packet);

        [[nodiscard]] DevError getLastError() const noexcept;

    private:
        DevError getPromiscuousSocket();

    private:
        std::string m_interface{};
        int m_socket{};
        DevError m_last_error{};

        bool m_promiscuous{false};

        // char m_buffer[UINT16_MAX]{};
    };

} // wirefish::net

#endif //C_DEVICE_H
