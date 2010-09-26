#ifndef NETWORKCOMMANDS_HPP
#define NETWORKCOMMANDS_HPP

namespace Engine {

enum NetworkCommand {
	// If this is sent client->server, the client is requesting being added
	// to the server's list of known clients. Basically, this is a handshake.
	// If this is sent server->client, the client is being notified of a new
	// accepted client.
	// Packge structure is: 
	// [sf::Uint16(NETCMD_CLIENTADD), std::string(client_name)]
	NETCMD_CLIENTADD = 0x00,

	// If this is sent client->server, the client is signaling a good-bye
	// to the server.
	// If this is sent server->client, the client is forcefully being removed.
	NETCMD_CLIENTQUIT = 0x01,

	// If this is sent client->server, the client is responding to the server's
	// last ping request. This is used to measure client latency and doubles
	// as a keep-alive.
	// If this is sent server->client, the client is being queried for latency.
	// The client is expected to simply respond with the same package. 
	// This is used to measure latency and doubles as a keep-alive.
	NETCMD_CLIENTPING = 0x02,

	// If this is sent client->server, the client is requesting the server
	// latency to itself. This doubles as a keep-alive.
	// If this is sent server->client, the server is responding to a client's
	// ping request. This doubles as a keep-alive.
	NETCMD_SERVERPING = 0x10,

	// If this is sent client->server, a client is requesting an entity to be
	// added.
	// If this is sent server->client, the client is being notified of a new 
	// entity.
	NETCMD_ENTITYADD = 0x20,

	// If this is sent client->server, a client is requesting an entity to 
	// start an action. An action is defined in a concrete entity's 
	// EntityAction enum. This could be ENTITYMOVE or ENTITYSHOOT, for example.
	// If this is sent server->client, the client is being notified of an
	// entity's action. This is useful for interpolating.
	NETCMD_ENTITYACTION = 0x21,

	// If this is sent client->server, ALL HELL BREAKS LOSE!
	// If this is sent server->client, the client is being notified of the
	// complete data of an entity. This info needs to be deserialized.
	NETCMD_ENTITYINFO = 0x22,

	// If this is sent client->server, a client is requesting a chat message
	// to be posted to all other clients.
	// Packge structure is: 
	// [sf::Uint16(NETCMD_CHATMESSAGE), std::string(client_name), ]
	// If this is sent server->client, the client is being sent a chat message.
	NETCMD_CHATMESSAGE = 0x30
};

}

#endif
