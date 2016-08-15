#ifndef FLASHgg_DiJetCandidate_h
#define FLASHgg_DiJetCandidate_h

#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

// L. Forthomme (KU)
// (modified from DiMuonCandidate container)

namespace flashgg {
    class DiJetCandidate : public reco::CompositeCandidate
    {
    public:
        DiJetCandidate();
        DiJetCandidate( edm::Ptr<pat::Jet>, edm::Ptr<pat::Jet> );
        DiJetCandidate( const pat::Jet &, const pat::Jet & );
        ~DiJetCandidate();

        const pat::Jet *leadingJet() const;
        const pat::Jet *subleadingJet() const;

    private:

    };

}


#endif

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
