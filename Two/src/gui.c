#include "engine.h"

void UpdateMenuPosition(struct nk_rect *menu,
    int x, int y, int w, int h)
{
    menu->x = x; menu->y = y;
    menu->w = w; menu->h = h;
}

void SetFont(struct nk_context *nk_ctx,
    const char *font_path, const unsigned char font_size)
{
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *font = nk_font_atlas_add_from_file(
        atlas, font_path, font_size, 0);
    nk_sdl_font_stash_end();
    nk_style_set_font(nk_ctx, &font->handle);
}

void SetMenuColor(struct nk_context *nk_ctx, int color)
{
    if (color == 0) {
        struct nk_color table[NK_COLOR_COUNT];
            table[NK_COLOR_WINDOW] = nk_rgba(60, 60, 60, 30);
            table[NK_COLOR_TEXT] = nk_rgba(180, 180, 180, 255);
            table[NK_COLOR_HEADER] = nk_rgba(181, 45, 69, 220);
            table[NK_COLOR_BORDER] = nk_rgba(51, 55, 67, 180);
            table[NK_COLOR_BUTTON] = nk_rgba(181, 45, 69, 255);
            table[NK_COLOR_BUTTON_HOVER] = nk_rgba(190, 50, 70, 255);
            table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(195, 55, 75, 255);
            table[NK_COLOR_TOGGLE] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 60, 60, 255);
            table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(181, 45, 69, 255);
            table[NK_COLOR_SELECT] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(181, 45, 69, 255);
            table[NK_COLOR_SLIDER] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(181, 45, 69, 255);
            table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(186, 50, 74, 255);
            table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(191, 55, 79, 255);
            table[NK_COLOR_PROPERTY] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_EDIT] = nk_rgba(80, 40, 40, 225);
            table[NK_COLOR_EDIT_CURSOR] = nk_rgba(190, 190, 190, 255);
            table[NK_COLOR_COMBO] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_CHART] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_CHART_COLOR] = nk_rgba(170, 40, 60, 255);
            table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba( 255, 0, 0, 255);
            table[NK_COLOR_SCROLLBAR] = nk_rgba(30, 33, 40, 255);
            table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
            table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
            table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
            table[NK_COLOR_TAB_HEADER] = nk_rgba(181, 45, 69, 220);
        nk_style_from_table(nk_ctx, table);
    } else {
        struct nk_color table[NK_COLOR_COUNT];
            table[NK_COLOR_EDIT] = nk_rgba(40, 00, 80, 225);
            table[NK_COLOR_EDIT_CURSOR] = nk_rgba(190, 190, 190, 255);
            table[NK_COLOR_WINDOW] = nk_rgba(60, 60, 60, 30);
            table[NK_COLOR_TEXT] = nk_rgba(180, 180, 180, 255);
            table[NK_COLOR_HEADER] = nk_rgba(181, 45, 69, 220);
            table[NK_COLOR_BORDER] = nk_rgba(51, 55, 67, 180);
            table[NK_COLOR_BUTTON] = nk_rgba(181, 45, 69, 255);
            table[NK_COLOR_BUTTON_HOVER] = nk_rgba(190, 50, 70, 255);
            table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(195, 55, 75, 255);
            table[NK_COLOR_TOGGLE] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 60, 60, 255);
            table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(181, 45, 69, 255);
            table[NK_COLOR_SELECT] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(181, 45, 69, 255);
            table[NK_COLOR_SLIDER] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(181, 45, 69, 255);
            table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(186, 50, 74, 255);
            table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(191, 55, 79, 255);
            table[NK_COLOR_PROPERTY] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_COMBO] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_CHART] = nk_rgba(51, 55, 67, 255);
            table[NK_COLOR_CHART_COLOR] = nk_rgba(170, 40, 60, 255);
            table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba( 255, 0, 0, 255);
            table[NK_COLOR_SCROLLBAR] = nk_rgba(30, 33, 40, 255);
            table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
            table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
            table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
            table[NK_COLOR_TAB_HEADER] = nk_rgba(181, 45, 69, 220);
        nk_style_from_table(nk_ctx, table);
    }
}

void Intro(SDL_Window *window, struct nk_context* nk_ctx)
{
    screen_gaps = screen_width-100;
    while (screen_gaps > default_screen_gaps)
    {
        GetEvent(window, nk_ctx);
        screen_gaps -= gaps_step;
        UpdateMenuPosition(&main_menu, main_menu_gaps);
        Render(window, nk_ctx);
    }
}

void InitDataLength(float data[furnace_count],
    char data_buf[furnace_count][20], int data_len[furnace_count])
{
    for (int i = 0; i < furnace_count; i++)
        data_len[i] = sprintf(data_buf[i], "%5.4f", data[i]);
}

void ViewRange(struct nk_context * nk_ctx)
{
    nk_layout_row_static(nk_ctx, 35, 60, 3);
    nk_label(nk_ctx, "Range:", NK_TEXT_LEFT);
    switch (sets) {
        case _performance:
            nk_edit_string(nk_ctx, NK_EDIT_SIMPLE,
                min_perf_buf, &min_perf_len, 7, nk_filter_float);
            min_perf_buf[min_perf_len] = '\0';
            min_perf = atof(min_perf_buf);
            nk_edit_string(nk_ctx, NK_EDIT_SIMPLE,
                max_perf_buf, &max_perf_len, 7, nk_filter_float);
            max_perf_buf[max_perf_len] = '\0';
            max_perf = atof(max_perf_buf);
            break;
        case _volume:
            nk_edit_string(nk_ctx, NK_EDIT_SIMPLE,
                min_vol_buf, &min_vol_len, 7, nk_filter_float);
            min_vol_buf[min_vol_len] = '\0';
            min_vol = atof(min_vol_buf);
            nk_edit_string(nk_ctx, NK_EDIT_SIMPLE,
                max_vol_buf, &max_vol_len, 7, nk_filter_float);
            max_vol_buf[max_vol_len] = '\0';
            max_vol = atof(max_vol_buf);
            break;
    }
    nk_spacing(nk_ctx, 1);
    nk_label(nk_ctx, "min", NK_TEXT_CENTERED);
    nk_label(nk_ctx, "max", NK_TEXT_CENTERED);
}

void ViewSrc(struct nk_context * nk_ctx, float data[furnace_count],
    char data_buf[furnace_count][20], int data_len[furnace_count])
{
    SetMenuColor(nk_ctx, 1);

    static char data_number[furnace_count][10];
    static int init = 1;
    if (init) {
        for (int i = 0; i < furnace_count; i++) {
            sprintf(data_number[i], "x%i ", i+1);
        } init = 0;
    } 
    
    nk_layout_row_static(nk_ctx, 28, 200, 1);
        nk_label(nk_ctx, "Source data:", NK_TEXT_LEFT);
    nk_layout_row_static(nk_ctx, 35, 60, 11);
        nk_spacing(nk_ctx, 1);
        for (int i = 0; i < furnace_count; i++) {
            nk_edit_string(nk_ctx, NK_EDIT_SIMPLE,
                data_buf[i], &data_len[i], 7, nk_filter_float);
            data_buf[i][data_len[i]] = '\0';
            data[i] = atof(data_buf[i]);
        }
        nk_spacing(nk_ctx, 1);
        for (int i = 0; i < furnace_count; i++)
            nk_label(nk_ctx, data_number[i], NK_TEXT_CENTERED);
    ViewRange(nk_ctx);
}

void ViewRes(struct nk_context * nk_ctx,
    float data[furnace_count][furnace_count], struct Properties prop)
{
    static int data_len[furnace_count][furnace_count];
    static char data_buf[furnace_count][furnace_count][50];
    static char data_number[furnace_count][10];

    for (int i = 0; i < furnace_count; i++) {
        sprintf(data_number[i], "x%i ", i+1);
        for (int j = 0; j < furnace_count; j++)
            data_len[i][j] = sprintf(data_buf[i][j], "%5.4f", data[i][j]);
    }

    nk_layout_row_dynamic(nk_ctx, 20, 1);
    value = nk_option_label(nk_ctx, "Membership",
        value == _membership) ? _membership : value;
    value = nk_option_label(nk_ctx, "Difference",
        value == _difference) ? _difference : value;

    nk_layout_row_static(nk_ctx, 35, 60, 11);
        nk_spacing(nk_ctx, 1);
    for (int i = 0; i < furnace_count; i++)
        nk_label(nk_ctx, data_number[i], NK_TEXT_CENTERED);
    for (int i = 0; i < furnace_count; i++) {
        nk_label(nk_ctx, data_number[i], NK_TEXT_CENTERED);
        for (int j = 0; j < furnace_count; j++) {

            if (i == j) SetMenuColor(nk_ctx, 1);
            else SetMenuColor(nk_ctx, 0);

            nk_edit_string(nk_ctx, NK_EDIT_READ_ONLY,
                data_buf[i][j], &data_len[i][j], 7, nk_filter_float);
            data_buf[i][j][data_len[i][j]] = '\0';
        }
    }
    nk_layout_row_dynamic(nk_ctx, 10, 1);
        nk_spacing(nk_ctx, 1);
    nk_layout_row_dynamic(nk_ctx, 20, 1);
        nk_label(nk_ctx, "Relationship properties:", NK_TEXT_LEFT);
        nk_label(nk_ctx, prop.ref_status, NK_TEXT_LEFT);
        nk_label(nk_ctx, prop.sym_status, NK_TEXT_LEFT);
        nk_label(nk_ctx, prop.trs_status, NK_TEXT_LEFT);
}

void ViewMatr(struct nk_context * nk_ctx, struct nk_rect * region)
{
    static int view_flag = 1;
    nk_flags nk_flags = \
        NK_WINDOW_BORDER
        | NK_WINDOW_NO_SCROLLBAR
        ;
    if (!view_flag) nk_flags |= NK_WINDOW_CLOSED;

    if (nk_begin(nk_ctx, "Data Editor", *region, nk_flags)) {
        nk_layout_row_dynamic(nk_ctx, 20, 1);
        sets = nk_option_label(nk_ctx, "Performance",
            sets == _performance) ? _performance : sets;
        sets = nk_option_label(nk_ctx, "Volume",
            sets == _volume) ? _volume : sets;

        switch (sets) {
            case _performance:
                GetPerformanceFurnaceDiff(performance_diff);
                GetPerformanceMembership(min_perf, max_perf, furnace_count,
                    performance_diff, performance_membership);
                UpdateProperties(performance_membership, &performance_properties);
                ViewSrc(nk_ctx, performance_stat, perf_src_buf, perf_src_len);
                switch (value) {
                    case _membership:
                        ViewRes(nk_ctx, performance_membership,
                            performance_properties);
                        break;
                    case _difference:
                        ViewRes(nk_ctx, performance_diff,
                            performance_properties);
                        break;
                }
                break;
            case _volume:
                GetVolumeFurnaceDiff(volume_diff);
                GetVolumeMembership(min_vol, max_vol, furnace_count,
                    volume_diff, volume_membership);
                UpdateProperties(volume_membership, &volume_properties);
                ViewSrc(nk_ctx, volume_stat, volu_src_buf, volu_src_len);
                switch (value) {
                    case _membership:
                        ViewRes(nk_ctx, volume_membership, 
                            volume_properties);
                        break;
                    case _difference:
                        ViewRes(nk_ctx, volume_diff, 
                            volume_properties);
                        break;
                }
                break;
        }
    } nk_end(nk_ctx);
}
