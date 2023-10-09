#include "elt/getLivetime.cpp"

TGraph* plotCarlos(int xcol=2,int ycol=25, string tgt="LD2",string spec="shms"){
  bool elimPts=false;
  double tau;
  if(spec=="shms")tau=37.1E-9;
  if(spec=="hms")tau=23.8E-9;

  double dumScale=1;
  if(tgt=="LH2")dumScale=3.789;
  if(tgt=="LD2")dumScale=4.063;
  double dumYield=0;

  if(tgt!="C12")
    {
      const int ncol=34;
      double arr[ncol];
      string temp;
      double num;
      ifstream duminfile (Form("%s_AL_yield.data",spec.c_str()));
      for(int j=0;j<ncol;j++){
	duminfile >> temp;
	cout <<j<<"\t"<< temp<<endl;   //this is like a legend
      }
      for(int j=0;j<ncol;j++){
	duminfile>>num;
	arr[j]=num;
      }
      dumYield=arr[ycol];
    }

  //  if(spec=="shms")dumYield=dumYield/.9979;
  //  if(spec=="hms")dumYield=dumYield/.9996;

  //  dumYield=0.;
  //   tau=0.;

  cout <<tau<<"ns\t"<< tgt << "\t" << spec << "\t"<<dumYield <<"\t"<<dumScale<<endl;  
  int rows=0;
  if(spec=="shms"&&tgt=="LH2")rows=8;
  if(spec=="hms"&&tgt=="LH2")rows=9;
  if(tgt=="C12")rows=3;
  if(tgt=="LD2")rows=7;
  const int ncol=34;
  const int nrow=rows;
  double arr[ncol+1][nrow];
  string temp;
  double num;
  ifstream infile (Form("%s_%s_yield.data",spec.c_str(),tgt.c_str()));
  
  for(int j=0;j<ncol;j++){
    infile >> temp;
    cout <<j<<"\t"<< temp<<endl;   //this is like a legend
  }
  
    //    cout << "What would you like to plot?"<<endl;
    //    cout << "x?"<<endl;
    //    cin >> xcol;
    //    cout << "y?"<<endl;
    //    cin >> ycol;    
    //    int i=0;
  for(int i=0;i<nrow;i++){
    for(int j=0;j<ncol;j++){
      infile>>num;
      arr[j][i]=num;
    }
  }
  for(int i=0;i<nrow;i++){arr[ncol][i]=arr[23][i]*arr[27][i]*arr[25][i]*arr[33][i];}//work backwards to get raw yield
  vector <double> x;
  vector <double> y;
    ////////////////////////////////
  for(int i=0;i<nrow;i++){
    if( tgt!="LD2" || arr[1][i]<65.|| (arr[1][i]>=65 && !elimPts) )
    {
      x.push_back(arr[xcol][i]);
      y.push_back(arr[ycol][i]);
    }
  }
    ////////////////////////////////
  if(ycol==23 || ycol == 21 || ycol==19){ //subtract dummy
    for(int i=0;i<x.size();i++){
      cout<<"About to apply ELT"<<endl;
      cout << tau << "\t" << arr[28][i]<<"\t"<<tau*arr[28][i]<<endl;
      cout << "Before y("<<i<<") = " << y.at(i);
      y.at(i)=y.at(i)/(1.-tau*arr[28][i]);
      cout << "\tAfter y("<<i<<") = " << y.at(i)<<endl;
      
      cout<<"About to subtract dummy"<<endl;
      cout << "Before y("<<i<<") = " << y.at(i);
      y.at(i)=y.at(i)-dumYield/dumScale;
      cout << "\tAfter y("<<i<<") = " << y.at(i)<<endl;
      }
  }
    ////////////////////////////////
    if(ycol==24 || ycol == 22 || ycol==20){//add ELT to Error
      for(int i=0;i<x.size();i++){
	double staterr=arr[ycol][i]/arr[ycol-1][i];
	double run=arr[0][i];
	double elte=getLivetime(run,"elte");
	double elt=getLivetime(run,"elt");
	double totalerr=sqrt(staterr*staterr+(elte/elt)*(elte/elt))*arr[ycol-1][i];
	y.at(i)=totalerr;
      }
    }
    ////////////////////////////////
    
  
  TGraph *gr=new TGraph(x.size(),&x[0],&y[0]);
  gr->SetMarkerStyle(25);
  gr->SetMarkerColor(kBlue);
  //    gr->Draw("ap")
  cout <<tau<<"ns\t"<< tgt << "\t" << spec << "\t"<<dumYield <<"\t"<<dumScale<<endl;  
  return gr;
  }
