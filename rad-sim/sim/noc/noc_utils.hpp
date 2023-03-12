#include <booksim_config.hpp>
#include <flit.hpp>
#include <radsim_defines.hpp>
#include <sc_flit.hpp>
#include <systemc.h>

int VCIDFromType(Flit::FlitType type, BookSimConfig *config);
void set_flit_payload(sc_flit &packetization_flit,
                      sc_bv<AXI_TRANSACTION_MAX_WIDTH> &packet_bv, int flit_id);
void set_flit_payload(sc_flit &packetization_flit,
                      sc_bv<AXIS_TRANSACTION_WIDTH> &packet_bv, int flit_id);