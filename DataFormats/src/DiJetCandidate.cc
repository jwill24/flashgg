#include "flashgg/DataFormats/interface/DiJetCandidate.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"

// L. Forthomme (KU)
// (modified from DiMuonCandidate container)

using namespace flashgg;

DiJetCandidate::DiJetCandidate() {}

DiJetCandidate::~DiJetCandidate() {}

DiJetCandidate::DiJetCandidate( edm::Ptr<pat::Jet> jet1, edm::Ptr<pat::Jet> jet2 )
{
    addDaughter( *jet1 );
    addDaughter( *jet2 );

    // Adding momenta
    // Needs its own object - but why?
    // Copied from example
    AddFourMomenta addP4;
    addP4.set( *this );
}

DiJetCandidate::DiJetCandidate( const pat::Jet &jet1, const pat::Jet &jet2 )
{
    addDaughter( jet1 );
    addDaughter( jet2 );

    // Adding momenta
    // Needs its own object - but why?
    // Copied from example
    AddFourMomenta addP4;
    addP4.set( *this );
}

const pat::Jet *DiJetCandidate::leadingJet() const
{
    if( daughter( 0 )->pt() > daughter( 1 )->pt() ) {
        return dynamic_cast<const pat::Jet *>( daughter( 0 ) );
    } else {
        return dynamic_cast<const pat::Jet *>( daughter( 1 ) );
    }
}

const pat::Jet *DiJetCandidate::subleadingJet() const
{
    if( daughter( 0 )->pt() > daughter( 1 )->pt() ) {
        return dynamic_cast<const pat::Jet *>( daughter( 1 ) );
    } else {
        return dynamic_cast<const pat::Jet *>( daughter( 0 ) );
    }
}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
