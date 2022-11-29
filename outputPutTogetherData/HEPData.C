

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
    
    TFile* fileP7 = TFile::Open( "20.root" );
    
    if(!fileP7)
    return;
    
    HistosPion7[9] = (TH1D*)fileP7->Get( "20.root"  );

    
    
    
    int YKaon[9] = {21,22,23,24,25,26,27,28,29};
    
    
    TH1D **HistosKaon7;
    HistosKaon7 = new TH1D*[10];

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("%d.root", YKaon[i]  ));
        
        if(!file)
        return;
        
        HistosKaon7[i] = (TH1D*)file->Get(Form("%d.root", YKaon[i]  ));
        
    }
    

    TFile* fileK7 = TFile::Open( "30.root" );
    
    if(!fileK7)
    return;
    
    HistosKaon7[9] = (TH1D*)fileK7->Get( "30.root"  );


    
    
    
    
    
    
    int YProton[9] = {31,32,33,34,35,36,37,38,39};

    
    TH1D **HistosProton7;
    HistosProton7 = new TH1D*[10];

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("%d.root", YProton[i]  ));
        
        if(!file)
        return;
        
        HistosProton7[i] = (TH1D*)file->Get(Form("%d.root", YProton[i]  ));
        
    }
    
    TFile* filePr7 = TFile::Open( "40.root" );
    
    if(!filePr7)
    return;
    
    HistosProton7[9] = (TH1D*)filePr7->Get( "40.root"  );

    
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
    
    
    TFile* fileP13 = TFile::Open( "HEPData-ins1784041-v1-Table_2.rootHist1D_y1.root" );
    
    if(!fileP13)
    return;
    
    HistosPion13[9] = (TH1D*)fileP13->Get( "HEPData-ins1784041-v1-Table_2.rootHist1D_y1.root"  );

    
    

    
    
    
    
    
    
    TH1D **HistosKaon13;
    HistosKaon13 = new TH1D*[10];

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("HEPData-ins1784041-v1-Table_3.rootHist1D_y%d.root", Y[i]  ));
        
        if(!file)
        return;
        
        HistosKaon13[i] = (TH1D*)file->Get(Form("HEPData-ins1784041-v1-Table_3.rootHist1D_y%d.root", Y[i]  ));
        
    }
    
    
    TFile* fileK13 = TFile::Open( "HEPData-ins1784041-v1-Table_4.rootHist1D_y1.root" );
    
    if(!fileK13)
    return;
    
    HistosKaon13[9] = (TH1D*)fileK13->Get( "HEPData-ins1784041-v1-Table_4.rootHist1D_y1.root"  );

    

    
    
    
    

    
    TH1D **HistosProton13;
    HistosProton13 = new TH1D*[10];

    for (int i = 0; i <9; i++){
        
        TFile* file = TFile::Open(Form("HEPData-ins1784041-v1-Table_5.rootHist1D_y%d.root", Y[i]  ));
        
        if(!file)
        return;
        
        HistosProton13[i] = (TH1D*)file->Get(Form("HEPData-ins1784041-v1-Table_5.rootHist1D_y%d.root", Y[i]  ));
        
    }
    
    
    TFile* filePr13 = TFile::Open( "HEPData-ins1784041-v1-Table_6.rootHist1D_y1.root" );
    
    if(!filePr13)
    return;
    
    HistosProton13[9] = (TH1D*)filePr13->Get( "HEPData-ins1784041-v1-Table_6.rootHist1D_y1.root"  );


    
    
    
    
    
    
    
    
//################################################ "Printing" ################################################

    
    

    
    
    
    

    
    
    float MinForAll = 0.00000008;
    float ShiftFor7 = 0.00000007;
    
    
    int Color[3] = {4,632-2,2};
    int funcColor = 9;
    
    //Histos[i]->SetMaximum(5.1);
    //Histos[i]->SetMinimum(-1.1);

    cout << "Hej" << endl;

    
    TCanvas * c = new TCanvas();

    c-> Divide (3,2) ;
    
    
    c->cd(1);
    c->cd(1)->SetLogy();
    
    double TextXStart = 0.1;
    double TextYStart = 0.9;
    
    
//    TLatex *lName7 = new TLatex(TextXStart, TextYStart, "Row of data at #sqrt{s} = 7 TeV"  );


//    lName7->SetNDC();
//    lName7->SetTextSize(0.04);
//    lName7->Draw();
    
    gStyle->SetTitleSize(0.1,"t");

    
    Float_t SIZE = 0.05;

    
    HistosPion7[0] ->SetTitle( "" );
    
    HistosPion7[0] ->SetMinimum(MinForAll-ShiftFor7);
    HistosPion7[0]->GetYaxis()->SetTitle("#frac{1}{N_{events}}  #frac{d^{2} N}{dy dp_{T}}    ");
    HistosPion7[0]->GetXaxis()->SetTitle("");
    HistosPion7[0]->GetXaxis()->SetLabelSize(SIZE);
    HistosPion7[0]->GetYaxis()->SetLabelSize(SIZE);

    HistosPion7[0]->GetYaxis()->SetTitleSize(SIZE);
    
    HistosPion7[0]->GetYaxis()->SetTitleOffset(-9);
    

    
    for (int i = 0 ; i < 10; i++){
        
        HistosPion7[i]->SetLineColor(Color[0]);
        HistosPion7[i]->Draw("sames");
        //funcsPion[i]->SetLineColor(funcColor);
        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
            
    }
    
    cout << "Hej" << endl;

    c->cd(2);
    c->cd(2)->SetLogy();
    
    HistosKaon7[0] ->SetTitle( "Row of data at #sqrt{s} = 7 TeV" );
    HistosKaon7[0] ->SetMinimum(MinForAll-ShiftFor7);
    HistosKaon7[0]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    HistosKaon7[0]->GetYaxis()->SetTitle("");
    HistosKaon7[0]->GetXaxis()->SetLabelSize(SIZE);
    HistosKaon7[0]->GetYaxis()->SetLabelSize(SIZE);
    HistosKaon7[0]->GetXaxis()->SetTitleSize(SIZE);
    HistosKaon7[0]->GetYaxis()->SetTitleSize(SIZE);

    HistosKaon7[0]->GetXaxis()->SetTitleOffset(-0.5);


    
    for (int i = 0 ; i < 10; i++){
        
        HistosKaon7[i]->SetLineColor(Color[1]);
        HistosKaon7[i]->Draw("sames");
        //funcsPion[i]->SetLineColor(funcColor);
        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
            
    }
    cout << "Hej" << endl;

    
    c->cd(3);
    c->cd(3)->SetLogy();
    
    HistosProton7[0] ->SetTitle( "" );
    HistosProton7[0] ->SetMinimum(MinForAll-ShiftFor7);
    HistosProton7[0]->GetXaxis()->SetTitle("");
    HistosProton7[0]->GetYaxis()->SetTitle("");
    HistosProton7[0]->GetXaxis()->SetLabelSize(SIZE);
    HistosProton7[0]->GetYaxis()->SetLabelSize(SIZE);

    
    for (int i = 0 ; i < 10; i++){
        
        HistosProton7[i]->SetLineColor(Color[2]);
        HistosProton7[i]->Draw("sames");
        //funcsPion[i]->SetLineColor(funcColor);
        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
            
    }
    
    auto legendH = new TLegend(0.5, 0.55, 0.9, 0.9); //(start from left, start from bottom ) //x1,y1,x2,y2
    legendH->SetHeader("Particles","C"); // option "C" allows to center the header
    legendH->AddEntry(HistosPion7[0], "#pi#pm","l");
    legendH->AddEntry(HistosKaon7[0], "K#pm","l");
    legendH->AddEntry(HistosProton7[0], "p(#bar{p})","l");

    legendH->Draw();

    
    cout << "Hej4" << endl;
    
    //c7->SaveAs( "HEPDataFit7.eps" );

    
    
    
    //########################## "13 TeV Print" ##########################
    
    //TCanvas * c13 = new TCanvas();

    //c13-> Divide (3,1) ;

    
    c->cd(4);
    c->cd(4)->SetLogy();
    
    
//    TLatex *lName13 = new TLatex(TextXStart, TextYStart, "Row of data at #sqrt{s} = 13 TeV"  );
//
//
//    lName13->SetNDC();
//    lName13->SetTextSize(0.04);
//    lName13->Draw();
    
    
    
    HistosPion13[0] ->SetTitle( "" );
    HistosPion13[0] ->SetMinimum(MinForAll);
    HistosPion13[0]->GetXaxis()->SetTitle("");
    HistosPion13[0]->GetYaxis()->SetTitle("#frac{1}{N_{events}}  #frac{d^{2} N}{dy dp_{T}}    ");
    HistosPion13[0]->GetXaxis()->SetLabelSize(SIZE);
    HistosPion13[0]->GetYaxis()->SetLabelSize(SIZE);

    HistosPion13[0]->GetYaxis()->SetTitleSize(SIZE);
    
    HistosPion13[0]->GetYaxis()->SetTitleOffset(-9);

    
    for (int i = 0 ; i < 10; i++){
        
        HistosPion13[i]->SetLineColor(Color[0]);
        HistosPion13[i]->Draw("sames");
        //funcsPion[i]->SetLineColor(funcColor);
        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
            
    }
    
    cout << "Hej5" << endl;
    
    c->cd(5);
    c->cd(5)->SetLogy();
    cout << "Hej51" << endl;

    
    HistosKaon13[0] ->SetTitle( "Row of data at #sqrt{s} = 13 TeV" );
    HistosKaon13[0] ->SetMinimum(MinForAll);
    HistosKaon13[0]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    HistosKaon13[0]->GetYaxis()->SetTitle(" ");
    HistosKaon13[0]->GetXaxis()->SetLabelSize(SIZE);
    HistosKaon13[0]->GetYaxis()->SetLabelSize(SIZE);
    
    HistosKaon13[0]->GetXaxis()->SetTitleSize(SIZE);
    HistosKaon13[0]->GetYaxis()->SetTitleSize(SIZE);
    
    HistosKaon13[0]->GetXaxis()->SetTitleOffset(-0.5);
    


    cout << "Hej52" << endl;


    for (int i = 0 ; i < 10; i++){
        
        HistosKaon13[i]->SetLineColor(Color[1]);
        HistosKaon13[i]->Draw("sames");
        cout << "Hej52 " << i << endl;


        //funcsPion[i]->SetLineColor(funcColor);
        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
            
    }
    
    cout << "Hej6" << endl;
    
    c->cd(6);
    c->cd(6)->SetLogy();
    
    HistosProton13[0] ->SetTitle( "" );
    HistosProton13[0] ->SetMinimum(MinForAll);
    HistosProton13[0]->GetXaxis()->SetTitle("");
    HistosProton13[0]->GetYaxis()->SetTitle("");
    HistosProton13[0]->GetXaxis()->SetLabelSize(SIZE);
    HistosProton13[0]->GetYaxis()->SetLabelSize(SIZE);

    
    for (int i = 0 ; i < 10; i++){
        
        HistosProton13[i]->SetLineColor(Color[2]);
        HistosProton13[i]->Draw("sames");
        //funcsPion[i]->SetLineColor(funcColor);
        //HistosPion7[i]->GetListOfFunctions()->Add(funcsPion[i]);
            
    }

    
    cout << "Hej7" << endl;
    
    
    c->SaveAs( "HEPData.eps" );

    
    
    
    
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



