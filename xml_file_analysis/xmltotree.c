#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtod */

// Taegyu Lee
// This code is to convert xml file to TTree

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}  // replace function replace(string name, a, b) replace a to b

void xmltotree()
{
    for(int i = 0; i < 4; i++)
    {
        int input = 800+50*i;
        
        char rootname[1024];
        char filename[1024];
        sprintf(rootname,"drs_HV%d_ch1mid_ch2top_ch3bot_trigch23_200mv.root",input);
        sprintf(filename,"drs_HV%d_ch1mid_ch2top_ch3bot_trigch23_200mv.xml",input);
        
        TFile *f = new TFile(rootname,"recreate");
        TTree *T = new TTree("oscilloscope","oscilloscope");
        
        vector<double> *time = 0;
        vector<double> *channel1 = 0;
        vector<double> *channel2 = 0;
        vector<double> *channel3 = 0;
        
        TBranch *time_0 = T->Branch("time",&time);
        TBranch *channel_1 = T->Branch("channel1",&channel1);
        TBranch *channel_2 = T->Branch("channel2",&channel2);
        TBranch *channel_3 = T->Branch("channel3",&channel3);
        
        string time1, voltage;
        
        double time0, voltage0;
        
        TTree *T2 = new TTree("timing","timing");
        
        double timing;
        
        double hour;
        double minute;
        double second;
        
        T2->Branch("timing", &timing, "timing/D");
        
        ifstream drs(filename); // open xml file
        string line_drs;
        string trig = "not yet";
        
        vector<double> time_stamp;
        
        if(drs.is_open())
        {
            while(drs.good())
            {
                getline(drs, line_drs);
                
                string s(line_drs);

                replace(s, "<Data>", " <Data> "); // made to separate words
                replace(s, ",", " "); // comma to space
                replace(s, "</Data>", " </Data> "); // made to separate words
                
                string channel_no;
                string dummy;
                
                stringstream stream(s);
                
                stream >> channel_no >> time1 >> voltage >> dummy; // relavant for <Data> to </Data>
                
                if(channel_no == "<CHN1>")
                {
                    trig = "channel1";
                }
                else if(channel_no == "<CHN2>")
                {
                    trig = "channel2";
                }
                else if(channel_no == "<CHN3>")
                {
                    trig = "channel3";
                }
                else
                {
                    trig = trig;
                } // trig is made to trigger at each channel
                
                time0 = atof(time1.c_str());
                voltage0 = atof(voltage.c_str());
                
    //            cout << time0 << "   " << voltage0 << endl;
                if(trig == "channel1" && channel_no == "<Data>")
                {
                    time->push_back(time0);
                    channel1->push_back(voltage0);
                }
                else if(trig == "channel2" && channel_no == "<Data>")
                {
                    channel2->push_back(voltage0);
                }
                else if(trig == "channel3" && channel_no == "<Data>")
                {
                    channel3->push_back(voltage0);
                } // save values to each channel
                
                if(channel_no == "</CHN3>")
                {
                    T->Fill();
                    time->clear();
                    channel1->clear();
                    channel2->clear();
                    channel3->clear();
                } // </CHN3> means one event saving is finished. At this step we fill the tree and initialize every variable
                
                string t(line_drs);

                replace(t, "<Time>", " <Time> ");
                replace(t, "</Time>", " <Time> ");
                replace(t, ":", " ");

                string time_info1;
                string date_info;
                string hour_info;
                string minute_info;
                string second_info;
                string time_info2;

                stringstream tstream(t);

                tstream >> time_info1 >> date_info >> hour_info >> minute_info >> second_info >> time_info2;

                hour = atof(hour_info.c_str());
                minute = atof(minute_info.c_str());
                second = atof(second_info.c_str());

                if(time_info1 == "<Time>")
                {
                    timing = hour*3600 + minute*60 + second;
                    time_stamp.push_back(timing);
                    T2->Fill();
                }
                else
                {
                    continue;
                }
            }
        }
        
        double start = time_stamp[0] - 1000;
        double end = time_stamp[size(time_stamp)-1] + 1000;
        double division = (end-start)/180;
        
        TH1F *hist = new TH1F("hist", "Histogram", division, start, end);
        
        hist->SetStats(0);
        
        for(int i = 0 ; i < size(time_stamp) ; i++)
        {
             // cout << t << " " << ch1 << " " << ch2 << " " << ch3 << endl;
            hist->Fill(time_stamp[i]);
        }
        
        time_stamp.clear();
        
        drs.close();
        f->Write();
        f->Close();
    }
    
}
