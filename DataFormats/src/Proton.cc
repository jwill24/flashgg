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
{
    /*for (std::map<unsigned int,ProtonTrack>::const_iterator p=aprotonarm.begin(); p!=aprotonarm.end(); p++)
    {
        if (p->first==  2) nl_track_ = p->second;
        if (p->first==102) nr_track_ = p->second;
        if (p->first==  3) fl_track_ = p->second;
        if (p->first==103) fr_track_ = p->second;
    }
    if (nl_track_.isValid() && fl_track_.isValid()) side_ = -1; // left side proton
    if (nr_track_.isValid() && fr_track_.isValid()) side_ = +1; // right side proton*/
}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

