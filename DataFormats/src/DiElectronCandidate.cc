#include "flashgg/DataFormats/interface/DiElectronCandidate.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"

// L. Forthomme (KU)
// (modified from DiMuonCandidate container)

using namespace flashgg;

DiElectronCandidate::DiElectronCandidate() {}

DiElectronCandidate::~DiElectronCandidate() {}

DiElectronCandidate::DiElectronCandidate( edm::Ptr<pat::Electron> ele1, edm::Ptr<pat::Electron> ele2 )
{
    addDaughter( *ele1 );
    addDaughter( *ele2 );

    // Adding momenta
    // Needs its own object - but why?
    // Copied from example
    AddFourMomenta addP4;
    addP4.set( *this );
}

DiElectronCandidate::DiElectronCandidate( const pat::Electron &ele1, const pat::Electron &ele2 )
{
    addDaughter( ele1 );
    addDaughter( ele2 );

    // Adding momenta
    // Needs its own object - but why?
    // Copied from example
    AddFourMomenta addP4;
    addP4.set( *this );
}

DiElectronCandidate::DiElectronCandidate( edm::Ptr<pat::Electron> ele1, edm::Ptr<pat::Electron> ele2, edm::Ptr<reco::Vertex> dil_vertex ) :
    vertex_(dil_vertex)
{
    addDaughter( *ele1 );
    addDaughter( *ele2 );

    // Adding momenta
    // Needs its own object - but why?
    // Copied from example
    AddFourMomenta addP4;
    addP4.set( *this );
}

const pat::Electron *DiElectronCandidate::leadingElectron() const
{
    if( daughter( 0 )->pt() > daughter( 1 )->pt() ) {
        return dynamic_cast<const pat::Electron *>( daughter( 0 ) );
    } else {
        return dynamic_cast<const pat::Electron *>( daughter( 1 ) );
    }
}

const pat::Electron *DiElectronCandidate::subleadingElectron() const
{
    if( daughter( 0 )->pt() > daughter( 1 )->pt() ) {
        return dynamic_cast<const pat::Electron *>( daughter( 1 ) );
    } else {
        return dynamic_cast<const pat::Electron *>( daughter( 0 ) );
    }
}

float DiElectronCandidate::deltaPhi() const
{
    float dphi = leadingElectron()->phi()-subleadingElectron()->phi();
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
