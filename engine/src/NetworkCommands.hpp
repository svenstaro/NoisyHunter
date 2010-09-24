#ifndef NETWORKCOMMANDS_HPP
#define NETWORKCOMMANDS_HPP

namespace Engine {

enum NetworkCommand {
	// If this is sent client->server, the client is requesting being added
	// to the server's list of known clients.
	// If this is sent server->client, the client is being notified of a new
	// accepted client.
	NETCMD_CLIENTADD = 0x00,

	// If this is sent client->server, the client is signaling a good-bye
	// to the server.
	// If this is sent server->client, the client is forcefully being removed.
	NETCMD_CLIENTQUIT = 0x01,

	// If this is sent client->server, a client is requesting an entity to be
	// added.
	// If this is sent server->client, the client is being notified of a new 
	// entity.
	NETCMD_ENTITYADD = 0x02,

	// If this is sent client->server, a client is requesting an entity to 
	// start an action. An action is defined in a concrete entity's 
	// EntityAction enum. This could be ENTITYMOVE or ENTITYSHOOT, for example.
	// If this is sent server->client, the client is being notified of an
	// entity's action. This is useful for interpolating.
	NETCMD_ENTITYACTION = 0x03,

	// If this is sent client->server, ALL HELL BREAKS LOSE
	// If this is sent server->client, the client is being notified of the
	// complete data of an entity. This info needs to be deserialized.
	NETCMD_ENTITYINFO = 0x04,

	// If this is sent client->server, a client is requesting a chat message
	// to be posted to all other clients.
	// If this is sent server->client, the client is being sent a chat message.
	NETCMD_CHATMESSAGE = 0x06
};

}

#endif
