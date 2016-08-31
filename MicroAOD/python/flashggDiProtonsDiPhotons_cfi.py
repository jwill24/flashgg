import FWCore.ParameterSet.Config as cms

flashggDiProtonsDiPhotons = cms.EDProducer('FlashggDiProtonDiPhotonProducer',
                                           DiProtonTag = cms.InputTag('flashggDiProtons'),
                                           DiPhotonTag = cms.InputTag('flashggDiPhotons'),
                                          )
