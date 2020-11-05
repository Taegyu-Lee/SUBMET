#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TSystem.h"

void one_tree() {
    // making root file to save data in several trees
    TFile *f = new TFile("onetree.root","recreate");
    TTree *T = new TTree("oscilloscope","oscilloscope");
    
    vector<double> *time = 0;
    vector<double> *channel1 = 0;
    vector<double> *channel2 = 0;
    vector<double> *channel3 = 0;
    
    TBranch *time_0 = T->Branch("time",&time);
    TBranch *channel_1 = T->Branch("channel1",&channel1);
    TBranch *channel_2 = T->Branch("channel2",&channel2);
    TBranch *channel_3 = T->Branch("channel3",&channel3);
    
    double time1;
    double time2;
    double time3;
    double chan1;
    double chan2;
    double chan3;

    for (int i=0; i<7281; i++){ // 7281
        
        // create parent tree
        
        // name of the file which we want to open
        char ch1[1024];
        char ch2[1024];
        char ch3[1024];
        
        // inserting variables in char
        sprintf(ch1,"A_C1_%d.txt",i);
        sprintf(ch2,"A_C2_%d.txt",i);
        sprintf(ch3,"A_C3_%d.txt",i);
        
        // creating several tree ( time, channel1, channel2, channel3 )
        fstream file1;
        file1.open(ch1,ios::in);
        fstream file2;
        file2.open(ch2,ios::in);
        fstream file3;
        file3.open(ch3,ios::in);
        
        while(1)
        {
            file1 >> time1 >> chan1;
            file2 >> time2 >> chan2;
            file3 >> time3 >> chan3;
            
            time->push_back(time1);
            channel1->push_back(chan1);
            channel2->push_back(chan2);
            channel3->push_back(chan3);
            if(file1.eof()) break;
//            cout << time1 << " " << channel1 << " " << channel2 << " " << channel3 <<endl;
        }
        T->Fill();
        
        time->clear();
        channel1->clear();
        channel2->clear();
        channel3->clear();
        //cout << no << endl;
        
        // closing the file after opening
        
        
        file1.close();
        file2.close();
        file3.close();
       //delete f;
    }
    // write every thing in root file
    f->Write();
    f->Close();
}

