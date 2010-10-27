#ifndef IOPACKET_HPP
#define IOPACKET_HPP

#include <SFML/Network.hpp>
#include <string>

namespace Engine{

class IOPacket {
public:
	IOPacket(bool stream_out, sf::Packet packet);
    ~IOPacket();

    IOPacket& operator & (sf::Int8      &data);
    IOPacket& operator & (sf::Uint8     &data);
    IOPacket& operator & (sf::Int16     &data);
    IOPacket& operator & (sf::Uint16    &data);
    IOPacket& operator & (sf::Int32     &data);
    IOPacket& operator & (sf::Uint32    &data);
    IOPacket& operator & (float         &data);
    IOPacket& operator & (double        &data);
    IOPacket& operator & (char          *data);
    IOPacket& operator & (std::string   &data);
    IOPacket& operator & (wchar_t       *data);
    IOPacket& operator & (std::wstring  &data);
    IOPacket& operator & (bool          &data);

	const sf::Packet& GetPacket() const;

	bool IsStreamOut() const;
private:
    sf::Packet mPacket;
    bool mStreamOut;

};

}

#endif
