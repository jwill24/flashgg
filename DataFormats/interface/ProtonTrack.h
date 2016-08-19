#ifndef FLASHgg_ProtonTrack_h
#define FLASHgg_ProtonTrack_h

#include "DataFormats/CTPPSReco/interface/TotemRPLocalTrack.h"
#include "DataFormats/TotemRPDetId/interface/TotemRPDetId.h" //FIXME will move to...
//#include "DataFormats/CTPPSDetId/interface/TotemRPDetId.h"

#include "flashgg/DataFormats/interface/WeightedObject.h"

namespace flashgg {

    class ProtonTrack : public TotemRPLocalTrack, public WeightedObject
    {

    public:
        enum Station { NearStation = 2, FarStation = 3 };
        enum Side { LeftSide = 0, RightSide = 1 };

        ProtonTrack();
        ProtonTrack( unsigned int, const TotemRPLocalTrack & );
        ~ProtonTrack();

        ProtonTrack *clone() const { return ( new ProtonTrack( *this ) ); }

        inline unsigned int decDetId() const { return TotemRPDetId::rawToDecId( det_id_ ); }
        inline TotemRPDetId detId() const { return det_id_; }

        inline Station station() const { return static_cast<Station>( det_id_.romanPot() ); } //FIXME shouldn't it be detector()?
        inline Side side() const { return static_cast<Side>( det_id_.arm() );  }

    private:
        TotemRPDetId det_id_;
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

