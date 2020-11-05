void read_tree() {
    TFile *file = new TFile("onetree.root","read"); // read root file that contain trees
    TTree *tree = (TTree *) file -> Get("event");     // read tree which we are interested

    int entries = tree->GetEntries(); // number of entries in the leaf
    cout << entries << endl;
//    int entries = 10;
    // set each parameter to represent each leaf in the tree
    vector<double> *fourvec = 0;
    tree -> SetBranchAddress("event1",&fourvec);

    // cout << entries << endl;
    
    // Variables for plotting
    vector<double> time;
    vector<double> channel1;
    vector<double> channel2;
    vector<double> channel3;
    
//    double channel1[entries];
//    double channel2[entries];
//    double channel3[entries];
    

    
    // one to one match from leaf data to variables
    for(int i = 0 ; i < entries ; i++)
    {
        tree -> GetEntry(i);
//        cout << fourvec->at(1) << 2 << endl;
//        for (int j=0; j<fourvec->size(); ++j) {
//            std::cout << "evt " << i << " var2[" << j << "]: " << fourvec->at(j) << std::endl;
//        }
//        time.push_back(i);
//        channel2.push_back(i*i);
//        time.push_back(fourvec[0]);
//        channel1.push_back(fourvec[1]);
//        channel2.push_back(fourvec[2]);
        //channel3.push_back(fourvec[3]);

    }
//    TGraph *g = new TGraph(entries, &time[0], &channel2[0]);
//    g->Draw("AL");
//
//    // Plotting
//
//    // making new TGraphs
//    TGraph *gr1 = new TGraph(entries,time,channel1);
//    TGraph *gr2 = new TGraph(entries,time,channel2);
//    TGraph *gr3 = new TGraph(entries,time,channel3);
//
//    // making multigraph to merge the graphs
//    TMultiGraph *mg = new TMultiGraph();
//
//    // making new canvas
//    TCanvas *c1 = new TCanvas();
//
//    // Legend
//    gr1->SetTitle("Channel 1");
//    gr2->SetTitle("Channel 2 (trigger)");
//    gr3->SetTitle("Channel 3");
//
//    // Color
//    gr1->SetLineColor(kGreen);
//    gr2->SetLineColor(kRed);
//    gr3->SetLineColor(kBlue);
//
//    // merging graphs
//    mg->Add(gr1);
//    mg->Add(gr2);
//    mg->Add(gr3);
//
//    // title
//    mg->SetTitle("Oscilloscope; time (s); voltage (V)");
//
//    //draw
//    mg->Draw("ACP");
//
//    // Legend
//    c1->BuildLegend();

}
