import FWCore.ParameterSet.Config as cms

flashggDiProtons = cms.EDProducer('FlashggDiProtonProducer',
                                  ProtonTag = cms.InputTag('flashggProtons'),
                                  SqrtS     = cms.double( 13.0 ),
                                  )
