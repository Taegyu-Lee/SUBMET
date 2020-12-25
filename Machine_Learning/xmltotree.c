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
    TFile *f = new TFile("channel1_only.root","recreate");
    TTree *T = new TTree("oscilloscope","oscilloscope");
    
    vector<double> *time = 0;
    vector<double> *channel1 = 0;
    
    TBranch *time_0 = T->Branch("time",&time);
    TBranch *channel_2 = T->Branch("channel1",&channel1);
    
    string time1, voltage;
    
    double time0, voltage0;
    
    ifstream drs("channel1_only.xml"); // open xml file
    string line_drs;
    string trig = "not yet";
    if(drs.is_open())
    {
        while(drs.good())
        {
            getline(drs, line_drs);
            
            string s(line_drs);
            
            string channel_no;
            string dummy;
            
            stringstream stream(s);
            
            stream >> channel_no >> time1 >> voltage >> dummy; // relavant for <Data> to </Data>
            
            if(channel_no == "<CHN1>")
            {
                trig = "channel1";
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
            
            if(channel_no == "</CHN1>")
            {
                T->Fill();
                time->clear();
                channel1->clear();
            } // </CHN3> means one event saving is finished. At this step we fill the tree and initialize every variable
        }
    }
    
    drs.close();
    f->Write();
    f->Close();

    
}
