#include "engine.h"

void UpdateMenuPosition(struct nk_rect *menu,
    int x, int y, int w, int h)
{
    menu->x = x; menu->y = y;
    menu->w = w; menu->h = h;

    matrix_width = screen_width - screen_gaps * 2;
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

void SetMenuColor(struct nk_context *nk_ctx)
{
    struct nk_color table[NK_COLOR_COUNT];
        table[NK_COLOR_TEXT] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(30, 33, 40, 215);
        table[NK_COLOR_HEADER] = nk_rgba(181, 45, 69, 220);
        table[NK_COLOR_BORDER] = nk_rgba(51, 55, 67, 255);
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
        table[NK_COLOR_EDIT] = nk_rgba(51, 55, 67, 225);
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
}

void Intro(SDL_Window *window, struct nk_context* nk_ctx)
{
    if (screen_width >= screen_height)
        screen_gaps = screen_width;
    else if (screen_width < screen_height)
        screen_gaps = screen_height;

    struct nk_color table[NK_COLOR_COUNT];
    table[NK_COLOR_WINDOW] = nk_rgba(60, 60, 60, 25);
    table[NK_COLOR_TEXT] = nk_rgba(180, 180, 180, 255);
    nk_style_from_table(nk_ctx, table);

    while (screen_gaps > default_screen_gaps)
    {
        GetEvent(window, nk_ctx);
        screen_gaps -= gaps_step;
        UpdateMenuPosition(&main_menu, main_menu_gaps);
        Render(window, nk_ctx);
    }
}

int view_flag = 0;
nk_bool status = nk_false;
void Canvas(SDL_Window *window, struct nk_context* nk_ctx)
{
   if (nk_begin(nk_ctx, "", main_menu,
            NK_WINDOW_BORDER
            | NK_WINDOW_NO_SCROLLBAR
            | NK_WINDOW_BACKGROUND)) 
    {
        nk_layout_row_dynamic(nk_ctx, (screen_height-screen_gaps*2.0)/5.0, 1);
        nk_spacing(nk_ctx, 2);
        nk_label(nk_ctx, "Hello World!", NK_TEXT_CENTERED);
        if (nk_checkbox_label(nk_ctx, "View", &status)) view_flag = !view_flag;
    }
    nk_end(nk_ctx);
}

void ViewData(struct nk_context * nk_ctx,
    float data[furnace_count][furnace_count])
{
    static int data_len[furnace_count][furnace_count];
    static char data_buf[furnace_count][furnace_count][50];
    static char data_number[furnace_count][10];

    for (int i = 0; i < furnace_count; i++) {
        sprintf(data_number[i], "x%i ", i+1);
        for (int j = 0; j < furnace_count; j++)
            data_len[i][j] = sprintf(data_buf[i][j], "%4.3f", data[i][j]);
    }

    nk_layout_row_static(nk_ctx, 40, 50, 11);
        nk_spacing(nk_ctx, 1);

    for (int i = 0; i < furnace_count; i++)
        nk_text(nk_ctx, data_number[i], 3, NK_TEXT_CENTERED);

    for (int i = 0; i < furnace_count; i++) {
        nk_text(nk_ctx, data_number[i], 3, NK_TEXT_CENTERED);
        for (int j = 0; j < furnace_count; j++) {
            nk_edit_string(nk_ctx, NK_EDIT_READ_ONLY,
                data_buf[i][j], &data_len[i][j], 6, nk_filter_float);
            data_buf[i][j][data_len[i][j]] = '\0';
        }
    }
}

void ViewMatr(struct nk_context * nk_ctx, struct nk_rect * region)
{

/*
    if (menu->w < matrix_width) menu->w += gaps_step;
    else if (menu->w > matrix_width) menu->w -= gaps_step;
*/

    #define _performance_matrix 0x1
    #define _volume_matrix      0x2

    static int matrix = _performance_matrix;

    static int view_flag = 1;
    nk_flags nk_flags = \
        NK_WINDOW_BORDER
        | NK_WINDOW_NO_SCROLLBAR
        ;
    if (!view_flag) nk_flags |= NK_WINDOW_CLOSED;

    if (nk_begin(nk_ctx, "Data Editor", *region, nk_flags)) {
        nk_layout_row_dynamic(nk_ctx, 25, 1);
        matrix = nk_option_label(nk_ctx, "Performance", 
            matrix == _performance_matrix) ? _performance_matrix : matrix;
        matrix = nk_option_label(nk_ctx, "Volume",
            matrix == _volume_matrix) ? _volume_matrix : matrix;

        switch (matrix)
        {
            case _performance_matrix:
                ViewData(nk_ctx, performance_membership);
                break;
            case _volume_matrix:
                ViewData(nk_ctx, volume_membership);
                break;
        }
    } nk_end(nk_ctx);
}
