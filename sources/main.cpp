//
// Created by marmelade on 07/08/22.
//

#include <iostream>

#include "net/interface.h"

int main() {

    std::vector<wirefish::net::Interface> ifrs;
    wirefish::net::Interface::list_interfaces(ifrs);

    for(const auto &elem: ifrs) {

        std::cout << elem.getName() << std::endl;
        std::cout << elem.getAddress() << std::endl;
        std::cout << elem.getNetMask() << std::endl;
        std::cout << elem.getFamily() << std::endl;
        std::cout << elem.getFlags() << std::endl;
        std::cout << "--------------------------------------------\n" << std::endl;
    }

    return 0;
}