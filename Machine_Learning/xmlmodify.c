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

void xmlmodify()
{
    ifstream drs("drs_HV800_ch1mid_ch2top_ch3bot_trigch23_20mv_better_optical_coupling.xml"); // open xml file
    ofstream modify("channel1_only_after_classification.xml");
    
    string line_drs;
    string trig = "not yet";
    if(drs.is_open())
    {
        while(drs.good())
        {
            getline(drs, line_drs);
            
            string s(line_drs);

//            replace(s, "<Data>", " <Data> "); // made to separate words
//            replace(s, ",", " "); // comma to space
//            replace(s, "</Data>", " </Data> "); // made to separate words

            string channel_no;
            string dummy;
            string time1;
            string voltage;

            stringstream stream(s);
            
//            cout << s << "   " << "byte: " << s.size() << endl;

            stream >> channel_no >> time1 >> voltage >> dummy; // relavant for <Data> to </Data>
            
            const char *s_char = s.c_str();
                        
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
            else if(channel_no == "</Event>")
            {
                trig = "not yet";
            }
            else
            {
                trig = trig;
            } // trig is made to trigger at each channel

            if(trig == "channel1" || trig == "not yet")
            {
                modify.write(s_char,s.size());
                modify << endl;
            }
            else
            {
                continue;
            }
////
//            time0 = atof(time1.c_str());
//            voltage0 = atof(voltage.c_str());
//
////            cout << time0 << "   " << voltage0 << endl;
//            if(trig == "channel1" && channel_no == "<Data>")
//            {
//                time->push_back(time0);
//                channel1->push_back(voltage0);
//            }
//            else if(trig == "channel2" && channel_no == "<Data>")
//            {
//                channel2->push_back(voltage0);
//            }
//            else if(trig == "channel3" && channel_no == "<Data>")
//            {
//                channel3->push_back(voltage0);
//            } // save values to each channel
//
//            if(channel_no == "</CHN3>")
//            {
//            } // </CHN3> means one event saving is finished. At this step we fill the tree and initialize every variable
        }
    }
    modify.close();
    drs.close();
//    f->Write();
//    f->Close();

    
}
