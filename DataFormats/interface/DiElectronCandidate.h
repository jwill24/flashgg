#ifndef FLASHgg_DiElectronCandidate_h
#define FLASHgg_DiElectronCandidate_h

#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "TMath.h"

// L. Forthomme (KU)
// (modified from DiMuonCandidate container)

namespace flashgg {
    class DiElectronCandidate : public reco::CompositeCandidate
    {
    public:
        DiElectronCandidate();
        DiElectronCandidate( edm::Ptr<pat::Electron>, edm::Ptr<pat::Electron> );
        DiElectronCandidate( const pat::Electron &, const pat::Electron & );
        DiElectronCandidate( edm::Ptr<pat::Electron>, edm::Ptr<pat::Electron>, edm::Ptr<reco::Vertex> );
        ~DiElectronCandidate();

        const pat::Electron *leadingElectron() const;
        const pat::Electron *subleadingElectron() const;
        const edm::Ptr<reco::Vertex> vtx() const { return vertex_; }

        float deltaPhi() const;

        bool IsOSDiElePair() const { return IsOSDiElePair_; }
        void setIsOSDiElePair( bool val ) { IsOSDiElePair_ = val;}

    private:

        edm::Ptr<reco::Vertex> vertex_;

        bool IsOSDiElePair_;

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
