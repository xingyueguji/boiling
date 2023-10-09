TGraph* plotCarlos(int xcol=2,int ycol=25, string tgt="LD2",string spec="shms"){

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
  /*
  //	  cout << endl;
  //	  i++;
  //          if(ycol==19 && spec=="shms")dumYield=6521.10; 
  //      if(ycol==19 && spec=="shms")dumYield=2132.51; 
  if(ycol==19 && spec=="shms")dumYield=2137.02;//new replay 


             if(ycol==21 && spec=="shms")dumYield=1367.28; 
      //      if(ycol==21 && spec=="shms")dumYield=1367.12; //tof_tolerance 3ns
	  //  if(ycol==21 && spec=="shms")dumYield=1370.01; //new replay
    //      if(ycol==21 && spec=="shms")dumYield=1362.03; //cer>10
    //      if(ycol==21 && spec=="shms")dumYield=1383.35; //remove cal
    //if(ycol==21 && spec=="shms")dumYield=869.45; //add good scin hit

    //            if(ycol==23 && spec=="shms")dumYield=638.238; 
	     if(ycol==23 && spec=="shms")dumYield=623.708; //cer cut//A
	  //                        if(ycol==23 && spec=="shms")dumYield=624.74; //new replay
	     //                        if(ycol==23 && spec=="shms")dumYield=421.14; //new replay tight delta
    //            if(ycol==23 && spec=="shms")dumYield=622.435; //cer>10
    //	    if(ycol==23 && spec=="shms")dumYield=624.74; //TOF TOLERANCE 3NS
    //	    if(ycol==23 && spec=="shms")dumYield=626.7; //track2021
    //            if(ycol==23 && spec=="shms")dumYield=1654.03; //remove calCut
    //      if(ycol==23 && spec=="shms")dumYield=623.83; //eprtracknorm cut
    //      if(ycol==23 && spec=="shms")dumYield=623.67; // add inside dipole
    //      if(ycol==23 && spec=="shms")dumYield=593.29; // add good scin hit


      if(ycol==19 && spec=="hms")dumYield=822.56; //el clean
      //      if(ycol==19 && spec=="hms")dumYield=1505.15; 
      //      if(ycol==21 && spec=="hms")dumYield=690.458; 
      //      if(ycol==21 && spec=="hms")dumYield=684.387;//tight
      //      if(ycol==21 && spec=="hms")dumYield=689.832;//wide
            if(ycol==21 && spec=="hms")dumYield=685.93;//wide+mo' cuts
      //if(ycol==21 && spec=="hms")dumYield=686.63;//remove calCut
      //      if(ycol==23 && spec=="hms")dumYield=534.810; 
      //      if(ycol==23 && spec=="hms")dumYield=514.173; //tight
      //      if(ycol==23 && spec=="hms")dumYield=518.374; //wide
            if(ycol==23 && spec=="hms")dumYield=517.16; //wide+mo cuts
      //      if(ycol==23 && spec=="hms")dumYield=746.34; //remove calCut
      //      if(ycol==23 && spec=="hms")dumYield=518.853; //with cer
      //      if(ycol==21 && spec=="hms")dumYield=682.25; //yeroCalCut
      //      if(ycol==23 && spec=="hms")dumYield=528.38; //yeroCalCut
      //      if(ycol==21 && spec=="hms")dumYield=684.72; //carlos
      //      if(ycol==23 && spec=="hms")dumYield=530.10; //carlos
      //if(ycol==21 && spec=="hms")dumYield=687.62; //carlos + mycal
      //if(ycol==23 && spec=="hms")dumYield=533.47; //carlos + mycal
      //      if(ycol==21 && spec=="hms")dumYield=684.72; //carlos + 2blocks fix
      //      if(ycol==23 && spec=="hms")dumYield=530.1; //carlos +  2blocks if
  */
  if(spec=="shms")dumYield=dumYield/.9979;
  if(spec=="hms")dumYield=dumYield/.9996;
  dumYield=0.;
  cout << tgt << "\t" << spec << "\t"<<dumYield <<"\t"<<dumScale<<endl;  
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
    //    ifstream infile ("allYields.txt");
    //    ifstream infile (Form("data_carlos_replay_with_my_cal/%s_%s_yield.data",spec.c_str(),tgt.c_str()));
    //    ifstream infile (Form("data_remove_calCut/%s_%s_yield.data",spec.c_str(),tgt.c_str()));
    ifstream infile (Form("%s_%s_yield.data",spec.c_str(),tgt.c_str()));
    /*
      for(int k=0;k<28;k++){
	getline(infile,temp);
	cout << k << "  "<<temp<<endl;
      }
    */
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
    //    while(!infile.eof()){
          for(int j=0;j<ncol;j++){
	    infile>>num;
	    //	    cout << num <<"\t";
	    arr[j][i]=num;
	  }
	  //	  cout << endl;
	  //	  i++;
    }
	//    for(int i=0;i<nrow;i++){cout<<arr[0][i]<<endl;}
    for(int i=0;i<nrow;i++){arr[ncol][i]=arr[23][i]*arr[27][i]*arr[25][i]*arr[33][i];}//work backwards to get raw yield
    vector <double> x;
    vector <double> y;
    double tau;
    if(spec=="shms")tau=37.1E-9;
    if(spec=="hms")tau=23.8E-9;
      tau=0;


	for(int i=0;i<nrow;i++){
	  //	  	  if(tgt!="LD2" || arr[1][i]<65.)
	  {
	    x.push_back(arr[xcol][i]);
	    y.push_back(arr[ycol][i]);
	  }
	}
	
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
    /*
    if(ycol==21){ //nontrack yield subtract dummy
      for(int i=0;i<nrow;i++){
	cout << "Before y("<<i<<") = " << y.at(i);
	y.at(i)=y.at(i)-1367.28/dumScale;
	cout << "\tAfter y("<<i<<") = " << y.at(i)<<endl;
      }
    }

    if(ycol==19){ //scaler yield subtract dummy
      for(int i=0;i<nrow;i++){
	cout << "Before y("<<i<<") = " << y.at(i);
	y.at(i)=y.at(i)-6521.1/dumScale;
	cout << "\tAfter y("<<i<<") = " << y.at(i)<<endl;
      }
    }
    */

    TGraph *gr=new TGraph(x.size(),&x[0],&y[0]);
    gr->SetMarkerStyle(25);
    gr->SetMarkerColor(kBlue);
    //    gr->Draw("ap");
    return gr;
}
