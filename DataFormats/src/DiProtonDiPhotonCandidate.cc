#include "flashgg/DataFormats/interface/DiProtonDiPhotonCandidate.h"

using namespace flashgg;

DiProtonDiPhotonCandidate::DiProtonDiPhotonCandidate() {}

DiProtonDiPhotonCandidate::~DiProtonDiPhotonCandidate() {}

DiProtonDiPhotonCandidate::DiProtonDiPhotonCandidate( edm::Ptr<flashgg::DiProtonCandidate> dpr, edm::Ptr<flashgg::DiPhotonCandidate> dph ) :
    diproton_( dpr ), diphoton_( dph )
{}


// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

