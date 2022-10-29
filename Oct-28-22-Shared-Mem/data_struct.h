#include <stdio.h>
#include <vector>
#include <string>
/*struct Components
{
  Atoms comp[N]; //Component
}*/

struct Complex
{
  double real;
  double imag;
};


struct Units
{
  double MassUnit;
  double TimeUnit;
  double LengthUnit;
  double energy_to_kelvin;
  double BoltzmannConstant;
};

struct Move_Statistics
{
  //Translation Move//
  double TranslationProb;
  int TranslationAccepted;
  int TranslationTotal;
  double TranslationAccRatio;
  //Rotation Move//
  double RotationProb;
  int RotationAccepted;
  int RotationTotal;
  double RotationAccRatio;
  double WidomProb;
  double ReinsertionProb;
  double SwapProb;
  size_t NumberOfBlocks; //Number of blocks for statistical averaging
};

struct Components
{
  size_t  Total_Components;                           // Number of Components in the system (including framework)
  size_t  TotalNumberOfMolecules;                     // Total Number of Molecules (including framework)
  size_t  NumberOfFrameworks;                         // Total Number of framework species, usually 1.
  std::vector<std::string> MoleculeName;              // Name of the molecule
  std::vector<size_t> Moleculesize;                   // Number of Pseudo-Atoms in the molecule
  std::vector<size_t> NumberOfMolecule_for_Component; // Number of Molecules for each component
  std::vector<double> MolFraction;                    // Mol fraction of the component(excluding the framework)
  std::vector<double> IdealRosenbluthWeight;          // Ideal Rosenbluth weight
  std::vector<double> FugacityCoeff;                  // Fugacity Coefficient
  std::vector<Move_Statistics>Moves;                  // Move statistics: total, acceptance, etc.
  std::vector<double>Tc;                              // Critical Temperature of the component
  std::vector<double>Pc;                              // Critical Pressure of the component
  std::vector<double>Accentric;                       // Accentric Factor of the component
};

struct Atoms
{
  double* x;
  double* y;
  double* z;
  double* scale;
  double* charge;
  double* scaleCoul;
  size_t* Type;
  //uint_32_t* CompID; //
  size_t* MolID;
  size_t  Molsize;
  size_t  size;
  //uint_32_t  size;   // These values are small, the can use 32-bit, need to test
  size_t  Allocate_size;
};

struct PseudoAtomDefinitions //Always a host struct, never on the device
{
  std::vector<std::string> Name;
  std::vector<double> oxidation;
  std::vector<double> mass;
  std::vector<double> charge;
  std::vector<double> polar; //polarizability
};

struct ForceField
{
  double* epsilon;
  double* sigma;
  double* z; // a third term
  double* shift;
  int*    FFType; //type of force field calculation  
  double* FFParams; // cutoffVDW, cutoffCoulomb...
  int*    OtherParams;  
  double* MaxTranslation;
  double* MaxRotation; 
  bool    noCharges;
  size_t  size;
  double Beta;
};

struct Boxsize
{
  //Complex* eik_x;
  //Complex* eik_y;
  //Complex* eik_z;
  //Complex* eik_xy;
  //Complex* storedEik;
  float*   float_Cell;
  float*   float_InverseCell;
  double*  Cell;
  double*  InverseCell;
  double   Pressure;
  double   Volume;
  double   Temperature;
  //size_t   alloc_x_size;
  //size_t   alloc_y_size;
  //size_t   alloc_z_size;
  //size_t   alloc_xy_size;
  //size_t   alloc_wavevector;
};

struct WidomStruct
{
  bool UseGPUReduction; //For calculating the energies for each bead
  bool Useflag;         //for using flags (for skipping reduction)
  size_t NumberWidomTrials;
  size_t NumberWidomTrialsOrientations;
  int* RosenbluthCount;
  bool*   flag;            // flag on the host   //  
  bool*   device_flag;          // flag on the device //
  float*  floatResult;          // float for dual-precision MC //
  double* Blocksum;             // Block sums for partial reduction //
  double* WidomFirstBeadResult; // for device, temporary result array
  double* Rosenbluth;
  double* RosenbluthSquared;
  double* ExcessMu;
  double* ExcessMuSquared;
  size_t  InsertionTotal;
  size_t  DeletionTotal;
  size_t  ReinsertionTotal;
  size_t  InsertionAccepted;
  size_t  DeletionAccepted;
  size_t  ReinsertionAccepted;
  size_t  WidomFirstBeadAllocatesize; //space allocated for WidomFirstBeadResult
};

struct RandomNumber
{
  double* host_random;
  double* device_random;
  size_t  randomsize;
  size_t  offset;
};
