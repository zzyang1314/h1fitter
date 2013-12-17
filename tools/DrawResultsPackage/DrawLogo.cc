#include "DrawLogo.h"

#include "logo.xpm"

#include <TImage.h>
#include <TLatex.h>
#include <TEnv.h>

#include <string>
#include <iostream>

#include <CommandParser.h>

using namespace std;
TPad * DrawLogo(string pos)
{
  string ver = VERSION;

  TImage *logo = TImage::Create();
  logo->SetImageBuffer(logo_xpm, TImage::kXpm);

  float dx = 0.1183 * 1.1;
  float dy = 0.0744 * 1.1;

  float x, y;
  x = 0.89;
  y = 0.89;
  if (pos == "dc")
    {
      x = 0.79;
      y = 0.12 + dy;
    }

  TPad * logopad = new TPad("logopad", "", x-dx, y-dy, x, y);
  if (!logo) 
    cout << "Error, Could not find logo" << endl;
  else
    {
      TString fp = gEnv->GetValue("Root.TTFontPath", "");
      TString bc = fp + "/BlackChancery.ttf";
      TString ar = fp + "/arial.ttf";

      logo->SetConstRatio(1);
      if (opts.version)
	logo->DrawText(500, 600, ver.c_str(), 200, 0, 
		       bc, TImage::kShadeBelow);
      logo->SetImageQuality(TAttImage::kImgBest);
      logopad->Draw();
      logopad->cd();
      logo->Draw("");
     }
  return logopad;
}

void CMS()
{
  TLatex l; //l.SetTextAlign(12);
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextSize(0.04);
  l.DrawLatex(lmarg+0.05, 0.91, "CMS");
}

void CMSpreliminary()
{
  TLatex l; //l.SetTextAlign(12);
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextSize(0.04);
  l.DrawLatex(lmarg+0.05, 0.91, "CMS Preliminary");
}

void ATLASpreliminary()
{
  TLatex p; 
  p.SetNDC();
  p.SetTextFont(42);
  p.SetTextSize(0.04);
  p.DrawLatex(lmarg+0.19, 0.85, "Preliminary");
}

void ATLAS()
{
  TLatex l; //l.SetTextAlign(12);
  l.SetNDC();
  l.SetTextFont(72);
  l.SetTextSize(0.04);
  l.DrawLatex(lmarg+0.05, 0.85, "ATLAS");
}

void ATLASinternal()
{
  TLatex p; 
  p.SetNDC();
  p.SetTextFont(42);
  p.SetTextSize(0.04);
  p.DrawLatex(lmarg+0.19, 0.85, "Internal");
}

//CDF Run II Preliminary
TPaveText * CDFIIpreliminary()
{
  TPaveText *cdfii = new TPaveText(0.45, 0.91, 0.95, 0.95, "NDC");
  cdfii->AddText("CDF Run II Preliminary");
  cdfii->SetTextAlign(12);
  cdfii->SetTextFont(62);
  cdfii->SetTextSize(0.04);
  cdfii->SetBorderSize(0);
  cdfii->SetFillColor(0);
  return cdfii;
}

void DrawLabels()
{
  if (opts.cms)
    CMS();
  if (opts.cmspreliminary)
    CMSpreliminary();
  if (opts.atlasinternal)
    {
      ATLAS();
      ATLASinternal();
    }
  else if (opts.atlaspreliminary)
    {
      ATLAS();
      ATLASpreliminary();
    }
  else if (opts.atlas)
    ATLAS();
  if (opts.cdfiipreliminary)
    CDFIIpreliminary()->Draw();
}
