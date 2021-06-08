#include "gui.h"

void DataCalculation()
{
    /* ------- Performance ------- */
    GetPerforanceFurnaceStat(performance_stat);
    GetPerformanceFurnaceDiff(performance_diff);
    GetPerformanceMembership(min_perf, max_perf, furnace_count, 
        performance_diff, performance_membership);
    UpdateProperties(performance_membership, &performance_properties);
    InitDataLength(performance_stat, perf_src_buf, perf_src_len);

    printf("\nPerformance diff:\n");
    PrintingSquarArray(performance_diff);

    printf("\nPerformance Membership:\n");
    PrintingSquarArray(performance_membership);

    printf("\nPerformance Properties:\n");
    printf("    Ref status: %s\n", performance_properties.ref_status);
    printf("    Sym status: %s\n", performance_properties.sym_status);
    printf("    Trs status: %s\n", performance_properties.trs_status);

    /* ------- Volume ------- */
    GetVolumeFurnaceStat(volume_stat);
    GetVolumeFurnaceDiff(volume_diff);
    GetVolumeMembership(min_vol, max_vol, furnace_count,
        volume_diff, volume_membership);
    UpdateProperties(volume_membership, &volume_properties);
    InitDataLength(volume_stat, volu_src_buf, volu_src_len);

    printf("\nVolume diff:\n");
    PrintingSquarArray(volume_diff);

    printf("\nVolume Membership:\n");
    PrintingSquarArray(volume_membership);

    printf("\nVolume Properties:\n");
    printf("    Ref status: %s\n", volume_properties.ref_status);
    printf("    Sym status: %s\n", volume_properties.sym_status);
    printf("    Trs status: %s\n", volume_properties.trs_status);
}