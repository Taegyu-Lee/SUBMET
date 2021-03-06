void area_to_ascii() {
    TFile *file = new TFile("oscilloscope.root","read"); // read root file that contain trees
    
    double a,b;

    ofstream myfile;
    myfile.open ("area.txt");
    
    for(int i = 0;  i < 7281; i++)
    {
        char eventno[1024];
        sprintf(eventno,"event%d",i+1);
        
        TTree *tree = (TTree *) file -> Get(eventno);     // read tree which we are interested
         
        int entries = tree->GetEntries(); // number of entries in the leaf
        // cout << entries << endl;
        
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

        double channel1_area = 0.0;
        double channel2_area = 0.0;
        double channel3_area = 0.0;

        
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
        double dt = (time[entries-1] - time[0])/entries;
        
        for(int i = 0; i < entries ; i ++)
        {
            if(channel1[i] < -0.06)
            {
                channel1_area += channel1[i]*dt;
            }
            else
            {
                channel1_area += 0.0;
            }
            if(channel2[i] < -0.06)
            {
                channel2_area += channel2[i]*dt;
            }
            else
            {
                channel2_area += 0.0;
            }
            if(channel3[i] < -0.06)
            {
                channel3_area += channel3[i]*dt;
            }
            else
            {
                channel3_area += 0.0;
            }
        }
        myfile << channel1_area << " " << channel2_area << " " << channel3_area << "\n";
        // cout << channel1_area << "  " << channel2_area << "  " << channel3_area << endl;
        cout << channel1_area << " " << channel2_area << " " << channel3_area << endl;
    }
    
    myfile.close();
//    file->Write();
//    file->Close();
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
