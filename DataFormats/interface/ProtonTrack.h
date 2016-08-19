#ifndef FLASHgg_ProtonTrack_h
#define FLASHgg_ProtonTrack_h

#include "DataFormats/CTPPSReco/interface/TotemRPLocalTrack.h"
#include "flashgg/DataFormats/interface/WeightedObject.h"

namespace flashgg {

    class ProtonTrack : public TotemRPLocalTrack, public WeightedObject
    {

    public:
        //FIXME to be replaced by a TotemRPDetId... eventually
        enum Station { FarStation = 0, NearStation = 1 };
        enum Side { LeftSide = -1, RightSide = 1 };

        ProtonTrack();
        ProtonTrack( unsigned short, const TotemRPLocalTrack & );
        ~ProtonTrack();

        ProtonTrack *clone() const { return ( new ProtonTrack( *this ) ); }

        inline void setDetId(unsigned int rpid) { det_id_ = rpid; }
        inline unsigned int detId() const { return det_id_; }

        inline Station station() const { return (det_id_%100==2) ? NearStation : FarStation; } // 003/103->F, 002/102->N
        inline Side    side()    const { return (det_id_/100==0) ? LeftSide    : RightSide;  } // 002/003->L, 102/103->R

    private:
        unsigned int det_id_;
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

