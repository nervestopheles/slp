void DataCalculation()
{
    /* ------- Performance ------- */
    GetPerforanceFurnaceStat(performance_stat);
    GetPerformanceFurnaceDiff(furnace_count, performance_diff);
    GetPerformanceMembership(min_perf, max_perf, furnace_count, 
        performance_diff, performance_membership);
    UpdateProperties(furnace_count,
        performance_membership, &performance_properties);

    printf("\nPerformance diff:\n");
    PrintingSquarArray(furnace_count, performance_diff);

    printf("\nPerformance Membership:\n");
    PrintingSquarArray(furnace_count, performance_membership);

    printf("\nPerformance Properties:\n");
    printf("    Ref status: %s\n", performance_properties.ref_status);
    printf("    Sym status: %s\n", performance_properties.sym_status);
    printf("    Trs status: %s\n", performance_properties.trs_status);

    /* ------- Volume ------- */
    GetVolumeFurnaceStat(volume_stat);
    GetVolumeFurnaceDiff(furnace_count, volume_diff);
    GetVolumeMembership(min_vol, max_vol, furnace_count,
        volume_diff, volume_membership);
    UpdateProperties(furnace_count, 
        volume_membership, &volume_properties);

    printf("\nVolume diff:\n");
    PrintingSquarArray(furnace_count, volume_diff);

    printf("\nVolume Membership:\n");
    PrintingSquarArray(furnace_count, volume_membership);

    printf("\nVolume Properties:\n");
    printf("    Ref status: %s\n", volume_properties.ref_status);
    printf("    Sym status: %s\n", volume_properties.sym_status);
    printf("    Trs status: %s\n", volume_properties.trs_status);
}