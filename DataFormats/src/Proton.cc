#include "flashgg/DataFormats/interface/Proton.h"

using namespace flashgg;

Proton::Proton() : TotemRPLocalTrack()
{}

Proton::~Proton()
{}

Proton::Proton( const TotemRPLocalTrack &aproton ) : TotemRPLocalTrack( aproton )
{}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

