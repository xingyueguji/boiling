#include "plotCarlos.cpp"

//TGraphErrors* plotBill(Double_t target=2.01, string spec="HMS", int option=1){
//TGraph* plotCarlos(int xcol=2,int ycol=25, string tgt="LD2"){
TGraphErrors *normalizeIt(TGraph *g, TGraph *ge){
  vector <double> iy;
  vector <double> iye;
  vector <double> ix;

  int npts=g->GetN();
  for(int i=0; i< npts; i++)
    {
      double xval, yval, yeval, xval2;
      g->GetPoint(i, xval, yval);
      ge->GetPoint(i, xval2, yeval);
      iy.push_back(yval);
      iye.push_back(yeval);
      ix.push_back(xval);
    }

  TGraphErrors *ig=new TGraphErrors(npts, &ix[0], &iy[0], 0, &iye[0]);
  ig->Draw();
  ig->Fit("pol1");
  gPad->Update();
  TF1 *func=(TF1*)ig->GetListOfFunctions()->FindObject("pol1");
  double b=func->GetParameter(0);

  vector <double> y;
  vector <double> ye;
  vector <double> x;

  npts=g->GetN();
  for(int i=0; i< npts; i++)
    {
      double xval, yval, yeval, xval2;
      g->GetPoint(i, xval, yval);
      ge->GetPoint(i, xval2, yeval);
      y.push_back(yval/b);
      ye.push_back(yeval/b);
      x.push_back(xval);
    }
  TGraphErrors *graph=new TGraphErrors(npts, &x[0], &y[0], 0, &ye[0]);
  return graph;
}

TPaveStats* formatit(TGraphErrors *g, int style, int color){
  g->SetMarkerStyle(style);
  g->SetLineColor(color);
  g->SetMarkerColor(color);
  g->Draw();
  TF1 *fun=new TF1("fun","[1]/10000*x+[0]");
  fun->SetParNames("y-int","slope (%/100uA)");
  g->Fit("fun");
  gPad->Update();
  TF1 *f=(TF1*)g->GetListOfFunctions()->FindObject("fun");
  f->SetLineColor(color);
  TPaveStats *stats = (TPaveStats*)g->FindObject("stats");  
  stats->SetTextColor(color);
  return stats;
}
void plotAllSlopes(string target="LH2", string spec="SHMS")
{
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1);
  //  TCanvas *c1=new TCanvas();
  //  c1->Divide(2,1);
  string specl;
  if(spec=="SHMS")specl="shms";
  if(spec=="HMS")specl="hms";
  TGraph *gr1=plotCarlos(18,23,target.c_str(),specl.c_str());//traacking yield
  TGraph *gr1e=plotCarlos(18,24,target.c_str(),specl.c_str());//traacking yield
  TGraph *gr2=plotCarlos(18,21,target.c_str(),specl.c_str());//non-tracking yield
  TGraph *gr2e=plotCarlos(18,22,target.c_str(),specl.c_str());//non-tracking yield
  TGraph *gr3=plotCarlos(18,19,target.c_str(),specl.c_str());//scaler 
  TGraph *gr3e=plotCarlos(18,20,target.c_str(),specl.c_str());//scaler 

  TGraphErrors *g_track_lh2_shms=normalizeIt(gr1, gr1e);
  TGraphErrors *g_nontrack_lh2_shms=normalizeIt(gr2, gr2e);
  TGraphErrors *g_scaler_lh2_shms=normalizeIt(gr3, gr3e);
  //  g_track_lh2_shms->SetName("g_track_lh2_shms");
 TPaveStats *st1=formatit(g_track_lh2_shms, 33, 600);
 TPaveStats *st2=formatit(g_nontrack_lh2_shms, 20, 632);
 TPaveStats *st3=formatit(g_scaler_lh2_shms, 31, 1);

  g_track_lh2_shms->GetYaxis()->SetRangeUser(.93,1.002);
  if(target=="C12")  g_track_lh2_shms->GetYaxis()->SetRangeUser(.90,1.05);
  g_track_lh2_shms->SetTitle(Form("%s %s Boiling",target.c_str(), spec.c_str()));
  g_track_lh2_shms->GetXaxis()->SetTitle("BCM4B Current (uA)");
  g_track_lh2_shms->GetYaxis()->SetTitle("Normalized QNY");
  


  g_track_lh2_shms->Draw("ap");
  //  g_track_lh2_shms->Fit("pol1");
  gPad->Update();  

  g_nontrack_lh2_shms->Draw("sp");
  //  g_nontrack_lh2_shms->Fit("pol1");

  g_scaler_lh2_shms->Draw("sp");
  //  g_scaler_lh2_shms->Fit("pol1");

  gPad->Update();

  //    TPaveStats *st1 = (TPaveStats*)g_track_lh2_shms->FindObject("stats");  
    st1->SetY1NDC(.41);
    st1->SetX1NDC(.11);
    st1->SetY2NDC(.56);
    st1->SetX2NDC(.5);
    st1->Draw("same");

    //  TPaveStats *st2 = (TPaveStats*)g_nontrack_lh2_shms->FindObject("stats");  
  st2->SetY1NDC(.26);
  st2->SetX1NDC(.11);
  st2->SetY2NDC(.41);
  st2->SetX2NDC(.5);
  st2->Draw("same");

  //  TPaveStats *st3 = (TPaveStats*)g_scaler_lh2_shms->FindObject("stats");  
  st3->SetY1NDC(.11);
  st3->SetX1NDC(.11);
  st3->SetY2NDC(.26);
  st3->SetX2NDC(.5);
  st3->Draw("same");


    TLegend *leg=new TLegend(.51,.15,.69,.4);
    leg->AddEntry(g_track_lh2_shms,"Tracking Yield","lp");
    leg->AddEntry(g_nontrack_lh2_shms,"Non-tracking Yield","lp");
    leg->AddEntry(g_scaler_lh2_shms,"Scaler Yield","lp");
    leg->Draw();

  gPad->SaveAs("test.pdf");
    /*
  c1->cd(1);
  gPad->Update();
  TPaveStats *stat_c = (TPaveStats*)gr1c->FindObject("stats");  
  TPaveStats *stat_b = (TPaveStats*)gr1b->FindObject("stats");  
  stat_c->SetY1NDC(0.6);
  stat_c->SetY2NDC(0.8);
  stat_c->SetTextColor(kBlue);
  stat_b->SetTextColor(kRed);
  stat_c->Draw();
  stat_b->Draw();

  c1->cd(2);
  */

  return;
}
/*
0#!Run[i,0]/
1set_current[f,1]/
2avg_current_bcm4a[f,2]/
3sclY4a[f,3]/
4sclY_err4a[f,4]/
5ntrkY4a[f,5]/
6ntrkY_err4a[f,6]/
7trkY4a[f,7]/
8trkY_err4a[f,8]/
9cpuLT_bcm4a[f,9]/
10tLT_bcm4a[f,10]/
11Qtot_bcm4a[f,11]/
12hs1x_rate_bcm4a[f,12]/
13ptrig1_rate_bcm4a[f,13]/
14ptrig2_rate_bcm4a[f,14]/
15ptrig3_rate_bcm4a[f,15]/
16hedtm_rate_bcm4a[f,16]/
17h_eTrkEff_bcm4a[f,17]/
18avg_current_bcm4b[f,18]/
19sclY4b[f,19]/
20sclY_err4b[f,20]/
21ntrkY4b[f,21]/
22ntrkY_err4b[f,22]/
23trkY4b[f,23]/
24trkY_err4b[f,24]/
25cpuLT_bcm4b[f,25]/
26tLT_bcm4b[f,26]/
27Qtot_bcm4b[f,27]/
28hs1x_rate_bcm4b[f,28]/
29ptrig1_rate_bcm4b[f,29]/
30ptrig2_rate_bcm4b[f,30]/
31ptrig3_rate_bcm4b[f,31]/
32hedtm_rate_bcm4b[f,32]/
33h_eTrkEff_bcm4b[f,33]/
*/
