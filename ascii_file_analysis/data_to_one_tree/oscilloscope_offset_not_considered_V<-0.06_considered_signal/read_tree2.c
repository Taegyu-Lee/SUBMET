void read_tree2() {
    TFile *file = new TFile("area2.root","read"); // read root file that contain trees
    TTree *tree = (TTree *) file -> Get("area");     // read tree which we are interested
     
    int entries = tree->GetEntries(); // number of entries in the leaf
    
    // set each parameter to represent each leaf in the tree
    double ch1;
    tree -> SetBranchAddress("channel1_area",&ch1);
    double ch2;
    tree -> SetBranchAddress("channel2_area",&ch2);
    double ch3;
    tree -> SetBranchAddress("channel3_area",&ch3);
    
    // cout << entries << endl;
    
    TCanvas *c1 = new TCanvas();
    
    gStyle->SetPalette(kRainBow);
    
    double min = -20.0*pow(10,-9);
    double max = 10.0*pow(10,-9);

    TH2D *hist = new TH2D("hist","histogram",100,min,max,100,min,max);
    
    hist->SetStats(0);
    
    // Variables for plotting
//    double time[entries];
//    double channel1[entries];
//    double channel2[entries];
//    double channel3[entries];
    
    // one to one match from leaf data to variables
    for(int i = 0 ; i < entries ; i++)
    {
        tree -> GetEntry(i);
         // cout << t << " " << ch1 << " " << ch2 << " " << ch3 << endl;
        hist->Fill(ch2,ch3);
    }
    hist->GetXaxis()->SetTitle("channel2_area");
    hist->GetYaxis()->SetTitle("channel3_area");
    hist->GetZaxis()->SetTitle("entries");
    
    hist->SetContour(1000);
    hist->Draw("colz");
}
