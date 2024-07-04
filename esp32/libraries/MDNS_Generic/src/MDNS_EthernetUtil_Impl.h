/****************************************************************************************************************************
  MDNS_EthernetUtil_Impl.h

  mDNS library to support mDNS (registering services) and DNS-SD (service discovery).

  Based on and modified from https://github.com/arduino-libraries/ArduinoMDNS
  Built by Khoi Hoang https://github.com/khoih-prog/MDNS_Generic
  Licensed under MIT license

  Original Author: Georg Kaindl (http://gkaindl.com)

  This file is part of Arduino EthernetBonjour.

  EthernetBonjour is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
  as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

  EthernetBonjour is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with EthernetBonjour.
  If not, see <http://www.gnu.org/licenses/>.

  Version: 1.4.2
  
  Version  Modified By   Date      Comments
  -------  -----------  ---------- -----------
  1.0.0    K Hoang      01/08/2020 Initial coding to support W5x00 using Ethernet, EthernetLarge libraries
                                   Supported boards: nRF52, STM32, SAMD21/SAMD51, SAM DUE, Mega
  ...
  1.3.0    K Hoang      28/09/2021 Add support to Portenta_H7, using WiFi or Ethernet
  1.3.1    K Hoang      10/10/2021 Update `platform.ini` and `library.json`
  1.4.0    K Hoang      26/01/2022 Fix `multiple-definitions` linker error
  1.4.1    K Hoang      11/04/2022 Use Ethernet_Generic library as default. Support SPI1/SPI2 for RP2040/ESP32
  1.4.2    K Hoang      12/10/2022 Fix bugs in UDP length check and in WiFi example
 *****************************************************************************************************************************/

#ifndef __MDNS_ETHERNET_UTIL_IMPL_H__
#define __MDNS_ETHERNET_UTIL_IMPL_H__

#define __ETHERNET_UTIL_BONJOUR__

#include <inttypes.h>

////////////////////////////////////////

#if defined(__ETHERNET_UTIL_BONJOUR__)

uint16_t ethutil_swaps(uint16_t i);
uint32_t ethutil_swapl(uint32_t l);

////////////////////////////////////////

extern uint16_t ethutil_htons(unsigned short hostshort)
{
#if ( SYSTEM_ENDIAN == _ENDIAN_LITTLE_ )
  return ethutil_swaps(hostshort);
#else
  return hostshort;
#endif
}

////////////////////////////////////////

extern int32_t ethutil_htonl(unsigned long hostlong)
{
#if ( SYSTEM_ENDIAN == _ENDIAN_LITTLE_ )
  return ethutil_swapl(hostlong);
#else
  return hostlong;
#endif
}

////////////////////////////////////////

extern uint16_t ethutil_ntohs(unsigned short netshort)
{
#if ( SYSTEM_ENDIAN == _ENDIAN_LITTLE_ )
  return ethutil_swaps(netshort);
#else
  return netshort;
#endif
}

////////////////////////////////////////

extern uint32_t ethutil_ntohl(unsigned long netlong)
{
#if ( SYSTEM_ENDIAN == _ENDIAN_LITTLE_ )
  return ethutil_swapl(netlong);
#else
  return netlong;
#endif
}

////////////////////////////////////////

// #pragma mark -
// #pragma mark Private

uint16_t ethutil_swaps(uint16_t i)
{
  uint16_t ret = 0;
  
  ret = (i & 0xFF) << 8;
  ret |= ((i >> 8) & 0xFF);
  
  return ret;
}

////////////////////////////////////////

uint32_t ethutil_swapl(uint32_t l)
{
  uint32_t ret = 0;
  
  ret = (l & 0xFF) << 24;
  ret |= ((l >> 8) & 0xFF) << 16;
  ret |= ((l >> 16) & 0xFF) << 8;
  ret |= ((l >> 24) & 0xFF);
  
  return ret;
}

////////////////////////////////////////

#endif    // __ETHERNET_UTIL_BONJOUR__

#endif    // __MDNS_ETHERNET_UTIL_IMPL_H__
