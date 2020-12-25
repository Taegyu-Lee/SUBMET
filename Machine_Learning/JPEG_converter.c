void JPEG_converter()
{

    TFile *file = new TFile("channel1_only.root","read"); // read root file that contain trees

    TTree *tree = (TTree *) file -> Get("oscilloscope");

    int entries = tree->GetEntries(); // number of entries in the leaf
    cout << entries << endl;
    for(int i = 0;  i < 100; i++)
    {   
        int no = i;
        TCanvas *c = new TCanvas;

        char picturename[1024];
        sprintf(picturename,"/Users/taegyulee/desktop/data/danny/modify/jpeg_sample/picture%d.jpeg",no);

        char entry_no[1024];
        sprintf(entry_no,"Entry$ == %i",no);

        tree->Draw("channel1:time",entry_no,"L");
        TH2F *htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("");

//        htemp->GetXaxis()->SetTickLength(0);
//        htemp->GetYaxis()->SetTickLength(0);
//
//        htemp->GetXaxis()->SetTitle("");
//        htemp->GetYaxis()->SetTitle("");
//
//        htemp->GetXaxis()->SetLabelSize(0);
//        htemp->GetYaxis()->SetLabelSize(0);
        // htemp->GetXaxis()->SetLabelOffset(999);

        // c->SetTitle("");
        c->SaveAs(picturename);
        c->Close();
    }
    file->Close();
}
