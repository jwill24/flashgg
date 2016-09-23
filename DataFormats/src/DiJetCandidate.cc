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

    computeP4();
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

    computeP4();
}

DiJetCandidate::DiJetCandidate( edm::Ptr<pat::Jet> jet1, edm::Ptr<pat::Jet> jet2, edm::Ptr<reco::Vertex> dijet_vertex ) :
    vertex_(dijet_vertex)
{
    addDaughter( *jet1 );
    addDaughter( *jet2 );
    setVertex( dijet_vertex->position() );

    // Adding momenta
    // Needs its own object - but why?
    // Copied from example
    AddFourMomenta addP4;
    addP4.set( *this );

    computeP4();
}

const pat::Jet *DiJetCandidate::leadingJet() const
{
    if( daughter( 0 )->pt() > daughter( 1 )->pt() ) {
        return dynamic_cast<const pat::Jet *>( daughter( 0 ) );
    } else {
        return dynamic_cast<const pat::Jet *>( daughter( 1 ) );
    }
}

const pat::Jet *DiJetCandidate::subLeadingJet() const
{
    if( daughter( 0 )->pt() > daughter( 1 )->pt() ) {
        return dynamic_cast<const pat::Jet *>( daughter( 1 ) );
    } else {
        return dynamic_cast<const pat::Jet *>( daughter( 0 ) );
    }
}

void DiJetCandidate::computeP4()
{
    this->setP4( leadingJet()->p4() + subLeadingJet()->p4() );
}

float DiJetCandidate::deltaPhi() const
{
    float dphi = leadingJet()->phi()-subLeadingJet()->phi();
    while (dphi<-TMath::Pi()) dphi += 2.*TMath::Pi();
    while (dphi> TMath::Pi()) dphi -= 2.*TMath::Pi();
    return dphi;
}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
