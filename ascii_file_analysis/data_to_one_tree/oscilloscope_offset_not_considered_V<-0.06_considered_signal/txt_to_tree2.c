#include "TTree.h"
#include "TFile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TROOT.h"
#include <vector>
#include <iostream>

void txt_to_tree2() {
    // making root file to save data in several trees
    TFile *f = new TFile("area2.root","recreate");
    
    // create parent tree
    TTree *T = new TTree("area","area");
        
    fstream file;
    file.open("area2.txt",ios::in);
    
    double channel1_area, channel2_area, channel3_area; // variables that we need
    
    // Save data in leaf of the tree we made
    T->Branch("channel1_area",&channel1_area,"channel1_area/D");
    T->Branch("channel2_area",&channel2_area,"channel2_area/D");
    T->Branch("channel3_area",&channel3_area,"channel3_area/D");
    
    
    // Save data in leaf
    while(1)
    {
        file >> channel1_area >> channel2_area >> channel3_area;
        if(file.eof()) break;
//            cout << time1 << " " << channel1 << " " << channel2 << " " << channel3 <<endl;

        T->Fill();
    }
    
    // closing the file after opening
    file.close();
       //delete f;
    // write every thing in root file
    f->Write();
    f->Close();
}
