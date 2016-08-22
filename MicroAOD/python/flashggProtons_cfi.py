import FWCore.ParameterSet.Config as cms

flashggProtons = cms.EDProducer('FlashggProtonProducer',
    protonTag = cms.InputTag('protons'),
)
