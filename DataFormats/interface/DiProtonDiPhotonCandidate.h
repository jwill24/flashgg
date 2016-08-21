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

        float massRP() const { return diproton_->mass(); }
        float massRPError() const { return diproton_->massError(); }
        float massCMS() const { return diphoton_->mass(); }

        float rapidityRP() const { return diproton_->rapidity(); }
        float rapidityRPError() const { return diproton_->rapidityError(); }
        float rapidityCMS() const { return ( diphoton_->leadingPhoton()->p4() + diphoton_->subLeadingPhoton()->p4() ).Rapidity(); }

        bool operator <( const DiProtonDiPhotonCandidate &b ) const { return massRP()<b.massRP(); } //FIXME
        bool operator >( const DiProtonDiPhotonCandidate &b ) const { return massRP()>b.massRP(); } //FIXME

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

