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




void Summer(const Char_t* filePart1="HEPData-ins1784041-v1-Table_1.root",const Char_t* filePart2="HEPData-ins1784041-v1-Table_1.root",const Char_t* filePart3="HEPData-ins1784041-v1-Table_1.root",const Char_t* filePart4="HEPData-ins1784041-v1-Table_1.root",const Char_t* filePart5="HEPData-ins1784041-v1-Table_1.root",const Char_t* filePart6="HEPData-ins1784041-v1-Table_1.root",const Char_t* filePart7="HEPData-ins1784041-v1-Table_1.root",const Char_t* filePart8="HEPData-ins1784041-v1-Table_1.root",const Char_t* filePart9="HEPData-ins1784041-v1-Table_1.root",const Char_t* filePart10="HEPData-ins1784041-v1-Table_1.root") {


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
    
    TFile* file1 = TFile::Open(filePart1);
    if(!file1)
    return;
    
    TH1D* h1 = (TH1D*)file1->Get(filePart1);
    
    
    /*
    TFile* file1 = TFile::Open(filePart1);
    if(!file1)
    return;
    
    TFile* file12 = (TFile*)file1->Get(filePart1);
    
    TH1D* h1 = (TH1D*)file12->Get(filePart1);
    
*/

    //################### 2
    TFile* file2 = TFile::Open(filePart2);
    if(!file2)
    return;
    
    TH1D* h2 = (TH1D*)file2->Get(filePart2);
    

    
    //################### 3
    TFile* file3 = TFile::Open(filePart3);
    if(!file3)
    return;
    
    TH1D* h3 = (TH1D*)file3->Get(filePart3);
    
    
    
    //################### 4
    TFile* file4 = TFile::Open(filePart4);
    if(!file4)
    return;
    
    TH1D* h4 = (TH1D*)file4->Get(filePart4);


    
    
    //################### 5
    TFile* file5 = TFile::Open(filePart5);
    if(!file5)
    return;
    
    TH1D* h5 = (TH1D*)file5->Get(filePart5);

    
    
    //################### 6
    TFile* file6 = TFile::Open(filePart6);
    if(!file6)
    return;
    
    TH1D* h6 = (TH1D*)file6->Get(filePart6);


    
    
    //################### 7
    TFile* file7 = TFile::Open(filePart7);
    if(!file7)
    return;
    
    TH1D* h7 = (TH1D*)file7->Get(filePart7);


    
    //################### 8
    TFile* file8 = TFile::Open(filePart8);
    if(!file8)
    return;
    
    TH1D* h8 = (TH1D*)file8->Get(filePart8);

    
    
    //################### 9
    TFile* file9 = TFile::Open(filePart9);
    if(!file9)
    return;
    
    TH1D* h9 = (TH1D*)file9->Get(filePart9);

    
    
    //################### 10
    TFile* file10 = TFile::Open(filePart10);
    if(!file10)
    return;
    
    TH1D* h10 = (TH1D*)file10->Get(filePart10);

    
    /*
    //################### 1
    TH1D* h1 = TFile::Open(filePart1);
    if(!file1)
    return;
    
    //TH1D* h1 = (TH1D*)file1->Get(filePart1);
    

    //################### 2
    TH1D* h2 = TFile::Open(filePart2);
    if(!file2)
    return;
    
    //TH1D* h2 = (TH1D*)file2->Get(filePart2);
    

    
    //################### 3
    TH1D* h3 = TFile::Open(filePart3);
    if(!file3)
    return;
    
    //TH1D* h3 = (TH1D*)file3->Get(filePart3);
    
    
    
    //################### 4
    TH1D* h4 = TFile::Open(filePart4);
    if(!file4)
    return;
    
    //TH1D* h4 = (TH1D*)file4->Get(filePart4);


    
    
    //################### 5
    TH1D* h5 = TFile::Open(filePart5);
    if(!file5)
    return;
    
    //TH1D* h5 = (TH1D*)file5->Get(filePart5);

    
    
    //################### 6
    TH1D* h6 = TFile::Open(filePart6);
    if(!file6)
    return;
    
    //TH1D* h6 = (TH1D*)file6->Get(filePart6);


    
    
    //################### 7
    TH1D* h7 = TFile::Open(filePart7);
    if(!file7)
    return;
    
    //TH1D* h7 = (TH1D*)file7->Get(filePart7);


    
    //################### 8
    TH1D* h8 = TFile::Open(filePart8);
    if(!file8)
    return;
    
    //TH1D* h8 = (TH1D*)file8->Get(filePart8);

    
    
    //################### 9
    TH1D* h9 = TFile::Open(filePart9);
    if(!file9)
    return;
    
    //TH1D* h9 = (TH1D*)file9->Get(filePart9);

    
    
    //################### 10
    TH1D* h10 = TFile::Open(filePart10);
    if(!file10)
    return;
    
    //TH1D* h10 = (TH1D*)file10->Get(filePart10);

    
    
    */
    
    
    /*
    for (int i =1 ; i<11; i++ ){
        
        TFile* file = TFile::Open(  Form( "filePart%d", i )  );
        if(!file)
        return;

        TString string = Form( "h%d" , i );
        
        TH1D* string = (TH1D*)file;

                                                  
    }
    */
    

                                                  
    
                                                  


    
    


    
    
    

    
    for (int ibin=1; ibin <= (h10->GetNbinsX())-1; ibin++) {
        
        float SUMContent =  (h1 -> GetBinContent(ibin) + h2 -> GetBinContent(ibin) + h3 -> GetBinContent(ibin) + h4 -> GetBinContent(ibin) + h5 -> GetBinContent(ibin) + h6 -> GetBinContent(ibin) + h7 -> GetBinContent(ibin) + h8 -> GetBinContent(ibin) + h9 -> GetBinContent(ibin) + h10 -> GetBinContent(ibin) )/10 ;
        
        float SUMError =  (h1 -> GetBinError(ibin) + h2 -> GetBinError(ibin) + h3 -> GetBinError(ibin) + h4 -> GetBinError(ibin) + h5 -> GetBinError(ibin) + h6 -> GetBinError(ibin) + h7 -> GetBinError(ibin) + h8 -> GetBinError(ibin) + h9 -> GetBinError(ibin) + h10 -> GetBinError(ibin) )/10 ;
        
        
        h1->SetBinContent(ibin,   SUMContent );
        
        h1->SetBinError(ibin,   SUMError );

        
        //cout << "ibin " << ibin << "hsystfull " << hsystfull -> GetBinContent(ibin) << endl;

    
        
    }
    
    
    /*
    if (h1->GetNbinsX() > 43){
        
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

    
    
    
    
    

    
    
    
    
    h->GetYaxis()->SetTitleOffset(1.15);
    //h->GetYaxis()->SetTitle("dN/dp_{T} (c/GeV)");
    h->GetXaxis()->SetTitle("V0 p_{T} (GeV/c)");
    
    h->GetYaxis()->SetLabelSize(0.035);  //Tar bort siffrorna
    
    h->GetYaxis()->SetTitleSize(0.044);
*/
    
    //h->GetXaxis()->SetLabelSize(0.035);
    
 
    //h1->SetLineWidth(2);
    //h->GetYaxis()->SetTitle("dN/dp_{T} (");
    h1->Draw();

    gPad->Update();
    h1->SetStats(0);

    
    //gPad->Update();
    //h->SetStats(1);



   
    
    
    
    
    
    
    


    TString pwd(gSystem->pwd());
    gSystem->cd(pwd.Data());

    // Test if directory exists or create it
    TString localDirName("outputSum");
    localDirName.ReplaceAll(".root", "");;

    if(gSystem->cd(localDirName.Data())) {

    gSystem->cd(pwd.Data());
    } else {

    gSystem->mkdir(localDirName.Data(), kTRUE); // kTRUE means recursive
    }
    
    
    h1->SetName(Form("Tot%s.root", filePart1 ));
    
    h1->SaveAs(Form("Tot%s.root", filePart1 ));
    
    c->SaveAs(Form("%s/Tot%s.root", localDirName.Data(), filePart1 ));
    
    c->SaveAs(Form("%s/Tot%s.eps", localDirName.Data(), filePart1 ));

    
    
    


}



















