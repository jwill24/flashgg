#include "flashgg/DataFormats/interface/Proton.h"

using namespace flashgg;

Proton::Proton() :
    valid_(false)
{}

Proton::~Proton()
{}

Proton::Proton( const ProtonTrack& atrack, const ProtonTrack::Side& aside, const ProtonTrack::Arm& aarm ) :
    valid_(true), side_(aside)
{
    switch (aarm) {
        case ProtonTrack::NearArm: near_track_ = atrack; break;
        case ProtonTrack::FarArm:  far_track_ = atrack;  break;
        default: return;
    }
}

Proton::Proton( const ProtonTrack& aneartrack, const ProtonTrack& afartrack, const ProtonTrack::Side& aside ) :
    valid_(true), near_track_(aneartrack), far_track_(afartrack), side_(aside)
{}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

