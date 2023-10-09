#include "plotBill.cpp"
#include "plotCarlos.cpp"

//TGraphErrors* plotBill(Double_t target=2.01, string spec="HMS", int option=1){
//TGraph* plotCarlos(int xcol=2,int ycol=25, string tgt="LD2"){

void compare()
{
  TCanvas *c1=new TCanvas();
  c1->Divide(3,2);

  TGraph *gr1b=plotBill(2.01,"HMS",1);
  TGraph *gr2b=plotBill(2.01,"HMS",2);
  TGraph *gr3b=plotBill(2.01,"HMS",3);
  TGraph *gr4b=plotBill(2.01,"HMS",4);
  TGraph *gr5b=plotBill(2.01,"HMS",5);

  TGraph *gr1c=plotCarlos(18,23,"LD2");//traacking yield
  TGraph *gr2c=plotCarlos(18,33,"LD2");//tracking eff
  TGraph *gr3c=plotCarlos(18,25,"LD2");//livetime
  TGraph *gr4c=plotCarlos(18,27,"LD2");//charge
  TGraph *gr5c=plotCarlos(18,34,"LD2");//raw yield

  //    gr1b->GetYaxis()->SetRangeUser(1700,1850);
  gr1b->GetYaxis()->SetRangeUser(2800,3000);
  gr2b->GetYaxis()->SetRangeUser(.98,1);
  c1->cd(1);
  gr1b->Draw("ap");
  gr1b->Fit("pol1");
  gr1c->Draw("sp");
  gr1c->Fit("pol1");
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
  gr2b->Draw("ap");

  gr2c->Draw("sp");
  c1->cd(3);
  TLegend *leg=new TLegend(.1,.1,.9,.9);
  leg->AddEntry(gr1b,"Bill's Code","p");
  leg->AddEntry(gr1c,"Carlos' Code","p");
  leg->Draw();
  //  gr1c->Draw("ap");
  //  gr1c->Fit("pol1");
  c1->cd(4);
  gr3b->Draw("ap");
  gr3c->Draw("sp");
  c1->cd(5);
  gr4b->Draw("ap");
  gr4c->Draw("sp");
  c1->cd(6);
  gr5b->Draw("ap");
  gr5c->Draw("sp");
  return;
}
