#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "flashgg/DataFormats/interface/DiProtonCandidate.h"

#include <map>

#include <iostream>

using namespace edm;
using namespace std;

namespace flashgg {

    class DiProtonProducer : public EDProducer
    {

    public:
        DiProtonProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;
        EDGetTokenT<View<flashgg::Proton> > protonToken_;
        double sqrtS_;
    };

    DiProtonProducer::DiProtonProducer( const ParameterSet &iConfig ) :
        protonToken_( consumes<View<flashgg::Proton> >( iConfig.getParameter<InputTag> ( "ProtonTag" ) ) ),
        sqrtS_( iConfig.getParameter<double> ( "SqrtS" ) )
    {
        produces<vector<flashgg::DiProtonCandidate> >();
    }

    void DiProtonProducer::produce( Event &evt, const EventSetup & )
    {
        Handle<View<flashgg::Proton> > protons;
        evt.getByToken( protonToken_, protons );

        auto_ptr<vector<DiProtonCandidate> > diProtonColl( new vector<DiProtonCandidate> );

        for( unsigned int i = 0 ; i < protons->size() ; i++ ) {

            Ptr<flashgg::Proton> pp1 = protons->ptrAt( i );
            reco::ProtonTrack::Side side1 = pp1->side();

            for( unsigned int j = i + 1 ; j < protons->size() ; j++ ) {
                Ptr<flashgg::Proton> pp2 = protons->ptrAt( j );
                if ( pp2->side()==side1 ) continue; // we only keep proton pairs from opposite side

                Ptr<flashgg::Proton> p1 = pp1, p2 = pp2;
                if ( pp1->side()==reco::ProtonTrack::RightSide ) {
                    p1 = pp2;
                    p2 = pp1;
                }

                DiProtonCandidate dipro( p1, p2 );

                const float rel_xi = std::sqrt( std::pow( p1->xiError()/p1->xi(), 2 ) + std::pow( p2->xiError()/p2->xi(), 2 ) );
                const float mass = sqrtS_*1.e3 * std::sqrt( p1->xi() * p2->xi() ),
                            rapidity = 0.5 * std::log( p2->xi() / p1->xi() );

                dipro.setMass( mass, mass/2. * rel_xi );
                dipro.setRapidity( rapidity, 0.5 * rel_xi );

                // store the diproton into the collection
                diProtonColl->push_back( dipro );
            }
        }
        // Sort the final collection (descending) and put it in the event
        std::sort( diProtonColl->begin(), diProtonColl->end(), greater<DiProtonCandidate>() );

        evt.put( diProtonColl );
    }
}

typedef flashgg::DiProtonProducer FlashggDiProtonProducer;
DEFINE_FWK_MODULE( FlashggDiProtonProducer );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

