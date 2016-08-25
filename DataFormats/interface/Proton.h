#ifndef FLASHgg_Proton_h
#define FLASHgg_Proton_h

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/CTPPSReco/interface/Proton.h"

#include "flashgg/DataFormats/interface/WeightedObject.h"

namespace flashgg {

    class Proton : public WeightedObject, public reco::Proton
    {

    public:
        Proton();
        Proton( const reco::Proton& );
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

