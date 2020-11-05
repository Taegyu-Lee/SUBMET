void read_tree() {
    TFile *file = new TFile("oscilloscope.root","read"); // read root file that contain trees
    TTree *tree = (TTree *) file -> Get("event7275");     // read tree which we are interested
     
    int entries = tree->GetEntries(); // number of entries in the leaf
    
    // set each parameter to represent each leaf in the tree
    double t;
    tree -> SetBranchAddress("time",&t);
    double ch1;
    tree -> SetBranchAddress("channel1",&ch1);
    double ch2;
    tree -> SetBranchAddress("channel2",&ch2);
    double ch3;
    tree -> SetBranchAddress("channel3",&ch3);
    
    // cout << entries << endl;
    
    // Variables for plotting
    double time[entries];
    double channel1[entries];
    double channel2[entries];
    double channel3[entries];
    
    // one to one match from leaf data to variables
    for(int i = 0 ; i < entries ; i++)
    {
    	 tree -> GetEntry(i);
         // cout << t << " " << ch1 << " " << ch2 << " " << ch3 << endl;
         time[i] = t;
         channel1[i] = ch1;
         channel2[i] = ch2;
         channel3[i] = ch3;
        
    }
    
    // Plotting
    
    // making new TGraphs
    TGraph *gr1 = new TGraph(entries,time,channel1);
    TGraph *gr2 = new TGraph(entries,time,channel2);
    TGraph *gr3 = new TGraph(entries,time,channel3);
    
    // making multigraph to merge the graphs
    TMultiGraph *mg = new TMultiGraph();
    
    // making new canvas
    TCanvas *c1 = new TCanvas();
    
    // Legend
    gr1->SetTitle("Channel 1");
    gr2->SetTitle("Channel 2 (trigger)");
    gr3->SetTitle("Channel 3");
    
    // Color
    gr1->SetLineColor(kGreen);
    gr2->SetLineColor(kRed);
    gr3->SetLineColor(kBlue);
    
    // merging graphs
    mg->Add(gr1);
    mg->Add(gr2);
    mg->Add(gr3);
    
    // title
    mg->SetTitle("Oscilloscope; time (s); voltage (V)");
    
    //draw
    mg->Draw("ACP");
    
    // Legend
    c1->BuildLegend();

}
