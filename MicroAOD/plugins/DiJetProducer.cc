#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "flashgg/DataFormats/interface/DiJetCandidate.h"

#include <map>

#include <iostream>

using namespace edm;
using namespace std;

namespace flashgg {

    class DiJetProducer : public EDProducer
    {

    public:
        DiJetProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;
        EDGetTokenT<View<pat::Jet> > jetToken_;

        double minJetPT_, maxJetEta_;

    };

    DiJetProducer::DiJetProducer( const ParameterSet &iConfig ) :
        jetToken_( consumes<View<pat::Jet> >( iConfig.getParameter<InputTag> ( "JetTag" ) ) ),
        minJetPT_( iConfig.getParameter<double> ( "minJetPT" ) ),
        maxJetEta_( iConfig.getParameter<double> ( "maxJetEta" ) )
    {
        produces<vector<flashgg::DiJetCandidate> >();
    }

    void DiJetProducer::produce( Event &evt, const EventSetup & )
    {
        Handle<View<pat::Jet> > jets;
        evt.getByToken( jetToken_, jets );

        unique_ptr<vector<DiJetCandidate> > diJetColl( new vector<DiJetCandidate> );

        for( unsigned int i = 0 ; i < jets->size() ; i++ ) {

            Ptr<pat::Jet> jet1 = jets->ptrAt( i );

            const double pt1 = jet1->pt();
            const double eta1 = jet1->eta();
            if( pt1 < minJetPT_ || fabs( eta1 ) > maxJetEta_ ) { continue; }

            for( unsigned int j = i + 1 ; j < jets->size() ; j++ ) {
                Ptr<pat::Jet> jet2 = jets->ptrAt( j );

                const double pt2 = jet2->pt();
                const double eta2 = jet2->eta();
                if( pt2 < minJetPT_ || fabs( eta2 ) > maxJetEta_ ) { continue; }

                Ptr<pat::Jet> LeadJet = jet1;
                Ptr<pat::Jet> SubLeadJet = jet2;
                if( pt2 > pt1 ) {
                    LeadJet = jet2;
                    SubLeadJet = jet1;
                }

                DiJetCandidate dijet( LeadJet, SubLeadJet );

                std::cout << "------> new dijet with pt=" << dijet.pt() << ", mass=" << dijet.mass() << std::endl;

                // store the dijet into the collection
                diJetColl->push_back( dijet );
            }
        }
        // Sort the final collection (descending) and put it in the event
        std::sort( diJetColl->begin(), diJetColl->end(), greater<DiJetCandidate>() );

        evt.put( std::move( diJetColl ) );
    }
}

typedef flashgg::DiJetProducer FlashggDiJetProducer;
DEFINE_FWK_MODULE( FlashggDiJetProducer );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

