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

void mean_area_time_voltage_offset_dark_current()
{   TFile *f = new TFile("area_signal_time_voltage_correction_time_-5_5.root","recreate");
    f->Close();
    for(int i = 0; i < 4; i++)
    {
        int input = 1300+50*i;
        
        char rootname[1024];
        char treename[1024];
        char histname1[1024];
        char histname2[1024];
        char histname3[1024];
        sprintf(rootname,"drs_HV%d_ch1mid_trigch1_6mv.root",input);
        sprintf(treename,"Area_HV%d",input);
        
        sprintf(histname1,"Area_HV%d_channel1",input);

        TFile *file = new TFile(rootname,"read"); // read root file that contain trees
        
        TFile *file2 = new TFile("area_signal_time_voltage_correction_time_-5_5.root","update"); // updating root file (adding new trees)
        
        TTree *T = new TTree(treename,treename);
        
        double channel1_area;
        
        double ch1_offset;

        double trigger_i;
        
        T->Branch("channel1_area", &channel1_area, "channel1_area/D");
        
        double a,b;
        
        vector<double> ch1_area;

        TTree *tree = (TTree *) file -> Get("oscilloscope");

        vector<double> *t = 0;
        tree -> SetBranchAddress("time",&t);
        vector<double> *ch1 = 0;
        tree -> SetBranchAddress("channel1",&ch1);
        
        int entries = tree->GetEntries(); // number of entries in the leaf

        for(int i = 0;  i < entries; i++)
        {
            
            tree -> GetEntry(i);
            
            vector<double>& time = *t;
            vector<double>& channel1 = *ch1;

            double dt;
//            cout << dt << endl;
            dt = (time[time.size()-1]-time[0])/time.size();

            channel1_area = 0;

            trigger_i = 0;
            ch1_offset = 0;
            // time shift compensation
            if( -5 < time[0] && time[0] < 5 )
            {   
                for(int i = 0; i < channel1.size(); i++)
                {
                    if(time[i] < 200)
                    {
                        ch1_offset += channel1[i];
                        trigger_i += 1;
                    }
                    else
                    {
                        break;
                    }
                    
                }
                // cout << ch1_offset << endl;
                ch1_offset = ch1_offset/trigger_i;
                cout << ch1_offset << endl;
                for(int i = 0; i < channel1.size(); i++)
                {   
                    {
                        if(220 < time[i] && time[i] < 240)
                        {
                            channel1_area += (channel1[i] - ch1_offset)*dt;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                T->Fill();
            
                ch1_area.push_back(channel1_area);                
            }
            else
            {
                continue;
            }
            
            
        }
        
        double avg_ch1_area = avg(ch1_area);
        
        double std_ch1_area = sqrt(variance(ch1_area, avg_ch1_area));
        
    //    //choose the histgram range 
    //    double start_1  = *min_element(ch1_area.begin(), ch1_area.end()) - 1000;
    //    double end_1    = *max_element(ch1_area.begin(), ch1_area.end()) + 2000;
    //    cout << "start is " << start_1 << endl;
        double division = 30;
        
        TH1F *hist1 = new TH1F(histname1,histname1,division, -100, 10);

        
        for(int i = 0 ; i < size(ch1_area) ; i++)
        {
             // cout << t << " " << ch1 << " " << ch2 << " " << ch3 << endl;
            hist1->Fill(ch1_area[i]);

        }
        
        hist1->SetTitle(treename);
        hist1->GetXaxis()->SetTitle("e-12 Vs");
        hist1->GetYaxis()->SetTitle("Number of Events");

        T->Fill();
        file2->Write();
        file2->Close();
        
        cout << treename << endl;
        cout << "Area of Channel1 = " << avg_ch1_area << " +- " << std_ch1_area << " (e-12 Vs) "<< endl;
        cout << "                   " << endl;
        
        ch1_area.clear();

    }
}
