/*
 * Copyright (c) 2015, CESAR.
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license. See the LICENSE file for details.
 *
 */

#ifdef ARDUINO
#include <Arduino.h>
#endif

 /**
 * struct phy_driver - driver abstraction for the physical layer
 * @name: driver name
 * @probe: function to initialize the driver
 * @remove: function to close the driver and free its resources
 * @socket: function to create a new socket FD
 * @listen: function to enable incoming connections
 * @accept: function that waits for a new connection and returns a 'pollable' FD
 * @connect: function to connect to a server socket
 *
 * This 'driver' intends to be an abstraction for Radio technologies or
 * proxy for other services using TCP or any socket based communication.
 */

typedef struct {
	const char *name;
	int domain;		/* Protocol domain: Radio nRF24L01, nRF905, ... */
	const uint8_t valid;
	int (*probe) (void);
	void (*remove) (void);

	int (*socket) (void);
	void (*close) (int sockfd);
	int (*listen) (int srv_sockfd);
	int (*accept) (int srv_sockfd);
	int (*connect) (int cli_sockfd, uint8_t to_addr);
	size_t (*recv) (int sockfd, void *buffer, size_t len);
	size_t (*send) (int sockfd, const void *buffer, size_t len);
} phy_driver;
