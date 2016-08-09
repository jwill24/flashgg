#ifndef FLASHgg_ProtonTrack_h
#define FLASHgg_ProtonTrack_h

#include "DataFormats/CTPPSReco/interface/TotemRPLocalTrack.h"
#include "flashgg/DataFormats/interface/WeightedObject.h"

namespace flashgg {

    class ProtonTrack : public TotemRPLocalTrack, public WeightedObject
    {

    public:
        enum Arm { FarArm = 0, NearArm = 1 };
        enum Side { LeftSide = -1, RightSide = 1 };

        ProtonTrack();
        ProtonTrack( const TotemRPLocalTrack & );
        ~ProtonTrack();

        ProtonTrack *clone() const { return ( new ProtonTrack( *this ) ); }

        inline void setRPId(unsigned int rpid) { rp_id_ = rpid; }
        inline unsigned int RPId() const { return rp_id_; }

        inline void setArm(const Arm& arm) { arm_ = arm; }
        inline Arm arm() const { return arm_; }

        inline void setSide(const Side& side) { side_ = side; }
        inline Side side() const { return side_; }

    private:
        Arm arm_;
        Side side_;
        unsigned int rp_id_;
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

