// system include files
#include <memory>
// user include files
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/CTPPSReco/interface/Proton.h"
#include "flashgg/DataFormats/interface/Proton.h"

using namespace std;
using namespace edm;

#include <iostream>

namespace flashgg {

    class ProtonProducer : public edm::EDProducer
    {
    public:
        ProtonProducer( const edm::ParameterSet & );
        ~ProtonProducer();

    private:
        void produce( edm::Event &, const edm::EventSetup & );

        edm::EDGetTokenT<vector<reco::Proton> > protonsToken_;

    };

    ProtonProducer::ProtonProducer( const ParameterSet &iConfig ):
        protonsToken_( consumes<vector<reco::Proton> >( iConfig.getParameter<InputTag>( "protonTag" ) ) )
    {
        produces<vector<flashgg::Proton> >();
    }

    ProtonProducer::~ProtonProducer() {}

    void ProtonProducer::produce( Event &evt, const EventSetup & )
    {
        Handle<vector<reco::Proton> >  protons;
        evt.getByToken( protonsToken_, protons );

        std::auto_ptr<vector<flashgg::Proton> > protonColl( new vector<flashgg::Proton> );

        for ( vector<reco::Proton>::const_iterator p = protons->begin(); p < protons->end(); p++ ) {
            if (!p->isValid()) continue;
            protonColl->push_back( flashgg::Proton( *p ) );
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

