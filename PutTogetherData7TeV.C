#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>

#include "AliPWGHistoTools.h"
#include "AliPWGFunc.h"
#include "AliLatexTable.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TROOT.h"
#include "TDatabasePDG.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TSystem.h"
#include "THashList.h"
#include "TMinuit.h"
#include "TLatex.h"


#include <TStyle.h>
#include <TPad.h>
#include <TEfficiency.h>
#include <TROOT.h>

#include <TLegend.h>
//#include <TPaveSats.h>


using namespace std;
#endif




void Sphere(const Char_t* fileMapp="Table 1", Int_t TableNr = 1) {


    // load stuff
    gSystem->Load("libTree");
    gSystem->Load("libVMC");
    gSystem->Load("libMinuit");
    gSystem->Load("libSTEERBase");
    gSystem->Load("libESD");
    gSystem->Load("libAOD");
    gSystem->Load("libANALYSIS");
    gSystem->Load("libANALYSISalice");
    gSystem->Load("libCORRFW");
    gSystem->Load("libPWG2spectra");

    gStyle->SetPadGridX("True");
    gStyle->SetPadGridY("True");

    
    // open file
    
    TFile* file = TFile::Open("HEPData-ins1684320-v1-root.root");
    if(!file)
    return;
    
    TFile* file2 = (TFile*)file->Get(fileMapp);
    
    
    TH1D* h = (TH1D*)file2->Get("Hist1D_y1");
    
    
    TH1D* hstat = (TH1D*)file2->Get("Hist1D_y1_e1");

    
    TH1D* hsystfull = (TH1D*)file2->Get("Hist1D_y1_e2");

    
    //TH1D* hsystunc = (TH1D*)file2->Get(fileParty3);


    gROOT->ForceStyle();
    h->UseCurrentStyle();




    
    for (int ibin=1; ibin <= h->GetNbinsX(); ibin++) {
        
        //float err2 = pow( hstat -> GetBinContent(ibin), 2) + pow( hsystfull -> GetBinContent(ibin), 2) + pow( hsystunc -> GetBinContent(ibin), 2);
        
        float err2 = pow( hstat -> GetBinContent(ibin), 2) + pow( hsystfull -> GetBinContent(ibin), 2);

        
        h->SetBinError(ibin,    sqrt (err2) );
    
        cout << "ibin " << ibin << "hsystfull " << hsystfull -> GetBinContent(ibin) << endl;

    
        
    }
    
    
    
    
    
    
    
    TString pwd(gSystem->pwd());
    gSystem->cd(pwd.Data());

    // Test if directory exists or create it
    TString localDirName("outputPutTogetherData");
    //localDirName.ReplaceAll(".root", "");;

    if(gSystem->cd(localDirName.Data())) {

    gSystem->cd(pwd.Data());
    } else {

    gSystem->mkdir(localDirName.Data(), kTRUE); // kTRUE means recursive
    }

    
    
    TCanvas * c = new TCanvas( Form("%d.root", TableNr ) );

    c->SetLogy();

   /*
    h->GetXaxis()->SetDefaults();
    h->GetXaxis()->SetTicks();
    
    h->GetYaxis()->SetDefaults();
    h->GetYaxis()->SetTicks();

    //h->SetTitle(  );


    
    
    
    
    h->GetYaxis()->SetTitleOffset(1.15);
    //h->GetYaxis()->SetTitle("dN/dp_{T} (c/GeV)");
    h->GetXaxis()->SetTitle("V0 p_{T} (GeV/c)");
    
    h->GetYaxis()->SetLabelSize(0.035);  //Tar bort siffrorna
    
    h->GetYaxis()->SetTitleSize(0.044);
*/
    
    //h->GetXaxis()->SetLabelSize(0.035);
   
    //h->SetTitle( "" );

    
    h->SetLineWidth(2);
    h->Draw();

    gPad->Update();
    h->SetStats(0);

    
    //gPad->Update();
    //h->SetStats(1);



   
    h->SetName(Form("%d.root", TableNr ));
    
    h->SaveAs(Form("%s/%d.root", localDirName.Data(), TableNr ));
    
    //c->SaveAs(Form("%s/%s%s.root.C", localDirName.Data(), fileName, filePart ));
    
    
    c->SaveAs(Form("%s/%d.eps", localDirName.Data(), TableNr ));

    
    
    
    
    


}



















