void read_tree2_select_event() {
    TFile *file = new TFile("area2.root","read");    // read root file that contain trees
    TTree *tree = (TTree *) file -> Get("area");     // read tree which we are interested
     
    int entries = tree->GetEntries(); // number of entries in the leaf
    
    // set each parameter to represent each leaf in the tree
    double ch1;
    tree -> SetBranchAddress("channel1_area",&ch1);
    double ch2;
    tree -> SetBranchAddress("channel2_area",&ch2);
    double ch3;
    tree -> SetBranchAddress("channel3_area",&ch3);
    
    vector<int> events;
    int no_event = 0;
    
    for(int i = 0; i < entries ; i++)
    {
        tree -> GetEntry(i);
        if(ch3 < -2*pow(10,-9))
        {
            no_event += 1;
            events.push_back(i);
        }
        else
        {
            no_event += 0;
        }
    }
    cout << "Number of signal events are " << no_event << " out of 7281 events." << endl;
    cout << "Outputs with voltage larger than -0.06 V are regarded as background noise." << endl;
    cout << "Total area larger than -2e-9 Vs are regarded as background noise." << endl;
    
    
    // cout << entries << endl;

    // Variables for plotting
//    double time[entries];
//    double channel1[entries];
//    double channel2[entries];
//    double channel3[entries];

    // one to one match from leaf data to variables
    vector<double> ch1_area;
    vector<double> ch2_area;
    vector<double> ch3_area;
    
    int j = 0;
    for(int i = 0 ; i < entries ; i++)
    {
        if(i == events[j])
        {
            tree->GetEntry(i);
            ch1_area.push_back(ch1);
            ch2_area.push_back(ch2);
            ch3_area.push_back(ch3);

            j += 1;
        }
        else
        {
            
        }
         // cout << t << " " << ch1 << " " << ch2 << " " << ch3 << endl;
    }
    file->Close();
    
    
    TCanvas *c1 = new TCanvas();

    gStyle->SetPalette(kRainBow);

    double min = -20.0*pow(10,-9);
    double max = 0.0;

    TH2D *hist = new TH2D("hist","histogram",50,min,max,50,min,max);


    TFile *file1 = new TFile("selected_area.root","recreate");
    TTree *T = new TTree("seleted_area","selected_area");
    
    double channel1_area, channel2_area, channel3_area; // variables that we need
    
    // Save data in leaf of the tree we made
    T->Branch("channel1_area",&channel1_area,"channel1_area/D");
    T->Branch("channel2_area",&channel2_area,"channel2_area/D");
    T->Branch("channel3_area",&channel3_area,"channel3_area/D");
    
    for(int i=0; i<no_event; i++)
    {
        channel1_area = ch1_area[i];
        channel2_area = ch2_area[i];
        channel3_area = ch3_area[i];
        hist->Fill(channel2_area,channel3_area);
        T->Fill();
    }
    file1->Write();
    hist->SetStats(0);
    
    hist->GetXaxis()->SetTitle("channel2_area");
    hist->GetYaxis()->SetTitle("channel3_area");
    hist->GetZaxis()->SetTitle("entries");

    hist->SetContour(1000);
    hist->Draw("colz");
    
//    file1->Close();
    
}
