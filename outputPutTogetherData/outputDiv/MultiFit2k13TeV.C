#include <Fit/Fitter.h>
#include <Fit/BinData.h>
#include <Fit/Chi2FCN.h>
#include <TH1.h>
#include <Math/WrappedMultiTF1.h>
#include <HFitInterface.h>
#include <TCanvas.h>
#include <TStyle.h>
 
#include <math.h>
#include <TMath.h>
#include <TFile.h>
#include <TF1.h>

#include <string>

#include <TLatex.h>
#include <TText.h>
#include <TPaveStats.h>
#include <TList.h>

#include <TROOT.h>

#include <Math/WrappedFunction.h>

#include <TLegend.h>



//NMax= 10 for all with NMin = 0
const int NMax = 9;
//NMin = 0; starts at the first histogram
const int NMin = 0;

const int Npar = 1 + 2*(NMax-NMin);



struct GlobalChi2 {GlobalChi2(
    ROOT::Math::IMultiGenFunction &f1, ROOT::Math::IMultiGenFunction &f2, ROOT::Math::IMultiGenFunction &f3, ROOT::Math::IMultiGenFunction &f4, ROOT::Math::IMultiGenFunction &f5, ROOT::Math::IMultiGenFunction &f6, ROOT::Math::IMultiGenFunction &f7, ROOT::Math::IMultiGenFunction &f8, ROOT::Math::IMultiGenFunction &f9) : fChi2_1(&f1), fChi2_2(&f2), fChi2_3(&f3), fChi2_4(&f4), fChi2_5(&f5), fChi2_6(&f6), fChi2_7(&f7), fChi2_8(&f8), fChi2_9(&f9) {}
    


    double operator()(const double *par) const
    {
        int ipar[NMax-NMin][3] = {{0,1,20},{2,3,20}, {4,5,20},{6,7,20},{8,9,20},   {10,11,20},{12,13,20},{14,15,20} } ;

        for (int i = 0; i < Npar-2; i = i + 2){
            
            ipar[i/2][0] = i;
            ipar[i/2][1] = i +1;
            ipar[i/2][2] = Npar-1;
          
        };
        
        double p[NMax-NMin][3] = {{0,0,0},{0,0,0}, {0,0,0},{0,0,0},{0,0,0},   {0,0,0},{0,0,0},{0,0,0} } ;
        
        for (int i = 0; i < (NMax - NMin); i++){
            
            p[i][0] = par[ipar[i][0]] ;
            p[i][1] = par[ipar[i][1]] ;
            p[i][2] = par[ipar[i][2]] ;

        };
        
        
        return  (*fChi2_1)( p[0] ) + (*fChi2_2)(p[1]) + (*fChi2_3)(p[2]) + (*fChi2_4)(p[3]) + (*fChi2_5)(p[4]) + (*fChi2_6)(p[5]) +(*fChi2_7)(p[6]) + (*fChi2_8)(p[7]) + (*fChi2_9)(p[8]);
        
        
    };
 
    const ROOT::Math::IMultiGenFunction *fChi2_1;
    const ROOT::Math::IMultiGenFunction *fChi2_2;
    const ROOT::Math::IMultiGenFunction *fChi2_3;
    const ROOT::Math::IMultiGenFunction *fChi2_4;
    const ROOT::Math::IMultiGenFunction *fChi2_5;
    const ROOT::Math::IMultiGenFunction *fChi2_6;
    const ROOT::Math::IMultiGenFunction *fChi2_7;
    const ROOT::Math::IMultiGenFunction *fChi2_8;
    const ROOT::Math::IMultiGenFunction *fChi2_9;
   
};



Double_t Funcer(Double_t *x, Double_t *p)
{
    Double_t pt = x[0];
    Double_t ConstHard = p[0];
    Double_t ConstSoft = p[1];
    Double_t k1 = p[2];
    //Double_t k2 = p[3];
    
    //Max limits
    if(pt>10.) ConstSoft = 0;
    if(pt>10.) ConstHard = 0;
    
    //Min limits
    if(pt<0.4) ConstSoft = 0;
    if(pt<0.4) ConstHard = 0;
    

    //Double_t ftot = ConstHard + ConstSoft* TMath::Exp(k/pt); //First try
    Double_t ftot = ConstHard + ConstSoft* TMath::Exp(k1/pt); //Second try
   // Double_t ftot = ConstHard + ConstSoft* TMath::Power(pt, TMath::Power(k1,k2));
    
    //Double_t ftot = ConstHard + ConstSoft* TMath::Exp( - TMath::Power(pt,k)  ); Third try
    
    //Double_t ftot = ConstHard + ConstSoft* TMath::Exp( - (TMath::Power(pt,k1))/k2  );
    
    return ftot;
    
}




 
void combinedFit(Int_t Table = 1 )
{
    

    gStyle->SetPadGridX("False");
    gStyle->SetPadGridY("False");


    int Y[9] = {1,2,3,4,5,6,7,8,9};
    

    TH1D **Histos;
    Histos = new TH1D*[NMax-NMin];


    for (int i = NMin; i <NMax; i++){
        
        TFile* file = TFile::Open(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", Table, Y[i]  ));
        
        if(!file)
        return;
        
        Histos[i-NMin] = (TH1D*)file->Get(Form("DivHEPData-ins1784041-v1-Table_%d.rootHist1D_y%d.root.root", Table, Y[i]  ));
        
    }
    

    TF1 **funcs;
    funcs = new TF1*[NMax-NMin];

    
    for (int i = 0; i < (NMax - NMin) ; i++){
        
        funcs[i] = new TF1("f",Funcer,0.4,10,3);
        funcs[i] ->SetParNames(Form("Hard%d", i), Form("Soft%d", i), "k1");
        
    }


    ROOT::Fit::DataOptions opt;
    
    ROOT::Fit::DataRange range[NMax-NMin];
    ROOT::Fit::BinData data[NMax-NMin];
   
    for (int i = 0; i < (NMax - NMin) ; i++){
        range[i].SetRange(0.4, 10);
        data[i] = ROOT::Fit::BinData (opt, range[i]);
        ROOT::Fit::FillData(data[i], Histos[i]);
    }
    
    ROOT::Fit::Chi2Function chi2_1(data[0], ROOT::Math::WrappedMultiTF1 (*funcs[0], 0));
    ROOT::Fit::Chi2Function chi2_2(data[1], ROOT::Math::WrappedMultiTF1 (*funcs[1], 0));
    ROOT::Fit::Chi2Function chi2_3(data[2], ROOT::Math::WrappedMultiTF1 (*funcs[2], 0));
    ROOT::Fit::Chi2Function chi2_4(data[3], ROOT::Math::WrappedMultiTF1 (*funcs[3], 0));
    ROOT::Fit::Chi2Function chi2_5(data[4], ROOT::Math::WrappedMultiTF1 (*funcs[4], 0));
    ROOT::Fit::Chi2Function chi2_6(data[5], ROOT::Math::WrappedMultiTF1 (*funcs[5], 0));
    ROOT::Fit::Chi2Function chi2_7(data[6], ROOT::Math::WrappedMultiTF1 (*funcs[6], 0));
    ROOT::Fit::Chi2Function chi2_8(data[7], ROOT::Math::WrappedMultiTF1 (*funcs[7], 0));
    ROOT::Fit::Chi2Function chi2_9(data[8], ROOT::Math::WrappedMultiTF1 (*funcs[8], 0));
    GlobalChi2 globalChi2(chi2_1, chi2_2, chi2_3, chi2_4, chi2_5, chi2_6, chi2_7, chi2_8, chi2_9);

    
    
    ROOT::Fit::Fitter fitter;
    

    double par0[Npar];

    fitter.Config().SetParamsSettings(Npar, par0);
    
//    fitter.Config().ParSettings(Npar-1).SetValue(1);
//    fitter.Config().ParSettings(Npar-1).Fix();
    //fitter.Config().ParSettings(Npar-2).SetLimits(0.5, 1);
    
    //fitter.Config().ParSettings(Npar-2).SetLimits(0.0004, 0.015);

    //fitter.Config().ParSettings(Npar).SetLimits(5, 100);
    
    //fitter.Config().ParSettings(Npar-1).SetLimits(0.005, 0.1);
    
    
//    if(Table == 1){
//        //fitter.Config().ParSettings(Npar-1).SetLimits(0.0062, 0.0063 );
//        fitter.Config().ParSettings(Npar-1).SetLimits(0.005, 0.01 );
//    }
//
//    if(Table == 3){
//        //fitter.Config().ParSettings(Npar-1).SetLimits(0.0076, 0.0077);
//        fitter.Config().ParSettings(Npar-1).SetLimits(0.005, 0.01);
//
//    }
//
//    if(Table == 5){
//        //fitter.Config().ParSettings(Npar-1).SetLimits(0.0082, 0.0083);
//        fitter.Config().ParSettings(Npar-1).SetLimits(0.005, 0.01);
//
//    }

    if(Table == 1){
        fitter.Config().ParSettings(Npar-1).SetLimits(0.00620634 - 0.00294569, 0.00620634 + 0.00294569);

    }

    if(Table == 3){
        fitter.Config().ParSettings(Npar-1).SetLimits(0.00764789 - 0.00295299, 0.00764789 + 0.00295299);


    }

    if(Table == 5){
        fitter.Config().ParSettings(Npar-1).SetLimits(0.00827862 - 0.00126328, 0.00827862 + 0.00126328);

    }

    
    
//    if(Table == 1){
//        fitter.Config().ParSettings(Npar-1).SetValue(0.00620634);
//        fitter.Config().ParSettings(Npar-1).Fix();
//
//    }
//
//    if(Table == 3){
//        fitter.Config().ParSettings(Npar-1).SetValue(0.00764789);
//        fitter.Config().ParSettings(Npar-1).Fix();
//
//    }
//
//    if(Table == 5){
//        fitter.Config().ParSettings(Npar-1).SetValue(0.00827862);
//        fitter.Config().ParSettings(Npar-1).Fix();
//
//    }

    
    
    fitter.Config().MinimizerOptions().SetPrintLevel(0);
    fitter.Config().SetMinimizer("Minuit2", "Migrad");

    
    
    fitter.FitFCN( Npar, globalChi2, 0, (NMax-NMin)*data[0].Size()  , true);
    
        
    ROOT::Fit::FitResult result = fitter.Result();
    
    result.Print(std::cout);
    

    TCanvas *c1 = new TCanvas("Simfit", "Simultaneous fit of two histograms");

    
    TF1 **funcerTot;
    funcerTot = new TF1*[NMax-NMin];

    for (int i = 0; i < (NMax - NMin) ; i++){
        
        //funcerTot[i] = new TF1("funcerTot", "[ConstHard] + [ConstSoft]* e**( -(x**[k1])/[k2] )", 0.4, 10.);
        //funcerTot[i] ->SetParNames(Form("Hard%d", i), Form("Soft%d", i), "k1", "k2");

        funcerTot[i] = new TF1("funcerTot", "[ConstHard] + [ConstSoft]* ( [k1]/x )", 0.4, 10.);
        funcerTot[i] ->SetParNames(Form("Hard%d", i), Form("Soft%d", i), "k1");
        
    }
    

    double TextXStart = 0.55 ;
    double TextYStart = 0.2 ;
    double LineShiftY = 0.065*(NMax - NMin - 1) ;
    
    double ValueShiftX = 0.2 ;
    double LineShiftYMult = -0.065 ;
    int ColorCountDirection = +3 ;
    int ColorStart = 52 ;

    

    for (int i = 0 ; i < (NMax - NMin); i++){
        
//        funcerTot[i]->FixParameter(0, funcs[i]->GetParameter(0) );
//        funcerTot[i]->FixParameter(1, funcs[i]->GetParameter(1) );
//        funcerTot[i]->FixParameter(2, funcs[i]->GetParameter(2) );
  
//        funcerTot[i]->FixParameter(0, 1 );
//        funcerTot[i]->FixParameter(1, 1 );
//        funcerTot[i]->FixParameter(2, 1 );

        
        //funcerTot[i]->FixParameter(3, funcs[i]->GetParameter(3) );

        
        funcerTot[i]->SetRange(range[i]().first, range[i]().second);
        funcs[i]->SetLineColor(ColorCountDirection*i + ColorStart);
        Histos[i]->GetListOfFunctions()->Add(funcs[i]);
        
        
        Histos[i]->SetMaximum(5.1);
        Histos[i]->SetMinimum(-1.1);

        Histos[i]->SetLineColor(kYellow +2);
        Histos[i]->Draw("sames");
        
        //Soft name and value
        TLatex *lSoftName = new TLatex(TextXStart, LineShiftYMult*i +0.06 + TextYStart +LineShiftY,Form("#color[%d]{%s}", ColorCountDirection*i + ColorStart, funcs[i]->GetParName(1) ) );
        lSoftName->SetNDC();
        lSoftName->SetTextSize(0.03);
        lSoftName->Draw();
        
        TLatex *lSoftValue = new TLatex(TextXStart + ValueShiftX, LineShiftYMult*i +0.06 + TextYStart +LineShiftY, Form("#color[%d]{%0.2f #pm %0.2f}", ColorCountDirection*i + ColorStart,  funcs[i]->GetParameter(1), result.ParError(2*i+1) ) );
        lSoftValue->SetNDC();
        lSoftValue->SetTextSize(0.03);
        lSoftValue->Draw();

        //Hard name and vaule
        TLatex *lHardName = new TLatex(TextXStart, LineShiftYMult*i +0.03 + TextYStart +LineShiftY,Form("#color[%d]{%s}", ColorCountDirection*i + ColorStart, funcs[i]->GetParName(0) ) );
        lHardName->SetNDC();
        lHardName->SetTextSize(0.03);
        lHardName->Draw();

        TLatex *lHardValue = new TLatex(TextXStart + ValueShiftX, LineShiftYMult*i +0.03 + TextYStart +LineShiftY, Form("#color[%d]{%0.2f #pm %0.2f}", ColorCountDirection*i + ColorStart, funcs[i]->GetParameter(0), result.ParError(2*i) ) );
        lHardValue->SetNDC();
        lHardValue->SetTextSize(0.03);
        lHardValue->Draw();

        
    }
        

    

    TLatex *lFunc = new TLatex(0.2, 0.83,Form("#color[1]{ #it{f}(#it{p}_{T}) = #it{C}_{Hard} + #it{C}_{Soft} e^{ #it{k}/#it{p}_{T}} }") );

    lFunc->SetNDC();
    lFunc->SetTextSize(0.03);
    lFunc->Draw();
    
    
    //k
    TLatex *lkName = new TLatex(TextXStart, TextYStart,Form("#color[2]{%s}", "k" ) );

    lkName->SetNDC();
    lkName->SetTextSize(0.03);
    lkName->Draw();
    
    TLatex *lkValue = new TLatex(TextXStart + ValueShiftX, TextYStart,Form("#color[2]{%0.4f #pm %0.4f}", funcs[NMin]->GetParameter(2), result.ParError(2*(NMax - NMin)) ) );
    lkValue->SetNDC();
    lkValue->SetTextSize(0.03);
    lkValue->Draw();
    
    //Chi2/NDF
    TLatex *lChi2NDFName = new TLatex(TextXStart, 0.065*(NMax - NMin+1) +0.06 + TextYStart,Form("#color[%d]{#chi^{2}/NDF}", 1 ) );
    lChi2NDFName->SetNDC();
    lChi2NDFName->SetTextSize(0.03);
    lChi2NDFName->Draw();
    
    TLatex *lChi2NDFValue= new TLatex(TextXStart + ValueShiftX, 0.065*(NMax - NMin+1) +0.06 + TextYStart,Form("#color[%d]{%f}", 1, (result.Chi2())/(result.Ndf()) ) );
    lChi2NDFValue->SetNDC();
    lChi2NDFValue->SetTextSize(0.03);
    lChi2NDFValue->Draw();

    //Titel
    TLatex *lName = new TLatex(TextXStart, 0.065*(NMax - NMin) +0.06 + TextYStart,Form("#color[%d]{Parameter name}", 1 ) );
    lName->SetNDC();
    lName->SetTextSize(0.03);
    lName->Draw();
    
    TLatex *lValue= new TLatex(TextXStart + ValueShiftX, 0.065*(NMax - NMin) +0.06 + TextYStart,Form("#color[%d]{Value #pm error }", 1 ) );
    lValue->SetNDC();
    lValue->SetTextSize(0.03);
    lValue->Draw();
    
    
    
    
    if(Table == 1){
        Histos[0]->SetTitle( "Multiplicity classes over their MB and fits for #pi^{#pm} at #sqrt{s} = 13 TeV" );

    }

    if(Table == 3){
        Histos[0]->SetTitle( "Multiplicity classes over their MB and fits for K^{#pm} at #sqrt{s} = 13 TeV" );

    }
    
    if(Table == 5){
        Histos[0]->SetTitle( "Multiplicity classes over their MB and fits for p(#bar{p}) at #sqrt{s} = 13 TeV" );

    }

    
    
    Histos[0] -> GetYaxis()->SetTitle("#frac{#it{dN}}{#it{dp}_{T}} #[]{#frac{#it{dN}_{MB}}{#it{dp}_{T}}}^{-1}");
    Histos[0] -> GetXaxis()->SetTitle("#it{p}_{T} (GeV/c)");
    
    
    c1->SaveAs(Form("Comb2k%d13TeV.eps", Table ));
    //c1->SaveAs(Form("Comb2k%d13TeV.C", Table ));
    
    TH1F* CSoft = new TH1F( "Soft_constants" , "Soft parameters", (NMax -NMin), NMin-0.5, NMax-0.5)    ;
    TH1F* CHard = new TH1F( "Hard_constants" , "Hard parameters", (NMax -NMin), NMin-0.5, NMax-0.5)    ;

    
    for(int i = 0 ; i < (NMax -NMin) ; i++ ){
        
        CSoft -> SetBinContent(i+1, funcs[i]->GetParameter(1));
        CHard -> SetBinContent(i+1, funcs[i]->GetParameter(0));
        
        CSoft -> SetBinError(i+1, result.ParError(2*i+1));
        CHard -> SetBinError(i+1, result.ParError(2*i));

        
    }
    
    CSoft -> SaveAs(Form( "CSoft%d.root", Table));
    CHard -> SaveAs(Form( "CHard%d.root", Table));
  
    
    
    //double MassesGeV[3] = {0.1396, 0.4937, 0.9383}; //{pion#pm, kaon#pm, proton} // in GeV

    double MassesGeV[3] = {0.0001396, 0.0004937, 0.0009383}; //{pion#pm, kaon#pm, proton} // in TeV

    
    
    if(Table==1){
        TH1D* hCk1 = new TH1D( "Theconstantk" , "#it{k} over each particles' mass at #sqrt{s} = 13 TeV", 3, 0, 3)    ;
        
        hCk1 ->SetBinContent(1, funcs[NMin]->GetParameter(2)/MassesGeV[0] );
        hCk1 ->SetBinError(1, result.ParError(2*(NMax - NMin))/MassesGeV[0] );

        hCk1 -> SaveAs(Form( "Ck%d.root", 1));
    }
    
    
    
    if(Table == 3){
        TH1D* hCk2 = new TH1D( "Theconstantk" , "#it{k} over each particles' mass at #sqrt{s} = 13 TeV", 3, 0, 3)    ;
        
        hCk2 ->SetBinContent(2, funcs[NMin]->GetParameter(2)/MassesGeV[1] );
        hCk2 ->SetBinError(2, result.ParError(2*(NMax - NMin))/MassesGeV[1] );

        hCk2 -> SaveAs(Form( "Ck%d.root", 3));
    }

    
    
    
    if(Table==5){
        TH1D* hCk3 = new TH1D( "Theconstantk" , "#it{k} over each particles' mass at #sqrt{s} = 13 TeV", 3, 0, 3)    ;
        
        hCk3 ->SetBinContent(3, funcs[NMin]->GetParameter(2)/MassesGeV[2] );
        hCk3 ->SetBinError(3, result.ParError(2*(NMax - NMin))/MassesGeV[2] );
        
        hCk3 -> SaveAs(Form( "Ck%d.root", 5));
    }
    

    
    
    
    
    
//    TH1F* Ck = new TH1F( "The_constant_k" , "The constant k-value over mass", 2, 0, 1)    ;
//
//    Ck ->SetBinContent(1, funcs[NMin]->GetParameter(2));
//    Ck ->SetBinError(1, result.ParError(2*(NMax - NMin)) );
//
//
//    Ck -> SaveAs(Form( "Ck%d.root", Table));
//
    
}



void AddingHistos(){
    

    int Table[3] = {1,3,5};
    
    TH1D **HistosCH;
    HistosCH = new TH1D*[3];

    TH1D **HistosCS;
    HistosCS = new TH1D*[3];
    
    TH1D **HistosCk;
    HistosCk = new TH1D*[3];

    
    for (int i = 0; i <3; i++){
        
        TFile* fileCH = TFile::Open(Form("CHard%d.root", Table[i]  ));
        HistosCH[i] = (TH1D*)fileCH->Get("Hard_constants");
        

        TFile* fileCS = TFile::Open(Form("CSoft%d.root", Table[i]  ));
        HistosCS[i] = (TH1D*)fileCS->Get("Soft_constants");
        
        
        TFile* fileCk = TFile::Open(Form("Ck%d.root", Table[i]  ));
        HistosCk[i] = (TH1D*)fileCk->Get("Theconstantk");
        
        
        if(!fileCH)
        return;
        if(!fileCS)
        return;
        if(!fileCk)
        return;


    }
    
    cout << "Hej" << endl;

    float SIZE = 0.06;
    
    float SIZEOffset = 0.82;

    
    TCanvas *cCk = new TCanvas("cCk", "The constant k-value over each particles mass");

    int Color[3] = {4,632-2,2};
    
    for (int i = 0 ; i < 3; i++){

        HistosCk[i] ->GetXaxis() ->SetBinLabel(1, "#pi#pm");
        HistosCk[i] ->GetXaxis() ->SetBinLabel(2, "K#pm");
        HistosCk[i] ->GetXaxis() ->SetBinLabel(3, "p(#bar{p})");
        HistosCk[i] ->GetXaxis() ->SetLabelSize(0.1);
        //HistosCk[i] ->SetMaximum( 51 );
        //HistosCk[i] ->SetMinimum( 7);
        HistosCk[i] ->SetLineWidth(2);
        HistosCk[i] ->SetStats(0);
        

        HistosCk[i] ->GetYaxis()->SetTitle("#it{k}[GeV/c] over mass[TeV/c^{2}] (10^{-3}c)"); //First fit
        
        //HistosCk[i] ->GetYaxis()->SetTitle("(The unit of #it{k})/GeV"); //Second fit
        
        
        
        HistosCk[i]->SetLineColor( Color[i] );
        HistosCk[i]->Draw("sames");
        
        HistosCk[i] ->GetYaxis()->SetTitleSize(SIZE);
        HistosCk[i] ->GetYaxis()->SetTitleOffset(SIZEOffset-0.05);

        
        
    }
    
    
    cCk -> SaveAs("cCk13TeV.eps");

    
    
    
    
//    int Color[3] = {4,632-2,2};
//
//
//    TH1D* hCk = new TH1D( "Theconstantk" , "The constant k-value over mass", 3, -0.5, 2.5)    ;
//
//
//
//    for (int i = 0 ; i < 3; i++){
//
//        hCk ->SetBinContent(i+1, HistosCk[i]->GetBinContent(1)/MassesGeV[i] );
//        hCk ->SetBinError(i+1, HistosCk[i]->GetBinError(1)/MassesGeV[i] );
//
//        hCk ->SetLineWidth(2);
//
//    }
//
//
//    hCk ->GetXaxis() ->SetBinLabel(1, "#pi#pm");
//    hCk ->GetXaxis() ->SetBinLabel(2, "K#pm");
//    hCk ->GetXaxis() ->SetBinLabel(3, "p(#bar{p})");
//
//    hCk ->GetXaxis() ->SetLabelSize(0.1);
//
//    TH1D* hCk1 = new TH1D( "Theconstantk" , "The constant k-value over mass", 3, 0.5, 2.5)    ;
//
//    for (int i = 0 ; i < 3; i++){
//        hCk1 ->SetBinContent(i+1, HistosCk[i]->GetBinContent(1)/0.5 );
//        hCk1 ->SetBinError(i+1, HistosCk[i]->GetBinError(1)/0.5 );
//
//
//    }
//
//
//
//    TCanvas *cCk = new TCanvas("cCk", "The constant k-value over each particles mass");
//
//
//    hCk->Draw("sames");
//    hCk->SetStats(0);
//
//
//    hCk->SetTitle( "The constant k-values over each particles mass at #sqrt{s} = 13 TeV" );
//
//    hCk-> GetYaxis()->SetTitle("The unit of the k-value/GeV");
//
//
//    cCk -> SaveAs("cCk13TeV.eps");
//
//
//
    
    int DIV = 1;
    
    
    for (int ibin=1; ibin <= (HistosCS[1] -> GetNbinsX()) ; ibin++) {
            
        HistosCS[1] -> SetBinContent(ibin, (HistosCS[1] ->GetBinContent(ibin)) /DIV );
        HistosCS[1] -> SetBinError(ibin, (HistosCS[1] ->GetBinError(ibin)) /DIV);
                    
        HistosCH[1] -> SetBinContent(ibin, (HistosCH[1] ->GetBinContent(ibin)) /DIV );
        HistosCH[1] -> SetBinError(ibin, (HistosCH[1] ->GetBinError(ibin)) /DIV);
        
    }
    

        
    TCanvas *cCH = new TCanvas("cCH", "Hard parameters for multiplicity classes at #sqrt{s} = 13 TeV");
    cout << "Hej" << endl;

    int MAXMIN = 120;
    

    
    for (int i = 0 ; i < 3; i++){
       
        //Best fit:
//        HistosCH[i]->SetMaximum(4);
//        HistosCH[i]->SetMinimum( -0.4 );

        //First fit:
        HistosCH[i]->SetMaximum(140);
        HistosCH[i]->SetMinimum( -80 );

        HistosCH[i] ->SetLineWidth(2);
        HistosCH[i]->SetLineColor( Color[i] );
        HistosCH[i]->Draw("sames");
        HistosCH[i]->SetStats(0);
        
        
        HistosCH[i]->SetTitle( "Hard parameters for multiplicity classes at #sqrt{s} = 13 TeV" );
        HistosCH[i] -> GetYaxis()->SetTitle("Hard parameter");
        
        HistosCH[i] ->GetYaxis()->SetTitleSize(SIZE);
        HistosCH[i] ->GetYaxis()->SetTitleOffset(SIZEOffset);

    }
    
    
    auto legendH = new TLegend(0.75, 0.65, 0.9, 0.9); //(start from left, start from bottom ) //x1,y1,x2,y2
    legendH->SetHeader("Particles","C"); // option "C" allows to center the header
    legendH->AddEntry(HistosCH[0], "#pi^{#pm}","l");
    legendH->AddEntry(HistosCH[1], "K^{#pm}","l");
    legendH->AddEntry(HistosCH[2], "p(#bar{p})","l");

    legendH->Draw();
        
    
    TLatex *lkNameleft = new TLatex(0.1, 0.02, Form("#color[1]{%s}", "High multiplicity" ) );


    lkNameleft->SetNDC();
    lkNameleft->SetTextSize(0.05);
    lkNameleft->Draw();
    
    TLatex *lkNameright = new TLatex(0.65, 0.02, Form("#color[1]{%s}", "Low multiplicity" ) );


    lkNameright->SetNDC();
    lkNameright->SetTextSize(0.05);
    lkNameright->Draw();
     
    cCH -> SaveAs("cCH13TeV.eps");
    
    
    
    
    
    TCanvas *cCS = new TCanvas("cCS", "Soft parameters for multiplicity classes at #sqrt{s} = 13 TeV");
    
    
    for (int i = 0 ; i < 3; i++){
        
        //Best fit
//        HistosCS[i]->SetMaximum( 0.5 );
//        HistosCS[i]->SetMinimum( -1.6);
//
        
        //First fit
        HistosCS[i]->SetMaximum(80);
        HistosCS[i]->SetMinimum( -140 );

        
        
        HistosCS[i] ->SetLineWidth(2);
        HistosCS[i]->SetLineColor( Color[i] );
        HistosCS[i]->Draw("sames");
        HistosCS[i]->SetStats(0);
        
        HistosCS[i]->SetTitle("Soft parameters for multiplicity classes at #sqrt{s} = 13 TeV");
        HistosCS[i] -> GetYaxis()->SetTitle("Soft parameter");
        
        HistosCS[i] ->GetYaxis()->SetTitleSize(SIZE);
        HistosCS[i] ->GetYaxis()->SetTitleOffset(SIZEOffset);
        
    }
    
    
    
    auto legendS = new TLegend(0.75, 0.15, 0.9, 0.4); //(start from left, start from bottom ) //x1,y1,x2,y2
    legendS->SetHeader("Particles","C"); // option "C" allows to center the header
    legendS->AddEntry(HistosCS[0], "#pi^{#pm}","l");
    legendS->AddEntry(HistosCS[1], "K^{#pm}","l");
    legendS->AddEntry(HistosCS[2], "p(#bar{p})","l");

    legendS->Draw();

    
    
    TLatex *lkNameleft2 = new TLatex(0.1, 0.02, Form("#color[1]{%s}", "High multiplicity" ) );


    lkNameleft2->SetNDC();
    lkNameleft2->SetTextSize(0.05);
    lkNameleft2->Draw();
    
    TLatex *lkNameright2 = new TLatex(0.65, 0.02, Form("#color[1]{%s}", "Low multiplicity" ) );


    lkNameright2->SetNDC();
    lkNameright2->SetTextSize(0.05);
    lkNameright2->Draw();


    cCS -> SaveAs("cCS13TeV.eps");
    
    
    
}








