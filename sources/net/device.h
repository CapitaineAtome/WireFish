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
        explicit Device(std::string ifr);

        Device(Device &other)=delete;
        Device(Device &&other) noexcept;
        ~Device();

        Device &operator=(const Device &other)=delete;
        Device &operator=(Device &&other) noexcept;

        void capture(Packet &raw_packet);

        [[nodiscard]] int getLastError() const noexcept;

    private:
        int getPromiscuousSocket();

    private:
        std::string m_interface{};
        int m_socket{};
        int m_last_error{};

        // char m_buffer[UINT16_MAX]{};
    };

} // wirefish::net

#endif //C_DEVICE_H
