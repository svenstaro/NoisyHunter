#ifndef NETWORKCOMMAND_HPP
#define NETWORKCOMMAND_HPP

namespace Engine {

enum NetworkCommand {
	// This is an empty packet for debugging purposes. If it is handled,
	// something probably went wrong.
	NETCMD_EMPTY = 0x00,

	// If this is sent client->server, the client is requesting being added
	// to the server's list of known clients. Basically, this is a handshake.
	// Packet structure is:
	// [sf::Uint16(NETCMD_CLIENTADD), std::string(client_name)]
	// If this is sent server->client, the client is being notified of a new
	// accepted client.
	// Packet structure is: 
	// [sf::Uint16(NETCMD_CLIENTADD), std::string(client_name), sf::Uint16(client_id)]
	NETCMD_CLIENTADD = 0x01,

	// If this is sent client->server, the client is signaling a good-bye
	// to the server.
	// Packet structure is:
	// [sf::Uint16(NETCMD_CLIENTQUIT)]
	// If this is sent server->client, the client is being notified that
	// another client left the server. If this is the same client, the client
	// is being forcefully removed.
	// Packet structure is:
	// [sf::Uint16(NETCMD_CLIENTQUIT), std::string(client_name),
	//  std::string(reason)]
	NETCMD_CLIENTQUIT = 0x02,

	// If this is sent client->server, the client is responding to the server's
	// last ping request. This is used to measure client latency and doubles
	// as a keep-alive.
	// Packet structure is:
	// [sf::Uint16(NETCMD_CLIENTPING)]
	// If this is sent server->client, the client is being queried for latency.
	// The client is expected to simply respond with the same package. 
	// This is used to measure latency and doubles as a keep-alive.
	// Packet structure is:
	// [sf::Uint16(NETCMD_CLIENTPING)]
	NETCMD_CLIENTPING = 0x04,

	// If this is sent client->server, the server is being queried for latency.
	// The server is expected to simply respond with the same package. 
	// This is used to measure latency and doubles as a keep-alive.
	// Packet structure is:
	// [sf::Uint16(NETCMD_SERVERPING)]
	// If this is sent server->client, the server is responding to a client's
	// last ping request. This is used to measure server latency and doubles
	// as a keep-alive.
	// Packet structure is:
	// [sf::Uint16(NETCMD_SERVERPING)]
	NETCMD_SERVERPING = 0x10,

	// If this is sent client->server, ALL HELL BREAKS LOOSE!
	// If this is sent server->client, the client is being notified of a new 
	// entity.
	// Packet structure is:
	// [sf::Uint16(NETCMD_ENTITYADD), sf::Uint16(entity_id), sf::Uint16(unique_id)]
	NETCMD_ENTITYADD = 0x20,

	// If this is sent client->server, a client is requesting an entity to 
	// start an action. An action is defined in a concrete entity's 
	// EntityAction enum. This could be ENTITYMOVE or ENTITYSHOOT, for example.
	// Packet structure is:
	// [sf::Uint16(NETCMD_ENTITYACTION), sf::Uint16(game_entity_action_id),
	//	sf::Uint16(unique_id), OPTIONAL_STREAMED_PARAMETERS]
	// If this is sent server->client, the client is being notified of an
	// entity's action. This is useful for interpolating.
	// Packet structure is:
	// [sf::Uint16(NETCMD_ENTITYACTION), sf::Uint16(game_entity_action_id),
	//	sf::Uint16(unique_id), OPTIONAL_STREAMED_PARAMETERS]
	NETCMD_ENTITYACTION = 0x21,

	// If this is sent client->server, ALL HELL BREAKS LOOSE!
	// Packet structure is:
	// NONE. THIS CANNOT BE SENT TO THE SERVER!
	// If this is sent server->client, the client is being notified of the
	// complete data of an entity. This info needs to be deserialized.
	// Packet structure is:
	// [sf::Uint16(NETCMD_ENTITYINFO), sf::Uint16(unique_id),
	//  sf::Uint16(entity_id), Engine::Entity(entity)]
	NETCMD_ENTITYINFO = 0x22,

	// If this is sent client->server, ALL HELL BREAKS LOOSE!
	// If this is sent server-client, the client should delete the local instance of the given entity.
	// Packet Structure is:
	// [sf::Uint16(NETCMD_ENTITYINFO), sf::Uint16(unique_id)]
	NETCMD_ENTITYDEL = 0x23,

	// If this is sent client->server, a client is requesting a chat message
	// to be posted to all other clients.
	// Packet structure is:
	// [sf::Uint16(NETCMD_CHATMESSAGE), std::string(message)]
	// If this is sent server->client, the client is being sent a chat message.
	// It also contains the name of the originating client.
	// Packet structure is:
	// [sf::Uint16(NETCMD_CHATMESSAGE), std::string(client_name),
	//  std::string(message)]
	NETCMD_CHATMESSAGE = 0x30,

	// If this is sent client->server, a client tells the server about an interaction
	// the user performed. An interaction is defined in a general game-specific enum.
	// This could be WALKTOPOSITION or DELETEALLENTITIES, for example. The server should
	// validate the interaction.
	// Packet structure is:
	// [sf::Uint16(NETCMD_INTERACTION), sf::Uint16(game_interaction_id),
	// OPTIONAL_STREAMED_PARAMETERS]
	// If this is sent server->client, ALL HELL BREAKS LOOSE!
	NETCMD_INTERACTION = 0x31
};

}

#endif
