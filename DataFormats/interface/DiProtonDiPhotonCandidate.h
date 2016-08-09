#ifndef FLASHgg_DiProtonDiPhotonCandidate_h
#define FLASHgg_DiProtonDiPhotonCandidate_h

#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h" 
#include "CommonTools/CandUtils/interface/AddFourMomenta.h" 
#include "flashgg/DataFormats/interface/DiProtonCandidate.h"
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/WeightedObject.h"

namespace flashgg {

    class DiProtonDiPhotonCandidate : public reco::CompositeCandidate, public WeightedObject
    {
    public:
        DiProtonDiPhotonCandidate();
        DiProtonDiPhotonCandidate( edm::Ptr<flashgg::DiProtonCandidate>, edm::Ptr<flashgg::DiPhotonCandidate> );
        ~DiProtonDiPhotonCandidate();

        const flashgg::DiProtonCandidate *diproton() const { return diproton_.get(); }
        const flashgg::DiPhotonCandidate *diphoton() const { return diphoton_.get(); }

        float rpM() const { return diproton_->M(); }
        float rpDeltaM() const { return diproton_->deltaM(); }
        float cmsM() const { return diphoton_->mass(); }

        float rpRapidity() const { return diproton_->rapidity(); }
        float rpDeltaRapidity() const { return diproton_->deltaRapidity(); }
        float cmsRapidity() const { return ( diphoton_->leadingPhoton()->p4() + diphoton_->subLeadingPhoton()->p4() ).Rapidity(); }

        bool operator <( const DiProtonDiPhotonCandidate &b ) const { return rpM()<b.rpM(); } //FIXME
        bool operator >( const DiProtonDiPhotonCandidate &b ) const { return rpM()>b.rpM(); } //FIXME

        DiProtonDiPhotonCandidate *clone() const { return ( new DiProtonDiPhotonCandidate( *this ) ); }

    private:
        edm::Ptr<flashgg::DiProtonCandidate> diproton_;
        edm::Ptr<flashgg::DiPhotonCandidate> diphoton_;
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

