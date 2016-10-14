/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_91641331_INCLUDED
#define BINARYDATA_H_91641331_INCLUDED

namespace BinaryData
{
    extern const char*   Bad_roll_ogg;
    const int            Bad_roll_oggSize = 25162;

    extern const char*   Bad_roll_wav_ogg;
    const int            Bad_roll_wav_oggSize = 27581;

    extern const char*   Bell_Forbidden2_ogg;
    const int            Bell_Forbidden2_oggSize = 62079;

    extern const char*   Chhhhaah_ogg;
    const int            Chhhhaah_oggSize = 53584;

    extern const char*   cr78_rim_spring_003_ogg;
    const int            cr78_rim_spring_003_oggSize = 53826;

    extern const char*   Cym_MoonTrouper1_ogg;
    const int            Cym_MoonTrouper1_oggSize = 34832;

    extern const char*   Cym_OldTapeNoGood_ogg;
    const int            Cym_OldTapeNoGood_oggSize = 112025;

    extern const char*   Dark_hit_ogg;
    const int            Dark_hit_oggSize = 254349;

    extern const char*   DUBRIM06_ogg;
    const int            DUBRIM06_oggSize = 23645;

    extern const char*   KICKHAT02_ogg;
    const int            KICKHAT02_oggSize = 15419;

    extern const char*   noiz_hats_springeq_3_004_ogg;
    const int            noiz_hats_springeq_3_004_oggSize = 13824;

    extern const char*   phat_break1_ogg;
    const int            phat_break1_oggSize = 31117;

    extern const char*   Ride_BluesbreakDrums2_ogg;
    const int            Ride_BluesbreakDrums2_oggSize = 93069;

    extern const char*   Ride_TastyReal_03_ogg;
    const int            Ride_TastyReal_03_oggSize = 86759;

    extern const char*   Roll_ogg;
    const int            Roll_oggSize = 14840;

    extern const char*   SineHackDelay_6_atmos_lp_ogg;
    const int            SineHackDelay_6_atmos_lp_oggSize = 127269;

    extern const char*   SnareDeep_ogg;
    const int            SnareDeep_oggSize = 23982;

    extern const char*   SnareThud_ogg;
    const int            SnareThud_oggSize = 26782;

    extern const char*   thisWorld_end_ogg;
    const int            thisWorld_end_oggSize = 159581;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 19;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
