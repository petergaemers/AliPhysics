#ifndef ALIRDHFCUTS_H
#define ALIRDHFCUTS_H
/* Copyright(c) 1998-2010, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

//***********************************************************
/// \class Class AliRDHFCuts
/// \brief base class for cuts on AOD reconstructed heavy-flavour decays
/// \author Author: A.Dainese, andrea.dainese@pd.infn.it
//***********************************************************

#include <TString.h>

#include "AliAnalysisCuts.h"
#include "AliESDtrackCuts.h"
#include "AliAODPidHF.h"
#include "AliAODEvent.h"
#include "AliVEvent.h"

class AliAODTrack;
class AliAODRecoDecayHF;
class AliESDVertex;
class TF1;
class TFormula;

class AliRDHFCuts : public AliAnalysisCuts 
{
 public:

  enum ECentrality {kCentOff,kCentV0M,kCentTRK,kCentTKL,kCentCL1,kCentZNA,kCentZPA,kCentV0A,kCentInvalid};
  enum ESelLevel {kAll,kTracks,kPID,kCandidate};
  enum EPileup {kNoPileupSelection,kRejectPileupEvent,kRejectTracksFromPileupVertex,kRejectMVPileupEvent};
  enum ESele {kD0toKpiCuts,kD0toKpiPID,kD0fromDstarCuts,kD0fromDstarPID,kDplusCuts,kDplusPID,kDsCuts,kDsPID,kLcCuts,kLcPID,kDstarCuts,kDstarPID};
  enum ERejBits {kNotSelTrigger,kNoVertex,kTooFewVtxContrib,kZVtxOutFid,kPileup,kOutsideCentrality,kPhysicsSelection,kBadSPDVertex,kZVtxSPDOutFid,kCentralityFlattening,kBadTrackV0Correl};
  enum EV0sel  {kAllV0s = 0, kOnlyOfflineV0s = 1, kOnlyOnTheFlyV0s = 2};

  AliRDHFCuts(const Char_t* name="RDHFCuts", const Char_t* title="");
  
  virtual ~AliRDHFCuts();
  
  AliRDHFCuts(const AliRDHFCuts& source);
  AliRDHFCuts& operator=(const AliRDHFCuts& source);

  virtual void SetStandardCutsPP2010() {return;}
  virtual void SetStandardCutsPbPb2010() {return;}
  virtual void SetStandardCutsPbPb2011() {return;}


  void SetMinCentrality(Float_t minCentrality=0.) {fMinCentrality=minCentrality;}
  void SetMaxCentrality(Float_t maxCentrality=100.) {fMaxCentrality=maxCentrality;} 
  void SetMinVtxType(Int_t type=3) {fMinVtxType=type;}  
  void SetUseEventsWithOnlySPDVertex(Bool_t flag=kTRUE){ 
    if(flag) fMinVtxType=1;
    else fMinVtxType=3;
  }
  void SetMinVtxContr(Int_t contr=1) {fMinVtxContr=contr;}  
  void SetMaxVtxRdChi2(Float_t chi2=1e6) {fMaxVtxRedChi2=chi2;}  
  void SetMaxVtxZ(Float_t z=1e6) {fMaxVtxZ=z;}  
  void SetMinSPDMultiplicity(Int_t mult=0) {fMinSPDMultiplicity=mult;}  

  void SetTriggerMask(ULong64_t mask=0) {fTriggerMask=mask;}
  void SetUseOnlyOneTrigger(Bool_t onlyOne) {fUseOnlyOneTrigger=onlyOne;}
  ULong64_t GetTriggerMask() {return fTriggerMask;}
  Bool_t GetUseOnlyOneTrigger() {return fUseOnlyOneTrigger;}

  void SetUseAnyTrigger() {fTriggerMask=AliVEvent::kAny;}
  void EnableMBTrigger(){
    fTriggerMask|=AliVEvent::kMB;
    fUseOnlyOneTrigger=kFALSE;
  }
  void ResetMaskAndEnableMBTrigger(){
    fTriggerMask=AliVEvent::kMB;
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseMBTriggerExclusively(){
    fTriggerMask=AliVEvent::kMB;
    fUseOnlyOneTrigger=kTRUE;
  }
  void EnableCentralTrigger(){
    fTriggerMask|=AliVEvent::kCentral;
    fUseOnlyOneTrigger=kFALSE;
  }
  void ResetMaskAndEnableCentralTrigger(){
    fTriggerMask=AliVEvent::kCentral;
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseCentralTriggerExclusively(){
    fTriggerMask=AliVEvent::kCentral;
    fUseOnlyOneTrigger=kTRUE;
  }
  void EnableSemiCentralTrigger(){
    fTriggerMask|=AliVEvent::kSemiCentral;
    fUseOnlyOneTrigger=kFALSE;
  }
  void ResetMaskAndEnableSemiCentralTrigger(){
    fTriggerMask=AliVEvent::kSemiCentral;
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseSemiCentralTriggerExclusively(){
    fTriggerMask=AliVEvent::kSemiCentral;
    fUseOnlyOneTrigger=kTRUE;
  }
  void EnableEMCALTrigger(){
    fTriggerMask|=(AliVEvent::kEMCEJE|AliVEvent::kEMCEGA);
    fUseOnlyOneTrigger=kFALSE;
  }
  void ResetMaskAndEnableEMCALTrigger(){
    fTriggerMask=(AliVEvent::kEMCEJE|AliVEvent::kEMCEGA);
    fUseOnlyOneTrigger=kFALSE;
  } 
  void SetUseEMCALTriggerExclusively(){
    fTriggerMask=(AliVEvent::kEMCEJE|AliVEvent::kEMCEGA);
    fUseOnlyOneTrigger=kTRUE;
  }
  //
  ///  Setters (helpers) for pp 2012 data
  void SetUseInt1TriggerPP2012(){
    fTriggerMask=AliVEvent::kMB;
    fTriggerClass[0]="CINT1";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseInt7TriggerPP2012(){
    fTriggerMask=AliVEvent::kINT7;
    fTriggerClass[0]="CINT7";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseInt8TriggerPP2012(){
    fTriggerMask=AliVEvent::kINT8;
    fTriggerClass[0]="CINT8";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseEMCAL7TriggerPP2012(){
    fTriggerMask=AliVEvent::kEMC7;
    fTriggerClass[0]="CEMC7";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseEMCAL8TriggerPP2012(){
    fTriggerMask=AliVEvent::kEMC8;
    fTriggerClass[0]="CEMC8";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseEMCALJET7TriggerPP2012(){
    fTriggerMask=AliVEvent::kEMCEJE;
    fTriggerClass[0]="CEMC7EJE";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseEMCALJET8TriggerPP2012(){
    fTriggerMask=AliVEvent::kEMCEJE;
    fTriggerClass[0]="CEMC8EJE";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseEMCALGA7TriggerPP2012(){
    fTriggerMask=AliVEvent::kEMCEGA;
    fTriggerClass[0]="CEMC7EGA";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseEMCALGA8TriggerPP2012(){
    fTriggerMask=AliVEvent::kEMCEGA;
    fTriggerClass[0]="CEMC8EGA";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseSPI7TriggerPP2012(){
    fTriggerMask=AliVEvent::kSPI7;
    fTriggerClass[0]="CSPI7";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseSPI8TriggerPP2012(){
    fTriggerMask=AliVEvent::kSPI;
    fTriggerClass[0]="CSPI8";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseHighMult7TriggerPP2012(){
    fTriggerMask=AliVEvent::kHighMult;
    fTriggerClass[0]="CSHM7";
    fUseOnlyOneTrigger=kFALSE;
  }
  void SetUseHighMult8TriggerPP2012(){
    fTriggerMask=AliVEvent::kHighMult;
    fTriggerClass[0]="CSHM8";
    fUseOnlyOneTrigger=kFALSE;
  }

  void SetMaxDifferenceTRKV0Centraltity(Double_t maxd=5.) {fMaxDiffTRKV0Centr=maxd;}
  void SetNotUseCutOnTRKVsV0Centraltity() {fMaxDiffTRKV0Centr=-1.;}
  void SetRemoveTrackletOutliers(Bool_t opt) {fRemoveTrackletOutliers=opt;}
  void SetCutOnzVertexSPD(Int_t opt) {
    if(opt>=0 && opt<=2) fCutOnzVertexSPD=opt;
    else AliError("Wrong option for cut on zVertexSPD");
  }
  void SetTriggerClass(TString trclass0, TString trclass1="") {fTriggerClass[0]=trclass0; fTriggerClass[1]=trclass1;} 
  void ApplySPDDeadPbPb2011(){fApplySPDDeadPbPb2011=kTRUE;}
  void ApplySPDMisalignedCutPP2012(){fApplySPDMisalignedPP2012=kTRUE;}
  void SetVarsForOpt(Int_t nVars,Bool_t *forOpt);
  void SetGlobalIndex(){fGlobalIndex=fnVars*fnPtBins;}
  void SetGlobalIndex(Int_t nVars,Int_t nptBins){fnVars=nVars; fnPtBins=nptBins; SetGlobalIndex();}
  void SetVarNames(Int_t nVars,TString *varNames,Bool_t *isUpperCut);  
  void SetPtBins(Int_t nPtBinLimits,Float_t *ptBinLimits);
  void SetCuts(Int_t nVars,Int_t nPtBins,Float_t** cutsRD);
  void SetCuts(Int_t glIndex, Float_t* cutsRDGlob);
  void AddTrackCuts(const AliESDtrackCuts *cuts) 
          {delete fTrackCuts; fTrackCuts=new AliESDtrackCuts(*cuts); return;}
  void SetUsePID(Bool_t flag=kTRUE) {fUsePID=flag; return;}
  void SetUseAOD049(Bool_t flag=kTRUE) {fUseAOD049=flag; return;}
  void SetKinkRejection(Bool_t flag=kTRUE) {fKinkReject=flag; return;}
  void SetUseTrackSelectionWithFilterBits(Bool_t flag=kTRUE){ 
    fUseTrackSelectionWithFilterBits=flag; return;}
  void SetUseCentrality(Int_t flag=1);    /// see enum below
  void SetPidHF(AliAODPidHF* pidObj) {
    if(fPidHF) delete fPidHF;
    fPidHF=new AliAODPidHF(*pidObj);
  }
  void SetRemoveDaughtersFromPrim(Bool_t removeDaughtersPrim) {fRemoveDaughtersFromPrimary=removeDaughtersPrim;}
  void SetMinPtCandidate(Double_t ptCand=-1.) {fMinPtCand=ptCand; return;}
  void SetMaxPtCandidate(Double_t ptCand=1000.) {fMaxPtCand=ptCand; return;}
  void SetMaxRapidityCandidate(Double_t ycand) {fMaxRapidityCand=ycand; return;}
  void SetOptPileup(Int_t opt=0){
    /// see enum below
    fOptPileup=opt;
  }
  void SetHistoForCentralityFlattening(TH1F *h,Double_t minCentr,Double_t maxCentr,Double_t centrRef=0.,Int_t switchTRand=0);
  void ConfigurePileupCuts(Int_t minContrib=3, Float_t minDz=0.6){
    fMinContrPileup=minContrib;
    fMinDzPileup=minDz;
  }
  void SetMinCrossedRowsTPCPtDep(const char *rows="");
  void SetMinRatioClsOverCrossRowsTPC(Float_t ratio=0.) {fCutRatioClsOverCrossRowsTPC = ratio;}
  void SetMinRatioSignalNOverCrossRowsTPC(Float_t ratio=0.) {fCutRatioSignalNOverCrossRowsTPC = ratio;}

  AliAODPidHF* GetPidHF() const {return fPidHF;}
  Float_t *GetPtBinLimits() const {return fPtBinLimits;}
  Int_t   GetNPtBins() const {return fnPtBins;}
  Int_t   GetNVars() const {return fnVars;} 
  TString *GetVarNames() const {return fVarNames;} 
  Bool_t  *GetVarsForOpt() const {return fVarsForOpt;} 
  Int_t   GetNVarsForOpt() const {return fnVarsForOpt;}
  const Float_t *GetCuts() const {return fCutsRD;} 
  void    GetCuts(Float_t**& cutsRD) const;
  Float_t GetCutValue(Int_t iVar,Int_t iPtBin) const;
  Double_t GetMaxVtxZ() const {return fMaxVtxZ;}  
  Float_t GetCentrality(AliAODEvent* aodEvent){return GetCentrality(aodEvent,(AliRDHFCuts::ECentrality)fUseCentrality);}
  Float_t GetCentrality(AliAODEvent* aodEvent, AliRDHFCuts::ECentrality estimator);
  Float_t GetCentralityOldFramework(AliAODEvent* aodEvent, AliRDHFCuts::ECentrality estimator);
  Bool_t  *GetIsUpperCut() const {return fIsUpperCut;}
  AliESDtrackCuts *GetTrackCuts() const {return fTrackCuts;}
  virtual AliESDtrackCuts *GetTrackCutsSoftPi() const {return 0;}
  virtual AliESDtrackCuts *GetTrackCutsV0daughters() const {return 0;}
  virtual void GetCutVarsForOpt(AliAODRecoDecayHF *d,Float_t *vars,Int_t nvars,Int_t *pdgdaughters) = 0;
  virtual void GetCutVarsForOpt(AliAODRecoDecayHF *d,Float_t *vars,Int_t nvars,Int_t *pdgdaughters,AliAODEvent * /*aod*/)
            {return GetCutVarsForOpt(d,vars,nvars,pdgdaughters);}
  Int_t   GetGlobalIndex(Int_t iVar,Int_t iPtBin) const;
  void    GetVarPtIndex(Int_t iGlob, Int_t& iVar, Int_t& iPtBin) const;
  Bool_t  GetIsUsePID() const {return fUsePID;}
  Bool_t  GetUseAOD049() const {return fUseAOD049;}
  Bool_t  GetUseKinkRejection() const {return fKinkReject;}
  Bool_t  GetUseEventsWithOnlySPDVertex() const{
    if(fMinVtxType==1 || fMinVtxType==2) return kTRUE;
    return kFALSE;
  }
  Bool_t  GetUseTrackSelectionWithFilterBits() const{return fUseTrackSelectionWithFilterBits;}
  Bool_t  GetIsPrimaryWithoutDaughters() const {return fRemoveDaughtersFromPrimary;}
  Bool_t GetOptPileUp() const {return fOptPileup;}
  Int_t GetUseCentrality() const {return fUseCentrality;}
  Float_t GetMinCentrality() const {return fMinCentrality;}
  Float_t GetMaxCentrality() const {return fMaxCentrality;}
  Double_t GetMinPtCandidate() const {return fMinPtCand;}
  Double_t GetMaxPtCandidate() const {return fMaxPtCand;}
  TH1F *GetHistoForCentralityFlattening(){return fHistCentrDistr;}
  void SetUseCentralityFlatteningInMC(Bool_t opt){fUseCentrFlatteningInMC=opt;}
  const char* GetMinCrossedRowsTPCPtDep() const {return fCutMinCrossedRowsTPCPtDep;}
  Float_t GetMinRatioClsOverCrossRowsTPC() const {return fCutRatioClsOverCrossRowsTPC;}
  Float_t GetMinRatioSignalNOverCrossRowsTPC() const {return fCutRatioSignalNOverCrossRowsTPC;}
  Bool_t IsSelected(TObject *obj) {return IsSelected(obj,AliRDHFCuts::kAll);}
  Bool_t IsSelected(TList *list) {if(!list) return kTRUE; return kFALSE;}
  Int_t  IsEventSelectedInCentrality(AliVEvent *event);
  Bool_t IsEventSelectedForCentrFlattening(Float_t centvalue);
  Bool_t IsEventSelected(AliVEvent *event);
  Bool_t AreDaughtersSelected(AliAODRecoDecayHF *rd) const;
  Bool_t IsDaughterSelected(AliAODTrack *track,const AliESDVertex *primary,AliESDtrackCuts *cuts) const;
  virtual Int_t IsSelectedPID(AliAODRecoDecayHF * /*rd*/) {return 1;}
  void SetupPID(AliVEvent *event);

  virtual Int_t IsSelected(TObject* obj,Int_t selectionLevel) = 0;
  virtual Int_t IsSelected(TObject* obj,Int_t selectionLevel,AliAODEvent* /*aod*/)
                {return IsSelected(obj,selectionLevel);}
  Int_t PtBin(Double_t pt) const;
  virtual void PrintAll()const;
  void PrintTrigger() const;

  virtual Bool_t IsInFiducialAcceptance(Double_t /*pt*/,Double_t /*y*/) const {return kTRUE;}

  void SetWhyRejection(Int_t why) {fWhyRejection=why; return;}
  Int_t GetWhyRejection() const {return fWhyRejection;}
  UInt_t GetEventRejectionBitMap() const {return fEvRejectionBits;}
  Bool_t IsEventRejectedDueToTrigger() const {
    return fEvRejectionBits&(1<<kNotSelTrigger);
  }
  Bool_t IsEventRejectedDueToNotRecoVertex() const {
    return fEvRejectionBits&(1<<kNoVertex);
  }
  Bool_t IsEventRejectedDueToVertexContributors() const {
    return fEvRejectionBits&(1<<kTooFewVtxContrib);
  }
  Bool_t IsEventRejectedDueToZVertexOutsideFiducialRegion() const {
    return fEvRejectionBits&(1<<kZVtxOutFid);
  }
  Bool_t IsEventRejectedDueToPileup() const {
    return fEvRejectionBits&(1<<kPileup);
  }
  Bool_t IsEventRejectedDueToCentrality() const {
    return fEvRejectionBits&(1<<kOutsideCentrality);
  }
  Bool_t IsEventRejectedDueToCentralityFlattening() const {
    return fEvRejectionBits&(1<<kCentralityFlattening);
  }
  Bool_t IsEventRejectedDueToTRKV0CentralityCorrel() const {
    return fEvRejectionBits&(1<<kBadTrackV0Correl);
  }
  Bool_t IsEventRejectedDuePhysicsSelection() const {
    return fEvRejectionBits&(1<<kPhysicsSelection);
  }


  void SetFixRefs(Bool_t fix=kTRUE) {fFixRefs=fix; return;}
  void SetUsePhysicsSelection(Bool_t use=kTRUE){fUsePhysicsSelection=use; return;}
  Bool_t GetUsePhysicsSelection() const { return fUsePhysicsSelection; }



  Bool_t CompareCuts(const AliRDHFCuts *obj) const;
  void MakeTable()const;

  Int_t GetIsSelectedCuts() const {return fIsSelectedCuts;}
  Int_t GetIsSelectedPID() const  {return fIsSelectedPID;}

  void SetUseMCVertex() { fUseMCVertex=kTRUE; }
  Bool_t GetUseMCVertex() const { return fUseMCVertex; }

  Bool_t RecalcOwnPrimaryVtx(AliAODRecoDecayHF *d,AliAODEvent *aod) const;
  Bool_t SetMCPrimaryVtx(AliAODRecoDecayHF *d,AliAODEvent *aod) const;
  void   CleanOwnPrimaryVtx(AliAODRecoDecayHF *d,AliAODEvent *aod,AliAODVertex *origownvtx) const;

  Bool_t CountEventForNormalization() const 
  { if(fWhyRejection==0) {return kTRUE;} else {return kFALSE;} }

  void SetKeepSignalMC() {fKeepSignalMC=kTRUE; return;}

  /// Flag and pt-maximum to check if the candidate daughters fulfill the kFirst criteria
  void SetSelectCandTrackSPDFirst( Bool_t flag, Double_t ptmax )
  { fIsCandTrackSPDFirst=flag; fMaxPtCandTrackSPDFirst=ptmax; }
  Bool_t IsSelectCandTrackSPDFirst() const { return fIsCandTrackSPDFirst; }
  Double_t IsMaxCandTrackSPDFirst() const { return fMaxPtCandTrackSPDFirst; }

  Bool_t CheckPtDepCrossedRows(TString rows,Bool_t print=kFALSE) const;



 protected:

  void SetNPtBins(Int_t nptBins){fnPtBins=nptBins;}
  void SetNVars(Int_t nVars){fnVars=nVars;}

  Bool_t IsSignalMC(AliAODRecoDecay *d,AliAODEvent *aod,Int_t pdg) const;
  Bool_t RecomputePrimaryVertex(AliAODEvent* event) const;

  /// cuts on the event
  Int_t fMinVtxType; /// 0: not cut; 1: SPDZ; 2: SPD3D; 3: Tracks
  Int_t fMinVtxContr;   /// minimum vertex contributors
  Float_t fMaxVtxRedChi2; /// maximum chi2/ndf
  Float_t fMaxVtxZ; /// maximum |z| of primary vertex
  Int_t fMinSPDMultiplicity; /// SPD multiplicity
  ULong64_t fTriggerMask; /// trigger mask
  Bool_t fUseOnlyOneTrigger; /// flag to select one trigger only
  TString  fTriggerClass[2]; /// trigger class
  /// quality cuts on the daughter tracks
  AliESDtrackCuts *fTrackCuts; /// tracks for daughter tracks (AOD converted to ESD on the flight!)
  /// cuts on the candidate
  Int_t fnPtBins;  /// number of pt bins for cuts
  Int_t fnPtBinLimits; /// "number of limits", that is fnPtBins+1
  Float_t* fPtBinLimits; //[fnPtBinLimits]  pt bins
  Int_t fnVars;    /// number of cut vars for candidates
  TString *fVarNames; //[fnVars] names of the variables
  Int_t fnVarsForOpt;    /// number of cut vars to be optimized for candidates
  Bool_t *fVarsForOpt; //[fnVars] kTRUE for vars to be used in optimization
  Int_t fGlobalIndex; /// fnVars*fnPtBins
  Float_t *fCutsRD; //[fGlobalIndex] the cuts values
  Bool_t  *fIsUpperCut; //[fnVars] use > or < to select
  Bool_t fUsePID; /// enable PID usage (off by default)
  Bool_t fUseAOD049; /// enable AOD049 centrality cleanup
  AliAODPidHF *fPidHF; /// PID for heavy flavours manager
  Int_t fWhyRejection; /// used to code the step at which candidate was rejected
  UInt_t fEvRejectionBits; //bit map storing the full info about event rejection
  Bool_t fRemoveDaughtersFromPrimary; /// flag to switch on the removal of duaghters from the primary vertex computation
  Bool_t fUseMCVertex; /// use MC primary vertex 
  Bool_t fUsePhysicsSelection; /// use Physics selection criteria
  Int_t  fOptPileup;      /// option for pielup selection
  Int_t  fMinContrPileup; /// min. n. of tracklets in pileup vertex
  Float_t fMinDzPileup;   /// min deltaz between main and pileup vertices
  Int_t   fUseCentrality; /// off =0 (default)
                          /// 1 = V0 
                          /// 2 = Tracks
                          /// 3 = Tracklets
                          /// 4 = SPD clusters outer 
  Float_t fMinCentrality; /// minimum centrality for selected events
  Float_t fMaxCentrality; /// maximum centrality for selected events
  Bool_t  fFixRefs;       /// fix the daughter track references 
  Int_t  fIsSelectedCuts; /// outcome of cuts selection
  Int_t  fIsSelectedPID;  /// outcome of PID selection
  Double_t fMinPtCand; /// minimum pt of the candidate
  Double_t fMaxPtCand; /// minimum pt of the candidate
  Double_t fMaxRapidityCand; /// max rapidity of candidate (if !=-999 overrides IsInFiducialAcceptance)
  Bool_t  fKeepSignalMC; /// IsSelected returns always kTRUE for MC signal
  Bool_t fIsCandTrackSPDFirst; /// flag to select the track kFirst criteria for pt < ptlimit
  Double_t fMaxPtCandTrackSPDFirst; /// maximum pt of the candidate for which to check if the daughters fulfill kFirst criteria
  Bool_t fApplySPDDeadPbPb2011;  /// flag to apply SPD dead module map of PbPb2011
  Bool_t fApplySPDMisalignedPP2012; /// flag to apply cut on tracks crossing SPD misaligned modules for PP2012 data
  Double_t fMaxDiffTRKV0Centr;   /// Max. difference between TRK and V0 centrality (remove TPC pileup for PbPb 2011)
  Bool_t fRemoveTrackletOutliers; /// flag to apply cut on tracklets vs. centrality for 2011 data
  Int_t fCutOnzVertexSPD; /// cut on zSPD vertex to remove outliers in centrality vs. tracklets (0=no cut, 1= cut at 12 cm, 2= cut on difference to z of vtx tracks
  Bool_t fKinkReject; /// flag to reject kink daughters
  Bool_t fUseTrackSelectionWithFilterBits; /// flag to enable/disable the check on filter bits
  Bool_t fUseCentrFlatteningInMC; /// flag for enabling/diabling centrality flattening in MC
  TH1F *fHistCentrDistr;   /// histogram with reference centrality distribution for centrality distribution flattening
  Float_t fCutRatioClsOverCrossRowsTPC; /// min. value ratio NTPCClusters/NTPCCrossedRows, cut if !=0
  Float_t fCutRatioSignalNOverCrossRowsTPC;   /// min. value ratio TPCPointsUsedForPID/NTPCCrossedRows, cut if !=0 
  TString fCutMinCrossedRowsTPCPtDep; /// pT-dep cut in TPC minimum n crossed rows
  TFormula *f1CutMinNCrossedRowsTPCPtDep; /// pT-dep cut in TPC minimum n crossed rows
 

  /// \cond CLASSIMP    
  ClassDef(AliRDHFCuts,36);  /// base class for cuts on AOD reconstructed heavy-flavour decays
  /// \endcond
};

#endif
