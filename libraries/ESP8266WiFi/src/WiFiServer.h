/*
  WiFiServer.h - Library for Arduino Wifi shield.
  Copyright (c) 2011-2014 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified by Ivan Grokhotkov, December 2014 - esp8266 support
*/

#ifndef wifiserver_h
#define wifiserver_h

extern "C" {
  #include "include/wl_definitions.h"
#if 1	//dc42
  #include "lwip/err.h"			// for err_t
#endif

  struct tcp_pcb;
}

#include "Server.h"
#include "IPAddress.h"

class ClientContext;
class WiFiClient;

class WiFiServer : public Server {
private:
  uint16_t _port;
  IPAddress _addr;
  tcp_pcb* _pcb;

  ClientContext* _unclaimed;
  ClientContext* _discarded;
  bool _noDelay = false;

public:
  WiFiServer(IPAddress addr, uint16_t port);
  WiFiServer(uint16_t port);
  virtual ~WiFiServer() {}
  WiFiClient available(uint8_t* status = NULL);
  bool hasClient();
  void begin();
  void setNoDelay(bool nodelay);
  bool getNoDelay();
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buf, size_t size);
  uint8_t status();
  void close();
  void stop();

  using Print::write;

protected:
#if 1	// dc42
  err_t _accept(tcp_pcb* newpcb, err_t err);
#else
  long _accept(tcp_pcb* newpcb, long err);
#endif
  void   _discard(ClientContext* client);

#if 1	// dc42
  static err_t _s_accept(void *arg, tcp_pcb* newpcb, err_t err);
#else
  static long _s_accept(void *arg, tcp_pcb* newpcb, long err);
#endif
  static void _s_discard(void* server, ClientContext* ctx);
};

#endif
