#include "IOPacket.hpp"


namespace Engine{

IOPacket::IOPacket(bool stream_out, sf::Packet packet) {
    mStreamOut = stream_out;
    mPacket = packet;
}
IOPacket::~IOPacket() {}

IOPacket& IOPacket::operator & (sf::Int8      &data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (sf::Uint8     &data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (sf::Int16     &data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (sf::Uint16    &data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (sf::Int32     &data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (sf::Uint32    &data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (float         &data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (double        &data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (char          *data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (std::string   &data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (wchar_t       *data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (std::wstring  &data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (bool          &data) {
    if (mStreamOut) mPacket >> data;
    else           mPacket << data;
    return *this;
}


sf::Packet&  IOPacket::GetPacket() {
    return mPacket;
}

}
