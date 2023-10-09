void fitResultsDummy(){
 gStyle->SetTitleX(0.2);
 gStyle->SetTitleW(.6);
 gStyle->SetOptStat(1111);
 gStyle->SetOptFit(1);
 gStyle->SetLabelSize(0.00,"x");// size of axis value font
  const int pts=4;
  double lh2[pts]={6.108, 4.549, 3.754, 4.07};
  double lh2e[pts]={.7513, .5009, .6827, .6};
  double ld2[pts]={4.117, 3.212, 4.29, 4.372};
  double ld2e[pts]={.7843, .5187, .7415, .6534};
  double x[pts]={1,2,3,4};


  TGraphErrors *gh=new TGraphErrors(pts,&x[0],&lh2[0],0,&lh2e[0]);
  TGraphErrors *gd=new TGraphErrors(pts,&x[0],&ld2[0],0,&ld2e[0]);

  gh->SetTitle("Boiling Slopes Summary With Dummy Subtraction");
  gh->GetYaxis()->SetRangeUser(0,7);
  gh->GetYaxis()->SetTitle("Boiling Slope ( %/ 100 uA)");
  gh->GetXaxis()->SetTitle("SHMS Tracking        SHMS NoTracking         HMS Tracking       HMS NoTracking");
  gh->SetMarkerColor(kRed);
  gh->SetMarkerStyle(33);

  gd->SetMarkerColor(kBlue);
  gd->SetMarkerStyle(20);

  gh->Draw("ap");
  gd->Draw("sp");

  gh->Fit("pol0");
  gd->Fit("pol0");

  TLegend *leg=new TLegend(.65,.7,.85,.85);
  leg->AddEntry(gh,"LH2","lp");
  leg->AddEntry(gd,"LD2","lp");
  leg->Draw();
  gPad->Update();
  TF1 *fh=(TF1*)gh->GetListOfFunctions()->FindObject("pol0");
  fh->SetLineColor(kRed);

  TF1 *fd=(TF1*)gd->GetListOfFunctions()->FindObject("pol0");
  fd->SetLineColor(kBlue);

  TPaveStats *statsh = (TPaveStats*)gh->FindObject("stats");  
  statsh->SetTextColor(kRed);
    statsh->SetY1NDC(.15);
    statsh->SetX1NDC(.15);
    statsh->SetY2NDC(.3);
    statsh->SetX2NDC(.4);
    statsh->Draw("same");
  TPaveStats *statsd = (TPaveStats*)gd->FindObject("stats");  
  statsd->SetTextColor(kBlue);
    statsd->SetY1NDC(.15);
    statsd->SetX1NDC(.45);
    statsd->SetY2NDC(.3);
    statsd->SetX2NDC(.7);
    statsd->Draw("same");
  return;
}
