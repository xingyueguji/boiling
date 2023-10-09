#include "src/readReport.cpp"

TGraphErrors* plotBill(Double_t target=2.01, string spec="HMS", int option=1){
  gStyle->SetOptFit();
  FILE *fp = fopen(Form("boilingYields%s.txt",spec.c_str()),"r");  
  Float_t run, curr, charge, yield, qny, lt, lt2, ps ,trkeff;
  Double_t tgt;
  Int_t ncols; 
  //  Float_t dumFact=3.789;
  Float_t dumFact=0;
  if(target==1.01)dumFact=1/3.789;
  if(target==2.01)dumFact=1/4.063;
  Float_t dumLt=0.;
  Float_t dumQ=0.;
  Float_t dumY=0.;
  Float_t dumTrk=0.;
  Float_t dumErr=0.;
  vector <float> x,y,y1,y2,y3,ye;
  // Loop through to get dummy
  float dumRun;
  if(spec=="SHMS")dumRun=3226;
  if(spec=="HMS")dumRun=2096;

  while (1) { 
    ncols = fscanf(fp,"%f %f %f %f %f %f %f %f %f",&run, &curr, &charge,&yield,  &qny, &lt, &lt2, &ps, &trkeff);
    if (ncols < 0) break;
    cout << "Looking for a dummy, run: "<<run<<endl;
    if(run==dumRun)
      {
	cout << "Found a dummy"<<endl;
	dumLt=lt2;
	dumQ=charge;
	dumY=yield;
	dumTrk=trkeff;
	dumErr=sqrt(yield)/yield;
	cout << "Yield"<<"\t"<<"Charge"<<"\t"<<"LiveTm"<<"\t"<<"TrkEff"<<endl;
	cout << dumY<<"\t"<<dumQ<<"\t"<<dumLt<<"\t"<<dumTrk;
      }
  }
  fclose(fp);
  fp = fopen(Form("boilingYields%s.txt",spec.c_str()),"r");  
  // Loop and grab right target
  while (1) { 
    ncols = fscanf(fp,"%f %f %f %f %f %f %f %f %f",&run, &curr, &charge,&yield,  &qny, &lt, &lt2, &ps, &trkeff);
    if (ncols < 0) break;
    tgt=readReport(run,"target");
    cout << "The target for run "<<run<< " is "<<tgt<<endl;
    if(tgt == target)
      {
	cout << "I made it !!"<<endl;
	x.push_back(curr);

	//	float error = sqrt(yield)/charge/trkeff/lt;
	float err1 = sqrt(yield)/yield; //fractional error
	float error=sqrt(yield)/charge/trkeff/lt2*1000.;
	if(option==1){
	  y.push_back(qny/trkeff/lt2*1000);
	  ye.push_back(error);
	}
	if(option==2){
	  y.push_back(trkeff);
	  ye.push_back(0);
	}
	if(option==3){
	  y.push_back(lt2);
	  ye.push_back(0);
	}
	if(option==4){
	  y.push_back(charge/1000.);
	  ye.push_back(0);
	}
	if(option==5){
	  y.push_back(yield);
	  ye.push_back(0);
	}
      }
  }
  fclose(fp);

  TGraphErrors *gr=new TGraphErrors(x.size(),&x[0],&y[0],0,&ye[0]);
  gr->SetMarkerStyle(26);   
  gr->SetMarkerColor(kRed);   

    if(option==2)gr->SetTitle(Form("%s Tracking Eff",spec.c_str()));
    if(option==3)gr->SetTitle(Form("%s Livetime",spec.c_str()));
    if(option==4)gr->SetTitle(Form("%s Charge",spec.c_str()));
    if(option==5)gr->SetTitle(Form("%s Raw Yield",spec.c_str()));

  if(target==1.01){
    if(option==1)gr->SetTitle(Form("%s Hydrogen Boiling",spec.c_str()));
    //    gr->GetYaxis()->SetRangeUser(1.2,2);
  }

  if(target==2.01){
    if(option==1)gr->SetTitle(Form("%s Deuterium Boiling",spec.c_str()));
    //    gr->GetYaxis()->SetRangeUser(1.8,3.2);
  }

  if(target==12.01){
    if(option==1)gr->SetTitle(Form("%s Carbon Boiling",spec.c_str()));
    //    gr->GetYaxis()->SetRangeUser(.7,1.);
  }

  //  gr->GetYaxis()->SetTitle("Normalized QNY");
  gr->GetXaxis()->SetTitle("Current (uA)");

  //  gr->Draw("ap");
  //  gr->Fit("pol1");
  /*
  TF1 *fun=(TF1*)gr->GetListOfFunctions()->FindObject("pol1");
  float norm=fun->GetParameter(0);
  vector <float> yy,yye;
  for(int i=0; i<y.size(); i++)
    {
      yy.push_back(y.at(i)/norm);
      yye.push_back(ye.at(i)/norm);
    }
    TGraphErrors *gr1=new TGraphErrors(x.size(),&x[0],&yy[0],0,&yye[0]);
  */
return gr;
  }
