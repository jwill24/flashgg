#include "flashgg/DataFormats/interface/EEGammaCandidate.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"

// L. Forthomme (KU)
// (modified from the MuMuGammaCandidate container)

using namespace flashgg;

EEGammaCandidate::EEGammaCandidate() {}

EEGammaCandidate::~EEGammaCandidate() {}

EEGammaCandidate::EEGammaCandidate( edm::Ptr<flashgg::DiElectronCandidate> dielectron, edm::Ptr<flashgg::Photon> photon, edm::Ptr<reco::Vertex> vertex )
{
    addDaughter( *dielectron );
    addDaughter( *photon );
    vertex_ = vertex;
    dieleptr_ = dielectron;
    // Adding momenta
    // Needs its own object - but why?
    // Copied from example
    AddFourMomenta addP4;
    addP4.set( *this );
}

EEGammaCandidate::EEGammaCandidate( edm::Ptr<flashgg::DiElectronCandidate> dielectron,  const flashgg::Photon &photon, edm::Ptr<reco::Vertex> vertex )
{
    addDaughter( *dielectron );
    addDaughter( photon );
    vertex_ = vertex;
    dieleptr_ = dielectron;

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
