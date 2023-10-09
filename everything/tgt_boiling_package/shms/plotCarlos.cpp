TGraph* plotCarlos(int xcol=2,int ycol=25, string tgt="LD2"){


    int rows=0;
    if(tgt=="LH2")rows=8;
    if(tgt=="C12")rows=3;
    if(tgt=="LD2")rows=7;
    const int ncol=34;
    const int nrow=rows;
    double arr[ncol+1][nrow];
    string temp;
    double num;
    //    ifstream infile ("allYields.txt");
    ifstream infile (Form("shms_%s_yield.data",tgt.c_str()));
    /*
      for(int k=0;k<28;k++){
	getline(infile,temp);
	cout << k << "  "<<temp<<endl;
      }
    */
    for(int j=0;j<ncol;j++){
      infile >> temp;
      cout <<j<<"\t"<< temp<<endl;
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
    for(int i=0;i<nrow;i++){cout<<arr[0][i]<<endl;}
    for(int i=0;i<nrow;i++){arr[ncol][i]=arr[23][i]*arr[27][i]*arr[25][i]*arr[33][i];}
    vector <double> x;
    vector <double> y;
    for(int i=0;i<nrow;i++){x.push_back(arr[xcol][i]);}
    for(int i=0;i<nrow;i++){y.push_back(arr[ycol][i]);cout<<arr[2][i]<<"    "<<arr[ycol][i]<<endl;}
    TGraph *gr=new TGraph(x.size(),&x[0],&y[0]);
    gr->SetMarkerStyle(25);
    gr->SetMarkerColor(kBlue);
    //    gr->Draw("ap");
    return gr;
}
