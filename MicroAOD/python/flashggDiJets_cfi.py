import FWCore.ParameterSet.Config as cms

flashggDiJets = cms.EDProducer('FlashggDiJetProducer',
                               JetTag = cms.InputTag('slimmedJets'),
                               VertexTag = cms.InputTag('offlineSlimmedPrimaryVertices'), 
                               ##Parameters                                                
                               minJetPT = cms.double(5.),
                               maxJetEta = cms.double(2.4),
                               matchVertex = cms.bool(False),
                               maxVertexDist = cms.double(0.005)
                               )
