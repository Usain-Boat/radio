//
// Created by Jamie on 21-4-2018.
//

#include "usain_network_message.h"

UsainNetworkMessage::UsainNetworkMessage()
{

}

UsainNetworkMessage::UsainNetworkMessage(uint8_t *src, uint8_t size)
{
    from_byte_array(src, size);
}

UsainNetworkMessage::message_t UsainNetworkMessage::get() const
{
    return _current_message;
}

UsainNetworkMessage::message_type_t UsainNetworkMessage::get_type() const
{
    return static_cast<message_type_t>(_current_message.type);
}

uint8_t UsainNetworkMessage::get_source() const
{
    return _current_message.source;
}

uint8_t UsainNetworkMessage::get_destination() const
{
    return _current_message.destination;
}

uint8_t UsainNetworkMessage::get_data_size() const
{
    return _current_message.data_size;
}

const uint8_t *UsainNetworkMessage::get_data() const
{
    return _current_message.data;
}

void UsainNetworkMessage::set_type(UsainNetworkMessage::message_type_t type)
{
    _current_message.type = type;
}

void UsainNetworkMessage::set_source(uint8_t source)
{
    _current_message.source = source;
}

void UsainNetworkMessage::set_destination(uint8_t destination)
{
    _current_message.destination = destination;
}

void UsainNetworkMessage::set_data(uint8_t *data, uint8_t size)
{
    if(size > 246)
        error("Error: network message overflow");

    memcpy(_current_message.data, data, size);
    _current_message.data_size = size;
}

void UsainNetworkMessage::from_byte_array(uint8_t src[], uint8_t size)
{
    memcpy(&_current_message, src, size);
}

uint8_t UsainNetworkMessage::to_byte_array(uint8_t *dst) const
{
    uint8_t total_size = _current_message.data_size + 10;

    memcpy(dst, &_current_message, total_size); // 10 bytes of header + data size

    return total_size;
}
