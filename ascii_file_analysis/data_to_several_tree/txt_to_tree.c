#include "TTree.h"
#include "TFile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TROOT.h"
#include <vector>
#include <iostream>

void txt_to_tree() {
    // making root file to save data in several trees
    TFile *f = new TFile("oscilloscope.root","recreate");
    
    for (int i=0; i<7281; i++){
        
        // create parent tree
        
        // name of the file which we want to open
        char ch1[1024];
        char ch2[1024];
        char ch3[1024];
        
        // inserting variables in char
        sprintf(ch1,"A_C1_%d.txt",i);
        sprintf(ch2,"A_C2_%d.txt",i);
        sprintf(ch3,"A_C3_%d.txt",i);
        
        // name of the tree
        char eventno[1024];
        sprintf(eventno,"event%d",i+1);
        
        
        // creating several tree ( time, channel1, channel2, channel3 )
        TTree *T = new TTree(eventno,eventno);
        fstream file1;
        file1.open(ch1,ios::in);
        fstream file2;
        file2.open(ch2,ios::in);
        fstream file3;
        file3.open(ch3,ios::in);

        double time2, time3; // dummy variable
        double time1, channel1, channel2, channel3; // variables that we need
        
        // Save data in leaf of the tree we made
        T->Branch("time",&time1,"time1/D");
        T->Branch("channel1",&channel1,"channel1/D");
        T->Branch("channel2",&channel2,"channel2/D");
        T->Branch("channel3",&channel3,"channel3/D");
        
        
        // Save data in leaf
        while(1)
        {
            file1 >> time1 >> channel1;
            file2 >> time2 >> channel2;
            file3 >> time3 >> channel3;
            if(file1.eof()) break;
//            cout << time1 << " " << channel1 << " " << channel2 << " " << channel3 <<endl;

            T->Fill();
        }
        
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
