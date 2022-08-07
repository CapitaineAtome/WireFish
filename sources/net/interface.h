//
// Created by marmelade on 07/08/22.
//

#ifndef WIREFISH_INTERFACE_H
#define WIREFISH_INTERFACE_H

#include <cerrno>

#include <vector>
#include <cstring>
#include <string>

#include <netdb.h>
#include <ifaddrs.h>
#include <sys/socket.h>

#include "../commons.h"

namespace wirefish::net {

    class Interface {
    public:
        static int list_interfaces(std::vector<Interface> &list_ifr);

        explicit Interface(struct ifaddrs *ifr); // default ctr
        Interface(const Interface &other); // copy ctr
        Interface(Interface &&other) noexcept ; // move ctr
        virtual ~Interface(); // dtr

        Interface &operator=(const Interface &other); // copy opr
        Interface &operator=(Interface &&other) noexcept; // move opr
        bool operator==(const Interface &other);

        void setInterface(struct ifaddrs *ifr);

        [[nodiscard]] const std::string &getName() const noexcept;

        [[nodiscard]] const std::string &getAddress() const noexcept;

        [[nodiscard]] const std::string &getNetMask() const noexcept;

        [[nodiscard]] int getFamily() const noexcept;

        [[nodiscard]] unsigned int getFlags() const noexcept;

    private:
        std::string m_name{};
        std::string m_address{};
        std::string m_net_mask{};

        int m_family{};
        unsigned int m_flags{};
    };

} // wirefish::net

#endif //WIREFISH_INTERFACE_H
