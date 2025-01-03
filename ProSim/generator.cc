#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator() {
    fParticleGun = new G4ParticleGun(1);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("proton");

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleMomentum(100. * GeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -1. * m));
}

MyPrimaryGenerator::~MyPrimaryGenerator() {
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent) {
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
