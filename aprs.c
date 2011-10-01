// Include the Ruby headers and goodies
#include "ruby.h"
#include <fap.h>

// Defining a space for information and references about the module to be stored internally
VALUE Aprs = Qnil;

// Prototype for the initialization method - Ruby calls this, not you
void Init_aprs();

//VALUE method_parseaprs(char const* input);
VALUE method_parseaprs(char* input);

// The initialization method for this module
void Init_aprs() {
	Aprs = rb_define_module("Aprs");
	rb_define_method(Aprs, "parse_aprs", method_parseaprs, 1);
}

VALUE method_parseaprs(char* input) {
//  char* input;
  unsigned int input_len;
  fap_packet_t* packet;
  
  fap_init();
  
  // Read TNC2-formatted input for example from APRS-IS.
  input_len = sizeof (input);
  
  // Process the packet.
  packet = fap_parseaprs(input, input_len, 0);

  if ( packet->error_code )
  {
    printf("Failed to parse packet (%s): %s\n", input, fap_explain_error(*packet->error_code));
  }
  else if ( packet->src_callsign )
  {
    printf("Got packet from %s.\n", packet->src_callsign);
  }

  fap_free(packet);
  
  fap_cleanup();
  
  return EXIT_SUCCESS;
}

