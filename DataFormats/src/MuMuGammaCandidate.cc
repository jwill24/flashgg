#include "flashgg/DataFormats/interface/MuMuGammaCandidate.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"

//-----------J. Tao from IHEP-Beijing--------------

using namespace flashgg;

MuMuGammaCandidate::MuMuGammaCandidate() :
    matchedVertex_(false)
{}

MuMuGammaCandidate::~MuMuGammaCandidate() {}

MuMuGammaCandidate::MuMuGammaCandidate( edm::Ptr<flashgg::DiMuonCandidate> dimuon, edm::Ptr<flashgg::Photon> photon, edm::Ptr<reco::Vertex> vertex ) :
    dimuptr_(dimuon), vertex_(vertex), matchedVertex_(false)
{
    addDaughter( *dimuon );
    addDaughter( *photon );
    // Adding momenta
    // Needs its own object - but why?
    // Copied from example
    AddFourMomenta addP4;
    addP4.set( *this );
}
/*
MuMuGammaCandidate::MuMuGammaCandidate( const flashgg::DiMuonCandidate &dimuon, const flashgg::Photon &photon, edm::Ptr<reco::Vertex> vertex, edm::Ptr<flashgg::DiMuonCandidate> dimuonPtr) :
    dimuptr_(dimuon), vertex_(vertex), matchedVertex_(false)
{
    addDaughter( dimuon );
    addDaughter( photon );

    // Adding momenta
    // Needs its own object - but why?
    // Copied from example
    AddFourMomenta addP4;
    addP4.set( *this );
}
*/

MuMuGammaCandidate::MuMuGammaCandidate( edm::Ptr<flashgg::DiMuonCandidate> dimuon,  const flashgg::Photon &photon, edm::Ptr<reco::Vertex> vertex ) :
    dimuptr_(dimuon), vertex_(vertex), matchedVertex_(false)
{
    addDaughter( *dimuon );
    addDaughter( photon );

    AddFourMomenta addP4;
    addP4.set( *this );
}


// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
