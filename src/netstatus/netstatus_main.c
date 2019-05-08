/// \file
/// \brief  КраткоеОписание
/// \author Art Navsegda <artnavsegda@gmail.com>
///
/// ПодробноеОписание

////////////////////////////////////////////////////////////////////////////
//  Подключение заголовочных файлов

#include <nuttx/config.h>

#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <nuttx/net/icmp.h>
#include "netutils/netlib.h"

////////////////////////////////////////////////////////////////////////////
//  Приватные константы препроцессора

#define ICMP_PING_DATALEN  56
#define ICMP_IOBUFFER_SIZE sizeof(struct icmp_hdr_s) + ICMP_PING_DATALEN

////////////////////////////////////////////////////////////////////////////
//  Приватные типы данных

struct ping_info_s
{
  int sockfd;               /* Open IPPROTO_ICMP socket */
  FAR struct in_addr dest;  /* Target address to ping */
  uint16_t count;           /* Number of pings requested */
  uint16_t nrequests;       /* Number of ICMP ECHO requests sent */
  uint16_t nreplies;        /* Number of matching ICMP ECHO replies received */
  int16_t delay;            /* Deciseconds to delay between pings */

  /* I/O buffer for data transfers */

  uint8_t iobuffer[ICMP_IOBUFFER_SIZE];
};

////////////////////////////////////////////////////////////////////////////
//  Константы


////////////////////////////////////////////////////////////////////////////
//  Предварительные определения функций
void icmp_ping(FAR struct ping_info_s *info);

////////////////////////////////////////////////////////////////////////////
//  Приватные функции


////////////////////////////////////////////////////////////////////////////
//  netstatus_main

//void ping_status(FAR const struct ping_result_s *result)
//{
//	printf("code: %d\r\n", result->code);
//}

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int netstatus_main(int argc, char *argv[])
#endif
{
  char ipname[15];
  struct in_addr myrouter;
  netlib_get_ipv4addr("ppp0", &myrouter); 
  printf("Local ip %s\r\n",inet_ntoa(myrouter));
  myrouter.s_addr = htonl(ntohl(myrouter.s_addr) - 1);
  printf("Remote ip %s\r\n",inet_ntoa(myrouter));
  char myhostname[] = "208.67.222.222";
  struct ping_info_s pinginfo = {
    .count = 1,
    .delay = 2000,
    .sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP)
  };
  inet_pton(AF_INET, "208.67.222.222", &(pinginfo.dest));
  icmp_ping(&pinginfo);
  printf("recv %d\r\n", pinginfo.nreplies);
  close(pinginfo.sockfd);
  return 0;
}
