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




void Diver(const Char_t* filePart1="HEPData-ins1784041-v1-Table_1.rootHist1D_y1.root",const Char_t* filePart2="TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root") {


    // load stuff
    //gSystem->Load("libTree");
   
    //gSystem->Load("libVMC");
   /* gSystem->Load("libMinuit");
    gSystem->Load("libSTEERBase");
    gSystem->Load("libESD");
    gSystem->Load("libAOD");
    gSystem->Load("libANALYSIS");
    gSystem->Load("libANALYSISalice");
    gSystem->Load("libCORRFW");
    */
    //gSystem->Load("libPWG2spectra");

    gStyle->SetPadGridX("True");
    gStyle->SetPadGridY("True");

    
    // open files

    //################### 1
    /*
    TFile* file1 = TFile::Open(filePart1);
    if(!file1)
    return;
    
    TH1D* h1;
    //h1->Sumw2();
    h1= (TH1D*)file1->Get(filePart1);
    
    

    
    //################### 2
    TFile* file2 = TFile::Open(filePart2);
    if(!file2)
    return;
    
    TH1D* h2;
    //h2->Sumw2();
    h2= (TH1D*)file2->Get(filePart2);
    */

    
    //h1->Divide(h2);
    //h1 -> Draw("E1");
    
    
    
    TFile* file1 = TFile::Open(filePart1);
    if(!file1)
    return;

    
    TFile* file2 = TFile::Open(filePart2);
    if(!file2)
    return;

    TH1D* h1;
    TH1D* h2;

    
    h1= (TH1D*)file1->Get(filePart1);
    h2= (TH1D*)file2->Get(filePart2);
    

    h1->Sumw2();

    
    h1->Divide(h2);
    h1->Draw("E1");
    
    for (int ibin=1; ibin <= (h2 -> GetNbinsX()) ; ibin++) {
        
        if (h1 -> GetXaxis() -> GetBinCenter(ibin) > 10.){
            
            h1 -> SetBinContent(ibin, 0);
            h1 -> SetBinError(ibin, 0);
            
            
        }
        
    }
    
    
    
    
    /*
    for (int i =1 ; i<11; i++ ){
        
        TFile* file = TFile::Open(  Form( "filePart%d", i )  );
        if(!file)
        return;

        TString string = Form( "h%d" , i );
        
        TH1D* string = (TH1D*)file;

                                                  
    }
    */
    

                                                  
    
                                                  


    
    


    
    
    

    /*
    for (int ibin=1; ibin <= (h2 -> GetNbinsX()) ; ibin++) {
        
        float DivContent =  (h1 -> GetBinContent(ibin) )  /   (h2 -> GetBinContent(ibin)   ) ;
        
        //float SUMError =  (h1 -> GetBinError(ibin) + h2 -> GetBinError(ibin) + h3 -> GetBinError(ibin) + h4 -> GetBinError(ibin) + h5 -> GetBinError(ibin) + h6 -> GetBinError(ibin) + h7 -> GetBinError(ibin) + h8 -> GetBinError(ibin) + h9 -> GetBinError(ibin) + h10 -> GetBinError(ibin) )/10 ;
        
        
        h1->SetBinContent(ibin,   DivContent );
        
        h1->SetBinError(ibin,   0.0000001 );
        //interpolation

        
        if (h1 -> GetXaxis() -> GetBinCenter(ibin) > 10. || h2 -> GetXaxis() -> GetBinCenter(ibin) > 10.  ){
            
            h1 -> SetBinContent(ibin, 0);
            
            
        }
        
        
        
        //cout << "ibin " << ibin << "hsystfull " << hsystfull -> GetBinContent(ibin) << endl;

    
        
    }
    */
    
    
    
    /*
    if (h2->GetNbinsX() > 43){
        
        for (int ibin= 44; ibin <= h1->GetNbinsX()  ; ibin++) {
            
            
            h1->SetBinContent(ibin,   0 );

            h1->SetBinError(ibin,   0 );

        
            
        }

        
        
    }
    */
    

    
    
    
    
    


    
    
    
    
    TCanvas * c = new TCanvas();

    //c->SetLogy();

   /*
    h->GetXaxis()->SetDefaults();
    h->GetXaxis()->SetTicks();
    
    h->GetYaxis()->SetDefaults();
    h->GetYaxis()->SetTicks();

    //h->SetTitle(  );

    
    
    h1->SetTitle( "" );

    
    h1->GetYaxis()->SetTitle("(dN/dp_{T}) /(dN_{MB}/dp_{T})");
    h1->GetXaxis()->SetTitle("p_{T} (GeV/c)");

    
    

    
    
    
    
    h->GetYaxis()->SetTitleOffset(1.15);
    //h->GetYaxis()->SetTitle("dN/dp_{T} (c/GeV)");
    h->GetXaxis()->SetTitle("V0 p_{T} (GeV/c)");
   
    
    h->GetYaxis()->SetLabelSize(0.035);  //Tar bort siffrorna
    
    h->GetYaxis()->SetTitleSize(0.044);
*/
    
    //h1->GetXaxis()->SetLabelSize(0.035);
    
 
    //h1->SetLineWidth(2);
  
    
    
    h1->Draw();

    gPad->Update();
    h1->SetStats(0);

    
    //gPad->Update();
    //h->SetStats(1);



   
    
    
    
    
    
    
    


    TString pwd(gSystem->pwd());
    gSystem->cd(pwd.Data());

    // Test if directory exists or create it
    TString localDirName("outputDiv");
    localDirName.ReplaceAll(".root", "");;

    if(gSystem->cd(localDirName.Data())) {

    gSystem->cd(pwd.Data());
    } else {

    gSystem->mkdir(localDirName.Data(), kTRUE); // kTRUE means recursive
    }
    
    
    
    //h1->SaveAs(Form("TotNewww%s.root", filePart1 ));
    
    h1->SetName(Form("Div%s.root", filePart1 ));
    
    h1->SaveAs(Form("%s/Div%s.root", localDirName.Data(), filePart1 ));
    h1->SaveAs(Form("Div%s.root", filePart1 ));
    c->SaveAs(Form("%s/Div%s.eps", localDirName.Data(), filePart1 ));

    
    
    


}



















