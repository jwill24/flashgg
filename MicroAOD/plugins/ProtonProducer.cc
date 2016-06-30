// system include files
#include <memory>
// user include files
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/CTPPSReco/interface/TotemRPLocalTrack.h"
#include "flashgg/DataFormats/interface/Proton.h"

using namespace std;
using namespace edm;

namespace flashgg {

    class ProtonProducer : public edm::EDProducer
    {
    public:
        ProtonProducer( const edm::ParameterSet & );

    private:
        void produce( edm::Event &, const edm::EventSetup & );

        edm::EDGetTokenT<View<TotemRPLocalTrack> > localTracksToken_;

    };

    ProtonProducer::ProtonProducer( const ParameterSet &iConfig ):
        localTracksToken_( consumes<View<TotemRPLocalTrack> >( iConfig.getParameter<InputTag>( "protonTag" ) ) )
    {
        produces<vector<flashgg::Proton> >();
    }

    void ProtonProducer::produce( Event &evt, const EventSetup & )
    {
        Handle<View<TotemRPLocalTrack> >  prptracks;
        evt.getByToken( localTracksToken_, prptracks );

        std::auto_ptr<vector<flashgg::Proton> > protonColl( new vector<flashgg::Proton> );

        for( unsigned int trackIndex = 0; trackIndex < prptracks->size(); trackIndex++ ) {
            Ptr<TotemRPLocalTrack> prptrack = prptracks->ptrAt( trackIndex );
            flashgg::Proton frpp = flashgg::Proton( *prptrack );

            protonColl->push_back( frpp );
        }
        evt.put( protonColl );
    }
}

typedef flashgg::ProtonProducer FlashggProtonProducer;
DEFINE_FWK_MODULE( FlashggProtonProducer );

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

