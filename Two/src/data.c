
void DataCalculation(int furnace_count)
{
    /* ------- Performance ------- */
    float performance_stat[furnace_count][furnace_count];
    GetPerformanceFurnaceDiff(furnace_count, performance_stat);

    float min_perf = 50; float max_perf = 500;
    float performance_membership[furnace_count][furnace_count];
    GetPerformanceMembership(min_perf, max_perf, furnace_count, 
        performance_stat, performance_membership);

    struct Properties performance_properties;
    UpdateProperties(furnace_count,
        performance_membership, &performance_properties);

    printf("\nPerformance diff:\n");
    PrintingSquarArray(furnace_count, performance_stat);
    printf("\nPerformance Membership:\n");
    PrintingSquarArray(furnace_count, performance_membership);
    printf("\nPerformance Properties:\n");
    printf("    Ref status code: %#x\n", performance_properties.ref_status);
    printf("    Sym status code: %#x\n", performance_properties.sym_status);
    printf("    Trs status code: %#x\n", performance_properties.trs_status);

    /* ------- Volume ------- */
    float volume_stat[furnace_count][furnace_count];
    GetVolumeFurnaceDiff(furnace_count, volume_stat);

    float min_vol = 0; float max_vol = 35;
    float volume_membership[furnace_count][furnace_count];
    GetVolumeMembership(min_vol, max_vol, furnace_count,
        volume_stat, volume_membership);

    struct Properties volume_properties;
    UpdateProperties(furnace_count, 
        volume_membership, &volume_properties);

    printf("\nVolume diff:\n");
    PrintingSquarArray(furnace_count, volume_stat);
    printf("\nVolume Membership:\n");
    PrintingSquarArray(furnace_count, volume_membership);
    printf("\nVolume Properties:\n");
    printf("    Ref status code: %#x\n", volume_properties.ref_status);
    printf("    Sym status code: %#x\n", volume_properties.sym_status);
    printf("    Trs status code: %#x\n", volume_properties.trs_status);
}