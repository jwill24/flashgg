#include "flashgg/DataFormats/interface/ProtonTrack.h"

using namespace flashgg;

ProtonTrack::ProtonTrack()
{}

ProtonTrack::~ProtonTrack()
{}

ProtonTrack::ProtonTrack( unsigned short det_id, const TotemRPLocalTrack& arplt ) :
    TotemRPLocalTrack(arplt), det_id_(det_id)
{}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

