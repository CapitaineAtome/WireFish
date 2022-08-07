//
// Created by marmelade on 07/08/22.
//

#ifndef C_COMMONS_H
#define C_COMMONS_H

#include <cerrno>

#ifndef NDEBUG
#define PRINT_ERROR(err_msg) perror(err_msg)
#else
#define PRINT_ERROR(err_msg) (void)
#endif

/*
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

#include <ifaddrs.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <linux/if_link.h>
#include <linux/if_packet.h>

#include <sys/ioctl.h>

#include <net/if.h>
#include <net/ethernet.h>

#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
 */
#endif //C_COMMONS_H
