
Double_t fitf(Double_t *x, Double_t *par)
{
    Double_t fitval = par[4]*TMath::Gaus(x[0],par[0],par[2])*TMath::Gaus(x[1], par[1], par[3]);
    return fitval;
}

class MCSim
{
public:
    //constructor
     MCSim();
    ~MCSim();

    //accessors
    void SetParams(Double_t Mu_x, Double_t Mu_y, Double_t Sigma_x, Double_t Sigma_y, Double_t Ampl);
    void MakeMC();
    void DrawMC();


protected:
    Double_t mu_x, mu_y, sigma_x, sigma_y, ampl;
    TF2 *func2;
    TH2F* h2;

};

MCSim::MCSim()
{
    func2 = new TF2("func2", fitf, -4, 4,-4, 4, 5);
    h2 = new TH2F("h2","Two dimensional gaussian", 100,-6,6, 100, -6,6);
}

MCSim::~MCSim()
{
    std::cout << "MCSim destructor..." << endl;
    //delete func2;
    //delete h2
}


void MCSim::SetParams(Double_t Mu_x, Double_t Mu_y, Double_t Sigma_x, Double_t Sigma_y, Double_t Ampl)
{
  Double_t mu_x    = Mu_x;
  Double_t mu_y    = Mu_y;
  Double_t sigma_y = Sigma_y;
  Double_t sigma_x = Sigma_x;
  Double_t ampl    = Ampl;

  func2 ->SetParameters(mu_x,mu_y,sigma_x,sigma_y,ampl);
}


void MCSim::MakeMC()
{
    TRandom* ran;
    ran = new TRandom();

    ran->SetSeed(15);
    for(Int_t idx = 0; idx < 100; idx++)
    {
        Double_t x = ran->Gaus(0,0.5);
        Double_t y = ran->Gaus(0,0.5);
        printf("x: %4.3f, y: %4.3f  \n", x, y);
    }


    Double_t xvalue;
    Double_t yvalue;
    for(Int_t i = 0; i < 10000; i = i + 1)
    {
        xvalue = ran->Gaus(0.4,1.2);
        yvalue = ran->Gaus(0.4,1.2);

        h2 ->Fill(xvalue,yvalue);
    }

}

void MCSim::DrawMC()
{
    h2 ->SetStats(0);
    h2 ->GetXaxis()->SetTitle("x axis");
    h2 ->GetYaxis()->SetTitle("y axis");
    h2 ->SetMarkerStyle(kFullCircle);
    h2 ->Draw();
    h2->Fit(func2,"MN");
    func2 ->SetLineColor(kRed-0);
    func2 ->SetLineWidth(2);
    func2 ->SetLineStyle(8);
    func2 ->Draw("same");
}

void myfirstclass2()
{
    MCSim blubb;
    blubb.SetParams(1.2, 1.3, 1.4, 1.5, 1.6);
    blubb.MakeMC();
    blubb.DrawMC();


    return 0;
}