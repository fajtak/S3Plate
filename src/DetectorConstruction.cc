//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: DetectorConstruction.cc,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UniformMagField.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "G4ThreeVector.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "globals.hh"

#include "G4MaterialPropertiesTable.hh"
#include <iostream>
#include <fstream>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{
  // materials
  DefineMaterials();

  // create commands for interactive definition of the calorimeter
  detectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete detectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{

    // or use G4-NIST materials data base
    //
    G4NistManager* man = G4NistManager::Instance();
    aluminiumMaterial = man->FindOrBuildMaterial("G4_Al");
    airMaterial = man->FindOrBuildMaterial("G4_AIR");
    mylar = man->FindOrBuildMaterial("G4_MYLAR");
    //teflon = man->FindOrBuildMaterial("G4_TEFLON");
    borGlass = man->FindOrBuildMaterial("G4_Pyrex_Glass");

    G4double a, z, density;

    G4int polyeth = 1;
    G4int nC_eth = 2*polyeth;
    G4int nH_eth = 4*polyeth;

    G4Element* H  = new G4Element("Hydrogen","H",z=1.,a=1.01*g/mole);
    G4Element* C  = new G4Element("Carbon","C", z=6.,a=12.01*g/mole);
    G4Element* N = new G4Element("N", "N", z=7., a= 14.01*g/mole);
    G4Element* O = new G4Element("O"  , "O", z=8., a= 16.00*g/mole);
    G4Element* F  = man->FindOrBuildElement("F");

    scintilator = new G4Material("Scint", density= 1.03*g/cm3, 2);
    scintilator->AddElement(C, 0.475);
    scintilator->AddElement(H, 0.525);

    Pstyrene = new G4Material("Polystyrene", density= 1.03*g/cm3, 2);
    Pstyrene->AddElement(C, 8);
    Pstyrene->AddElement(H, 8);
    //Cladding(PMMA)
    PMMA = new G4Material("PMMA", density=1190*kg/m3,3);
    PMMA->AddElement(H,0.533);
    PMMA->AddElement(C,0.336);
    PMMA->AddElement(O,0.131);
    //Double cladding(flourinated polyethylene)
    fPethylene = new G4Material("fPethylene", density=1430*kg/m3,2);
    fPethylene->AddElement(H,nH_eth);
    fPethylene->AddElement(C,nC_eth);

    teflon = new G4Material("TeflonMat", density= 0.2*g/cm3, 2);
    teflon->AddElement(C, 2);
    teflon->AddElement(F, 4);

    // print table
    //
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

    const G4int nEntries = 2;

    G4double PhotonEnergy[nEntries] =
            { 1.7*eV, 7.136*eV };

    G4double RefractiveIndex2[nEntries] =
        { 1.00, 1.00 };

    G4double RefractiveIndex3[nEntries] =
        { 1.315, 1.315};

    G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
    myMPT2->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex2, nEntries);

    G4MaterialPropertiesTable* myMPT3 = new G4MaterialPropertiesTable();
    myMPT3->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex3, nEntries);

    airMaterial->SetMaterialPropertiesTable(myMPT2);
    teflon->SetMaterialPropertiesTable(myMPT3);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    WorldSizeXY = 1.0*m;
    WorldSizeZ = 1.0*m;
    //
    // World
    //
    solidWorld = new G4Box("World",				//its name
                   WorldSizeXY/2,WorldSizeXY/2,WorldSizeZ/2);	//its size

    logicWorld = new G4LogicalVolume(solidWorld,		//its solid
                                   airMaterial,	//its material
                                   "World");		//its name

    physiWorld = new G4PVPlacement(0,			//no rotation
                 G4ThreeVector(),	//at (0,0,0)
                                 logicWorld,		//its logical volume
                                 "World",		//its name
                                 0,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number

    detX = 200.0*cm;
    detY = 20.0*cm;
    detZ = 1.0*cm;

    double teflonX = detX + 2*800.0*um;
    double teflonY = detY + 2*800.0*um;
    double teflonZ = detZ + 2*800.0*um;

    G4Box* teflon_box = new G4Box("teflon_box", teflonX/2, teflonY/2, teflonZ/2);
    G4LogicalVolume* teflon_log = new G4LogicalVolume(teflon_box, teflon, "teflon_log", 0,0,0);
    G4PVPlacement* teflon_phys = new G4PVPlacement(0, G4ThreeVector(0,0,0), teflon_log, "Teflon", logicWorld, false, 0);

    G4Box* det_box = new G4Box("det_box", detX/2, detY/2, detZ/2);
    G4LogicalVolume* det_log = new G4LogicalVolume(det_box, scintilator, "det_log", 0,0,0);
    G4PVPlacement* det_phys = new G4PVPlacement(0, G4ThreeVector(0,0,0), det_log, "Detector", teflon_log, false, 0);

    double r = 0.5*mm;
    double z = detX;

    double fiber_rmin = 0.00*cm;
    double fiber_rmax = 0.940*r;
    //double fiber_z    = z - 2.2*mm;;
    double fiber_z    = z - 0.6*mm;;
    double fiber_sphi = 0.00*deg;
    double fiber_ephi = 360.*deg;

    double clad1_rmin = 0.;// fiber_rmax;
    double clad1_rmax = 0.970*r;

    double clad1_z    = fiber_z;
    double clad1_sphi = fiber_sphi;
    double clad1_ephi = fiber_ephi;

    double clad2_rmin = 0.;//clad1_rmax;
    double clad2_rmax = r;

    double clad2_z    = fiber_z;
    double clad2_sphi = fiber_sphi;
    double clad2_ephi = fiber_ephi;

    double holder_rmin = 0;
    double holder_rmax = r;

    double holder_z = z;
    double holder_sphi = fiber_sphi;
    double holder_ephi = fiber_ephi;

    G4Tubs* Holder_tube =
      new G4Tubs("Holder",holder_rmin,holder_rmax,holder_z/2,holder_sphi,holder_ephi);

    G4LogicalVolume* Holder_log =
      new G4LogicalVolume(Holder_tube,airMaterial,
			  "Holder",0,0,0);

    G4Tubs* Fiber_tube =
      new G4Tubs("Fiber",fiber_rmin,fiber_rmax,fiber_z/2,fiber_sphi,fiber_ephi);

    G4LogicalVolume* Fiber_log =
      new G4LogicalVolume(Fiber_tube,Pstyrene,
			  "Fiber",0,0,0);

    // Cladding (first layer)
    //
    G4Tubs* clad1_tube =
      new G4Tubs("Cladding1",clad1_rmin,clad1_rmax,clad1_z/2,clad1_sphi,
		 clad1_ephi);

    G4LogicalVolume* clad1_log =
      new G4LogicalVolume(clad1_tube,PMMA,
			  "Cladding1",0,0,0);

    // Cladding (second layer)
    //
    G4Tubs* clad2_tube =
      new G4Tubs("Cladding2",clad2_rmin,clad2_rmax,clad2_z/2,clad2_sphi,
		 clad2_ephi);

    G4LogicalVolume* clad2_log =
      new G4LogicalVolume(clad2_tube,fPethylene,
			  "Cladding2",0,0,0);

    G4RotationMatrix* rm = new G4RotationMatrix();
    rm->rotateY(90*deg);

    G4PVPlacement* Fiber_Pla = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),Fiber_log,
		      "Fiber", clad1_log,false,0);
    G4PVPlacement* clad1_pla = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),clad1_log,
		      "Cladding1",clad2_log,false,0);
	G4PVPlacement* clad2_pla = new G4PVPlacement(0,G4ThreeVector(0.,0.,-0.3*mm),clad2_log,
		      "Cladding2",Holder_log,false,0);

    int nFibers = 2;
    double length = detY/nFibers;
    for (int i = 0 ; i < nFibers ; i++)
    {
        G4PVPlacement* Holder_pla = new G4PVPlacement(rm,G4ThreeVector(0.0,(-detY/2+length/2 + length*i),detZ/2-holder_rmax),Holder_log,
		      "Holder",det_log,false,0);
    }

    //****************** Build PMTs
    double d_mtl=0.6*mm;
    double outerRadius_pmt = r;

    G4double innerRadius_pmt = 0.*cm;
    G4double height_pmt = d_mtl;
    G4double startAngle_pmt = 0.*deg;
    G4double spanningAngle_pmt = 360.*deg;
    G4double height_vacuumGap = 0.58*mm;
    G4double height_photoca = 0.02*mm;

    G4double pmtX = 0.6*mm;
    G4double photocathX = 0.02*mm;
    G4double pmtY = 18.0*mm;
    G4double pmtZ = 10.0*mm;

    G4Tubs* pmt = new G4Tubs("pmt_tube",innerRadius_pmt,outerRadius_pmt,
		     height_pmt/2,startAngle_pmt,spanningAngle_pmt);

    G4Tubs* photocath = new G4Tubs("photocath_tube",innerRadius_pmt,outerRadius_pmt,
             height_photoca/2,startAngle_pmt,spanningAngle_pmt);

    //G4Box* pmt = new G4Box("pmt_box",pmtX/2,pmtY/2,pmtZ/2);

    //G4Box* photocath = new G4Box("photocath_box",photocathX/2,pmtY/2,pmtZ/2);

    G4LogicalVolume* pmt_log = new G4LogicalVolume(pmt,borGlass,
				  "pmt_log");
    G4LogicalVolume* photocath_log = new G4LogicalVolume(photocath,
					aluminiumMaterial,
					"photocath_log");

    G4PVPlacement* photocath_phys = new G4PVPlacement(0,G4ThreeVector(0,0,+height_pmt/2-height_photoca/2),
				       photocath_log,"photocath",
				       pmt_log,false,0);

    //G4PVPlacement* photocath_phys = new G4PVPlacement(0,G4ThreeVector(-pmtX/2+photocathX/2,0,0),photocath_log,"photocath",pmt_log,false,0);

    G4PVPlacement* pmt_phys = new G4PVPlacement(0,G4ThreeVector(0,0,+holder_z/2-height_pmt/2),
				       pmt_log,"pmt",
				       Holder_log,false,0);

    //G4PVPlacement* pmt_phys = new G4PVPlacement(0,G4ThreeVector(-detX/2+pmtX/2,0,0),pmt_log,"pmt",det_log,false,0);

    MaterialPropertiesScintillator();
    MaterialPropertiesTeflon(teflon_log,det_phys,teflon_phys);
    MaterialPropertiesFiber();
    MaterialPropertiesPMT(photocath_log,photocath_phys,pmt_phys);

    return physiWorld;
}

void DetectorConstruction::MaterialPropertiesTeflon(G4LogicalVolume* mylar_log, G4PVPlacement* air_phys, G4PVPlacement* mylar_phys)
{
    G4double wavelength;
    G4String filler;

    G4double reflectivityEnergy[500] = {0};
    G4double reflectivityIndex[500] = {0};
    G4double efficiencyIndex[500] = {0};

    G4int reflectivityEntries = 0;
    ifstream Readreflectivity;

    //G4String reflectivity_file="/home/fajtak/work/g4work/My/Aivaras/ucl/input_files/teflon_ref_coeff.txt";
    G4String reflectivity_file="input_files/teflon_ref_coeff.txt";
    Readreflectivity.open(reflectivity_file);

    if(Readreflectivity.is_open())
    {
        while(!Readreflectivity.eof())
        {
            Readreflectivity>>wavelength>>filler>>reflectivityIndex[18-reflectivityEntries];
            efficiencyIndex[18-reflectivityEntries] = 0;
            reflectivityEnergy[18 - reflectivityEntries] = (1240/wavelength)*eV;
            reflectivityEntries++;
        }
    }else G4cout<<"Error opening file: "<<reflectivity_file<<G4endl;
    Readreflectivity.close();
    reflectivityEntries--;

    G4MaterialPropertiesTable* mylarMPT = new G4MaterialPropertiesTable();
    mylarMPT -> AddProperty("REFLECTIVITY",reflectivityEnergy,reflectivityIndex,reflectivityEntries);
    mylarMPT -> AddProperty("EFFICIENCY",reflectivityEnergy,efficiencyIndex,reflectivityEntries);


    //G4OpticalSurface* AirMylar = new G4OpticalSurface("AirMylar",unified,ground,dielectric_dielectric);
    G4OpticalSurface* AirMylar = new G4OpticalSurface("AirMylar",unified,ground,dielectric_dielectric);
    AirMylar -> SetMaterialPropertiesTable(mylarMPT);

    G4LogicalBorderSurface* Surface = new G4LogicalBorderSurface("AirMalyr",air_phys,mylar_phys,AirMylar);
    //G4LogicalSkinSurface* Surface = new G4LogicalSkinSurface("AirMy",mylar_log,AirMylar);
}

void DetectorConstruction::MaterialPropertiesScintillator()
{
    G4double wavelength;
    G4String filler;

    G4double rindexEnergy[500] = {0};
    G4double scintIndex[500] = {0};

    G4int rindexEntries = 0;
    ifstream ReadRindex;

    //G4String rindex_file="/home/fajtak/work/g4work/My/Aivaras/ucl/input_files/rindexScint.txt";
    G4String rindex_file="input_files/rindexScint.txt";
    ReadRindex.open(rindex_file);

    if(ReadRindex.is_open())
    {
        while(!ReadRindex.eof())
        {
            ReadRindex>>wavelength>>filler>>scintIndex[76-rindexEntries];
            rindexEnergy[76 - rindexEntries] = (1240/wavelength)*eV;
            rindexEntries++;
        }
    }else G4cout<<"Error opening file: "<<rindex_file<<G4endl;
    ReadRindex.close();
    rindexEntries--;

    G4double scintEnergy[501] = {0};
    G4double scintEmit[501] = {0};
    G4double scintEmitSlow[501] = {0};

    G4int scintEntries = 0;
    ifstream ReadScint;

    //G4String Scint_file="/home/fajtak/work/g4work/My/Aivaras/ucl/input_files/pTP_emission.txt";
    G4String Scint_file="input_files/pTP_emission.txt";
    ReadScint.open(Scint_file);

    if(ReadScint.is_open())
    {
        while(!ReadScint.eof())
        {
            ReadScint>>wavelength>>filler>>scintEmit[500-scintEntries];
            //convert wavelength to eV:
            scintEnergy[500 - scintEntries] = (1240/wavelength)*eV;
            scintEmitSlow[500 - scintEntries] = scintEmit[500 - scintEntries];
            scintEntries++;
        }
    }else G4cout<<"Error opening file: "<<Scint_file<<G4endl;
    ReadScint.close();
    scintEntries--;

    G4int absorbEntries = 0;
    G4double varabsorblength;
    G4double absorbEnergy[501] = {0};
    G4double Absorb[501] = {0};

    ifstream ReadAbsorb;
    //G4String ReadAbsorbLength="/home/fajtak/work/g4work/My/Aivaras/ucl/input_files/PlasticBulkAbsorb2.cfg";
    G4String ReadAbsorbLength="input_files/PlasticBulkAbsorb2.cfg";

    ReadAbsorb.open(ReadAbsorbLength);
    if (ReadAbsorb.is_open())
    {
        while(!ReadAbsorb.eof())
        {
            ReadAbsorb>>wavelength>>filler>>varabsorblength;
            absorbEnergy[500 - absorbEntries]=(1240/wavelength)*eV;
            Absorb[500 - absorbEntries]=varabsorblength*m;
            absorbEntries++;
        }
    }else G4cout<<"Error opening file: "<<ReadAbsorb<<G4endl;
    ReadAbsorb.close();
    absorbEntries--;

    G4double wlsEnergy[501] = {0};
    G4double wlsEmit[501] = {0};

    G4int wlsScintEntries = 0;
    ifstream ReadWLSScint;

    //G4String wls_Scint_file="/home/fajtak/work/g4work/My/Aivaras/ucl/input_files/full_popop_emission.cfg";
    G4String wls_Scint_file="input_files/full_popop_emission.cfg";
    ReadWLSScint.open(wls_Scint_file);

    if(ReadWLSScint.is_open())
    {
        while(!ReadWLSScint.eof())
        {
            ReadWLSScint>>wavelength>>filler>>wlsEmit[500-wlsScintEntries];
            //convert wavelength to eV:
            wlsEnergy[500 - wlsScintEntries] = (1240/wavelength)*eV;
            wlsScintEntries++;
        }
    }else G4cout<<"Error opening file: "<<wls_Scint_file<<G4endl;
    ReadWLSScint.close();
    wlsScintEntries--;

    G4int wlsAbsorbEntries = 0;
    G4double wlsAbsorbEnergy[501] = {0};
    G4double wlsAbsorb[501] = {0};

    ifstream ReadWLSAbsorb;
    //G4String ReadWLSAbsorbLength="/home/fajtak/work/g4work/My/Aivaras/ucl/input_files/scintAbsLen.txt";
    G4String ReadWLSAbsorbLength="input_files/scintAbsLen.txt";

    ReadWLSAbsorb.open(ReadWLSAbsorbLength);
    if (ReadWLSAbsorb.is_open())
    {
        while(!ReadWLSAbsorb.eof())
        {
            ReadWLSAbsorb>>wavelength>>filler>>varabsorblength;
            wlsAbsorbEnergy[500 - wlsAbsorbEntries]=(1240/wavelength)*eV;
            wlsAbsorb[500 - wlsAbsorbEntries]=varabsorblength*m;
            wlsAbsorbEntries++;
        }
    }else G4cout<<"Error opening file: "<<ReadWLSAbsorb<<G4endl;
    ReadWLSAbsorb.close();
    wlsAbsorbEntries--;

    G4MaterialPropertiesTable* MPT = new G4MaterialPropertiesTable();

    MPT->AddProperty("WLSABSLENGTH",wlsAbsorbEnergy,wlsAbsorb,wlsAbsorbEntries);
    MPT->AddProperty("WLSCOMPONENT",wlsEnergy,wlsEmit,wlsScintEntries);
    MPT->AddConstProperty("WLSTIMECONSTANT", 12*ns);

    MPT->AddProperty("RINDEX",        rindexEnergy,  scintIndex, rindexEntries);
    MPT->AddProperty("ABSLENGTH",     absorbEnergy, Absorb,     absorbEntries);
    MPT->AddProperty("FASTCOMPONENT", scintEnergy,  scintEmit,  scintEntries);
    MPT->AddProperty("SLOWCOMPONENT",scintEnergy, scintEmitSlow,     scintEntries);

    MPT->AddConstProperty("SCINTILLATIONYIELD",11520./MeV);
    //MPT->AddConstProperty("SCINTILLATIONYIELD",100./MeV);
    MPT->AddConstProperty("RESOLUTIONSCALE",4.0); // rozmytí
    MPT->AddConstProperty("FASTTIMECONSTANT", 2.1*ns); //puvodni hodnota 2.1
    MPT->AddConstProperty("SLOWTIMECONSTANT",14.2*ns); // puvodni hodnota 14.2
    MPT->AddConstProperty("YIELDRATIO",1.0); // poměr rychlé složky vůči celkovému

    scintilator->SetMaterialPropertiesTable(MPT);
}


void DetectorConstruction::MaterialPropertiesFiber()
{
    const G4int WLS_NUMENTRIES = 2;
    G4double WLS_Energy[WLS_NUMENTRIES] = {1.7*eV,7.0*eV};

    G4double RefractiveIndexFiber[WLS_NUMENTRIES]={ 1.60, 1.60};
    G4double AbsFiber[WLS_NUMENTRIES]={10.0*m,10.0*m};

    G4double wavelength;
    G4String filler;
    G4double varabsorblength;

    G4double absEnergy[500] = {0};
    G4double abs[500] = {0};

    G4int absEntries = 0;
    ifstream ReadAbs;

    //G4String abs_file="/home/fajtak/work/g4work/My/Aivaras/ucl/input_files/fiberAbs.txt";
    G4String abs_file="input_files/fiberAbs.txt";
    ReadAbs.open(abs_file);

    if(ReadAbs.is_open())
    {
        while(!ReadAbs.eof())
        {
            ReadAbs>>wavelength>>filler>>varabsorblength;
            absEnergy[38 - absEntries] = (1240/wavelength)*eV;
            abs[38 - absEntries] = varabsorblength*m;
            absEntries++;
        }
    }else G4cout<<"Error opening file: "<<abs_file<<G4endl;
    ReadAbs.close();
    absEntries--;

    G4double wlsabsEnergy[500] = {0};
    G4double wlsabs[500] = {0};

    G4int wlsabsEntries = 0;
    ifstream ReadwlsAbs;

    //G4String wlsabs_file="/home/fajtak/work/g4work/My/Aivaras/ucl/input_files/fiberWLSabs.txt";
    G4String wlsabs_file="input_files/fiberWLSabs.txt";
    ReadwlsAbs.open(wlsabs_file);

    if(ReadwlsAbs.is_open())
    {
        while(!ReadwlsAbs.eof())
        {
            ReadwlsAbs>>wavelength>>filler>>varabsorblength;
            wlsabsEnergy[27 - wlsabsEntries] = (1240/wavelength)*eV;
            wlsabs[27-wlsabsEntries] = varabsorblength*m;
            wlsabsEntries++;
        }
    }else G4cout<<"Error opening file: "<<wlsabs_file<<G4endl;
    ReadwlsAbs.close();
    wlsabsEntries--;

    G4double wlsEnergy[501] = {0};
    G4double wlsEmit[501] = {0};

    G4int wlsEntries = 0;
    ifstream ReadWLS;

    //G4String wls_file="/home/fajtak/work/g4work/My/Aivaras/ucl/input_files/fiberWLS.txt";
    G4String wls_file="input_files/fiberWLS.txt";
    ReadWLS.open(wls_file);

    if(ReadWLS.is_open())
    {
        while(!ReadWLS.eof())
        {
            ReadWLS>>wavelength>>filler>>wlsEmit[21-wlsEntries];
            //convert wavelength to eV:
            wlsEnergy[21 - wlsEntries] = (1240/wavelength)*eV;
            wlsEntries++;
        }
    }else G4cout<<"Error opening file: "<<wls_file<<G4endl;
    ReadWLS.close();
    wlsEntries--;

    G4MaterialPropertiesTable* MPTFiber = new G4MaterialPropertiesTable();
    MPTFiber->AddProperty("RINDEX",WLS_Energy,RefractiveIndexFiber,
            WLS_NUMENTRIES);
    MPTFiber->AddProperty("WLSABSLENGTH",wlsabsEnergy,wlsabs,wlsabsEntries);
    MPTFiber->AddProperty("WLSCOMPONENT",wlsEnergy,wlsEmit,wlsEntries);
    MPTFiber->AddConstProperty("WLSTIMECONSTANT", 0.5*ns);
    MPTFiber->AddProperty("ABSLENGTH",     absEnergy, abs,     absEntries);
    Pstyrene->SetMaterialPropertiesTable(MPTFiber);

    G4double RefractiveIndexClad1[WLS_NUMENTRIES]={ 1.49,1.49};
    G4MaterialPropertiesTable* MPTClad1 = new G4MaterialPropertiesTable();
    MPTClad1->AddProperty("RINDEX",WLS_Energy,RefractiveIndexClad1,
            WLS_NUMENTRIES);
    MPTClad1->AddProperty("ABSLENGTH",WLS_Energy,AbsFiber,WLS_NUMENTRIES);
    PMMA->SetMaterialPropertiesTable(MPTClad1);

    G4double RefractiveIndexClad2[WLS_NUMENTRIES]={ 1.42,1.42};
    G4MaterialPropertiesTable* MPTClad2 = new G4MaterialPropertiesTable();
    MPTClad2->AddProperty("RINDEX",WLS_Energy,RefractiveIndexClad2,
            WLS_NUMENTRIES);
    MPTClad2->AddProperty("ABSLENGTH",WLS_Energy,AbsFiber,WLS_NUMENTRIES);
    fPethylene->SetMaterialPropertiesTable(MPTClad2);
}

void DetectorConstruction::MaterialPropertiesPMT(G4LogicalVolume* photocath_log, G4PVPlacement* photocath_phys, G4PVPlacement* vacuumGap_phys)
{
    const G4int LXe_NUMENTRIES = 3;
    G4double LXe_Energy[LXe_NUMENTRIES]    = { 1.7*eV , 7.07*eV, 7.14*eV };

    G4double Glass_RIND[LXe_NUMENTRIES]={1.49,1.49,1.49};
    G4double Glass_AbsLength[LXe_NUMENTRIES]={420.*cm,420.*cm,420.*cm};
    G4MaterialPropertiesTable *Glass_mt = new G4MaterialPropertiesTable();
    Glass_mt->AddProperty("ABSLENGTH",LXe_Energy,Glass_AbsLength,LXe_NUMENTRIES);
    Glass_mt->AddProperty("RINDEX",LXe_Energy,Glass_RIND,LXe_NUMENTRIES);
    borGlass->SetMaterialPropertiesTable(Glass_mt);

    const G4int num = 2;
    G4double Ephoton[num] = {1.7*eV, 7.14*eV};

    G4double wavelength;
    G4String filler;

    G4double qeffEnergy[501] = {0};
    G4double qeff[501] = {0};

    G4int qeffEntries = 0;
    ifstream ReadQeff;

    //G4String qeff_file="/home/fajtak/work/g4work/My/Aivaras/ucl/input_files/R7600u-300.txt";
    G4String qeff_file="input_files/R7600u-300.txt";
    ReadQeff.open(qeff_file);

    if(ReadQeff.is_open())
    {
        while(!ReadQeff.eof())
        {
            ReadQeff>>wavelength>>filler>>qeff[18-qeffEntries];
            //convert wavelength to eV:
            qeffEnergy[18 - qeffEntries] = (1240/wavelength)*eV;
            qeffEntries++;
        }
    }else G4cout<<"Error opening file: "<<qeff_file<<G4endl;
    ReadQeff.close();
    qeffEntries--;

    //**Photocathode surface properties
    G4double Refreflectivity[num] = {0, 0};
    G4double Eff[num] = {0.25, 0.25};
    G4MaterialPropertiesTable* photocath_mt = new G4MaterialPropertiesTable();
    photocath_mt->AddProperty("EFFICIENCY",qeffEnergy,qeff,qeffEntries);
    photocath_mt -> AddProperty("REFLECTIVITY",Ephoton,Refreflectivity,num);
    G4OpticalSurface* photocath_opsurf=
        new G4OpticalSurface("photocath_opsurf",unified,polished,
             dielectric_metal);
    photocath_opsurf->SetMaterialPropertiesTable(photocath_mt);

    //new G4LogicalSkinSurface("photocath_surf",photocath_log,photocath_opsurf);
    G4LogicalBorderSurface* photoCathSurface = new G4LogicalBorderSurface("photoCathSurface",vacuumGap_phys,photocath_phys,photocath_opsurf);
}
