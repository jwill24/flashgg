# flashgg (with CT-PPS add-on)

Instructions for using the "tweaked MiniAOD" (MiniAOD + CT-PPS RP information):
- start by creating your CMSSW working environment:
```
 cmsrel CMSSW_8_0_19
 cd CMSSW_8_0_19/src && cmsenv
 git cms-init
 cd $CMSSW_BASE/src
```
- then, import the forward protons reconstruction to build reco::Proton objects out of forward RP local tracks information:
```
 git cms-merge-topic forthommel:forward-proton-reco_80X
```
- clone my fork of flashgg and checkout the branch containing all diproton* leaves:
```
 git clone https://github.com/forthommel/flashgg flashgg && cd flashgg
 git checkout forwardprotons-81x
```
- finally, check the flashgg dependencies and start building (time-consuming operation!)
```
 cd $CMSSW_BASE/src
 source flashgg/setup.sh # might take some time
 scram b -j 10           # _will_ take some time!
```
