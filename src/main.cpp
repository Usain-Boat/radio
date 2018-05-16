#include "mbed.h"
#include "usain_network.h"

void tx_handler()
{
    printf("transmission done\n");
}

void rx_handler(const UsainNetworkMessage &message)
{
    printf("received type: %d\n", message.get_type());
    printf("received message: %s\n", message.get_data());
}

int main()
{
    UsainNetwork network;

    network.register_message_received(callback(rx_handler));
    network.register_message_send(callback(tx_handler));

    while (true)
    {
        // receiver example, uncomment for transmitter
        UsainNetworkMessage m;

        m.set_type(UsainNetworkMessage::POST);
        m.set_data((uint8_t *)"this is a test", 14);

        network.send(m);

        wait(2.0);
    }
}
