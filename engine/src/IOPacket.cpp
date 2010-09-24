#include "IOPacket.hpp"


namespace Engine{

IOPacket::IOPacket(bool is_output, sf::Packet packet) {
    mIsOutput = is_output;
    mPacket = packet;
}
IOPacket::~IOPacket() {}

IOPacket& IOPacket::operator & (sf::Int8      &data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (sf::Uint8     &data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (sf::Int16     &data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (sf::Uint16    &data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (sf::Int32     &data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (sf::Uint32    &data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (float         &data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (double        &data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (char          *data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (std::string   &data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (wchar_t       *data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (std::wstring  &data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}
IOPacket& IOPacket::operator & (bool          &data) {
    if (mIsOutput) mPacket >> data;
    else           mPacket << data;
    return *this;
}


sf::Packet&  IOPacket::GetPacket() {
    return mPacket;
}

}
