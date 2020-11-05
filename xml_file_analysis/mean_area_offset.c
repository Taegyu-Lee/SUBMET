//Function for average
double avg ( vector<double> &v )
{
        double return_value = 0.0;
        int n = v.size();
       
        for ( int i=0; i < n; i++)
        {
            return_value += v[i];
        }
       
        return ( return_value / v.size());
}
//****************End of average funtion****************

//Function for variance
double variance ( vector<double> &v , double mean )
{
        double sum = 0.0;
        double temp;
        double var;
       
        int n = v.size();
    
        for ( int j =0; j < n; j++)
        {
            temp = pow((v[j] - mean),2);
            sum += temp;
        }
       
        return var = sum/v.size();
}
//****************End of variance funtion****************

void mean_area_offset()
{   TFile *f = new TFile("area_offset_cancel.root","recreate");
    f->Close();
    for(int i = 0; i < 4; i++)
    {
        int input = 800+50*i;
        
        char rootname[1024];
        char treename[1024];
        char histname1[1024];
        char histname2[1024];
        char histname3[1024];
        sprintf(rootname,"drs_HV%d_ch1mid_ch2top_ch3bot_trigch23_200mv.root",input);
        sprintf(treename,"Area_HV%d",input);
        
        sprintf(histname1,"Area_HV%d_channel1",input);
        sprintf(histname2,"Area_HV%d_channel2",input);
        sprintf(histname3,"Area_HV%d_channel3",input);

        TFile *file = new TFile(rootname,"read"); // read root file that contain trees
        
        TFile *file2 = new TFile("area_offset_cancel.root","update");
        
        TTree *T = new TTree(treename,treename);
        
        double channel1_area;
        double channel2_area;
        double channel3_area;
        
        double ch1_offset;
        double ch2_offset;
        double ch3_offset;
        double trigger_i;
        
        T->Branch("channel1_area", &channel1_area, "channel1_area/D");
        T->Branch("channel2_area", &channel2_area, "channel2_area/D");
        T->Branch("channel3_area", &channel3_area, "channel3_area/D");
        
        double a,b;
        
        vector<double> ch1_area;
        vector<double> ch2_area;
        vector<double> ch3_area;
        
//        vector<double> channel1_area_offset;
//        vector<double> channel2_area_offset;
//        vector<double> channel3_area_offset;

    //    ofstream myfile;
    //    myfile.open ("area.txt");
        // set each parameter to represent each leaf in the tree
        

        TTree *tree = (TTree *) file -> Get("oscilloscope");

        vector<double> *t = 0;
        tree -> SetBranchAddress("time",&t);
        vector<double> *ch1 = 0;
        tree -> SetBranchAddress("channel1",&ch1);
        vector<double> *ch2 = 0;
        tree -> SetBranchAddress("channel2",&ch2);
        vector<double> *ch3 = 0;
        tree -> SetBranchAddress("channel3",&ch3);
        
    //    vector<double> a10;
    //    for(int i = 0; i < 10; i++)
    //    {
    //        a10.push_back(i);
    //    }
    //
    //    cout << a10[1] << " go "<< *&a10[1] <<endl;

    //    cout << rows << endl;
        //
        int entries = tree->GetEntries(); // number of entries in the leaf
    //    cout << entries << endl;
    //    cout << typeid(t).name() << endl;
    //    cout << typeid(time).name() << endl;

        for(int i = 0;  i < entries; i++)
        {
            // cout << entries << endl;

            // cout << entries << endl;
            // Variables for plotting
    //        vector<double> time;
    //        vector<double> channel1;
    //        vector<double> channel2;
    //        vector<double> channel3;
    //        double aj;
            
            tree -> GetEntry(i);
            
            vector<double>& time = *t;
            vector<double>& channel1 = *ch1;
            vector<double>& channel2 = *ch2;
            vector<double>& channel3 = *ch3;

            double dt;
//            cout << dt << endl;
            dt = (time[time.size()-1]-time[0])/time.size();

            channel1_area = 0;
            channel2_area = 0;
            channel3_area = 0;
            
            ch1_offset = 0;
            ch2_offset = 0;
            ch3_offset = 0;
            trigger_i = 0;
            
            for(int i = 0; i < channel1.size(); i++)
            {
                if(time[i] < 250)
                {
                ch1_offset += channel1[i];
                ch2_offset += channel2[i];
                ch3_offset += channel3[i];
                trigger_i += 1;
                }
                else
                {
                    break;
                }
                
            }
//            cout << trigger_i << endl;
            ch1_offset = ch1_offset/trigger_i;
            ch2_offset = ch2_offset/trigger_i;
            ch3_offset = ch3_offset/trigger_i;
            
            for(int i = 0; i < channel1.size(); i++)
            {
                channel1_area += (channel1[i] - ch1_offset)*dt;
                channel2_area += (channel2[i] - ch2_offset)*dt;
                channel3_area += (channel3[i] - ch3_offset)*dt;
            }
            T->Fill();
            
            ch1_area.push_back(channel1_area);
            ch2_area.push_back(channel2_area);
            ch3_area.push_back(channel3_area);
            
    //        myfile << channel1_area << " " << channel2_area << " " << channel3_area << "\n";
    //
    //         cout << channel1_area << "  " << channel2_area << "  " << channel3_area << endl;
        }
        
        double avg_ch1_area = avg(ch1_area);
        double avg_ch2_area = avg(ch2_area);
        double avg_ch3_area = avg(ch3_area);
        
        double std_ch1_area = sqrt(variance(ch1_area, avg_ch1_area));
        double std_ch2_area = sqrt(variance(ch2_area, avg_ch2_area));
        double std_ch3_area = sqrt(variance(ch3_area, avg_ch3_area));
        
        
//        double start_1  = *min_element(ch1_area.begin(), ch1_area.end()) - 1000;
//        double end_1    = *max_element(ch1_area.begin(), ch1_area.end()) + 2000;
////        cout << "start is " << start_1 << endl;
//        double start_23 = *min_element(ch2_area.begin(), ch2_area.end()) - 1000;
//        double end_23   = *max_element(ch2_area.begin(), ch2_area.end()) + 2000;
        double division = 200;
        
        TH1F *hist1 = new TH1F(histname1,histname1,division, -10000, 1000);
        TH1F *hist2 = new TH1F(histname2,histname2,division, -20000, -1000);
        TH1F *hist3 = new TH1F(histname3,histname3,division, -20000, -1000);
        
        for(int i = 0 ; i < size(ch2_area) ; i++)
        {
             // cout << t << " " << ch1 << " " << ch2 << " " << ch3 << endl;
            hist1->Fill(ch1_area[i]);
            hist2->Fill(ch2_area[i]);
            hist3->Fill(ch3_area[i]);
        }
        
        T->Fill();
        file2->Write();
        file2->Close();
        
        cout << treename << endl;
        cout << "Area of Channel1 = " << avg_ch1_area << " +- " << std_ch1_area << " (e-12 Vs) "<< endl;
        cout << "Area of Channel2 = " << avg_ch2_area << " +- " << std_ch2_area << " (e-12 Vs) "<< endl;
        cout << "Area of Channel3 = " << avg_ch3_area << " +- " << std_ch3_area << " (e-12 Vs) "<< endl;
        cout << "                   " << endl;
        
        ch1_area.clear();
        ch2_area.clear();
        ch3_area.clear();

    }
}
