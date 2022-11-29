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





void AddingHistoTalker() {

    //gStyle->SetPadGridX("True");
    //gStyle->SetPadGridY("True");

    TH1D **HistosPion;
    HistosPion = new TH1D*[10];
    
    int Y[9] = {1,2,3,4,5,6,7,8,9};

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("HEPData-ins1784041-v1-Table_1.rootHist1D_y%d.root", Y[i]  ));
        
        if(!file)
        return;
        
        HistosPion[i] = (TH1D*)file->Get(Form("HEPData-ins1784041-v1-Table_1.rootHist1D_y%d.root", Y[i]  ));
        
    }
    
    
    TFile* fileP = TFile::Open( "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root" );
    
    if(!fileP)
    return;
    
    HistosPion[9] = (TH1D*)fileP->Get( "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root"  );

    
    
    AliPWGFunc * fm;
    fm = new AliPWGFunc;
    fm->SetVarType(AliPWGFunc::VarType_t(AliPWGFunc::kdNdpt));
    
    Double_t massPion = TDatabasePDG::Instance()->GetParticle("pi+")->Mass();
    
    TF1 **funcsPion;
    funcsPion = new TF1*[10];
    
    for (int i = 0; i <= 9 ; i++){
        
        cout << "Pion fit #" << i << endl;
        funcsPion[i] = fm->GetLevi(massPion, 0.4, 750,3);
        funcsPion[i]->SetRange(0.4, 10);
        HistosPion[i]->Fit(funcsPion[i],"","",0.4,10);
    }

    
    

    TH1D **HistosMBPion;
    HistosMBPion = new TH1D*[9];


    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 1, Y[i]  ));
        
        if(!file)
        return;
        
        HistosMBPion[i] = (TH1D*)file->Get(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 1, Y[i]  ));
        
    }

    
    
    
    
    
    TH1D **HistosKaon;
    HistosKaon = new TH1D*[9];

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("HEPData-ins1784041-v1-Table_3.rootHist1D_y%d.root", Y[i]  ));
        
        if(!file)
        return;
        
        HistosKaon[i] = (TH1D*)file->Get(Form("HEPData-ins1784041-v1-Table_3.rootHist1D_y%d.root", Y[i]  ));
        
    }
    
    TFile* fileK = TFile::Open( "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root" );
    
    if(!fileK)
    return;
    
    HistosKaon[9] = (TH1D*)fileK->Get( "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root"  );

    

    Double_t massKaon = TDatabasePDG::Instance()->GetParticle("K+")->Mass();
    
    TF1 **funcsKaon;
    funcsKaon = new TF1*[10];
    
    for (int i = 0; i <= 9 ; i++){
        
        cout << "Kaon fit #" << i << endl;
        funcsKaon[i] = fm->GetLevi(massKaon, 0.4, 750,3);
        funcsKaon[i]->SetRange(0.4, 10);
        HistosKaon[i]->Fit(funcsKaon[i],"","",0.4,10);
    
    }
    
    
    
    TH1D **HistosMBKaon;
    HistosMBKaon = new TH1D*[9];


    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 3, Y[i]  ));
        
        if(!file)
        return;
        
        HistosMBKaon[i] = (TH1D*)file->Get(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 3, Y[i]  ));
        
    }
    
    
    
    
    
    
    
    
    

    
    TH1D **HistosProton;
    HistosProton = new TH1D*[10];

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("HEPData-ins1784041-v1-Table_5.rootHist1D_y%d.root", Y[i]  ));
        
        if(!file)
        return;
        
        HistosProton[i] = (TH1D*)file->Get(Form("HEPData-ins1784041-v1-Table_5.rootHist1D_y%d.root", Y[i]  ));
        
    }
    
    TFile* filePr = TFile::Open( "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root" );
    
    if(!filePr)
    return;
    
    HistosProton[9] = (TH1D*)filePr->Get( "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root"  );

    

    Double_t massProton = TDatabasePDG::Instance()->GetParticle("proton")->Mass();
    
    TF1 **funcsProton;
    funcsProton = new TF1*[10];
    
    for (int i = 0; i <= 9 ; i++){
        
        cout << "Proton fit #" << i << endl;
        funcsProton[i] = fm->GetLevi(massProton, 0.4, 750,3);
        funcsProton[i]->SetRange(0.4, 10);
        HistosProton[i]->Fit(funcsProton[i],"","",0.4,10);
    }
    
    
    TH1D **HistosMBProton;
    HistosMBProton = new TH1D*[9];


    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 5, Y[i]  ));
        
        if(!file)
        return;
        
        HistosMBProton[i] = (TH1D*)file->Get(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", 5, Y[i]  ));
        
    }

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    TCanvas * c = new TCanvas();

    c->SetLogy();
    
    

    int Color[3] = {1,4,2};
    int funcColor = 9;
    

    cout << "Hej" << endl;
    for (int i = 0 ; i < 10; i++){
        
        HistosPion[i]->SetLineColor(Color[0]);
        HistosPion[i]->Draw("sames");
        

        HistosKaon[i]->SetLineColor(Color[1]);
        HistosKaon[i]->Draw("sames");
        
        
        HistosProton[i]->SetLineColor(Color[2]);
        HistosProton[i]->Draw("sames");
   
    }
    

    HistosPion[0] ->SetTitle( "Particle data from HEPData" );
    
    HistosPion[0] ->SetMinimum(0.00000008);
    HistosPion[0]->GetXaxis()->SetTitle("p_{T} (GeV/c)");

    auto legendH = new TLegend(0.7, 0.7, 0.9, 0.9); //(start from left, start from bottom ) //x1,y1,x2,y2
    legendH->SetHeader("Particles","C"); // option "C" allows to center the header
    legendH->AddEntry(HistosPion[0], "#pi#pm","l");
    legendH->AddEntry(HistosKaon[0], "K#pm","l");
    legendH->AddEntry(HistosProton[0], "p(#bar{p})","l");

    legendH->Draw();

    
    //c->SaveAs( "HEPDataFit13TeV.eps" );

    
    
    
    
    
    
    
    
    TCanvas * cPion = new TCanvas();

    cPion->SetLogy();
    
    for (int i = 0 ; i < 10; i++){
        
        HistosPion[i]->SetLineColor(Color[0]);
        HistosPion[i]->Draw("sames");

        
    }

    HistosPion[0] ->SetTitle( "Particle data from HEPData, #pi#pm" );
    
    HistosPion[0] ->SetMinimum(0.00000008);
    HistosPion[0]->GetXaxis()->SetTitle("p_{T} (GeV/c)");

    //cPion->SaveAs( "HEPDataPionFit13TeV.eps" );
    
    
    TCanvas * cKaon = new TCanvas();

    cKaon->SetLogy();
    
    for (int i = 0 ; i < 10; i++){
        
        HistosKaon[i]->SetLineColor(Color[1]);
        HistosKaon[i]->Draw("sames");

    }

    HistosKaon[0] ->SetTitle( "Particle data from HEPData, K#pm" );
    
    HistosKaon[0] ->SetMinimum(0.00000008);
    HistosKaon[0] ->GetXaxis()->SetTitle("p_{T} (GeV/c)");

    //cKaon->SaveAs( "HEPDataKaonFit13TeV.eps" );

    
    TCanvas * cProton = new TCanvas();

    cProton->SetLogy();
    
    for (int i = 0 ; i < 10; i++){
        
        HistosProton[i]->SetLineColor(Color[2]);
        HistosProton[i]->Draw("sames");
        
    }

    HistosProton[0] ->SetTitle( "Particle data from HEPData, p(#bar{p})" );
    
    HistosProton[0] ->SetMinimum(0.00000008);
    HistosProton[0] ->GetXaxis()->SetTitle("p_{T} (GeV/c)");

    //cProton->SaveAs( "HEPDataProtonFit13TeV.eps" );

    
    
    
    
    
    
    
    
    
    int LogYOnOff = 0;
    
    TCanvas * cDivPion = new TCanvas();
    if(LogYOnOff ==1) cDivPion ->SetLogy();

    
    
    TF1 **funcsPionDiv;
    funcsPionDiv = new TF1*[9];
    
    
    for (int i = 0; i < 9 ; i++){
        
        funcsPionDiv[i] = new TF1("f",FuncDiver,0.4,10,7);
        funcsPionDiv[i] ->SetParNames(Form("Norm%d", i), Form("n%d", i), Form("temp%d", i), "mass", Form("NormMB%d", i), Form("nMB%d", i), Form("tempMB%d", i));
        funcsPionDiv[i] ->SetParameter(0, funcsPion[i]->GetParameter(0) );
        funcsPionDiv[i] ->SetParameter(1, funcsPion[i]->GetParameter(1) );
        funcsPionDiv[i] ->SetParameter(2, funcsPion[i]->GetParameter(2) );
        funcsPionDiv[i] ->SetParameter(3, massPion );
        
        funcsPionDiv[i] ->SetParameter(4, funcsPion[9]->GetParameter(0) );
        funcsPionDiv[i] ->SetParameter(5, funcsPion[9]->GetParameter(1) );
        funcsPionDiv[i] ->SetParameter(6, funcsPion[9]->GetParameter(2) );
    
        
        HistosMBPion[i]->GetListOfFunctions()->Add(funcsPionDiv[i]);
        HistosMBPion[i]-> GetXaxis() -> SetRangeUser(0, 10);
        HistosMBPion[i]->Draw("sames");

        
        HistosMBPion[i]->SetTitle( "Levi fits for each multiplicity divided by Levi fit for min bias at #sqrt{s} = 13 TeV for #pi#pm" );

        HistosMBPion[i]-> GetYaxis()->SetTitle("(dN/dp_{T}) /(dN_{MB}/dp_{T})");

        HistosMBPion[i]-> GetXaxis()->SetTitle("p_{T} (GeV/c)");
        
        
    }
    
    cDivPion->SaveAs( "HEPDataPionFitDiv13TeV.eps" );
    
    
    
    TCanvas * cN1Pion = new TCanvas();
    
    
    TH1D* hN1Pion = new TH1D( "Div" , "The n1-value for each multiplicity", 9, -0.5, 8.5)    ;
    
    
    for (int i = 0; i < 9 ; i++){
        
        hN1Pion ->SetBinContent(i+1, funcsPion[i]->GetParameter(1) );
        hN1Pion ->SetBinError(i+1, funcsPion[i]->GetParError(1) );
                
    }
    
    hN1Pion->Draw();

    gPad->Update();
    hN1Pion->SetStats(0);

    cN1Pion->SaveAs( "HEPDataPionN113TeV.eps" );

    hN1Pion->SaveAs( "HEPDataN11.root" );

    
    
    TCanvas * cN12Pion = new TCanvas();
    
    
    TH1D* hN12Pion = new TH1D( "Div" , "The (n2-n1)-value for each multiplicity", 9, -0.5, 8.5)    ;
    
    
    for (int i = 0; i < 9 ; i++){
        
        hN12Pion ->SetBinContent(i+1, funcsPion[9]->GetParameter(1) - funcsPion[i]->GetParameter(1) );
        hN12Pion ->SetBinError(i+1, funcsPion[9]->GetParError(1) - funcsPion[i]->GetParError(1) );
                
    }
    
    hN12Pion->Draw();

    gPad->Update();
    hN12Pion->SetStats(0);

    cN12Pion->SaveAs( "HEPDataPionN1213TeV.eps" );

    hN12Pion->SaveAs( "HEPDataN121.root" );

    
    
    
    
    TH1F* Ck1 = new TH1F( "The_constant_k" , "The constant k-value over mass", 2, 0, 1)    ;

    Ck1 ->SetBinContent(1, funcsPion[9]->GetParameter(1) );
    Ck1 ->SetBinError(1, funcsPion[9]->GetParError(1) );
    
    Ck1 -> SaveAs(Form( "CN2%d.root", 1));

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    TCanvas * cDivKaon = new TCanvas();
    if(LogYOnOff ==1) cDivKaon ->SetLogy();
    
        
    TF1 **funcsKaonDiv;
    funcsKaonDiv = new TF1*[9];
    
    
    for (int i = 0; i < 9 ; i++){
        
        funcsKaonDiv[i] = new TF1("f",FuncDiver,0.4,10,7);
        funcsKaonDiv[i] ->SetParNames(Form("Norm%d", i), Form("n%d", i), Form("temp%d", i), "mass", Form("NormMB%d", i), Form("nMB%d", i), Form("tempMB%d", i));
        funcsKaonDiv[i] ->SetParameter(0, funcsKaon[i]->GetParameter(0) );
        funcsKaonDiv[i] ->SetParameter(1, funcsKaon[i]->GetParameter(1) );
        funcsKaonDiv[i] ->SetParameter(2, funcsKaon[i]->GetParameter(2) );
        funcsKaonDiv[i] ->SetParameter(3, massKaon );
        
        funcsKaonDiv[i] ->SetParameter(4, funcsKaon[9]->GetParameter(0) );
        funcsKaonDiv[i] ->SetParameter(5, funcsKaon[9]->GetParameter(1) );
        funcsKaonDiv[i] ->SetParameter(6, funcsKaon[9]->GetParameter(2) );
    
                
        HistosMBKaon[i]->GetListOfFunctions()->Add(funcsKaonDiv[i]);
        HistosMBKaon[i]-> GetXaxis() -> SetRangeUser(0, 10);
        HistosMBKaon[i]->Draw("sames");

        HistosMBKaon[i]->SetTitle( "Levi fits for each multiplicity divided by Levi fit for min bias at #sqrt{s} = 13 TeV for K#pm" );

        HistosMBKaon[i]-> GetYaxis()->SetTitle("(dN/dp_{T}) /(dN_{MB}/dp_{T})");

        HistosMBKaon[i]-> GetXaxis()->SetTitle("p_{T} (GeV/c)");
        
        //hDivKaon->Draw("sames");
        
    }
    
    cDivKaon->SaveAs( "HEPDataKaonFitDiv13TeV.eps" );
    
    
    
    TCanvas * cN1Kaon = new TCanvas();
    
    
    TH1D* hN1Kaon = new TH1D( "Div" , "The n1-value for each multiplicity", 9, -0.5, 8.5)    ;
    
    
    for (int i = 0; i < 9 ; i++){
        
        hN1Kaon ->SetBinContent(i+1, funcsKaon[i]->GetParameter(1) );
        hN1Kaon ->SetBinError(i+1, funcsKaon[i]->GetParError(1) );
                
    }
    
    hN1Kaon->Draw();

    gPad->Update();
    hN1Kaon->SetStats(0);

    cN1Kaon->SaveAs( "HEPDataKaonN113TeV.eps" );

    hN1Kaon->SaveAs( "HEPDataN13.root" );
    
    
    
    
    
    TCanvas * cN12Kaon = new TCanvas();
    
    
    TH1D* hN12Kaon = new TH1D( "Div" , "The (n2-n1)-value for each multiplicity", 9, -0.5, 8.5)    ;
    
    
    for (int i = 0; i < 9 ; i++){
        
        hN12Kaon ->SetBinContent(i+1, funcsKaon[9]->GetParameter(1) - funcsKaon[i]->GetParameter(1) );
        hN12Kaon ->SetBinError(i+1, funcsKaon[9]->GetParError(1) - funcsKaon[i]->GetParError(1) );
                
    }
    
    hN12Kaon->Draw();

    gPad->Update();
    hN12Kaon->SetStats(0);

    cN12Kaon->SaveAs( "HEPDataKaonN1213TeV.eps" );

    hN12Kaon->SaveAs( "HEPDataN123.root" );
    
    
    
    
    
    
    TH1F* Ck3 = new TH1F( "The_constant_k" , "The constant n2-value", 2, 0, 1)    ;

    Ck3 ->SetBinContent(1, funcsKaon[9]->GetParameter(1) );
    Ck3 ->SetBinError(1, funcsKaon[9]->GetParError(1) );
    
    Ck3 -> SaveAs(Form( "CN2%d.root", 3));

    
    
    
    
    
    
    
    
    

    
    
    
    
    TCanvas * cDivProton = new TCanvas();
    
    if(LogYOnOff ==1)  cDivProton->SetLogy();
    
    
    TF1 **funcsProtonDiv;
    funcsProtonDiv = new TF1*[9];
    
    
    for (int i = 0; i < 9 ; i++){
        
        funcsProtonDiv[i] = new TF1("f",FuncDiver,0.4,10,7);
        funcsProtonDiv[i] ->SetParNames(Form("Norm%d", i), Form("n%d", i), Form("temp%d", i), "mass", Form("NormMB%d", i), Form("nMB%d", i), Form("tempMB%d", i));
        funcsProtonDiv[i] ->SetParameter(0, funcsProton[i]->GetParameter(0) );
        funcsProtonDiv[i] ->SetParameter(1, funcsProton[i]->GetParameter(1) );
        funcsProtonDiv[i] ->SetParameter(2, funcsProton[i]->GetParameter(2) );
        funcsProtonDiv[i] ->SetParameter(3, massProton );
        
        funcsProtonDiv[i] ->SetParameter(4, funcsProton[9]->GetParameter(0) );
        funcsProtonDiv[i] ->SetParameter(5, funcsProton[9]->GetParameter(1) );
        funcsProtonDiv[i] ->SetParameter(6, funcsProton[9]->GetParameter(2) );
    
        
        
        HistosMBProton[i]->GetListOfFunctions()->Add(funcsProtonDiv[i]);
        HistosMBProton[i]-> GetXaxis() -> SetRangeUser(0, 10);
        HistosMBProton[i]->Draw("sames");

        HistosMBProton[i]->SetTitle( "Levi fits for each multiplicity divided by Levi fit for min bias at #sqrt{s} = 13 TeV for protons" );

        HistosMBProton[i]-> GetYaxis()->SetTitle("(dN/dp_{T}) /(dN_{MB}/dp_{T})");

        HistosMBProton[i]-> GetXaxis()->SetTitle("p_{T} (GeV/c)");
        
        //hDivProton->Draw("sames");
        
    }
    
    cDivProton->SaveAs( "HEPDataProtonFitDiv13TeV.eps" );
    
    
    
    
    
    TCanvas * cN1Proton = new TCanvas();
    
    
    TH1D* hN1Proton = new TH1D( "Div" , "The n1-value for each multiplicity", 9, -0.5, 8.5)    ;
    
    
    for (int i = 0; i < 9 ; i++){
        
        hN1Proton ->SetBinContent(i+1, funcsProton[i]->GetParameter(1) );
        hN1Proton ->SetBinError(i+1, funcsProton[i]->GetParError(1) );
                
    }
    
    hN1Proton->Draw();

    gPad->Update();
    hN1Proton->SetStats(0);

    cN1Proton->SaveAs( "HEPDataProtonN113TeV.eps" );

    hN1Proton->SaveAs( "HEPDataN15.root" );
    
    
    
    
    
    TCanvas * cN12Proton = new TCanvas();
    
    
    TH1D* hN12Proton = new TH1D( "Div" , "The (n2-n1)-value for each multiplicity", 9, -0.5, 8.5)    ;
    
    
    for (int i = 0; i < 9 ; i++){
        
        hN12Proton ->SetBinContent(i+1, funcsProton[9]->GetParameter(1) - funcsProton[i]->GetParameter(1) );
        hN12Proton ->SetBinError(i+1, funcsProton[9]->GetParError(1) - funcsProton[i]->GetParError(1) );
                
    }
    
    hN12Proton->Draw();

    gPad->Update();
    hN12Proton->SetStats(0);

    cN12Proton->SaveAs( "HEPDataProtonN1213TeV.eps" );

    hN12Proton->SaveAs( "HEPDataN125.root" );
    
    
    
    
    
    
    TH1F* Ck5 = new TH1F( "The_constant_k" , "The constant n2-value", 2, 0, 1)    ;

    Ck5 ->SetBinContent(1, funcsProton[9]->GetParameter(1) );
    Ck5 ->SetBinError(1, funcsProton[9]->GetParError(1) );
    
    Ck5 -> SaveAs(Form( "CN2%d.root", 5));
    
    
}



void AddingHistos(){
    
    // The cout << "Hej" << endl; are just to check where an error has occurred

    
    cout << "Hej" << endl;

    
    //gStyle->SetPadGridX("False");
    //gStyle->SetPadGridY("False");
    gROOT->ForceStyle();


    int Table[3] = {1,3,5};
    
    
    TH1D **HistosCH;
    HistosCH = new TH1D*[3];

    TH1D **HistosCS;
    HistosCS = new TH1D*[3];
    
    TH1D **HistosCk;
    HistosCk = new TH1D*[3];

    
    for (int i = 0; i <3; i++){
        
        //Files with n1
        TFile* fileCH = TFile::Open(Form("HEPDataN1%d.root", Table[i]  ));
        HistosCH[i] = (TH1D*)fileCH->Get("Div");
        
        
        //Files with n2 -n1
        TFile* fileCS = TFile::Open(Form("HEPDataN12%d.root", Table[i]  ));
        HistosCS[i] = (TH1D*)fileCS->Get("Div");
        
        
        //Files with n2
        TFile* fileCk = TFile::Open(Form("CN2%d.root", Table[i]  ));
        HistosCk[i] = (TH1D*)fileCk->Get("The_constant_k");
        

        
        if(!fileCH)
        return;
        if(!fileCS)
        return;
        if(!fileCk)
        return;


        

    }
    cout << "Hej" << endl;

    
    double MassesGeV[3] = {0.1396, 0.4937, 0.9383}; //{pion#pm, kaon#pm, proton}
    
    TH1D* hCk = new TH1D( "Theconstantk" , "The n2-values over their particles mass at #sqrt{s} = 13 TeV", 3, 0.5, 2.5)    ;

    cout << "Hej" << endl;

    
    for (int i = 0 ; i < 3; i++){

        hCk ->SetBinContent(i+1, HistosCk[i]->GetBinContent(1) /MassesGeV[i] );
        hCk ->SetBinError(i+1, HistosCk[i]->GetBinError(1) /MassesGeV[i] );
    }
    
    hCk ->GetXaxis() ->SetBinLabel(1, "#pi#pm");
    hCk ->GetXaxis() ->SetBinLabel(2, "K#pm");
    hCk ->GetXaxis() ->SetBinLabel(3, "p(#bar{p})");

    hCk ->GetXaxis() ->SetLabelSize(0.1);
    
    
    TH1D* hCk1 = new TH1D( "Theconstantk" , "The n2-value", 3, 0.5, 2.5)    ;
    
    for (int i = 0 ; i < 3; i++){
        hCk1 ->SetBinContent(i+1, HistosCk[i]->GetBinContent(1) );
        hCk1 ->SetBinError(i+1, HistosCk[i]->GetBinError(1) );
        
    }
    
    
    cout << "Hej" << endl;

    TCanvas *cCk = new TCanvas("cCk", "The constant k-value over each particles mass");
    
    hCk->SetMaximum( 51 );
    hCk->SetMinimum( 7);

    hCk->Draw("sames");
    hCk->SetStats(0);

    hCk ->GetYaxis()->SetTitle("n2-value/mass (1/GeV)");

    
    cCk -> SaveAs("cN213TeV.eps");
    cout << "Hej" << endl;
    
        

    int Color[3] = {4,632-2,2};
    
    TCanvas *cCH = new TCanvas("cN1", "n1-values for each multiplicity");
    cout << "Hej" << endl;

    int MAXMIN = 120;
    
    for (int i = 0 ; i < 3; i++){
        
        //Histos[i]->SetMaximum(5.1);
        //Histos[i]->SetMinimum(-1.1);

        //For best fit
        
        HistosCH[i]->SetMaximum( ((HistosCH[2]-> GetBinContent(1)) + (HistosCH[2]-> GetBinError(1)))*(1.05) );
        HistosCH[i]->SetMinimum(  ( (HistosCH[0]-> GetBinContent( HistosCH[0]-> GetNbinsX() ) ) - (HistosCH[0]-> GetBinError( HistosCH[0]-> GetNbinsX())) ) *(0.95) );
        
        HistosCH[i] ->SetLineWidth(1);
        HistosCH[i]->SetLineColor( Color[i] );
        HistosCH[i]->Draw("sames");
        HistosCH[i]->SetStats(0);
        
        HistosCH[i]->SetTitle( "n1-values for each multiplicity at #sqrt{s} = 13 TeV" );

        
        //HistosCk[i]->Draw("sames");
    }
    
    auto legendH = new TLegend(0.65, 0.65, 0.9, 0.9); //(start from left, start from bottom ) //x1,y1,x2,y2
    legendH->SetHeader("Particles","C"); // option "C" allows to center the header
    legendH->AddEntry(HistosCH[0], "#pi#pm","l");
    legendH->AddEntry(HistosCH[1], "K#pm","l");
    legendH->AddEntry(HistosCH[2], "p(#bar{p})","l");

    legendH->Draw();
    
    
    TLatex *lkNameleft = new TLatex(0.1, 0.025, Form("#color[1]{%s}", "High multiplicity" ) );


    lkNameleft->SetNDC();
    lkNameleft->SetTextSize(0.03);
    lkNameleft->Draw();
    
    TLatex *lkNameright = new TLatex(0.75, 0.025, Form("#color[1]{%s}", "Low multiplicity" ) );


    lkNameright->SetNDC();
    lkNameright->SetTextSize(0.03);
    lkNameright->Draw();

    
     
    cCH -> SaveAs("cN113TeV.eps");
    
    
    
    
    
    TCanvas *cCS = new TCanvas("cN12", "(n2-n1)-values for each multiplicity");
    cout << "Hej" << endl;

    
    for (int i = 0 ; i < 3; i++){
        
        HistosCS[i]->SetMaximum( ((HistosCS[2]-> GetBinContent( HistosCS[2]-> GetNbinsX())) + (HistosCS[2]-> GetBinError( HistosCS[2]-> GetNbinsX())))*(1.05) );
        HistosCS[i]->SetMinimum( ((HistosCS[2]-> GetBinContent(1)) - (HistosCS[2]-> GetBinError(1)))*(1.05)   );


        HistosCS[i] ->SetLineWidth(1);
        HistosCS[i]->SetLineColor( Color[i] );
        HistosCS[i]->Draw("sames");
        HistosCS[i]->SetStats(0);
        
        HistosCS[i]->SetTitle( "(n2-n1)-values for each multiplicity at #sqrt{s} = 13 TeV" );

        
    }
    
    
    
    auto legendS = new TLegend(0.65, 0.15, 0.9, 0.4); //(start from left, start from bottom ) //x1,y1,x2,y2
    legendS->SetHeader("Particles","C"); // option "C" allows to center the header
    legendS->AddEntry(HistosCS[0], "#pi#pm","l");
    legendS->AddEntry(HistosCS[1], "K#pm","l");
    legendS->AddEntry(HistosCS[2], "p(#bar{p})","l");

    legendS->Draw();

    TLatex *lkNameleft2 = new TLatex(0.1, 0.025, Form("#color[1]{%s}", "High multiplicity" ) );


    lkNameleft2->SetNDC();
    lkNameleft2->SetTextSize(0.03);
    lkNameleft2->Draw();
    
    TLatex *lkNameright2 = new TLatex(0.75, 0.025, Form("#color[1]{%s}", "Low multiplicity" ) );


    lkNameright2->SetNDC();
    lkNameright2->SetTextSize(0.03);
    lkNameright2->Draw();


    cCS -> SaveAs("cN1213TeV.eps");

    

    
    
}
















