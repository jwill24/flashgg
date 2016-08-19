#include "flashgg/DataFormats/interface/Proton.h"

using namespace flashgg;

Proton::Proton() :
    valid_(false)
{}

Proton::~Proton()
{}

Proton::Proton( const ProtonTrack& atrack, const ProtonTrack::Side& aside ) :
    valid_(true), side_(aside)
{
    tracks_map_.insert( std::pair<TotemRPDetId,ProtonTrack>( atrack.detId(), atrack ) );
}

Proton::Proton( const ProtonTrack& aneartrack, const ProtonTrack& afartrack, const ProtonTrack::Side& aside ) :
    valid_(true), side_(aside)
{
    tracks_map_.insert( std::pair<TotemRPDetId,ProtonTrack>( afartrack.detId(),  afartrack ) );
    tracks_map_.insert( std::pair<TotemRPDetId,ProtonTrack>( aneartrack.detId(), aneartrack ) );
}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

