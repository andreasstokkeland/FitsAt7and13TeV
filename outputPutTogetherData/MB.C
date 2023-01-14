

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

#include <THStack.h>


#include <TLegend.h>
//#include <TPaveSats.h>


using namespace std;
#endif


Double_t FuncDiver(Double_t *x, Double_t *p)
{
    Double_t pt = x[0];
    
    Double_t norm1 = p[0];
    Double_t n1 = p[1];
    Double_t temp1 = p[2];
    Double_t mass = p[3];
    Double_t norm2 = p[4];
    Double_t n2 = p[5];
    Double_t temp2 = p[6];
    
    
    Double_t fup = (( pt*norm1*(n1-1)*(n1-2)  )/( n1*temp1*( n1*temp1+mass*(n1-2) )  )) * TMath::Power(( 1 + (sqrt(mass*mass+pt*pt) -mass)/(n1*temp1)  ),(-n1));
    
    Double_t fdown = (( pt*norm2*(n2-1)*(n2-2)  )/( n2*temp2*( n2*temp2+mass*(n2-2) )  )) * TMath::Power(( 1 + (sqrt(mass*mass+pt*pt) -mass)/(n2*temp2)  ),(-n2));
    
    Double_t fDiv = fup/fdown;
    
    return fDiv;
    
}



void HEPData() {

    gStyle->SetPadGridX("True");
    gStyle->SetPadGridY("True");

    TH1D **HistosPion7;
    HistosPion7 = new TH1D*[10];
    
    
    //################################################ "7 TeV" ################################################
    
    int YPion[9] = {11,12,13,14,15,16,17,18,19};

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("%d.root", YPion[i]  ));
        
        if(!file)
        return;
        
        HistosPion7[i] = (TH1D*)file->Get(Form("%d.root", YPion[i]  ));
        
    }
    
    TFile* fileP7 = TFile::Open( "Tot11.root.root" );
    
    if(!fileP7)
    return;
    
    HistosPion7[9] = (TH1D*)fileP7->Get( "Tot11.root.root"  );

    
    
    
    
    
    AliPWGFunc * fm;
    fm = new AliPWGFunc;
    fm->SetVarType(AliPWGFunc::VarType_t(AliPWGFunc::kdNdpt));
    
    
    
    
    Double_t massPion = TDatabasePDG::Instance()->GetParticle("pi+")->Mass();
    
    TF1 **funcsPion7;
    funcsPion7 = new TF1*[10];
    
    for (int i = 0; i <= 9 ; i++){
        
        cout << "Pion fit #" << i << endl;
        funcsPion7[i] = fm->GetLevi(massPion, 0.4, 750,3);
        funcsPion7[i]->SetRange(0.4, 10);
        HistosPion7[i]->Fit(funcsPion7[i],"","",0.4,10);
    }

    
    

    TH1D **HistosMBPion7;
    HistosMBPion7 = new TH1D*[9];


    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("Div%d.root.root", YPion[i]  ));
        
        if(!file)
        return;
        
        HistosMBPion7[i] = (TH1D*)file->Get(Form("Div%d.root.root", YPion[i]  ));
        
    }

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int YKaon[9] = {21,22,23,24,25,26,27,28,29};
    
    
    TH1D **HistosKaon7;
    HistosKaon7 = new TH1D*[10];

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("%d.root", YKaon[i]  ));
        
        if(!file)
        return;
        
        HistosKaon7[i] = (TH1D*)file->Get(Form("%d.root", YKaon[i]  ));
        
    }
    

    TFile* fileK7 = TFile::Open( "Tot21.root.root" );
    
    if(!fileK7)
    return;
    
    HistosKaon7[9] = (TH1D*)fileK7->Get( "Tot21.root.root"  );


    
    
    
    
    
    
    Double_t massKaon = TDatabasePDG::Instance()->GetParticle("K+")->Mass();
    
    TF1 **funcsKaon7;
    funcsKaon7 = new TF1*[10];
    
    for (int i = 0; i <= 9 ; i++){
        
        cout << "Kaon fit #" << i << endl;
        funcsKaon7[i] = fm->GetLevi(massKaon, 0.19, 750,3);
        funcsKaon7[i]->SetRange(0.4, 10);
        HistosKaon7[i]->Fit(funcsKaon7[i],"","",0.4,10);
        
        cout << funcsKaon7[i]->GetParameter(1) << endl;
    
    }
    
    funcsKaon7[8] = fm->GetLevi(massKaon, 0.4, 750,3);
    funcsKaon7[8]->SetRange(0.4, 10);
    HistosKaon7[8]->Fit(funcsKaon7[8],"","",0.4,10);
    
    
    TH1D **HistosMBKaon7;
    HistosMBKaon7 = new TH1D*[9];


    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("Div%d.root.root", YKaon[i]  ));
        
        if(!file)
        return;
        
        HistosMBKaon7[i] = (TH1D*)file->Get(Form("Div%d.root.root", YKaon[i]  ));
        
    }
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int YProton[9] = {31,32,33,34,35,36,37,38,39};

    
    TH1D **HistosProton7;
    HistosProton7 = new TH1D*[10];

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("%d.root", YProton[i]  ));
        
        if(!file)
        return;
        
        HistosProton7[i] = (TH1D*)file->Get(Form("%d.root", YProton[i]  ));
        
    }
    
    TFile* filePr7 = TFile::Open( "Tot31.root.root" );
    
    if(!filePr7)
    return;
    
    HistosProton7[9] = (TH1D*)filePr7->Get( "Tot31.root.root"  );

    
    
    
    
    Double_t massProton = TDatabasePDG::Instance()->GetParticle("proton")->Mass();
    
    TF1 **funcsProton7;
    funcsProton7 = new TF1*[10];
    
    for (int i = 0; i <= 9 ; i++){
        
        cout << "Proton fit #" << i << endl;
        funcsProton7[i] = fm->GetLevi(massProton, 0.4, 750,3);
        funcsProton7[i]->SetRange(0.4, 10);
        HistosProton7[i]->Fit(funcsProton7[i],"","",0.4,10);
    }
    
    
    TH1D **HistosMBProton7;
    HistosMBProton7 = new TH1D*[9];


    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("Div%d.root.root", YProton[i]  ));
        
        if(!file)
        return;
        
        HistosMBProton7[i] = (TH1D*)file->Get(Form("Div%d.root.root", YProton[i]  ));
        
    }

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //################################################ "13 TeV" ################################################
    
    
    
    TH1D **HistosPion13;
    HistosPion13 = new TH1D*[10];
    
    int Y[9] = {1,2,3,4,5,6,7,8,9};

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("HEPData-ins1784041-v1-Table_1.rootHist1D_y%d.root", Y[i]  ));
        
        if(!file)
        return;
        
        HistosPion13[i] = (TH1D*)file->Get(Form("HEPData-ins1784041-v1-Table_1.rootHist1D_y%d.root", Y[i]  ));
        
    }
    
    
    TFile* fileP13 = TFile::Open( "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root" );
    
    if(!fileP13)
    return;
    
    HistosPion13[9] = (TH1D*)fileP13->Get( "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root"  );

    
    

    
    
    
    
    
    
//    AliPWGFunc * fm;
//    fm = new AliPWGFunc;
//    fm->SetVarType(AliPWGFunc::VarType_t(AliPWGFunc::kdNdpt));
//
    //Double_t massPion = TDatabasePDG::Instance()->GetParticle("pi+")->Mass();
    
    TF1 **funcsPion13;
    funcsPion13 = new TF1*[10];
    
    for (int i = 0; i <= 9 ; i++){
        
        cout << "Pion fit #" << i << endl;
        funcsPion13[i] = fm->GetLevi(massPion, 0.4, 750,3);
        funcsPion13[i]->SetRange(0.4, 10);
        HistosPion13[i]->Fit(funcsPion13[i],"","",0.4,10);
    }

    
    

    TH1D **HistosMBPion13;
    HistosMBPion13 = new TH1D*[9];


    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 1, Y[i]  ));
        
        if(!file)
        return;
        
        HistosMBPion13[i] = (TH1D*)file->Get(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 1, Y[i]  ));
        
    }

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    TH1D **HistosKaon13;
    HistosKaon13 = new TH1D*[10];

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("HEPData-ins1784041-v1-Table_3.rootHist1D_y%d.root", Y[i]  ));
        
        if(!file)
        return;
        
        HistosKaon13[i] = (TH1D*)file->Get(Form("HEPData-ins1784041-v1-Table_3.rootHist1D_y%d.root", Y[i]  ));
        
    }
    
    
    TFile* fileK13 = TFile::Open( "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root" );
    
    if(!fileK13)
    return;
    
    HistosKaon13[9] = (TH1D*)fileK13->Get( "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root"  );

    

    
    
    //Double_t massKaon = TDatabasePDG::Instance()->GetParticle("K+")->Mass();
    
    TF1 **funcsKaon13;
    funcsKaon13 = new TF1*[10];
    
    for (int i = 0; i <= 9 ; i++){
        
        cout << "Kaon fit #" << i << endl;
        funcsKaon13[i] = fm->GetLevi(massKaon, 0.4, 750,3);
        funcsKaon13[i]->SetRange(0.4, 10);
        HistosKaon13[i]->Fit(funcsKaon13[i],"","",0.4,10);
    
    }
    
    
    
    TH1D **HistosMBKaon13;
    HistosMBKaon13 = new TH1D*[9];


    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 3, Y[i]  ));
        
        if(!file)
        return;
        
        HistosMBKaon13[i] = (TH1D*)file->Get(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 3, Y[i]  ));
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    
    TH1D **HistosProton13;
    HistosProton13 = new TH1D*[10];

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("HEPData-ins1784041-v1-Table_5.rootHist1D_y%d.root", Y[i]  ));
        
        if(!file)
        return;
        
        HistosProton13[i] = (TH1D*)file->Get(Form("HEPData-ins1784041-v1-Table_5.rootHist1D_y%d.root", Y[i]  ));
        
    }
    
    
    TFile* filePr13 = TFile::Open( "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root" );
    
    if(!filePr13)
    return;
    
    HistosProton13[9] = (TH1D*)filePr13->Get( "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root"  );

    
    
    
    
    
    //Double_t massProton = TDatabasePDG::Instance()->GetParticle("proton")->Mass();
    
    TF1 **funcsProton13;
    funcsProton13 = new TF1*[10];
    
    for (int i = 0; i <= 9 ; i++){
        
        cout << "Proton fit #" << i << endl;
        funcsProton13[i] = fm->GetLevi(massProton, 0.4, 750,3);
        funcsProton13[i]->SetRange(0.4, 10);
        HistosProton13[i]->Fit(funcsProton13[i],"","",0.4,10);
    }
    
    
    TH1D **HistosMBProton13;
    HistosMBProton13 = new TH1D*[9];


    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 5, Y[i]  ));
        
        if(!file)
        return;
        
        HistosMBProton13[i] = (TH1D*)file->Get(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 5, Y[i]  ));
        
    }

    
    
    
    
    
    
    
    
    

    
    
    
    //################################################ "Printing" ################################################

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
//################################################ "Printing" ################################################

    
    

    
    
    
    

    
    
    float MinForAll = 0.00000008;
    float ShiftFor7 = 0.00000007;
    
    
    int Color[3] = {4,632-2,2};
    
    int FuncColor = 433;
    
    //Histos[i]->SetMaximum(5.1);
    //Histos[i]->SetMinimum(-1.1);

    cout << "Hej" << endl;

    
    TCanvas * c = new TCanvas();

    c-> Divide (3,2) ;
    
    
    c->cd(1);
    
    double TextXStart = 0.1;
    double TextYStart = 0.9;
    
    
//    TLatex *lName7 = new TLatex(TextXStart, TextYStart, "Row of data at #sqrt{s} = 7 TeV"  );


//    lName7->SetNDC();
//    lName7->SetTextSize(0.04);
//    lName7->Draw();
    
    gStyle->SetTitleSize(0.1,"t");

    
    Float_t SIZE = 0.05;
    
//        HistosPion7[0]->GetXaxis()->SetLabelSize(SIZE);
//    HistosPion7[0]->GetYaxis()->SetLabelSize(SIZE);
//
//    HistosPion7[0]->GetYaxis()->SetTitleSize(SIZE);

    
    
    float XStart = 0.45;
    float YStart = 0.82;
    
    
    TF1 **funcsPionDiv7;
    funcsPionDiv7 = new TF1*[9];
    
    
    for (int i = 0; i < 9 ; i++){
        
        funcsPionDiv7[i] = new TF1("f",FuncDiver,0.4,10,7);
        funcsPionDiv7[i] ->SetParNames(Form("Norm%d", i), Form("n%d", i), Form("temp%d", i), "mass", Form("NormMB%d", i), Form("nMB%d", i), Form("tempMB%d", i));
        funcsPionDiv7[i] ->SetParameter(0, funcsPion7[i]->GetParameter(0) );
        funcsPionDiv7[i] ->SetParameter(1, funcsPion7[i]->GetParameter(1) );
        funcsPionDiv7[i] ->SetParameter(2, funcsPion7[i]->GetParameter(2) );
        funcsPionDiv7[i] ->SetParameter(3, massPion );
        
        funcsPionDiv7[i] ->SetParameter(4, funcsPion7[9]->GetParameter(0) );
        funcsPionDiv7[i] ->SetParameter(5, funcsPion7[9]->GetParameter(1) );
        funcsPionDiv7[i] ->SetParameter(6, funcsPion7[9]->GetParameter(2) );
        funcsPionDiv7[i] ->SetLineColor( FuncColor );

    
        
        HistosMBPion7[i]->GetListOfFunctions()->Add(funcsPionDiv7[i]);
        HistosMBPion7[i]-> GetXaxis() -> SetRangeUser(0, 10);
        HistosMBPion7[i]-> GetYaxis() -> SetRangeUser(0, 4.5);
        HistosMBPion7[i]->SetLineColor( Color[0] );

        HistosMBPion7[i]->Draw("sames");

        
        HistosMBPion7[i]->SetTitle( "" ); //Ratios of Levi fits for multiplicities and MB at #sqrt{s} = 7 TeV for #pi#pm

        
        
        //Levi fits for each multiplicity divided by Levi fit for min bias
        //=> Ratios of Levi fits for multiplicities and MB
        
        //HistosMBPion7[i]-> GetYaxis()->SetTitle("#frac{#it{dN}}{#it{dp}_{T}} #[]{#frac{#it{dN}_{MB}}{#it{dp}_{T}}}^{-1} ");

        HistosMBPion7[i]-> GetYaxis()->SetTitle("#frac{#it{dN}}{#it{dp}_{T}} #[]{#frac{#it{dN}_{MB}}{#it{dp}_{T}}}^{-1} ");

        
        HistosMBPion7[i]->GetYaxis()->SetTitleOffset(-1.55);
        
        HistosMBPion7[i] ->GetYaxis()->SetTitleSize(0.05);


        HistosMBPion7[i]-> GetXaxis()->SetTitle(" #bf{#it{p}_{T} (GeV/c)}");
        
        HistosMBPion7[i] ->GetXaxis()->SetTitleSize(0.045);

        
    }

    
    

    TLatex *lFunc1 = new TLatex(XStart, YStart,Form("#color[1]{#scale[1.5]{#pi}^{#scale[2]{#pm}} at #sqrt{s} = 7 TeV }") );
    
    //TLatex *lFunc1 = new TLatex(XStart, YStart,Form("#color[1]{#pi^{#pm} at #sqrt{s} = 7 TeV }") );

    
    
    lFunc1->SetNDC();
    lFunc1->SetTextSize(0.05);
    lFunc1->Draw();

    
    
    
    
    c->cd(2);

    
    
    
    
    
    TF1 **funcsKaonDiv7;
    funcsKaonDiv7 = new TF1*[9];
    
    
    for (int i = 0; i < 9 ; i++){
        
        funcsKaonDiv7[i] = new TF1("f",FuncDiver,0.4,10,7);
        funcsKaonDiv7[i] ->SetParNames(Form("Norm%d", i), Form("n%d", i), Form("temp%d", i), "mass", Form("NormMB%d", i), Form("nMB%d", i), Form("tempMB%d", i));
        funcsKaonDiv7[i] ->SetParameter(0, funcsKaon7[i]->GetParameter(0) );
        funcsKaonDiv7[i] ->SetParameter(1, funcsKaon7[i]->GetParameter(1) );
        funcsKaonDiv7[i] ->SetParameter(2, funcsKaon7[i]->GetParameter(2) );
        funcsKaonDiv7[i] ->SetParameter(3, massKaon );
        
        funcsKaonDiv7[i] ->SetParameter(4, funcsKaon7[9]->GetParameter(0) );
        funcsKaonDiv7[i] ->SetParameter(5, funcsKaon7[9]->GetParameter(1) );
        funcsKaonDiv7[i] ->SetParameter(6, funcsKaon7[9]->GetParameter(2) );
        funcsKaonDiv7[i] ->SetLineColor( FuncColor );

    
                
        HistosMBKaon7[i]->GetListOfFunctions()->Add(funcsKaonDiv7[i]);
        HistosMBKaon7[i]-> GetXaxis() -> SetRangeUser(0, 10);
        HistosMBKaon7[i]-> GetYaxis() -> SetRangeUser(0, 4.5);
        HistosMBKaon7[i]->SetLineColor( Color[1] );
        

        HistosMBKaon7[i]->Draw("sames");

        HistosMBKaon7[i]->SetTitle( "Multiplicity classes over MB with" ); //Levi fits for each multiplicity divided by Levi fit for min bias at #sqrt{s} = 13 TeV for K#pm
        
        
        //HistosMBKaon7[i]->SetTitle( "Ratios of Levi fits for multiplicities and MB" );
        
        //Ratios of Levi fits for multiplicities and MB
        
        HistosMBKaon7[i]-> GetYaxis()->SetTitle(""); //#frac{#it{dN}}{#it{dp}_{T}} #[]{#frac{#it{dN}_{MB}}{#it{dp}_{T}}}^{-1}


        HistosMBKaon7[i]-> GetXaxis()->SetTitle(" #bf{#it{p}_{T} (GeV/c)}");
        
        HistosMBKaon7[i] ->GetXaxis()->SetTitleSize(0.045);

        
        //hDivKaon->Draw("sames");
        
    }

    
    TLatex *lFunc2 = new TLatex(XStart, YStart,Form("#color[1]{#scale[1.2]{K}^{#scale[2]{#pm}} at #sqrt{s} = 7 TeV }") );
    
    
    
    lFunc2->SetNDC();
    lFunc2->SetTextSize(0.05);
    lFunc2->Draw();






    cout << "Hej" << endl;

    
    
    
    
    
    
    
    
    
    
    c->cd(3);

    
    
    
    
    TF1 **funcsProtonDiv7;
    funcsProtonDiv7 = new TF1*[9];
    
    
    for (int i = 0; i < 9 ; i++){
        
        funcsProtonDiv7[i] = new TF1("f",FuncDiver,0.4,10,7);
        funcsProtonDiv7[i] ->SetParNames(Form("Norm%d", i), Form("n%d", i), Form("temp%d", i), "mass", Form("NormMB%d", i), Form("nMB%d", i), Form("tempMB%d", i));
        funcsProtonDiv7[i] ->SetParameter(0, funcsProton7[i]->GetParameter(0) );
        funcsProtonDiv7[i] ->SetParameter(1, funcsProton7[i]->GetParameter(1) );
        funcsProtonDiv7[i] ->SetParameter(2, funcsProton7[i]->GetParameter(2) );
        funcsProtonDiv7[i] ->SetParameter(3, massProton );
        
        funcsProtonDiv7[i] ->SetParameter(4, funcsProton7[9]->GetParameter(0) );
        funcsProtonDiv7[i] ->SetParameter(5, funcsProton7[9]->GetParameter(1) );
        funcsProtonDiv7[i] ->SetParameter(6, funcsProton7[9]->GetParameter(2) );
        funcsProtonDiv7[i] ->SetLineColor( FuncColor );
    
        
        
        HistosMBProton7[i]->GetListOfFunctions()->Add(funcsProtonDiv7[i]);
        HistosMBProton7[i]-> GetXaxis() -> SetRangeUser(0, 10);
        HistosMBProton7[i]-> GetYaxis() -> SetRangeUser(0, 4.5);
        HistosMBProton7[i]->SetLineColor( Color[2] );
        HistosMBProton7[i]->Draw("sames");

        HistosMBProton7[i]->SetTitle( "" );    //"Levi fits for each multiplicity divided by Levi fit for min bias at #sqrt{s} = 13 TeV for protons"
 
        HistosMBProton7[i]-> GetYaxis()->SetTitle("");
//
//
//        HistosMBProton7[i]->GetYaxis()->SetTitleOffset(-1.5);

        
        HistosMBProton7[i]-> GetXaxis()->SetTitle(" #bf{#it{p}_{T} (GeV/c)}");
        
        HistosMBProton7[i] ->GetXaxis()->SetTitleSize(0.045);
        
        //hDivProton->Draw("sames");
        
    }

    
    
    TLatex *lFunc3 = new TLatex(0.46, 0.56,Form("#color[1]{p(#bar{p}) at #sqrt{s} = 7 TeV }") );
    
    
    
    lFunc3->SetNDC();
    lFunc3->SetTextSize(0.05);
    lFunc3->Draw();


    
    
    
    
    
    
    
    
    
    
    
    
//    auto legendH = new TLegend(0.5, 0.55, 0.9, 0.9); //(start from left, start from bottom ) //x1,y1,x2,y2
//    legendH->SetHeader("Particles","C"); // option "C" allows to center the header
//    legendH->AddEntry(HistosPion7[0], "#pi#pm","l");
//    legendH->AddEntry(HistosKaon7[0], "K#pm","l");
//    legendH->AddEntry(HistosProton7[0], "p(#bar{p})","l");
//
//    legendH->Draw();

    
    cout << "Hej4" << endl;
    
    //c7->SaveAs( "HEPDataFit7.eps" );

    
    
    
    //########################## "13 TeV Print" ##########################
    
    //TCanvas * c13 = new TCanvas();

    //c13-> Divide (3,1) ;

    
    c->cd(4);

    
    
//    TLatex *lName13 = new TLatex(TextXStart, TextYStart, "Row of data at #sqrt{s} = 13 TeV"  );
//
//
//    lName13->SetNDC();
//    lName13->SetTextSize(0.04);
//    lName13->Draw();
    
    
    
    TF1 **funcsPionDiv13;
    funcsPionDiv13 = new TF1*[9];
    
    
    for (int i = 0; i < 9 ; i++){
        
        funcsPionDiv13[i] = new TF1("f",FuncDiver,0.4,10,7);
        funcsPionDiv13[i] ->SetParNames(Form("Norm%d", i), Form("n%d", i), Form("temp%d", i), "mass", Form("NormMB%d", i), Form("nMB%d", i), Form("tempMB%d", i));
        funcsPionDiv13[i] ->SetParameter(0, funcsPion13[i]->GetParameter(0) );
        funcsPionDiv13[i] ->SetParameter(1, funcsPion13[i]->GetParameter(1) );
        funcsPionDiv13[i] ->SetParameter(2, funcsPion13[i]->GetParameter(2) );
        funcsPionDiv13[i] ->SetParameter(3, massPion );
        
        funcsPionDiv13[i] ->SetParameter(4, funcsPion13[9]->GetParameter(0) );
        funcsPionDiv13[i] ->SetParameter(5, funcsPion13[9]->GetParameter(1) );
        funcsPionDiv13[i] ->SetParameter(6, funcsPion13[9]->GetParameter(2) );
        
        funcsPionDiv13[i] ->SetLineColor( FuncColor );

    
        
        HistosMBPion13[i]->GetListOfFunctions()->Add(funcsPionDiv13[i]);
        HistosMBPion13[i]-> GetXaxis() -> SetRangeUser(0, 10);
        HistosMBPion13[i]-> GetYaxis() -> SetRangeUser(0, 4.5);
        HistosMBPion13[i]->SetLineColor( Color[0] );

        HistosMBPion13[i]->Draw("sames");

        
        HistosMBPion13[i]->SetTitle( "" );  //Levi fits for each multiplicity divided by Levi fit for min bias at #sqrt{s} = 13 TeV for #pi#pm

        //HistosMBPion13[i]-> GetYaxis()->SetTitle(""); //#frac{#it{dN}}{#it{dp}_{T}} #[]{#frac{#it{dN}_{MB}}{#it{dp}_{T}}}^{-1}

        HistosMBPion13[i]-> GetXaxis()->SetTitle(" #bf{#it{p}_{T} (GeV/c)}");
        
        HistosMBPion13[i] ->GetXaxis()->SetTitleSize(0.045);
        
        HistosMBPion13[i]-> GetYaxis()->SetTitle("#frac{#it{dN}}{#it{dp}_{T}} #[]{#frac{#it{dN}_{MB}}{#it{dp}_{T}}}^{-1} ");

        
        HistosMBPion13[i]->GetYaxis()->SetTitleOffset(-1.55);
        
        HistosMBPion13[i] ->GetYaxis()->SetTitleSize(0.05);

        
    }

    
    TLatex *lFunc4 = new TLatex(XStart, YStart,Form("#color[1]{#scale[1.5]{#pi}^{#scale[2]{#pm}} at #sqrt{s} = 13 TeV }") );
    
    
    
    lFunc4->SetNDC();
    lFunc4->SetTextSize(0.05);
    lFunc4->Draw();
    
    
    
    
    
    
    cout << "Hej5" << endl;
    
    c->cd(5);

    cout << "Hej51" << endl;

    
    
    
    
    
    TF1 **funcsKaonDiv13;
    funcsKaonDiv13 = new TF1*[9];
    
    
    for (int i = 0; i < 9 ; i++){
        
        funcsKaonDiv13[i] = new TF1("f",FuncDiver,0.4,10,7);
        funcsKaonDiv13[i] ->SetParNames(Form("Norm%d", i), Form("n%d", i), Form("temp%d", i), "mass", Form("NormMB%d", i), Form("nMB%d", i), Form("tempMB%d", i));
        funcsKaonDiv13[i] ->SetParameter(0, funcsKaon13[i]->GetParameter(0) );
        funcsKaonDiv13[i] ->SetParameter(1, funcsKaon13[i]->GetParameter(1) );
        funcsKaonDiv13[i] ->SetParameter(2, funcsKaon13[i]->GetParameter(2) );
        funcsKaonDiv13[i] ->SetParameter(3, massKaon );
        
        funcsKaonDiv13[i] ->SetParameter(4, funcsKaon13[9]->GetParameter(0) );
        funcsKaonDiv13[i] ->SetParameter(5, funcsKaon13[9]->GetParameter(1) );
        funcsKaonDiv13[i] ->SetParameter(6, funcsKaon13[9]->GetParameter(2) );
        funcsKaonDiv13[i] ->SetLineColor( FuncColor );

        
                
        HistosMBKaon13[i]->GetListOfFunctions()->Add(funcsKaonDiv13[i]);
        HistosMBKaon13[i]-> GetXaxis() -> SetRangeUser(0, 10);
        HistosMBKaon13[i]-> GetYaxis() -> SetRangeUser(0, 4.5);
        HistosMBKaon13[i]->SetLineColor( Color[1] );

        HistosMBKaon13[i]->Draw("sames");

        //HistosMBKaon13[i]->SetTitle( "" ); //Levi fits for each multiplicity divided by Levi fit for min bias at #sqrt{s} = 13 TeV for K#pm

        HistosMBKaon13[i]->SetTitle( "" );

        
        HistosMBKaon13[i]-> GetYaxis()->SetTitle("");

        HistosMBKaon13[i]-> GetXaxis()->SetTitle(" #bf{#it{p}_{T} (GeV/c)}");
        
        HistosMBKaon13[i] ->GetXaxis()->SetTitleSize(0.045);

        
        //hDivKaon->Draw("sames");
        
    }
    
    
    //ratios of Levi fits for multiplicity classes and MB

    TLatex *lFuncTitle = new TLatex(0.02, 0.93,Form("#color[1]{ratios of Levi fits for multiplicity classes and MB }") );
    
    
    
    lFuncTitle->SetNDC();
    lFuncTitle->SetTextSize(0.045);
    lFuncTitle->Draw();

    
    
    
    TLatex *lFunc5 = new TLatex(XStart, YStart,Form("#color[1]{#scale[1.2]{K}^{#scale[2]{#pm}} at #sqrt{s} = 13 TeV }") );
    
    
    
    lFunc5->SetNDC();
    lFunc5->SetTextSize(0.05);
    lFunc5->Draw();
    
    
    
    
    
    
    
    c->cd(6);

    
    
    
    
    TF1 **funcsProtonDiv13;
    funcsProtonDiv13 = new TF1*[9];
    
    
    for (int i = 0; i < 9 ; i++){
        
        funcsProtonDiv13[i] = new TF1("f",FuncDiver,0.4,10,7);
        funcsProtonDiv13[i] ->SetParNames(Form("Norm%d", i), Form("n%d", i), Form("temp%d", i), "mass", Form("NormMB%d", i), Form("nMB%d", i), Form("tempMB%d", i));
        funcsProtonDiv13[i] ->SetParameter(0, funcsProton13[i]->GetParameter(0) );
        funcsProtonDiv13[i] ->SetParameter(1, funcsProton13[i]->GetParameter(1) );
        funcsProtonDiv13[i] ->SetParameter(2, funcsProton13[i]->GetParameter(2) );
        funcsProtonDiv13[i] ->SetParameter(3, massProton );
        
        funcsProtonDiv13[i] ->SetParameter(4, funcsProton13[9]->GetParameter(0) );
        funcsProtonDiv13[i] ->SetParameter(5, funcsProton13[9]->GetParameter(1) );
        funcsProtonDiv13[i] ->SetParameter(6, funcsProton13[9]->GetParameter(2) );
        funcsProtonDiv13[i] ->SetLineColor( FuncColor );
    
        
        
        HistosMBProton13[i]->GetListOfFunctions()->Add(funcsProtonDiv13[i]);
        HistosMBProton13[i]-> GetXaxis() -> SetRangeUser(0, 10);
        HistosMBProton13[i]-> GetYaxis() -> SetRangeUser(0, 4.5);
        HistosMBProton13[i]->SetLineColor( Color[2] );

        HistosMBProton13[i]->Draw("sames");

        HistosMBProton13[i]->SetTitle( "" );  // Levi fits for each multiplicity divided by Levi fit for min bias at #sqrt{s} = 13 TeV for protons

        HistosMBProton13[i]-> GetYaxis()->SetTitle(""); //#frac{#it{dN}}{#it{dp}_{T}} #[]{#frac{#it{dN}_{MB}}{#it{dp}_{T}}}^{-1}

        
        //HistosMBProton13[i]->GetYaxis()->SetTitleOffset(-1.5);

        
        
        
        HistosMBProton13[i]-> GetXaxis()->SetTitle(" #bf{#it{p}_{T} (GeV/c)}");
        
        HistosMBProton13[i] ->GetXaxis()->SetTitleSize(0.045);
        
        
        
        
        
        
        
        //hDivProton->Draw("sames");
        
    }

    
    
    TLatex *lFunc6 = new TLatex(0.46, 0.56,Form("#color[1]{p(#bar{p}) at #sqrt{s} = 13 TeV }") );
    
    
    
    lFunc6->SetNDC();
    lFunc6->SetTextSize(0.05);
    lFunc6->Draw();


    
    
    
    
    
    
    
    
    
    
    cout << "Hej7" << endl;
    
    
    c->SaveAs( "MB.eps" );

    
    
    
    
//    TCanvas * c7 = new TCanvas();
//
//    c7-> Divide (3,1) ;
//
//
//    c7->cd(1);
//    c7->cd(1)->SetLogy();
//
//    HistosPion7[0] ->SetTitle( "" );
//    HistosPion7[0] ->SetMinimum(MinForAll);
//    HistosPion7[0]->GetXaxis()->SetTitle("");
//    HistosPion7[0]->GetYaxis()->SetTitle("");
//
//    for (int i = 0 ; i < 10; i++){
//
//        HistosPion7[i]->SetLineColor(Color[0]);
//        HistosPion7[i]->Draw("sames");
//        //funcsPion[i]->SetLineColor(funcColor);
//        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
//
//    }
//
//    cout << "Hej" << endl;
//
//    c7->cd(2);
//    c7->cd(2)->SetLogy();
//
//    HistosKaon7[0] ->SetTitle( "" );
//    HistosKaon7[0] ->SetMinimum(MinForAll);
//    HistosKaon7[0]->GetXaxis()->SetTitle("");
//    HistosKaon7[0]->GetYaxis()->SetTitle("");
//
//    for (int i = 0 ; i < 10; i++){
//
//        HistosKaon7[i]->SetLineColor(Color[1]);
//        HistosKaon7[i]->Draw("sames");
//        //funcsPion[i]->SetLineColor(funcColor);
//        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
//
//    }
//    cout << "Hej" << endl;
//
//
//    c7->cd(3);
//    c7->cd(3)->SetLogy();
//
//    HistosProton7[0] ->SetTitle( "" );
//    HistosProton7[0] ->SetMinimum(MinForAll);
//    HistosProton7[0]->GetXaxis()->SetTitle("");
//    HistosProton7[0]->GetYaxis()->SetTitle("");
//
//    for (int i = 0 ; i < 10; i++){
//
//        HistosProton7[i]->SetLineColor(Color[2]);
//        HistosProton7[i]->Draw("sames");
//        //funcsPion[i]->SetLineColor(funcColor);
//        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
//
//    }
//
//
//    cout << "Hej4" << endl;
//
//    c7->SaveAs( "HEPDataFit7.eps" );
//
//
//
//
//    //########################## "13 TeV Print" ##########################
//
//    TCanvas * c13 = new TCanvas();
//
//    c13-> Divide (3,1) ;
//
//
//    c13->cd(1);
//    c13->cd(1)->SetLogy();
//
//    HistosPion13[0] ->SetTitle( "" );
//    HistosPion13[0] ->SetMinimum(MinForAll);
//    HistosPion13[0]->GetXaxis()->SetTitle("");
//    HistosPion13[0]->GetYaxis()->SetTitle("");
//
//    for (int i = 0 ; i < 10; i++){
//
//        HistosPion13[i]->SetLineColor(Color[0]);
//        HistosPion13[i]->Draw("sames");
//        //funcsPion[i]->SetLineColor(funcColor);
//        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
//
//    }
//
//    cout << "Hej5" << endl;
//
//    c13->cd(2);
//    c13->cd(2)->SetLogy();
//    cout << "Hej51" << endl;
//
//
//    HistosKaon13[0] ->SetTitle( "" );
//    HistosKaon13[0] ->SetMinimum(MinForAll);
//    HistosKaon13[0]->GetXaxis()->SetTitle("");
//    HistosKaon13[0]->GetYaxis()->SetTitle("");
//    cout << "Hej52" << endl;
//
//
//    for (int i = 0 ; i < 10; i++){
//
//        HistosKaon13[i]->SetLineColor(Color[1]);
//        HistosKaon13[i]->Draw("sames");
//        cout << "Hej52 " << i << endl;
//
//
//        //funcsPion[i]->SetLineColor(funcColor);
//        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
//
//    }
//
//    cout << "Hej6" << endl;
//
//    c13->cd(3);
//    c13->cd(3)->SetLogy();
//
//    HistosProton13[0] ->SetTitle( "" );
//    HistosProton13[0] ->SetMinimum(MinForAll);
//    HistosProton13[0]->GetXaxis()->SetTitle("");
//    HistosProton13[0]->GetYaxis()->SetTitle("");
//
//    for (int i = 0 ; i < 10; i++){
//
//        HistosProton13[i]->SetLineColor(Color[2]);
//        HistosProton13[i]->Draw("sames");
//        //funcsPion[i]->SetLineColor(funcColor);
//        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
//
//    }
//
//
//    cout << "Hej7" << endl;
//
//
//    c13->SaveAs( "HEPDataFit13.eps" );
//
//
    


    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    auto legendH = new TLegend(0.7, 0.7, 0.9, 0.9); //(start from left, start from bottom ) //x1,y1,x2,y2
    legendH->SetHeader("Particles","C"); // option "C" allows to center the header
    legendH->AddEntry(HistosPion13[0], "#pi#pm","l");
    legendH->AddEntry(HistosKaon13[0], "K#pm","l");
    legendH->AddEntry(HistosProton13[0], "p(#bar{p})","l");

    legendH->Draw();
*/
    
    
    /*
    //h1->GetYaxis()->SetTitle("(dN/dp_{T}) /(dN_{MB}/dp_{T})");
     HistosPion7[0]->GetXaxis()->SetTitle("p_{T} (GeV/c)");

    HistosPion7[0]->GetYaxis()->SetTitleOffset(1.15);
    
    h1->GetYaxis()->SetTitleSize(0.04);

    h1->GetXaxis()->SetTitleSize(0.044);


    
    h1->Draw();
    //c -> Update();
    h2 -> SetLineColor(kRed);
    
    h2->Draw("same");
    gPad->Update();
    h1->SetStats(0);
*/
    

    
        
    //c->SaveAs("HEPData.root");
    
    
    
  
  

}



