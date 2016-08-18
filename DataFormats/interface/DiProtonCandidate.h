#ifndef FLASHgg_DiProtonCandidate_h
#define FLASHgg_DiProtonCandidate_h

#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Common/interface/View.h"
//#include "DataFormats/Candidate/interface/CompositeCandidate.h" 
//#include "CommonTools/CandUtils/interface/AddFourMomenta.h" 
#include "flashgg/DataFormats/interface/Proton.h"
#include "flashgg/DataFormats/interface/WeightedObject.h"

namespace flashgg {

    class DiProtonCandidate : public WeightedObject
    {
    public:
        DiProtonCandidate();
        DiProtonCandidate( edm::Ptr<flashgg::Proton>, edm::Ptr<flashgg::Proton> );
        ~DiProtonCandidate();

        const flashgg::Proton *proton1() const { return proton1_.get(); }
        const flashgg::Proton *proton2() const { return proton2_.get(); }

        void setM( float val ) { m_ = val; }
        float mass() const { return m_; }
        void setDeltaM( float val ) { dm_ = val; }
        float deltaMass() const { return dm_; }

        void setRapidity( float val ) { rap_ = val; }
        float rapidity() const { return rap_; }
        void setDeltaRapidity( float val ) { drap_ = val; }
        float deltaRapidity() const { return drap_; }

        bool operator <( const DiProtonCandidate &b ) const { return mass()<b.mass(); } //FIXME
        bool operator >( const DiProtonCandidate &b ) const { return mass()>b.mass(); } //FIXME

        DiProtonCandidate *clone() const { return ( new DiProtonCandidate( *this ) ); }

    private:
        
        float m_;
        float dm_;
        float rap_;
        float drap_;

        edm::Ptr<flashgg::Proton> proton1_;
        edm::Ptr<flashgg::Proton> proton2_;
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

