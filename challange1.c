/* 
    # Data Packet Corruption Detection
    * In a Wireless communciation device, multiple data packets are transferred over the air. 
    * It is possible that data might get corrupted or lost before it reaches the destination.
    * Create a method to identify if a data packet is corrupted
    * Assume below format for the data packet

    ```
    #define MAX_PACKET_DATA_LENGTH (50)

    typedef struct data_packet_t{
        uint8_t id;
        uint8_t data_length;
        uint8_t data[MAX_PACKET_DATA_LENGTH];
        uint16_t crc;
    }data_packet_t;

*/

#include <stdio.h>
#include <stdint.h>

#define MAX_PACK_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACK_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

uint16_t calculate_cr(const uint8_t *data, size_t length) {
    uint16_t crc = 0xFFFF;  // Initial CRC value

    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x0001)
                crc = (crc >> 1) ^ 0xA001;  // XOR with the CRC-16 polynomial
            else
                crc >>= 1;
        }
    }

    return crc;
}

int is_packet_corrupted(const data_packet_t *packet) {
    uint16_t calculated_cr = calculate_cr(packet->data, packet->data_length);

    if (calculated_crc != packet->crc)
        return 1;  // Packet is corrupted
    else
        return 0;  // Packet is not corrupted
}