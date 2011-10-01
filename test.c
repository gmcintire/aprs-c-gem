#include "fap.h"

int main()
{
        char* input;
	char* packet;
        unsigned int input_len;
//        fap_packet_t* packet;

        fap_init();

        // Read TNC2-formatted input for example from APRS-IS.
	packet = "SR5NRV>APNX03,qAR,SR5GK:;439.350WM*111111z5216.19N/02107.21ErT127 -7600kHz R99k SR5WA";
	input_len = sizeof (packet);

        // Process the packet.
        packet = fap_parseaprs(input, input_len, 0);
        printf("Got packet from %s.\n", packet->src_callsign);

        fap_free(packet);

        fap_cleanup();

//        return EXIT_SUCCESS;
}

