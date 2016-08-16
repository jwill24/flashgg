#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "flashgg/DataFormats/interface/DiElectronCandidate.h"

//-----------J. Tao from IHEP-Beijing--------------

using namespace edm;
using namespace std;

namespace flashgg {

    class DiElectronProducer : public EDProducer
    {

    public:
        DiElectronProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;
        EDGetTokenT<View<pat::Electron> > electronToken_;
        EDGetTokenT<View<reco::Vertex> > vertexToken_;

        double minElePT_;
        double maxEleEta_;
        bool matchVertex_;
        double matchVertexMaxDist2_;

    };

    DiElectronProducer::DiElectronProducer( const ParameterSet &iConfig ) :
        electronToken_( consumes<View<pat::Electron> >( iConfig.getParameter<InputTag> ( "ElectronTag" ) ) ),
        vertexToken_( consumes<View<reco::Vertex> >( iConfig.getParameter<InputTag> ( "VertexTag" ) ) )
    {
        minElePT_ = iConfig.getParameter<double>( "minElectronPT" );
        maxEleEta_ = iConfig.getParameter<double>( "maxElectronEta" );
        matchVertex_ = iConfig.getParameter<bool>( "matchVertex" );
        matchVertexMaxDist2_ = pow( iConfig.getParameter<double>( "maxVertexDist" ), 2 );
        produces<vector<flashgg::DiElectronCandidate> >();
    }

    void DiElectronProducer::produce( Event &evt, const EventSetup & )
    {

        Handle<View<reco::Vertex> > primaryVertices;
        evt.getByToken( vertexToken_, primaryVertices );
        //const PtrVector<reco::Vertex>& pvPointers = primaryVertices->ptrVector();
        edm::Ptr<reco::Vertex> vtx = primaryVertices->ptrAt( 0 ); //pvPointers[0]; //selected vertex 0
        const reco::Vertex myrecovtx = reco::Vertex( *vtx );

        Handle<View<pat::Electron> > electrons;
        evt.getByToken( electronToken_, electrons );
        const std::vector<edm::Ptr<pat::Electron> > &electronPointers = electrons->ptrs();


        auto_ptr<vector<flashgg::DiElectronCandidate> > diElectronColl( new vector<flashgg::DiElectronCandidate> );
        //    cout << "evt.id().event()= " << evt.id().event() << "\tevt.isRealData()= " << evt.isRealData() << "\telectronPointers.size()= " << electronPointers.size() << "\tpvPointers.size()= " << pvPointers.size() << endl;

        for( unsigned int i = 0 ; i < electronPointers.size() ; i++ ) {
            Ptr<pat::Electron> electron1 = electronPointers[i];
            double pt1 = electron1->pt();
            double eta1 = electron1->eta();
            if( pt1 < minElePT_ || fabs( eta1 ) > maxEleEta_ ) { continue; }
            for( unsigned int j = i + 1 ; j < electronPointers.size() ; j++ ) {
                Ptr<pat::Electron> electron2 = electronPointers[j];
                double pt2 = electron2->pt();
                double eta2 = electron2->eta();
                if( pt2 < minElePT_ || fabs( eta2 ) > maxEleEta_ ) { continue; }

                Ptr<pat::Electron> LeadElectron = electronPointers[i];
                Ptr<pat::Electron> SubLeadElectron = electronPointers[j];
                if( pt2 > pt1 ) {
                    LeadElectron = electronPointers[j];
                    SubLeadElectron = electronPointers[i];
                }

                DiElectronCandidate diele;
                if ( matchVertex_ ) {
                    reco::Vertex::Point lVtx = LeadElectron->vertex(), slVtx = SubLeadElectron->vertex();
                    // First check if both the leptons' vertices are compatible with one single vertex
                    if ( ( lVtx-slVtx ).Mag2() > matchVertexMaxDist2_ ) { continue; }

                    // Then find the associated vertex object in the collection (shortest distance approach)
                    int vtx_id = -1;
                    float vtx_dist = 999.;
                    for ( unsigned int k = 0 ; k < primaryVertices->size() ; k++ ) {
                        Ptr<reco::Vertex> vtx = primaryVertices->ptrAt( k );
                        float dist = sqrt( ( vtx->position()-lVtx ).Mag2() ); //FIXME compute wrt leading lepton's vertex or mean?
                        if ( dist<vtx_dist ) {
                            vtx_id = k;
                            vtx_dist = dist;
                        }
                    }
                    if ( vtx_id<0 ) { continue; }
                    const edm::Ptr<reco::Vertex> Vertex = primaryVertices->ptrAt( vtx_id );

                    diele = DiElectronCandidate( LeadElectron, SubLeadElectron, Vertex );
                }
                else {
                    diele = DiElectronCandidate( LeadElectron, SubLeadElectron );
                }

                diele.setIsOSDiElePair( (electron1->charge() * electron2->charge() < 0) );

                // store the dielectron into the collection
                diElectronColl->push_back( diele );
            }
        }
        evt.put( diElectronColl );

    }
}

typedef flashgg::DiElectronProducer FlashggDiElectronProducer;
DEFINE_FWK_MODULE( FlashggDiElectronProducer );

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
