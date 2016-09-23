#ifndef FLASHgg_DiJetCandidate_h
#define FLASHgg_DiJetCandidate_h

#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"
#include "flashgg/DataFormats/interface/WeightedObject.h"
#include "TMath.h"

namespace flashgg {

    class DiJetCandidate : public WeightedObject, public reco::CompositeCandidate
    {
    public:
        DiJetCandidate();
        DiJetCandidate( edm::Ptr<pat::Jet>, edm::Ptr<pat::Jet> );
        DiJetCandidate( const pat::Jet&, const pat::Jet& );
        DiJetCandidate( edm::Ptr<pat::Jet>, edm::Ptr<pat::Jet>, edm::Ptr<reco::Vertex> );
        ~DiJetCandidate();

        const pat::Jet *leadingJet() const;
        const pat::Jet *subLeadingJet() const;

        bool operator <( const DiJetCandidate &b ) const { return mass()<b.mass(); } //FIXME
        bool operator >( const DiJetCandidate &b ) const { return mass()>b.mass(); } //FIXME

        float deltaPhi() const;

        DiJetCandidate *clone() const { return ( new DiJetCandidate( *this ) ); }

    private:
        void computeP4();

        edm::Ptr<pat::Jet> jet1_;
        edm::Ptr<pat::Jet> jet2_;

        edm::Ptr<reco::Vertex> vertex_;
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

