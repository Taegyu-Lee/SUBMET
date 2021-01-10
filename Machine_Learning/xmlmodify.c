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
            else if(channel_no == "</Board_2972>")
            {
                trig = "not yet";
            }
            else if(channel_no == "</DRSOSC>")
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
        }
    }
    modify.close();
    drs.close();
//    f->Write();
//    f->Close();

    
}
