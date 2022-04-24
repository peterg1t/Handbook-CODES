#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <interp.h>

QStringList interlocks_linac;
QStringList desc_linac;
QStringList action_linac;
QStringList interlocks_tb;

//Data for collimator scatter factor calculation
QVector<double> SctabulatedFS;
QVector<double> SctabulatedEner;
QVector<double> SctabulatedVal;

//Data for phantom scatter factor calculation
QVector<double> SptabulatedFS;
QVector<double> SptabulatedEner;
QVector<double> SptabulatedVal;

//Data for tray factor calculations
QVector<double> TFtabulatedFS;
QVector<double> TFtabulatedEner;
QVector<double> TFtabulatedVal;


double ptp, ppol, pion;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_3->setWordWrap(true);
    ui->label_4->setWordWrap(true);

    ui->groupBox_4->setVisible(false);
    ui->groupBox_5->setVisible(false);


    //calcualting initial parameters with default variables
    ptp = ((273.2+ui->doubleSpinBox->value())*101.33)/((273.2+22.0)*ui->doubleSpinBox_2->value());
    ui->label_14->setText("Ptp="+QString::number(ptp));
    ppol = (ui->doubleSpinBox_5->value()-ui->doubleSpinBox_6->value())/(2*ui->doubleSpinBox_5->value());
    ui->label_15->setText("Ppol="+QString::number(ppol));

    pion = ( 1 - ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value() )/( ui->doubleSpinBox_3->value()/ui->doubleSpinBox_4->value() - ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value() );
    ui->label_16->setText("Pion="+QString::number(pion));


        TFtabulatedEner << 6 << 10 << 15; //Tabulated energies for the TF calculation

        TFtabulatedFS << 5
                      << 10
                      << 20
                      << 30
                      << 40;



        SctabulatedEner << 6  //Tabulated energies for the collimator scatter factor
                       <<    10
                       <<    15
                       <<    18;

        SptabulatedEner = SctabulatedEner;




        //Tabulated field size for the phantom scatter factor
        SptabulatedFS <<  4
              <<  5
              <<  6
              <<  7
              <<  8
              <<  9
              <<  10
              <<  11
              <<  12
              <<  13
              <<  14
              <<  15
              <<  16
              <<  17
              <<  18
              <<  19
              <<  20
              <<  21
              <<  22
              <<  23
              <<  24
              <<  25
              <<  30
              <<  35
              <<  40;





        // Tabulated phantom scatter factors
        SptabulatedVal << 0.970
              << 0.977
              <<  0.983
              <<  0.988
              <<  0.993
              <<  0.997
              <<  1
              <<  1.004
              <<  1.007
              <<  1.010
              <<  1.013
              <<  1.017
              <<  1.019
              <<  1.021
              <<  1.023
              <<  1.025
              <<  1.027
              <<  1.028
              <<  1.029
              <<  1.030
              <<  1.032
              <<  1.033
              <<  1.040
              <<  1.045
              <<  1.048
              <<  0.961
              <<  0.969
              <<  0.977
              <<  0.982
              <<  0.987
              <<  0.994
              <<  1.000
              <<  1.004
              <<  1.007
              <<  1.009
              <<  1.011
              <<  1.014
              <<  1.016
              <<  1.018
              <<  1.021
              <<  1.023
              <<  1.027
              <<  1.028
              <<  1.029
              <<  1.030
              <<  1.030
              <<  1.031
              <<  1.037
              <<  1.042
              <<  1.048
              <<  0.957
              <<  0.967
              <<  0.977
              <<  0.983
              <<  0.990
              <<  0.995
              <<  1.000
              <<  1.005
              <<  1.010
              <<  1.014
              <<  1.017
              <<  1.020
              <<  1.023
              <<  1.026
              <<  1.029
              <<  1.031
              <<  1.033
              <<  1.035
              <<  1.037
              <<  1.039
              <<  1.041
              <<  1.048
              <<  1.051
              <<  1.054
              <<  0.950
              <<  0.958
              <<  0.975
              <<  0.981
              <<  0.987
              <<  0.994
              <<  1.000
              <<  1.007
              <<  1.013
              <<  1.018
              <<  1.023
              <<  1.027
              <<  1.031
              <<  1.035
              <<  1.038
              <<  1.041
              <<  1.044
              <<  1.046
              <<  1.048
              <<  1.050
              <<  1.052
              <<  1.054
              <<  1.056
              <<  1.059
              <<  1.063;



        //Tabulated field size for the collimator scatter factor
        SctabulatedFS << 3
              <<  4
              <<  5
              <<  6
              <<  7
              <<  8
              <<  9
              <<  10
              <<  11
              <<  12
              <<  13
              <<  14
              <<  15
              <<  16
              <<  17
              <<  18
              <<  19
              <<  20
              <<  21
              <<  22
              <<  23
              <<  24
              <<  25
              <<  26
              <<  27
              <<  28
              <<  29
              <<  30
              <<  35
              <<  40;


        // Tabulated collimator scatter factors
        SctabulatedVal << 0.945
              << 0.957
              <<  0.966
              <<  0.977
              <<  0.983
              <<  0.99
              <<  0.995
              <<  1
              <<  1.004
              <<  1.008
              <<  1.011
              <<  1.014
              <<  1.015
              <<  1.017
              <<  1.018
              <<  1.02
              <<  1.022
              <<  1.024
              <<  1.025
              <<  1.026
              <<  1.028
              <<  1.029
              <<  1.031
              <<  1.033
              <<  1.034
              <<  1.035
              <<  1.036
              <<  1.037
              <<  1.043
              <<  1.047
              <<  0.94
              <<  0.953
              <<  0.964
              <<  0.974
              <<  0.982
              <<  0.989
              <<  0.996
              <<  1
              <<  1.004
              <<  1.008
              <<  1.011
              <<  1.013
              <<  1.016
              <<  1.018
              <<  1.019
              <<  1.021
              <<  1.022
              <<  1.024
              <<  1.025
              <<  1.027
              <<  1.028
              <<  1.03
              <<  1.031
              <<  1.033
              <<  1.034
              <<  1.036
              <<  1.037
              <<  1.039
              <<  1.045
              <<  1.05
              <<  0.956
              <<  0.965
              <<  0.973
              <<  0.981
              <<  0.987
              <<  0.989
              <<  0.996
              <<  1
              <<  1.002
              <<  1.004
              <<  1.006
              <<  1.009
              <<  1.011
              <<  1.012
              <<  1.013
              <<  1.015
              <<  1.017
              <<  1.019
              <<  1.02
              <<  1.021
              <<  1.023
              <<  1.024
              <<  1.025
              <<  1.026
              <<  1.028
              <<  1.029
              <<  1.031
              <<  1.032
              <<  1.037
              <<  1.041
              <<  0.937
              <<  0.951
              <<  0.961
              <<  0.972
              <<  0.982
              <<  0.989
              <<  0.995
              <<  1
              <<  1.004
              <<  1.008
              <<  1.01
              <<  1.013
              <<  1.015
              <<  1.017
              <<  1.019
              <<  1.021
              <<  1.022
              <<  1.024
              <<  1.025
              <<  1.027
              <<  1.028
              <<  1.03
              <<  1.031
              <<  1.032
              <<  1.034
              <<  1.035
              <<  1.037
              <<  1.038
              <<  1.044
              <<  1.049;

        // Tabulated tray factors
        TFtabulatedVal << 0.967
                       << 0.967
                       << 0.971
                       << 0.975
                       << 0.976
                       << 0.976
                       << 0.978
                       << 0.981
                       << 0.984
                       << 0.987
                       << 0.978
                       << 0.979
                       << 0.981
                       << 0.984
                       << 0.986;


         qDebug() << SctabulatedFS.length() << SctabulatedEner.length() <<SctabulatedVal.length() ;


//    ui->tab->layout()->setSizeConstraint(QLayout::SetFixedSize);

    interlocks_linac << "ACC"
                     << "AIR"
                     << "BMAG"
                     << "CARR"
                     << "CDOS"
                     << "CKFA"
                     << "CKTO"
                     << "CLFA"
                     << "CLTO"
                     << "CMNR"
                     << "CNF"
                     << "COLL"
                     << "CTRL"
                     << "DOOR"
                     << "DOS1"
                     << "DOS2"
                     << "DPSN"
                     << "DS12"
                     << "DSFA"
                     << "ENSW"
                     << "EXBH"
                     << "EXQ1"
                     << "EXQ2"
                     << "EXQT"
                     << "EXT"
                     << "FLOW"
                     << "FOIL"
                     << "GAS"
                     << "GFIL"
                     << "HVCB"
                     << "HVOC"
                     << "HWFA"
                     << "ION1"
                     << "ION2"
                     << "IPSN"
                     << "KEY"
                     << "KFIL"
                     << "KSOL"
                     << "LVPS"
                     << "MFIL"
                     << "MGNT"
                     << "MLC"
                     << "MOD"
                     << "MODE"
                     << "MOTN"
                     << "ORNT"
                     << "PNDT"
                     << "PUMP"
                     << "RVBP"
                     << "STPR"
                     << "STPS"
                     << "SYM1"
                     << "SYM2"
                     << "TARG"
                     << "TDLY"
                     << "TDRV"
                     << "TIME"
                     << "UDR1"
                     << "UDR2"
                     << "UDRS"
                     << "VAC1"
                     << "VAC2"
                     << "VSWR"
                     << "XDP1"
                     << "XDP2"
                     << "XDR1"
                     << "XDR2"
                     << "XDRS"
                     << "YLD";


    desc_linac << "Selected accessory does not match the mounted accessory.\n -OR- \n Accessory is improperly positioned. A loose accessory can fall out of the accessory slot.\n -OR- \n Red Reset button on the collimator lights up and machine movements are locked; no interlock message appears. On High Energy accelerators only: The electron applicator touch guard may have been tripped."
                     << "Air pressure is below 30 psig limit. (This condition may be temporary.)"
                     << "Voltage for bending magnet power supply exceeds the set value limit. The allowable range is ±5% \n -OR- \n Current is too high-OR-low for the energy mode."
                     << "Carousel is not in position for the selected mode. \n -OR- \n Communication failed between the console computer and carousel controller."
                     << "External customer-defined dosimetry interlock has tripped (The interlock was not asserted during the check cycle.)\n"
                        "The CDOS interlock is connected to PortalVision, Yield Monitor, and third-party systems."
                     << "Dosimetry check cycle failure.\n"
                        "The Controller activated the following interlocks during the calibration cycle, but the console did not detect one-OR-more of them:\n"
                        "XDP1, XDP2, XDRS, XDR1,\n"
                        "XDR2, EXQ1/SYM1, EXQ2/SYM2,\n"
                        "EXQT/YLD, ION1, ION2, LVPS,\n"
                        "DS12. DOS1, DOS2, and TIME.\n"
                        "The actual values of DOS1, DOS2, and TIME must match the set values.\n"
                        "This interlock is activated in Clinical mode only."
                     << "Check cycle did not complete before timeout. The Console initiates a Dose Count Check cycle\n"
                        "and asserts the interlock if the cycle does not complete within 1.8 to 2.4 seconds after the command is received."
                     << "Dose calibration cycle failure.\n"
                        "Calibration failed during calibration check.At the end of the Dose Calibration cycle (in Clinical mode only), the Console Processor reads MU1, MU2, and TIME values, and checks the condition of the DS12 interlock."
                     << "The calibration cycle took too long, and did not finish before timeout (Clinical mode only)."
                     << "An external customer-defined minor interlock is activated."
                     << "Configuration data is missing due to one of the following conditions:\n"
                        "The console controller did not\n"
                        "receive the required configuration data from the console computer. \n-OR-\n"
                        "PRO readouts are in RAW units. \n-OR-\n"
                        "(UNIQUE) A dynamic treatment type was selected but the Magnetron Pulse Rate Frequency was not determined."
                     << "The accessory combination is invalid. \n-OR-\n"
                        "The accessory combination is invalid for the set Treatment"
                        "type-OR-Energy. \n-OR-\n"
                        "The collimator jaws are positioned incorrectly (that is., not "
                        "within the prescribed 2mm tolerance of the specified positions-OR-range of positions). \n-OR-\n"
                        "Either set of jaws is in Symmetric mode and is not"
                        "tracking within 2mm."
                     << "The console control computer detected an abnormal operating condition."
                     << "Treatment room door is open"
                     << "The number of accumulated mon-itor units in the primary dosimetry channel equals the value that was set for MU1."
                     << "Indicates DOS1 failed. Issue with main circuit prevents completion \n"
                        "of the dose. Number of accumulated monitor units in secondary \n"
                        "dosimetry channel exceeds the preset dose by 10% (10% or \n"
                        "25MU, whichever is less, for all Clinical mode and electron arc \n"
                        "treatments [available on High Energy accelerators only]). \n"
                     << "Dose vs. Position mismatch.\n"
                        "In dynamic mode, an incorrectly positioned physical element\n"
                        "(MLC leaf or gantry) caused the beam to terminate."
                        "\n -OR- \n"
                        "For respiratory gating, gating is out-of-tolerance because the\n"
                        "beam was held too long (more than 30 seconds for an external\n"
                        "beam hold, or more than 15 sec onds for clinical conditions)."
                     << "For dynamic treatments, a discrepancywas detected when comparing:\n"
                        "dose delivered and one or more axis positions \n -OR- \n"
                        "primary and secondary dosimetry channels \n -OR- \n"
                        "two or more counters/timers that are counting the same signal"
                     << "Actual dose exceeds set dose."
                     << "The Accelerator energy switch is not in the correct position for the selected mode.\n"
                        "If an AIR interlock appears at the same time, there may be a problem with the hydraulic air "
                        "system that moves the energy switch."
                     << "An external beam hold occurred during an electron mode or X-ray "
                        "arc mode treatment. For example, Respiratory Gating or a third party connected to the "
                        "linear accelerator can produce an external beam hold."
                     << "Radial beam symmetry is out of tolerance or instantaneous dose "
                        "rate exceeds 800 MU/min per pulse. \n"
                        "EXQ does not apply to 4MeV treatments. For 4MeV, asymmetry of < 5% terminates beam with a UDR interlock."
                     << "Transverse beam symmetry is out of tolerance or instantaneous dose "
                        "rate exceeds 800 MU/min per pulse. \n"
                        "EXQ does not apply to 4MeV treatments. For 4MeV, asymmetry of < 5% terminates beam with a UDR interlock."
                     << "Total asymmetry, total dosimetry channel charge per pulse, or "
                        "average dose rate exceeds limits. \n"
                        "EXQ does not apply to 4MeV treatments. For 4MeV, asymmetry of < 5% terminates beam with a UDR interlock."
                     << "External record/verify. Treatment delivery software has not yet accepted "
                        "the actual parameters as being within tolerance of the plan. \n"
                        "The linear accelerator software has detected a problem in communication with the RV system."
                     << "The cooling water flow is too slow. Insufficient water flow "
                        "opened a flow switch in the stand or gantry unit."
                     << "Carousel locking pin is not in the home position or the plunger for "
                        "the energy selected is not pushed in."
                     << "High Energy: Waveguide dielectric gas pressure is < 30 psig."
                        "\n -OR- \n UNIQUE: Waveguide dielectric gas pressure is < 17 psig."
                     << "The filament and bias voltages are below proper operating level "
                        "for the linear accelerator gun. In digital gun drivers, the gun controller "
                        "detected a faulty condition."
                     << "The high voltage circuit breaker is open."
                     << "High voltage power supply overcurrent. Peak or average charging "
                        "current in the high-voltage power supply may have exceeded its limits."
                     << "The control processor detected a minor hardware failure during runtime integrity checks."
                     << "Power supply voltage for radial ion chamber is below 350 V DC."
                     << "Power supply voltage for transverse ion chamber is below 350 V DC."
                     << "Dynamic treatment actual position parameters are out of tolerance "
                        "with plan position parameters."
                     << "The Disable/Enable keyswitch on the dedicated keyboard is in the Disable position."
                     << "The klystron filament current is at or below half nominal value. "
                        "KFIL is disabled for 5 seconds after the power key is turned on."
                     << "Klystron power is low."
                     << "Low voltage power supply (+12, ±15, or +5 V) failed."
                     << "The magnetron filament current is below nominal value. \n"
                        "If the Clinac is in Standby mode, MFIL is disabled for 15 seconds "
                        "during the transition from Standby to On while the filament warms up."
                     << "Magnetron electromagnet voltage is ±7% of nominal. "
                        "\n -OR- \n Magnetron electromagnet current is ±2% of nominal."
                     << "The multileaf collimator is preventing linear accelerator operation because:\n"
                        "MLC leaves are not in the planned treatment position."
                        "\n -OR- \n MLC is disabled in Physics mode."
                        "\n -OR- \n MLC controller asserted an interlock."
                     << "Negative voltage buildup (exceeding "
                        "9.5 V) on the modulator "
                        "pulse-forming network occurs at "
                        "the input to the sensing circuit. "
                        "This is a transient but significant "
                        "interlock.\n "
                        "For UNIQUE machines, reverse "
                        "voltage is caused by an arcing "
                        "magnetron.\n "
                        "For high energy machines, negative "
                        "voltage is caused by a modulator, "
                        "klystron, or pulse transformer overcurrent."
                     << "The selected energy mode does not match the check code returned from the console controller."
                     << "Unplanned motions were detected on an axis not selected for "
                        "dynamic therapy, or before or during treatment. The patient "
                        "may have moved on the treatment couch."
                     << "Enhanced Dynamic Wedge orientation "
                        "selected at the console does "
                        "not match the in-room orientation "
                        "selection.\n"
                        "No Enhanced Dynamic Wedge "
                        "orientation has yet been selected "
                        "from the hand pendant."
                     << "Hand pendant is not in the pendant cradle on the treatment couch.\n -OR- \n"
                        "Treatment couch longitudinal "
                        "and/or lateral brakes are not engaged "
                        "at the treatment couch side "
                        "panel (couch top is unlocked and "
                        "can be moved manually)."
                     << "The water tank level is low, or the pump was shut off manually, or "
                        "by a fault condition. Fault examples include: water temperature "
                        "too high, or controller malfunction."
                     << "One or more beam parameters downloaded by the treatment delivery "
                        "software differ from the actual beam setting at the linear accelerator."
                     << "The beamstopper is not fully extended or retracted. Gantry positions "
                        "that require the beamstopper to be extended for the specified energies may be programmed into the system."
                     << "Stand power supply failure. Motion is disabled as long as the interlock is asserted.\n"
                        "For UNIQUE machines this interlock is asserted for motion control "
                        "power supply only (±27 V). For high energy machines the interlock "
                        "is asserted for motion control or beam steering power supply (±27 V or ±16 V)."
                     << "Radial symmetry exceeds 2% of symmetrical adjustment."
                     << "Transverse symmetry exceeds 2% of symmetrical adjustment."
                     << "Target is not in the correct position for the selected mode. The "
                        "target drive mechanism position is jammed or mechanism proximity "
                        "switches are either misaligned or defective."
                     << "A time delay of 12 minutes for component warm-up allows "
                        "equipment filaments to reach their operating temperatures. The "
                        "delay starts when the power key is turned clockwise from Off to "
                        "On. The length of the delay varies with how long the machine was off:\n"
                        "   -2-minute delay if the machine was off less than 1 minute\n"
                        "   -4-minute delay if the machine was off more than 2 minutes\n"
                        "   -12-minute delay if off more than 5 minutes.\n"
                        "A delay longer than 12 minutes indicates that a major interlock "
                        "must be cleared to proceed through the time delay."
                     << "The RF system shunt-tee power attenuator turntable is not in the "
                        "correct position for the selected mode and the power attenuator "
                        "system setting disagrees with the energy set at the console."
                     << "The displayed beam-on time is greater than or equal to the value set for time."
                     << "Dose rate measured by the radial ion chambers is too low. \n"
                        "For 4MeV treatments, UDR may be triggered by asymmetry < 5%.\n "
                        "Alternatively, the radial dose rate is less than 80% of the set value,"
                        "possibly from:\n"
                        "Too few MU per servo period (1/20 of a second). \n -OR- \n"
                        "AFC may be out of tune."
                     << "Dose rate measured by the transverse ion chambers is too low. \n"
                        "For 4MeV treatments, UDR may be triggered by asymmetry < 5%.\n "
                        "Alternatively, the transverse dose rate is less than 80% of the set value,"
                        "possibly from:\n"
                        "Too few MU per servo period (1/20 of a second). \n -OR- \n"
                        "AFC may be out of tune."
                     << "For 4MeV treatments, UDR may be triggered by asymmetry < 5%.\n "
                        "Alternatively, the servo-ed dose rate is less than 80% of the set value,"
                        "possibly from:\n"
                        "Too few MU per servo period (1/20 of a second). \n -OR- \n"
                        "AFC may be out of tune."
                     << "There is a major vacuum leak somewhere in an area controlled "
                        "by the power supply circuits that monitor pump current."
                     << "There may be an impurity, minor vacuum leak, or transient release"
                        "of gas somewhere in the system.\n Impurities are usually self-clearing;"
                        "leaks require repair by trained personnel."
                     << "Voltage standing wave ratio at the klystron directional coupler exceeds 1.5 to 1."
                     << "Radial dose per pulse exceeded normal mode limits."
                     << "Transverse dose per pulse exceeded normal mode limits."
                     << "Radial dose rate exceeded set dose rate."
                     << "Transverse dose rate exceeded set dose rate."
                     << "Servoed dose rate exceeded intended dose rate."
                     << "Yield ratio. The ratio of peak target current to peak ion "
                        "chamber current deviated ±3.5% from its preset point.";

    action_linac << "Select the correct accessory.\n -OR- \n Reposition the accessory.\n -OR- \n Clear the path of the electron applicator and press the red Reset button."
                     << "Try the treatment again: \n"
                        "1. Press Setup. \n"
                        "2. Reprogram the treatment and attempt beam-on."
                     << "Check the water temperature. \n"
                        "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and\n"
                        "attempt beam-on."
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and\n"
                        "attempt beam-on."
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and\n"
                        "attempt beam-on."
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and\n"
                        "attempt beam-on."
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and\n"
                        "attempt beam-on."
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and\n"
                        "attempt beam-on."
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and\n"
                        "attempt beam-on."
                     << "1.2.Correct the condition that activated the interlock. (For example, close the extra door).\n"
                        "Proceed with the treatment."
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and\n"
                        "attempt beam-on.\n"
                        "3. Choose from the following options:\n"
                        "If this interlock recurs, measure the pulse repetition frequency (PRF).\n-OR-\n"
                        "If measuring the PRF does not resolve the \n"
                        "problem, have an authorized user check the position readout (PRO) \n"
                        "settings in Physics mode."
                     << "Reset the collimator jaws.\n"
                        "Reattempt the treatment."
                     << "Press F2 and then Enter to run the computer’s power-up self-test cycle. Before the test starts, press \n"
                        "Clear to cancel. Once the test begins, it cannot be canceled."
                     << "1. Close the treatment room door.\n"
                        "2. Proceed with treatment."
                     << "No action."
                     << "Do not perform further treatments. Contact authorized service personnel. (Put accelerator in Standby)"
                     << "Check physical elements, and correct those that are out of position.\n -OR- \n"
                        "Correct the gating condition that is holding the beam."
                     << "Reprogram the treatment and attempt beam-on.\n"
                        "If the treatment was interrupted:\n"
                        "Record the gantry location and Start angle, to determine the new Start angle.\n"
                        "Reprogram the treatment and enter a partial MU value to continue from where the interlock occurred."
                     << "Do not perform further treatments. Contact authorized service personnel."
                     << "Check the air pressure. Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and attempt beam-on."
                     << "1. Press Enter to clear the EXBH interlock.\n"
                        "2. Discontinue use of the external gating system during arc treatments or electron"
                        "treatments (available only on High Energy accelerators).\n"
                        "3. Continue treatment. If the problem persists, contact authorized service personnel."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "1. Check the patient setup for discrepancies.\n"
                        "2. Edit or acquire the RV parameters "
                        "to match the actual parameters on the Varian linear accelerator, if appropriate.\n"
                        "3. Check the serial connection between the console computer and the RV system."
                     << "1. Check the water tank level.\n"
                        "2. If it is low, fill the tank (distilled water only) to the optimum level.\n"
                        "3. If this does not correct the problem and the FLOW interlock "
                        "recurs, turn off the linear accelerator and contact qualified service personnel."
                     << "1. Check the carousel locking pin and fix it if it is jammed or stuck.\n"
                        "2. Try the treatment again:\n"
                        "   a. Press Setup.\n"
                        "   b. Reprogram the treatment and attempt beam-on.\n"
                     << "Adjust the gas or change the gas tank."
                     << "Try the treatment again: \n"
                        "1. Press Setup. \n"
                        "2. Reprogram the treatment and "
                        "attempt beam-on (you may "
                        "need to turn the linear accelerator "
                        "power switch to "
                        "Standby and then on again)."
                     << "1. Look at the breaker handle to "
                        "detect a circuit breaker trip.\n"
                        "2. Check the doors, screen "
                        "switches, and S1 switch in "
                        "the main thyratron chassis.\n"
                        "3. Reset the circuit breaker."
                     << "Try the treatment again: \n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "Check the actual position parameters on system with the plan position"
                        "parameters and make appropriate changes."
                     << "Turn the Disable/Enable keyswitch to the Enable position."
                     << "1. Turn the power keyswitch in the console electronics cabinet "
                        "counterclockwise to the Standby position\n"
                        "2. Then turn clockwise to the On position."
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "1. Turn the power keyswitch in "
                        "the console electronics cabinet "
                        "counterclockwise to the "
                        "Standby position \n"
                        "2. Then turn clockwise to the On position."
                     << "Try the treatment again: \n"
                        "1. Press Setup. \n"
                        "2. Reprogram the treatment and "
                        "attempt beam-on."
                     << "Correct the problem with the MLC and re-attempt treatment."
                     << "Try the treatment again: \n"
                        "1. Press Setup. \n"
                        "2. Reprogram the treatment and "
                        "attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Press Setup. \n"
                        "2. Reprogram the treatment and "
                        "attempt beam-on."
                     << "1. Correct for the motions, and "
                        "retry the treatment.\n "
                        "2. If the interlock recurs repeatedly "
                        "or does not appear to "
                        "have an obvious cause, contact "
                        "qualified service personnel. "
                     << "1. Correct discrepancies between the console and inroom orientation selection.\n"
                        "2. Select an EDW orientation from the hand pendant."
                     << "Hang the pendant in the holder at the end of the treatment couch. \n -OR- \n"
                        "Lock the treatment couch longitudinal and/or lateral brakes at the "
                        "treatment couch side panel (so the couch top is locked)."
                     << "Read the water and temperature "
                        "gauges. Based on the readings, do "
                        "the following to ensure normal "
                        "temperature and pressure: \n"
                        "   -Fill water tank to optimum level.\n"
                        "   -Maintain recommended operating water temperature range:\n"
                        "   -For High Energy: between 15°–26° C (59°– 79° F).\n"
                        "For UNIQUE: between 38°–42° C (100°– 107° F).\n"
                        "Ensure that the water temperature does not exceed 48° C (118° F)."
                        "Ensure that the water pressure does not exceed 100 psi."
                        "The pump reset switch on the primary power distribution pane"
                        "clears the PUMP interlock after the water level and temperature are within limits."
                     << "1. Correct discrepancies between the plan downloaded "
                        "by the treatment delivery (RV) system and the linear accelerator settings.\n "
                        "2. Check patient setup.\n "
                        "3. Reattempt treatment. "
                     << "Correct the beamstopper position."
                     << "Try the treatment again: \n"
                        "1. Press Setup. \n"
                        "2. Reprogram the treatment and "
                        "attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the treatment and attempt beam-on.\n"
                        "3. If this does not clear the interlock, try to program another energy."
                     << "If the TDLY interlock does not clear after 12 minutes, check for other interlocks.\n"
                        "It is not possible to adjust or override the standard 12-minute time delay."
                     << "Reboot the linear accelerator. If this does not resolve the problem, contact authorized service personnel."
                     << "   -Check the MU1 and MU2  readouts for discrepancies to "
                        "determine whether this interlock resulted from a failure of both MU1 and MU2 readouts. \n"
                        "   -If a failure of MU1 or MU2 readouts caused the TIME interlock "
                        "or the interlock cause is unclear, do not perform further "
                        "treatments. Contact authorized service personnel. \n"
                        "(You can put the accelerator in Standby mode. It is unnecessary to power off.)"
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the machine with the remaining MU and attempt beam-on."
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the machine with the remaining MU and attempt beam-on."
                     << "Try the treatment again:\n"
                        "1. Press Setup.\n"
                        "2. Reprogram the machine with the remaining MU and attempt beam-on."
                     << "Push an EMERGENCY OFF button, and call qualified service personnel."
                     << "Try the treatment again: \n"
                        "1. Press Setup. \n"
                        "2. Reprogram the treatment and "
                        "attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Press Setup. \n"
                        "2. Reprogram the treatment and "
                        "attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on."
                     << "Try the treatment again: \n"
                        "1. Enter the dosimetry password.\n"
                        "2. Press Setup.\n"
                        "3. Reprogram the treatment and attempt beam-on.";

    interlocks_tb << "TB1"
                  << "TB2"
                  << "TB2";

    ui->comboBox_2->addItems(interlocks_linac);



    //Tabulated data initialization
    // Here we calculate the initial values of the phantom scatter factor
    double fieldSize_psf=ui->doubleSpinBox_9->value();
    double energy_psf = ui->doubleSpinBox_10->value();

    interp interp_psf;
    double value_psf = interp_psf.bilinearInterp(fieldSize_psf, energy_psf, SptabulatedFS, SptabulatedEner, SptabulatedVal);
    ui->label_18->setText("Sp= "+QString::number(value_psf));




    //Here we calculate the initial values of the collimator scatter factor
    double fieldSize_csf=ui->doubleSpinBox_11->value();;
    double energy_csf = ui->doubleSpinBox_12->value();

    interp interp_csf;
    double value_csf = interp_csf.bilinearInterp(fieldSize_csf, energy_csf, SctabulatedFS, SctabulatedEner, SctabulatedVal);
    ui->label_21->setText("Sc= "+QString::number(value_csf));


    //Here we calculate the initial values of the tray factor calculation
    double fieldSize_tf=ui->doubleSpinBox_13->value();;
    double energy_tf = ui->doubleSpinBox_14->value();

    interp interp_tf;
    double value_tf = interp_tf.bilinearInterp(fieldSize_tf, energy_tf, TFtabulatedFS, TFtabulatedEner, TFtabulatedVal);
    ui->label_24->setText("TF= "+QString::number(value_tf));





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_activated(int index)
{
    ui->comboBox_2->clear();
    if (index==0) {
        ui->comboBox_2->addItems(interlocks_linac);
    }
    else if (index==1){
        ui->comboBox_2->addItems(interlocks_tb);
    }
}

void MainWindow::on_comboBox_2_activated(int index)
{
    ui->label_3->setText(desc_linac.at(index));
    ui->label_4->setText(action_linac.at(index));
}


// on the fly calculations of ptp
void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    if (ui->comboBox_3->currentIndex()==0){
        ptp = ((273.2+arg1)*101.33)/((273.2+22.0)*ui->doubleSpinBox_2->value());}
    else if (ui->comboBox_3->currentIndex()==1){
        ptp = ((273.2+arg1)*101.33)/((273.2+22.0)*ui->doubleSpinBox_2->value()*0.1);
    }
    else{
        ptp = ((273.2+arg1)*101.33)/((273.2+22.0)*ui->doubleSpinBox_2->value()*(101.33/760));
    }

    ui->label_14->setText("Ptp="+QString::number(ptp));
}

// on the fly calculations of ptp
void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    if (ui->comboBox_3->currentIndex()==0){
        ptp = ((273.2+ui->doubleSpinBox->value())*101.33)/((273.2+22.0)*arg1);}
    else if (ui->comboBox_3->currentIndex()==1){
        ptp = ((273.2+ui->doubleSpinBox->value())*101.33)/((273.2+22.0)*arg1*0.1);
    }
    else{
        ptp = ((273.2+ui->doubleSpinBox->value())*101.33)/((273.2+22.0)*arg1*(101.33/760));
    }
    ui->label_14->setText("Ptp="+QString::number(ptp));
}

//activating units change in ptp
void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    on_doubleSpinBox_2_valueChanged(ui->doubleSpinBox_2->value());
}



// here we show the different sections of the QC
void MainWindow::on_comboBox_4_activated(int index)
{
    if (index==0) {
        ui->groupBox_4->setVisible(true);
        ui->groupBox_5->setVisible(false);}
    else if (index==1) {
        ui->groupBox_4->setVisible(false);
        ui->groupBox_5->setVisible(true);}
}


// on the fly calculations of ppol
void MainWindow::on_doubleSpinBox_5_valueChanged(double arg1)
{
    ppol = (arg1-ui->doubleSpinBox_6->value())/(2*arg1);
    ui->label_15->setText("Ppol="+QString::number(ppol));
}

void MainWindow::on_doubleSpinBox_6_valueChanged(double arg1)
{
    ppol = (ui->doubleSpinBox_5->value()-arg1)/(2*ui->doubleSpinBox_5->value());
    ui->label_15->setText("Ppol="+QString::number(ppol));
}

// on the fly calculations of pion
void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{

    if (ui->comboBox_5->currentIndex()==0){
        //
          pion = ( 1 - (ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value()) )/( arg1/ui->doubleSpinBox_4->value() - (ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value()) );
          ui->label_16->setText("Pion="+QString::number(pion));
    }
    else if (ui->comboBox_5->currentIndex()==1) {
        //
          pion = ( 1 - (ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value())*(ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value()) )/( arg1/ui->doubleSpinBox_4->value() - (ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value())*(ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value()) );
          ui->label_16->setText("Pion="+QString::number(pion));
    }




}

void MainWindow::on_doubleSpinBox_4_valueChanged(double arg1)
{


    if (ui->comboBox_5->currentIndex()==0){
        //
          pion = ( 1 - (ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value()) )/( ui->doubleSpinBox_3->value()/arg1 - (ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value()) );
          ui->label_16->setText("Pion="+QString::number(pion));
    }
    else if (ui->comboBox_5->currentIndex()==1){
        //
          pion = ( 1 - (ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value())*(ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value()) )/ ( ui->doubleSpinBox_3->value()/arg1 - (ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value())*(ui->doubleSpinBox_7->value()/ui->doubleSpinBox_8->value()) );
          ui->label_16->setText("Pion="+QString::number(pion));
    }


}

void MainWindow::on_doubleSpinBox_7_valueChanged(double arg1)
{

    if (ui->comboBox_5->currentIndex()==0){
        //
          pion = ( 1 - (arg1/ui->doubleSpinBox_8->value()) )/( ui->doubleSpinBox_3->value()/ui->doubleSpinBox_4->value() - (arg1/ui->doubleSpinBox_8->value()) );
          ui->label_16->setText("Pion="+QString::number(pion));
    }
    else if (ui->comboBox_5->currentIndex()==1){
        //
          pion = ( 1 - (arg1/ui->doubleSpinBox_8->value())*(arg1/ui->doubleSpinBox_8->value()) )/( ui->doubleSpinBox_3->value()/ui->doubleSpinBox_4->value() - (arg1/ui->doubleSpinBox_8->value())*(arg1/ui->doubleSpinBox_8->value()) );
          ui->label_16->setText("Pion="+QString::number(pion));
    }


}

void MainWindow::on_doubleSpinBox_8_valueChanged(double arg1)
{
    if (ui->comboBox_5->currentIndex()==0){
        //
          pion = ( 1 - (ui->doubleSpinBox_7->value()/arg1) )/( ui->doubleSpinBox_3->value()/ui->doubleSpinBox_4->value() - (ui->doubleSpinBox_7->value()/arg1) );
          ui->label_16->setText("Pion="+QString::number(pion));
    }
    else if (ui->comboBox_5->currentIndex()==1){
        //
          pion = ( 1 - (ui->doubleSpinBox_7->value()/arg1)*(ui->doubleSpinBox_7->value()/arg1) )/( ui->doubleSpinBox_3->value()/ui->doubleSpinBox_4->value() - (ui->doubleSpinBox_7->value()/arg1)*(ui->doubleSpinBox_7->value()/arg1) );
          ui->label_16->setText("Pion="+QString::number(pion));
    }
}



void MainWindow::on_comboBox_5_currentIndexChanged(int index)
{
    on_doubleSpinBox_3_valueChanged(ui->doubleSpinBox_3->value());
}




// Here we llist the slots corrresponding to table lookup
void MainWindow::on_doubleSpinBox_9_valueChanged(double arg1)
{
    //arg1 <- this is the field size input
    double fieldSize=arg1;
    double energy = ui->doubleSpinBox_10->value();

    interp interp;
    double value = interp.bilinearInterp(fieldSize, energy, SptabulatedFS, SptabulatedEner, SptabulatedVal);
    ui->label_18->setText("Sp= "+QString::number(value));

}

void MainWindow::on_doubleSpinBox_10_valueChanged(double arg1)
{
    //arg1 <- this is the energy input
    double energy=arg1;
    double fieldSize = ui->doubleSpinBox_9->value();

    interp interp;
    double value = interp.bilinearInterp(fieldSize, energy, SptabulatedFS, SptabulatedEner, SptabulatedVal);
    ui->label_18->setText("Sp= "+QString::number(value));
}

void MainWindow::on_doubleSpinBox_11_valueChanged(double arg1)
{
    //arg1 <- this is the field size input
    double fieldSize=arg1;
    double energy = ui->doubleSpinBox_12->value();

    interp interp;
    double value = interp.bilinearInterp(fieldSize, energy, SctabulatedFS, SctabulatedEner, SctabulatedVal);
    ui->label_21->setText("Sc= "+QString::number(value));
}

void MainWindow::on_doubleSpinBox_12_valueChanged(double arg1)
{
    //arg1 <- this is the energy input
    double energy=arg1;
    double fieldSize = ui->doubleSpinBox_11->value();

    interp interp;
    double value = interp.bilinearInterp(fieldSize, energy, SctabulatedFS, SctabulatedEner, SctabulatedVal);
    ui->label_21->setText("Sc= "+QString::number(value));
}

void MainWindow::on_doubleSpinBox_17_valueChanged(double arg1)
{
    //arg1 <- this is the field size input
    double fieldSize=arg1;
    double energy = ui->doubleSpinBox_18->value();
    double depth = ui->doubleSpinBox_19->value();

    interp interp;
    double value = interp.bilinearInterp(fieldSize, energy, SctabulatedFS, SctabulatedEner, SctabulatedVal);
    ui->label_21->setText("Sc= "+QString::number(value));
}

void MainWindow::on_doubleSpinBox_18_valueChanged(double arg1)
{
    //arg1 <- this is the field size input
    double energy=arg1;
    double fieldSize = ui->doubleSpinBox_17->value();
    double depth = ui->doubleSpinBox_19->value();

    interp interp;
    double value = interp.bilinearInterp(fieldSize, energy, SctabulatedFS, SctabulatedEner, SctabulatedVal);
    ui->label_21->setText("Sc= "+QString::number(value));
}

void MainWindow::on_doubleSpinBox_19_valueChanged(double arg1)
{
    //arg1 <- this is the field size input
    double depth=arg1;
    double fieldSize = ui->doubleSpinBox_17->value();
    double energy = ui->doubleSpinBox_18->value();

    interp interp;
    double value = interp.bilinearInterp(fieldSize, energy, SctabulatedFS, SctabulatedEner, SctabulatedVal);
    ui->label_21->setText("Sc= "+QString::number(value));
}
