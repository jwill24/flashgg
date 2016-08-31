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

        void setMass( float m, float m_err ) {
            m_ = m;
            m_err_ = m_err;
        }
        float mass() const { return m_; }
        float massError() const { return m_err_; }

        void setRapidity( float rap, float rap_err ) {
            rap_ = rap;
            rap_err_ = rap_err;
        }
        float rapidity() const { return rap_; }
        float rapidityError() const { return rap_err_; }

        bool operator <( const DiProtonCandidate &b ) const { return mass()<b.mass(); } //FIXME
        bool operator >( const DiProtonCandidate &b ) const { return mass()>b.mass(); } //FIXME

        DiProtonCandidate *clone() const { return ( new DiProtonCandidate( *this ) ); }

    private:
        
        float m_, m_err_;
        float rap_, rap_err_;

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

