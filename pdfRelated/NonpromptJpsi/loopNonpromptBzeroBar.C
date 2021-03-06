
#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TMath.h>
#include <iostream>
#include <TNtuple.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <cmath>
#include "loopNonpromptBzero.h"

#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916

void fillTree(TVector3* bP, TVector3* bVtx, TLorentzVector* b4P, int j, int typesize, float track_mass1, float track_mass2, int REAL)
{

  //Event Info
  Event = EvtInfo_EvtNo;
  Run = EvtInfo_RunNo;
  size = typesize+1;
  besttktkmass = 0;
  bestchi2 = 0;

  // Trigger Info
  HLT_PAL1DoubleMu0_v1 = Bfr_HLT_PAL1DoubleMu0_v1;
  HLT_PAL1DoubleMu0_v1_Prescl = Bfr_HLT_PAL1DoubleMu0_v1_Prescl;
  HLT_PADimuon0_NoVertexing_v1 = Bfr_HLT_PADimuon0_NoVertexing_v1;
  HLT_PADimuon0_NoVertexing_v1_Prescl = Bfr_HLT_PADimuon0_NoVertexing_v1_Prescl;
  HLT_PAL1DoubleMu0_HighQ_v1 = Bfr_HLT_PAL1DoubleMu0_HighQ_v1;
  HLT_PAL1DoubleMu0_HighQ_v1_Prescl = Bfr_HLT_PAL1DoubleMu0_HighQ_v1_Prescl;
  HLT_PAL1DoubleMuOpen_v1 = Bfr_HLT_PAL1DoubleMuOpen_v1;
  HLT_PAL1DoubleMuOpen_v1_Prescl = Bfr_HLT_PAL1DoubleMuOpen_v1_Prescl;
  HLT_PAL2DoubleMu3_v1 = Bfr_HLT_PAL2DoubleMu3_v1;
  HLT_PAL2DoubleMu3_v1_Prescl = Bfr_HLT_PAL2DoubleMu3_v1_Prescl;
  HLT_PAMu3_v1 = Bfr_HLT_PAMu3_v1;
  HLT_PAMu3_v1_Prescl = Bfr_HLT_PAMu3_v1_Prescl;
  HLT_PAMu7_v1 = Bfr_HLT_PAMu7_v1;
  HLT_PAMu7_v1_Prescl = Bfr_HLT_PAMu7_v1_Prescl;
  HLT_PAMu12_v1 = Bfr_HLT_PAMu12_v1;
  HLT_PAMu12_v1_Prescl = Bfr_HLT_PAMu12_v1_Prescl;

  //B Info
  bP->SetXYZ(BInfo_px[j],BInfo_py[j],BInfo_pz[j]*0);
  bVtx->SetXYZ(BInfo_vtxX[j]-EvtInfo_PVx,
	       BInfo_vtxY[j]-EvtInfo_PVy,
	       BInfo_vtxZ[j]*0-EvtInfo_PVz*0);
  b4P->SetXYZM(BInfo_px[j],BInfo_py[j],BInfo_pz[j],BInfo_mass[j]);

  bindex[typesize] = typesize;
  y[typesize] = b4P->Rapidity();
  dtheta[typesize] = bP->Angle(*bVtx);
  pt[typesize] = BInfo_pt[j];
  eta[typesize] = BInfo_eta[j];
  phi[typesize] = BInfo_phi[j];
  chi2cl[typesize] = TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j]);
  d0[typesize] = sqrt((BInfo_vtxX[j]-EvtInfo_PVx)*(BInfo_vtxX[j]-EvtInfo_PVx)+(BInfo_vtxY[j]-EvtInfo_PVy)*(BInfo_vtxY[j]-EvtInfo_PVy));
  vx[typesize] = BInfo_vtxX[j] - EvtInfo_PVx;
  vy[typesize] = BInfo_vtxY[j] - EvtInfo_PVy;
  d0Err[typesize] = sqrt(BInfo_vtxXE[j]*BInfo_vtxXE[j]+BInfo_vtxYE[j]*BInfo_vtxYE[j]);
  mass[typesize] = BInfo_mass[j];
  tktkmass[typesize] = BInfo_tktk_mass[j];
  chi2ndf[typesize] = BInfo_vtxchi2[j]/BInfo_vtxdof[j];
  lxy[typesize] = ((BInfo_vtxX[j]-EvtInfo_PVx)*BInfo_px[j] + (BInfo_vtxY[j]-EvtInfo_PVy)*BInfo_py[j])/BInfo_pt[j];
  isbestchi2[typesize] = 0;
  isbesttktkmass[typesize] = 0;
  kstar[typesize] = 0;
  if(BInfo_type[j]==4) kstar[typesize]=1;
  else if(BInfo_type[j]==5) kstar[typesize]=2;

  //muon section
  mu1Striplayer[typesize] = MuonInfo_i_nStripLayer[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1Pixellayer[typesize] = MuonInfo_i_nPixelLayer[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1Chi2ndf[typesize] = MuonInfo_i_chi2[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]/MuonInfo_i_ndf[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1dxy[typesize] = MuonInfo_dxyPV[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1dz[typesize] = MuonInfo_dzPV[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  if(MuonInfo_muqual[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]&16) mu1TrackerMuArbitrated[typesize] = 1;
  else mu1TrackerMuArbitrated[typesize] = 0;
  if(MuonInfo_muqual[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]&4096) mu1StationTight[typesize] = 1;
  else mu1StationTight[typesize] = 0;

  mu2Striplayer[typesize] = MuonInfo_i_nStripLayer[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2Pixellayer[typesize] = MuonInfo_i_nPixelLayer[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2Chi2ndf[typesize] = MuonInfo_i_chi2[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]/MuonInfo_i_ndf[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2dxy[typesize] = MuonInfo_dxyPV[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2dz[typesize] = MuonInfo_dzPV[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  if(MuonInfo_muqual[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]&16) mu2TrackerMuArbitrated[typesize] = 1;
  else mu2TrackerMuArbitrated[typesize] = 0;
  if(MuonInfo_muqual[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]&4096) mu2StationTight[typesize] = 1;
  else mu2StationTight[typesize] = 0;
  
  float mu1px,mu1py,mu1pz,mu1E;
  float mu2px,mu2py,mu2pz,mu2E;

  mu1px = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*cos(MuonInfo_phi[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
  mu1py = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*sin(MuonInfo_phi[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
  mu1pz = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*sinh(MuonInfo_eta[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
  b4P->SetXYZM(mu1px,mu1py,mu1pz,MUON_MASS);
  mu1E = b4P->E();
  mu1eta[typesize] = b4P->Eta();
  mu1phi[typesize] = b4P->Phi();
  mu1y[typesize] = b4P->Rapidity();
  mu1pt[typesize] = b4P->Pt();
  mu1p[typesize] = b4P->P();

  mu2px = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*cos(MuonInfo_phi[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
  mu2py = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*sin(MuonInfo_phi[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
  mu2pz = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*sinh(MuonInfo_eta[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
  b4P->SetXYZM(mu2px,mu2py,mu2pz,MUON_MASS);
  mu2E = b4P->E();
  mu2eta[typesize] = b4P->Eta();
  mu2phi[typesize] = b4P->Phi();
  mu2y[typesize] = b4P->Rapidity();
  mu2pt[typesize] = b4P->Pt();
  mu2p[typesize] = b4P->P();

  b4P->SetPxPyPzE(mu1px+mu2px,
		  mu1py+mu2py,
		  mu1pz+mu2pz,
		  mu1E+mu2E);
  mumumass[typesize] = b4P->Mag();
  mumueta[typesize] = b4P->Eta();
  mumuphi[typesize] = b4P->Phi();
  mumuy[typesize] = b4P->Rapidity();
  mumupt[typesize] = b4P->Pt();


  //jpsi section
  ujmass[typesize] = BInfo_uj_mass[BInfo_rfuj_index[j]];
  ujvProb[typesize] = TMath::Prob(BInfo_uj_vtxchi2[BInfo_rfuj_index[j]],BInfo_uj_vtxdof[BInfo_rfuj_index[j]]);
  b4P->SetXYZM(BInfo_uj_px[BInfo_rfuj_index[j]],
	       BInfo_uj_py[BInfo_rfuj_index[j]],
	       BInfo_uj_pz[BInfo_rfuj_index[j]],
	       BInfo_uj_mass[BInfo_rfuj_index[j]]);
  ujpt[typesize] = b4P->Pt();
  ujeta[typesize] = b4P->PseudoRapidity();
  ujphi[typesize] = b4P->Phi();
  ujy[typesize] = b4P->Rapidity();
  ujlxy[typesize] = ((BInfo_uj_vtxX[BInfo_rfuj_index[j]]-EvtInfo_PVx)*BInfo_uj_px[BInfo_rfuj_index[j]] + (BInfo_uj_vtxY[BInfo_rfuj_index[j]]-EvtInfo_PVy)*BInfo_uj_py[BInfo_rfuj_index[j]])/ujpt[typesize];

  //track section
  float tk1px,tk1py,tk1pz,tk1E;
  float tk2px,tk2py,tk2pz,tk2E;


   if(BInfo_type[j]==5)
    {
      b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk2_index[j]],TrackInfo_eta[BInfo_rftk2_index[j]],TrackInfo_phi[BInfo_rftk2_index[j]],track_mass1);
      trk1Dxy[typesize] = TrackInfo_dxyPV[BInfo_rftk2_index[j]];
      trk1D0Err[typesize] = TrackInfo_d0error[BInfo_rftk2_index[j]];
      trk1PixelHit[typesize] = TrackInfo_pixelhit[BInfo_rftk2_index[j]];
      trk1StripHit[typesize] = TrackInfo_striphit[BInfo_rftk2_index[j]];
      trk1Pt[typesize] = TrackInfo_pt[BInfo_rftk2_index[j]];
      trk1Chi2ndf[typesize] = TrackInfo_chi2[BInfo_rftk2_index[j]]/TrackInfo_ndf[BInfo_rftk2_index[j]];
      trk1Eta[typesize] = TrackInfo_eta[BInfo_rftk2_index[j]];
      trk1Phi[typesize] = TrackInfo_phi[BInfo_rftk2_index[j]];
      trk1Y[typesize] = b4P->Rapidity();
      tk1px = b4P->Px();
      tk1py = b4P->Py();
      tk1pz = b4P->Pz();
      tk1E = b4P->E();

      b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk1_index[j]],TrackInfo_eta[BInfo_rftk1_index[j]],TrackInfo_phi[BInfo_rftk1_index[j]],track_mass2);
      trk2Dxy[typesize] = TrackInfo_dxyPV[BInfo_rftk1_index[j]];
      trk2D0Err[typesize] = TrackInfo_d0error[BInfo_rftk1_index[j]];
      trk2PixelHit[typesize] = TrackInfo_pixelhit[BInfo_rftk1_index[j]];
      trk2StripHit[typesize] = TrackInfo_striphit[BInfo_rftk1_index[j]];
      trk2Pt[typesize] = TrackInfo_pt[BInfo_rftk1_index[j]];
      trk2Chi2ndf[typesize] = TrackInfo_chi2[BInfo_rftk1_index[j]]/TrackInfo_ndf[BInfo_rftk1_index[j]];
      trk2Eta[typesize] = TrackInfo_eta[BInfo_rftk1_index[j]];
      trk2Phi[typesize] = TrackInfo_phi[BInfo_rftk1_index[j]];
      trk2Y[typesize] = b4P->Rapidity();
      tk2px = b4P->Px();
      tk2py = b4P->Py();
      tk2pz = b4P->Pz();
      tk2E = b4P->E();

      b4P->SetPxPyPzE(tk1px+tk2px,
		      tk1py+tk2py,
		      tk1pz+tk2pz,
		      tk1E+tk2E);
      tktkmass[typesize] = b4P->Mag();
      tktketa[typesize] = b4P->Eta();
      tktkphi[typesize] = b4P->Phi();
      tktky[typesize] = b4P->Rapidity();
      tktkpt[typesize] = b4P->Pt();
      tktkvProb[typesize] = TMath::Prob(BInfo_tktk_vtxchi2[j],BInfo_tktk_vtxdof[j]);
      doubletmass[typesize] = BInfo_tktk_mass[j];
      b4P->SetXYZM(BInfo_tktk_px[j],BInfo_tktk_py[j],BInfo_tktk_pz[j],BInfo_tktk_mass[j]);
      doubletpt[typesize] = b4P->Pt();
      doubleteta[typesize] = b4P->PseudoRapidity();
      doubletphi[typesize] = b4P->Phi();
      doublety[typesize] = b4P->Rapidity();
    }
  else if(BInfo_type[j]==4){
      b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk1_index[j]],TrackInfo_eta[BInfo_rftk1_index[j]],TrackInfo_phi[BInfo_rftk1_index[j]],track_mass1);
      trk1Dxy[typesize] = TrackInfo_dxyPV[BInfo_rftk1_index[j]];
      trk1D0Err[typesize] = TrackInfo_d0error[BInfo_rftk1_index[j]];
      trk1PixelHit[typesize] = TrackInfo_pixelhit[BInfo_rftk1_index[j]];
      trk1StripHit[typesize] = TrackInfo_striphit[BInfo_rftk1_index[j]];
      trk1Pt[typesize] = TrackInfo_pt[BInfo_rftk1_index[j]];
      trk1Chi2ndf[typesize] = TrackInfo_chi2[BInfo_rftk1_index[j]]/TrackInfo_ndf[BInfo_rftk1_index[j]];
      trk1Eta[typesize] = TrackInfo_eta[BInfo_rftk1_index[j]];
      trk1Phi[typesize] = TrackInfo_phi[BInfo_rftk1_index[j]];
      trk1Y[typesize] = b4P->Rapidity();
      tk1px = b4P->Px();
      tk1py = b4P->Py();
      tk1pz = b4P->Pz();
      tk1E = b4P->E();

      b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk2_index[j]],TrackInfo_eta[BInfo_rftk2_index[j]],TrackInfo_phi[BInfo_rftk2_index[j]],track_mass2);
      trk2Dxy[typesize] = TrackInfo_dxyPV[BInfo_rftk2_index[j]];
      trk2D0Err[typesize] = TrackInfo_d0error[BInfo_rftk2_index[j]];
      trk2PixelHit[typesize] = TrackInfo_pixelhit[BInfo_rftk2_index[j]];
      trk2StripHit[typesize] = TrackInfo_striphit[BInfo_rftk2_index[j]];
      trk2Pt[typesize] = TrackInfo_pt[BInfo_rftk2_index[j]];
      trk2Chi2ndf[typesize] = TrackInfo_chi2[BInfo_rftk2_index[j]]/TrackInfo_ndf[BInfo_rftk2_index[j]];
      trk2Eta[typesize] = TrackInfo_eta[BInfo_rftk2_index[j]];
      trk2Phi[typesize] = TrackInfo_phi[BInfo_rftk2_index[j]];
      trk2Y[typesize] = b4P->Rapidity();
      tk2px = b4P->Px();
      tk2py = b4P->Py();
      tk2pz = b4P->Pz();
      tk2E = b4P->E();

      b4P->SetPxPyPzE(tk1px+tk2px,
		      tk1py+tk2py,
		      tk1pz+tk2pz,
		      tk1E+tk2E);
      tktkmass[typesize] = b4P->Mag();
      tktketa[typesize] = b4P->Eta();
      tktkphi[typesize] = b4P->Phi();
      tktky[typesize] = b4P->Rapidity();
      tktkpt[typesize] = b4P->Pt();
      tktkvProb[typesize] = TMath::Prob(BInfo_tktk_vtxchi2[j],BInfo_tktk_vtxdof[j]);
      doubletmass[typesize] = BInfo_tktk_mass[j];
      b4P->SetXYZM(BInfo_tktk_px[j],BInfo_tktk_py[j],BInfo_tktk_pz[j],BInfo_tktk_mass[j]);
      doubletpt[typesize] = b4P->Pt();
      doubleteta[typesize] = b4P->PseudoRapidity();
      doubletphi[typesize] = b4P->Phi();
      doublety[typesize] = b4P->Rapidity();
    }

  //gen info judgement

  if(!REAL)
    {
      gen[typesize] = 0;//gen init
      genIndex[typesize] = -1;//gen init
      genpt[typesize] = -1;
      geneta[typesize] = -20;
      genphi[typesize] = -20;
      geny[typesize] = -1;
      int mGenIdxTk1=-1;
      int mGenIdxTk2=-1;
      int bGenIdxTk1=-1;
      int bGenIdxTk2=-1;
      int bGenIdxMu1=-1;
      int bGenIdxMu2=-1;
      
      
      float BId,MId,tk1Id,tk2Id;
      //tk1:positive, tk2:negtive
      if(BInfo_type[j]==4)
	{
	  BId = 511;//B0
	  MId = 313;//K*0
	  tk1Id = 321;//K+
	  tk2Id = 211;//pi-
	}
      if(BInfo_type[j]==5)
	{
	  BId = 511;//B0
	  MId = 313;//K*0
	  tk1Id = 211;//pi+
	  tk2Id = 321;//K-
	}
      
      int twoTks,kStar,flagkstar=0;
      if(BInfo_type[j]==1 || BInfo_type[j]==2) twoTks=0;
      else twoTks=1;
      if(BInfo_type[j]==4 || BInfo_type[j]==5) kStar=1;
      else kStar=0;

      // tk1
      if(TrackInfo_geninfo_index[BInfo_rftk1_index[j]]>-1)
	{
	  int level =0;
	  if(abs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]])==tk1Id)
	    {
	      level = 1;
	      if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]>-1)
		{
		  if(!twoTks)//one trk channel
		    {
		      mGenIdxTk1=0;
		      if(abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]])==BId)
			{
			  level = 3;
			  bGenIdxTk1=GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]];
			}		  
		    }
		  else//two trk channel
		    {
		      if(abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]])==MId)
			{
			  level = 2;
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]>-1)
			    {
			      if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]])==BId)
				{
				  level = 3;
				  bGenIdxTk1=GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]];
				}
			    }
			  mGenIdxTk1=GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]];
			}
		    }
		}
	    }
	  gen[typesize]=level;
	}
      
      //tk2
      if(!twoTks)//one trk channel
	{
	  gen[typesize]+=30;
	  mGenIdxTk2=0;
	  bGenIdxTk2=0;
	}
      else//two trk channel
	{
	  if(TrackInfo_geninfo_index[BInfo_rftk2_index[j]]>-1)
	    {
	      int level =0;
	      if(abs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]])==tk2Id)
		{
		  level = 1;
		  if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]>-1)
		    {
		      if(abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]])==MId)
			{
			  level = 2;
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]>-1)
			    {
			      if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]])==BId)
				{
				  level = 3;
				  bGenIdxTk2 = GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]];
				}
			    }
			  mGenIdxTk2 = GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]];
			}
		    }
		}
	      gen[typesize]+=(level*10);
	    }
	}

     
      //mu1
      if(MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]>-1)
	{  
	  int level =0;
	  if(abs(GenInfo_pdgId[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]])==13) level=1;
	  if(GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]>-1)
	    {
	      if(GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]]>-1)
		{
		  if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]]])==BId)
		    {
		      level = 2;
		      bGenIdxMu1=GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]];
		      flagkstar++;///////////////////////////////////////////////=1
		    }
		} 
	    }
	  gen[typesize]+=(level*100);
	}
      
      //mu2
      if(MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]>-1)
	{  
	  int level =0;
	  if(abs(GenInfo_pdgId[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]])==13) level = 1;
	  if(GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]>-1)
	    {
	      if(GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]]>-1)
		{
		  if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]]])==BId)
		    {
		      level = 2;
		      bGenIdxMu2=GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]];
		      flagkstar++;///////////////////////////////////////////////////=2
		    }
		}
	    }
	  gen[typesize]+=(level*1000);
	}
      
      int level=0;
      if(mGenIdxTk1!=-1 && mGenIdxTk2!=-1)
	{
	  if(!twoTks) level=1;
	  else
	    {
	      if(mGenIdxTk1==mGenIdxTk2) level=1;
	    }
	}
      if(bGenIdxMu1!=-1 && bGenIdxMu1==bGenIdxMu2 && bGenIdxMu1==bGenIdxTk1)
	{
	  if(!twoTks)
	    {
	      level=2;
	      genIndex[typesize] = bGenIdxMu1;
	    }
	  else if(bGenIdxMu1==bGenIdxTk2)
	    {
	      level=2;
	      genIndex[typesize] = bGenIdxMu1;
	    }
	}
      gen[typesize]+=(level*10000);

      //kstar#############################################################################
      if(kStar)
	{
	  //tk1
	  if(TrackInfo_geninfo_index[BInfo_rftk1_index[j]]>-1)
	    {
	      if(abs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]])==tk2Id)
		{
		  if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]>-1)
		    {
		      if(abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]])==MId)
			{
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]>-1)
			    {
			      if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]])==BId)
				{
				  flagkstar++;//////////////////////////////////////////////=3
				  bGenIdxTk1=GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]];
				}
			    }
			  mGenIdxTk1=GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]];
			}
		    }
		}
	    }
	  
	  //tk2
	  if(TrackInfo_geninfo_index[BInfo_rftk2_index[j]]>-1)
	    {
	      if(abs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]])==tk1Id)
		{
		  if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]>-1)
		    {
		      if(abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]])==MId)
			{
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]>-1)
			    {
			      if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]])==BId)
				{
				  flagkstar++;////////////////////////////////////////////////////=4
				  bGenIdxTk2 = GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]];
				}
			    }
			  mGenIdxTk2 = GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]];
			}
		    }
		}
	    }
	  if(flagkstar==4)
	    {
	      if((bGenIdxMu1!=-1) 
		 && (bGenIdxMu1==bGenIdxMu2)
		 && (bGenIdxMu1==bGenIdxTk1)
		 && (bGenIdxMu1==bGenIdxTk2)
		 )
		{
		  gen[typesize]=41000;
		}
	    }
	}//kstar End#############################################################################

      int tgenIndex=genIndex[typesize];
      if(gen[typesize]==22233)
	{
	  genpt[typesize] = GenInfo_pt[tgenIndex];
	  geneta[typesize] = GenInfo_eta[tgenIndex];
	  genphi[typesize] = GenInfo_phi[tgenIndex];
	  b4P->SetXYZM(GenInfo_pt[tgenIndex]*cos(GenInfo_phi[tgenIndex]),
		       GenInfo_pt[tgenIndex]*sin(GenInfo_phi[tgenIndex]),
		       GenInfo_pt[tgenIndex]*sinh(GenInfo_eta[tgenIndex]),
		       GenInfo_mass[tgenIndex]);
	  geny[typesize] = b4P->Rapidity();
	}
    }
}


void loopNonpromptBzero(string infile="/mnt/hadoop/cms/store/user/jwang/Bfinder_BoostedMC_20140418_Hijing_PPb502_MinimumBias_HIJINGemb_inclBtoPsiMuMu_5TeV.root", string outfile="../../output/myoutputBzero.root", bool REAL=0){
//////////////////////////////////////////////////////////Phi
//   This file has been automatically generated 
//     (Thu Nov 21 13:34:42 2013 by ROOT version5.27/06b)
//   from TTree root/root
//   found on file: merged_pPbData_20131114.root
//////////////////////////////////////////////////////////

  const char* infname;
  const char* outfname;

  if(REAL) cout<<"--- REAL DATA ---"<<endl;
  else cout<<"--- MC ---"<<endl;


  infname = infile.c_str();
  outfname = outfile.c_str();

  //File type
  TFile *f = new TFile(infname);
  TTree *root = (TTree*)f->Get("demo/root");
  TTree *hlt = (TTree*)f->Get("hltanalysis/HltTree");
  if (root->GetEntries()!=hlt->GetEntries()) {
     cout <<"Inconsistent number of entries!!!"<<endl;
     cout <<"HLT tree: "<<hlt->GetEntries()<<endl;
     cout <<"Bfinder tree: "<<root->GetEntries()<<endl;
  }
  
  //Chain type
  //TChain* root = new TChain("demo/root");
  //root->Add("/mnt/hadoop/cms/store/user/wangj/HI_Btuple/20140213_PAMuon_HIRun2013_PromptReco_v1/Bfinder_all_100_1_dXJ.root");
  //root->Add("/mnt/hadoop/cms/store/user/wangj/HI_Btuple/20140213_PAMuon_HIRun2013_PromptReco_v1/Bfinder_all_101_1_kuy.root");
  //root->Add("/mnt/hadoop/cms/store/user/wangj/HI_Btuple/20140213_PAMuon_HIRun2013_PromptReco_v1/Bfinder_all_10_1_ZkX.root");
  //root->Add("/mnt/hadoop/cms/store/user/wangj/HI_Btuple/20140213_PAMuon_HIRun2013_PromptReco_v1/Bfinder_all_102_1_NyI.root");
  
  TFile *outf = new TFile(outfname,"recreate");

  setBranch(root);
  setHltBranch(hlt);
    
  int ifchannel[7];
  ifchannel[3] = 1; //jpsi+K*(K+,pi-)
  ifchannel[4] = 1; //jpsi+K*(K-,pi+)
  
  TTree* nt3 = new TTree("ntKstar","");
  buildBranch(nt3);

  cout<<"--- Tree building finished ---"<<endl;
  
  Long64_t nentries = root->GetEntries();
  nentries = 50000;
  Long64_t nbytes = 0;
  TVector3* bP = new TVector3;
  TVector3* bVtx = new TVector3;
  TLorentzVector* b4P = new TLorentzVector;
  TLorentzVector* b4Pout = new TLorentzVector;
  TLorentzVector bGen;
  int type,flag;
  int flagEvt=0;  
  int offsetHltTree=0;

  int testevent=0,testcand=0;
  
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += root->GetEntry(i);
    flagEvt=0;
    while (flagEvt==0)
    {
       hlt->GetEntry(i+offsetHltTree);
       //cout <<offsetHltTree<<" "<<Bfr_HLT_Event<<" "<<EvtInfo_EvtNo<<endl;
       if (Bfr_HLT_Event==EvtInfo_EvtNo && Bfr_HLT_Run==EvtInfo_RunNo) flagEvt=1; else offsetHltTree++;
    } 

    if (i%10000==0) cout <<i<<" / "<<nentries<<"   offset HLT:"<<offsetHltTree<<endl;

    int type1size=0,type2size=0,type3size=0,type4size=0,type5size=0,type6size=0,type7size=0;
    float best,best2,temy;
    int bestindex,best2index;

    
    size=0;
    best=-1;
    bestindex=-1;
    best2=10000.;
    best2index=-1;
    for (int j=0;j<BInfo_size;j++) 
      {
	if(BInfo_type[j]>7) continue;
	if (ifchannel[BInfo_type[j]-1]!=1) continue;
	//skim{{{
	b4Pout->SetXYZM(BInfo_px[j],BInfo_py[j],BInfo_pz[j],BInfo_mass[j]);
	temy = b4Pout->Rapidity();
	if(REAL)
	  {
	    if(!(((EvtInfo_RunNo>=210498&&EvtInfo_RunNo<=211256&&abs(temy+0.465)<1.93)||(EvtInfo_RunNo>=211313&&EvtInfo_RunNo<=211631&&abs(temy-0.465)<1.93)))) continue;
	  }
	else
	  {
	    if(abs(temy+0.465)>=1.93) continue;
	  }
	if(BInfo_mass[j]<5 || BInfo_mass[j]>6) continue;
	if(BInfo_pt[j]<10.) continue;
	//}}}
	if(BInfo_type[j]==4 || BInfo_type[j]==5)
	  {
	    fillTree(bP,bVtx,b4P,j,type4size,KAON_MASS,PION_MASS,REAL);
	    if(chi2cl[type4size]>best)
	      {
		best = chi2cl[type4size];
		bestindex = type4size;
	      }
	    if(abs(tktkmass[type4size]-KSTAR_MASS)<best2)
	      {
		best2 = abs(tktkmass[type4size]-KSTAR_MASS);
		best2index = type4size;
	      }
	    type4size++;
	  }
      }
    if(size>0)
      {
	bestchi2 = bestindex;
	isbestchi2[bestindex] = 1;
	besttktkmass = best2index;
	isbesttktkmass[best2index] = 1;
      }
    nt3->Fill();
    
  }

  outf->Write();
  outf->Close();
}


