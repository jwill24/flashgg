#include "flashgg/DataFormats/interface/DiProtonCandidate.h"

using namespace flashgg;

DiProtonCandidate::DiProtonCandidate() {}

DiProtonCandidate::~DiProtonCandidate() {}

DiProtonCandidate::DiProtonCandidate( edm::Ptr<flashgg::Proton> proton1, edm::Ptr<flashgg::Proton> proton2 ) :
    //proton1_( &(*proton1) ), proton2_( &(*proton2) )
    proton1_( proton1 ), proton2_( proton2 )
{
    /*addDaughter( proton1 );
    addDaughter( proton2 );
    AddFourMomenta addP4;
    addP4.set( *this );*/
}


// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

