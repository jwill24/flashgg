#ifndef FLASHgg_Proton_h
#define FLASHgg_Proton_h

#include "flashgg/DataFormats/interface/ProtonTrack.h"
#include "flashgg/DataFormats/interface/WeightedObject.h"

namespace flashgg {

    class Proton : public WeightedObject
    {

    public:
        Proton();
        Proton( const ProtonTrack&, const ProtonTrack::Side&, const ProtonTrack::Arm& );
        Proton( const ProtonTrack&, const ProtonTrack&, const ProtonTrack::Side& );
        ~Proton();

        Proton *clone() const { return ( new Proton( *this ) ); }

        inline void setValid( bool valid=true ) { valid_ = valid; }
        inline bool isValid() const { return valid_; }

        inline void setSide( const ProtonTrack::Side& side ) { side_ = side; }
        inline ProtonTrack::Side side() const { return side_; }

        inline ProtonTrack nearTrack() const { return near_track_; }
        inline ProtonTrack farTrack() const { return far_track_; }

        inline void setXi( float xi ) { xi_ = xi; }
        inline float xi() const { return xi_; }
        inline void setDeltaXi( float dxi ) { dxi_ = dxi; }
        inline float deltaXi() const { return dxi_; }

    private:
        void computeXi();

        bool valid_;

        ProtonTrack near_track_;
        ProtonTrack far_track_;

        ProtonTrack::Side side_;

        float xi_;
        float dxi_;
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

