#include "generator.hh"
#include "G4RandomTools.hh"

G4double SampleThetaCos2(G4double thetaMin,
                         G4double thetaMax){

    while(true){

        // Uniform candidate
        G4double theta =
            thetaMin
            + G4UniformRand()*(thetaMax-thetaMin);

        // Random number between 0 and 1
        G4double y =
            G4UniformRand();

        // Accept according to cos^2(theta)
        if(y < std::pow(std::cos(theta),2)){
            return theta;
        }
    }
}

generator::generator(){

    fParticleGun = new G4ParticleGun(1);
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("mu-");

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(10 *MeV);

    fMessenger = new G4GenericMessenger(this, "/generator/", "Primary generator control");
    fMessenger->DeclareProperty("deg", deg, "Incidence mode");

    // Modes:
    // 0 -> 15°-25° top face
    // 1 -> 25°-40° top face
    // 2 -> 15°-25° lateral face
    // 3 -> 25°-40° lateral face

    deg = 0;
}

generator::~generator(){

    delete fParticleGun;
}

void generator::GeneratePrimaries(G4Event *anEvent){

    //----------------------------------------------------------------
    G4double x,y,z;

    G4double rad_real = 25.*cm;
    G4double half_height = 17.*cm;

    G4double theta;
    G4double Phi;

    G4double px,py,pz;

    const G4double deg2rad = M_PI/180.;

    x = 0.;
    y = 0.;
    z = 0.;

    px = 0.;
    py = 0.;
    pz = 0.;

    //----------------------------------------------------------------
    // Generation modes
    //----------------------------------------------------------------

    switch(deg){

        //============================================================
        // TOP FACE : 15° - 25°
        //============================================================

        case 0:

            // Random point on upper disk
            do{

                x = (2.*G4UniformRand() - 1.)*rad_real;
                y = (2.*G4UniformRand() - 1.)*rad_real;

            }while(std::sqrt(x*x + y*y) > rad_real);

            z = half_height;

            // Angular range
            theta = SampleThetaCos2(
                15.*deg2rad,
                25.*deg2rad);

            Phi = 2.*M_PI*G4UniformRand();

            fThetaGen = theta;
            fPhiGen = Phi;

            // Momentum direction
            px = -std::sin(theta)*std::cos(Phi);
            py = -std::sin(theta)*std::sin(Phi);
            pz = -std::cos(theta);

            fParticleGun->SetParticlePosition(
                G4ThreeVector(x,y,z));

            fParticleGun->SetParticleMomentumDirection(
                G4ThreeVector(px,py,pz));

            break;

        //============================================================
        // TOP FACE : 25° - 40°
        //============================================================

        case 1:

            do{

                x = (2.*G4UniformRand() - 1.)*rad_real;
                y = (2.*G4UniformRand() - 1.)*rad_real;

            }while(std::sqrt(x*x + y*y) > rad_real);

            z = half_height;

            theta = SampleThetaCos2(
                25.*deg2rad,
                40.*deg2rad);

            Phi = 2.*M_PI*G4UniformRand();

            fThetaGen = theta;
            fPhiGen = Phi;

            px = -std::sin(theta)*std::cos(Phi);
            py = -std::sin(theta)*std::sin(Phi);
            pz = -std::cos(theta);

            fParticleGun->SetParticlePosition(
                G4ThreeVector(x,y,z));

            fParticleGun->SetParticleMomentumDirection(
                G4ThreeVector(px,py,pz));

            break;

        //============================================================
        // LATERAL FACE : 15° - 25°
        //============================================================

        case 2:

            // Random point on cylinder lateral surface
            Phi = 2.*M_PI*G4UniformRand();

            x = rad_real*std::cos(Phi);
            y = rad_real*std::sin(Phi);

            z = (2.*G4UniformRand() - 1.)*half_height;

            // Angular range with respect to radial normal
            theta = SampleThetaCos2(
                15.*deg2rad,
                25.*deg2rad);

            fThetaGen = theta;
            fPhiGen = Phi;

            // Momentum toward crystal interior
            px = -std::cos(Phi)*std::cos(theta);
            py = -std::sin(Phi)*std::cos(theta);

            // Vertical component
            pz = (2.*G4UniformRand() - 1.)*std::sin(theta);

            // Normalize momentum vector
            {
                G4double norm = std::sqrt(px*px + py*py + pz*pz);

                px /= norm;
                py /= norm;
                pz /= norm;
            }

            fParticleGun->SetParticlePosition(
                G4ThreeVector(x,y,z));

            fParticleGun->SetParticleMomentumDirection(
                G4ThreeVector(px,py,pz));

            break;

        //============================================================
        // LATERAL FACE : 25° - 40°
        //============================================================

        case 3:

            Phi = 2.*M_PI*G4UniformRand();

            x = rad_real*std::cos(Phi);
            y = rad_real*std::sin(Phi);

            z = (2.*G4UniformRand() - 1.)*half_height;

            theta = SampleThetaCos2(
                25.*deg2rad,
                40.*deg2rad);

            fThetaGen = theta;
            fPhiGen = Phi;

            px = -std::cos(Phi)*std::cos(theta);
            py = -std::sin(Phi)*std::cos(theta);

            pz = (2.*G4UniformRand() - 1.)*std::sin(theta);

            // Normalize momentum vector
            {
                G4double norm = std::sqrt(px*px + py*py + pz*pz);

                px /= norm;
                py /= norm;
                pz /= norm;
            }

            fParticleGun->SetParticlePosition(
                G4ThreeVector(x,y,z));

            fParticleGun->SetParticleMomentumDirection(
                G4ThreeVector(px,py,pz));

            break;

        //============================================================
        default:

            G4cerr << "Invalid mode selected" << G4endl;
    }

    //----------------------------------------------------------------

    fParticleGun->GeneratePrimaryVertex(anEvent);
}

