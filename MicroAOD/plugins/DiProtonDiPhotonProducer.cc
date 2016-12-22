#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "flashgg/DataFormats/interface/DiProtonDiPhotonCandidate.h"

#include <map>

using namespace edm;
using namespace std;

namespace flashgg {

    class DiProtonDiPhotonProducer : public EDProducer
    {

    public:
        DiProtonDiPhotonProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;
        EDGetTokenT<View<flashgg::DiProtonCandidate> > diprotonToken_;
        EDGetTokenT<View<flashgg::DiPhotonCandidate> > diphotonToken_;
    };

    DiProtonDiPhotonProducer::DiProtonDiPhotonProducer( const ParameterSet &iConfig ) :
        diprotonToken_( consumes<View<flashgg::DiProtonCandidate> >( iConfig.getParameter<InputTag> ( "DiProtonTag" ) ) ),
        diphotonToken_( consumes<View<flashgg::DiPhotonCandidate> >( iConfig.getParameter<InputTag> ( "DiPhotonTag" ) ) )
    {
        produces<vector<flashgg::DiProtonDiPhotonCandidate> >();
    }

    void DiProtonDiPhotonProducer::produce( Event &evt, const EventSetup & )
    {
        Handle<View<flashgg::DiProtonCandidate> > dipr;
        evt.getByToken( diprotonToken_, dipr );

        Handle<View<flashgg::DiPhotonCandidate> > diph;
        evt.getByToken( diphotonToken_, diph );

        auto_ptr<vector<DiProtonDiPhotonCandidate> > diProtonPhotonColl( new vector<DiProtonDiPhotonCandidate> );

        for( unsigned int i = 0 ; i < dipr->size() ; i++ ) {
            Ptr<flashgg::DiProtonCandidate> dpr = dipr->ptrAt( i );

            for( unsigned int j = 0 ; j < diph->size() ; j++ ) {
                Ptr<flashgg::DiPhotonCandidate> dph = diph->ptrAt( j );

                DiProtonDiPhotonCandidate dipropho( dpr, dph );

                // store the diproton/diphoton into the collection
                diProtonPhotonColl->push_back( dipropho );
            }
        }
        // Sort the final collection (descending) and put it in the event
        std::sort( diProtonPhotonColl->begin(), diProtonPhotonColl->end(), greater<DiProtonDiPhotonCandidate>() );

        evt.put( diProtonPhotonColl );
    }
}

typedef flashgg::DiProtonDiPhotonProducer FlashggDiProtonDiPhotonProducer;
DEFINE_FWK_MODULE( FlashggDiProtonDiPhotonProducer );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

