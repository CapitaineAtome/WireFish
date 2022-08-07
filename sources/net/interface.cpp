//
// Created by marmelade on 07/08/22.
//

#include "interface.h"

namespace wirefish::net {

    int Interface::list_interfaces(std::vector<Interface> &list_ifr) {

        struct ifaddrs *ifr{};

        if(getifaddrs(&ifr) == -1) {

            PRINT_ERROR("getifaddrs");
            return -errno;
        }

        for(auto _elem{ifr}; _elem != nullptr; _elem = _elem->ifa_next) {

            if (_elem->ifa_addr == nullptr) {
                continue;
            }

            Interface _interface{_elem};
            list_ifr.push_back(_interface);

        }

        return 0;
    }

    Interface::Interface(struct ifaddrs *ifr) {

        setInterface(ifr);
    }

    Interface::Interface(const Interface &other) {

        m_name = other.m_name;
        m_address = other.m_address;
        m_net_mask = other.m_net_mask;

        m_family = other.m_family;
        m_flags = other.m_flags;
    }

    Interface::Interface(Interface &&other) noexcept {

        if(this == &other) {

            return ;
        }

        // Copy values
        m_name = other.m_name;
        m_address = other.m_address;
        m_net_mask = other.m_net_mask;

        m_family = other.m_family;
        m_flags = other.m_flags;

        // Set to default value
        other.m_name = "";
        other.m_address = "";
        other.m_net_mask = "";

        other.m_family = 0;
        other.m_flags = 0;
    }

    Interface::~Interface()=default;

    Interface &Interface::operator=(const Interface &other) {
        // Copy values
        m_name = other.m_name;
        m_address = other.m_address;
        m_net_mask = other.m_net_mask;

        m_family = other.m_family;
        m_flags = other.m_flags;

        return *this;
    }

    Interface &Interface::operator=(Interface &&other) noexcept {

        if(this == &other) {

            return *this;
        }

        // Copy values
        m_name = other.m_name;
        m_address = other.m_address;
        m_net_mask = other.m_net_mask;

        m_family = other.m_family;
        m_flags = other.m_flags;

        // Set to default value
        other.m_name = "";
        other.m_address = "";
        other.m_net_mask = "";

        other.m_family = 0;
        other.m_flags = 0;

        return *this;
    }

    bool Interface::operator==(const Interface &other) {

        return (m_name == other.m_name &&
                m_address == other.m_address &&
                m_net_mask == other.m_net_mask &&

                m_family == other.m_family&&
                m_flags == other.m_flags);
    }


    void Interface::setInterface(struct ifaddrs *ifr) {

        char _str[NI_MAXHOST];

        if(ifr != nullptr) {
            m_name = ifr->ifa_name;

            m_family = ifr->ifa_addr->sa_family;
            m_flags = ifr->ifa_flags;

            memset(_str, 0, sizeof(_str) / sizeof(*_str));
            if(!getnameinfo(ifr->ifa_addr,
                            (m_family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
                            _str, NI_MAXHOST,
                            nullptr, 0, NI_NUMERICHOST)) {

                m_address = _str;
            }

            memset(_str, 0, sizeof(_str) / sizeof(*_str));
            if(!getnameinfo(ifr->ifa_addr,
                            (m_family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
                            _str, NI_MAXHOST,
                            nullptr, 0, NI_NUMERICHOST)) {

                m_net_mask = _str;
            }

        }

    }

    [[nodiscard]] const std::string &Interface::getName() const noexcept {
        return m_name;
    }

    [[nodiscard]] const std::string &Interface::getAddress() const noexcept {
        return m_address;
    }

    [[nodiscard]] const std::string &Interface::getNetMask() const noexcept {
        return m_net_mask;
    }

    [[nodiscard]] int Interface::getFamily() const noexcept {
        return m_family;
    }

    [[nodiscard]] unsigned int Interface::getFlags() const noexcept {
        return m_flags;
    }

} // wirefish::net