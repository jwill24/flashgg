#include "flashgg/DataFormats/interface/ProtonTrack.h"

using namespace flashgg;

ProtonTrack::ProtonTrack()
{}

ProtonTrack::~ProtonTrack()
{}

ProtonTrack::ProtonTrack( unsigned int dec_det_id, const TotemRPLocalTrack& arplt ) :
    TotemRPLocalTrack(arplt), det_id_( TotemRPDetId::decToRawId( dec_det_id * 10 ) )
{}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

