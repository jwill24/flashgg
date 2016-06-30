#ifndef FLASHgg_Proton_h
#define FLASHgg_Proton_h

#include "DataFormats/CTPPSReco/interface/TotemRPLocalTrack.h"
#include "flashgg/DataFormats/interface/WeightedObject.h"

namespace flashgg {

    class Proton : public TotemRPLocalTrack, public WeightedObject
    {

    public:
        Proton();
        Proton( const TotemRPLocalTrack & );
        ~Proton();

        Proton *clone() const { return ( new Proton( *this ) ); }

    private:
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

